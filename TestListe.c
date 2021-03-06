#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "CuTest/CuTest.h"

#include "lib/liste.h"

void test_liste_copier(CuTest *tc)
{
  Liste *liste = NULL;

  liste_ajouter_suite(&liste, "11 10 5 4 -1 6");

  Liste *copie = liste_copier(liste);

  CuAssertTrue(tc, copie != liste);
  int taille = liste_taille(liste);
  CuAssertIntEquals(tc, taille, liste_taille(copie));

  // Comparer toutes les valeurs
  int i;
  Liste *ptrListe = liste, *ptrCopie = copie;
  for (i = 0; i < taille; ++i)
    {
      CuAssertIntEquals(tc, ptrListe->val, ptrCopie->val);

      ptrCopie = ptrCopie->suiv;
      ptrListe = ptrListe->suiv;
    }
}

void test_inserer_liste_1(CuTest *tc)
{
  Liste *liste = NULL;
  liste_inserer(&liste, 0, 0);
  CuAssertIntEquals(tc, 1, liste_taille(liste));
  CuAssertIntEquals(tc, 0, liste->val);

  liste_ajouter_suite(&liste, "1 2 3 4");
  liste_inserer(&liste, 5, liste_taille(liste));


  CuAssertIntEquals(tc, 6, liste_taille(liste));
}

void test_liste_couper_0(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajouter_suite(&liste, "1 2 3 4 5 6 7 8 9");

  Liste *liste2 = liste_couper(&liste, 0);

  CuAssertIntEquals(tc, 0, liste_taille(liste));
  CuAssertIntEquals(tc, 9, liste_taille(liste2));
}

void test_liste_couper_milieu(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajouter_suite(&liste, "1 2 3 4 5 6 7 8 9");

  Liste *liste2 = liste_couper(&liste, 3);

  CuAssertIntEquals(tc, 3, liste_taille(liste));
  CuAssertIntEquals(tc, 6, liste_taille(liste2));
}

void test_liste_couper_fin(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajouter_suite(&liste, "1 2 3 4 5 6 7 8 9");

  Liste *liste2 = NULL;

  int tailleListe1 = liste_taille(liste);
  int tailleListe2 = liste_taille(liste2);

  liste2 = liste_couper(&liste, liste_taille(liste));

  CuAssertIntEquals(tc, tailleListe1, liste_taille(liste));
  CuAssertIntEquals(tc, tailleListe2, liste_taille(liste2));
}

void test_liste_ajout_suite(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajouter_suite(&liste, "1 2 3 55 6");


  CuAssertIntEquals(tc, 5, liste_taille(liste));

  int numbers[5] = {1, 2, 3, 55, 6};
  Liste *courant = liste;
  int i = 0;
  for(i = 0; i < 5; ++i)
    {
      CuAssertIntEquals(tc, numbers[i], courant->val);
      courant = courant->suiv;
    }

}

void test_liste_ajout_debut(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajout_debut(&liste, 5);

  CuAssertIntEquals(tc, 1, liste_taille(liste));
  CuAssertIntEquals(tc, 5, liste->val);

  int i = 0;
  for(i = 0; i < 10; i++)
    {
      liste_ajout_debut(&liste, i);
    }

  CuAssertIntEquals(tc, 11, liste_taille(liste));
  Liste *courant = liste;


  for(i = 9; courant->suiv->val != 5; i--)
    {
      CuAssertIntEquals(tc, i, courant->val);
      courant = courant->suiv;
    }
}

void test_inserer_liste(CuTest *tc)
{
  Liste *liste = NULL;
  // Test 1:
  liste_ajout_debut(&liste, 5);

  CuAssertIntEquals(tc, 1, liste_taille(liste));
  CuAssertTrue(tc, 5 ==  liste->val);
  CuAssertTrue(tc, NULL == liste->suiv);

  // Test 2:
  // insértion de plusieurs valeurs
  int nbr = 10;
  Liste *liste2 = NULL;
  int i;
  for (i = 0; i < nbr; ++i)
    liste_inserer(&liste2, i * 2, 0);
  // test des valeurs
  Liste *courant = liste2;
  for (i = 0; i < nbr; ++i, courant = courant->suiv)
    CuAssertIntEquals(tc, 2 * (nbr - i - 1), courant->val);
  CuAssertTrue(tc, NULL == courant);

  // Test 3:
  Liste *liste3 = NULL;
  for(i = 0; i < 10; ++i)
    liste_inserer(&liste3, i, liste_taille(liste3));
  CuAssertIntEquals(tc, 10, liste_taille(liste3));
}

void test_supprimer_liste(CuTest *tc)
{
  Liste *liste = NULL;
  int i;
  for(i = 0; i < 4; ++i) liste_inserer(&liste, i, liste_taille(liste));

  liste_supprimer(&liste, 0);
  CuAssertIntEquals(tc, 3, liste_taille(liste));

  liste_supprimer(&liste, liste_taille(liste) - 1);
  CuAssertIntEquals(tc, 1, liste->val);
  CuAssertIntEquals(tc, 2, liste->suiv->val);

  CuAssertIntEquals(tc, 2, liste_taille(liste));

  // Vider la liste
  while(liste_taille(liste)) liste_supprimer(&liste, 0);


  CuAssertIntEquals(tc, 0, liste_taille(liste));
}

void Test_liste_taille(CuTest *tc)
{
  Liste *liste = NULL;
  CuAssertIntEquals(tc, liste_taille(liste), 0);
}

void test_premier_liste(CuTest *tc)
{
  Liste *liste = NULL;
  int i;
  for (i = 0; i < 10; ++i) liste_inserer(&liste, i, liste_taille(liste));

  CuAssertIntEquals(tc, 0, liste->val);
  CuAssertIntEquals(tc, 1, liste->suiv->val);
}

void test_liste_pos(CuTest *tc)
{
  Liste *liste = NULL;
  int i;
  for(i = 0; i < 19; ++i)
    liste_inserer(&liste, i, liste_taille(liste));

  CuAssertIntEquals(tc, 3, liste_recherche(3, liste, NULL));
  CuAssertIntEquals(tc, -1, liste_recherche(44, liste, NULL));
  liste_detruire(&liste);
}

void test_liste_acceder(CuTest *tc)
{
  Liste *liste = NULL;
  int i;
  for(i = 0; i < 10; ++i)
    liste_inserer(&liste, i, liste_taille(liste));

  CuAssertIntEquals(tc, 0, liste_acceder(liste, 0)->val);

  liste_detruire(&liste);
}

void test_liste_intersection(CuTest *tc)
{
  Liste *liste1 = NULL, *liste2 = NULL;

  liste_inserer(&liste1, 1, 0);
  liste_inserer(&liste1, 2, 0);
  liste_inserer(&liste1, 3, 0);
  liste_inserer(&liste1, 4, 0);

  liste_inserer(&liste2, 3, 0);
  liste_inserer(&liste2, 4, 0);
  liste_inserer(&liste2, 5, 0);
  liste_inserer(&liste2, 6, 0);
  liste_inserer(&liste2, 7, 0);
  liste_inserer(&liste2, 8, 0);


  Liste *intersect = liste_intersection(liste1, liste2);

  CuAssertIntEquals(tc, 2, liste_taille(intersect));
  CuAssertTrue(tc, -1 != liste_recherche(3, intersect, NULL));
  CuAssertTrue(tc, -1 != liste_recherche(4, intersect, NULL));
  liste_detruire(&liste1);
  liste_detruire(&liste2);
}

void test_liste_echange(CuTest *tc)
{
  Liste *liste = NULL;
  int i;
  for(i = 0; i < 10; ++i) liste_ajout_fin(&liste, i);
  liste_echange(liste, 4, 6);

  CuAssertIntEquals(tc, 6, liste_acceder(liste, 4)->val);
  CuAssertIntEquals(tc, 4, liste_acceder(liste, 6)->val);

  liste_echange(liste, 0, 9);
  CuAssertIntEquals(tc, 10, liste_taille(liste));
  CuAssertIntEquals(tc, 0, liste_acceder(liste, 9)->val);
  CuAssertIntEquals(tc, 9, liste_acceder(liste, 0)->val);

  liste_detruire(&liste);
}

void test_liste_tri_bulles(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 10; ++i) liste_ajout_fin(&liste, rand() % 100);

  liste_tri_bulles(liste, 0);
  CuAssertIntEquals(tc, 10, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv) {
      CuAssertTrue(tc, courant->val <= courant->suiv->val);
    }

  liste_detruire(&liste);
}

void test_liste_ajout_fin(CuTest *tc)
{
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 100; ++i) liste_ajout_fin(&liste, i);

  CuAssertIntEquals(tc, 100, liste_taille(liste));

  // Test
  Liste *courant;
  for(i = 0, courant = liste; courant; courant = courant->suiv, ++i)
    CuAssertIntEquals(tc, i, courant->val);

  liste_detruire(&liste);
}

void test_liste_insertion_ordonee(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 100; ++i) liste_insertion_ordonnee(&liste, rand() % 100);

  CuAssertIntEquals(tc, 100, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv) {
      CuAssertTrue(tc, courant->val <= courant->suiv->val);
    }

  liste_detruire(&liste);
}

void test_liste_tri_insertion(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 100; ++i) liste_ajout_fin(&liste, rand() % 1000);

  liste_tri_insertion(&liste, 0);
  CuAssertIntEquals(tc, 100, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv) {
      CuAssertTrue(tc, courant->val <= courant->suiv->val);
    }

  liste_detruire(&liste);
}

void test_liste_min(CuTest *tc)
{
  Liste *liste = NULL;
  liste_ajout_debut(&liste, 12);
  liste_ajout_debut(&liste, 14);
  liste_ajout_debut(&liste, 1);
  liste_ajout_debut(&liste, -1);
  liste_ajout_debut(&liste, 4);
  liste_ajout_debut(&liste, 3);
  liste_ajout_debut(&liste, 0);

  Liste *min = liste_min(liste);
  CuAssertIntEquals(tc, 7, liste_taille(liste));
  CuAssertIntEquals(tc, -1, min->val);
  liste_detruire(&liste);
}

void test_liste_tri_selection(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 100; ++i) liste_ajout_fin(&liste, rand() % 1000);

  liste_tri_selection(&liste, 0);
  CuAssertIntEquals(tc, 100, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv)
      CuAssertTrue(tc, courant->val <= courant->suiv->val);

  liste_detruire(&liste);
}

void test_liste_tri_rapide(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 10; ++i) liste_ajout_fin(&liste, rand() % 1000);

  liste_tri_rapide(&liste, NULL, 0);
  CuAssertIntEquals(tc, 10, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv)
      CuAssertTrue(tc, courant->val <= courant->suiv->val);

  liste_detruire(&liste);
}

void test_liste_tri_tas(CuTest *tc)
{
  // Remplissage de liste avec des nombres aléatoires
  srand(time(NULL));
  Liste *liste = NULL;

  int i;
  for(i = 0; i < 10; ++i) liste_ajout_fin(&liste, rand() % 1000);

  liste_tri_tas(liste, 0);
  CuAssertIntEquals(tc, 10, liste_taille(liste));

  // Test
  Liste *courant;
  for(courant = liste; courant->suiv; courant = courant->suiv)
      CuAssertTrue(tc, courant->val <= courant->suiv->val);

  liste_detruire(&liste);
}

CuSuite* Liste_get_suite()
{
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_liste_ajout_debut);
  SUITE_ADD_TEST(suite, test_liste_acceder);
  SUITE_ADD_TEST(suite, test_inserer_liste);
  SUITE_ADD_TEST(suite, test_premier_liste);
  SUITE_ADD_TEST(suite, test_supprimer_liste);
  SUITE_ADD_TEST(suite, Test_liste_taille);
  SUITE_ADD_TEST(suite, test_liste_pos);
  SUITE_ADD_TEST(suite, test_liste_intersection);
  SUITE_ADD_TEST(suite, test_liste_echange);
  SUITE_ADD_TEST(suite, test_liste_tri_bulles);
  SUITE_ADD_TEST(suite, test_liste_ajout_fin);
  SUITE_ADD_TEST(suite, test_liste_insertion_ordonee);
  SUITE_ADD_TEST(suite, test_liste_tri_insertion);
  SUITE_ADD_TEST(suite, test_liste_min);
  SUITE_ADD_TEST(suite, test_liste_tri_selection);
  SUITE_ADD_TEST(suite, test_liste_tri_rapide);
  SUITE_ADD_TEST(suite, test_liste_tri_tas);
  SUITE_ADD_TEST(suite, test_liste_couper_0);
  SUITE_ADD_TEST(suite, test_liste_couper_milieu);
  SUITE_ADD_TEST(suite, test_liste_ajout_suite);
  SUITE_ADD_TEST(suite, test_liste_couper_fin);
  SUITE_ADD_TEST(suite, test_inserer_liste_1);
  SUITE_ADD_TEST(suite, test_liste_copier);

  return suite;
}


