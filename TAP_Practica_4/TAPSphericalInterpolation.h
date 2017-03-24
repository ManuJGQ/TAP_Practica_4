#pragma once

#include <iostream>
#include <vector>
#include <string>

struct Quaternion {
	double s;
	double x;
	double y;
	double z;
};

class TAPSphericalInterpolation{

	std::vector<Quaternion> coordenadasV;
	std::vector<double> coordenadasT;

public:
	TAPSphericalInterpolation();
	TAPSphericalInterpolation(std::string archivoTXT);
	TAPSphericalInterpolation(std::vector<Quaternion> coordV, std::vector<double> coordT);
	TAPSphericalInterpolation(const TAPSphericalInterpolation &interpolacion);

	Quaternion getPosicionInterpolada(double _t);
	Quaternion getPosicionInterpolada(const TAPSphericalInterpolation &interpolacion);

	double getUltimoT() { return coordenadasT[coordenadasT.size() - 1]; }
	double getPrimeraT() { return coordenadasT[0]; }

	~TAPSphericalInterpolation();
};

