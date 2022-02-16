#include "tour.h"
#include "town.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE 200
#define DATA_PER_LINE 3


struct tourPosition_t {
    Town *town;
    struct tourPosition_t *next;
};

struct tour_t {
    TourPosition *head;
    TourPosition *tail;
    int size;
};



static void terminate(char *m){
    assert(m != NULL);
    
    printf("%s\n", m);
    exit(EXIT_FAILURE);
}


Tour *createEmptyTour(){
    Tour *tour = (Tour *)malloc(sizeof(Tour));
    
    if (!tour)
        terminate("Not enough space to create a tour");
    
    tour -> head = NULL;
    tour -> tail = NULL;
    tour -> size = 0;
    return tour;
}


Tour *createTourFromFile(char *filename){
    assert(filename != NULL);
    
    Tour *tour = createEmptyTour();
    FILE *f = fopen(filename, "r");
    
    if (!f)
        terminate("Error when opening file");
    
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, f)) {
        char *string = buffer;
        char *token[DATA_PER_LINE];
        
        for (int i = 0; i < DATA_PER_LINE; i++) {
            if ((token[i] = strsep(&string, ",")) == NULL)
                 terminate("Error when reading file");
        }
        
        addTownAtTourEnd(tour, createTown(token[0],
                                          atof(token[1]),
                                          atof(token[2])));
    }
        
    fclose(f);
    
    return tour;
}


void freeTour(Tour *tour, int townToFree){
    assert(tour != NULL && townToFree >= 0);
    
    TourPosition *cur = getTourStartPosition(tour);
    
    while (cur) {
        TourPosition *next = getNextTourPosition(tour, cur);
        if (townToFree > 0)
            freeTown(getTownAtPosition(tour, cur));
        
        free(cur);
        cur = next;
    }
    
    free(tour);
}


void addTownAtTourEnd(Tour *tour, Town *town){
    assert(tour != NULL && town != NULL);
    
    TourPosition *tp = malloc(sizeof(TourPosition));
    
    if (!tp)
        terminate("Not enough space to create a node");
    
    tp -> town = town;
    tp -> next = NULL;
    
    if (tour -> tail)
        tour -> tail -> next = tp;
    else
        tour -> head = tp;
    
    tour -> tail = tp;
    tour -> size++;
}


void addTownAfterTourPosition(Tour *tour, TourPosition *pos, Town *town){
    assert(tour != NULL && pos != NULL && town != NULL);
    
    TourPosition *tp = malloc(sizeof(TourPosition));
    
    if (!tp)
        terminate("Not enough space to create a node");
    
    tp -> town = town;
    tp -> next = getNextTourPosition(tour, pos);
    pos -> next = tp;
    tour -> size++;
}


TourPosition *getTourStartPosition(Tour *tour){
    assert(tour != NULL);
    
    return tour -> head;
}


TourPosition *getNextTourPosition(Tour *tour, TourPosition *pos){
    assert(tour != NULL && pos != NULL);
    
    return pos -> next;
}


Town *getTownAtPosition(Tour *tour, TourPosition *pos){
    assert(tour != NULL && pos != NULL);
    
    return pos -> town;
}


int getTourSize(Tour *tour){
    assert(tour != NULL);
    
    return tour -> size;
}


double getTourLength(Tour *tour){
    assert(tour != NULL);
    
    TourPosition *startPos = getTourStartPosition(tour);
    TourPosition *cur = startPos;
    TourPosition *next = getNextTourPosition(tour, cur);
    double length = 0.f;
    
    while (next != NULL){
        length += distanceBetweenTowns(getTownAtPosition(tour, cur),
                                       getTownAtPosition(tour, next));
        cur = getNextTourPosition(tour, cur);
        next = getNextTourPosition(tour, next);
    }
    
    length += distanceBetweenTowns(getTownAtPosition(tour, cur),
                                   getTownAtPosition(tour, startPos));
    
    return length;
}



