/*
 * Jiaming QU
 * height.c
 * This function will find the height of a function
 * 
 */
#include <stdio.h>
#include <math.h>
// P is base, Q is left side, V is right side
float height(float P, float Q, float V){
  
 float x,h;
 
 x=(powf(Q,2)-powf(V,2)+powf(P,2))/(2.0*P);
 //calcuate height
 h=sqrtf(powf(Q,2)-powf(x,2));
 
 return h;
  
}