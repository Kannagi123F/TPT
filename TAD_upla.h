#ifndef TAD_UPLA_H
#define TAD_UPLA_H
#include <string.h>
#include "TAD_data.h"
#define TAM 20
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

tUpla cargarAlfabeto2();
tUpla cargarEstado2();
tUpla cargarInicial2();
tUpla cargarFinal2();
tUpla cargarTransicion2(tUpla ,tUpla);
#endif
