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

	// define la posici�n de las c�maras
	void set(igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V, float _tc);

	// define una c�mara de tipo paralela o frustum
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _xwmin, double _xwmax, double _ywmin, double _ywmax, double _znear, double _zfar, float _tc);

	// define una c�mara de tipo perspectiva
	void set(tipoCamara _tipo, igvPunto3D _P0, igvPunto3D _r, igvPunto3D _V,
		double _angulo, double _raspecto, double _znear, double _zfar, float _tc);

	~TAPStereoscopicCamera();
};

