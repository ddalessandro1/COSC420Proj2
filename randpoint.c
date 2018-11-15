/*David D'Alessandro
  Jiaming Qu
  Ian Schwartz
  randpoint.c v1.0
  COSC420 Proj 2
 */

#include <stdio.h>
#include <stdlib.h>

/*rand point generation
  takes a maximum point "n" as an argument
  returns the random number
*/
float randpoint(float n){
    
    float a;
    //store the rand point(n is the max number between 0 to n
    a =(float)rand()/(float)(RAND_MAX/n);
    //return the rand point
    return a;
  }
