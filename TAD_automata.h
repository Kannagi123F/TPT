#ifndef TAD_AUTOMATA_H
#define TAD_AUTOMATA_H

#include <stdio.h>
#include <stdlib.h>
#include "TAD_Data.h" 

typedef char Symbol;
typedef str State;   

//Estructura numero 2
typedef struct transition {
	Symbol symbol;
	tData to;               
	struct transition* next;
} Transition;

typedef struct stateNode {
	State name;
	Transition* transitions; 
	int isFinal;             
	struct stateNode* next;  
} StateNode;

typedef struct {
	StateNode* states;   //lista de los estados   
	State q0;                
	int deterministic;   // 1 si es AFD, 0 si es AFND
} Automata;

typedef struct nodoProcesadoAFD{
	tData conjuntoNFA; // Set de estados [q0, q1]
	str nombreDFA; // Nombre concatenado (q0q1), p0,p1 etc
	struct nodoProcesadoAFD* next;
} NodoProcesadoAFD;

// eliminar el uso de doble puntero (**)
typedef struct {
	NodoProcesadoAFD* cabecera;
} HistorialProcesados;

typedef Automata* AutomataPtr;
typedef StateNode* StateNodePtr;
typedef Transition* TransitionPtr;


//funciones
AutomataPtr Cargar_hard();
AutomataPtr crearAutomata(int esDet, State estadoInicial);
StateNodePtr buscarEstado(AutomataPtr af, State nombre);
void agregarEstado(AutomataPtr af, State nombre, int isFinal);
void agregarTransicion(AutomataPtr af, State origen, Symbol c, State destino);
int verificarCadena(AutomataPtr af, StateNodePtr actual, str w);
void mostrarAutomata(AutomataPtr af);

//Para probar y arreglar
AutomataPtr convertirAFNDaAFD(AutomataPtr afnd);

#endif
