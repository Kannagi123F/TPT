#include "TAD_automata.h"
//nuestra cadena recibe que termine en 01
AutomataPtr Cargar_hard() {
	str s_q0, s_q1, s_q2;
	AutomataPtr af;
	
	s_q0 = load2("q0");
	s_q1 = load2("q1");
	s_q2 = load2("q2");
	
	af = crearAutomata(0, s_q0);
	
	agregarEstado(af, s_q0, 0);
	agregarEstado(af, s_q1, 0);
	agregarEstado(af, s_q2, 1);
	
	agregarTransicion(af, s_q0, '0', s_q0);
	agregarTransicion(af, s_q0, '0', s_q1);
	agregarTransicion(af, s_q0, '1', s_q0);
	agregarTransicion(af, s_q1, '1', s_q2);
	
	freeString(s_q0);
	freeString(s_q1);
	freeString(s_q2);
	
	return af;
}

AutomataPtr crearAutomata(int esDet, State estadoInicial) {
	AutomataPtr af;
	
	af = (AutomataPtr)malloc(sizeof(Automata));
	af->states = NULL;
	af->deterministic = esDet;
	af->q0 = copyStr(estadoInicial); 
	
	return af;
}

StateNodePtr buscarEstado(AutomataPtr af, State nombre) {
	StateNodePtr aux;
	
	aux = af->states;
	while (aux != NULL) {
		if (compStr(aux->name, nombre) == 0) { 
			return aux; 
		}
		aux = aux->next;
	}
	return NULL; 
}

void agregarEstado(AutomataPtr af, State nombre, int isFinal) {
	StateNodePtr existe;
	StateNodePtr nvo;
	
	existe = buscarEstado(af, nombre);
	if (existe != NULL) {
		existe->isFinal = isFinal;
		return;
	}
	
	nvo = (StateNodePtr)malloc(sizeof(StateNode));
	nvo->name = copyStr(nombre); 
	nvo->isFinal = isFinal;
	nvo->transitions = NULL;
	
	//Inserto al inicio de estados
	nvo->next = af->states;
	af->states = nvo;
}

void agregarTransicion(AutomataPtr af, State origen, Symbol c, State destino) {
	StateNodePtr nodoOrigen;
	TransitionPtr t;
	tData nvoDestino;
	TransitionPtr nvaTrans;
	
	nodoOrigen = buscarEstado(af, origen);
	if (nodoOrigen == NULL) return;
	
	t = nodoOrigen->transitions;
	nvoDestino = create_str_ast();
	nvoDestino->string = copyStr(destino);
	
	while (t != NULL) {
		if (t->symbol == c) {
			insert_set(&(t->to), nvoDestino);
			af->deterministic = 0; //le sacamos determinista si ya tiene mas de un destino
			freeData(nvoDestino);
			return;
		}
		t = t->next;
	}
	
	//no existe, le agrego una transicion
	nvaTrans = (TransitionPtr)malloc(sizeof(Transition));
	nvaTrans->symbol = c;
	nvaTrans->to = create_set();
	insert_set(&(nvaTrans->to), nvoDestino);
	
	nvaTrans->next = nodoOrigen->transitions;
	nodoOrigen->transitions = nvaTrans;
	
	freeData(nvoDestino);
}

int verificarCadena(AutomataPtr af, StateNodePtr actual, str w) {
	Symbol c;
	TransitionPtr t;
	tData dest;
	StateNodePtr nodoSig;
	
	//Caso base: si la cadena termino verificamos si el estado es final
	if (w == NULL) {
		return actual->isFinal;
	}
	
	c = w->dato;
	t = actual->transitions;
	
	//recursivo para buscar caminos hasta que encontremos al menos 1 y volvamos hacia atras
	while (t != NULL) {
		if (t->symbol == c) {
			dest = t->to; 
			
			while (dest != NULL && dest->data != NULL) {
				if (dest->data->nodeType == STR) {
					nodoSig = buscarEstado(af, dest->data->string);
					if (nodoSig != NULL && verificarCadena(af, nodoSig, w->sig) == 1) {
						return 1; //Exito entonces retorna 1
					}
				}
				dest = dest->sig;
			}
		}
		t = t->next;
	}
	
	return 0; 
}

void mostrarAutomata(AutomataPtr af) {
	StateNodePtr aux;
	TransitionPtr t;
	
	printf("\nEstado Inicial: ");
	print(af->q0);
	printf("\n");
	
	aux = af->states;
	while (aux != NULL) {
		printf("Estado [");
		print(aux->name);
		printf("]");
		if (aux->isFinal) printf(" (FINAL)");
		printf(":\n");
		
		t = aux->transitions;
		while (t != NULL) {
			printf("  --(%c)--> ", t->symbol);
			mostrarData(t->to); 
			printf("\n");
			t = t->next;
		}
		aux = aux->next;
	}
}

//Funciones auxiliares para AFND A AFD

int esConjuntoFinal(AutomataPtr afnd, tData set) {
	tData aux;
	StateNodePtr sn;
	
	aux = set;
	while (aux != NULL && aux->data != NULL) {
		if (aux->data->nodeType == STR) {
			sn = buscarEstado(afnd, aux->data->string); // Si tan solo UNO de los estados originales es final el nuevo estado es final
			if (sn != NULL && sn->isFinal) return 1;
		}
		aux = aux->sig;
	}
	return 0;
}

str generarNombreSecuencial(int id) {
	char numero[20];
	sprintf(numero, "p%d", id);
	return load2(numero);       
}

tData estadosAlcanzables(AutomataPtr afnd, tData stateSet, Symbol c) {
	tData result;
	tData aux;
	StateNodePtr sn;
	TransitionPtr t;
	tData dest;
	
	result = create_set(); 
	aux = stateSet;
	
	// Recorremos por cada estado del set actual
	while (aux != NULL && aux->data != NULL) {
		if (aux->data->nodeType == STR) {
			sn = buscarEstado(afnd, aux->data->string);
			if (sn != NULL) {
				t = sn->transitions;
				while (t != NULL) { // busco a donde va el simbolo
					if (t->symbol == c) {
						dest = t->to;
						// agrego los destinos en un conjunto final 
						while (dest != NULL && dest->data != NULL) {
							insert_set(&result, dest->data); 
							dest = dest->sig;
						}
					}
					t = t->next;
				}
			}
		}
		aux = aux->sig;
	}
	
	// si no encontro nada, el estado residual R, devolvemos NULL
	if (result->data == NULL) {
		freeData(result);
		return NULL;
	}
	return result;
}

void agregarProcesado(HistorialProcesados* historial, tData conjunto, str nombre) {
	NodoProcesadoAFD* nvo;
	
	nvo = (NodoProcesadoAFD*)malloc(sizeof(NodoProcesadoAFD));
	nvo->conjuntoNFA = copy_list(conjunto); // Clonamos para evitar problemas con punteros
	nvo->nombreDFA = copyStr(nombre);
	
	// Insertamos al inicio usando la cabecera
	nvo->next = historial->cabecera;
	historial->cabecera = nvo;
}

str buscarProcesado(HistorialProcesados* historial, tData conjunto) {
	NodoProcesadoAFD* aux;
	
	aux = historial->cabecera;
	while (aux != NULL) {
		if (equals_set(aux->conjuntoNFA, conjunto) == 0) {
			return aux->nombreDFA; // Retorna el nombre si el conjunto ya fue procesado
		}
		aux = aux->next;
	}
	return NULL;
}

// Contruimos el automata (RECURSIVO)

void dfsConstruccion(AutomataPtr afd, AutomataPtr afnd, tData actualNFA, str nombreActual,HistorialProcesados* historial, char* alfabeto, int cantAlf, int* contadorDFA) {
	int i, esFinal;
	Symbol c;
	tData alcanzables;
	str nombreDest;

	esFinal = esConjuntoFinal(afnd, actualNFA);// 1 Evaluamos si es final y lo agregamos al nuevo AFD
	agregarEstado(afd, nombreActual, esFinal);
	
	agregarProcesado(historial, actualNFA, nombreActual);// 2 Lo marcamos como procesado
	
	
	for (i = 0; i < cantAlf; i++) {// 3 Por cada simbolo del alfabeto buscamos hacia donde va
		c = alfabeto[i];
		alcanzables = estadosAlcanzables(afnd, actualNFA, c);
		
		if (alcanzables != NULL) {//Vemos si el subconjunto ya existe como un estado en el AFD
			nombreDest = buscarProcesado(historial, alcanzables);
			if (nombreDest == NULL) {//si es nuevo
				nombreDest = generarNombreSecuencial((*contadorDFA)++);
				dfsConstruccion(afd, afnd, alcanzables, nombreDest, historial, alfabeto, cantAlf, contadorDFA);
				agregarTransicion(afd, nombreActual, c, nombreDest);
				freeString(nombreDest);// Agregamos la transicion y liberamos el nombre usado localmente
			} else {
				agregarTransicion(afd, nombreActual, c, nombreDest);//si existe solo agrego la transicion
			}
			freeData(alcanzables);
		}
	}
}

AutomataPtr convertirAFNDaAFD(AutomataPtr afnd) {
	AutomataPtr afd;
	char alfabeto[50];
	int cantAlf, i, contadorDFA;
	StateNodePtr snAux;
	TransitionPtr tAux;
	HistorialProcesados historial;
	NodoProcesadoAFD* aLiberar;
	tData initSet, ConjuntoInicial;
	str nombreInit;
	
	cantAlf = 0;
	contadorDFA = 0;
	historial.cabecera = NULL;
	afd = NULL;
	
	if (afnd == NULL) return NULL;
	
	// 1 Paso el alfabeto recorriendo todas las transiciones
	snAux = afnd->states;
	while (snAux != NULL) {
		tAux = snAux->transitions;
		while (tAux != NULL) {
			i = 0;
			while (i < cantAlf && alfabeto[i] != tAux->symbol) {i++;}
			if (i == cantAlf) {alfabeto[cantAlf++] = tAux->symbol;}
			tAux = tAux->next;
		}
		snAux = snAux->next;
	}
	// 2 creo el conjunto q0 inicial
	initSet = create_set(); 
	ConjuntoInicial = create_str_ast();
	ConjuntoInicial->string = copyStr(afnd->q0);
	insert_set(&initSet, ConjuntoInicial);
	freeData(ConjuntoInicial);
	
	nombreInit = generarNombreSecuencial(contadorDFA++);//3 creo el AFD y genero nombres secuenciales para los conjuntos
	afd = crearAutomata(1, nombreInit);
	dfsConstruccion(afd, afnd, initSet, nombreInit, &historial, alfabeto, cantAlf, &contadorDFA);
	
	freeData(initSet); //4 limpio todo lo que queda para evitar desborde de memoria
	freeString(nombreInit);
	while(historial.cabecera != NULL) {
		aLiberar = historial.cabecera;
		historial.cabecera = historial.cabecera->next;
		freeData(aLiberar->conjuntoNFA);
		freeString(aLiberar->nombreDFA);
		free(aLiberar);
	}
	return afd;
}
