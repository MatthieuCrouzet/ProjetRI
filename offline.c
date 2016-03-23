#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "rdjpeg.h"

#define INTER 4



int main (int argc, char *argv[])
{
  float hist[3][4];
  int i,j,n,nx,ny,nb;
  int cpt_z1,cpt_z2,cpt_z3,cpt_z4;
  float z1,z2,z3,z4;
  CIMAGE cim;
  /*------------------------------------------------*/
  /* lecture d'une image requête                    */
  /*------------------------------------------------*/
  read_cimage(argv[1],&cim);
  /*------------------------------------------------*/
  /* affichage des valeurs pour le premier bloc 8x8 */
  /* comme exemple de traitement                    */
  /*------------------------------------------------*/
  /*printf("Largeur de l'image : %d\n",cim.nx);
  printf("Hauteur de l'image : %d\n",cim.ny);*/
/*  printf("Plan rouge du premier bloc 8x8 :\n"); */
  cpt_z1 = 0;
  cpt_z2 = 0;
  cpt_z3 = 0;
  cpt_z4 = 0;
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      if(cim.r[i][j]<(256/INTER)){ cpt_z1++; }
      else if (cim.r[i][j]<(2*256/INTER)){ cpt_z2++; }
      else if(cim.r[i][j]<(3*256/INTER)) { cpt_z3++; }
      else { cpt_z4++; }
    }
    z1 = (float) cpt_z1/64;
    z2 = (float) cpt_z2/64;
    z3 = (float) cpt_z3/64;
    z4 = (float) cpt_z4/64;
    hist[0][0] = z1;
    hist[0][1] = z2;
    hist[0][2] = z3;
    hist[0][3] = z4;
  }
 /* printf("Plan vert du premier bloc 8x8 :\n"); */
  cpt_z1 = 0;
  cpt_z2 = 0;
  cpt_z3 = 0;
  cpt_z4 = 0;
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      if(cim.g[i][j]<(256/INTER)){ cpt_z1++; }
      else if (cim.g[i][j]<(2*256/INTER)){ cpt_z2++; }
      else if(cim.g[i][j]<(3*256/INTER)) { cpt_z3++; }
      else { cpt_z4++; }
    }
    z1 = (float) cpt_z1/64;
    z2 = (float) cpt_z2/64;
    z3 = (float) cpt_z3/64;
    z4 = (float) cpt_z4/64;
    hist[1][0] = z1;
    hist[1][1] = z2;
    hist[1][2] = z3;
    hist[1][3] = z4;
  }
/*  printf("Plan bleu du premier bloc 8x8 :\n"); */
  cpt_z1 = 0;
  cpt_z2 = 0;
  cpt_z3 = 0;
  cpt_z4 = 0;
  for (j = 0; j < 8; j++) {       /* ligne par ligne */
    for (i = 0; i < 8; i++) {   /* pixel par pixel */
      if(cim.b[i][j]<(256/INTER)){ cpt_z1++; }
      else if (cim.b[i][j]<(2*256/INTER)){ cpt_z2++; }
      else if(cim.b[i][j]<(3*256/INTER)) { cpt_z3++; }
      else { cpt_z4++; }
    }
    z1 = (float) cpt_z1/64;
    z2 = (float) cpt_z2/64;
    z3 = (float) cpt_z3/64;
    z4 = (float) cpt_z4/64;
    hist[2][0] = z1;
    hist[2][1] = z2;
    hist[2][2] = z3;
    hist[2][3] = z4;
  }
  /*------------------------------------------------*/

 for(j=0; j<3; j++){
 	for(i=0; i<4; i++){
 	printf("%.3f ",hist[j][i]);
 	}
 	printf("\n");
 }

  exit(0);
}
