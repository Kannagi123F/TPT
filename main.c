#include "TAD_DATA.H"
#include "TAD_data.h"

void ejecutarPruebasTPT();
void menuInteractivo();
void cargarConjuntoPorConsola(tData *conjunto);
void cargarListaPorConsola(tData *lista);

int main() {
	int op;
	printf("=== TPT Version 1.3 ===\n");
	printf("1) Ejecutar Casos de Prueba\n");
	printf("2) Menu Interactivo Libre\n");
	printf("0) Salir\n");
	printf("Opcion: ");
	scanf("%d", &op);
	
	if(op == 1) {
		ejecutarPruebasTPT();
	} else if (op == 2) {
		menuInteractivo();
	}
	
	return 0;
}


//CASOS DE PRUEBA

void ejecutarPruebasTPT() {
	printf("\n--- INICIANDO ---\n");

	printf("\n1) OPERACIONES SOBRE STR\n");
	tData s1 = create_str_ast(); s1->string = load2("Hola");
	tData s2 = create_str_ast(); s2->string = load2("Mundo");
	tData sConcatenada = concat_str(s1, s2);
	
	printf("STR 1: "); mostrarData(s1); printf("\n");
	printf("STR 2: "); mostrarData(s2); printf("\n");
	printf("Concatenacion (s1 + s2): "); mostrarData(sConcatenada); printf("\n");
	
	printf("\n2) CONJUNTOS (SET): VACIO Y DUPLICADOS\n");
	tData setA = create_set(); 
	insert_set(&setA, s1);
	insert_set(&setA, s1); 
	insert_set(&setA, s2);
	
	printf("Set A (Solo deberia tener 'Hola' y 'Mundo'): "); mostrarData(setA); printf("\n");
	printf("Cardinalidad (length) de Set A: %d\n", length(setA));
	
	printf("\n3) OPERACIONES ALGEBRAICAS\n");
	tData s3 = create_str_ast(); s3->string = load2("TCI");
	tData setB = create_set();
	insert_set(&setB, s2);
	insert_set(&setB, s3);
	
	printf("Conjunto A: "); mostrarData(setA); printf("\n");
	printf("Conjunto B: "); mostrarData(setB); printf("\n");
	
	tData u = union_set(setA, setB);
	printf("Union (A U B): "); mostrarData(u); printf("\n");
	
	tData i = intersection_set(setA, setB);
	printf("Interseccion (A n B): "); mostrarData(i); printf("\n");
	
	tData d = difference_set(setA, setB);
	printf("Diferencia (A - B): "); mostrarData(d); printf("\n");
	
	printf("\n4) PRODUCTO CARTESIANO (A x B)\n");
	tData prod = producto_cartesiano(setA, setB);
	printf("Resultado: "); mostrarData(prod); printf("\n");
	
	printf("\n5) CONVERSIONES Y LISTAS ANIDADAS\n");
	tData cadena = create_str_ast(); cadena->string = load2("ABC");
	tData listaChar = str_to_list(cadena);
	printf("STR 'ABC' convertido a LIST: "); mostrarData(listaChar); printf("\n");
	
	tData listaAnidada = create_list();
	append(&listaAnidada, s1);
	append(&listaAnidada, listaChar); 
	printf("Lista Anidada: "); mostrarData(listaAnidada); printf("\n");
	
	printf("\n6) COPIA PROFUNDA (Deep Copy)\n");
	tData copiaA = copy_list(setA);
	remove_set(&copiaA, s1);
	printf("Original (mantiene 'Hola'): "); mostrarData(setA); printf("\n");
	printf("Copia (sin 'Hola'): "); mostrarData(copiaA); printf("\n");
	
	freeData(s1); freeData(s2); freeData(s3); freeData(sConcatenada);
	freeData(setA); freeData(setB); freeData(u); freeData(i); freeData(d);
	freeData(prod); freeData(cadena); freeData(listaChar); 
	freeData(listaAnidada); freeData(copiaA);
	
	printf("\n--- PRUEBAS FINALIZADAS CON EXITO ---\n\n");
}


void menuInteractivo() {
	int opcion;
	tData A = create_set();
	tData B = create_set();
	tData L1 = create_list();
	
	do {
		printf("\n=== MENU INTERACTIVO ===");
		printf("\n1) Agregar a Conjunto A (insert_set)");
		printf("\n2) Agregar a Conjunto B (insert_set)");
		printf("\n3) Mostrar Conjuntos A y B");
		printf("\n4) Union A y B");
		printf("\n5) Interseccion A y B");
		printf("\n6) Eliminar de A (remove_set)");
		printf("\n7) Agregar a Lista (append)");
		printf("\n8) Mostrar Lista");
		printf("\n9) Longitud de Lista (length)");
		printf("\n10) Concatenar dos STR (concat_str)");
		printf("\n0) Volver al inicio");
		printf("\nSeleccione: ");
		scanf("%d", &opcion);
		
		switch(opcion) {
		case 1: cargarConjuntoPorConsola(&A); break;
		case 2: cargarConjuntoPorConsola(&B); break;
		case 3:
			printf("\nA: "); mostrarData(A);
			printf("\nB: "); mostrarData(B); printf("\n");
			break;
		case 4: {
			tData res = union_set(A, B);
			printf("\nResultado Union: "); mostrarData(res); printf("\n");
			freeData(res); break;
		}
		case 5: {
			tData res = intersection_set(A, B);
			printf("\nResultado Interseccion: "); mostrarData(res); printf("\n");
			freeData(res); break;
		}
		case 6: {
			tData temp = create_str_ast();
			printf("Texto a eliminar de A: "); temp->string = load();
			remove_set(&A, temp);
			freeData(temp); break;
		}
		case 7: cargarListaPorConsola(&L1); break;
		case 8: printf("\nLista: "); mostrarData(L1); printf("\n"); break;
		case 9: printf("\nLongitud: %d\n", length(L1)); break;
		case 10: {
			tData c1 = create_str_ast(); printf("Cadena 1: "); c1->string = load();
			tData c2 = create_str_ast(); printf("Cadena 2: "); c2->string = load();
			tData res = concat_str(c1, c2);
			printf("Resultado: "); mostrarData(res); printf("\n");
			freeData(c1); freeData(c2); freeData(res); break;
		}
		}
	} while(opcion != 0);
	
	freeData(A); freeData(B); freeData(L1);
}

void cargarConjuntoPorConsola(tData *conjunto) {
	tData temp = create_str_ast();
	printf("Ingrese texto: ");
	temp->string = load();
	insert_set(conjunto, temp);
	freeData(temp);
	printf("Elemento procesado.\n");
}

void cargarListaPorConsola(tData *lista) {
	tData temp = create_str_ast();
	printf("Ingrese texto para la lista: ");
	temp->string = load();
	append(lista, temp);
	freeData(temp);
	printf("Elemento agregado.\n");
}
