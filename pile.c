/**
 * @file pile.c
 * @brief fichier d'implementation pour la gestion de pile
 */ 
 
#include <stdlib.h>
#include "pile.h"
 
// Placer ici les fonctions de gestion de pile que vous avez ecrit en TP2 

 
/** TO DO
 * @brief Initialiser une pile du type pile_t
 *   - allocation de memoire pour une structure pile_t et un tableau de taille elements
 * @param [in] taille taille de la pile
 * @return l'adresse de la structure
 */
 
pile_t* initPile(int taille) {
    pile_t  * pile = (pile_t*) malloc(sizeof(pile_t));
    if (pile){
        pile->taille = taille;
        pile->sommet = -1;
        if (taille > 0)
            pile->base = (eltType_pile*) malloc(taille*sizeof(eltType_pile));
        else 
            pile->base = NULL;
        if (pile->base == NULL) {
                free(pile);
                pile = NULL;
        }  
     }
    return pile;
 }
    


/** TO DO
 * @brief Liberer les memoires occupees par la pile
 * @param [in, out] adrPtPile l'adresse du pointeur de la structure pile_t
 */
void libererPile(pile_t** adrPtPile)
 {
    if(*adrPtPile != NULL) {
        free((*adrPtPile)->base) ;
        free(*adrPtPile);
        *adrPtPile = NULL ;    
    }
 }


/** TO DO
 * @brief Verifier si la pile est vide (aucun element dans la "base")
 * @param [in] ptPile l'adresse de la structure pile_t
 * @return 1 - vide, ou 0 - non vide
 */
int estVidePile(pile_t* ptPile)
{
    int res = 0; 
    if  (ptPile->sommet == -1) 
          res = 1;  
    return(res) ; 
}


/** TO DO
 * @brief Entrer un element dans la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [in] ptVal l'adresse de la valeur a empiler
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
 
 void empiler(pile_t* ptPile, eltType_pile* ptVal, int* code)
 {
  *code = 1 ;
  if (ptPile->sommet < ptPile->taille -1){
    ptPile->sommet += 1 ;
    copyElt(ptVal , ptPile->base + ptPile->sommet ) ; 
    *code = 0 ; 
  } 
 }


/** TO DO
 * @brief Sortir un element de la pile
 * @param [in, out] ptPile l'adresse de la structure pile_t
 * @param [out] ptRes l'adresse de l'element sorti
 * @param [in, out] code : l'adresse du code de sortie
 *                     *code = 0 si reussi
 *                           = 1 si echec
 */
 
void depiler(pile_t* ptPile, eltType_pile* ptRes, int* code) {
    *code = 1;
    if (estVidePile(ptPile) != 1 ) {        
        copyElt(ptPile->base + ptPile->sommet,ptRes);       
        ptPile->sommet -= 1;
        *code = 0;
    }
}