#include "TAPMotionController.h"

/**
* Constructor parametrizado
*/
TAPMotionController::TAPMotionController(){
	nEntradasTabla = 0;
}

/**
* Constructor parametrizado
*/
TAPMotionController::TAPMotionController(int n, TAPBezier _desp, TAPSpeedController _vel){
	nEntradasTabla = n;

	desplazamiento = TAPBezier(_desp);
	velocidad = TAPSpeedController(_vel);

	construirTablaIncrementos();
}

/**
* COnstructor de copia
*/
TAPMotionController::TAPMotionController(const TAPMotionController & motioncontroller){
	nEntradasTabla = motioncontroller.nEntradasTabla;

	desplazamiento = TAPBezier(motioncontroller.desplazamiento);
	velocidad = TAPSpeedController(motioncontroller.velocidad);

	construirTablaIncrementos();
}

/**
* Funcion que construye la tabla de incrementos con la cual podemos
* obtener el valor u dada un desplazamiento s, y asi poder calcular
* posteriormente la poscion p en el instante t
*/
void TAPMotionController::construirTablaIncrementos(){
	//std::cout << "ENTRO" << std::endl;
	tablaIncrementos.clear();
	
	float incremento = 1.0f / (float)(nEntradasTabla - 1);

	float dist_Acumulada = 0.0f;
	float uAcumulada = 0.0f;
	int i = 0;

	tablaIncrementos.push_back(std::pair<float, int>(dist_Acumulada, i));
	i++;

	while (uAcumulada <= 1.0f) {
		float u = incremento * (float)i;

		float dist = desplazamiento.distancia(uAcumulada, u) + dist_Acumulada;

		tablaIncrementos.push_back(std::pair<float, int>(dist, i));
		i++;

		dist_Acumulada = dist;
		uAcumulada = u;
	}

	/*for (int j = 0; j < tablaIncrementos.size(); j++) {
		std::cout << tablaIncrementos[j].first << " --- " << tablaIncrementos[j].second << std::endl;
	}*/
}

/**
* Funcion que devuelve el indice correspondiente al valor mas
* aproximado a una distancia s dada
*/
int TAPMotionController::get_Indice(float s){
	int i = 0;

	while (tablaIncrementos[i].first < s && i < nEntradasTabla) {
		i++;
	}

	return i;
}

/**
* Funcion que devuelve el Punto p en el que el objete se encuentre
* en el instante t
*/
Punto TAPMotionController::get_Punto(float t){
	float incremento = 1.0f / (float)nEntradasTabla;

	float s = velocidad.ease(t) * tablaIncrementos[nEntradasTabla].first / velocidad.ease(1.0f);

	
	//std::cout << t << " -- " << velocidad.ease(t) << " -- " << tablaIncrementos[nEntradasTabla].first << std::endl;

	int ind = get_Indice(s);
	//float u = (float)(ind - 1) * incremento + (3 / 8) * (((float)ind * incremento) - ((float)(ind - 1) * incremento));

	//std::cout << s << " - " << ind << " - " << u << std::endl;

	//std::cout << (float)ind * incremento << std::endl;

	return desplazamiento.getPunto((float)ind * incremento);
}

float TAPMotionController::get_Twist(float t){
	float incremento = 1.0f / (float)nEntradasTabla;

	float s = velocidad.ease(t) * tablaIncrementos[nEntradasTabla].first / velocidad.ease(1.0f);

	int ind = get_Indice(s);

	return (float)ind * incremento;
}

/**
* Destructor
*/
TAPMotionController::~TAPMotionController(){}
