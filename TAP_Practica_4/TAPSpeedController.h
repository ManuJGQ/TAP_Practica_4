#pragma once

/**
* Clase encargada de controlar la velocidad con la que queremios
* que se mueva nuestro objeto. Esta clase se controla manejando 
* dos tiempos, k1 y k2. k1 representa el momento en el que para
* de acelerar, mientras que k2 representa el momento en el que 
* empieza a frenar. Reseumiendo:
* 
* - Instantes 0 - k1: ACELERA
* - Instantes k1 - k2: VELOCIDAD CONSTANTE
* - Instantes k2 - 1: DECELERA
*/
class TAPSpeedController{

	float k1;
	float k2;

	float f;

public:
	TAPSpeedController();
	TAPSpeedController(float _k1, float _k2);
	TAPSpeedController(const TAPSpeedController &speedcontroller);

	float ease(float t);

	void actualizarF();

	void pintarCurva();

	void set_K1(float _k1) {
		if (k1 + _k1 >= 0.0f && k1 + _k1 <= k2) {
			k1 += _k1;
			actualizarF();
		}
	}

	void set_K2(float _k2) {
		if (k2 + _k2 >= k1 && k2 + _k2 <= 1.0f) {
			k2 += _k2;
			actualizarF();
		}
	}

	~TAPSpeedController();
};

