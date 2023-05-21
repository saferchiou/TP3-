
/**
 * @file arbres_construct.c
 * @brief fichier d'implementation du programme pour la construction d'une arborescence
 */
#include <stdio.h>
#include <stdlib.h>
 
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
 
/**
 * @brief lire le fichier contenant la representation prefixee de l'arborescence
 * @param [in] fileName le nom du fichier contenant la representation prefixee
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref l'adresse memoire contenant le nombre des elements du tabEltPref
 * @return le nombre de racines
 */  
int lirePref_fromFileName(char* fileName, eltPrefPostFixee_t* tabEltPref, int * nbEltsPref)
 {
    FILE*file = fopen(fileName, "r");
    int i         = 0 ,
        nbRacines = 0;
    if (file)
    {
        fscanf(file, "%d ", &nbRacines);
        if (nbRacines > 0)
             while(!feof(file))
             {       
                fscanf(file, "%c %d ", &(tabEltPref[i].val), &(tabEltPref[i].nbFils));
                i++;
             }
      fclose(file);
    }
    *nbEltsPref = i;
    return (nbRacines); 
 }

/** TO DO
 * @brief afficher les elements de la representation prefixee sur un flux de sortie
 * @param file : le flux de sortie
 * @param [in, out] tabEltPref tableau des elements de la representation prefixee
 * @param [in, out] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
 {  
     int i = 0; 
     if (file)
     {
         for (i=0; i<nbEltsPref-1; i++)
            { 
               if(nbEltsPref >0)
                  fprintf(file, "(%c,%d) ", tabEltPref[i].val, tabEltPref[i].nbFils);        
            } 
         fprintf (file, "(%c,%d)\n", tabEltPref[nbEltsPref-1].val, tabEltPref[nbEltsPref-1].nbFils);
     }
 }

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
 cell_lvlh_t * allocPoint(char val) {
 
  cell_lvlh_t * new = malloc(sizeof(cell_lvlh_t)) ;
  if (new != NULL)
   {
        new->val = val; 
        new->lv = NULL;
        new->lh = NULL; 
   }
   return(new); 
 }

/** TO DO
 * @brief construire un arbre avec lvlh a partir de representation prefixee
 * @param [in] tabEltPref tableau des elements de la representation prefixee
 * @param [in] nbRacines nombre de racines de l'arborescence
 * @return : 
 *     - NULL si l'arbre resultatnt est vide
 *     - l'adresse de la racine de l'arbre sinon
*/

cell_lvlh_t* pref2lvlh(eltPrefPostFixee_t *tabEltPref, int nbRacines){
   pile_t       * pile       = initPile(NB_ELTPREF_MAX);
   cell_lvlh_t  ** adrRacine = (cell_lvlh_t**) malloc(sizeof(cell_lvlh_t*)),
                 * new       = NULL;
   eltType_pile  * cour      = (eltType_pile*) malloc (sizeof(eltType_pile));
   int  code = 0,
        i    = 0;
   if (cour) 
   {
      cour->nbFils_ou_Freres = nbRacines;
      cour->adrCell = *adrRacine;
      cour->adrPrec = adrRacine;
   }
   while ((cour->nbFils_ou_Freres >0) || (!estVidePile(pile))) 
   {
      if (cour->nbFils_ou_Freres >0)  
      {
         new = allocPoint (tabEltPref[i].val);
         *(cour->adrPrec) = new;  
         cour->nbFils_ou_Freres-=1 ;
         cour->adrPrec= &(new->lh);
         empiler(pile,cour,&code);  
         cour->adrPrec = &(new->lv);
         cour->nbFils_ou_Freres = tabEltPref[i].nbFils; 
         i++; 
      }    
      else 
      {
         if (!estVidePile(pile)) 
         {
            depiler(pile,cour,&code);   
         }
      }
   }
   libererPile(&pile);
   return(*adrRacine);   
}
/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */
/*
void libererArbre(cell_lvlh_t ** adrPtRacine)

   
}*/