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
			nvo->dato = elem;
			*cab = nvo;
		}
		else
			*cab = elem;
		
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
			nvo->dato = elem;
			aux->sig = nvo;
			break;
		}
	}
	}
}
	
//conjuntos
	
tData Union (tData A, tData B){
	if (A->tipoNodo != SET || B->tipoNodo != SET)
		return NULL;
	return A;
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
/*		tData auxB = B;*/
/*		while(auxB != NULL){*/
/*			if(pertenece(A, auxB->dato) != 0) return 1;*/
/*			auxB = auxB->sig;*/
/*		}*/
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
		
