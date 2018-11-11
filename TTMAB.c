#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

static void on_display(void);
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);


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

static void on_display(void){

	
	glClear(GL_COLOR_BUFFER_BIT);

	//postavljanje kamere
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2, 2, 2, 
			   0, 0, 0,
			   0, 1, 0);
	//iscrtavanje koordinatnnog sistema
	glBegin(GL_LINES);
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);

		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);

	glEnd();

	glColor3f(0.5,0.5,0.5);
	glutWireSphere(1,20,20);

	//menjanje bafera
	glutSwapBuffers();


}




