#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "levenshtein.h"
#include <stdio.h>

char ** trazas;
int **mdist;
char *abc="abcdefghijklmnopqrstuvwxyz";
int main()
{
    int canttrazas=10;
    int tamtraza=10;

    trazas= malloc(sizeof(char*)*canttrazas);
    for(int i=0;i<canttrazas;i++){
        *(trazas+i)=malloc(sizeof(char)*tamtraza);
    }

    cargarTrazas(trazas,canttrazas,tamtraza);
    mdist=malloc(sizeof(int*)*canttrazas);
    for(int i=0;i<canttrazas;i++){
        *(mdist+i)=malloc(sizeof(int)*canttrazas);
    }
    cargarmdist(mdist,canttrazas);

    imprimematrizchar(trazas,canttrazas);
    matrizDistancia(mdist,canttrazas);
    imprimematrizint(mdist,canttrazas);

 return 0;
}

// `levenshtein.c` - levenshtein
// MIT licensed.
// Copyright (c) 2015 Titus Wormer <tituswormer@gmail.com>



// Returns a size_t, depicting the difference between `a` and `b`.
// See <https://en.wikipedia.org/wiki/Levenshtein_distance> for more information.
size_t levenshtein_n(const char *a, const size_t length, const char *b, const size_t bLength) {
  // Shortcut optimizations / degenerate cases.
  if (a == b) {
    return 0;
  }

  if (length == 0) {
    return bLength;
  }

  if (bLength == 0) {
    return length;
  }

  size_t *cache = calloc(length, sizeof(size_t));
  size_t index = 0;
  size_t bIndex = 0;
  size_t distance;
  size_t bDistance;
  size_t result;
  char code;

  // initialize the vector.
  while (index < length) {
    cache[index] = index + 1;
    index++;
  }

  // Loop.
  while (bIndex < bLength) {
    code = b[bIndex];
    result = distance = bIndex++;
    index = SIZE_MAX;

    while (++index < length) {
      bDistance = code == a[index] ? distance : distance + 1;
      distance = cache[index];

      cache[index] = result =
      distance > result? bDistance > result? result + 1: bDistance: bDistance > distance? distance + 1: bDistance;
    }
  }

  free(cache);

  return result;
}

size_t levenshtein(const char *a, const char *b) {
  const size_t length = strlen(a);
  const size_t bLength = strlen(b);

  return levenshtein_n(a, length, b, bLength);
}

/*--------------------------------------------------------------------------------------*/

void matrizDistancia(int ** d,int col){
    for(int i=0;i<col;i++){
        for(int j=0;j<i;j++){
           int dtemp=levenshtein(*(trazas+i),*(trazas+j));
           *(*(mdist+i)+j)=dtemp;
           *(*(mdist+j)+i)=dtemp;
        }
    }
}
//GENERA VALORES PARA LAS TRAZAS
void cargarTrazas(char** t, int c,int l){
    for(int i=0;i<c;i++){
        for(int j=0;j<l;j++){
            *(*(t+i)+j)=*(abc+(((i*j)+j)%26));
        }
    }
}
//INICIALIZA LA MATRIZ DISTANCIA EN 0
void cargarmdist(int** t, int c){
    for(int i=0;i<c;i++){
        for(int j=0;j<c;j++){
            *(*(t+i)+j)=0;
        }
    }
}

//IMPRIME LA MATRIZ DISTANCIA
void imprimematrizint(int** t, int c){
    for(int i=0;i<c;i++){
        for(int j=0;j<c;j++){
            printf("%d\t",*(*(t+i)+j));
        }
        printf("\n");
    }
     printf("\n");
}
//IMPRIME LAS TRAZAS
void imprimematrizchar(char** t, int c,int l){
    for(int i=0;i<c;i++){
        for(int j=0;j<l;j++){
            printf("%c",*(*(t+i)+j));
        }
        printf("\n");
    }
     printf("\n");
}
