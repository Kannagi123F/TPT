#include "TAD_AUTOMATA.H"
void Menu();
	
int main(){
	tAF A;
	Menu(&A);
	
	return 0;
}
	
int mensaje(){
	int op;
	printf("Elija como cargar el automata:\n");
	printf("1-Por consola\n");
	printf("2-Pre-cargado\n");
	printf("3-Por archivo Excel\n");
	printf("Ingrese opcion:");
	scanf("%d",&op);
	return op;
}

	
void Menu(tAF *A){
	int op;

	op=mensaje();
	system("cls");
	switch(op){
	case 1:*A =CargarPorConsola();seleccion(*A);break;
	case 2:*A =Cargar_hard();seleccion(*A);break;
	case 3:*A =Carga_desde_excel();seleccion(*A);break;
	}
	
}
