#include "animaciones_ferb.h"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <cmath>
#include <cstdlib>

// Variables globales
float tiempoCarrusel = 0.0f;
float ballonyTime = 0.0f;
float ferbHandTime = 0.0f;
float phineasHandTime = 0.0f;

glm::vec3 posicionesPerry[8] = {
	// Columna izquierda (m�s negativa en X)
	{-87.1f, 2.4f, -138.5f},
	{-88.25f, 2.4f, -138.5f},
	{-89.4f, 2.4f, -138.5f},
	{-90.55f, 2.4f, -138.5f},
	// Columna derecha
	{-87.1f, 2.4f, -136.5f},
	{-88.25f, 2.4f, -136.5f},
	{-89.4f, 2.4f, -136.5f},
	{-90.55f, 2.4f, -136.5f}
};


int perryActual = rand() % 8;
float perryY = 0.0f;
bool subiendo = true;
float esperaActual = 0.0f;
bool esperando = false;

float doofGolpeTime = 0.0f;
float rotBicep = 0.0f;
float rotBrazo = 0.0f;
float rotMuneca = 0.0f;

glm::vec3 dardoInicio = glm::vec3(140.0f, 8.0f, 110.0f);  // justo en la l�nea roja

glm::vec3 dardoObjetivos[3] = {
	glm::vec3(140.0f, 7.5f, 135.0f),   // Globo centro
	glm::vec3(137.5f, 10.0f, 135.0f),  // Fallo entre centro y superior izq
	glm::vec3(145.0f, 7.5f, 135.0f)    // Globo derecha
};


int dardoEstado = 0;
int tiradaActual = 0;
float tiempoEspera_dardos = 0.0f;
float tLanzamiento = 0.0f;
float duracionLanzamiento = 20.0f;
glm::vec3 posDardoActual = dardoInicio;
std::vector<glm::vec3> dardosFinales;

bool globos[3][3] = { {true, true, true}, {true, true, true}, {true, true, true} };
bool globosPonchados[3][3] = { {false, false, false}, {false, false, false}, {false, false, false} };

float rotacionDardo = 0.0f;
float velocidadRotacionDardo = 180.0f;

float posX = 0.0f;
float posY = 0.0f;
float posZ = 0.0f;

const float velocidadPerry = 0.025f;
const float alturaMax = 0.4f;
const float tiempoEspera = 4.0f;
const float tiempoArriba = 2.5f;

const float ballonySpeed = 0.01f;
const float ballonyAmplitudeY = 15.0f;
const float ballonyAmplitudeZ = 50.0f;
const float ballonyAmplitudeX = 35.0f;

void animaciones_ferb(float deltaTime) {
	// DeltaTime - Phineas & Ferb
	tiempoCarrusel += deltaTime;
	ballonyTime += deltaTime;
	ferbHandTime += deltaTime;
	phineasHandTime += deltaTime;


	// ------------------------- Animaci�n Whack a Perry ------------------------------
	if (esperando) {
		esperaActual += deltaTime;
		if (esperaActual >= tiempoEspera) {
			esperando = false;
			esperaActual = 0.0f;
			perryActual = rand() % 8;  // Cambia de hoyo
		}
	}
	else {
		if (subiendo) {
			perryY += velocidadPerry * deltaTime;
			if (perryY >= alturaMax) {
				perryY = alturaMax;
				subiendo = false;
				esperaActual = 0.0f;
			}
		}
		else {
			esperaActual += deltaTime;
			if (esperaActual >= tiempoArriba) {
				perryY -= velocidadPerry * deltaTime;
				if (perryY <= 0.0f) {
					perryY = 0.0f;
					subiendo = true;
					esperando = true;
					esperaActual = 0.0f;
				}
			}
		}
	}

	doofGolpeTime += deltaTime;

	rotBicep = 0.0f;
	rotBrazo = 0.0f;
	rotMuneca = 0.0f;

	if (doofGolpeTime >= 10.0f) rotBicep = 35.0f;
	if (doofGolpeTime >= 25.0f) rotBrazo = 35.0f;
	if (doofGolpeTime >= 35.0f) rotMuneca = 45.0f;

	// Reinicia la animaci�n despu�s de completar el ciclo
	if (doofGolpeTime >= 50.0f) doofGolpeTime = 0.0f;



	// --------------------------------------------------------------------------------


   // ------------------------------ Animaci�n Juego de los globos --------------------

	// Aqui se agrega el c�digo de actualizaci�n de deltaTime

	if (dardoEstado == 0) {
		// Inicia lanzamiento
		tLanzamiento = 0.0f;
		dardoEstado = 1;
	}
	else if (dardoEstado == 1) {
		// Interpolaci�n con glm::mix para animaci�n suave
		tLanzamiento += deltaTime;
		float t = glm::clamp(tLanzamiento / duracionLanzamiento, 0.0f, 1.0f);
		posDardoActual = glm::mix(dardoInicio, dardoObjetivos[tiradaActual], t);

		if (t >= 1.0f) {
			dardoEstado = 2;
			tiempoEspera_dardos = 0.0f;
		}
	}
	else if (dardoEstado == 2) {
		tiempoEspera_dardos += deltaTime;
		if (tiempoEspera_dardos >= 5.0f) {
			// Guardar la posici�n final
			dardosFinales.push_back(dardoObjetivos[tiradaActual]);

			//Modificar globos seg�n la tirada
			if (tiradaActual == 0) { globos[1][1] = false; globosPonchados[1][1] = true; }
			if (tiradaActual == 2) { globos[1][2] = false; globosPonchados[1][2] = true; }


			tiradaActual++;
			if (tiradaActual >= 3) {
				if (tiempoEspera_dardos >= 30.0f) {
					//Reiniciar animaci�n y restaurar globos
					tiradaActual = 0;
					dardoEstado = 0;
					posDardoActual = dardoInicio;
					dardosFinales.clear();

					//Restaurar todos los globos
					for (int i = 0; i < 3; ++i)
						for (int j = 0; j < 3; ++j) {
							globos[i][j] = true;
							globosPonchados[i][j] = false;
						}

				}
			}
			else {
				dardoEstado = 0;
				posDardoActual = dardoInicio;
			}
		}
	}



	// ----------------------------------------------------------------------------------


	// Movimiento de ballony
	posX = -50.0f + cos(ballonyTime * ballonySpeed * 0.7f) * ballonyAmplitudeX;
	posY = 150.0f + sin(ballonyTime * ballonySpeed) * ballonyAmplitudeY;
	posZ = 80.0f + sin(ballonyTime * ballonySpeed * 0.5f) * ballonyAmplitudeZ;
}