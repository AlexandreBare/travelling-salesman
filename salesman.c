#include "tour.h"
#include "tsp.h"
#include "easyppm.h"
#include <stdio.h>


#define SIZE 1000
#define ARGC 2


void ppmTour(Tour *tour, const char *ppmName, int size);

void ppmTour(Tour *tour, const char *ppmName, int size) {

  ppmcolor black = easyppm_rgb(0,0,0);
  ppmcolor white = easyppm_rgb(255,255,255);
       
  double prevX, prevY;
  double nextX, nextY;

  TourPosition *current = getTourStartPosition(tour);
  Town *currentTown = getTownAtPosition(tour, current);
  double minX = getTownX(currentTown);
  double maxX = minX;
  double minY = getTownY(currentTown);
  double maxY = minY;

  while (current != NULL) {
    double currentX = getTownX(getTownAtPosition(tour, current));
    double currentY = getTownY(getTownAtPosition(tour, current));
    
    if (currentX < minX)
      minX = currentX;
    else if (currentX > maxX)
      maxX = currentX;

    if (currentY < minY)
      minY = currentY;
    else if (currentY > maxY)
      maxY = currentY;
      
    current = getNextTourPosition(tour, current);
       
  }
  
  double xRange = maxX - minX;
  double yRange = maxY - minY;
  
  int sizex, sizey;
  if (xRange > yRange) {
    sizex = size;
    sizey = size*yRange/xRange;
  } else {
    sizex = size*xRange/yRange;
    sizey = size;
  }
  
  PPM ppm = easyppm_create(sizex+10, sizey+10, IMAGETYPE_PPM);
  easyppm_clear(&ppm, white);
  
  printf("minx = %f, maxx = %f, miny = %f, maxy = %f\n",minX,maxX,minY,maxY);
  current = getTourStartPosition(tour);
  while (current) {
    prevX = (getTownX(getTownAtPosition(tour, current)) - minX)*sizex/xRange+5;
    prevY = (getTownY(getTownAtPosition(tour, current)) - minY)*sizey/yRange+5;
	     
    TourPosition *next = getNextTourPosition(tour, current);
    if (next) {
      nextX = (getTownX(getTownAtPosition(tour, next)) - minX)*sizex/xRange+5;
      nextY = (getTownY(getTownAtPosition(tour, next)) - minY)*sizey/yRange+5;
      easyppm_draw_line(&ppm, (int) prevX, (int) prevY, (int) nextX, (int) nextY, black);
    }
        
    current = next;
  }
    
  double startX, startY;
  startX = (getTownX(getTownAtPosition(tour, getTourStartPosition(tour))) - minX) * sizex/xRange+5;;
  startY = (getTownY(getTownAtPosition(tour, getTourStartPosition(tour))) - minY) * sizey/yRange+5;
  easyppm_draw_line(&ppm, (int) nextX, (int) nextY, (int) startX, (int) startY, black);
  
  easyppm_write(&ppm, ppmName);
  easyppm_destroy(&ppm);

}


int main(int argc, char *argv[]){
    if (argc != ARGC) {
        printf("Either an argument is missing or there are more than 2 arguments\n");
        return -1;
    }
    
    char *filename = argv[1];
    Tour *tour = createTourFromFile(filename);
    ppmTour(tour, "tour-default.ppm", SIZE);
    
    Tour *shortestTour1 = heuristic1(tour);
    ppmTour(shortestTour1, "tour-heuristic1.ppm", SIZE);
    printf("Shortest tour length (Heuristic1): %f\n", getTourLength(shortestTour1));
    freeTour(shortestTour1, 1);
    
    Tour *shortestTour2 = heuristic2(tour);
    printf("Shortest tour length (Heuristic2): %f\n", getTourLength(shortestTour2));
    ppmTour(shortestTour2, "tour-heuristic2.ppm", SIZE);
    freeTour(shortestTour2, 1);
    
    freeTour(tour, 1);
   
    return 0;
}
