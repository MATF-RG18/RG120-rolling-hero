#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>
#include<stdbool.h>
#include<stdbool.h>
#include "sumpoints.h"

/*Program sabira broj sakupljenih dijamanata*/

int SumPoints(float x_curr,float z_curr){
	//1
	if(x_curr == 6 && z_curr == 3)
		return 1;
	if(x_curr == 10 && z_curr == 3)
		return 1;
	if(x_curr == 14 && z_curr == 3)
		return 1;
	//2
	if(x_curr == 95 && z_curr == 2.5)
		return 1;
	if(x_curr == 100 && z_curr == 2.5)
		return 1;
	if(x_curr == 120 && z_curr == -2.5)
		return 1;
	if(x_curr == 125 && z_curr == -2.5)
		return 1;
	//3
	if(x_curr == 150 && z_curr == 0)
		return 1;
	if(x_curr == 155 && z_curr == 0)
		return 1;
	if(x_curr == 198 && z_curr == -4)
		return 1;
	//4
	if(x_curr == 253 && z_curr == -5.6)
		return 1;
	if(x_curr == 258 && z_curr == -5.6)
		return 1;
	if(x_curr == 261 && z_curr == -5.6)
		return 1;
	if(x_curr == 350 && z_curr == 2)
		return 1;
	if(x_curr == 360 && z_curr == 2)
		return 1;
	//5
	if(x_curr == 415 && z_curr == -10)
		return 1;
	if(x_curr == 420 && z_curr == -10)
		return 1;
	if(x_curr == 470 && z_curr == 5.6)
		return 1;
	if(x_curr == 477 && z_curr == 5.6)
		return 1;
	if(x_curr == 560 && z_curr == 0)
		return 1;
	if(x_curr == 570 && z_curr == 0)
		return 1;
	//6
	if(x_curr == 630 && z_curr == 0)
		return 1;
	if(x_curr == 634 && z_curr == 0)
		return 1;
	//7
	if(x_curr == 678 && z_curr == -6)
		return 1;
	if(x_curr == 683 && z_curr == -6)
		return 1;
	if(x_curr == 688 && z_curr == -6)
		return 1;
	if(x_curr == 725 && z_curr == 0)
		return 1;
	if(x_curr == 740 && z_curr == -2.3)
		return 1;
	if(x_curr == 800 && z_curr == 6.8)
		return 1;
	if(x_curr == 805 && z_curr == 6.8)
		return 1;
	//8
	if(x_curr == 869 && z_curr == -4)
		return 1;
	if(x_curr == 874 && z_curr == -4)
		return 1;
	if(x_curr == 900 && z_curr == 5)
		return 1;
	if(x_curr == 900 && z_curr == 0)
		return 1;
	if(x_curr == 950 && z_curr == 0)
		return 1;
	if(x_curr == 955 && z_curr == 0)
		return 1;
	if(x_curr == 960 && z_curr == 0)
		return 1;
	if(x_curr == 980 && z_curr == 5.4)
		return 1;
	if(x_curr == 990 && z_curr == 5.4)
		return 1;
	if(x_curr == 1130 && z_curr == -3)
		return 1;
	if(x_curr == 1134 && z_curr == -3)
		return 1;
	//9
	if(x_curr == 1200 && z_curr == -4)
		return 1;
	if(x_curr == 1205 && z_curr == -4)
		return 1;
	if(x_curr == 1250 && z_curr == 0)
		return 1;
	if(x_curr == 1255 && z_curr == 0)
		return 1;
	if(x_curr == 1260 && z_curr == 0)
		return 1;
	if(x_curr == 1330 && z_curr == -7.5)
		return 1;
	if(x_curr == 1335 && z_curr == -7.5)
		return 1;
	if(x_curr == 1390 && z_curr == 4.3)
		return 1;
	if(x_curr == 1428 && z_curr == 4.6)
		return 1;
	if(x_curr == 1433 && z_curr == 4.6)
		return 1;
	if(x_curr == 1480 && z_curr == -3.5)
		return 1;
	if(x_curr == 1485 && z_curr == -3)
		return 1;
	if(x_curr == 1490 && z_curr == -3)
		return 1;
	if(x_curr == 1520 && z_curr == -3)
		return 1;
	if(x_curr == 1525 && z_curr == -3)
		return 1;
	if(x_curr == 1530 && z_curr == -3)
		return 1;
	if(x_curr == 1570 && z_curr == 4)
		return 1;
	if(x_curr == 1575 && z_curr == 5)
		return 1;
	if(x_curr == 1580 && z_curr == 5)
		return 1;
	if(x_curr == 1585 && z_curr == 5)
		return 1;

	//10
	if(x_curr == 1600 && z_curr == -4)
		return 1;
	if(x_curr == 1605 && z_curr == -4)
		return 1;
	if(x_curr == 1650 && z_curr == 0)
		return 1;
	if(x_curr == 1655 && z_curr == 0)
		return 1;
	if(x_curr == 1660 && z_curr == 0)
		return 1;
	if(x_curr == 1730 && z_curr == -7.5)
		return 1;
	if(x_curr == 1735 && z_curr == -7.5)
		return 1;
	if(x_curr == 1790 && z_curr == 4.3)
		return 1;
	if(x_curr == 1828 && z_curr == 4.6)
		return 1;
	if(x_curr == 1833 && z_curr == 4.6)
		return 1;
	if(x_curr == 1880 && z_curr == -3.5)
		return 1;
	if(x_curr == 1885 && z_curr == -3)
		return 1;
	if(x_curr == 1890 && z_curr == -3)
		return 1;
	if(x_curr == 1920 && z_curr == -3)
		return 1;
	if(x_curr == 1925 && z_curr == -3)
		return 1;
	if(x_curr == 1930 && z_curr == -3)
		return 1;
	if(x_curr == 1970 && z_curr == 4)
		return 1;
	if(x_curr == 1975 && z_curr == 5)
		return 1;
	if(x_curr == 1980 && z_curr == 5)
		return 1;
	if(x_curr == 1985 && z_curr == 5)
		return 1;

	return 0;
}