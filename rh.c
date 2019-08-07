#include <stdlib.h>
#include <GL/glut.h>
#include<math.h>

#define TIMER_INTERVAL 300
#define TID_1 1
#define TID_2 2
#define TID_3 3
#define TID_4 4
#define TID_5 5

/* Vreme proteklo od pocetka simulacije. */
static int time;
/*Debljina putanje*/
static int thickness = 0;
static int animation_ongoing_A=0, animation_ongoing_D=0, animation_ongoing_W=0,animation_ongoing_R=0,animation_ongoing_P = 0;
/*Pomeraji*/
static int xPlus=0, zPlus=0, zMinus=0;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);

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
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //face = GL_FRONT;

    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
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
        //ovde mi fali da vratim na pocetnu poz.
        glutPostRedisplay();
        glutTimerFunc(1000,on_timer,4);
   }

   else if(value == TID_5 && animation_ongoing_P == 1){  
        glutPostRedisplay();
        glutTimerFunc(1000,on_timer,5);
   }


   else
    return;
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
    GLfloat diffuse_coeffs[] = { 0.3, 0.3, 0.8, 1 };
    /* Koeficijenti spekularne refleksije materijala. */
    GLfloat specular_coeffs[] = { 1, 1, 1, 1 };
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
    glPushMatrix();
     glColor3f(1, 0, 0);
     glTranslatef(-10,0,0);
     glTranslatef(0+xPlus,0,0+zPlus-zMinus);
     // rotacija loptice
     glRotatef(-360 * time / (1.2*12*30 * 24), 0, 0, 1);
     glutSolidSphere(1, 16, 16);
    glPopMatrix();

    /* Pravljenje putanje*/
    //+-+-+-+-+-+-+-+--+-++-+-+-+-+-+-+-+-+--++-+-+-+-+-+-+-+-

    /*Osvetljenje i materijali putanje*/
    
    glShadeModel(GL_SMOOTH);    
    GLfloat light_p[] = { -10, 50, 0, 0 };
    GLfloat light_a[] = { 0.2, 0.2, 0.2, 1 };    
    GLfloat light_d[] = { 0.7, 0.9, 0.9, 1 };    
    GLfloat light_s[] = { 0.9, 0.9, 0.9, 1 };    
    GLfloat a_coeffs[] = { 1.0, 0.1, 0.1, 1 };    
    GLfloat d_coeffs[] = { 0.3, 0.3, 0.8, 1 };   
    GLfloat s_coeffs[] = { 0.4, 1, 1, 1 }; 
    GLfloat sh = 1;

    
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
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(35,-1,0);
      glScalef(100,thickness,15);
      glutSolidCube(1);
    glPopMatrix();
    //2
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(110,-1,0);
      glScalef(50,thickness,6);
      glutSolidCube(1);
    glPopMatrix();
    //3
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(135+40,-1,0);
      glScalef(80,thickness,10);
      glutSolidCube(1);
    glPopMatrix();
    //4
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(215+100,-1,0);
      glScalef(200,thickness,15);
      glutSolidCube(1);
    glPopMatrix();
    //5
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(415+100,-1,0);
      glScalef(200,thickness,25);
      glutSolidCube(1);
    glPopMatrix();
    //6
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(615+50,-1,0);
      glScalef(100,thickness,5);
      glutSolidCube(1);
    glPopMatrix();
    //7
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(665 + 100,-1,0);
      glScalef(200,thickness,15);
      glutSolidCube(1);
    glPopMatrix();

    /*Prepreke na putu*/

    /*Osvetljenje i materijali prepreka*/
    
    glShadeModel(GL_SMOOTH);    
    GLfloat light_p1[] = { -10, 50, 20, 0 };
    GLfloat light_a1[] = { 0.7, 0.2, 0.2, 1 };    
    GLfloat light_d1[] = { 0.3, 0.4, 0.9, 1 };    
    GLfloat light_s1[] = { 0.9, 0.9, 0.9, 1 };    
    GLfloat a_coeffs1[] = { 1.0, 0.5, 0.1, 1 };    
    GLfloat d_coeffs1[] = { 0.3, 0.3, 0.8, 1 };   
    GLfloat s_coeffs1[] = { 0.4, 1, 1, 1 }; 
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
      glutSolidDodecahedron();
    glPopMatrix();
    //04
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(78,1.5,3);
      glScalef(5,3,3);
      glutSolidCube(1);
    glPopMatrix();


    //21
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(140,2,3.5);
      glScalef(1.4,1,2);
      glutSolidDodecahedron();
    glPopMatrix();
    //22
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(161,1,-3.4);
      glScalef(7,2,3);
      glutSolidCube(1);
    glPopMatrix();   
    //23
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(195,3.5,-3);
      glRotatef(90,1,0,0);
      glutSolidCone(3,5,16, 16);
    glPopMatrix();
    //24
    glColor3f(0,1,0);
    glPushMatrix();
      glTranslatef(195,3.5,3);
      glRotatef(90,1,0,0);
      glutSolidCone(3,5,16, 16);
    glPopMatrix();
    



    









    //+-+-+-+-+-+-+-+--+-++-+-+-+-+-+-+-+-+--++-+-+-+-+-+-+-+-


    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
