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
	
tUpla cargarAlfabeto2() {
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	int col=0;
	char linea[TAM];
	char*token;
	
	FILE* file = fopen("Datos.csv", "r");
	
	fgets(linea, sizeof(linea), file);
	linea[strcspn(linea, "\n")] = 0;
	token = strtok(linea, ";");
	int n=strlen(linea);
	while(col<n){
		if (col>0){
			aux = createStr();
			aux->cad=load2(token);
			agregarData(&nuevo,aux);}
		token = strtok(NULL, ";");
		col=col+1;
	}
	fclose(file);
	return nuevo;
} 
	
tUpla cargarEstado2() {
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	aux = createStr();
	int fila=0;
	char linea[TAM];
	char*token;
	
	FILE* file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);
	
	while (fgets(linea, sizeof(linea), file) != NULL) {
		linea[strcspn(linea, "\n")] = 0;
		
		token = strtok(linea, ";");
		if (token != NULL) {
			if (token[0] == '*') token=token+1;
			aux = createStr();
			aux->cad = load2(token);  
			agregarData(&nuevo,aux);
		}
		fila++;
	}
fclose(file);
return nuevo;
}
	
tUpla cargarInicial2(){
	tUpla nuevo;
	nuevo = createStr();
	char linea[TAM];
	char*token;
	
	FILE* file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);
	fgets(linea, sizeof(linea), file);
	linea[strcspn(linea, "\n")] = 0;
	token = strtok(linea, ";");
	nuevo->cad=load2(token);
	agregarData(&nuevo,nuevo);
	
	fclose(file);
	return nuevo;
}
	
tUpla cargarFinal2() {	
	tUpla nuevo;
	tData aux;
	nuevo = createSet();
	char linea[TAM];
	char*token;
	
	FILE* file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);
	token = strtok(linea, ";");
	
	while (fgets(linea, sizeof(linea), file) != NULL) {
		linea[strcspn(linea, "\n")] = 0;
		token = strtok(linea, ";");
		if(token[0] == '*')
		{token=token+1;
		aux = createStr();
		aux->cad = load2(token); 
		agregarData(&nuevo,aux);}
	}
	return nuevo;
}	

void cortar_linea(char *linea) {
	if (linea != NULL && linea[0] == '*') {
	memmove(linea, linea + 1, strlen(linea));
	}
}
	
	
tUpla cargarTransicion2(tUpla Alfa, tUpla Estado) {
	tUpla nuevo,nav, aux1;
	tData aux;
	nuevo = createList();
	nav=createList();
	aux1=Alfa;
	char linea[TAM];
	char*token;
	int col;
	
	FILE* file = fopen("Datos.csv", "r");
	fgets(linea, sizeof(linea), file);
	fgets(linea, sizeof(linea), file);
	token = strtok(linea, ";");
	
	while(Estado!=NULL){
		Alfa=aux1;
		if(token[0] == '*')col=1;
		else col=0;
		int c=0;
		while(Alfa!=NULL &&col!='\n'){
			if (col>0){
				c=strlen(token);
				if(c<=3){
					aux=createStr();
					aux->cad=load2(token);
					agregarData(&nav,Estado->dato);
					agregarData(&nav,Alfa->dato);
					agregarData(&nav,aux);
				} else{
					aux->cad=load2(token);
					agregarData(&nav,Estado->dato);
					agregarData(&nav,Alfa->dato);
					agregarData(&nav,aux);	}
			}	
			if (c==0)token = strtok(NULL, ";");
			else if(col>0)
			{agregarData(&nuevo, nav);
			nav=NULL;
			Alfa= Alfa->sig;
			token = strtok(linea, ";");
			}
			else if (col<0 &&token==NULL){
				token = strtok(NULL, ";");}
			
			col=col+1;
		} 
		fgets(linea, sizeof(linea), file);
		if(token[0] == '*')
			cortar_linea(linea);
		token = strtok(linea, ";");
		Estado= Estado->sig;
	}
	return nuevo;

}
