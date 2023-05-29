/**
 * program for general linked list testing
 */
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "arbres_construct.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_CONSTRUCT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );
	free(new);
}

TEST(lirePref_fromFileName1_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	printf("\033[34m\nlirePref_fromFileName1_exTP :");
	printf("\033[0m\n");

	//Cas fichier vide:
	nbRacines = lirePref_fromFileName("../arbreVide.txt", tabEltPref, &nbEltsPref); 
	CHECK( 0 == nbRacines );
	CHECK( 0 == nbEltsPref );

}


TEST(lirePref_fromFileName2_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);

	printf("\033[34m\nlirePref_fromFileName2_exTP :");
	printf("\033[0m\n");

	CHECK( 2 == nbRacines ); 
	CHECK( 13 == nbEltsPref );
	CHECK( 'A' == tabEltPref[0].val );
	CHECK( 3 == tabEltPref[0].nbFils );

	CHECK( 'B' == tabEltPref[1].val );
	CHECK( 2 == tabEltPref[1].nbFils );

	CHECK( 'C' == tabEltPref[7].val );
	CHECK( 2 == tabEltPref[7].nbFils );
	
	CHECK( 'I' == tabEltPref[nbEltsPref-1].val );
	CHECK( 0 == tabEltPref[nbEltsPref-1].nbFils );
}

TEST(printTabEltPref1_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[34m\nprintPref1_exTP :");
	printf("\033[0m\n");

	//Cas fichier vide:

	nbRacines = lirePref_fromFileName("../arbreVide.txt", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "0 ") ); 
	
} 

TEST(printTabEltPref2_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];

	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[34m\nprintPref2_exTP :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	fprintf(file, "%d ", nbRacines);
	printTabEltPref(file, tabEltPref, nbEltsPref);
	fclose(file);
	CHECK( 0 == strcmp(buffer, "2 (A,3) (B,2) (E,0) (J,0) (D,0) (H,1) (G,0) (C,2) (F,3) (K,0) (M,0) (T,0) (I,0)\n") ); 
	
} 

TEST(pref2lvlh1_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	printf("\033[35m\npref2lvlh1_exTP :");
	printf("\033[0m\n");

	// cas fichier vide
	nbRacines = lirePref_fromFileName("../arbreVide.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref,nbRacines);
     
    REQUIRE( racine == NULL );
	CHECK( 0 == nbRacines );
    libererArbre(&racine);
} 

TEST(pref2lvlh2_exTP) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;

	printf("\033[35m\npref2lvlh2_exTP :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref,nbRacines);
     
    REQUIRE(racine != NULL);
    CHECK( 'A' == racine->val );	
    CHECK( 'C' == racine->lh->val );
	CHECK( 'B' == racine->lv->val );
    CHECK( 'D' == racine->lv->lh->val );
	CHECK( 'H' == racine->lv->lh->lh->val );
	CHECK( 'E' == racine->lv->lv->val );
	CHECK( 'J' == racine->lv->lv->lh->val );
	CHECK( NULL == racine->lv->lv->lh->lv );
	CHECK( NULL == racine->lv->lv->lh->lh );
	CHECK( 'G' == racine->lv->lh->lh->lv->val );
	CHECK( 'F' == racine->lh->lv->val );
	CHECK( 'I' == racine->lh->lv->lh->val );
	CHECK( 'K' == racine->lh->lv->lv->val );
	CHECK( 'M' == racine->lh->lv->lv->lh->val );
	CHECK( 'T' == racine->lh->lv->lv->lh->lh->val );
	CHECK( NULL == racine->lh->lv->lv->lh->lh->lh );
    libererArbre(&racine);	
} 
TEST(libererArbre_exTP) {
	int nbRacines  = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t * racine = NULL,
				* new    = NULL;

	printf("\033[35m\nlibererArbre_exTP :");
	printf("\033[0m\n");

	// arbre vide
	libererArbre(&racine);
	REQUIRE(racine == NULL);
	
	// arbre à un seul élement 
	new = allocPoint('S');
	racine = new;
	libererArbre(&racine);
	REQUIRE(racine == NULL);

	// arbre à plusieurs éléments 
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref,nbRacines);
    libererArbre(&racine);
	REQUIRE(racine == NULL);
}

END_TEST_GROUP(ARBRE_CONSTRUCT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_CONSTRUCT);
	return EXIT_SUCCESS;
}
