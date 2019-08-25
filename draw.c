#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#include "image.h"
#include "boundaries.h"
#include "sumpoints.h"
#include "draw.h"
#include<stdbool.h>
#include<string.h>

void Draw(void){

	/*Program iscrtava prepreke na putu*/

    /*Osvetljenje i materijali prepreka*/
    
    glShadeModel(GL_SMOOTH);    
    GLfloat light_p1[] = { -10, 100, 1000, 0 };
    GLfloat light_a1[] = { 0.7, 0.2, 0.2, 1 };    
    GLfloat light_d1[] = { 0.3, 0.4, 0.9, 1 };    
    GLfloat light_s1[] = { 0.9, 0.9, 0.9, 1 };    
    GLfloat a_coeffs1[] = { 0.7, 0.5, 0.1, 1 };    
    GLfloat d_coeffs1[] = { 0.3, 0.3, 0.8, 1 };   
                            //0.4,1,1,1
    GLfloat s_coeffs1[] = { 0.447059 , 0.264706,0.284706, 1}; 
    GLfloat sh1 = 1;

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_p1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_a1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_d1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_s1);

   
    glMaterialfv(GL_FRONT, GL_AMBIENT, a_coeffs1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d_coeffs1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s_coeffs1);
    glMaterialf(GL_FRONT, GL_SHININESS, sh1);  
    
    //01
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(-10,1.5,-4.5);
      glScalef(5,3,3);
      glutSolidCube(1);
    glPopMatrix();
    //02
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(10,2.15,-1.6);
      glScalef(4.3,4.3,4.3);
      glutSolidCube(1);
    glPopMatrix();   
    //03
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(41,0.9,-3.2);
      glScalef(3,1.8,2.6);
      glutSolidCube(1);
    glPopMatrix();
    //04
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(78,1.5,3);
      glScalef(5,3,3);
      glutSolidCube(1);
    glPopMatrix();

    //31
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(140,2,3.5);
      glScalef(1.4,1,2);
      glutSolidCube(1);
    glPopMatrix();
    //32
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(161,1,-3);
      glScalef(7,2,3);
      glutSolidCube(1);
    glPopMatrix();   
    //33
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(191,-0.5,2.5);
      glScalef(10,3,5);
      glutSolidCube(1);
    glPopMatrix();  

     //34
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(210,1,0);
      glScalef(2,2,2);
      glutSolidCube(1);
    glPopMatrix(); 

    //41
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(250,1,-3);
      glScalef(6,8,3);
      glutSolidCube(1);
    glPopMatrix(); 

    //42
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(300,1,4);
      glScalef(12,17,3.4);
      glutSolidCube(1);
    glPopMatrix();

    //43
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(370,1,-5);
      glScalef(8,4,1);
      glutSolidCube(1);
    glPopMatrix();

    //51
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(418,1,-4);
      glScalef(8,8,8);
      glutSolidCube(1);
    glPopMatrix(); 

    //52
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(440,1,8);
      glScalef(7,2,3);
      glutSolidCube(1);
    glPopMatrix();

    //53
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(495,1,5);
      glScalef(13,4,4);
      glutSolidCube(1);
    glPopMatrix();

    //54
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(536,1,-2);
      glScalef(7,7,7);
      glutSolidCube(1);
    glPopMatrix();

    //55
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(570,1,-2);
      glScalef(8,4,1);
      glutSolidCube(1);
    glPopMatrix();

    //56
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(515,1,6);
      glScalef(8,8,3);
      glutSolidCube(1);
    glPopMatrix();

    //71
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(670,1,-5.5);
      glScalef(10,2,4);
      glutSolidCube(1);
    glPopMatrix(); 
    //72
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(700,1,-3.7);
      glScalef(15,15,4);
      glutSolidCube(1);
    glPopMatrix(); 
    //73
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(742,1,3.7);
      glScalef(15,15,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //74
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(780,1,-4);
      glScalef(5,5,5);
      glutSolidCube(1);
    glPopMatrix(); 
    //75
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(808,1,7);
      glScalef(5,4,1);
      glutSolidCube(1);
    glPopMatrix(); 
    //76
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(833,1,-2);
      glScalef(2,2,2);
      glutSolidCube(1);
    glPopMatrix(); 

    //81
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(866,1,-4);
      glScalef(20,20,10);
      glutSolidCube(1);
    glPopMatrix(); 
    //82
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(920,1,3.7);
      glScalef(15,3,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //83
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(935,1,-3.7);
      glScalef(15,3,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //84
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(950,1,-7);
      glScalef(10,7,7);
      glutSolidCube(1);
    glPopMatrix(); 
    //85
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(999,1,7);
      glScalef(18,6,5);
      glutSolidCube(1);
    glPopMatrix(); 
    //86
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1060,1,-2);
      glScalef(2,2,2);
      glutSolidCube(1);
    glPopMatrix(); 
    //87
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1080,1,-5);
      glScalef(5,8,3);
      glutSolidCube(1);
    glPopMatrix();
  //88
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1100,1,-5);
      glScalef(5,13,5);
      glutSolidCube(1);
    glPopMatrix(); 
    //89
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1148,1,3);
      glScalef(20,7,2);
      glutSolidCube(1);
    glPopMatrix(); 

    //810
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1186,1,2);
      glScalef(6,2,6);
      glutSolidCube(1);
    glPopMatrix();
    //91
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1213,1,2);
      glScalef(7,20,7);
      glutSolidCube(1);
    glPopMatrix(); 
    //92
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1229,1,3.7);
      glScalef(15,3,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //93
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1270,1,-3.7);
      glScalef(15,3,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //94
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1342,1,-7);
      glScalef(10,7,7);
      glutSolidCube(1);
    glPopMatrix(); 
    //95
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1371,1,7);
      glScalef(18,6,5);
      glutSolidCube(1);
    glPopMatrix(); 
    //96
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1400,1,-2);
      glScalef(2,2,2);
      glutSolidCube(1);
    glPopMatrix(); 
    //97
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1433,1,-5);
      glScalef(5,8,3);
      glutSolidCube(1);
    glPopMatrix();
    //98
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1464,1,-5);
      glScalef(5,13,5);
      glutSolidCube(1);
    glPopMatrix(); 
    //99
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1497,1,3);
      glScalef(20,7,1);
      glutSolidCube(1);
    glPopMatrix(); 
    //910
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1515,1,3);
      glScalef(20,7,2);
      glutSolidCube(1);
    glPopMatrix(); 
    //911
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1547,1,3);
      glScalef(20,7,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //912
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1582,1,-3);
      glScalef(20,7,2);
      glutSolidCube(1);
    glPopMatrix(); 
     //913
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1383,1,-3);
      glScalef(6,6,6);
      glutSolidCube(1);
    glPopMatrix(); 

    //10
  
    //2
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1617,1,-1.6);
      glScalef(4.3,4.3,4.3);
      glutSolidCube(1);
    glPopMatrix();   
    //3
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1635,1,-3.2);
      glScalef(3,1.8,2.6);
      glutSolidCube(1);
    glPopMatrix();
    //4
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1670,1,3);
      glScalef(5,3,3);
      glutSolidCube(1);
    glPopMatrix();
    //5
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1698,1,3.5);
      glScalef(1.4,1,2);
      glutSolidCube(1);
    glPopMatrix();
    //6
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1703,1,-3);
      glScalef(7,2,3);
      glutSolidCube(1);
    glPopMatrix();   
    //7
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1730,1,2.5);
      glScalef(10,3,5);
      glutSolidCube(1);
    glPopMatrix();  
     //8
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1760,1,0);
      glScalef(2,2,2);
      glutSolidCube(1);
    glPopMatrix(); 
    //9
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1793,1,-3);
      glScalef(6,8,3);
      glutSolidCube(1);
    glPopMatrix(); 
    //10
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1812,1,4);
      glScalef(12,17,3.4);
      glutSolidCube(1);
    glPopMatrix();
    //11
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1831,1,-5);
      glScalef(8,4,1);
      glutSolidCube(1);
    glPopMatrix();

    //12
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1862,1,-4);
      glScalef(8,8,8);
      glutSolidCube(1);
    glPopMatrix(); 

    //13
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1880,1,8);
      glScalef(7,2,3);
      glutSolidCube(1);
    glPopMatrix();

}