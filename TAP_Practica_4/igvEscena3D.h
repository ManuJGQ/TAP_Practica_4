#ifndef __IGVESCENA3D
#define __IGVESCENA3D

#include <glut.h>

#include <iostream>
#include "TAPMotionController.h"
#include "TAPSphericalInterpolation.h"

#define Epsilon 0.000001

static bool iguales(double a, double b) {
	return (abs(a - b) <= Epsilon);
}

using namespace std;

class igvEscena3D {
	Punto movimiento;

	Quaternion giro;

	float twist;
protected:	
	bool ejes;
	bool tapering;
public:
	// Constructores por defecto y destructor
	igvEscena3D();
	~igvEscena3D();

	// Metodos estáticos

	// Métodos
	// método con las llamadas OpenGL para visualizar la escena
	void visualizar(void);

	void setGiro(Quaternion _giro) {
		giro.s = _giro.s;
		giro.x = _giro.x;
		giro.y = _giro.y;
		giro.z = _giro.z;
	}

	void setMovimiento(Punto _mov) {
		movimiento.x = _mov.x;
		movimiento.y = _mov.y;
		movimiento.z = _mov.z;
	}

	void setTwist(float _t) {
		float tw = _t;
		if ((tw > -0.7 || iguales(tw, -0.7)) && (tw < 0.7 || iguales(tw, 0.7)) && !tapering) {
			twist = _t;
		}
	}

	bool get_ejes() { return ejes; };
	void set_ejes(bool _ejes) { ejes = _ejes; };

	bool getTapering() { return tapering; }
	void setTapering(bool _t) { tapering = _t; }
};

#endif
