#include "liste.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <printf.h>
#include <string.h>

struct Liste
{
  int taille;
  ElementListe *premier;
};

Liste* liste_creer()
{
  // Allocation de la mémoire
  Liste *liste = malloc(sizeof(Liste));
  if(!liste)
    {
      printf("Erreur d'allocation de mémoire\n");
      exit(1);
    }

  // Initialisation
  liste->taille = 0;
  liste->premier = NULL;

  return liste;
}

int liste_taille(Liste *liste)
{
  return liste->taille;
}

ElementListe* liste_premier(Liste *liste)
{
  return liste->premier;
}

void liste_inserer(Liste *liste, void *val, int pos)
{
  // Conditions
  assert(pos >= 0);
  assert(pos <= liste->taille);

  // Nouvel élément pour la valeur
  ElementListe *element = calloc(1, sizeof(ElementListe));
  if(!element)
    {
      printf("Erreur d'allcation de mémoire\n");
      exit(1);
    }
  element->val = calloc(1, sizeof(*val));
  memcpy(element->val, val, sizeof(*val));

  // Insértion
  if(!pos)
    {
      if(liste->premier)
        {
          ElementListe *ancienPremier = liste->premier;
          liste->premier = element;
          liste->premier->suivant = ancienPremier;
        }
      else
        liste->premier = element;
    }
  else
    {
      ElementListe *courant = liste->premier;
      int i;
      for(i = 0; i < pos - 1; ++i) courant = courant->suivant;

      element->suivant = courant->suivant;
      courant->suivant = element;
    }

  // Incrémentation de la taille
  liste->taille++;
}

void liste_supprimer(Liste *liste, int pos)
{
  assert(pos < liste->taille);

  ElementListe *elem;
  if(!pos)
    {
      elem = liste->premier;
      liste->premier = liste->premier->suivant;
    }
  else
    {
      int i;
      ElementListe *courant = liste->premier;
      for (i = 0; i < pos - 1; ++i) courant = courant->suivant;

      elem = courant->suivant;
      courant->suivant = courant->suivant->suivant;
    }

  // Suppression de la mémoire allouée
  free(elem->val);
  free(elem);

  // Décrementer la taille
  liste->taille--;
}

void liste_detruire(Liste **liste)
{
  while(liste_taille(*liste)) liste_supprimer(*liste, 0);
  free(*liste);
  liste = NULL;
}

int liste_pos_val(void *val, Liste *liste,
                  int (*cmp)(const void *, const void *))
{
  ElementListe *courant = liste->premier;
  int pos;
  for(pos = 0; courant; ++pos, courant = courant->suivant)
      if(cmp(courant->val, val) == 0)
         return pos;
  return -1;
}

ElementListe* liste_acceder(Liste *liste, int pos)
{
  assert(pos >= 0);
  assert(pos < liste_taille(liste));

  ElementListe *courant = liste->premier;
  int i;
  for(i = 0; i < pos ; ++i) courant = courant->suivant;

  return courant;
}
