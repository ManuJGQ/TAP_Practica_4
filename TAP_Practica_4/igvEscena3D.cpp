#include <cstdlib>
#include <stdio.h>

#include "igvEscena3D.h"

// Metodos constructores 

igvEscena3D::igvEscena3D() {
	ejes = true;
	tapering = false;

	movimiento.x = 0;
	movimiento.y = 0;
	movimiento.z = 0;

	twist = 0;
}

igvEscena3D::~igvEscena3D() {

}

// Metodos publicos 

void pintar_ejes(void) {
	GLfloat rojo[] = { 1,0,0,1.0 };
	GLfloat verde[] = { 0,1,0,1.0 };
	GLfloat azul[] = { 0,0,1,1.0 };

	glBegin(GL_LINES);
	glMaterialfv(GL_FRONT, GL_EMISSION, rojo);
	glVertex3f(1000, 0, 0);
	glVertex3f(-1000, 0, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, verde);
	glVertex3f(0, 1000, 0);
	glVertex3f(0, -1000, 0);

	glMaterialfv(GL_FRONT, GL_EMISSION, azul);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}


void igvEscena3D::visualizar() {
	// crear luces
	GLfloat luz0[4] = { 5.0,5.0,5.0,1 }; // luz puntual  
	glLightfv(GL_LIGHT0, GL_POSITION, luz0); // la luz se coloca aquí si permanece fija y no se mueve con la escena
	glEnable(GL_LIGHT0);

	// crear el modelo
	glPushMatrix(); // guarda la matriz de modelado

	  // se pintan los ejes
	if (ejes) pintar_ejes();

	//glLightfv(GL_LIGHT0,GL_POSITION,luz0); // la luz se coloca aquí si se mueve junto con la escena

	glTranslated(movimiento.x, movimiento.y, movimiento.z);
	glRotatef(giro.s, giro.x, giro.y, giro.z);

	//Vertices cubo

	Punto x1 = {};
	Punto x2 = {};
	Punto x3 = {};
	Punto x4 = {};

	Punto x5 = {};
	Punto x6 = {};
	Punto x7 = {};
	Punto x8 = {};

	if (!tapering) {
		x1 = { -1.5f * cos(twist * 1.5f) - 1.5f * sin(twist * 1.5f), -1.5f * sin(twist * 1.5f) + 1.5f * cos(twist * 1.5f), 1.5f };
		x2 = { 1.5f * cos(twist * 1.5f) - 1.5f * sin(twist * 1.5f), 1.5f * sin(twist * 1.5f) + 1.5f * cos(twist * 1.5f), 1.5f };
		x3 = { 1.5f * cos(twist * -1.5f) - 1.5f * sin(twist * -1.5f), 1.5f * sin(twist * -1.5f) + 1.5f * cos(twist * -1.5f), -1.5f };
		x4 = { -1.5f * cos(twist * -1.5f) - 1.5f * sin(twist * -1.5f), -1.5f * sin(twist * -1.5f) + 1.5f * cos(twist * -1.5f), -1.5f };

		x5 = { 1.5f * cos(twist * 1.5f) + 1.5f * sin(twist * 1.5f), 1.5f * sin(twist * 1.5f) - 1.5f * cos(twist * 1.5f), 1.5f };
		x6 = { -1.5f * cos(twist * 1.5f) + 1.5f * sin(twist * 1.5f), -1.5f * sin(twist * 1.5f) - 1.5f * cos(twist * 1.5f), 1.5f };
		x7 = { 1.5f * cos(twist *-1.5f) + 1.5f * sin(twist * -1.5f), 1.5f * sin(twist * -1.5f) - 1.5f * cos(twist * -1.5f), -1.5f };
		x8 = { -1.5f * cos(twist * -1.5f) + 1.5f * sin(twist * -1.5f), -1.5f * sin(twist * -1.5f) - 1.5f * cos(twist * -1.5f), -1.5f };
	}
	else {
		float sz = (1.5f - 1.5f) / (1.5f + 1.5f);
		x1 = { -1.5f * sz, 1.5f * sz, 1.5f };

		sz = (1.5f - 1.5f) / (1.5f + 1.5f);
		x2 = { 1.5f * sz, 1.5f * sz, 1.5f };

		sz = (1.5f + 1.5f) / (1.5f + 1.5f);
		x3 = { 1.5f  * sz, 1.5f  * sz, -1.5f };

		sz = (1.5f + 1.5f) / (1.5f + 1.5f);
		x4 = { -1.5f * sz ,1.5f  * sz, -1.5f };

		sz = (1.5f - 1.5f) / (1.5f + 1.5f);
		x5 = { 1.5f * sz , -1.5f * sz , 1.5f };

		sz = (1.5f - 1.5f) / (1.5f + 1.5f);
		x6 = { -1.5f * sz , -1.5f * sz , 1.5f };

		sz = (1.5f + 1.5f) / (1.5f + 1.5f);
		x7 = { 1.5f * sz , -1.5f * sz , -1.5f };

		sz = (1.5f + 1.5f) / (1.5f + 1.5f);
		x8 = { -1.5f * sz, -1.5f * sz , -1.5f };
	}


	glRotated(-90, 1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
	// top
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1.x, x1.y, x1.z);
	glVertex3f(x2.x, x2.y, x2.z);
	glVertex3f(x3.x, x3.y, x3.z);
	glVertex3f(x4.x, x4.y, x4.z);

	glEnd();

	glBegin(GL_QUADS);
	// front
	glColor3f(0.0f, 1.0f, 0.0f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x5.x, x5.y, x5.z);
	glVertex3f(x2.x, x2.y, x2.z);
	glVertex3f(x1.x, x1.y, x1.z);
	glVertex3f(x6.x, x6.y, x6.z);

	glEnd();

	glBegin(GL_QUADS);
	// right
	glColor3f(0.0f, 0.0f, 1.0f);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x3.x, x3.y, x3.z);
	glVertex3f(x2.x, x2.y, x2.z);
	glVertex3f(x5.x, x5.y, x5.z);
	glVertex3f(x7.x, x7.y, x7.z);

	glEnd();

	glBegin(GL_QUADS);
	// left
	glColor3f(0.0f, 0.0f, 0.5f);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(x6.x, x6.y, x6.z);
	glVertex3f(x1.x, x1.y, x1.z);
	glVertex3f(x4.x, x4.y, x4.z);
	glVertex3f(x8.x, x8.y, x8.z);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glColor3f(0.5f, 0.0f, 0.0f);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(x5.x, x5.y, x5.z);
	glVertex3f(x6.x, x6.y, x6.z);
	glVertex3f(x8.x, x8.y, x8.z);
	glVertex3f(x7.x, x7.y, x7.z);

	glEnd();

	glBegin(GL_QUADS);
	// back
	glColor3f(0.0f, 0.5f, 0.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x3.x, x3.y, x3.z);
	glVertex3f(x7.x, x7.y, x7.z);
	glVertex3f(x8.x, x8.y, x8.z);
	glVertex3f(x4.x, x4.y, x4.z);

	glEnd();

	glPopMatrix(); // restaura la matriz de modelado
}