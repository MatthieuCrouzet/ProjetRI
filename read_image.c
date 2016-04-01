#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define INTER 4



void init(float hist_tmp[INTER][INTER][INTER]){
 int r, g, b;
 for(r = 0; r<INTER; r++){
   for(g = 0; g<INTER; g++){
	for(b = 0; b<INTER; b++){
		hist_tmp[r][g][b] = 0;
	}
   }
 }
}

void remplir_hist(CIMAGE cim, float hist_tmp[INTER][INTER][INTER]){
 int r, g, b;
 int i, j;
 int nx = cim.nx;
 int ny = cim.ny;
 int nb = ny*nx;
 for (i = 0; i < ny; i++) {    
   for (j = 0; j < nx; j++) { 
    	r = cim.r[j][i]/(256/INTER);
    	g = cim.g[j][i]/(256/INTER);
    	b = cim.b[j][i]/(256/INTER);
      	hist_tmp[r][g][b]=hist_tmp[r][g][b]+1.0/nb;
   }
 }
}

void remplir_hist_bin(char* filename, int nb, float hist_tmp[INTER][INTER][INTER]){
 int r, g, b;
 FILE *fp = NULL;
 fp = fopen(filename, "w+");
 if(fp!=NULL){
    for(r = 0; r<INTER; r++){
       for(g = 0; g<INTER; g++){
          for(b = 0; b<INTER; b++){
 		fwrite(&(hist_tmp[r][g][b]), sizeof(float), 1, fp);
 	  }
       }
     }
 }
 fclose(fp);
}

void recup_hist_bin(FILE *fp, float retour[INTER][INTER][INTER]){
 int r, g, b;
 if(fp!=NULL){
    for(r = 0; r<INTER; r++){
       for(g = 0; g<INTER; g++){
          for(b = 0; b<INTER; b++){
 		fread(&(retour[r][g][b]), sizeof(float), 1, fp);
 	  }
       }
    }
 }
}

float distance(float hist_img[INTER][INTER][INTER], float hist_tmp[INTER][INTER][INTER]){
int r, g, b;
float dist = 0;
	for(r = 0; r<INTER; r++){
	   for(g = 0; g<INTER; g++){
		for(b = 0; b<INTER; b++){
			if(hist_tmp[r][g][b]<hist_img[r][g][b]) {
				dist = dist + (hist_img[r][g][b]-hist_tmp[r][g][b]);
			}else{
				dist = dist + (hist_tmp[r][g][b]-hist_img[r][g][b]);
			}
		}	
	   }
	 }
return dist;
}


void ordonnerTableau(float tableau[], int debut, int fin)
{
   int i, j, tmp;
   for(i=debut; i<=fin; i++){
      for(j=i+1; j<=fin; j++) {
        if(tableau[i]>tableau[j]) {
         tmp = tableau[i];
         tableau[i] = tableau[j];
         tableau[j] = tmp;     
        }
      }
   }
}


int main (int argc, char *argv[])
{
  CIMAGE cim;
  int TAILLE_MAX = 99;
  char chaine[TAILLE_MAX];
  int i;
  float hist_requete[INTER][INTER][INTER];
  float retour[INTER][INTER][INTER];
  float dist[99];
  float hist_tmp[INTER][INTER][INTER];
  read_cimage(argv[1],&cim);
  init(hist_requete);
  remplir_hist(cim,hist_requete);
  FILE *f = NULL;
  f = fopen("test/img.txt","r");
  while(!feof(f)){
  	  fgets(chaine, TAILLE_MAX, f);
  	  chaine[19] = '\0';
  	  printf("%s\n", chaine);
	  init(hist_tmp);
	  read_cimage(chaine,&cim);
	  remplir_hist(cim,hist_tmp);
	  remplir_hist_bin("hist.bin", cim.ny*cim.nx, hist_tmp);
  }
  FILE *fp = NULL;
  fp = fopen("hist.bin", "r");
  for(i=0;i<10;i++){ dist[i] = 0; }
  for(i=0;i<10;i++){
  	init(retour);
  	recup_hist_bin(fp, retour);
  	dist[i] = distance(hist_requete, retour);
  	printf("%.2f ", dist[i]);
  }
  ordonnerTableau(dist,1,10);
  for(i=1;i<=10;i++){
  	printf("%.2f ", dist[i]);
  }	
  fclose(fp);
  exit(0);

}
