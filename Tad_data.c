#include "TAD_data.h"

tData createData(int tipo){
	tData nvo;
	nvo = (tData) malloc (sizeof(TNodoData));
	
	if(tipo == STR){
		nvo->cad = create();
		nvo->tipoNodo = STR;
	}
	else {
		nvo->dato = NULL;
		nvo->sig = NULL;
		nvo->tipoNodo = tipo;
	}
	return nvo;
}
tData createList(){
	return createData(LIST);
}
tData createSet(){
	return createData(SET);
}	
tData createStr(){
	return createData(STR);
}

void mostrarData(tData nodo){
	
	if(nodo == NULL) return;
	
	
	switch(nodo->tipoNodo){
	case STR: 
		print(nodo->cad);
		break;
	case LIST:
		printf("[");
		
		tData aux;
		aux= nodo;
		while(aux != NULL){
			mostrarData(aux->dato);
			if(aux->sig != NULL)
				printf(",");
			aux = aux->sig;
		}
		printf("]");
		
		break;
	case SET:
		printf("{");
		
		tData aux2;
		aux2= nodo;
		while(aux2 != NULL){
			mostrarData(aux2->dato);
			if(aux2->sig != NULL)
				printf(",");
			aux2 = aux2->sig;
		}
		printf("}");
		break;
		
	}
}

void agregarData(tData* cab, tData elem){
	
	if((*cab) == NULL || (*cab)->dato == NULL){
		tData nvo;
		
		if(elem->tipoNodo == STR){
			if((*cab) != NULL)
				nvo = createData((*cab)->tipoNodo);
			else
				nvo = createList();
			nvo->dato = copiarData(elem);
			*cab = nvo;
		}
		else{
			tData nvo = createData((*cab != NULL) ? (*cab)->tipoNodo : LIST);  // o SET seg�n contexto
			nvo->dato = copiarData(elem);
			*cab = nvo;
		}
	}
	else{
		switch ((*cab)->tipoNodo){
		case STR: 
			return;
			break;
		case SET:
		case LIST: {
			tData aux = *cab;
			tData nvo;
			
			if (aux->tipoNodo == SET) {
				if(pertenece(aux, elem) == 0) 
					return;
			}
			while (aux->sig != NULL)
				aux = aux->sig;
			
			nvo = createData(aux->tipoNodo);
			nvo->dato = copiarData(elem);
			aux->sig = nvo;
			break;
			}
		}
	}
}	
	
//funciones nucleo	
tData copiarData (tData copiado){
	tData nvo = NULL;
	if (copiado == NULL) return nvo;
	
	switch (copiado->tipoNodo){
	case STR:
		nvo = createStr(); 
		nvo->cad = copyStr(copiado->cad);
		break;
	case LIST:
		nvo = createList();
		nvo->dato = copiarData( copiado->dato);
		nvo->sig = copiarData (copiado ->sig);
		break;
	case SET:
		nvo = createSet();
		nvo->dato = copiarData( copiado->dato);
		nvo->sig = copiarData (copiado ->sig);
		break;
	}
	
	return nvo;
}	
	
void freeData(tData descartado){
	
	if (descartado == NULL) return;
	
	switch (descartado->tipoNodo){
	case STR:
		freeString(descartado->cad);
		break;
	case LIST:
	case SET:
		freeData(descartado->dato);
		freeData(descartado->sig);
		break;
	}
	
	free(descartado);
}
	
int Igualdad(tData A, tData B){
		
	if(A==NULL && B==NULL) return 0;
	if(A==NULL || B==NULL || (A->tipoNodo!=B->tipoNodo)) return 1;
	
	
	switch(A->tipoNodo){
	case STR: 
		return compStr(A->cad,B->cad);
		break;
	case SET:{
		tData auxA = A;
		while(auxA != NULL){
			if(pertenece(B, auxA->dato) != 0) return 1;
				auxA = auxA->sig;
		}
		tData auxB = B;
		while(auxB != NULL){
			if(pertenece(A, auxB->dato) != 0) return 1;
				auxB = auxB->sig;
		}
		return 0;
		}
		
	case LIST:{
		tData auxA = A;
		tData auxB = B;

		while(auxA != NULL && auxB != NULL){
			if(Igualdad(auxA->dato, auxB->dato) != 0) return 1;
				auxA = auxA->sig;
				auxB = auxB->sig;
			}
			if(auxA != NULL || auxB != NULL)
				return 1;

			return 0;
			}	
	default: return 1;
	}
}	

tData Cargar (){
	tData nvo = NULL;
	
	nvo = crear_arbol(0, 0);
	
	return nvo;
}	

void mostrartipo(int tipo){
	switch(tipo){
	case 1: printf("string"); break;
	case 2: printf("list"); break;
	case 3: printf("set"); break;
	default: printf("Sin tipo");
	}
}
	
int retorna_tipo(){
	int op;
	do{printf("\nQue desea agregar");
	printf("\nPresione 1 cadena");
	printf("\nPresione 2 lista");
	printf("\nPresione 3 conjunto");
	printf("\nIngrese su opcion: ");
	scanf("%d",&op);}while (op!= 1 && op != 2 && op != 3);
	return op;
}	
int continuar(int nivel){
	int op;
	
	do{
	printf("\nDesea seguir cargando en nivel %d", nivel);
	printf("\nPresione 1 Si");
	printf("\nPresione 0 No");
	printf("\nIngrese su opcion: ");
	scanf("%d",&op);}while (op != 1 && op != 0);
	return op;
}
	
tData crear_arbol(int nivel, int tipo){
	int op;
	tData nva=NULL;
	
	printf("\n Se encuentra en el nivel : %d", nivel);
	printf("\n El tipo de dato en este nivel es : "); mostrartipo(tipo);
	op=retorna_tipo();
	
	
	if(op!=STR){
		nva = createData(op);
		
		do {
			tData hijo = crear_arbol(nivel + 1, op);
			
		
			agregarData(&nva, hijo);
		} while (continuar(nivel+1) == 1);
	}
	else{
		nva=createStr();
		
		printf("Ingrese la cadena: ");
		nva->cad=load();
		return nva;
	}
	return nva;
}		
	
//conjuntos
	
tData Union (tData A, tData B){
	if (A == NULL)
		return copiarData(B);
	if(B == NULL)
		return copiarData(A);	
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	
	while(A != NULL){
		
		aux= createSet();
		aux->dato = copiarData(A->dato);
		
		if(C_Cab == NULL) C_Cab = aux;
		else C_act->sig = aux;
		
		C_act= aux;
		
		A = A->sig;
	}
	while(B != NULL){
		
		if(pertenece(C_Cab, B->dato)){
			
			aux= createSet();
			aux->dato = copiarData(B->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		B = B->sig;
	}
	
	return C_Cab;
}

tData Interseccion (tData A, tData B){
	if (A == NULL || B == NULL)
		return NULL;
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL){
		
		if(! pertenece(B, A->dato)){
			
			aux= createSet();
			aux->dato = copiarData(A->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		A = A->sig;
	}
	return C_Cab;
}

tData Diferencia (tData A, tData B){
	if (A == NULL)
		return NULL;
	if (B == NULL)
		return copiarData(A);
	
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL){
		
		if( pertenece(B, A->dato)){
			
			aux= createSet();
			aux->dato = copiarData(A->dato);
			
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			
			C_act= aux;
			
		}
		A = A->sig;
	}
	return C_Cab;
}

tData DifSimetrica (tData A, tData B){
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	
	tData D = Diferencia(A, B);
	tData E = Diferencia(B, A);
	
	tData F = NULL;
	F = Union (D, E);
	
	
	return F;
}

int pertenece(tData A, tData elem){
	if (A == NULL || elem == NULL) return 1;
	if (A->tipoNodo != LIST && A->tipoNodo != SET) return 1;
		
	tData aux = A;
		
	while (aux != NULL) {
		if (Igualdad(aux->dato, elem) == 0)
			return 0;
		aux = aux->sig;
	}
	
	return 1;
}

int contenido(tData A, tData B){
	
	tData auxA = A;
	while(auxA != NULL){
		if(pertenece(B, auxA->dato) != 0) return 0;
		auxA = auxA->sig;
	}
	return 1;
}

int cardinalidad (tData A){
	
	if (A == NULL || A->tipoNodo != SET)
		return 0;
	
	int c= 0;
	
	while(A!= NULL){
		c++;
		A = A->sig;
	}
	
	return c;
}

	
tData toSetWToken(tData cad, char token){
	
	if(cad == NULL || cad->tipoNodo != STR)
		return NULL;
	
	
	tData A_Cab = NULL;
	tData A_act = NULL;
	tData Aux;
	tData restante = NULL;
	tData nvoStr;
	
	restante = copiarData(cad);
	
	while (restante->cad != NULL && restante->cad != '\0') {
		tData parte= createStr();
		parte->cad = before_token(restante->cad, token);  
		tData siguiente= createStr();
		siguiente->cad = after_token(restante->cad, token); 
		
		nvoStr = createStr();
		nvoStr->cad = parte->cad;  
		
		if (pertenece(A_Cab, nvoStr) != 0) {
			Aux = createSet();
			Aux->dato = nvoStr;
			
			if (A_Cab == NULL) A_Cab = Aux;
			else A_act->sig = Aux;
			
			A_act = Aux;
		} else {
			freeData(nvoStr); 
		}
		
		free(restante->cad);          
		restante->cad = siguiente->cad;    
	}
	
	freeData(restante); 

	return A_Cab;
}	

tData procesar_cadena_simple(str *restante) {
	str parte = before_token(*restante, ',');
	parte = before_token(parte, ']');
	parte = before_token(parte, '}');
	
	tData nodo = createStr();
	if (nodo != NULL) {
	nodo->cad = copyStr(parte);
	}
	while (*restante != NULL && (*restante)->dato != ',' && (*restante)->dato != ']' && (*restante)->dato != '}') {
	*restante = (*restante)->sig;
	}
	freeString(parte);
	
	return nodo;
}
	
tData buscarCadena(str *restante) {
	if (*restante == NULL) return NULL;
	
	tData nodo = NULL;
	char primer_car = (*restante)->dato;
	char delimitador = (primer_car == '[') ? ']' : '}'; 
	
	if (primer_car == '[') {
	nodo = createList();
	} else if (primer_car == '{') {
	nodo = createSet();
	} else {return procesar_cadena_simple(restante);
	}
	
	*restante = (*restante)->sig; 
	
	while (*restante != NULL && (*restante)->dato != delimitador) {
	tData elem = buscarCadena(restante);
	if (elem != NULL) {
	agregarData(&nodo, elem);
	}
	if (*restante != NULL && (*restante)->dato == ',') {
		*restante = (*restante)->sig;
	}}
	
	if (*restante != NULL) {
	*restante = (*restante)->sig;
	}
	
return nodo;
}
	
tData crearDesdeCadena(const char *input) {
	str S = load2(input);
	str restante = S;
	tData resultado = buscarCadena(&restante);
	freeString(S);
	return resultado;
}
