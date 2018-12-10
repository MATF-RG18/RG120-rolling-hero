#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_timer(int value);

static int hours;
static int timer_active;
static double r_Sun=50;
static double r_Earth=6.4;
static double r_Moon=2;
static double r_Mercury=5;
static double r_Venus=12;
static double r_Mars=6.7;
static double r_Jupiter=13;
static double r_Saturn=11;
static double r_Uranus=9.2;
static double r_Neptune=9.12;


int main(int argc, char *argv[])
{
	
	//inicijalizacija	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	//pravljenje prozora
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Walking on sunshine");

	//postavljanje boja za ciscenje
	glClearColor(0, 0, 0, 0);

	//pozivanje funkcija
	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_keyboard);

	 glutTimerFunc(50, on_timer, 0);

	//ulaz u glavnu petlju
	glutMainLoop();

	return 0;
}


static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
	}

}

static void on_reshape(int width, int height){

	//postavljanje projekcije
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)width/height, 1, 1500);
}

static void on_timer(int value)
{
    /* Proverava se da li callback dolazi od odgovarajuceg tajmera. */
    if (value != 0)
        return;

    /* Azurira se vreme simulacije. */
  
    hours += 10;

    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
     glutTimerFunc(50, on_timer, 0);
}

static void on_display(void){

	
	glClear(GL_COLOR_BUFFER_BIT);

	//postavljanje kamere
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 800, 0, 
			   0, 0, 0,
			   1, 0, 0);


	/*gluLookAt(400,200,400, 
			   0, 0, 0,
			   3, 2, 1);*/
	//iscrtavanje koordinatnnog sistema
	glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(1000, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1000, 0);

		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1000);

	glEnd();

	//Pravljenje Sunca
	glPushMatrix();
		glColor3f(1,1,0);
		glutSolidSphere(r_Sun,50,50);
	glPopMatrix();

	
    //Merkur
    double mercury_revolution = 360 * hours / (0.241*12*30 * 24);
	double mercury_rotation = 360 * hours / (116 * 24);

	
	glPushMatrix();
		glColor3f(1,0,0);
		glRotatef(mercury_revolution,0,1,0);
		glTranslatef(50,0,50);
		glRotatef(mercury_rotation,0,1,0);
		glutSolidSphere(r_Mercury,10,10);
	glPopMatrix();

	//Rotacija i revolucija <3Venere<3
	double venus_revolution = 360 * hours / (0.615*12*30 * 24);
    double venus_rotation = 360 * hours / (224 * 24);

	glPushMatrix();
	glColor3f(1, 0.5, 0);
    glRotatef(venus_revolution, 0, 1, 0);
    glTranslatef(100, 0, 100);
    glRotatef(venus_rotation, 0, -1, 0);
    glutWireSphere(r_Venus, 10, 10);
	glPopMatrix();


	//Rotacija i revolucija Marsa
	double mars_revolution = 360 * hours / (1.881*12*30 * 24);
    double mars_rotation = 360 * hours / (128 * 24);

	glPushMatrix();
	glColor3f(1, 0, 1);
    glRotatef(mars_revolution, 0, 1, 0);
    glTranslatef(200, 0, 200);
    glRotatef(mars_rotation, 0, 1, 0);
    glutWireSphere(r_Mars, 10, 10);
	glPopMatrix();


	//Rotacija i revolucija Jupitera<3
	double jupiter_revolution = 360 * hours / (11.87*12*30 * 24);
    double jupiter_rotation = 360 * hours / (168 * 24);

	glPushMatrix();
	glColor3f(1, 0.7, 0.2);
    glRotatef(jupiter_revolution, 0, 1, 0);
    glTranslatef(250, 0, 250);
    glRotatef(jupiter_rotation, 0, 1, 0);
    glutWireSphere(r_Jupiter, 10, 10);
	glPopMatrix();


	//Rotacija i revolucija Saturna
	double saturn_revolution = 360 * hours / (29.47*12*30 * 24);
    double saturn_rotation = 360 * hours / (400 * 24);

	glPushMatrix();
	glColor3f(0.4, 0.7, 0.9);
    glRotatef(saturn_revolution, 0, 1, 0);
    glTranslatef(300, 0, 300);
    glRotatef(saturn_rotation, 0, 1, 0);
    glutWireSphere(r_Saturn, 10, 10);
	glPopMatrix();

	//Rotacija i revolucija Urana
	double uranus_revolution = 360 * hours / (84.00 *12*30 * 24);
    double uranus_rotation = 360 * hours / (400 * 24);

	glPushMatrix();
	glColor3f(0, 0.3, 0.97);
    glRotatef(uranus_revolution, 0, 1, 0);
    glTranslatef(370, 0, 370);
    glRotatef(uranus_rotation, 0, 1, 0);
    glutWireSphere(r_Uranus, 10, 10);
	glPopMatrix();


	//Rotacija i revolucija Neptuna
	double neptune_revolution = 360 * hours / (164.9 *12*30 * 24);
    double neptune_rotation = 360 * hours / (400 * 24);

	glPushMatrix();
	glColor3f(0, 0, 1);
    glRotatef(neptune_revolution, 0, 1, 0);
    glTranslatef(450, 0, 450);
    glRotatef(neptune_rotation, 0, 1, 0);
    glutWireSphere(r_Neptune, 10, 10);
	glPopMatrix();


	//Rotacija i revolucija Zemlje
	double earth_revolution = 360 * hours / (365.2564 * 24);
	double earth_rotation = 360 * hours / (1 * 24);

	glRotatef(earth_revolution,0,1,0);
	glTranslatef(150,0,150);

	glPushMatrix();
		glColor3f(0,1,0);
		glRotatef(earth_rotation,0,1,0);
		glutSolidSphere(r_Earth,10,10);
	glPopMatrix();

	//Rotacija i revolucija meseca
	double moon_revolution = 360 * hours / (27.6 * 24);
    double moon_rotation = 360 * hours / (27.6 * 24);

	glPushMatrix();
    glRotatef(moon_revolution, 0, 1, 0);
    glTranslatef(30, 0, 0);
    glRotatef(moon_rotation, 0, 1, 0);
    glColor3f(1, 1, 1);
    glutWireSphere(r_Moon, 10, 10);
	glPopMatrix();


	//menjanje bafera
	glutSwapBuffers();


}




