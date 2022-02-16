#ifndef _TSP_H
#define _TSP_H

#include "tour.h"

// Renvoie un nouveau tour qui contient l’ensemble des villes de tour
// ordonnées grâce à la première heuristique.
Tour *heuristic1(Tour *tour);

// Renvoie un nouveau tour qui contient l’ensemble des villes de tour
// ordonnées grâce à la seconde heuristique.
Tour *heuristic2(Tour *tour);

#endif
