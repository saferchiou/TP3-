/**
 * program for general linked list testing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pile.h"
#include "../eltsArbre.h"
#include "../Seance1/arbres_construct.h"
#include "../Seance2/arbres_parcours.h"
#include "arbres_insert.h"
#include "../teZZt.h"


BEGIN_TEST_GROUP(ARBRE_INSERT)

TEST(nouvCell) {
	cell_lvlh_t *new;

	new = allocPoint('A');
	REQUIRE( NULL != new ); 
	CHECK( 'A' == new->val );
	CHECK( NULL == new->lv );
	CHECK( NULL == new->lh );

	free(new);
}


TEST(rechercher_v) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;

	printf("\033[35m\nrechercher_v :");
	printf("\033[0m\n");

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'X');   // valeur inexistante
	CHECK( NULL == pere );

	pere = rechercher_v(racine, 'A');   // valeur a la racine
	REQUIRE( NULL != pere );
	CHECK( 'A' == pere->val );
// autres tests a ajouter
	pere = rechercher_v(racine, 'T');   // 
	REQUIRE( NULL != pere );
	CHECK( 'T' == pere->val );

	pere = rechercher_v(racine, 'H');   // 
	REQUIRE( NULL != pere );
	CHECK( 'H' == pere->val );


	//libererArbre(&racine);
}

TEST(rechercherPrecFilsTries) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	cell_lvlh_t *pere = NULL;
	cell_lvlh_t **pprec = NULL;

	printf("\033[34m\nrechercherPrecFilsTries :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	pere = rechercher_v(racine, 'F');
	REQUIRE( NULL != pere );
	CHECK( 'F' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'A');
	REQUIRE( NULL != *pprec );
	CHECK( 'K' == (*pprec)->val );
// autres tests a ajouter
	pere = rechercher_v(racine, 'D');
	REQUIRE( NULL != pere );
	CHECK( 'D' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'R');
	CHECK( NULL == *pprec );

	pere = rechercher_v(racine, 'B');
	REQUIRE( NULL != pere );
	CHECK( 'B' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'H');
	REQUIRE( NULL != *pprec );
	CHECK( 'J' == (*pprec)->val );

	pere = rechercher_v(racine, 'H');
	REQUIRE( NULL != pere );
	CHECK( 'H' == pere->val );

	pprec = rechercherPrecFilsTries(pere, 'Z');
	CHECK( NULL == *pprec );


	// libererArbre(&racine);
}

TEST(insererTrie) {
	int nbRacines = 0;
	int nbEltsPref = 0;
	eltPrefPostFixee_t tabEltPref[NB_ELTPREF_MAX];
	cell_lvlh_t *racine = NULL;
	
	char buffer[1024];
	FILE * file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	printf("\033[34m\ninsererTrie :");
	printf("\033[0m\n");
	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);

	REQUIRE(0 == insererTrie(racine,'X','A'));

	REQUIRE(1 == insererTrie(racine,'F','A'));
	printPostfixee(file, racine);
	fprintf(file, "%d\n", nbRacines);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (D,0) (G,0) (H,1) (A,3) (A,0) (K,0) (M,0) (T,0) (F,4) (I,0) (C,2) 2\n") );

	file = fmemopen(buffer, 1024, "w");
	REQUIRE ( NULL != file);

	nbRacines = lirePref_fromFileName("../pref_exTP.txt", tabEltPref, &nbEltsPref);
	racine = pref2lvlh(tabEltPref, nbRacines);
	REQUIRE(1 == insererTrie(racine,'D','N'));
	printPostfixee(file, racine);
	fprintf(file, "%d\n", nbRacines);
	fclose(file);
	CHECK( 0 == strcmp(buffer,"(E,0) (J,0) (B,2) (N,0) (D,1) (G,0) (H,1) (A,3) (K,0) (M,0) (T,0) (F,3) (I,0) (C,2) 2\n") );

}
END_TEST_GROUP(ARBRE_INSERT)

int main(void) {
	RUN_TEST_GROUP(ARBRE_INSERT);
	return EXIT_SUCCESS;
}
