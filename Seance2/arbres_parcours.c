/**
 * @file arbres_parcours.c
 * @brief fichier d'implementation du module pour le parcours d'arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_parcours.h"

 
/** TO DO
 * @brief calculer le nombre de fils ou freres d'un point a partir du pointeur du debut de la liste
 * @param [in] ptCell pointeur vers le 1er frere
 * @return le nombre de fils ou freres
 */
int getNbFils_ou_Freres(cell_lvlh_t * ptCell)
{
    cell_lvlh_t * cour = ptCell;
    int nb = 0;
    while (cour != NULL)
    {
        cour= cour->lh; 
        nb++; 
    }
    return (nb);
}


/** TO DO
 * @brief parcours en profondeur postfixee
 * @param [in] file le flux de sortie
 * @param [in] racine la racine de l'arborescence
 */
void printPostfixee(FILE * file, cell_lvlh_t* racine )
 {
    pile_t       * pile   = initPile(NB_ELTPREF_MAX);
    cell_lvlh_t  * cour   = racine;
    eltType_pile * cp     = (eltType_pile*) malloc (sizeof(eltType_pile));
    int  code = 0;
    cp->adrPrec =NULL;
    cp->nbFils_ou_Freres = 0; 
    
    while (cour != NULL)
    {
        while (cour->lv != NULL) 
        {
            cp->adrCell= cour; 
            empiler(pile,cp,&code);
            cour= cour->lv;
        }
        fprintf(file, "(%c,%d) ", cour->val, getNbFils_ou_Freres(cour->lv));
        cour=cour->lh;
        while ((cour == NULL) && (!estVidePile(pile)))
        {
            depiler(pile,cp,&code);
            cour=cp->adrCell; 
            fprintf(file, "(%c,%d) ", cour->val, getNbFils_ou_Freres(cour->lv));
            cour=cour->lh; 
        }
    }
    libererPile(&pile);
}