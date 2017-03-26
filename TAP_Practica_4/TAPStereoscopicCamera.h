#pragma once

#include "igvCamara.h"
#include "igvPunto3D.h"

class TAPStereoscopicCamera{

	igvCamara leftCamera;
	igvCamara rightCamera;

	float d0;
	float tc;

public:
	TAPStereoscopicCamera();

	TAPStereoscopicCamera(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, float _tc);

	// define la posición de las cámaras
	void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, float _tc);

	// define una cámara de tipo paralela o frustum
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar, float _tc);

	// define una cámara de tipo perspectiva
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _angulo, double _raspecto, double _znear, double _zfar, float _tc);

	void aplicar(int i);

	void zoom(double factor);

	float get_tc() {
		return tc;
	}
	void set_tc(float _tc) {
		
		float TC = _tc - tc;

		tc = _tc;

		//Actualizamos la primera camara
		igvPunto3D _P0A = leftCamera.P0;
		_P0A.set(_P0A[0] - TC, _P0A[1], _P0A[2]);
		igvPunto3D _rA = leftCamera.r;
		_rA.set(_rA[0] - TC, _rA[1], _rA[2]);

		leftCamera.P0 = _P0A;
		leftCamera.r = _rA;

		//Actualizamos la segunda camara
		igvPunto3D _P0B = rightCamera.P0;
		_P0A.set(_P0B[0] + TC, _P0B[1], _P0B[2]);
		igvPunto3D _rB = rightCamera.r;
		_rB.set(_rB[0] + TC, _rB[1], _rB[2]);

		rightCamera.P0 = _P0B;
		rightCamera.r = _rB;
	}

	float get_d0() {
		return d0;
	}
	void set_d0(float _d0) {
		d0 = _d0;

		//Actualizamos la primera camara
		igvPunto3D _rA = leftCamera.r;
		_rA.set(_rA[0], _rA[1], _rA[2] + d0);

		leftCamera.r = _rA;

		//Actualizamos la segunda camara
		igvPunto3D _rB = rightCamera.r;
		_rB.set(_rB[0], _rB[1], _rB[2] + d0);

		rightCamera.P0 = _rB;

	}

	~TAPStereoscopicCamera();
};

