/**
 * @file arbres_insert.c
 * @brief fichier d'implementation du module pour l'insertion de valeur dans une arborescence
 */
#include <stdio.h>
#include <stdlib.h>

#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_insert.h"
 

/**
 * @brief rechercher un point de valeur v
 * @param [in] racine pointeur vers la racine de l'arborescence 
 * @return 
 *   - l'adresse du point contenant v si v existe dans l'arborescence
 *   - NULL, sinon
 */
cell_lvlh_t* rechercher_v(cell_lvlh_t* racine, char v)
{
    pile_t       * pile   = initPile(NB_ELTPREF_MAX);
    cell_lvlh_t  * cour   = racine;
    eltType_pile * cp     = (eltType_pile*) malloc (sizeof(eltType_pile));
    int  code = 0;

    if (cp) 
    {
        while ((cour) && (cour->val != v)) // on parcourt l'arbre tant qu'on ne trouve pas v 
        {
            cp->adrCell = cour; 
            empiler(pile, cp, &code); // on empile l'élément courant 
            cour = cour->lv;         // on passe à lv 
            while ((cour == NULL) && (!estVidePile(pile))) 
            {
                depiler(pile, cp, &code); 
                cour = cp->adrCell;
                cour = cour->lh; // on passe à lh 
            }
        }
        free(cp);
    }  
    libererPile(&pile); 
    return(cour);
}
 
/**
 * @brief rechercher le double prec de w dans une liste de fils
 * @param [in] adrPere l'adresse du pere
 * @param [in] w la valeur a inserer
 * @return l'adresse du pointeur prec apres lequel w doit etre inseree
 */
cell_lvlh_t** rechercherPrecFilsTries(cell_lvlh_t* adrPere, char w)
{
    cell_lvlh_t **  pprec = NULL; // Même comportement qu'une liste chainée avec un pointeur pprec
    pprec = &(adrPere->lv);  // adressage indirect de la lch des fils 
    while ((*pprec != NULL) && ((*pprec)->val < w))
    {
        pprec = &((*pprec)->lh);
    }
    return (pprec);
}

/** TO DO
 * @brief inserer une valeur w dans les fils d'un point de valeur v
 * @param [in] racine la racine de l'arborescence
 * @param [in] v la valeur d'un point auquel on va inserer la valeur w en fils
 * @param [in] w la valeur a inserer
 * @return 1 - insertion realisee; 0 - insertion n'a pas ete realisee
 */
int insererTrie(cell_lvlh_t *racine, char v, char w)
{
    cell_lvlh_t *  pere     = rechercher_v(racine,v),
                *  new      = NULL,
                ** pprec    = NULL;
    int code = 0;
    if (pere) // si le point auquel on va insérer existe 
    {
        pprec = rechercherPrecFilsTries(pere,w); // on cherche l'adr du pointeur prec apres lequel w doit etre inseree
        new   = (cell_lvlh_t*) malloc(sizeof(cell_lvlh_t)); // on crée un nouvel élement
        if (new)
        {
            new->val = w;
            new->lv  = NULL;
            new->lh  = *pprec;
            *pprec   = new; // on relie new à son précedent 
            code     = 1; // insertion réalisée 
        }     
    }    
    return(code);  
}
