#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define INTER 4



int main (int argc, char *argv[])
{
  /*         R  G  B*/
  float hist[INTER][INTER][INTER];
  int i,j,n,nx,ny,nb;
  int r,g,b;
  CIMAGE cim;
  /*------------------------------------------------*/
  /* lecture d'une image requ�te                    */
  /*------------------------------------------------*/
  read_cimage(argv[1],&cim);
  /*------------------------------------------------*/
  /* affichage des valeurs pour le premier bloc 8x8 */
  /* comme exemple de traitement                    */
  /*------------------------------------------------*/
  /*printf("Largeur de l'image : %d\n",cim.nx);
  printf("Hauteur de l'image : %d\n",cim.ny);*/
  nx = cim.nx;
  ny = cim.ny;
  nb = nx*ny;
for(r = 0; r<INTER; r++){
	for(g = 0; g<INTER; g++){
		for(b = 0; b<INTER; b++){
			hist[r][g][b] = 0;
		}
	}
}
/*  printf("Plan rouge du premier bloc 8x8 :\n"); */
  for (j = 0; j < ny; j++) {       /* ligne par ligne */
    for (i = 0; i < nx; i++) {   /* pixel par pixel */
      /*remplir hist[r][g][b]*/
    }
  }
  /*------------------------------------------------*/
 FILE *fp = NULL;
 fp = fopen(argv[2], "w+");
 if(fp!=NULL){
    for(r = 0; r<INTER; r++){
       for(g = 0; g<INTER; g++){
          for(b = 0; b<INTER; b++){
 		fwrite(&(hist[r][g][b]), sizeof(float), 1, fp);
 	  }
       }
     }
 }
  exit(0);
}
