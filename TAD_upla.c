#include "TAD_upla.h"

//Upla 
tUpla Carga_Upla(){
	tUpla nuevo;
	nuevo = createSet();
	return nuevo;
}

void Mostrar_Upla(tUpla A){
	mostrarData(A);
}		
tData transicion(tData ini, tUpla transi, char c){
	tData aux, term, acepta;
	str carac;
	int b;
	b = 0;
	carac = create();
	carac->dato = c;
	while(transi != NULL && b == 0){
		aux = transi->dato;
		
		if(Igualdad(aux->dato, ini) == 0){
			aux = aux->sig;
			acepta = aux->dato;
			
			if(compStr(acepta->cad, carac) == 0){
				b = 1;
			}
			else{
				transi = transi->sig;
			}
		}
		else{
			transi = transi->sig;
		}
		
	}
	if(b == 1){
		aux = aux->sig;
		term = copiarData(aux->dato);
	}
	else{
		term = NULL;
	}
return term;
}

/*tData transicion_ND(tData act, tUpla transi, char c) {*/
/*	tData est_sig = createSet();*/
/*	tData term = createSet();*/
/*	tData aux = createSet();*/
/*	tData nav = createSet();*/
/*	tData auxnav = createSet();*/
/*	str carac = create();*/
/*	int b1=0;*/
/*	carac->dato=c;*/
/*	print(carac);*/
/*	auxnav = act;*/
/*	while(transi!=NULL){*/
/*		aux=transi->dato;*/
/*		if(auxnav!=NULL){*/
/*			nav=auxnav->dato;*/
/*			while(nav!=NULL && b1==0){*/
/*				if(Igualdad(aux->dato,nav)==0){*/
/*					aux=aux->sig;*/
/*					if((compStr(carac , aux->dato->cad))==0){*/
/*						term = aux->sig;*/
/*						b1=1;*/
/*					}*/
/*				}*/
/*				nav=nav->sig;*/
/*			}*/
/*			if(b1==1){*/
/*				agregarData(&est_sig,term);*/
/*				b1=0;*/
/*			}*/
/*			auxnav=auxnav->sig;*/
/*		}*/
/*		transi=transi->sig;*/
/*	}*/
/*	printf("\n");*/
/*	mostrarData(est_sig);*/
/*return est_sig;*/
/*}*/
int seguir(){
	int op;
	
	do{
		printf("\nDesea seguir cargando la upla?\n");
		printf("\nPresione 1 Si");
		printf("\nPresione 0 No");
		printf("\nIngrese su opcion: ");
		scanf("%d",&op);}while (op != 1 && op != 0);
	return op;
}
	
tUpla cargarEstados(){
	tUpla nuevo;
	tData nva;
	nuevo = createSet();
	int b=1;
	
	while (b==1){
	nva=createStr();
	
	printf("\nIngrese el estado: ");
	nva->cad=load();
	agregarData(&nuevo, nva);
	b=seguir();
	}
	
	return nuevo;
}

tUpla cargarAlfabeto(){
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	int b=1;
	
	while (b==1){
		aux=createStr();
		
		printf("\nIngrese el caracter: ");
		aux->cad=load();
		agregarData(&nuevo, aux);
		b=seguir();
	}
	
	return nuevo;
	
}

tUpla cargarInicial(tUpla Estado){
	tUpla nuevo;
	nuevo = createStr();
	do{
	nuevo->cad=load();
	if(pertenece(Estado,nuevo)==0)
		return nuevo;
	}while(pertenece(Estado,nuevo)==1);
	
return NULL;
}

tUpla cargarFinal(tUpla Estado){
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	
	int b=1;
	
	while (b==1){
		aux=createStr();
		
		printf("\nIngrese el estado final: ");
		do{
			aux->cad=load();
			if(pertenece(Estado,aux)==0){
				agregarData(&nuevo, aux);
				mostrarData(nuevo);
            }
		}while(pertenece(Estado,aux)==1);
		
		b=seguir();
	}
	return nuevo;
}

tUpla cargarTransicion(tUpla Alfa, tUpla Estado, int a){
	tUpla nuevo,nav, aux1;
	tData aux;
	nuevo = createList();
	nav=createList();
	aux1=Alfa;
	if(a==1){
		aux=createStr();
	}else
		{aux=createSet();}
	
	while(Estado!=NULL){
		Alfa=aux1;
		while(Alfa!=NULL){
			printf("ingrese el destino de:\n Delta(");
			mostrarData(Estado->dato);
			printf(",");
			mostrarData(Alfa->dato);
			printf(")-->");
			
			if(a==1){
				aux->cad=load();
				agregarData(&nav,Estado->dato);
				agregarData(&nav,Alfa->dato);
				agregarData(&nav,aux);
			}
			else
			   {
				aux=cargarEstados();
				agregarData(&nav,Estado->dato);
				agregarData(&nav,Alfa->dato);
				agregarData(&nav,aux);
				
			}
			agregarData(&nuevo, nav);
			
			nav=NULL;
			
			
			Alfa= Alfa->sig;
		} 
		Estado= Estado->sig;
		
	}
return nuevo;
}
