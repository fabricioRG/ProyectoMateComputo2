#include <stdio.h>
const char FICHERO_ARBOL[] = "arbol.txt";
const char FICHERO_RECORRIDO[] = "recorrido.txt";
const char FICHERO_ELIMINAR[] = "eliminar.txt";
const char FICHERO_RECORRIDO_E[] = "recorridoE.txt";
const char FICHERO_NIVEL[] = "nivel.txt";
const char FICHERO_NIVEL_S[] = "nivelS.txt";
const char FICHERO_PESOS[] = "pesos.txt";
const char FICHERO_PESOS_S[] = "pesosS.txt";
extern char *texto2[];
char *nombre_fich1[];
char *nombre_fich2[];

enum {EXITO, FALLO, LONGITUD_MAXIMA = 80};

int error_msg(char *nombre_fichero) 
{
	printf("Falló algo con el fichero %s.\n", nombre_fichero);
	return FALLO;
}

int leerArchivo(int opcion){
	FILE *ptr_fich1, *ptr_fich2;
	if (opcion == 1){
		*nombre_fich2 = FICHERO_ARBOL;
		*nombre_fich1 = FICHERO_RECORRIDO;
	} else if (opcion == 2){
		*nombre_fich2 = FICHERO_ELIMINAR;
		*nombre_fich1 = FICHERO_RECORRIDO_E;
	} else if (opcion == 3){
		*nombre_fich2 = FICHERO_NIVEL;
		*nombre_fich1 = FICHERO_NIVEL_S;
	} else {
		*nombre_fich2 = FICHERO_PESOS;
		*nombre_fich1 = FICHERO_PESOS_S;
	}

	  int resultado = EXITO;

  if ( (ptr_fich1 = fopen(*nombre_fich1, "w")) == NULL ) {
    resultado = error_msg(*nombre_fich1);
  } else {
    if ((ptr_fich2 = fopen(*nombre_fich2, "r")) == NULL ){
      resultado = error_msg(*nombre_fich2);
    } else {
      int num;
      char buffer[LONGITUD_MAXIMA + 1];

      while(!feof(ptr_fich2)) {
        num = fread(buffer,sizeof(char), LONGITUD_MAXIMA, ptr_fich2);
        buffer[num*sizeof(char)] = '\0';
        if (fwrite(buffer, sizeof(char), num, ptr_fich1) != num) {
          resultado = error_msg(*nombre_fich1);
          break;
      	}
        //printf("%s.",buffer);
      } //end of while
      printf("%s", buffer);
      //*texto = buffer;
      fclose(ptr_fich1);
      fclose(ptr_fich2);
      //printf("\n");
      if (fclose(ptr_fich2)!=0) {
        resultado = error_msg(*nombre_fich2);
      }
    }
    if (fclose(ptr_fich2)!=0) {
      resultado = error_msg(*nombre_fich1);
    }
  }
  return resultado;
}
