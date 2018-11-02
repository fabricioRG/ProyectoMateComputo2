//#include "HeaderValues.h"
//#include "HeaderFicheros.h"
#include <stdlib.h>
#include <stdio.h>
const char FICHERO_ARBOL[] = "arbol.txt";
const char FICHERO_RECORRIDO[] = "recorrido.txt";
const char FICHERO_ELIMINAR[] = "eliminar.txt";
const char FICHERO_RECORRIDO_E[] = "recorridoE.txt";
const char FICHERO_NIVEL[] = "nivel.txt";
const char FICHERO_NIVEL_S[] = "nivelS.txt";
const char FICHERO_PESOS[] = "pesos.txt";
const char FICHERO_PESOS_S[] = "pesosS.txt";
const char TEXTO_IN_ORDEN[] = "InOrden: ";
const char TEXTO_PRE_ORDEN[] = "PreOrden: ";
const char TEXTO_POST_ORDEN[] = "PostOrden: ";
#define TRUE 1
#define FALSE 0
FILE *fd;
char *nombre_fich1[];
char *nombre_fich2[];

/* Estructuras y tipos */
typedef struct _nodo {
   int dato;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

Arbol ArbolInt=NULL;

/* Funciones con �rboles: */
/* Insertar en �rbol ordenado: */
void Insertar(Arbol *a, int dat);
/* Borrar un elemento: */
void Borrar(Arbol *a, int dat);
/* Funci�n de b�squeda: */
int Buscar(Arbol a, int dat);
Arbol ObtenerArbol(Arbol a, int dat);
/* Comprobar si el �rbol est� vac�o: */
int Vacio(Arbol r);
/* Comprobar si es un nodo hoja: */
int EsHoja(pNodo r);
/* Contar n�mero de nodos: */
void NumeroNodos(Arbol a, int *contIzq, int *contDer, int dato);
/* Calcular altura de un dato: */
int Altura(Arbol a, int dat);
/* Aplicar una funci�n a cada elemento del �rbol: */
void InOrden(Arbol a);
void PreOrden(Arbol a);
void PostOrden(Arbol a);

/* Funciones auxiliares: */
void Podar(Arbol *a);
void auxContador(Arbol nodo, int *c);
void auxAltura(Arbol a, int, int*);

void Mostrar(int *d);

/*Funcion encargada de leer el archivo de entrada*/
void leerArchivo(int opcion);
/*Funcion que recibe como parametro un numero para imprimir su caracter*/
void imprimirDato(int dato);
/*Metodo encargado de imprimir los tres recorridos*/
void imprimirRecorridos();
/*Funcion encargada de imprimir el nivel en un archivo*/
void imprimirNivel(int dato);
/*Funcion encargada de imprimir el peso en un archivo*/
void imprimirPeso(int dato, int *c1, int *c2);

/*Funcion principal*/
int main()
{
   int altura;
   /* Inserci�n de nodos en �rbol: */
   leerArchivo(1);
   imprimirRecorridos();

   leerArchivo(2);
   imprimirRecorridos();   

   leerArchivo(3);

   leerArchivo(4);

   printf("===============> Proceso Terminado <===============\n");
   /* Liberar memoria asociada al �rbol: */
   Podar(&ArbolInt);
   return 0;
}

/* Poda: borrar todos los nodos a partir de uno, incluido */
void Podar(Arbol *a)
{
   /* Algoritmo recursivo, recorrido en postorden */
   if(*a) {
      Podar(&(*a)->izquierdo); /* Podar izquierdo */
      Podar(&(*a)->derecho);   /* Podar derecho */
      free(*a);                /* Eliminar nodo */
      *a = NULL;
   }
}

/* Insertar un dato en el �rbol ABB */
void Insertar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual = *a;

   /* Buscar el dato en el �rbol, manteniendo un puntero al nodo padre */
   while(!Vacio(actual) && dat != actual->dato) {
      padre = actual;
      if(dat < actual->dato) actual = actual->izquierdo;
      else if(dat > actual->dato) actual = actual->derecho;
   }

   /* Si se ha encontrado el elemento, regresar sin insertar */
   if(!Vacio(actual)) return;
   /* Si padre es NULL, entonces el �rbol estaba vac�o, el nuevo nodo ser�
      el nodo raiz */
   if(Vacio(padre)) {
      *a = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
   }
   /* Si el dato es menor que el que contiene el nodo padre, lo insertamos
      en la rama izquierda */
   else if(dat < padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
   }
   /* Si el dato es mayor que el que contiene el nodo padre, lo insertamos
      en la rama derecha */
   else if(dat > padre->dato) {
      actual = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = actual;
      actual->dato = dat;
      actual->izquierdo = actual->derecho = NULL;
  }
}

/* Eliminar un elemento de un �rbol ABB */
void Borrar(Arbol *a, int dat)
{
   pNodo padre = NULL;
   pNodo actual;
   pNodo nodo;
   int aux;

   actual = *a;
   /* Mientras sea posible que el valor est� en el �rbol */
   while(!Vacio(actual)) {
      if(dat == actual->dato) { /* Si el valor est� en el nodo actual */
         if(EsHoja(actual)) { /* Y si adem�s es un nodo hoja: lo borramos */
            if(padre) /* Si tiene padre (no es el nodo raiz) */
               /* Anulamos el puntero que le hace referencia */
               if(padre->derecho == actual) padre->derecho = NULL;
               else if(padre->izquierdo == actual) padre->izquierdo = NULL;
            free(actual); /* Borrar el nodo */
            actual = NULL;
            return;
         }
         else { /* Si el valor est� en el nodo actual, pero no es hoja */
            padre = actual;
            /* Buscar nodo m�s izquierdo de rama derecha */
            if(actual->derecho) {
               nodo = actual->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            /* O buscar nodo m�s derecho de rama izquierda */
            else {
               nodo = actual->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* Intercambiar valores de no a borrar u nodo encontrado
               y continuar, cerrando el bucle. El nodo encontrado no tiene
               por qu� ser un nodo hoja, cerrando el bucle nos aseguramos
               de que s�lo se eliminan nodos hoja. */
            aux = actual->dato;
            actual->dato = nodo->dato;
            nodo->dato = aux;
            actual = nodo;
         }
      }
      else { /* Todav�a no hemos encontrado el valor, seguir busc�ndolo */
         padre = actual;
         if(dat > actual->dato) actual = actual->derecho;
         else if(dat < actual->dato) actual = actual->izquierdo;
      }
   }
}

/* Recorrido de �rbol en inorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void InOrden(Arbol a)
{
   if(a->izquierdo) InOrden(a->izquierdo);
   //func(&(a->dato));
   imprimirDato(a->dato);
   if(a->derecho) InOrden(a->derecho);
}

/* Recorrido de �rbol en preorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void PreOrden(Arbol a)
{
   //func(&a->dato);
   imprimirDato(a->dato);
   if(a->izquierdo) PreOrden(a->izquierdo);
   if(a->derecho) PreOrden(a->derecho);
}

/* Recorrido de �rbol en postorden, aplicamos la funci�n func, que tiene
   el prototipo:
   void func(int*);
*/
void PostOrden(Arbol a)
{
   if(a->izquierdo) PostOrden(a->izquierdo);
   if(a->derecho) PostOrden(a->derecho);
   //func(&a->dato);
   imprimirDato(a->dato);
}

/* Buscar un valor en el �rbol */
int Buscar(Arbol a, int dat)
{
   pNodo actual = a;

   /* Todav�a puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->dato) return TRUE; /* dato encontrado */
      else if(dat < actual->dato) actual = actual->izquierdo; /* Seguir */
      else if(dat > actual->dato) actual = actual->derecho;
   }
   return FALSE; /* No est� en �rbol */
}

/*Obtener el arbol segun un valor dado*/
Arbol ObtenerArbol(Arbol a, int dat)
{
   Arbol actual = a;

   /* Todav�a puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->dato) return actual; /* dato encontrado */
      else if(dat < actual->dato) actual = actual->izquierdo; /* Seguir */
      else if(dat > actual->dato) actual = actual->derecho;
   }
   return actual; /* No est� en �rbol */
}

/* Calcular la altura del nodo que contiene el dato dat */
int Altura(Arbol a, int dat)
{
   int altura = 1;
   pNodo actual = a;

   /* Todav�a puede aparecer, ya que quedan nodos por mirar */
   while(!Vacio(actual)) {
      if(dat == actual->dato) return altura; /* encontrado: devolver altura */
      else {
         altura++; /* Incrementamos la altura, seguimos buscando */
         if(dat < actual->dato) actual = actual->izquierdo;
         else if(dat > actual->dato) actual = actual->derecho;
      }
   }
   return -1; /* No est� en �rbol, devolver -1 */
}

/* Contar el n�mero de nodos */
void NumeroNodos(Arbol a, int *contIzq, int *contDer, int dato)
{
   *contIzq = 0;
   *contDer = 0;
   Arbol nodo = ObtenerArbol(ArbolInt, dato);
   if(nodo->izquierdo){
      (*contIzq)++;
      auxContador(nodo->izquierdo, contIzq);
   } /* Funci�n auxiliar */
   if(nodo->derecho){
      (*contDer)++;
      auxContador(nodo->derecho, contDer);
   }  
   imprimirPeso(dato, contIzq, contDer);
}

/* Funci�n auxiliar para contar nodos. Funci�n recursiva de recorrido en
   preorden, el proceso es aumentar el contador */
void auxContador(Arbol nodo, int *c)
{
   if(nodo->izquierdo){
      (*c)++;
      auxContador(nodo->izquierdo, c);
   } 
   if(nodo->derecho){
      (*c)++;
      auxContador(nodo->derecho, c);
   }
}

/* Funci�n auxiliar para calcular altura. Funci�n recursiva de recorrido en
   postorden, el proceso es actualizar la altura s�lo en nodos hojas de mayor
   altura de la m�xima actual */
void auxAltura(pNodo nodo, int a, int *altura)
{
   /* Recorrido postorden */
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1, altura);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1, altura);
   /* Proceso, si es un nodo hoja, y su altura es mayor que la actual del
      �rbol, actualizamos la altura actual del �rbol */
   if(EsHoja(nodo) && a > *altura) *altura = a;
}

/* Comprobar si un �rbol es vac�o */
int Vacio(Arbol r)
{
   return r==NULL;
}

/* Comprobar si un nodo es hoja */
int EsHoja(pNodo r)
{
   return !r->derecho && !r->izquierdo;
}

/* Funci�n de prueba para recorridos del �rbol */
void Mostrar(int *d)
{
   printf("%d, ", *d);
}

/*Leer un archivo dependiendo de texto ya creado, si este no existe se notifica
al usuario*/
void leerArchivo(int opcion){
   int nnodosIzq;
   int nnodosDer;
   if (opcion == 1){
      *nombre_fich2 = FICHERO_ARBOL;
      *nombre_fich1 = FICHERO_RECORRIDO;
   } else if (opcion == 2){
      *nombre_fich2 = FICHERO_ELIMINAR;
      *nombre_fich1 = FICHERO_RECORRIDO_E;
   } else if (opcion == 3){
      *nombre_fich2 = FICHERO_NIVEL;
      *nombre_fich1 = FICHERO_NIVEL_S;
      FILE *fp;
      fp = fopen(*nombre_fich1, "w+");
      fclose(fp);
   } else {
      *nombre_fich2 = FICHERO_PESOS;
      *nombre_fich1 = FICHERO_PESOS_S;
      FILE *fp;
      fp = fopen(*nombre_fich1, "w+");
      fclose(fp);
   }
    int c;
    fd = fopen(*nombre_fich2, "r");
    if(fd == NULL){
        printf("====== No se ha encontrado el archivo '%s' ======\n", *nombre_fich2);
    } else {
       while((c = fgetc(fd)) != EOF) {
           if(c == '\n'){
               //printf("\n");
           } else {
               if(opcion == 1){
                  Insertar(&ArbolInt, c);
               } else if (opcion == 2){
                  if(Buscar(ArbolInt, c) == 1){
                     Borrar(&ArbolInt, c);
                  } else {
                     printf("No se ha encontrado '%c'\n", c);
                  }
                  
               } else if (opcion == 3){
                  if(Buscar(ArbolInt, c) == 1){
                  imprimirNivel(Altura(ArbolInt, c));
                  } else {
                     printf("No se ha encontrado '%c'\n", c);
                  }
               } else if (opcion == 4){
                  if(Buscar(ArbolInt, c) == 1){
                     NumeroNodos(ArbolInt, &nnodosIzq, &nnodosDer, c);
                  } else {
                     printf("No se ha encontrado '%c'\n", c);
                  }
               }
           }
       }
   }
}

void imprimirDato(int dato){
   FILE *fp;
   fp = fopen(*nombre_fich1, "a+t");
   fputc(dato, fp);
   fclose(fp);
}

void imprimirRecorridos(){
   FILE *fp;
   fp = fopen(*nombre_fich1, "w+");
   fputs( TEXTO_IN_ORDEN, fp );
   fclose(fp);
   InOrden(ArbolInt);
   fp = fopen(*nombre_fich1, "a+t");
   fputs( "\n", fp );
   fputs( TEXTO_PRE_ORDEN, fp );
   fclose(fp);
   PreOrden(ArbolInt);
   fp = fopen(*nombre_fich1, "a+t");
   fputs( "\n", fp );
   fputs( TEXTO_POST_ORDEN, fp );
   fclose(fp);
   PostOrden(ArbolInt);
}

void imprimirNivel(int dato){
   FILE *fp;
   fp = fopen(*nombre_fich1, "a+t");
   fprintf(fp, "%d,", dato);
   fclose(fp);
}

void imprimirPeso(int dato, int *c1, int *c2){
   FILE *fp;
   fp = fopen(*nombre_fich1, "a+t");
   fprintf(fp, "Para %c: izquierdo %d - derecho %d\n", dato, *c1, *c2);
   fclose(fp);
}
