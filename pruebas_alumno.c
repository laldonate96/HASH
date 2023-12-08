#include "pa2m.h"
#include "src/hash.h"
#include <stdlib.h>

void prueba_hash_crear()
{
	hash_t *hash = hash_crear(3);

	pa2m_afirmar(hash != NULL, "Puedo crear un hash.");

	hash_destruir(hash);
}

void prueba_hash_crear_mayor_a_3()
{
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash != NULL,
		     "Puedo crear un hash con capacidad mayor a 3.");

	hash_destruir(hash);
}

void prueba_hash_crear_menor_a_3()
{
	hash_t *hash = hash_crear(2);

	pa2m_afirmar(
		hash != NULL,
		"Si intento crear un hash con capacidad menor a 3, se crea con capacidad igual a 3.");

	hash_destruir(hash);
}

void prueba_hash_insertar_en_hash_nulo()
{
	hash_t *hash = NULL;
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	pa2m_afirmar(hash_insertar(hash, clave, elemento, NULL) == NULL,
		     "No puedo insertar en un hash nulo.");

	free(elemento);
}

void prueba_hash_insertar_clave_nula()
{
	hash_t *hash = hash_crear(3);
	char *clave = NULL;
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	pa2m_afirmar(hash_insertar(hash, clave, elemento, NULL) == NULL,
		     "No puedo insertar una clave nula.");

	free(elemento);
	hash_destruir(hash);
}

void prueba_hash_insertar_elemento_nulo()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = NULL;

	pa2m_afirmar(hash_insertar(hash, clave, elemento, NULL) != NULL,
		     "Puedo insertar un elemento nulo con una clave válida.");

	hash_destruir(hash);
}

void prueba_hash_insertar()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	pa2m_afirmar(hash_insertar(hash, clave, elemento, NULL) != NULL,
		     "Puedo insertar un elemento con una clave válida.");

	hash_destruir(hash);

	free(elemento);
}

void prueba_hash_insertar_varios()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	char *clave2 = "clave2";
	char *clave3 = "clave3";

	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));

	*elemento1 = 1;
	*elemento2 = 2;
	*elemento3 = 3;

	hash_insertar(hash, clave1, elemento1, NULL);
	hash_insertar(hash, clave2, elemento2, NULL);
	hash_insertar(hash, clave3, elemento3, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "Puedo insertar varios elementos en un hash.");

	hash_destruir(hash);

	free(elemento1);
	free(elemento2);
	free(elemento3);
}

void prueba_hash_insertar_varios_causando_rehash()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	char *clave2 = "clave2";
	char *clave3 = "clave3";
	char *clave4 = "clave4";

	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));
	int *elemento4 = malloc(sizeof(int));

	*elemento1 = 1;
	*elemento2 = 2;
	*elemento3 = 3;
	*elemento4 = 4;

	hash_insertar(hash, clave1, elemento1, NULL);
	hash_insertar(hash, clave2, elemento2, NULL);
	hash_insertar(hash, clave3, elemento3, NULL);
	hash_insertar(hash, clave4, elemento4, NULL);

	pa2m_afirmar(
		hash_cantidad(hash) == 4,
		"Puedo insertar varios elementos en un hash causando un rehash.");

	hash_destruir(hash);

	free(elemento1);
	free(elemento2);
	free(elemento3);
	free(elemento4);
}

void prueba_hash_actualizar_elemento()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	int *elemento_actualizado = malloc(sizeof(int));
	*elemento_actualizado = 2;

	hash_insertar(hash, clave, elemento_actualizado, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 1,
		     "Puedo actualizar un elemento en un hash.");

	hash_destruir(hash);

	free(elemento);
	free(elemento_actualizado);
}

void prueba_hash_quitar_en_hash_nulo()
{
	hash_t *hash = NULL;
	char *clave = "clave";

	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "No puedo quitar un elemento de un hash nulo.");
}

void prueba_hash_quitar_clave_nula()
{
	hash_t *hash = hash_crear(3);
	char *clave = NULL;

	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "No puedo quitar un elemento de un hash con clave nula.");

	hash_destruir(hash);
}

void prueba_hash_quitar_clave_no_existente()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";

	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "No puedo quitar una clave de un hash si no existe.");

	hash_destruir(hash);
}

void prueba_hash_quitar_clave_existente()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	pa2m_afirmar(hash_quitar(hash, clave) == elemento,
		     "Puedo quitar una clave de un hash si existe.");

	hash_destruir(hash);

	free(elemento);
}

void prueba_hash_quitar_clave_dos_veces()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	hash_quitar(hash, clave);

	pa2m_afirmar(hash_quitar(hash, clave) == NULL,
		     "No puedo quitar una clave de un hash si ya no existe.");

	hash_destruir(hash);

	free(elemento);
}

void prueba_hash_obtener_de_un_hash_nulo()
{
	hash_t *hash = NULL;
	char *clave = "clave";

	pa2m_afirmar(hash_obtener(hash, clave) == NULL,
		     "No puedo obtener un elemento de un hash nulo.");
}

void prueba_hash_obtener_de_un_hash_con_clave_nula()
{
	hash_t *hash = hash_crear(3);
	char *clave = NULL;

	pa2m_afirmar(hash_obtener(hash, clave) == NULL,
		     "No puedo obtener un elemento de un hash con clave nula.");

	hash_destruir(hash);
}

void prueba_hash_obtener_de_un_hash_con_clave_no_existente()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";

	pa2m_afirmar(
		hash_obtener(hash, clave) == NULL,
		"No puedo obtener un elemento de un hash si la clave no existe.");

	hash_destruir(hash);
}

void prueba_hash_obtener_de_un_hash_con_clave_existente()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	pa2m_afirmar(
		hash_obtener(hash, clave) == elemento,
		"Puedo obtener un elemento de un hash si la clave existe.");

	hash_destruir(hash);

	free(elemento);
}

void prueba_hash_obtener_clave_y_borrar()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	hash_obtener(hash, clave);

	hash_quitar(hash, clave);

	pa2m_afirmar(
		hash_obtener(hash, clave) == NULL,
		"No puedo obtener un elemento de un hash si la clave fue previamente quitada.");

	hash_destruir(hash);

	free(elemento);
}

void hash_prueba_cantidad_elementos_en_hash_nulo()
{
	hash_t *hash = NULL;

	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Un hash nulo no puede tener elementos.");
}

void hash_prueba_cantidad_elementos_en_hash_valido()
{
	hash_t *hash = hash_crear(3);
	char *clave = "clave";
	int *elemento = malloc(sizeof(int));
	*elemento = 1;

	hash_insertar(hash, clave, elemento, NULL);

	pa2m_afirmar(
		hash_cantidad(hash) == 1,
		"La cantidad de elementos de un hash válido al que se le insertó un solo elemento es 1.");

	hash_destruir(hash);

	free(elemento);
}

bool funcion_iterador(const char *clave, void *elemento, void *extra)
{
	return true;
}

void hash_prueba_iterar_hash_nulo()
{
	hash_t *hash = NULL;
	int *elemento = malloc(sizeof(int));
	void *extra = NULL;

	pa2m_afirmar(hash_con_cada_clave(hash, funcion_iterador, extra) == 0,
		     "No puedo iterar un hash nulo.");

	free(elemento);
}

void hash_prueba_iterar_hash_valido_con_funcion_nula()
{
	hash_t *hash = hash_crear(3);
	int *elemento = malloc(sizeof(int));
	void *extra = NULL;

	pa2m_afirmar(hash_con_cada_clave(hash, NULL, extra) == 0,
		     "No puedo iterar un hash válido con una función nula.");

	hash_destruir(hash);

	free(elemento);
}

void prueba_hash_iterar_totalidad()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	char *clave2 = "clave2";
	char *clave3 = "clave3";
	void *extra = NULL;

	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));

	*elemento1 = 1;
	*elemento2 = 2;
	*elemento3 = 3;

	hash_insertar(hash, clave1, elemento1, NULL);
	hash_insertar(hash, clave2, elemento2, NULL);
	hash_insertar(hash, clave3, elemento3, NULL);

	pa2m_afirmar(
		hash_con_cada_clave(hash, funcion_iterador, extra) == 3,
		"Se puede iterar en su totalidad un hash valido y devuelve la cantidad de elementos iterados.");

	hash_destruir(hash);

	free(elemento1);
	free(elemento2);
	free(elemento3);
}

bool funcion_iterar_2(const char *clave, void *elemento, void *extra)
{
	return false;
}

void prueba_hash_iterar_corta_antes()
{
	hash_t *hash = hash_crear(3);
	char *clave1 = "clave1";
	char *clave2 = "clave2";
	char *clave3 = "clave3";
	void *extra = NULL;

	int *elemento1 = malloc(sizeof(int));
	int *elemento2 = malloc(sizeof(int));
	int *elemento3 = malloc(sizeof(int));

	*elemento1 = 1;
	*elemento2 = 0;
	*elemento3 = 3;

	hash_insertar(hash, clave1, elemento1, NULL);
	hash_insertar(hash, clave2, elemento2, NULL);
	hash_insertar(hash, clave3, elemento3, NULL);

	pa2m_afirmar(
		hash_con_cada_clave(hash, funcion_iterar_2, extra) == 1,
		"El iterador se detiene antes de visitar todos los elementos si la funcion auxiliar devuelve false.");

	hash_destruir(hash);

	free(elemento1);
	free(elemento2);
	free(elemento3);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== CREACION ========================");
	prueba_hash_crear();
	prueba_hash_crear_mayor_a_3();
	prueba_hash_crear_menor_a_3();

	pa2m_nuevo_grupo(
		"\n======================== INSERCION ========================");
	prueba_hash_insertar_en_hash_nulo();
	prueba_hash_insertar_clave_nula();
	prueba_hash_insertar_elemento_nulo();
	prueba_hash_insertar();
	prueba_hash_insertar_varios();
	prueba_hash_insertar_varios_causando_rehash();
	prueba_hash_actualizar_elemento();

	pa2m_nuevo_grupo(
		"\n======================== ELIMINACION ========================");
	prueba_hash_quitar_en_hash_nulo();
	prueba_hash_quitar_clave_nula();
	prueba_hash_quitar_clave_no_existente();
	prueba_hash_quitar_clave_existente();
	prueba_hash_quitar_clave_dos_veces();

	pa2m_nuevo_grupo(
		"\n======================== OBTENCION ========================");
	prueba_hash_obtener_de_un_hash_nulo();
	prueba_hash_obtener_de_un_hash_con_clave_nula();
	prueba_hash_obtener_de_un_hash_con_clave_no_existente();
	prueba_hash_obtener_de_un_hash_con_clave_existente();
	prueba_hash_obtener_clave_y_borrar();

	pa2m_nuevo_grupo(
		"\n======================== CONTENER ========================");
	hash_prueba_cantidad_elementos_en_hash_nulo();
	hash_prueba_cantidad_elementos_en_hash_valido();

	pa2m_nuevo_grupo(
		"\n======================== ITERADOR ========================");
	hash_prueba_iterar_hash_nulo();
	hash_prueba_iterar_hash_valido_con_funcion_nula();
	prueba_hash_iterar_totalidad();
	prueba_hash_iterar_corta_antes();

	return pa2m_mostrar_reporte();
}
