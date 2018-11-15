#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  float Verts[6]; //array to hold the unit triangles vertices
  float Insc[6]; //array to hold the inscribed triangle vertices
  float x,y; //x and y values for the vertex coordinate
  float i; //index variable

  //Vertex A (Ax,Ay)
  Verts[0]=0;
  Verts[1]=0;

  //Vertex B (Bx, By)
  Verts[2]=0;
  Verts[3]=2;
  
  //Vertex C (Cx, Cy)
  Verts[4]=1;
  Verts[5]=0;

  printf("The unit triangle sides are\nA= (%.0f,%.0f)\nB=(%.0f,%.0f)\nC=(%.0f,%.0f)\n",Verts[0],Verts[1],Verts[2],Verts[3],Verts[4],Verts[5]);

  printf("Calculating random sides of inscribed triangle\n");

  Insc[0] = (float)rand()/(float)(RAND_MAX/1);
  Insc[1] = (float)rand()/(float)(RAND_MAX/1);
  Insc[2] = (float)rand()/(float)(RAND_MAX/1);
  Insc[3] = (float)rand()/(float)(RAND_MAX/1);
  Insc[4] = (float)rand()/(float)(RAND_MAX/1);
  Insc[5] = (float)rand()/(float)(RAND_MAX/1);
  printf("The random float is %.4f\n", Insc[0]);
  
  return 0;
}
