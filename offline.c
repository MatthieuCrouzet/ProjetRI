#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define INTER 4

////////////R//////G//////B/////
float hist[INTER][INTER][INTER];

void init(){
 int r, g, b;
 for(r = 0; r<INTER; r++){
   for(g = 0; g<INTER; g++){
	for(b = 0; b<INTER; b++){
		hist[r][g][b] = 0;
	}
   }
 }
}

void remplir_hist(CIMAGE cim){
 int r, g, b;
 int i, j;
 int nx = cim.nx;
 int ny = cim.ny;
 int nb = ny*nx;
 for (i = 0; i < ny; i++) {    
   for (j = 0; j < nx; j++) { 
    	r = cim.r[j][i]/64;
    	g = cim.g[j][i]/64;
    	b = cim.b[j][i]/64;
      	hist[r][g][b]=hist[r][g][b]+1.0/nb;
   }
 }
}

void remplir_fichier_bin(char* filename, int nb){
 int r, g, b;
 FILE *fp = NULL;
 fp = fopen(filename, "w+");
 if(fp!=NULL){
    for(r = 0; r<INTER; r++){
       for(g = 0; g<INTER; g++){
          for(b = 0; b<INTER; b++){
 		fwrite(&(hist[r][g][b]), sizeof(float), 1, fp);
 	  }
       }
     }
 }
 fclose(fp);
}

void recup_fichier_bin(char* filename){
 int r, g, b;
 FILE *fp = NULL;
 fp = fopen(filename, "w+");
 if(fp!=NULL){
    for(r = 0; r<INTER; r++){
       for(g = 0; g<INTER; g++){
          for(b = 0; b<INTER; b++){
 		fread(&(hist[r][g][b]), sizeof(float), 1, fp);
 	  }
       }
     }
 }
 fclose(fp);
 /*
  for(r = 0; r<INTER; r++){
   printf("\n\t");
   for(g = 0; g<INTER; g++){
     	printf("\n\t");
	for(b = 0; b<INTER; b++){
		printf("%.3f ",hist[r][g][b]);
	}	
   }
 }
 printf("\n");
 */
}






int main (int argc, char *argv[])
{
  CIMAGE cim;
  /*------------------------------------------------*/
  /* lecture d'une image requête                    */
  /*------------------------------------------------*/
  read_cimage(argv[1],&cim);
  /*------------------------------------------------*/
  /* affichage des valeurs pour le premier bloc 8x8 */
  /* comme exemple de traitement                    */
  /*------------------------------------------------*/
  init();
  remplir_hist(cim);
  remplir_fichier_bin(argv[2], cim.ny*cim.nx);
  recup_fichier_bin(argv[2]);
  exit(0);
}
