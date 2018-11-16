/*David D'Alessandro
  Jiaming Qu
  Ian Schwartz
  COSC420 Proj2
  tri.c v1.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "randpoint.h"
#include "side.h"
#include "Area.h"
#include "height.h"

/*main function
  creates the unit triangle
  as of v1.0 used to test the funciton implementation
 */
int main(){
  float V[6]; //array to hold the unit triangles vertices
  float I[6]; //array to hold the inscribed triangle vertices
  float x,y; //x and y values for the vertex coordinate
  float i; //index variable
  float area;//area of the triangle

  //Vertex A (Ax,Ay)
  V[0]=0;
  V[1]=0;

  //Vertex B (Bx, By)
  V[2]=0;
  V[3]=2;
  
  //Vertex C (Cx, Cy)
  V[4]=1;
  V[5]=0;

  printf("The unit triangle sides are\nA= (%.0f,%.0f)\nB=(%.0f,%.0f)\nC=(%.0f,%.0f)\n",V[0],V[1],V[2],V[3],V[4],V[5]);

  printf("Calculating random sides of inscribed triangle\n");
  //rx,ry
  I[0] = 0;
  I[1] = randpoint(2);
  //tx,ty
  I[2] = randpoint(1);
  I[3] = 0;
  //sx,sy
  I[4] = randpoint(1);
  I[5] = -2*(I[4])+2;//y=-2x+2

  printf("The side lengths are\n");
  printf("RT = %f\n",side(I[0],I[1],I[2],I[3]));
  printf("TS = %f\n",side(I[2],I[3],I[4],I[5]));
  printf("RS = %f\n",side(I[0],I[1],I[4],I[5]));
  //Are(rt, rs, ts)
  area=Area(side(I[0],I[1],I[2],I[3]),side(I[0],I[1],I[4],I[5]),side(I[2],I[3],I[4],I[5]));
  
  printf("Area is %f\n",area);
  
  return 0;
}
