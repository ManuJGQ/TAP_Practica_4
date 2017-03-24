#include "TAPLinearInterpolation.h"

#include <fstream>
#include <math.h>

#define Epsilon 0.000001

static bool iguales(double a, double b) {
	return (abs(a - b) <= Epsilon);
}

/**
* Constructor por defecto de la interpolacion lineal
*/
TAPLinearInterpolation::TAPLinearInterpolation(){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();
}

/**
* Constructor que crea la interpolacion a partir de un fichero .txt
* con el siguiente formato en cada linea:
* t,v Ejemplo: 0.6,1,1,1 tiene t = 0.6 y Punto = 1,1,1
*/
TAPLinearInterpolation::TAPLinearInterpolation(std::string archivoTXT) {
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	int coma;
	std::string linea_actual;

	double T;
	std::string sV;
	Puntos V;

	try {
		std::ifstream archivoInterpolacion;
		archivoInterpolacion.open(archivoTXT);

		if (!archivoInterpolacion.good()) throw std::string("No se puedo leer el archivo");

		while (std::getline(archivoInterpolacion, linea_actual)) {
			coma = linea_actual.find(',');

			T = std::stod(linea_actual.substr(0, coma));

			sV = linea_actual.substr(coma + 1, linea_actual.length());

			coma = sV.find(',');

			V.x = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.y = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			coma = sV.find(',');

			V.z = std::stod(sV.substr(0, coma));

			sV = sV.substr(coma + 1, sV.length());

			//std::cout << T << " - " << V.x << "," << V.y << "," << V.z << "," << std::endl;

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
TAPLinearInterpolation::TAPLinearInterpolation(std::vector<Puntos> coordV, std::vector<double> coordT){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < coordV.size(); i++) {
		coordenadasT.push_back(coordT[i]);
		coordenadasV.push_back(coordV[i]);
	}
}

/**
* Constructor de copia
*/
TAPLinearInterpolation::TAPLinearInterpolation(const TAPLinearInterpolation & interpolacion){
	coordenadasV = std::vector<Puntos>();
	coordenadasT = std::vector<double>();

	for (int i = 0; i < interpolacion.coordenadasT.size(); i++) {
		coordenadasT.push_back(interpolacion.coordenadasT[i]);
		coordenadasV.push_back(interpolacion.coordenadasV[i]);
	}
}

/**
* Funcion que dado un valor T devuelve la posicion en funcion a la interpolacion
*/
Puntos TAPLinearInterpolation::getPosicionInterpolada(double _t){
	int tamaT = coordenadasT.size() - 1;

	if(_t > coordenadasT[tamaT]) throw std::string("T no valido");

	for (int i = 0; i < tamaT; i++) {
		if (iguales(coordenadasT[i], _t)) {
			return coordenadasV[i];
		}
		if (_t > coordenadasT[i] && _t < coordenadasT[i + 1]) {

			double alfa = (_t - coordenadasT[i]) / (coordenadasT[i + 1] - coordenadasT[i]);

			Puntos x1 = coordenadasV[i];
			Puntos x2 = coordenadasV[i + 1];

			Puntos p;
			p.x = ((1 - alfa) * x1.x) + (alfa * x2.x);
			p.y = ((1 - alfa) * x1.y) + (alfa * x2.y);
			p.z = ((1 - alfa) * x1.z) + (alfa * x2.z);

			//std::cout << p.x << " " << p.y << " " << p.z << std::endl;

			return p;
		}
	}
}

/**
* Funcion que calcula el punto en un instante t comprendido entre el comienzo y el 
* final de dos interpolaciones distintas
*/
Puntos TAPLinearInterpolation::getPosicionInterpolada(const TAPLinearInterpolation & interpolacion){
	int tamaT = coordenadasT.size() - 1;
	int tamaT2 = interpolacion.coordenadasT.size() - 1;
	
	if (coordenadasT[tamaT] < interpolacion.coordenadasT[0]) {
		double _t = (coordenadasT[tamaT] + interpolacion.coordenadasT[0]) / 2;
		double alfa = (_t - coordenadasT[tamaT]) / (interpolacion.coordenadasT[0] - coordenadasT[tamaT]);

		Puntos x1 = coordenadasV[tamaT];
		Puntos x2 = interpolacion.coordenadasV[0];

		Puntos p;
		p.x = ((1 - alfa) * x1.x) + (alfa * x2.x);
		p.y = ((1 - alfa) * x1.y) + (alfa * x2.y);
		p.z = ((1 - alfa) * x1.z) + (alfa * x2.z);

		return p;
	} else {
		double _t = (coordenadasT[0] + interpolacion.coordenadasT[tamaT2]) / 2;
		double alfa = (_t - interpolacion.coordenadasT[tamaT2]) / (coordenadasT[0] - interpolacion.coordenadasT[tamaT2]);

		Puntos x1 = interpolacion.coordenadasV[tamaT2];
		Puntos x2 = coordenadasV[0];

		Puntos p;
		p.x = ((1 - alfa) * x1.x) + (alfa * x2.x);
		p.y = ((1 - alfa) * x1.y) + (alfa * x2.y);
		p.z = ((1 - alfa) * x1.z) + (alfa * x2.z);

		return p;
	}
}

/**
* Destructor
*/
TAPLinearInterpolation::~TAPLinearInterpolation(){}
