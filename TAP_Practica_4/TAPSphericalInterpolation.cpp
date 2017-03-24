#include "TAPSphericalInterpolation.h"

#include <fstream>
#include <math.h>

#define Epsilon 0.000001

static bool iguales(double a, double b) {
	return (abs(a - b) <= Epsilon);
}

/**
* Constructor por defecto de la interpolacion esferica
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();
}

/**
* Constructor que crea la interpolacion a partir de un fichero .txt
* con el siguiente formato en cada linea:
* t,v Ejemplo: 0.6,1,1,1,1 tiene t = 0.6 y Quaternion = 1,1,1,1
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(std::string archivoTXT){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	int coma;
	std::string linea_actual;

	double T;
	std::string sV;
	Quaternion V;

	try {
		std::ifstream archivoInterpolacion;
		archivoInterpolacion.open(archivoTXT);

		if (!archivoInterpolacion.good()) throw std::string("No se puedo leer el archivo");

		while (std::getline(archivoInterpolacion, linea_actual)) {
			coma = linea_actual.find(',');

			T = std::stod(linea_actual.substr(0, coma));

			sV = linea_actual.substr(coma + 1, linea_actual.length());

			coma = sV.find(',');

			V.s = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.x = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.y = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.z = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			//std::cout << T << " - " << V.s << "," << V.x << "," << V.y << "," << V.z << "," << std::endl;

			coordenadasT.push_back(T);
			coordenadasV.push_back(V);

		}

	}
	catch (std::string &e) {
		throw e;
	}
}

/**
* Constructor que crea la interpolacion a partir de dos vectores
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(std::vector<Quaternion> coordV, std::vector<double> coordT){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < coordV.size(); i++) {
		coordenadasT.push_back(coordT[i]);
		coordenadasV.push_back(coordV[i]);
	}
}

/**
* Constructor de copia
*/
TAPSphericalInterpolation::TAPSphericalInterpolation(const TAPSphericalInterpolation & interpolacion){
	coordenadasV = std::vector<Quaternion>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < interpolacion.coordenadasT.size(); i++) {
		coordenadasT.push_back(interpolacion.coordenadasT[i]);
		coordenadasV.push_back(interpolacion.coordenadasV[i]);
	}
}

/**
* Funcion que dado un valor T devuelve el Quaternion en funcion a la interpolacion
*/
Quaternion TAPSphericalInterpolation::getPosicionInterpolada(double _t){
	int tamaT = coordenadasT.size() - 1;

	for (int i = 0; i < tamaT; i++) {
		if (iguales(coordenadasT[i], _t)) {
			return coordenadasV[i];
		}
		if (_t > coordenadasT[i] && _t < coordenadasT[i + 1]) {

			double alfa = (_t - coordenadasT[i]) / (coordenadasT[i + 1] - coordenadasT[i]);

			Quaternion x = coordenadasV[i];
			Quaternion y = coordenadasV[i + 1];

			//Normalizamos los dos Quaternions
			//double modX = abs(pow(x.s, 2) + pow(x.x, 2) + pow(x.y, 2) + pow(x.z, 2));
			//double modY = abs(pow(y.s, 2) + pow(y.x, 2) + pow(y.y, 2) + pow(y.z, 2));

			//x.s = x.s / modX;
			//x.x = x.x / modX;
			//x.y = x.y / modX;
			//x.z = x.z / modX;

			//y.s = y.s / modY;
			//y.x = y.x / modY;
			//y.y = y.y / modY;
			//y.z = y.z / modY;

			//Obtenemos el angulo Phi
			double c = x.s * y.s + x.x * y.x + x.y * y.y + x.z * y.z;

			Quaternion v;
			v.s = y.s - (c * x.s);
			v.x = y.x - (c * x.x);
			v.y = y.y - (c * x.y);
			v.z = y.z - (c * x.z);

			double s = abs(v.s * v.s + v.x * v.x + v.y * v.y + v.z * v.z);

			double angPhi = atan2(s, c);

			std::cout << angPhi << std::endl;

			double a = (sin((1 - alfa) * angPhi)) / (sin(angPhi));

			double b = (sin(alfa * angPhi)) / (sin(angPhi));

			Quaternion z;
			z.s = (a * x.s) + (b * y.s);
			z.x = (a * x.x) + (b * y.x);
			z.y = (a * x.y) + (b * y.y);
			z.z = (a * x.z) + (b * y.z);

			std::cout << z.s << " " << z.x << " " << z.y << " " << z.z << std::endl;

			return z;
		}
	}
}

/**
* Funcion que calcula el Quaternion en un instante t comprendido entre el comienzo y el
* final de dos interpolaciones esfericas distintas
*/
Quaternion TAPSphericalInterpolation::getPosicionInterpolada(const TAPSphericalInterpolation & interpolacion){

	return Quaternion();
}

/**
* Destructor
*/
TAPSphericalInterpolation::~TAPSphericalInterpolation(){}
