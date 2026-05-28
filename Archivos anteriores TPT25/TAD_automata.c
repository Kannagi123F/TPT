#include "TAD_automata.h"
//Privadas
/*int Delta_ND(str Cad,tAF A){*/
/*	tData act=createSet();*/
/*	tData est_sig;*/
/*	agregarData(&act, copiarData(A.Inicial));*/
/*	while (Cad != NULL) {*/
/*		char c = Cad->dato;*/
/*		est_sig = transicion_ND(act, A.Delta, c);*/
/*		act = est_sig;*/
/*		Cad = Cad->sig;*/
/*	}*/
/*	tData aux = act;*/
/*	while (aux != NULL) {*/
/*		if (pertenece(A.ConjA, aux->dato) == 0) {*/
/*			return 1;*/
/*		}*/
/*		aux = aux->sig;*/
/*	}*/
/*	freeData(act);*/
/*	return 0 ;*/
/*}*/
int Delta_ND(str Cad, tAF A) {
	tData act = createSet();
	act->dato = copiarData (A.Inicial);  
	
	while (Cad != NULL) {
		tData nuevos = NULL;
		
		while (act != NULL) {
			
			tData trans = transicion(act->dato, A.Delta, Cad->dato);
			tData unionTmp = Union(nuevos, trans);
			freeData(nuevos);  
			nuevos = unionTmp;
			
			act = act->sig;
		}
		freeData(act);
		act = nuevos;  
		Cad = Cad->sig;
	}
	
	if (Interseccion(A.ConjA, act) != NULL) {
		freeData(act);
		return 1;
	}
	
	freeData(act);
	return 0;
}

int Delta_D(str Cad, tAF A){
	tData act;
	act = copiarData(A.Inicial);
	
	while(Cad!=NULL ){
		act = transicion(act, A.Delta, Cad->dato);
		Cad=Cad->sig;
	}
    if(pertenece(A.ConjA, act) == 0)
		return 1;
	return 0;
}
	
int Esdet(tAF A){
	tData aux,nav;
	aux = A.Delta;
	nav = ((aux->dato)->sig)->sig;
	if((nav->dato->tipoNodo) == 1){
		return 1;
	}
	else{
		printf("\n ES NO DETERMINISTA");
		return 0;
	}
}

	
tAF Cargar_aut(){
	tAF B;
	B.Alfabeto = Carga_Upla();
	B.ConjE = Carga_Upla();
	B.ConjA = Carga_Upla();
	B.Inicial = Carga_Upla();
	B.Delta = Carga_Upla();
return B;	
}
void Mostrar_aut(tAF B){
	printf("A =( ");
	Mostrar_Upla(B.Alfabeto);
	printf("\n");
	Mostrar_Upla(B.ConjE);
	printf("\n");
	Mostrar_Upla(B.ConjA);
	printf("\n");
	Mostrar_Upla(B.Inicial);
	printf("\n");
	Mostrar_Upla(B.Delta);
	printf("\n)");
}
	
	
void Verifica_cad(tAF B){
	str cad;
	
	printf("\nIngrese cadena:");
	cad = load();
	if((Esdet(B))==1){
	    if(Delta_D(cad,B))
			printf("\n La cadena ingresada es aceptada");
		else
			printf("\n La cadena ingresada no es aceptada");
	}
	else{
		if(Delta_ND(cad,B)==1)
			printf("\n La cadena ingresada es aceptada");
	    else
		   printf("\n La cadena ingresada no es aceptada");
	}
	

}
tAF Cargar_hard(){
	tAF nue;
	tData arbol, aux;
	int c;
	printf("Seleccione estados DT O NDT(0 o 1):");
	scanf("%d",&c);
	if(c==0){
		arbol=crearDesdeCadena("{{q0,q1},{q1},{0,1},q0,[[q0,0,q1],[q0,1,q0],[q1,0,q0],[q1,1,q1]]}");
	}
	else{
		arbol=crearDesdeCadena("{{q0,q1},{q1},{0,1},q0,[[q0,0,{q1}],[q0,1,{q0}],[q1,0,{q0}],[q1,1,{q1}]]}");
	}
	nue.ConjE= arbol->dato;
	aux = arbol;
	arbol = arbol->sig;
	free(aux);
	
	nue.ConjA=arbol->dato;
	aux= arbol;
	arbol=arbol->sig;
	free(aux);
	
	nue.Alfabeto=arbol->dato;
	aux= arbol;
	arbol=arbol->sig;
	free(aux);
	
	nue.Inicial=arbol->dato;
	aux= arbol;
	arbol=arbol->sig;
	free(aux);
	
	nue.Delta=arbol->dato;
	free(arbol);
	
return nue;
}

tAF CargarPorConsola(){
	tAF nuevo;
	int b;
	
	printf("Estados:");
	nuevo.ConjE= cargarEstados();
	printf("\nAlfabeto:");
	nuevo.Alfabeto=cargarAlfabeto();
	printf("\nEstado inicial:");
	nuevo.Inicial=cargarInicial(nuevo.ConjE);
	printf("\nEstados finales:");
	nuevo.ConjA=cargarFinal(nuevo.ConjE);
	printf("\nTransiciones:");
	printf("Desea cargar 1- AFD 2-AFND :");scanf("%d",&b);
	nuevo.Delta=cargarTransicion(nuevo.Alfabeto,nuevo.ConjE,b);
	return nuevo;
}
	
tData obtener_elemento(tData lista, int pos) {
	for (int i = 0; i < pos && lista != NULL; i++) {
		lista = lista->sig;
	}
	return (lista != NULL) ? lista->dato : NULL;
}


tAF cargar_automata_desde_csv() {
	tAF automata;
	
	automata.ConjE = createSet();
	automata.Alfabeto = createSet();
	automata.ConjA = createSet();  
	automata.Inicial = NULL;
	automata.Delta = createList();
	
	FILE *file = fopen("Datos.csv", "r");
	
	char linea[TAM];
	int fila = 0;
	
	while (fgets(linea, sizeof(linea), file)) {
	linea[strcspn(linea, "\n")] = 0;
/*	La función strcspn() busca la primera aparición de un carácter en este caso el salto de linea */
	char *token = strtok(linea, ";");
	int col = 0;
	
	if (fila == 0) {
		while (token) {
		if (col > 0) {  // Ignorar "Q/E"
		tData simbolo = createStr();
		simbolo->cad = load2(token);
		agregarData(&automata.Alfabeto, simbolo);
		}
		token = strtok(NULL, ";");
		col++;
		}
	} 

	else {
		char estado[TAM];
		int es_final = 0;
		
		if (token[0] == '*') {
		es_final = 1;
		strcpy(estado, token + 1); //Aca es para leer el estado final si tiene * solo copia lo de adelante
		} else {
		strcpy(estado, token);
		}

		tData nodo_estado = createStr();
		nodo_estado->cad = load2(estado);
		agregarData(&automata.ConjE, nodo_estado);
	
		if (es_final) {
		tData final = createStr();
		final->cad = copyStr(nodo_estado->cad); 
		agregarData(&automata.ConjA, final);
		}
		
		token = strtok(NULL, ";");
		col = 0;
			while (token) {
			tData transicion = createList();
			agregarData(&transicion, copiarData(nodo_estado));
	
			tData simbolo = createStr();
			tData simbolo_alfabeto = obtener_elemento(automata.Alfabeto, col);
			if (simbolo_alfabeto && simbolo_alfabeto->tipoNodo == STR) {
				simbolo->cad = copyStr(simbolo_alfabeto->cad);
				}
			agregarData(&transicion, simbolo);
		
			tData destino = createStr();
			destino->cad = load2((token[0] == '*') ? token + 1 : token);
			agregarData(&transicion, destino);
		
			agregarData(&automata.Delta, transicion);
		
			token = strtok(NULL, ";");
			col++;
			}
		}
	fila++;
	}
	
	if (automata.ConjE != NULL) {
		automata.Inicial = copiarData(automata.ConjE->dato);
	}
	fclose(file);
	
return automata;
}

void limpiar(){
	printf("\n");system("pause");system("cls");;
}

void MostrarUpla(tAF B){
	int op;
	do{
	
	printf("\nIngrese que Upla desea ver:\n");
	printf("1-Alfabeto\n");
	printf("2-Estados\n");
	printf("3-Estados finales\n");
	printf("4-Estado inicial\n");
	printf("5-Transiciones\n");
	printf("6-Salir\n");
	printf("Ingrese opcion:");
	scanf("%d",&op);
	
	switch(op){
	case 1:Mostrar_Upla(B.Alfabeto);limpiar();break;
	case 2:Mostrar_Upla(B.ConjE);limpiar();break;
	case 3:Mostrar_Upla(B.ConjA);limpiar();break;
	case 4:Mostrar_Upla(B.Inicial);limpiar();break;
	case 5:Mostrar_Upla(B.Delta);limpiar();break;
	case 6:printf("Volviendo al menu...\n");break;
	default:printf("Error de ingreso");limpiar();break;
	}
	}while(op!=6);
}

void seleccion(tAF A){
	int selec=0;
	while(selec!=4){
		printf("\nMostrar:\n1-Una Upla\n2-Automata completo\n3-Verificar automata\n4-Salir\n");
		printf("Ingrese opcion:");
		scanf("%d",&selec);
		if (selec==2)
		{limpiar();
		Mostrar_aut(A);}
		else if(selec==1){limpiar();
			MostrarUpla(A);printf("\n");}
		else if (selec==3) {Verifica_cad(A);printf("\n");}
		else if(selec==4) printf("Saliendo...");
		else {printf("Error de ingreso\n");
		system("CLS");}
	}
}

tAF Carga_desde_excel() {
	tAF Aut;
	
	Aut.Alfabeto = cargarAlfabeto2();
	Aut.ConjE = cargarEstado2();
	Aut.Inicial = cargarInicial2();
	Aut.ConjA=cargarFinal2();
	Aut.Delta=cargarTransicion2(Aut.Alfabeto,Aut.ConjE);
	return Aut;
}
	
