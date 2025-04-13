#include "TAD_data.h"

int main (){
	
	tData lista = createData(2);
	tData sublista = createData(3);
	tData sublista2 = createData(3);
	
	tData cadena1 = createData(1);
	tData cadena2 = createData(1);
	cadena1->cad= load2("Hola");
	cadena2->cad= load2("mundo");
	tData cadena3 = createData(1);
	tData cadena4 = createData(1);
	cadena3->cad= load2("causa");
	cadena4->cad= load2("pe");
	
	
	agregarData(&lista, cadena1);
	agregarData(&lista, cadena2);
	
	agregarData(&sublista, cadena3);
	agregarData(&sublista, cadena4);
	
	agregarData(&sublista2, cadena3);
	agregarData(&sublista2, cadena4);
	
	agregarData(&lista, sublista);
	
	
	printf("\n");
	printf("Contenido de lista 1:\n");
	mostrarData(lista);
	printf("\n\n");
	printf("Contenido de lista 2:\n");
	mostrarData(sublista2);
	printf("\n");
	int c;
	c= pertenece(lista, sublista2);
	printf("\n");
	if (c==0)
		printf("Si pertenece");
	else 
		printf("No pertenece");
	return 0;
}
