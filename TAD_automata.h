#ifndef TAD_AUTOMATA_H
#define TAD_AUTOMATA_H
#define TAM 100
#include "TAD_upla.h"


typedef struct{
	tUpla ConjE;
	tUpla Alfabeto;
	tUpla ConjA;
	tUpla Inicial;
	tUpla Delta;
}tAF;

tAF Cargar_aut();
void Mostrar_aut(tAF);
void Verifica_cad(tAF);
tAF Cargar_aut_cons();
tAF Cargar_hard();
tAF CargarPorConsola();
tAF cargar_automata_desde_csv();
void seleccion(tAF);

#endif
