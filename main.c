#include "TAD_data.h"

void menuConjuntos(tData, tData);
void crearConjunto(tData*,int);
void cargarConjuntoPorConsola(tData *conjunto);

int main (){
	int op;
	tData lista = createList();
	printf("Lista inicializada.\n");
	
	lista->dato=Cargar();
	printf("\nLista cargada: ");
	mostrarData(lista);
	printf("\n");
	
	tData A = createSet();
	tData B = createSet();
	printf("\nConjunto vacio creado.\n");
	
	printf("1) Cargar por consola\n2) Usar precargado\nOpcion: ");
	scanf("%d", &op);
	if (op==1){

	printf("\nElementos para A:\n");
	cargarConjuntoPorConsola(&A);
	printf("\nElementos para B:\n");
	cargarConjuntoPorConsola(&B);
	
	}else{
	crearConjunto(&A,1);crearConjunto(&B,2);
	}
	
	printf("\nConjunto A: ");
	mostrarData(A);
	printf("\nConjunto B: ");
	mostrarData(B);
	printf("\n");
	
	menuConjuntos(A, B);
	
	freeData(A);
	freeData(B);
	freeData(lista);
}
	
	
void menuConjuntos(tData A, tData B) {
	int opcion;
	do {
	printf("\n=== MENU ===");
	printf("\n1) Union");
	printf("\n2) Interseccion");
	printf("\n3) Diferencia (A - B)");
	printf("\n4) Diferencia (B - A)");
	printf("\n5) Cardinalidad");
	printf("\n6) Pertenencia");
	printf("\n7) Inclusion A con B");
	printf("\n8) Inclusion B con A");
	printf("\n9) Mostrar conjuntos");
	printf("\n0) Salir");
	printf("\nIngrese opcion: ");
	scanf("%d", &opcion);
	
	switch(opcion) {
	case 1: {
		tData unionAB = Union(A, B);
		printf("\nUnion A y B: ");
		mostrarData(unionAB);
		freeData(unionAB);
		break;
	}
	case 2: {
		tData interseccionAB = Interseccion(A, B);
		printf("\nInterseccion A y B: ");
		mostrarData(interseccionAB);
		freeData(interseccionAB);
			break;
	}
	case 3: {
		tData dif = Diferencia(A, B);
		printf("\nDiferencia A - B: ");
		mostrarData(dif);
		freeData(dif);
		break;
	}
	case 4: {
		tData dif = Diferencia(B, A);
		printf("\nDiferencia B - A: ");
		mostrarData(dif);
		freeData(dif);
		break;
	}
	case 5: {
		printf("\nCardinalidad A: %d", cardinalidad(A));
		printf("\nCardinalidad B: %d", cardinalidad(B));
		break;
	}
	case 6: {
		tData elem = createStr();
		printf("\nElemento que pertenece: ");
		elem->cad = load();
		printf("Pertenece a A? %s", pertenece(A, elem) ? "No" : "Si");
		printf("\nPertenece a B? %s", pertenece(B, elem) ? "No" : "Si");
		freeData(elem);
		break;
	}
	case 7:
	if(contenido(A,B))
	printf("\n A esta contenido en B");
	else
	printf("A no esta contenido en B");
	break;
	case 8:
	if(contenido(B,A))
	printf("B esta contenido en A");
	else
	printf("B no esta contenido en A");
	break;
	case 9: {
		printf("\nConjunto A: ");
		mostrarData(A);
		printf("\nConjunto B: ");
		mostrarData(B);
		break;
	}
	}
	printf("\n");
} while(opcion != 0);
}

void crearConjunto(tData *A,int i){
	tData cadena1 = createData(1);
	tData cadena2 = createData(1);
	
	if(i==1){
		cadena1->cad= load2("Hola");
		cadena2->cad= load2("mundo");}
	else{
		cadena1->cad= load2("Hola");
		cadena2->cad= load2("TCI");}
	
	agregarData(&(*A), cadena1);
	agregarData(&(*A), cadena2);
}

	
void cargarConjuntoPorConsola(tData *conjunto) {
	int seguir = 1;
	
	while(seguir == 1) {
	tData elemento = createData(1);
	elemento->cad= load();
	agregarData(conjunto, elemento); 
	
	printf("Otro elemento? (1 = Si / 0 = No): ");
	scanf("%d", &seguir);
	if (seguir==1)
	printf("Ingrese elemento: ");
	}
}
