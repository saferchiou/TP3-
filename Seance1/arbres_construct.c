
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
    FILE *file = fopen(fileName, "r");
    int i         = 0 ,
        nbRacines = 0;
    
    if (file)
    {
        
        fscanf(file, "%d ", &nbRacines);
        if (nbRacines > 0)
        {
             while(!feof(file))
             {       
                fscanf(file, "%c %d ", &(tabEltPref[i].val), &(tabEltPref[i].nbFils));
                i++;
             }
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
 * @param [in] nbEltsPref le nombre des elements du tabEltPref
 */
void printTabEltPref(FILE *file, eltPrefPostFixee_t *tabEltPref, int nbEltsPref)
 {  
     int i = 0; 
     if (nbEltsPref > 0)
     {
         if (file)
         {
            for (i=0; i<nbEltsPref-1; i++)
            { 
               fprintf(file, "(%c,%d) ", tabEltPref[i].val, tabEltPref[i].nbFils);        
            } 
            fprintf (file, "(%c,%d)\n", tabEltPref[nbEltsPref-1].val, tabEltPref[nbEltsPref-1].nbFils);
         }
     }
 }

/** TO DO
 * @brief creer et initialiser un nouveau point de l'arborescence
 * @param [in] val la valeur du point
 * @return l'adresse du nouveau point 
 */
cell_lvlh_t * allocPoint(char val) {
   cell_lvlh_t * new = malloc(sizeof(cell_lvlh_t));
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
   pile_t        * pile      = initPile(NB_ELTPREF_MAX);
  
   cell_lvlh_t   * new       = NULL,
                 * racine    = NULL;
   int  code = 0,
        i    = 0;
   if (nbRacines >0)
   {
      cell_lvlh_t  ** adrRacine = (cell_lvlh_t**) malloc(sizeof(cell_lvlh_t*));
      if (adrRacine)
      {
         eltType_pile  * cour  = (eltType_pile*) malloc (sizeof(eltType_pile));
         if (cour) 
         {
            cour->nbFils_ou_Freres = nbRacines;
            cour->adrCell = NULL;
            cour->adrPrec = adrRacine;
         
            while ((cour->nbFils_ou_Freres >0) || (!estVidePile(pile))) 
            {
               if (cour->nbFils_ou_Freres >0)  
               {
                  new = allocPoint (tabEltPref[i].val); // crée un nouveau maillon
                  *(cour->adrPrec) = new;  // relie  le nouveau maillon à son prec
                  cour->nbFils_ou_Freres-=1 ;
                  cour->adrPrec= &(new->lh);
                  empiler(pile,cour,&code);  // sauvegarder les infos pour la remontée 
                  cour->adrPrec = &(new->lv); // continue sur lv
                  cour->nbFils_ou_Freres = tabEltPref[i].nbFils; // nb de fils de nouv
                  i++;   // passe à la valeur suivante
               }    
               else 
               {
                  if (!estVidePile(pile)) 
                  {
                     depiler(pile,cour,&code);   // dépiler l'adresse du lh d'un point et le nb de fils ou frere 
                  }
               }
            }
         }
         free(cour);
         cour = NULL;
      }
      racine = *adrRacine;
      free(adrRacine);
   } 
   libererPile(&pile);  
   return(racine);   
}
/** TO DO
 * @brief liberer les blocs memoire d'un arbre
 * @param [in] adrPtRacine l'adresse du pointeur de la racine d'un arbre
 */

void libererArbre(cell_lvlh_t ** adrPtRacine)
{
   cell_lvlh_t  * cour   = NULL;
   pile_t       * pile   = initPile(NB_ELTPREF_MAX);
   eltType_pile * cp     = (eltType_pile*) malloc (sizeof(eltType_pile));
   int  code = 0;
 
   if (cp)
   {
      cp->adrCell = NULL;
      cp->adrPrec = NULL;
      cp->nbFils_ou_Freres = 0;
      while (*adrPtRacine) // tant que l'arbre est non vide 
      {
         cour = *adrPtRacine;
         if (cour->lh)  // on n'empile pas les élements sans frères  
         {
            cp->adrCell = cour->lh; 
            empiler(pile,cp,&code); // sauvegarder l'adresse de lh 
         }   
         *adrPtRacine = cour->lv;  // on passe à lv 
         free(cour);  // on supprime l'élement courant
         cour = NULL;           
         if ((*adrPtRacine == NULL) && (!estVidePile(pile))) // si l'élement n'a pas de fils et la pile n'est pas vide 
         {
            depiler(pile, cp, &code);   // on dépile l'adresse de lh
            *adrPtRacine = cp->adrCell; 
         }
      }
      free(cp);
      adrPtRacine = NULL;
   }
   libererPile(&pile);      
}