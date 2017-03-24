#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Puntos {
	double x;
	double y;
	double z;
};

class TAPLinearInterpolation {

	std::vector<Puntos> coordenadasV;
	std::vector<double> coordenadasT;

public:
	TAPLinearInterpolation();
	TAPLinearInterpolation(std::string archivoTXT);
	TAPLinearInterpolation(std::vector<Puntos> coordV, std::vector<double> coordT);
	TAPLinearInterpolation(const TAPLinearInterpolation &interpolacion);

	Puntos getPosicionInterpolada(double _t);
	Puntos getPosicionInterpolada(const TAPLinearInterpolation &interpolacion);

	double getUltimoT() { return coordenadasT[coordenadasT.size() - 1]; }
	double getPrimeraT() { return coordenadasT[0]; }

	~TAPLinearInterpolation();
};

