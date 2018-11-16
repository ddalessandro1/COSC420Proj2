/* Area.c
 * this function check each angle first, and then determine which side will be the base.
 * and send each side to hight function to get hight and calcute the area
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "height.h"
float Area(float rt, float rs, float ts){

  float cosT, cosR, cosS, area;
  //for angleT two sides are rt, ts, base is rs
  cosT=(powf(rt,2)+powf(ts,2)-powf(rs,2))/(2*(rt*ts));
  
  //for angleR two sides are rt, rs, base is ts
  cosR=(powf(rs,2)+powf(rt,2)-powf(ts,2))/(2*(rs*rt));
  
  //for angleS two sides are rs, ts, base is rt
  cosS=(powf(ts,2)+powf(rs,2)-powf(rt,2))/(2*(rs*ts));
  
  //if the angleT >= 90 degree
  if(cosT<=0){
    
    //base is rs, left side is ts, right side is rt
    area=0.5*rs*height(rs, ts, rt);
    return area;
    
  }
  //if the angleR >= 90 degree
  else if(cosR<=0){
    
    //base is ts, left side is rt, right side is rs
    area=0.5*ts*height(ts, rt, rs);
    return area;
    
  }
  //if the angleS >= 90 degree
  else if(cosS<=0){
    //base is rt, left side is rs, right side is ts
    area=0.5*rt*height(rt, rs, ts);
    return area;
    
  }
  //if all angles are less than 90 degree, just choose any angle
  else{
    //base is rs, left side is ts, right side is rt
    area=0.5*rs*height(rs, ts, rt);
    return area;
    
  }

}
