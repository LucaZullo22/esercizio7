// strcpy crea semplicemente un nuovo oggetto di tipo char* con il contenuto all'interno della stringa passata in parametro
// malloc alloca nella memoria un tot di byte, è comodo usarlo con sizeof() per determinare la grandezza di un tipo di dati
// free è come il delete di cpp, permette di liberare la memoria
// spawn() è usato per creare un processo, restituisce un valore in base allo stato del processo
// open() permette di aprire un file con l'aiuto di un puntatore FILE*
// fopen() è come open() ma fa parte di stdio.h
// fwrite() permette di scrivere all'interno di un file


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_DIM 1024

/**
*menu che permette di scrivere un buffer dentro un file
*
*/

int main(int argc, char* argv[]){
 FILE* file;
 unsigned char buffer[BLOCK_DIM];
 int n;
 int fifo;
 
 if (argc != 2)
 {
  printf("Uso: %s file\r\n", argv[0]);
  return 0;
 }

 fifo = open("my_fifo", O_RDONLY);
 if (fifo < 0)
 {
  printf("Errore apertura FIFO\r\n");
  return 0;
 }
 file = fopen(argv[1], "wb");
 if (file == NULL)
 {
  printf("Errore apertura file \"%s\"\r\n", argv[1]);
  close(fifo);
  return 0;
 }
 while ((n = read(fifo, buffer, sizeof(buffer))) > 0)
      fwrite(buffer, 1, n, file);
 close(fifo);
 fclose(file);
 return 1;
}
