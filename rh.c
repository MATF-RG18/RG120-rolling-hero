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

    time += 50;

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
    gluLookAt(-30+xPlus, 30, 0+zPlus-zMinus, 
              0+xPlus, 0, 0+zPlus-zMinus,
              1, 1, 0);
    

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
     glTranslatef(0+xPlus,0,0+zPlus-zMinus);
     // rotacija loptice
     glRotatef(360 * time / (1.881*12*30 * 24), 0, 0, 1);
     glutWireSphere(1, 16, 16);
    glPopMatrix();
    
    /* Nova slika se salje na ekran. */
    glutSwapBuffers();
}
