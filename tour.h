#ifndef _TOUR_H
#define _TOUR_H

#include "town.h"

typedef struct tour_t Tour;
typedef struct tourPosition_t TourPosition;

// Crée un tour vide
Tour *createEmptyTour(void);

// Crée un tour contenant les villes présentes dans le fichier filename
Tour *createTourFromFile(char *filename);

// Libère la mémoire occupée par le tour tour.
// Si freeTown est plus grand que 0, les villes sont également libérées
void freeTour(Tour *tour, int townToFree);

// Ajoute la ville town à la fin du tour tour
void addTownAtTourEnd(Tour *tour, Town *town);

// Ajoute la ville town juste après la position pos dans le tour tour
void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town);

// Renvoie la première position dans le tour tour
TourPosition *getTourStartPosition(Tour *tour);

// Renvoie la position qui suit la position pos dans le tour tour.
// Si pos est la denière position dans le tour
// (avant de revenir à la ville de départ), la fonction renverra NULL
TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos);

// Renvoie la ville à la position pos dans le tour tour.
Town *getTownAtPosition(Tour *tour, TourPosition *pos);

// Renvoie le nombre de villes (uniques) dans le tour
int getTourSize(Tour *tour);

// Renvoie la longueur du tour
double getTourLength(Tour *tour);

#endif
