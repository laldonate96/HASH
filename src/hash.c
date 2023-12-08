#include <stdlib.h>
#include <string.h>

#include "hash.h"

#define FACTOR_CARGA_MAXIMO 0.7

typedef struct par {
	char *clave;
	void *elemento;
	struct par *siguiente;
} par_t;

struct hash {
	size_t capacidad;
	size_t cantidad;
	par_t **tabla;
};

size_t funcion_hash(const char *clave, size_t capacidad)
{
	size_t hash = 0;
	size_t const p = 31;
	size_t const m = 1e9 + 9;

	for (size_t i = 0; clave[i] != '\0'; i++) {
		hash = (hash * p + (size_t)clave[i]) % m;
	}

	return hash % capacidad;
}

char *copiar_clave(const char *original)
{
	char *copia = malloc(strlen(original) + 1);
	if (copia == NULL)
		return NULL;
	strcpy(copia, original);
	return copia;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));

	if (!hash)
		return NULL;

	if (capacidad < 3)
		capacidad = 3;

	hash->capacidad = capacidad;
	hash->cantidad = 0;

	hash->tabla = calloc(capacidad, sizeof(par_t *));

	if (!hash->tabla) {
		free(hash);
		return NULL;
	}

	return hash;
}

bool rehash(hash_t *hash)
{
	if (!hash)
		return false;

	hash_t *hash_nuevo = hash_crear(hash->capacidad * 2);
	if (!hash_nuevo) {
		return false;
	}

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *par = hash->tabla[i];
		while (par) {
			hash_insertar(hash_nuevo, par->clave, par->elemento,
				      NULL);
			par_t *siguiente = par->siguiente;
			free(par->clave);
			free(par);
			par = siguiente;
		}
	}

	free(hash->tabla);

	hash->capacidad = hash_nuevo->capacidad;
	hash->cantidad = hash_nuevo->cantidad;
	hash->tabla = hash_nuevo->tabla;

	free(hash_nuevo);

	return true;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;

	if ((float)hash->cantidad / (float)hash->capacidad >
	    FACTOR_CARGA_MAXIMO) {
		rehash(hash);
	}

	size_t pos = funcion_hash(clave, hash->capacidad);

	par_t *par = hash->tabla[pos];

	while (par) {
		if (strcmp(par->clave, clave) == 0) {
			if (anterior)
				*anterior = par->elemento;
			par->elemento = elemento;
			return hash;
		}
		par = par->siguiente;
	}

	par = malloc(sizeof(par_t));

	if (!par)
		return NULL;

	par->clave = copiar_clave(clave);

	if (!par->clave) {
		free(par);
		return NULL;
	}

	par->elemento = elemento;
	par->siguiente = hash->tabla[pos];
	hash->tabla[pos] = par;
	hash->cantidad++;

	if (anterior)
		*anterior = NULL;

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t pos = funcion_hash(clave, hash->capacidad);
	par_t *actual = hash->tabla[pos];
	par_t *anterior = NULL;

	while (actual && strcmp(actual->clave, clave) != 0) {
		anterior = actual;
		actual = actual->siguiente;
	}

	if (!actual)
		return NULL;

	if (anterior)
		anterior->siguiente = actual->siguiente;
	else
		hash->tabla[pos] = actual->siguiente;

	void *elemento = actual->elemento;

	free(actual->clave);
	free(actual);

	hash->cantidad--;

	return elemento;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t pos = funcion_hash(clave, hash->capacidad);
	par_t *actual = hash->tabla[pos];

	while (actual && strcmp(actual->clave, clave) != 0) {
		actual = actual->siguiente;
	}

	return (actual) ? actual->elemento : NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t pos = funcion_hash(clave, hash->capacidad);
	par_t *actual = hash->tabla[pos];

	while (actual) {
		if (strcmp(actual->clave, clave) == 0) {
			return true;
		}
		actual = actual->siguiente;
	}

	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;
	return hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *par = hash->tabla[i];
		while (par) {
			if (destructor)
				destructor(par->elemento);
			free(par->clave);
			par_t *siguiente = par->siguiente;
			free(par);
			par = siguiente;
		}
	}
	free(hash->tabla);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	size_t n = 0;
	if (!hash || !f)
		return n;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *actual = hash->tabla[i];

		while (actual) {
			if (!f(actual->clave, actual->elemento, aux)) {
				n++;
				actual = actual->siguiente;
				return n;
			}

			n++;
			actual = actual->siguiente;
		}
	}

	return n;
}
