/** 
 * Crea un arbol binario y lo recorre en
 * preorden, inorden, y en postOrden 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/* estructura autoreferenciada */
struct nodoArbol { 
 struct nodoArbol *ptrIzq; 
 int dato;
 struct nodoArbol *prtDer; 
};

typedef struct nodoArbol NodoArbol; /* sinónimo de la estructura nodoArbol */
typedef NodoArbol *ptrNodoArbol; /* sinónimo de NodoArbol* */
 
/* prototipos */
void insertaNodo(ptrNodoArbol *ptrArbol, int valor);
void inOrden(ptrNodoArbol ptrArbol);
void preOrden(ptrNodoArbol ptrArbol);
void postOrden(ptrNodoArbol ptrArbol);

/* la función main comienza la ejecución del programa */
int main()
{ 
 int i; /* contador para el ciclo de 1 a 10 */
 int elemento; /* variable para almacenar valores al azar */
 ptrNodoArbol ptrRaiz = NULL; /* árbol inicialemnte vacío */
 
 srand(time(NULL)); 
 printf("Los números colocados en el arbol son:n");
 
 /* inserta valores al azar entre 1 y 15 en el árbol */
 for (i = 1; i <= 10; i++) { 
 elemento = rand() % 15;
 printf("%3d", elemento);
 insertaNodo(&ptrRaiz, elemento);
 }
 
 /* recorre el árbol en preorden */
 printf("nnEl recorrido en preorden es:n");
 preOrden(ptrRaiz);
 
 /* recorre el árbol en in inorden */
 printf("nnEl recorrido inorden es:n");
 inOrden(ptrRaiz);
 
 /* recorre el árbol en postOrden */
 printf("nnEl recorrido en postOrden es:n");
 postOrden(ptrRaiz);
 
 return 0;
}
 
/* inserta un nodo dentro del árbol */
void insertaNodo( ptrNodoArbol *ptrArbol, int valor )
{ 
 /* si el árbol está vacío */
if (*ptrArbol == NULL) { 
	 *ptrArbol = malloc(sizeof(NodoArbol));
	 
	 /* si la memoria está asignada, entonces asigna el dato */
	 if (*ptrArbol != NULL) {
		 (*ptrArbol)->dato = valor;
		 (*ptrArbol)->ptrIzq = NULL;
		 (*ptrArbol)->prtDer = NULL;
	 } else {
	 	printf("no se inserto %d. No hay memoria disponible.n", valor);
	 }
 } else {
	 /* el dato a insertar es menor que el dato en el nodo actual */
	 if (valor < (*ptrArbol)->dato) {
	 	insertaNodo(&((*ptrArbol)->ptrIzq), valor);

	 } else if (valor > (*ptrArbol)->dato) {
	 	insertaNodo(&((*ptrArbol)->prtDer), valor);

	 } else { 
		printf("dup");

	 }

 }
} 
 
/* comienza el recorrido inorden del árbol */
void inOrden(ptrNodoArbol ptrArbol)
{ 
 /* si el árbol no está vacío, entonces recórrelo */
 if (ptrArbol != NULL) {
 inOrden(ptrArbol->ptrIzq);
 printf("%3d", ptrArbol->dato);
 inOrden(ptrArbol->prtDer);
 }
}
 
/* comienza el recorrido preorden del árbol */
void preOrden(ptrNodoArbol ptrArbol)
{ 
 /* si el árbol no está vacío, entonces recórrelo */
 if (ptrArbol != NULL) { 
 printf("%3d", ptrArbol->dato);
 preOrden(ptrArbol->ptrIzq);
 preOrden(ptrArbol->prtDer);
 }
}
 
/* comienza el recorrido postOrden del árbol */
void postOrden(ptrNodoArbol ptrArbol)
{ 
 /* si el árbol no está vacío, entonces recórrelo */
 if (ptrArbol != NULL) { 
 postOrden(ptrArbol->ptrIzq);
 postOrden(ptrArbol->prtDer);
 printf("%3d", ptrArbol->dato);
 }
}