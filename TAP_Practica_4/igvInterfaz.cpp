#include <cstdlib>
#include <stdio.h>

#include <glui.h>

#include "igvInterfaz.h"

extern igvInterfaz interfaz; // los callbacks deben ser estaticos y se requiere este objeto para acceder desde
							 // ellos a las variables de la clase

// Metodos constructores -----------------------------------

igvInterfaz::igvInterfaz() {
	//inicialización de los atributos para realizar la selección mediante lista de impactos
	modo = IGV_VISUALIZAR;

	ang = 70;

	va.set(0, 1.0, 0);

	i = 0;

	tc = 0.5;
	d0 = 8;

	vistas[0].set(6.0, 4.0, d0);
	vistas[1].set(10, 0, 0);
	vistas[2].set(0, 10, 0);
	vistas[3].set(0, 0, d0 + 2);

	planos[1] = -3;
	planos[2] = 1;

	formato = false;
	vista = false;

	animacion = false;

	pt = 0.0f;

	bezier = TAPBezier("bezier.txt");

	velocidad = TAPSpeedController(0.2f, 0.5f);

	movController = TAPMotionController(3000, bezier, velocidad);

	twist = 0.0f;

	sphericalInterpolation = TAPSphericalInterpolation("sphericalInterpolation.txt");

	pintarBezier = true;

	anaglifo = true;
}

igvInterfaz::~igvInterfaz() {}


// Metodos publicos ----------------------------------------

void igvInterfaz::crear_mundo(void) {
	//establecer los parámetros de la cámara en función de la escena concreta que se esté modelando
	interfaz.camara.set(IGV_PARALELA, interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(),
		-1 * 20, 1 * 20, -1 * 20, 1 * 20, interfaz.planos[1], 2000, interfaz.tc);

}

void igvInterfaz::configura_entorno(int argc, char** argv,
	int _ancho_ventana, int _alto_ventana,
	int _pos_X, int _pos_Y, string _titulo) {

	// inicialización de las variables de la interfaz																	
	ancho_ventana = _ancho_ventana;
	alto_ventana = _alto_ventana;

	// inicialización de la ventana de visualización
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(_ancho_ventana, _alto_ventana);
	glutInitWindowPosition(_pos_X, _pos_Y);
	glutCreateWindow(_titulo.c_str());


	glEnable(GL_DEPTH_TEST); // activa el ocultamiento de superficies por z-buffer
	glClearColor(0.0, 0.0, 0.0, 0.0); // establece el color de fondo de la ventana

	glEnable(GL_LIGHTING); // activa la iluminacion de la escena
	glEnable(GL_NORMALIZE); // normaliza los vectores normales para calculo iluminacion

	crear_mundo(); // crea el mundo a visualizar en la ventana
}

void igvInterfaz::inicia_bucle_visualizacion() {
	glutMainLoop(); // inicia el bucle de visualizacion de OpenGL
}

void igvInterfaz::set_glutKeyboardFunc(unsigned char key, int x, int y) {
	switch (key) {
		// incluir aquí el cambio de la cámara para mostrar las vistas planta, perfil, alzado o perspectiva
	case 'V':
	case 'v':
		interfaz.i++;
		interfaz.vistas[3].set(0, 0, 10);
		if (interfaz.i > 3)interfaz.i = 0;
		if (interfaz.i == 2)interfaz.set_va(1.0, 0, 0);
		else interfaz.set_va(0, 1.0, 0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		interfaz.camara.aplicar(0);
		interfaz.camara.aplicar(1);
		break;
	case '1':
		interfaz.opcion = '1';
		std::cout << "K1" << std::endl;
		break;
	case '2':
		interfaz.opcion = '2';
		std::cout << "K2" << std::endl;
		break;
	case '+':
		if (interfaz.opcion == '1' && !interfaz.animacion) {
			interfaz.movController.set_K1(0.05);
			interfaz.velocidad.set_K1(0.05);
		}
		if (interfaz.opcion == '2' && !interfaz.animacion) {
			interfaz.movController.set_K2(0.05);
			interfaz.velocidad.set_K2(0.05);
		}
		break;
	case '-':
		if (interfaz.opcion == '1' && !interfaz.animacion) {
			interfaz.movController.set_K1(-0.05);
			interfaz.velocidad.set_K1(-0.05);
		}
		if (interfaz.opcion == '2' && !interfaz.animacion) {
			interfaz.movController.set_K2(-0.05);
			interfaz.velocidad.set_K2(-0.05);
		}
		break;
	case 'X':
		interfaz.tc += 0.5;
		//interfaz.camara.set_tc(interfaz.tc);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		break;
	case 'x':
		interfaz.tc -= 0.5;
		//interfaz.camara.set_tc(interfaz.tc);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		break;
	case 'Z':
		interfaz.d0 += 0.5;
		interfaz.vistas[0].set(6.0, 4.0, interfaz.d0);
		interfaz.vistas[3].set(0, 0, interfaz.d0 + 2);
		interfaz.camara.set_d0(interfaz.d0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		break;
	case 'z':
		interfaz.d0 -= 0.5;
		interfaz.vistas[0].set(6.0, 4.0, interfaz.d0);
		interfaz.vistas[3].set(0, 0, interfaz.d0 + 2);
		interfaz.camara.set_d0(interfaz.d0);
		interfaz.camara.set(interfaz.get_vistas(interfaz.i), igvPunto3D(0, 0, 0), interfaz.get_va(), interfaz.tc);
		break;
	case 'M':
	case 'm': 
		interfaz.set_anaglifo(interfaz.get_anaglifo() ? false : true);
		break;
	case 'A':
	case 'a': // activa/desactiva la animación de la escena
	// incluir aquí la activación de la animación
		interfaz.animacion = (interfaz.animacion ? false : true);
		break;
	case 'B':
	case 'b':
		interfaz.pintarBezier = (interfaz.pintarBezier ? false : true);
		break;
	case 'e': // activa/desactiva la visualizacion de los ejes
		interfaz.escena.set_ejes(interfaz.escena.get_ejes() ? false : true);
		break;
	case 27: // tecla de escape para SALIR
		exit(1);
		break;
	}
	glutPostRedisplay(); // renueva el contenido de la ventana de vision
}

void igvInterfaz::set_glutReshapeFunc(int w, int h) {
	// dimensiona el viewport al nuevo ancho y alto de la ventana
	// guardamos valores nuevos de la ventana de visualizacion
	interfaz.set_ancho_ventana(w);
	interfaz.set_alto_ventana(h);

	// establece los parámetros de la cámara y de la proyección
	interfaz.camara.aplicar(0);
	interfaz.camara.aplicar(1);
}

void igvInterfaz::set_glutDisplayFunc() {
	GLuint lista_impactos[1024]; // array con la lista de impactos cuando se visualiza en modo selección
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // borra la ventana y el z-buffer

	for (int i = 0; i < 2; i++) {

		glClear(GL_DEPTH_BUFFER_BIT);

		// se establece el viewport
		if (interfaz.anaglifo)glViewport(0, 0, interfaz.get_ancho_ventana() , interfaz.get_alto_ventana());
		else {
			if (i == 0) {
				glViewport(0, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana());
			} else {
				glViewport(interfaz.get_ancho_ventana() / 2, 0, interfaz.get_ancho_ventana() / 2, interfaz.get_alto_ventana());
			}
		}


		// aplica las transformaciones en función de los parámetros de la cámara y del modo (visualización o selección)
		

		if (i == 0) {
			interfaz.camara.aplicar(0);
			if(interfaz.anaglifo)glColorMask(GL_TRUE, GL_FALSE, GL_FALSE, GL_FALSE);
		}
		else {
			interfaz.camara.aplicar(1);
			if (interfaz.anaglifo)glColorMask(GL_FALSE, GL_FALSE, GL_TRUE, GL_FALSE);
		}

		if (interfaz.pintarBezier)interfaz.bezier.pintarCurva();
		else interfaz.velocidad.pintarCurva();

		// visualiza la escena
		interfaz.escena.visualizar();

		if (interfaz.anaglifo)glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	}


	// refresca la ventana
	glutSwapBuffers();

}

void igvInterfaz::set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y) {
	if (boton == 3) {
		interfaz.camara.zoom(10);
	}
	if (boton == 4) {
		interfaz.camara.zoom(-10);
	}

	glutPostRedisplay();
}

void igvInterfaz::set_glutIdleFunc() {
	// incluir el código para animar el modelo de la manera más realista posible
	if (interfaz.animacion) {
		/***************************************************************
		*		     INTERPOLACION MOVIMIENTO & DEFORMACION			   *
		***************************************************************/
		
		Punto nuevoPunto = interfaz.movController.get_Punto(interfaz.pt);

		interfaz.twist = interfaz.movController.get_Twist(interfaz.pt);

		interfaz.pt += 0.01f;
		if (interfaz.pt >= 1.0f) {
			interfaz.pt = 0.0f;
		}

		/*std::cout << interfaz.pt << std::endl;
		std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;*/

		Punto movimiento;
		movimiento.x = nuevoPunto.x - interfaz.puntoActual.x;
		movimiento.y = nuevoPunto.y - interfaz.puntoActual.y;
		movimiento.z = nuevoPunto.z - interfaz.puntoActual.z;

		/*std::cout << "--------------------------------------------------------" << std::endl;
		std::cout << interfaz.puntoActual.x << " " << interfaz.puntoActual.y << " " << interfaz.puntoActual.z << std::endl;*/

		interfaz.puntoActual = nuevoPunto;

		//std::cout << nuevoPunto.x << " " << nuevoPunto.y << " " << nuevoPunto.z << std::endl;
		//std::cout << movimiento.x << " " << movimiento.y << " " << movimiento.z << std::endl;

		//std::cout << interfaz.twist << std::endl;

		interfaz.escena.setMovimiento(nuevoPunto);
		interfaz.escena.setTwist(interfaz.twist * 0.7f);

		Quaternion nuevoGiro = interfaz.sphericalInterpolation.getPosicionInterpolada(interfaz.twist * interfaz.sphericalInterpolation.getUltimoT());

		interfaz.escena.setGiro(nuevoGiro);

		glutPostRedisplay();
	}
}

void igvInterfaz::escribir(char *st, int x, int y) {
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(st); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}

}

void igvInterfaz::inicializa_callbacks() {
	glutKeyboardFunc(set_glutKeyboardFunc);
	glutReshapeFunc(set_glutReshapeFunc);
	glutDisplayFunc(set_glutDisplayFunc);
	glutIdleFunc(set_glutIdleFunc);
	glutMouseFunc(set_glutMouseFunc);
}
