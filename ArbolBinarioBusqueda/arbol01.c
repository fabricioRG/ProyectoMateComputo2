
#include <stdio.h>
#include <stdlib.h>

struct ABB{
	int *dato;
	struct ABB *izq;
	struct ABB *der;
};

struct ABB *CrearArbol(){
	struct ABB *raiz;
	raiz = (struct ABB*) malloc(sizeof(struct ABB));
	raiz-> dato = (int*)malloc(2*sizeof(int));
	raiz-> dato[0] = 0;
	raiz-> dato[1] = -1;
	raiz->izq = NULL;
	raiz->der = NULL; 
	return raiz;
}

void Insertar(int dato, struct ABB *raiz){
	if ((raiz!=NULL) && (raiz->izq == NULL) && (raiz-> der == NULL)){
		raiz->dato[0] = dato;
		raiz->dato[1] = 0;
		raiz->izq = CrearArbol();
		raiz->der = CrearArbol();
	}
	if (dato<raiz->dato[0]){
		Insertar(dato, raiz->izq);
	} else if (dato>raiz->dato[0]) {
		Insertar(dato, raiz->der);
	}
}


void Preorden(struct ABB *raiz){
	if(raiz!= NULL){
		if(raiz->dato[1]!=-1){
			printf("%d",raiz->dato[0]);
		}
	}
}



int main(int argc, char** argv){
	struct ABB *arbol;
	arbol = CrearArbol();
	Insertar(1, arbol);
	Preorden(arbol);
	return (0);
}
