#include "town.h"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct town_t {
    char *name;
    double positionX;
    double positionY;
};


Town *createTown(const char *name, double x, double y){
    assert(name != NULL);
    
    Town *town = (Town *) malloc(sizeof(Town));
    if (!town) {
        printf("Not enough space to create town\n");
        exit(EXIT_FAILURE);
    }
    
    town -> name = (char *) malloc(strlen(name) * sizeof(char));
    if (!getTownName(town)) {
        printf("Not enough space to create town -> name\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(town -> name, name);
    town -> positionX = x;
    town -> positionY = y;
    
    return town;
}


double getTownX(Town *town){
    assert(town != NULL);
    
    return town -> positionX;
}


double getTownY(Town *town){
    assert(town != NULL);
    
    return town -> positionY;
}


const char *getTownName(Town *town){
    assert(town != NULL);
    
    return town -> name;
}


double distanceBetweenTowns(Town *town1, Town *town2){
    assert(town1 != NULL && town2 != NULL);
    
    return sqrt(pow(getTownX(town1) - getTownX(town2), 2)
                + pow(getTownY(town1) - getTownY(town2), 2));
}


void freeTown(Town *town){
    assert(town != NULL);
    
    free(town -> name);
    free(town);
}
