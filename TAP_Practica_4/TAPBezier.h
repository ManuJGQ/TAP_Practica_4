#pragma once

#include <iostream>
#include <string>

struct Punto {
	float x;
	float y;
	float z;
};

class TAPBezier{
	
	Punto A; //Punto principal 1
	Punto C0; //Punto de control 1
	Punto C1; //Punto de control 2
	Punto B; //Punto principal 2

public:
	TAPBezier();
	TAPBezier(Punto _a, Punto _c0, Punto _c1, Punto _b);
	TAPBezier(std::string ficheroTXT);
	TAPBezier(const TAPBezier &bezier);

	Punto getPunto(float _u);

	float distancia(float u1, float u2);

	void pintarCurva();

	void setA(Punto _a) { A = _a; }
	void setC0(Punto _c0) { C0 = _c0; }
	void setC1(Punto _c1) { C1 = _c1; }
	void setB(Punto _b) { B = _b; }

	~TAPBezier();
};

