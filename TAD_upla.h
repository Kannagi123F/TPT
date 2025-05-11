#ifndef TAD_UPLA_H
#define TAD_UPLA_H
#include <string.h>
#include "TAD_data.h"

typedef tData tUpla;

tUpla Carga_Upla();
void Mostrar_Upla(tUpla);



//DELTA 
tData transicion(tData,tUpla,char);
tData transicion_ND(tData,tUpla,char);

//Cargas de automata
tUpla cargarEstados();
tUpla cargarAlfabeto();
tUpla cargarInicial(tUpla);
tUpla cargarFinal(tUpla);
tUpla cargarTransicion(tUpla,tUpla,int);
#endif
