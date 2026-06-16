#include <stdio.h>
#include "TAD_automata.h"
int mensaje();

int main() {
	Automata* A = NULL;
	int op = 0;
	str cadena;
	
	do {
		op = mensaje();
		switch(op) {
		case 1:
			A = Cargar_hard();
			printf("\nAutomata cargado exitosamente!\n");
			break;
			
		case 2:
			if (A != NULL) mostrarAutomata(A);
			else printf("\nPrimero se debe cargar el automata.\n");
			break;
			
		case 3:
			if (A != NULL) {
				printf("\nIngrese cadena w: ");
				cadena = load(); 
				
				StateNode* inicial = buscarEstado(A, A->q0);
				int aceptada = verificarCadena(A, inicial, cadena);
				
				if (aceptada == 1) printf("\nLa cadena ingresada SI ES ACEPTADA\n");
				else printf("\nLa cadena ingresada NO ES ACEPTADA\n");
				
				freeString(cadena); 
			} else {
				printf("\nPrimero se debe cargar el automata.\n");
			}
			break;
			
		case 4:
			if (A != NULL) {
				printf("\nConvirtiendo AFND a AFD...\n");
				AutomataPtr miAFD = convertirAFNDaAFD(A);
				
				printf("\n--- AUTOMATA DETERMINISTA RESULTANTE ---\n");
				mostrarAutomata(miAFD);
			} else {
				printf("\nPrimero se debe cargar el automata original.\n");
			}
			break;
			
		case 5:
			printf("\nSaliendo...\n");
			break;
			
		default:
			printf("\nOpcion incorrecta\n");
			break;
		}
	} while (op != 5);
	
	return 0;
}

// Funciones
int mensaje() {
	int op;
	printf("\n--- MENU AUTOMATA FINITO ---\n");
	printf("1- Cargar Automata Hardcodeado (AFND de prueba)\n"); //nuestra cadena recibe que termine en 01
	printf("2- Mostrar Automata\n");
	printf("3- Verificar Cadena\n");
	printf("4- Convertir a AFD y mostrar\n");
	printf("5- Salir\n");
	printf("Ingrese opcion: ");
	scanf("%d", &op);
	return op;
}
