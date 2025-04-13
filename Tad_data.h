#ifndef TAD_DATA_H
#define TAD_DATA_H

#include "TAD_string.h"
#define STR 1
#define LIST 2
#define SET 3


typedef struct nodo_data{
	int tipoNodo;
	union{
		str cad;
		struct{
			struct nodo_data * dato;
			struct nodo_data * sig;
		};
	};
}TNodoData;

typedef TNodoData * tData;


tData createData(int);

void mostrarData(tData);

void agregarData(tData*, tData);



//operaciones de conjunto

int pertenece(tData,tData);

#endif
