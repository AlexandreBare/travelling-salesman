#include "tsp.h"
#include "tour.h"
#include "town.h"
#include <assert.h>
#include <stdio.h>
#include <float.h>


Tour *heuristic1(Tour *tour){
    assert(tour != NULL && getTourSize(tour) > 0);

    TourPosition *tourPos = getTourStartPosition(tour);
    Town *tourTown = getTownAtPosition(tour, tourPos);
    
    Tour *t = createEmptyTour();
    
    addTownAtTourEnd(t, createTown(getTownName(tourTown),
                                   getTownX(tourTown),
                                   getTownY(tourTown)));
    
    tourPos = getNextTourPosition(tour, tourPos);
    while (tourPos) {
        tourTown = getTownAtPosition(tour, tourPos);
        
        TourPosition *tPos = getTourStartPosition(t);
        Town *tTown;
        double minDistance = DBL_MAX;
        TourPosition *closestPos;
        
        while (tPos) {
            tTown = getTownAtPosition(t, tPos);
            double distance = distanceBetweenTowns(tourTown, tTown);
            if (distance < minDistance) {
                minDistance = distance;
                closestPos = tPos;
            }
            tPos = getNextTourPosition(t, tPos);
        }
        
        addTownAfterTourPosition(t, closestPos, createTown(getTownName(tourTown),
                                                           getTownX(tourTown),
                                                           getTownY(tourTown)));
    
        tourPos = getNextTourPosition(tour, tourPos);
    }
    
    return t;
}


Tour *heuristic2(Tour *tour) {
    assert(tour != NULL && getTourSize(tour) > 0);
    
    TourPosition *tourPos = getTourStartPosition(tour);
    Town *tourTown = getTownAtPosition(tour, tourPos);
    
    Tour *t = createEmptyTour();
    Town *startTown = createTown(getTownName(tourTown),
                                 getTownX(tourTown),
                                 getTownY(tourTown));
    addTownAtTourEnd(t, startTown);
    
    tourPos = getNextTourPosition(tour, tourPos);
    while (tourPos) {
        tourTown = getTownAtPosition(tour, tourPos);
        
        TourPosition *tPos = getTourStartPosition(t);
        Town *tTown;
        TourPosition *tNextPos;
        Town *tNextTown;
        double tMinLengthIncrease = DBL_MAX;
        TourPosition *closestPos;
        
        while (tPos) {
            tTown = getTownAtPosition(t, tPos);
            tNextPos = getNextTourPosition(t, tPos);
            double tLengthIncrease;
            
            if (tNextPos != NULL) {
                tNextTown = getTownAtPosition(t, tNextPos);
                tLengthIncrease = distanceBetweenTowns(tourTown, tTown)
                                  + distanceBetweenTowns(tourTown, tNextTown)
                                  - distanceBetweenTowns(tTown, tNextTown);
            } else
                tLengthIncrease = distanceBetweenTowns(tourTown, tTown)
                                  + distanceBetweenTowns(tourTown, startTown)
                                  - distanceBetweenTowns(tTown, startTown);
            
            if (tLengthIncrease < tMinLengthIncrease) {
                tMinLengthIncrease = tLengthIncrease;
                closestPos = tPos;
            }
            
            tPos = tNextPos;
        }
        
        addTownAfterTourPosition(t, closestPos, createTown(getTownName(tourTown),
                                                           getTownX(tourTown),
                                                           getTownY(tourTown)));
        
        tourPos = getNextTourPosition(tour, tourPos);
    }
    
    return t;
}
