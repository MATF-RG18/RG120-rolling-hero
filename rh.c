#include<stdio.h>
#include<stdlib.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <GL/glut.h>
#include<math.h>
#include "image.h"
#include "boundaries.h"
#include "sumpoints.h"
#include<stdbool.h>

#define TIMER_INTERVAL 300
#define TID_1 1
#define TID_2 2
#define TID_3 3
#define TID_4 4
#define TID_5 5

/* Imena fajlova sa teksturama. */
#define FILENAME0 "wood.bmp"
#define FILENAME1 "lights.bmp"
#define FILENAME2 "grass.bmp"
#define FILENAME3 "sand.bmp"
#define FILENAME4 "sea.bmp"
#define FILENAME5 "sky1.bmp"
/* Identifikatori tekstura. */
static GLuint names[6];

/* Vreme proteklo od pocetka simulacije. */
static int time=0;
/*Broj poena osvojen u toku igre*/
static int points = 0;
/*Debljina putanje*/
static int thickness = 100;
static int animation_ongoing_A=0, animation_ongoing_D=0, animation_ongoing_W=0,animation_ongoing_R=0,animation_ongoing_P = 0;
/*Pomeraji*/
static int xPlus=0, zPlus=0, zMinus=0;
/* Parametar animacije */
//static float animationParameter = -1.0;
/*Trenutne koord. centra loptice*/
static float x_curr = -10, z_curr = 0; 

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);
static void initialize(void);
//static void CheckBoundries(float x_curr,float z_curr);

//--------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    /* Kreira se prozor. */
    glutInitWindowSize(1100, 800);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Rolling Hero");

    /* Registruju se callback funkcije. */
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    //glutTimerFunc(TIMER_INTERVAL, on_timer, 0);

    /* Obavlja se OpenGL inicijalizacija. */  
   //glClearColor(  0.184314, 0.184314, 0.309804,0);
    glClearColor(  0.134314, 0.124314, 0.209804,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //face = GL_FRONT;
    initialize();
    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}
static void initialize(void)
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla.
    Sve vezano za teksture uzeto je iz kodova sa casa */

    Image * image;


    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    image = image_init(0, 0);

    image_read(image, FILENAME0);

    /* Generisu se identifikatori tekstura. */
    glGenTextures(6, names);

    glBindTexture(GL_TEXTURE_2D, 0);


    /* Kreira se prva tekstura. */
    glBindTexture(GL_TEXTURE_2D, names[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T,GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Tekstura Zgrada */
    image_read(image, FILENAME1);
    glBindTexture(GL_TEXTURE_2D, names[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /* Trava. */
    image_read(image, FILENAME2);
    glBindTexture(GL_TEXTURE_2D, names[2]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /*Kreira se tekstura peska*/
    image_read(image, FILENAME3);   
    glBindTexture(GL_TEXTURE_2D, names[3]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /*Kreira se tekstura mora*/
    image_read(image, FILENAME4);
    glBindTexture(GL_TEXTURE_2D, names[4]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    /*Nebo*/
    image_read(image, FILENAME5);
    glBindTexture(GL_TEXTURE_2D, names[5]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S,  GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);


    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);

}

//----------------------------------------------------------------------------------------------
static void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 27:
         /* Zavrsava se program. */
            exit(0); break;

        /* Kretanje unapred (tj. fiksiranje pravca)*/
        case 'w':{
         animation_ongoing_W=1;
         animation_ongoing_D=0;
         animation_ongoing_A=0;
         glutTimerFunc(TIMER_INTERVAL,on_timer,1);
            break;
        }
        /* Kretanje udesno (loptica se sve vreme krece unapred!)*/
        case 'd':{
         animation_ongoing_W=1;
         animation_ongoing_D=1;
         animation_ongoing_A=0;
         glutTimerFunc(TIMER_INTERVAL,on_timer,2);
            break;
        }
        /* Kretanje ulevo*/
        case 'a':{
         animation_ongoing_W=1;
         animation_ongoing_D=0;
         animation_ongoing_A=1;
         glutTimerFunc(TIMER_INTERVAL,on_timer,3);
            break;
        }
        
        /*Vracanje loptice na pocetnu poziciju (reset)*/
        case 'r':{
        animation_ongoing_W=0;
        animation_ongoing_D=0;
        animation_ongoing_A=0;
        xPlus=0, zPlus=0, zMinus=0;
        time = 0;
        points = 0;
        glutPostRedisplay();
        glutTimerFunc(TIMER_INTERVAL,on_timer,4);
            break;
        }
        /*(pause)*/
        case 'p':{
         animation_ongoing_W=0;
         animation_ongoing_D=0;
         animation_ongoing_A=0;
         glutTimerFunc(TIMER_INTERVAL,on_timer,5);
            break;
        }
        
    }
}

//------------------------------------------------------------------------------------------

static void on_timer(int value)
{

    time += 200;
    //animationParameter += 0.01;

   if(value == TID_1 && animation_ongoing_W == 1){
        xPlus += 1;
        glutPostRedisplay();
        glutTimerFunc(100,on_timer,1);
   }
   else if(value == TID_2 && animation_ongoing_D == 1 && animation_ongoing_W == 1){
        xPlus += 1;
        zPlus += 1;
        glutPostRedisplay();
        glutTimerFunc(100,on_timer,2);
   }

   else if(value == TID_3 && animation_ongoing_A == 1 && animation_ongoing_W == 1){
        xPlus += 1;
        zMinus += 1;
        glutPostRedisplay();
        glutTimerFunc(100,on_timer,3);
   }
    else if(value == TID_4 && animation_ongoing_R == 1){
        glutPostRedisplay();
        glutTimerFunc(1000,on_timer,4);
   }

   else if(value == TID_5 && animation_ongoing_P == 1){  
        glutPostRedisplay();
        glutTimerFunc(1000,on_timer,5);
   }

   else
    return;
  
   
   x_curr = xPlus - 10;
   z_curr = zPlus-zMinus;

   if(CheckBoundries(x_curr,z_curr) == true){
    /* Kreira se novi prozor u slucaju izgubljene igre */
    animation_ongoing_W=0;
    animation_ongoing_D=0;
    animation_ongoing_A=0;
    glutInitWindowSize(250, 20);
    glutInitWindowPosition(560, 560);
    glutCreateWindow("Game over! :(");
   }

   points += SumPoints(x_curr,z_curr);

   if(x_curr>=2000){
    animation_ongoing_W=0;
    animation_ongoing_D=0;
    animation_ongoing_A=0;

    /* Kreira se novi prozor u slucaju pobede */
    

    glutInitWindowSize(250, 20);
    glutInitWindowPosition(560, 560);
    printf("%d\n", points);
    glutCreateWindow("You Won!!! :)");
   }
    
  
}
//--------------------------------------------------------------------------------
static void on_reshape(int width, int height)
{
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);
    /* Podesava se projekcija. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);
}
//---------------------------------------------------------------------------------
static void on_display(void)
{

    /* Brise se prethodni sadrzaj prozora. */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     /* Pratimo kretanje loptice */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*gluLookAt(-10+xPlus, 30, 0+zPlus-zMinus, 
              0+xPlus, 0, 0+zPlus-zMinus,
              1, 1, 0);*/
    gluLookAt(-30+xPlus, 10, 0+zPlus-zMinus, 
              0+xPlus, 0, 0+zPlus-zMinus,
              1, 0.5, 0);

    /*Osvetljenje i materijali lopte*/
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    glShadeModel(GL_SMOOTH);
    /* Pozicija svetla (u pitanju je direkcionalno svetlo). */
    GLfloat light_position[] = { -0.3, 2, 1, 0 };
    /* Ambijentalna boja svetla. */
    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1 };
    /* Difuzna boja svetla. */
    GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1 };
    /* Spekularna boja svetla. */
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1 };
    /* Koeficijenti ambijentalne refleksije materijala. */
    GLfloat ambient_coeffs[] = { 1.0, 0.1, 0.1, 1 };
    /* Koeficijenti difuzne refleksije materijala. */
   // GLfloat diffuse_coeffs[] = { 0.3, 0.3, 0.8, 1 };
    GLfloat diffuse_coeffs[] = { 0.647059 , 0.164706,0.164706,1};
    /* Koeficijenti spekularne refleksije materijala. */
    //GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
    GLfloat specular_coeffs[] = { 0.647059 , 0.164706,0.164706, 1 };
    /* Koeficijent glatkosti materijala. */
    GLfloat shininess = 10;

    /* Ukljucuje se osvjetljenje i podesavaju parametri svetla. */
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    /* Podesavaju se parametri materijala. */
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);  
    //+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    

    /* iscrtavanje koordinatnog sistema */
    glBegin(GL_LINES);
        // x osa (plava)
        glColor3f(0, 0, 1);
        glVertex3f(-1000, 0, 0);
        glVertex3f(1000, 0, 0);
        // y osa (zelena)
        glColor3f(0, 1, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1000, 0);
        // z osa (crvena)
        glColor3f(1, 0, 0);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
    glEnd();

    /* Pravimo lopticu */
    //glBindTexture(GL_TEXTURE_2D, names[0]);  
    glPushMatrix();
     glColor3f(1, 0, 0);
     glTranslatef(-10,0,0);
     glTranslatef(0+xPlus,0,0+zPlus-zMinus);
     // rotacija loptice
     glRotatef(-360 * time / (1.2*12*30 * 24), 0, 0, 1);
     glutSolidSphere(1, 16, 16);
    glPopMatrix();
   // glBindTexture(GL_TEXTURE_2D, 0);  

    /* Pravljenje putanje*/
    //+-+-+-+-+-+-+-+--+-++-+-+-+-+-+-+-+-+--++-+-+-+-+-+-+-+-

    /*Osvetljenje i materijali putanje*/
    
    glShadeModel(GL_SMOOTH);    
    GLfloat light_p[] = { 100, 1000, 1000, 0 };
    GLfloat light_a[] = { 0.2, 0.2, 0.2, 1 };    
    GLfloat light_d[] = { 0.7, 0.9, 0.9, 1 };    
    GLfloat light_s[] = { 0.9, 0.9, 0.9, 1 };    
    //GLfloat a_coeffs[] = { 0.858824,  0.439216 , 0.576471, 1 };    
    //GLfloat d_coeffs[] = { 0.858824 , 0.439216 , 0.576471, 1 }; 
    GLfloat a_coeffs[] = { 0.647059 , 0.164706,0.164706,1 };    
    GLfloat d_coeffs[] = { 0.647059 , 0.164706,0.164706,1 };   
    GLfloat s_coeffs[] = { 0.4, 1, 1, 1 }; 
    GLfloat sh = 0.5;

    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_p);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_a);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_d);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_s);

   
    glMaterialfv(GL_FRONT, GL_AMBIENT, a_coeffs);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d_coeffs);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s_coeffs);
    glMaterialf(GL_FRONT, GL_SHININESS, sh);
    
    /*Kao putanju loptice koristicemo skaliranu kocku*/
    //1
    /*Postavljamo strukturu na putanju (stenu)*/
    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(-15,-1, -7.5);

        glTexCoord2f(10, 0);
        glVertex3f(-15,-1, 7.5);

        glTexCoord2f(10, 10);
        glVertex3f(85, -1, 7.5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(85, -1, -7.5);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(35,-51.001,0);
      glScalef(100,thickness,15);
      glutSolidCube(1);
    glPopMatrix();

   
    
    //2

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(85,-1,-3);

        glTexCoord2f(10, 0);
        glVertex3f(85,-1, 3);

        glTexCoord2f(10, 10);
        glVertex3f(135, -1,3);      

        glTexCoord2f(0, 10);                  
        glVertex3f(135, -1, -3);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0); 


    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(110,-51.001,0);
      glScalef(50,thickness,6);
      glutSolidCube(1);
    glPopMatrix();
    //3

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(135,-1,-5);

        glTexCoord2f(10, 0);
        glVertex3f(135,-1,5);

        glTexCoord2f(10, 10);
        glVertex3f(215, -1,5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(215, -1,-5);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0); 

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(135+40,-51.001,0);
      glScalef(80,thickness,10);
      glutSolidCube(1);
    glPopMatrix();
    //4
    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(215,-1,-7.5);

        glTexCoord2f(10, 0);
        glVertex3f(215,-1,7.5);

        glTexCoord2f(10, 10);
        glVertex3f(415,-1,7.5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(415,-1,-7.5);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0); 

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(215+100,-51.001,0);
      glScalef(200,thickness,15);
      glutSolidCube(1);
    glPopMatrix();
    //5

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(415,-1,-12.5);

        glTexCoord2f(10, 0);
        glVertex3f(415,-1,12.5);

        glTexCoord2f(10, 10);
        glVertex3f(615,-1,12.5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(615,-1,-12.5);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0); 

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(415+100,-51.001,0);
      glScalef(200,thickness,25);
      glutSolidCube(1);
    glPopMatrix();
    //6
      glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(615,-1,-2.5);

        glTexCoord2f(10, 0);
        glVertex3f(615,-1,2.5);

        glTexCoord2f(10, 10);
        glVertex3f(665,-1,2.5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(665,-1,-2.5);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(615+50,-51.001,0);
      glScalef(100,thickness,5);
      glutSolidCube(1);
    glPopMatrix();
    //7
      glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(665,-1,-7.5);

        glTexCoord2f(10, 0);
        glVertex3f(665,-1,7.5);

        glTexCoord2f(10, 10);
        glVertex3f(865,-1,7.5);      

        glTexCoord2f(0, 10);                  
        glVertex3f(865,-1,-7.5);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(665 + 100,-51.001,0);
      glScalef(200,thickness,15);
      glutSolidCube(1);
    glPopMatrix();

    //8

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(865,-1,-6);

        glTexCoord2f(10, 0);
        glVertex3f(865,-1,6);

        glTexCoord2f(10, 10);
        glVertex3f(1200,-1,6);      

        glTexCoord2f(0, 10);                  
        glVertex3f(1200,-1,-6);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(865 + 167.5,-51.001,0);
      glScalef(335,thickness,12);
      glutSolidCube(1);
    glPopMatrix();

  //9

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(1200,-1,-8);

        glTexCoord2f(10, 0);
        glVertex3f(1200,-1,8);

        glTexCoord2f(10, 10);
        glVertex3f(1600,-1,8);      

        glTexCoord2f(0, 10);                  
        glVertex3f(1600,-1,-8);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1200 + 200,-51.001,0);
      glScalef(400,thickness,16);
      glutSolidCube(1);
    glPopMatrix();

  //10

    glBindTexture(GL_TEXTURE_2D, names[0]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(1600,-1,-10);

        glTexCoord2f(10, 0);
        glVertex3f(1600,-1,10);

        glTexCoord2f(10, 10);
        glVertex3f(2000,-1,10);      

        glTexCoord2f(0, 10);                  
        glVertex3f(2000,-1,-10);
      glEnd();
    glBindTexture(GL_TEXTURE_2D,0);

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1600 + 200,-51.001,0);
      glScalef(400,thickness,20);
      glutSolidCube(1);
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(2000+7.2,-0.99,0);
      glRotatef(90,1,0,0);
      glutSolidCone(15,100,16,16);
    glPopMatrix();

    /*Prepreke na putu*/

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

    //+-+-+-+-+-+-+-+--+-++-+-+-+-+-+-+-+-+--++-+-+-+-+-+-+-+-

    /*DIJAMANTI*/

    glShadeModel(GL_SMOOTH);       
    GLfloat a_coeffs2[] = {  0.196078 , 0.196078 , 0.8, 1 };    
    GLfloat d_coeffs2[] = { 0.196078 ,0.196078 , 0.8, 1 };   
    GLfloat s_coeffs2[] = { 0.74902 , 0.847059 , 0.847059, 1}; 
    GLfloat sh2 = 1;
 
    glMaterialfv(GL_FRONT, GL_AMBIENT, a_coeffs2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d_coeffs2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s_coeffs2);
    glMaterialf(GL_FRONT, GL_SHININESS, sh2);  
  
    //1
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(6,1,3);
      glScalef(0.6,0.6,0.6);
      // Dijamanti se rotiraju 
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(10,1,3);
      glScalef(0.6,0.6,0.6); 
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(14,1,3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //2

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(95,1,2.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(100,1,2.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(120,1,-2.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(125,1,-2.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //3

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(150,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

        glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(155,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(198,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //4

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(253,1,-5.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(258,1,-5.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(261,1,-5.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();


    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(350,1,2);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(360,1,2);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //5
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(415,1,-10);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(420,1,-10);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(470,1,5.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(477,1,5.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(560,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(570,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //6
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(630,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(634,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //7
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(678,1,-6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(683,1,-6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(688,1,6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(725,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(740,1,-2.3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(800,1,6.8);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(805,1,6.8);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //8
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(869,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(874,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(900,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(900,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(950,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(955,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(960,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(980,1,5.4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(990,1,5.4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();


    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1130,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1134,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //9
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1200,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1205,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

        glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1250,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1255,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1260,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1330,1,-7.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1335,1,-7.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1390,1,4.3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1428,1,4.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1433,1,4.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1480,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();


    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1485,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1490,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1520,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1525,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1530,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1570,1,4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1575,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1580,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1585,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //10
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1600,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1605,1,-4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1650,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1655,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1660,1,0);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1730,1,-7.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1735,1,-7.5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1790,1,4.3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1828,1,4.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1433,1,4.6);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1880,1,5.-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();


    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1885,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1890,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1920,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1925,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1930,1,-3);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1970,1,4);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1975,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1980,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

     glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(1985,1,5);
      glScalef(0.6,0.6,0.6);
      glRotatef(360 * time / (1.2*12*30 * 24), 0, 1, 0);
      glutSolidOctahedron();
    glPopMatrix();

    //+-+-+-+-+-+-+-+--+-++-+-+-+-+-+-+-+-+--++-+-+-+-+-+-+-+-

    /*Okolina*/

    /*Zgradice*/

    //desna
    glBindTexture(GL_TEXTURE_2D, names[1]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,0,1); 

        glTexCoord2f(0,0);
        glVertex3f(0,100, 35);

        glTexCoord2f(1, 0);
        glVertex3f(1000,100, 35);

        glTexCoord2f(1, 1);
        glVertex3f(1000, -100, 35);      

        glTexCoord2f(0, 1);                  
        glVertex3f(0, -100, 35);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
  
    //leva
      glBindTexture(GL_TEXTURE_2D, names[1]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,0,-1); 

        glTexCoord2f(0,0);
        glVertex3f(0,-100, -35);

        glTexCoord2f(1, 0);
        glVertex3f(1000,-100, -35);

        glTexCoord2f(1, 1);
        glVertex3f(1000, 100, -35);      

        glTexCoord2f(0, 1);                  
        glVertex3f(0, 100, -35);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    /*trava*/
    glBindTexture(GL_TEXTURE_2D, names[2]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(-1000,-100, 1000);

        glTexCoord2f(10, 0);
        glVertex3f(-1000,-100, 1000);

        glTexCoord2f(10, 10);
        glVertex3f(1000, -100,1000);      

        glTexCoord2f(0, 10);                  
        glVertex3f(1000, -100, -1000);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

  /*pesak*/
    glBindTexture(GL_TEXTURE_2D, names[3]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(1000,-100,-1000);

        glTexCoord2f(10, 0);
        glVertex3f(1000,-100, 1000);

        glTexCoord2f(10, 10);
        glVertex3f(1500, -100,1500);      

        glTexCoord2f(0, 10);                  
        glVertex3f(1500, -100,-1500);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

  /*more*/
    glBindTexture(GL_TEXTURE_2D, names[4]);     
      glBegin(GL_POLYGON);
        glNormal3f(0,1,0); 

        glTexCoord2f(0,0);
        glVertex3f(1500,-100,-1500);

        glTexCoord2f(10, 0);
        glVertex3f(1500,-100,1500);

        glTexCoord2f(10, 10);
        glVertex3f(3000, -100,3000);      

        glTexCoord2f(0, 10);                  
        glVertex3f(3000, -100,-3000);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    /*nebo*/
    glBindTexture(GL_TEXTURE_2D, names[5]);     
      glBegin(GL_POLYGON);
        glNormal3f(-1,0,0); 

        glTexCoord2f(0,0);
        glVertex3f(2500,-100, -3000);

        glTexCoord2f(1, 0);
        glVertex3f(2500,-100, 3000);

        glTexCoord2f(1, 1);
        glVertex3f(2500, 1000, 3000);      

        glTexCoord2f(0, 1);                  
        glVertex3f(2500, 1000, -3000);
     glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);


    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
