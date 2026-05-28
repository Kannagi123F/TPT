#include "TAD_data.h"
//OPERACIONES PARA CREAR

tData create_str_ast() {
	tData nvo = (tData) malloc(sizeof(TNodoData));
	nvo->string = create();
	nvo->nodeType = STR;
	return nvo;
}

tData create_list() {
	tData nvo = (tData) malloc(sizeof(TNodoData));
	nvo->data = NULL;
	nvo->sig = NULL;
	nvo->nodeType = LIST;
	return nvo;
}

tData create_set() {
	tData nvo = (tData) malloc(sizeof(TNodoData));
	nvo->data = NULL;
	nvo->sig = NULL;
	nvo->nodeType = SET;
	return nvo;
}


//OPERACIONES SOBRE STR


tData concat_str(tData s1, tData s2) {
	if (s1 == NULL || s1->nodeType != STR) return NULL;
	if (s2 == NULL || s2->nodeType != STR) return NULL;
	
	tData nvo_str = create_str_ast();
	nvo_str->string = concat(s1->string, s2->string);
	return nvo_str;
}

int compare_str(tData s1, tData s2) {
	if (s1 == NULL || s1->nodeType != STR) return 1;
	if (s2 == NULL || s2->nodeType != STR) return 1;
	return compStr(s1->string, s2->string);
}

//OPERACIONES AUXILIARES

tData copy_list(tData copiado) {
	tData nvo = NULL;
	if (copiado == NULL) return nvo;
	
	switch (copiado->nodeType) {
	case STR:
		nvo = create_str_ast(); 
		nvo->string = copyStr(copiado->string);
		break;
	case LIST:
		nvo = create_list();
		nvo->data = copy_list(copiado->data);
		nvo->sig = copy_list(copiado->sig);
		break;
	case SET:
		nvo = create_set();
		nvo->data = copy_list(copiado->data);
		nvo->sig = copy_list(copiado->sig);
		break;
	}
	return nvo;
}	

void freeData(tData descartado) {
	if (descartado == NULL) return;
	
	switch (descartado->nodeType) {
	case STR:
		freeString(descartado->string);
		break;
	case LIST:
	case SET:
		freeData(descartado->data);
		freeData(descartado->sig);
		break;
	}
	free(descartado);
}

void mostrarData(tData nodo) {
	if(nodo == NULL) return;
	
	switch(nodo->nodeType) {
	case STR: 
		print(nodo->string);
		break;
	case LIST:
		printf("[");
		tData aux = nodo;
		while(aux != NULL) {
			mostrarData(aux->data);
			if(aux->sig != NULL) printf(",");
			aux = aux->sig;
		}
		printf("]");
		break;
	case SET:
		printf("{");
		tData aux2 = nodo;
		while(aux2 != NULL) {
			mostrarData(aux2->data);
			if(aux2->sig != NULL) printf(",");
			aux2 = aux2->sig;
		}
		printf("}");
		break;
	}
}

//OPERACIONES PARA SET Y LIST

int equals_set(tData A, tData B) {
	if(A == NULL && B == NULL) return 0;
	if(A == NULL || B == NULL || (A->nodeType != B->nodeType)) return 1;
	
	switch(A->nodeType) {
	case STR: 
		return compStr(A->string, B->string);
	case SET: {
		tData auxA = A;
		while(auxA != NULL) {
			if(belongs(B, auxA->data) != 0) return 1;
			auxA = auxA->sig;
		}
		tData auxB = B;
		while(auxB != NULL) {
			if(belongs(A, auxB->data) != 0) return 1;
			auxB = auxB->sig;
		}
		return 0;
	}
	case LIST: {
		tData auxA = A;
		tData auxB = B;
		while(auxA != NULL && auxB != NULL) {
			if(equals_set(auxA->data, auxB->data) != 0) return 1;
			auxA = auxA->sig;
			auxB = auxB->sig;
		}
		if(auxA != NULL || auxB != NULL) return 1;
		return 0;
	}	
	default: return 1;
	}
}

int belongs(tData A, tData elem) {
	if (A == NULL || elem == NULL) return 1;
	if (A->nodeType != LIST && A->nodeType != SET) return 1;
	
	tData aux = A;
	while (aux != NULL) {
		if (equals_set(aux->data, elem) == 0)
			return 0;
		aux = aux->sig;
	}
	return 1;
}

int search(tData list, tData elem) {
	return belongs(list, elem);
}

//OPERACIONES PARA AGREGAR

void append(tData* cab, tData elem) {
	if((*cab) == NULL || (*cab)->data == NULL) {
		tData nvo;
		if(elem->nodeType == STR) {
			if((*cab) != NULL)
				nvo = ((*cab)->nodeType == SET) ? create_set() : create_list();
			else
				nvo = create_list();
			nvo->data = copy_list(elem);
			*cab = nvo;
		} else {
			tData nvo = ((*cab != NULL) ? ((*cab)->nodeType == SET ? create_set() : create_list()) : create_list());
			nvo->data = copy_list(elem);
			*cab = nvo;
		}
	} else {
		switch ((*cab)->nodeType) {
		case STR: 
			return;
		case SET:
		case LIST: {
			tData aux = *cab;
			tData nvo;
			
			if (aux->nodeType == SET) {
				if(belongs(aux, elem) == 0) return; //Evita duplicados 
			}
			while (aux->sig != NULL)
				aux = aux->sig;
			
			nvo = (aux->nodeType == SET) ? create_set() : create_list();
			nvo->data = copy_list(elem);
			aux->sig = nvo;
			break;
		}
		}
	}
}

void insert_set(tData* set, tData elem) {
	append(set, elem); 
}

//OPERACIONES SOBRE LISTAS

int length(tData list) {
	if (list == NULL || (list->nodeType != LIST && list->nodeType != SET)) 
		return 0;
	
	int c = 0;
	while(list != NULL) {
		c++;
		list = list->sig;
	}
	return c;
}

tData concat_list(tData l1, tData l2) {
	if (l1 != NULL && l1->nodeType != LIST) return NULL;
	if (l2 != NULL && l2->nodeType != LIST) return NULL;
	
	tData nueva_cab = NULL;
	tData act = NULL;
	
	tData aux1 = l1;
	while (aux1 != NULL) {
		tData nvo = create_list();
		nvo->data = copy_list(aux1->data);
		if (nueva_cab == NULL) nueva_cab = nvo;
		else act->sig = nvo;
		act = nvo;
		aux1 = aux1->sig;
	}
	
	tData aux2 = l2;
	while (aux2 != NULL) {
		tData nvo = create_list();
		nvo->data = copy_list(aux2->data);
		if (nueva_cab == NULL) nueva_cab = nvo;
		else act->sig = nvo;
		act = nvo;
		aux2 = aux2->sig;
	}
	return nueva_cab;
}

//OPERACIONES ALGEBRAICAS DE CONJUNTOS

tData union_set(tData A, tData B) {
	if (A->nodeType != SET || B->nodeType != SET) return NULL;
	
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	
	while(A != NULL) {
		aux = create_set();
		aux->data = copy_list(A->data);
		if(C_Cab == NULL) C_Cab = aux;
		else C_act->sig = aux;
		C_act = aux;
		A = A->sig;
	}
	while(B != NULL) {
		if(belongs(C_Cab, B->data) != 0) {
			aux = create_set();
			aux->data = copy_list(B->data);
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			C_act = aux;
		}
		B = B->sig;
	}
	return C_Cab;
}

tData intersection_set(tData A, tData B) {
	if (A->nodeType != SET || B->nodeType != SET) return NULL;
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL) {
		if(belongs(B, A->data) == 0) {
			aux = create_set();
			aux->data = copy_list(A->data);
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			C_act = aux;
		}
		A = A->sig;
	}
	return C_Cab;
}

tData difference_set(tData A, tData B) {
	if (A->nodeType != SET || B->nodeType != SET) return NULL;
	tData C_Cab = NULL, C_act = NULL;
	tData aux;
	while(A != NULL) {
		if(belongs(B, A->data) != 0) {
			aux = create_set();
			aux->data = copy_list(A->data);
			if(C_Cab == NULL) C_Cab = aux;
			else C_act->sig = aux;
			C_act = aux;
		}
		A = A->sig;
	}
	return C_Cab;
}

int subset(tData A, tData B) {
	tData auxA = A;
	while(auxA != NULL) {
		if(belongs(B, auxA->data) != 0) return 0;
		auxA = auxA->sig;
	}
	return 1;
}

void remove_set(tData *set, tData elem) {
	if (set == NULL || *set == NULL || (*set)->nodeType != SET || elem == NULL) 
		return;
	
	tData act = *set;
	tData ant = NULL;
	
	while (act != NULL) {
		if (equals_set(act->data, elem) == 0) { 
			if (ant == NULL) *set = act->sig;
			else ant->sig = act->sig;
			act->sig = NULL; 
			freeData(act); 
			return; 
		}
		ant = act;
		act = act->sig;
	}
}

tData producto_cartesiano(tData A, tData B) {
	if (A == NULL || B == NULL || A->nodeType != SET || B->nodeType != SET) 
		return NULL;
	
	tData C_Cab = NULL, C_act = NULL;
	tData auxA = A;
	
	while (auxA != NULL) {
		tData auxB = B;
		while (auxB != NULL) {
			tData par = create_list();
			par->data = copy_list(auxA->data);
			
			tData segundo = create_list();
			segundo->data = copy_list(auxB->data);
			par->sig = segundo;
			
			tData nvo_set = create_set();
			nvo_set->data = par;
			
			if (C_Cab == NULL) C_Cab = nvo_set;
			else C_act->sig = nvo_set;
			C_act = nvo_set;
			auxB = auxB->sig;
		}
		auxA = auxA->sig;
	}
	return C_Cab;
}

//OPERACIONES DE CONVERSION

tData toSetWToken(tData cad, char token) {
	if(cad == NULL || cad->nodeType != STR) return NULL;
	
	tData A_Cab = NULL, A_act = NULL, Aux;
	tData restante = copy_list(cad);
	tData nvoStr;
	
	while (restante->string != NULL) {
		tData parte = create_str_ast();
		parte->string = before_token(restante->string, token);  
		tData siguiente = create_str_ast();
		siguiente->string = after_token(restante->string, token); 
		
		nvoStr = create_str_ast();
		nvoStr->string = parte->string;  
		
		if (belongs(A_Cab, nvoStr) != 0) {
			Aux = create_set();
			Aux->data = nvoStr;
			if (A_Cab == NULL) A_Cab = Aux;
			else A_act->sig = Aux;
			A_act = Aux;
		} else {
			freeData(nvoStr); 
		}
		
		freeString(restante->string);
		restante->string = siguiente->string;
		free(parte); 
		free(siguiente);
	}
	freeData(restante); 
	return A_Cab;
}	

tData str_to_list(tData cadena) {
	if (cadena == NULL || cadena->nodeType != STR) return NULL;
	
	tData lista = NULL;
	tData act = NULL;
	str cad_aux = cadena->string;
	
	while (cad_aux != NULL) {
		tData nvo_str = create_str_ast();
		nvo_str->string = create();
		nvo_str->string->dato = cad_aux->dato;
		
		tData nvo_list = create_list();
		nvo_list->data = nvo_str;
		
		if (lista == NULL) lista = nvo_list;
		else act->sig = nvo_list;
		act = nvo_list;
		cad_aux = cad_aux->sig;
	}
	return lista;
}

tData list_to_str(tData lista) {
	if (lista == NULL || lista->nodeType != LIST) return NULL;
	
	tData str_nvo = create_str_ast();
	str cab = NULL;
	str act_str = NULL;
	tData aux_list = lista;
	
	while (aux_list != NULL) {
		if (aux_list->data != NULL && aux_list->data->nodeType == STR) {
			str c_aux = aux_list->data->string;
			while (c_aux != NULL) {
				str nvo = create();
				nvo->dato = c_aux->dato;
				if (cab == NULL) cab = nvo;
				else act_str->sig = nvo;
				act_str = nvo;
				c_aux = c_aux->sig;
			}
		}
		aux_list = aux_list->sig;
	}
	str_nvo->string = cab;
	return str_nvo;
}
