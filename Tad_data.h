#ifndef TAD_DATA_H
#define TAD_DATA_H

#include "TAD_string.h"

#define STR 1
#define SET 2
#define LIST 3

typedef struct nodo_data {
	int nodeType;
	union {
		str string;
		struct {
			struct nodo_data *data;
			struct nodo_data *sig;
		};
	};
} TNodoData;

typedef TNodoData *tData;

/* Creación */
tData create_str_ast();
tData create_list();
tData create_set();

/* Operaciones sobre STR */
tData concat_str(tData s1, tData s2);
int compare_str(tData s1, tData s2);

/* Operaciones sobre LIST */
void append(tData* list, tData elem);
int length(tData list);
tData copy_list(tData list);
tData concat_list(tData l1, tData l2);
int search(tData list, tData elem);

/* Operaciones sobre SET */
void insert_set(tData* set, tData elem);
int belongs(tData set, tData elem);
void remove_set(tData* set, tData elem);

/* Operaciones algebraicas */
tData union_set(tData A, tData B);
tData intersection_set(tData A, tData B);
tData difference_set(tData A, tData B);
int subset(tData A, tData B);
int equals_set(tData A, tData B);

/* Auxiliares */
void freeData(tData descartado);
void mostrarData(tData nodo);
tData producto_cartesiano(tData A, tData B);
tData toSetWToken(tData cad, char token);
tData str_to_list(tData cadena);
tData list_to_str(tData lista);

#endif
