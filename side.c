/* David D'Alessandr
   Jiaming Qu
   Ian Schwartz
   COSC420 Proj2
   side.c v1.0
*/
#include <stdio.h>
#include <math.h>

/* This function finds the distance between two
   points.
   takes two sets of vertex coords as arguments
   returns one distance
*/
float side(float x1, float y1, float x2, float y2){

  float length; //variable to hold the final length
  float xdiff = powf((x2-x1),2); //calculates the squared difference between x's
  float ydiff = powf((y2-y1),2); //calculates the squared differences between y's
  length = sqrtf(xdiff+ydiff); //actual length calculations 
  return length; //return the calculated length
}
