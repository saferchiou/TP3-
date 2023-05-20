/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "arbres_parcours.h"
#include "../teZZt.h"

 
BEGIN_TEST_GROUP(ARBRE_PARCOURS)

/*TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
} */


TEST(getNbFils_ou_Freres) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\ngetNbFils_ou_Freres :");
	printf("\033[0m\n");

//	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	//racine = pref2lvlh(tabEltPref, nbRacines);

    racine = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
    racine->val='A';
	racine->lh = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	racine->lh->val = 'C' ;
	racine->lh->lh=NULL;
	racine->lh->lv = NULL ;
    racine->lv = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	racine->lv->val = 'B' ;
	racine->lv->lv= (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
    racine->lv->lv->val='E' ;
	racine->lv->lv->lv =NULL ; 
	racine->lv->lv->lh =NULL ;
	racine->lv->lv->lh = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	racine->lv->lv->lh->val = 'J'; 
	racine->lv->lv->lh->lv= NULL ; 
	racine->lv->lv->lh->lh =NULL ;
    racine->lv->lh= (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ; 
	racine->lv->lh->val= 'D';
	racine->lv->lh->lv = NULL;
	racine->lv->lh->lh = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ; 
	racine->lv->lh->lh->val = 'H'; 
    racine->lv->lh->lh->lh = NULL ; 
	racine->lv->lh->lh->lv = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	racine->lv->lh->lh->lv->val ='G';
	racine->lv->lh->lh->lv->lv = NULL;
    racine->lv->lh->lh->lv->lh = NULL ;


	REQUIRE( NULL != racine );
	//printf("A = %c\n", racine->val);
	CHECK( 2 == getNbFils_ou_Freres(racine) );     // 2 freres y compris lui-meme
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) ); // 3 fils

	REQUIRE( NULL != racine->lv );
//	printf("B = %c\n", racine->lv->val);
	CHECK( 3 == getNbFils_ou_Freres(racine->lv) );     // 3 freres y compris lui-meme
	CHECK( 2 == getNbFils_ou_Freres(racine->lv->lv) ); // 2 fils

	REQUIRE( NULL != racine->lv->lh );
//	printf("D = %c\n", racine->lv->lh->val);
	CHECK( 0 == getNbFils_ou_Freres(racine->lv->lh->lv) ); // 0 fils

	REQUIRE( NULL != racine->lv->lh->lh );
//	printf("H = %c\n", racine->lv->lh->lh->val);
	CHECK( 1 == getNbFils_ou_Freres(racine->lv->lh->lh->lv) ); // 1 fils

	//libererArbre(&racine);
}

TEST(printPostfixee) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[35m\nprintPostFixee :");
	printf("\033[0m\n");

	//nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	//racine = pref2lvlh(tabEltPref, nbRacines);


    racine = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
    racine->val='A';
	racine->lh = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	racine->lv = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	
	racine->lh->val = 'C' ;
	racine->lh->lh=NULL;
	racine->lh->lv = NULL ;
    
	racine->lv->val = 'B' ;
	racine->lv->lh=   NULL ;
	//(cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;  
	racine->lv->lv= (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;

    racine->lv->lv->val='E' ;
	racine->lv->lv->lv =NULL ; 
	racine->lv->lv->lh = NULL ;
	/*(cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;

	racine->lv->lv->lh->val = 'J'; 
	racine->lv->lv->lh->lv= NULL ; 
	racine->lv->lv->lh->lh =NULL ;

    
	racine->lv->lh->val= 'D';
	racine->lv->lh->lv = NULL;
	racine->lv->lh->lh = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ; 

	racine->lv->lh->lh->val = 'H'; 
    racine->lv->lh->lh->lh = NULL ; 
	racine->lv->lh->lh->lv = (cell_lvlh_t*) malloc (sizeof(cell_lvlh_t)) ;
	
	racine->lv->lh->lh->lv->val ='G';
	racine->lv->lh->lh->lv->lv = NULL;
    racine->lv->lh->lh->lv->lh = NULL ;  */
	
	printPostfixee(stdout, racine);
	printPostfixee(file, racine);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") );
	
	//libererArbre(&racine);
}


END_TEST_GROUP(ARBRE_PARCOURS)

int main(void) {
	RUN_TEST_GROUP(ARBRE_PARCOURS);
	return EXIT_SUCCESS;
}