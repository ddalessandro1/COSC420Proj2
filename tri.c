/* Project1.c
David D'Alessandro
Jiaming Qu
Ian Schwartz
*************************
COSC420
Project 2
Start: 11/5/18
Last Update: 11/18/18
*************************
This program will take input for N triangles, divide those N triangles up 
amongst server nodes and use those as estimation attempts for the area of
a random inscribed triangle in a unit triangle of specified points
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <mpi.h>

#include "randpoint.h"
#include "side.h"
#include "Area.h"
#include "height.h"

/*int *freqtable
  The function will count the frequency of 
  each element and return an array pointer
  
 */
int *freqtable(int* arr, int* frequency, int start, int end)
{
    int i;
    for(i=start;i<end;i++)
    {
        frequency[arr[i]]++;
    }
    return frequency;
}

/*void err
Error function.
When an error is thrown and caught, use this
function to display error message and exit
*/
void err(char *str){
    printf("%s\n", str);
    exit(1);
}

/*int main
Main function that requests input from user and 
dynamically allocates memory for an array of that size
and then fills it with numbers from 0 - M (another user
requested parameter)
*/
int main(int argc, char *argv[]){
       
    int *arr; //pointer variable to array
    
    int numberOfTriangles; //holds number of triangles to calculate
    float errRate; //holds the error rate
    int sizeOfFreq; //holds the size of the frequency table
    
    int *frequency; //pointer variable to frequency array
    int i,j; //counter variables
    
    float V[6]; //array to hold the unit triangles vertices
    float I[6]; //array to hold the inscribed triangle vertices
    float x,y; //x and y values for the vertex coordinate
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
    
    //variables for the division of labor
    int size,rank,even,chunkSize, chunkStart;
    int length;
    char name[80];
    

    //standard MPI stuff
    MPI_Status status;
    MPI_Init(&argc, &argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(name,&length);
    
/////////////////////////////////////////////////////////////////////////////////
//
//
//      MASTER NODE START
//
//
////////////////////////////////////////////////////////////////////////////////    
    if(rank==0)
    {
        even = 0;
	//gets input for numberOfTriangles
        printf("Please enter the amount of triangles:\n");
        scanf("%d", &numberOfTriangles); 

        //get input for max value size
        printf("Please enter the error rate (ie. 0.001):\n");
        scanf("%f", &errRate); //gets input for errRate
        
        //this determines how large the frequency table should be
        i=0;
        while(errRate < .9){
            errRate = errRate * 10;
            i++;
        }
        
        sizeOfFreq = 1;
	int iValue = i;
        while(i > 0){
            sizeOfFreq = sizeOfFreq * 10;
            i--;
        }
        
        sizeOfFreq=sizeOfFreq+1;
        //dynamically allocate memory for the array using malloc() sys call
        //initialize final frequency array
        arr = (int *)malloc(sizeof(int)*sizeOfFreq); 
        frequency = (int *)malloc(sizeof(int)*sizeOfFreq); 
        
    
        clock_t t;
        t = clock();
        
        for(i=0; i<sizeOfFreq; i++)
        {
            arr[i]=0;
            frequency[i]=0;
        }
        int sum = 0;
        
        //if size(# nodes) >sizeOfFreq it will then split up array each by one
	//to do calculations (SPECIAL CASE), otherwise it will do it normally
        if(size > numberOfTriangles)
        {
            //calculate chunkSize
            chunkSize = 1;
        }
        else
        {
            //calculate chunkSize
            chunkSize = numberOfTriangles / (size-1);
        }        
        printf("\n");    
        printf("Size of nodes are: %d\n", size);
        printf("\n");
        //sends info to each node
        for(i=1; i<size; i++)
        {
            
        
            //////////////////////////////////////////////////////////////////////
            //FOR REGULAR ALGORITHM
            //
            //make unit triangle(above tho) and send nodes the unit triangle
	    //coordinates(done, but not actually sent)
            ///////////////////////////////////////////////////////////////////// 
            
            //send size of frequency table
            MPI_Send(&sizeOfFreq,1,MPI_INT,i,999,MPI_COMM_WORLD);
            //send errRate multiplier
            MPI_Send(&errRate,1,MPI_INT,i,999,MPI_COMM_WORLD);
            
            //send chunkSize which tells node i how much of array to look through
            MPI_Send(&chunkSize,1,MPI_INT,i,999,MPI_COMM_WORLD);
            
            //send frequency array
            MPI_Send(frequency,sizeOfFreq, MPI_INT,i,1,MPI_COMM_WORLD);
            
        }  
    
        
        //receives the information from each node, and
	//computes the amount of evens
        for(i=1; i<size; i++)
        {
      
            //recieve frequency array
            MPI_Recv(frequency,sizeOfFreq,MPI_INT,i,1,MPI_COMM_WORLD,&status);
            
            for(j=0;j<sizeOfFreq;j++)
            {
                arr[j]+=frequency[j];
                
        
            }
        
            
            
        }
        
        //if the size of the array is greater or equal to the number of processes,
	//the master will determine the leftovers whether or not they are even
        if(sizeOfFreq >= size)
        {
            int mod = numberOfTriangles % (size-1);
            //sum the frequency array
            for(i=0;i<mod;i++)
            {
                I[0] = 0;
                I[1] = randpoint(2);
                //tx,ty
                I[2] = randpoint(1);
                I[3] = 0;
                //sx,sy
                I[4] = randpoint(1);
                I[5] = -2*(I[4])+2;//y=-2x+2
            
                area=Area(side(I[0],I[1],I[2],I[3]),side(I[0],I[1],I[4],I[5]),side(I[2],I[3],I[4],I[5]));
            
 
                arr[(int)(area * (sizeOfFreq-1))]++;
        
            }
        
        }
        printf("The following areas actual decimal value is the (area # / error rate):\n(Note: area 0 means that the area is smaller than the error rate so it stays at zero)\n");
	
        for(i=1; i<sizeOfFreq; i++)
        {
	  if(arr[i] != 0){
            printf("Area %.*f occurs %d\n",iValue,((float)i)/(float)sizeOfFreq,arr[i]);
	  }
        }
        
        sum = 0;
        for(i=0;i<sizeOfFreq;i++)
        {
            sum += arr[i];
        }
	printf("Error chosen = %.*f\n", iValue, errRate/sizeOfFreq);
        printf("Total Triangles = %d\n",sum);
        //free up memory
        free(arr);
        free(frequency);
        //free(sum1);
    
        t = clock() - t;
        float time_taken = ((float)t)/CLOCKS_PER_SEC;
        printf("Time: %.5fs\n", time_taken);
        
    }
    else
    {
        
/////////////////////////////////////////////////////////////////////////////////
//
//
//      SERVER NODE START
//
//
////////////////////////////////////////////////////////////////////////////////
        even = 0;
        
////////////////////////////////////////////////////        
        //FOR REGULAR ALGORITHM
        //
        //needs to receive unit triangle (not needed for current algorithm)
        //calc random points (done)
        //compute areas (done)
        //send back frequency table (done)
/////////////////////////////////////////////////////        
        
        //receive sizeOfFreq
        MPI_Recv(&sizeOfFreq,1,MPI_INT,0,999,MPI_COMM_WORLD,&status);
        
        //receive errRate multiplier
        MPI_Recv(&errRate,1,MPI_INT,0,999,MPI_COMM_WORLD,&status);
        
        //receive chunkSize from master
        MPI_Recv(&chunkSize,1,MPI_INT,0,999,MPI_COMM_WORLD,&status);
    
            
        
        //make variable to hold , needs to be done
        int *frequency = (int *)malloc(sizeof(int)*sizeOfFreq);
        
        //receive frequency
        MPI_Recv(frequency,sizeOfFreq,MPI_INT,0,1,MPI_COMM_WORLD,&status);
    
        //calculating a certain amount of random numbers and their areas
        for(i = 0; i < chunkSize; i++)
        {
            I[0] = 0;
            I[1] = randpoint(2);
            //tx,ty
            I[2] = randpoint(1);
            I[3] = 0;
            //sx,sy
            I[4] = randpoint(1);
            I[5] = -2*(I[4])+2;//y=-2x+2
            
            while(I[1] == 0 || I[2] == 0 || I[4] == 0 || I[4] == I[2] || I[5] == I[1] || I[5] == 0)
            {
                //I[0] = 0;
                I[1] = randpoint(2);
                //tx,ty
                I[2] = randpoint(1);
                //I[3] = 0;
                //sx,sy
                I[4] = randpoint(1);
                I[5] = -2*(I[4])+2;//y=-2x+2
            
            }
            
            
//////////////////////////////////////////////////////////
//      MONTE CARLO SIMULATION IDEA
//          THIS MIGHT REQUIRE UNIT TRIANGLE TO BE PASSED 
//              AND RECEIVED WHICH IS NOT CURRENTLY HAPPENING
//  -the unit triangle might be global so the nodes might
//      already have the points
//  -this is probably where we would instead calculate random points
//      instead of calculating the sides and area
//      (might be easier to just choose an amount ourselves
//          (like 100,000 points))
//  -then determine what triangle the point is in, unit or inscribed
//  -then check the probability to determine area
//  -increment the correct area (in frequency array)
//  -repeat till it does its amount of triangles and send back to master
//////////////////////////////////////////////////////////

            //calculate the area based on area
            area=Area(side(I[0],I[1],I[2],I[3]),side(I[0],I[1],I[4],I[5]),side(I[2],I[3],I[4],I[5]));
            
            //a is area as an int
            int a = (int)(area * (sizeOfFreq-1));
            if(a >= 0 && a < sizeOfFreq-1)
            {
                frequency[a]++;
            }
            else
            {
                frequency[0]++;
            }
            
        }
        
        MPI_Send(frequency,sizeOfFreq,MPI_INT,0,1,MPI_COMM_WORLD);
       
        free(frequency);
        
    }
    MPI_Finalize();
    return 0;
}
