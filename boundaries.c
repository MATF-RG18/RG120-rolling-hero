#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include<stdbool.h>
#include "boundaries.h"

/*Program proverava pozicije loptice u toku igre*/

bool CheckBoundries(float x_curr,float z_curr){

/*Provera granica putanje*/


	   //1 
	  if(x_curr<85 && (z_curr > 7.5 || z_curr < -7.5))
   		return true;  
   	//2
   	if((x_curr<135 && x_curr>85) && (z_curr > 3 || z_curr < -3))
   		 return true;
   	//3
   	if((x_curr<215 && x_curr>135) && (z_curr > 5 || z_curr < -5))
   		return true;
   	//4
   	if((x_curr<415 && x_curr>215) && (z_curr > 7.5 || z_curr < -7.5))
   		 return true;
   	//5
   	if((x_curr<615 && x_curr>415) && (z_curr > 12.5 || z_curr < -12.5))
   		 return true;
   	//6
   	if((x_curr<665 && x_curr>615) && (z_curr > 2.5 || z_curr < -2.5))
   		 return true;
   	//7
   	if((x_curr<865 && x_curr>665) && (z_curr > 7.5 || z_curr < -7.5))
   		 return true;
   	//8
   	if((x_curr<1200 && x_curr>865) && (z_curr > 6 || z_curr < -6))
   		 return true;
   	//9
   	if((x_curr<1600 && x_curr>1200) && (z_curr > 8 || z_curr < -8))
   		 return true;
   	//10
   	if((x_curr<2000 && x_curr>1600) && (z_curr > 10 || z_curr < -10))
   		 return true;

   	//1 (Na prvoj putanji)
   	 if(x_curr<85 && (z_curr < 7.5 || z_curr > -7.5)){

   	 	if(x_curr<-7.5 && z_curr == -3+0.5 )
   	 		return true;

   	 	if((x_curr<=12.15 && x_curr>=7.85 ) && (z_curr <= -0.55+1  && z_curr >= -3.75-1))
   	 		return true;

   	 	if((x_curr<=41+1.5-1 && x_curr>=41-1.5+1 ) && (z_curr <= -3.2+2.6+0.5 && z_curr >= -3.2-2.6+1))
   	 		return true;

   	 	if((x_curr<=78+2.5+1 && x_curr>=78-2.5-1 ) && (z_curr <= 3+1.5+1 && z_curr >= 3-1.5-1))
   	 		return true;

   	 }

   	 //3

   	 if((x_curr<215 && x_curr>135) && (z_curr < 7.5 || z_curr > -7.5)){

   	 	if((x_curr<=140+0.7+0.5 && x_curr>=140-0.7-0.5 ) && (z_curr <= 3.5+1+0.5 && z_curr >= 3.5-1-0.5))
   	 		return true;

   	 	if((x_curr<=161+3.5-1 && x_curr>=161-3.5+1 ) && (z_curr <= -3+1.5+0.5 && z_curr >= -3-1.5+0.5))
   	 		return true;

   	 	if((x_curr<=191+5+1 && x_curr>=191-5-1 ) && (z_curr <= 2.5+2.5+1 && z_curr >= 2.5-2.5-1))
   	 		return true;

   	 	if((x_curr<=210+1+1 && x_curr>=210-1-1 ) && (z_curr <= 0+1+1 && z_curr >= 0-1-1))
   	 		return true;
   	 }
   	 //4
   	if((x_curr<415 && x_curr>215) && (z_curr < 7.5 || z_curr > -7.5)){

   	 	if((x_curr<=250+3-1 && x_curr>=250-3+1 ) && (z_curr <= -3+1.5+1 && z_curr >= -3-1.5+1))
   	 		return true;

   	 	if((x_curr<=300+6+0.5 && x_curr>=300-6-0.5 ) && (z_curr <= 4+1.7+0.5 && z_curr >= 4-1.7-0.5))
   	 		return true;

   	 	if((x_curr<=370+4-1 && x_curr>=370-4+1 ) && (z_curr <= -5+0.5+1 && z_curr >= -5-0.5+1))
   	 		return true;

   	 }

   	//5
      if((x_curr<615 && x_curr>415) && (z_curr < 12.5 || z_curr > -12.5)){

   		if((x_curr<=418+4-1 && x_curr>=418-4+1 ) && (z_curr <= -4+4+1 && z_curr >= -4-4+1))
   	 		return true;

   	 	if((x_curr<=440+3.5+0.5 && x_curr>=440-3.5-0.5) && (z_curr <= 8+1.5+0.5 && z_curr >= 8-1.5-0.5))
   	 		return true;

   	 	if((x_curr<=495+6.5+0.5 && x_curr>=495-6.5-0.5) && (z_curr <= 5+2+0.5 && z_curr >= 5-2-0.5))
   	 		return true;

   	 	if((x_curr<=536+3.5-1 && x_curr>=536-3.5+1 ) && (z_curr <= -2+3.5+1 && z_curr >= -2-3.5+1))
   	 		return true;

   	 	if((x_curr<=570+4-1 && x_curr>=570-4+1 ) && (z_curr <= -2+0.5+1 && z_curr >= -2-0.5+1))
   	 		return true;

   	 	if((x_curr<=515+4+0.5 && x_curr>=515-4-0.5) && (z_curr <= 6+1.5+0.5 && z_curr >= 6-1.5-0.5))
   	 		return true;
   	}
   	//7
   	if((x_curr<865 && x_curr>665) && (z_curr < 7.5 || z_curr > -7.5)){

   		if((x_curr<=670+5-0.5 && x_curr>=670-5+0.5 ) && (z_curr <= -5.5+2+0.5 && z_curr >= -5.5-2+0.5))
   	 		return true;

   	 	if((x_curr<=700+7.5-1 && x_curr>=700-7.5+1 ) && (z_curr <= -3.7+2+1 && z_curr >= -3.7-2+1))
   	 		return true;

   	 	if((x_curr<=742+7.5+0.5 && x_curr>=742-7.5-0.5) && (z_curr <= 3.7+1.5+0.5 && z_curr >= 3.7-1.5-0.5))
   	 		return true;

   	 	if((x_curr<=780+2.5-1 && x_curr>=780-2.5+1 ) && (z_curr <= -4+2.5+1 && z_curr >= -4-2.5+1))
   	 		return true;

   	 	if((x_curr<=808+2.5+0.5 && x_curr>=808-2.5-0.5) && (z_curr <=7+0.5+0.5 && z_curr >= 7-0.5-0.5))
   	 		return true;

   	 	if((x_curr<=833+1-1 && x_curr>=833-1+1 ) && (z_curr <= -2+1+1 && z_curr >= -2-1+1))
   	 		return true;

   	}
	//8
   	if((x_curr<1200 && x_curr>865) && (z_curr < 6 || z_curr > -6)){

   		if((x_curr<=866+10-0.5 && x_curr>=866-10+0.5 ) && (z_curr <= -4+5+0.5 && z_curr >= -4-5+0.5))
   	 		return true;

   	 	if((x_curr<=920+7.5+0.5 && x_curr>=920-7.5-0.5) && (z_curr <= 3.7+1.5+0.5 && z_curr >= 3.7-1.5-0.5))
   	 		return true;

   	 	if((x_curr<=935+7.5-0.5 && x_curr>=935-7.5+0.5 ) && (z_curr <= -3.7+1.5+0.5 && z_curr >= -3.7-1.5+0.5))
   	 		return true;

   	 	if((x_curr<=950+5-0.5 && x_curr>=950-5+0.5 ) && (z_curr <= -7+3.5+0.5 && z_curr >= -7-3.5+0.5))
   	 		return true;

   	 	if((x_curr<=999+9+0.5 && x_curr>=999-9-0.5) && (z_curr <= 7+2.5+0.5 && z_curr >= 7-2.5-0.5))
   	 		return true;

   	 	if((x_curr<=1060+1-0.5 && x_curr>=1060-1+0.5 ) && (z_curr <= -2+1+0.5 && z_curr >= -2-1+0.5))
   	 		return true;

   	 	if((x_curr<=1080+2.5-0.5 && x_curr>=1080-2.5+0.5 ) && (z_curr <= -5+1.5+0.5 && z_curr >= -5-1.5+0.5))
   	 		return true;

   	 	if((x_curr<=1100+2.5-0.5 && x_curr>=1100-2.5+0.5 ) && (z_curr <= -5+2.5+0.5 && z_curr >= -5-2.5+0.5))
   	 		return true;

   	 	if((x_curr<=1148+10+0.5 && x_curr>=1148-10-0.5) && (z_curr <= 3+1+0.5 && z_curr >= 3-1-0.5))
   	 		return true;
   	}
      //9
      if((x_curr<1600 && x_curr>1200) && (z_curr < 8 || z_curr > -8)){

         if((x_curr<=1213+3.5+0.5 && x_curr>=1213-3.5-0.5) && (z_curr <= 2+3.5+0.5 && z_curr >= 2.7-3.5-0.5))
            return true;

         if((x_curr<=1229+7.5+0.5 && x_curr>=1229-7.5-0.5) && (z_curr <= 3.7+1.5+0.5 && z_curr >= 3.7-1.5-0.5))
            return true;

         if((x_curr<=1270+7.5-0.5 && x_curr>=1270-7.5+0.5 ) && (z_curr <= -3.7+1.5+0.5 && z_curr >= -3.7-1.5+0.5))
            return true;

         if((x_curr<=1342+5-0.5 && x_curr>=1342-5+0.5 ) && (z_curr <= -7+3.5+0.5 && z_curr >= -7-3.5+0.5))
            return true;

         if((x_curr<=1371+9+0.5 && x_curr>=1371-9-0.5) && (z_curr <= 7+2.5+0.5 && z_curr >= 7-2.5-0.5))
            return true;

         if((x_curr<=1400+1-0.5 && x_curr>=1400-1+0.5 ) && (z_curr <= -2+1+0.5 && z_curr >= -2-1+0.5))
            return true;

         if((x_curr<=1433+2.5-0.5 && x_curr>=1433-2.5+0.5 ) && (z_curr <= -5+1.5+0.5 && z_curr >= -5-1.5+0.5))
            return true;

         if((x_curr<=1464+2.5-0.5 && x_curr>=1464-2.5+0.5 ) && (z_curr <= -5+2.5+0.5 && z_curr >= -5-2.5+0.5))
            return true;

         if((x_curr<=1497+10+0.5 && x_curr>=1497-10-0.5) && (z_curr <= 3+0.5+0.5 && z_curr >= 3-0.5-0.5))
            return true;

         if((x_curr<=1515+10+0.5 && x_curr>=1515-10-0.5) && (z_curr <= 3+1+0.5 && z_curr >= 3-1-0.5))
            return true;

         if((x_curr<=1547+10+0.5 && x_curr>=1547-10-0.5) && (z_curr <= 3+1.5+0.5 && z_curr >= 3-1.5-0.5))
            return true;

         if((x_curr<=1582+10-0.5 && x_curr>=1582-10+0.5 ) && (z_curr <= -3+1+0.5 && z_curr >= -3-1+0.5))
            return true;

         if((x_curr<=1383+3-0.5 && x_curr>=1383-3+0.5 ) && (z_curr <= -3+3+0.5 && z_curr >= -3-3+0.5))
            return true;
      }
      //10
         if((x_curr<2000 && x_curr>1600) && (z_curr < 10 || z_curr > -10)){

         if((x_curr<=1617+2.15-0.5 && x_curr>=1617-2.15+0.5) && (z_curr <= -1.6+2.15+1 && z_curr >= -1.6-2.15-1))
            return true;

         if((x_curr<=1635+1.5-0.5 && x_curr>=1635-1.5+0.5 ) && (z_curr <= -3.2+1.3+1 && z_curr >= -3.2-1.3+1))
            return true;

         if((x_curr<=1670+2.5+0.5 && x_curr>=1670-2.5-0.5 ) && (z_curr <= 3+1.5+1 && z_curr >= 3-1.5-1))
            return true;

         if((x_curr<=1698+0.7+0.5 && x_curr>=1698-0.7-0.5 ) && (z_curr <= 3.5+1+0.5 && z_curr >= 3.5-1-0.5))
            return true;

         if((x_curr<=1703+3.5-1 && x_curr>=1703-3.5+1 ) && (z_curr <= -3+1.5+0.5 && z_curr >= -3-1.5+0.5))
            return true;

         if((x_curr<=1730+5+1 && x_curr>=1730-5-1 ) && (z_curr <= 2.5+2.5+1 && z_curr >= 2.5-2.5-1))
            return true;

         if((x_curr<=1760+1+1 && x_curr>=1760-1-1 ) && (z_curr <= 0+1+1 && z_curr >= 0-1-1))
            return true;

         if((x_curr<=1793+3-1 && x_curr>=1793-3+1 ) && (z_curr <= -3+1.5+1 && z_curr >= -3-1.5+1))
            return true;

         if((x_curr<=1812+6+0.5 && x_curr>=1812-6-0.5 ) && (z_curr <= 4+1.7+0.5 && z_curr >= 4-1.7-0.5))
            return true;

         if((x_curr<=1831+4-1 && x_curr>=1831-4+1 ) && (z_curr <= -5+0.5+1 && z_curr >= -5-0.5+1))
            return true;

         if((x_curr<=1862+4-1 && x_curr>=1862-4+1 ) && (z_curr <= -4+4+1 && z_curr >= -4-4+1))
            return true;

         if((x_curr<=1880+3.5+0.5 && x_curr>=1880-3.5-0.5) && (z_curr <= 8+1.5+0.5 && z_curr >= 8-1.5-0.5))
            return true;

         }


         return false;

}
