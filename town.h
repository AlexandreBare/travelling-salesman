#ifndef _TOWN_H
#define _TOWN_H

typedef struct town_t Town;

// Crée une ville nommée name et situé à la position (x,y)
Town *createTown(const char *name, double x, double y);

// Renvoie la coordonnée x de la ville town
double getTownX(Town *town);

// Renvoie la coordonnée y de la ville town
double getTownY(Town *town);

// Renvoie le nom de la ville town
const char *getTownName(Town *town);

// Renvoie la distance euclidienne entre les villes town1 et town2.
double distanceBetweenTowns(Town *town1, Town *town2);

// Libère la mémoire prise par town
void freeTown(Town *town);

#endif
