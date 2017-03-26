#include "TAPStereoscopicCamera.h"



TAPStereoscopicCamera::TAPStereoscopicCamera() {}

TAPStereoscopicCamera::TAPStereoscopicCamera(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, float _tc) {
	tc = _tc;
	d0 = _P0[2];

	//Definimos la primera camara
	igvPunto3D _P0A = _P0;
	_P0A.set(_P0A[0] - tc, _P0A[1], _P0A[2]);
	igvPunto3D _rA = _r;
	_rA.set(_rA[0] - tc, _rA[1], _rA[2]);

	leftCamera = igvCamara(_tipo, _P0A, _rA, _V);

	//Definimos la segunda camara
	igvPunto3D _P0B = _P0;
	_P0B.set(_P0B[0] + tc, _P0B[1], _P0B[2]);
	igvPunto3D _rB = _r;
	_rB.set(_rB[0] + tc, _rB[1], _rB[2]);

	rightCamera = igvCamara(_tipo, _P0B, _rB, _V);

}

void TAPStereoscopicCamera::set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, float _tc) {
	tc = _tc;
	d0 = _P0[2];

	//Actualizamos la primera camara
	igvPunto3D _P0A = _P0;
	_P0A.set(_P0A[0] - tc, _P0A[1], _P0A[2]);
	igvPunto3D _rA = _r;
	_rA.set(_rA[0] - tc, _rA[1], _rA[2]);

	leftCamera.set(_P0A, _rA, _V);

	//Actualizamos la segunda camara
	igvPunto3D _P0B = _P0;
	_P0B.set(_P0B[0] + tc, _P0B[1], _P0B[2]);
	igvPunto3D _rB = _r;
	_rB.set(_rB[0] + tc, _rB[1], _rB[2]);

	rightCamera.set(_P0B, _rB, _V);
}

void TAPStereoscopicCamera::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar, float _tc) {
	tc = _tc;
	d0 = _P0[2];

	//Actualizamos la primera camara
	igvPunto3D _P0A = _P0;
	_P0A.set(_P0A[0] - tc, _P0A[1], _P0A[2]);
	igvPunto3D _rA = _r;
	_rA.set(_rA[0] - tc, _rA[1], _rA[2]);

	leftCamera.set(_tipo, _P0A, _rA, _V, _xwmin, _xwmax, _ywmin, _ywmax, _znear, _zfar);

	//Actualizamos la segunda camara
	igvPunto3D _P0B = _P0;
	_P0B.set(_P0B[0] + tc, _P0B[1], _P0B[2]);
	igvPunto3D _rB = _r;
	_rB.set(_rB[0] + tc, _rB[1], _rB[2]);

	rightCamera.set(_tipo, _P0B, _rB, _V, _xwmin, _xwmax, _ywmin, _ywmax, _znear, _zfar);
}


void TAPStereoscopicCamera::set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, double _angulo, double _raspecto, double _znear, double _zfar, float _tc) {
	tc = _tc;
	d0 = _P0[2];

	//Actualizamos la primera camara
	igvPunto3D _P0A = _P0;
	_P0A.set(_P0A[0] - tc, _P0A[1], _P0A[2]);
	igvPunto3D _rA = _r;
	_rA.set(_rA[0] - tc, _rA[1], _rA[2]);

	leftCamera.set(_tipo, _P0A, _rA, _V, _angulo, _raspecto, _znear, _zfar);

	//Actualizamos la segunda camara
	igvPunto3D _P0B = _P0;
	_P0B.set(_P0B[0] + tc, _P0B[1], _P0B[2]);
	igvPunto3D _rB = _r;
	_rB.set(_rB[0] + tc, _rB[1], _rB[2]);

	rightCamera.set(_tipo, _P0B, _rB, _V, _angulo, _raspecto, _znear, _zfar);
}

void TAPStereoscopicCamera::aplicar(int i) {
	if (i == 0)leftCamera.aplicar();
	if (i == 1)rightCamera.aplicar();
}

void TAPStereoscopicCamera::zoom(double factor) {
	leftCamera.zoom(factor);
	rightCamera.zoom(factor);
}

TAPStereoscopicCamera::~TAPStereoscopicCamera() {}
