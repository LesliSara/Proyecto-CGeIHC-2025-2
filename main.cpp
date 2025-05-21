#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include <map>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
#include "animaciones_ferb.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
float rotExtrLink;
float rotExtrLinkOffset;
bool avanza;
bool limiteExtrLink;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;
bool cambio;
int aux;

float movMandroid = -107.782f;
float movBillyBot = 30.623f;
bool cambioMandroid;
bool cambioBillyBot;

// ------ ANIMACIÓN DE DADOS ------
glm::vec3 posDado1(-6.75f, 4.304f, 2.008f);
glm::vec3 posDado2(-6.75f, 4.304f, 3.5f);
glm::vec3 rotDado1(0.0f); // en grados
glm::vec3 rotDado2(0.0f);
float velYDados = 10.0f;
int rebotesDados = 0;
bool dadosLanzados = false;

//------- ANIMACIÓN DE LA HOZ ------

static float avanceHoz = 0.0f;
static float rotacionHoz = 0.0f;
static float tiempoImpactoHoz = 0.0f;
static bool lanzandoHoz = false;
static bool impactoHoz = false;

// ------ ANIMACIÓN BOMBA (BOLA DE BOLICHE) ------
glm::vec3 posBomba(3.5f, -5.2f, 30.60f); // posición inicial (ajusta según tu pista)
glm::vec3 velBomba(0.0f, 0.0f, 0.0f);
float velInicialBomba = -35.0f; // velocidad en z (hacia los pinos)
float velYBomba = 0.0f;
float gravedadBomba = -40.0f;
int rebotesBomba = 0;
bool bombaLanzada = false;




Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;



Texture pastoTexture;
Texture Topos;
Texture JuegoTopos;

Texture LetrasTexture;


Model Arbol_Hojas_M;
Model Arbol_Tronco_M;
Model Tronco_Hojas_M;
Model Tronco_Tronco_M;

Model Luz_M;
Model Banco_M;
Model Mesa_Banco_M;
Model BañoM_M;
Model BañoH_M;
Model Miche_M;
Model HotDog_M;
Model Nieves_M;
Model Cotton_Candy_M;
Model Palomitas_M;


//PINOS
Model Bomba_M;
Model Linea_M;
Model Pantalla_M;
Model Pino_M;
// JAULA BATEO
Model Bola_M;
Model Caja_M;
Model Campo_M;
Model Cofre_M;
Model Espada_M;
Model Reflector_M;
Model Reja_M;
// HOCEEEEES
Model Banda_M;
Model BlancoD_M;
Model BlancoI_M;
Model CarpaH_M;
Model Hoz_M;
//
// DADOOOOOOOS
Model CarpaD_M;
Model Dado_M;
Model Letrero1_M;
Model Letrero2_M;
Model MesaD_M;
Model PelucheD_M;
Model RepisaR_M;

//Link
Model CabezaLink_M;
Model CuerpoLink_M;
Model SombreroLink_M;
Model BotaDerLink_M;
Model BotaIzqLink_M;
Model BrazoDerLink_M;
Model BrazoIzqLink_M;
Model PiernaDerLink_M;
Model PiernaIzqLink_M;
Model VainaLink_M;

//GUMBAAAL
Model Gumball_Carro_M;
Model Carrie_Krueger_M;
Model Gumball_M;
Model Darwin_M;
Model Penny_M;
Model Pork_Cassidy_M;
Model Teri_M;
Model Puerta_M;
Model Letrero_M;

// BillyBot
Model BillyBotAbdomen_M;
Model BillyBotAntena_M;
Model BillyBotBrazoDerecho_M;
Model BillyBotBrazoIzquierdo_M;
Model BillyBotCuerpo_M;
Model BillyBotNariz_M;
Model BillyBotOjoIzquierdo_M;
Model BillyBotPiernaDerecha_M;
Model BillyBotPiernaIzquierda_M;
Model BillyBotPinzaSuperiorIzquierda_M;
Model BillyBotPinzaSuperiorDerecha_M;
Model BillyBotPinzaInferiorIzquierda_M;
Model BillyBotPinzaInferiorDerecha_M;


//Mandroid
Model MandroidCuerpo_M;
Model MandroidCabeza_M;
Model MandroidBrazoIzquierdo_M;
Model MandroidBrazoDerecho_M;
Model MandroidManoDerecha_M;
Model MandroidManoIzquierda_M;
Model MandroidPieIzquierdo_M;
Model MandroidPieDerecho_M;
Model MandroidPiernaIzquierda_M;
Model MandroidPiernaDerecha_M;

//********************************MODELOS PHINEAS Y FERB***********************************
//Modelos Phineas y Ferb
Model edificioDoof_M;
Model Ferb_M;
Model Perry_M;
Model Phineas_M;
Model Candace_M;
Model Isabella_M;
Model Bufard_M;
Model Baljeet_M;
Model Doof_M;
Model Doof_bicep_M;
Model Doof_brazo_M;
Model Doof_muneca_M;
Model topo_machine_M;
Model planty_M;
Model ballony_M;
Model phineasHouse_M;
Model reja_madera_M;
Model arbol_phineas_M;
Model carrusel_M;
Model carpa_perry_M;
Model mesa_perry_M;
Model letrero_perry_juego_M;
Model techo_carrusel_M;
Model nave1_M;
Model nave2_M;
Model nave3_M;
Model nave4_M;
Model nave5_M;
Model nave6_M;
Model toilet_phineas_M;
Model decoracion_M;
Model puesto_tacos_M;
Model puesto_miches_M;
Model Ferb_mano_M;
Model Phineas_mano_M;
Model Mazo_M;
Model carpa_globo_M;
Model globo_M;
Model dardo_M;
Model linea_roja_M;
Model globo_ponchado_M;


Model _M;
Skybox skybox;



//materiales
Material Material_brillante;
Material Material_opaco;


Material Material_WindWaker;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;
static float acumuladorr = 0.0f;
//Variables texto
std::string textoActual = "PROYECTO CGEIHC"; // Texto inicial
float tiempoRotacion = 0.5f; // Tiempo entre rotaciones (en segundos)
float tiempoUltimaRotacion = 0.0f;
// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};
	//Piso que mide 20 unidades
	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	1.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		1.0f, 1.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj1);

	//aggarra solo una region letra
	unsigned int letraIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat letraVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.00f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.11f, 0.00f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.11f, 0.33f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 0.33f,		    0.0f, -1.0f, 0.0f,

	};

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(letraVertices, letraIndices, 32, 6);
	meshList.push_back(obj2);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}





std::map<char, glm::vec4> letraUVs;
void InicializarMapaLetras() {
	int columnas = 9;
	int filas = 3;
	float anchoCelda = 1.0f / columnas;
	float altoCelda = 1.0f / filas;

	std::string letras = "ABCDEFGHI"
		"JKLMNOPQR"
		"STUVWXYZ";

	for (int fila = 0; fila < filas; ++fila) {
		for (int columna = 0; columna < columnas; ++columna) {
			char letra = letras[fila * columnas + columna];
			float u_min = columna * anchoCelda;
			float v_min = 1.0f - (fila + 1) * altoCelda; // Desde la parte superior
			float u_max = (columna + 1) * anchoCelda;
			float v_max = 1.0f - fila * altoCelda;

			letraUVs[letra] = glm::vec4(u_min, v_min, u_max, v_max);

		}
	}
}



void RenderTextoEstatico(const std::string& texto, glm::vec3 posicionInicial,
	float separacion, GLuint uniformModel, GLuint uniformTextureOffset) {
	for (size_t i = 0; i < texto.size(); ++i) {
		char letra = texto[i];

		// Verifica si la letra está en el mapa de UVs
		if (letraUVs.find(letra) == letraUVs.end()) continue;

		glm::vec4 uv = letraUVs[letra]; // Coordenadas UV de la letra
		glm::vec2 toffset = glm::vec2(uv.x, uv.y);

		// Calcula la posición de la letra
		glm::vec3 posicionLetra = posicionInicial + glm::vec3(0.0f, 0.0f, i * separacion);

		// Renderiza la letra
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, posicionLetra);
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f)); // Rotación al plano XY
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación al plano XY
		model = glm::scale(model, glm::vec3(1.4f, 4.5f, 4.5f)); // Aplica la escala
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		LetrasTexture.UseTexture();
		meshList[1]->RenderMesh(); // Usa un plano para renderizar la letra
	}
}

std::string RotarTexto(const std::string& texto) {
	if (texto.empty()) return texto; // Si el texto está vacío, no hacer nada
	return texto.substr(1) + texto[0]; // Mueve la primera letra al final
}

void actualizarAnimacionDados(float deltaTime) {
	if (!dadosLanzados) return;

	if (rebotesDados > 0) {
		// Movimiento vertical tipo rebote
		posDado1.y += velYDados * deltaTime;
		posDado2.y += velYDados * deltaTime;
		rotDado1 += glm::vec3(110.0f, 140.0f, 100.0f) * deltaTime;
		rotDado2 += glm::vec3(120.0f, 135.0f, 80.0f) * deltaTime;

		// Rebote en la "mesa" (y = 4.304)
		if (posDado1.y <= 4.304f) {
			posDado1.y = 4.304f;
			posDado2.y = 4.304f;
			velYDados *= -0.55f; // rebote con pérdida de energía
			rebotesDados--;
		}
		velYDados -= 18.0f * deltaTime; // gravedad
	}
	else {
		dadosLanzados = false; // Detener cuando termine de rebotar
	}
}

void lanzarDados() {
	if (!dadosLanzados) {
		posDado1 = glm::vec3(-6.75f, 8.304f, 2.008f); // inicia más arriba para que caigan
		posDado2 = glm::vec3(-6.75f, 8.304f, 3.5f);
		rotDado1 = glm::vec3(0.0f);
		rotDado2 = glm::vec3(0.0f);
		velYDados = 12.0 + float(rand() % 6); // aleatorio entre 12 y 17
		rebotesDados = 7;
		dadosLanzados = true;
	}
}

void lanzarHoz() {
	if (!lanzandoHoz) {
		lanzandoHoz = true;
		impactoHoz = false;
		tiempoImpactoHoz = 0.0f;
		avanceHoz = 0.0f;
		rotacionHoz = 0.0f;
	}
}

void actualizarHoz(float deltaTime) {
	if (lanzandoHoz) {
		if (!impactoHoz) {
			if (avanceHoz < 50.0f) {
				avanceHoz += 5.0f * deltaTime;
				rotacionHoz += 720.0f * deltaTime;
			}
			else {
				tiempoImpactoHoz += deltaTime;
				if (tiempoImpactoHoz >= 3.0f) {
					lanzandoHoz = false;
					impactoHoz = false;
					tiempoImpactoHoz = 0.0f;
					avanceHoz = 0.0f;
					rotacionHoz = 0.0f;
				}
				else {
					impactoHoz = true;
				}
			}
		}
		else {
			tiempoImpactoHoz += deltaTime;
			if (tiempoImpactoHoz >= 3.0f) {
				lanzandoHoz = false;
				impactoHoz = false;
				tiempoImpactoHoz = 0.0f;
				avanceHoz = 0.0f;
				rotacionHoz = 0.0f;
			}
		}
	}
}






int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();


	CreateObjects();
	CreateShaders();
	InicializarMapaLetras();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);


	pastoTexture = Texture("Textures/pastoCamino.tga");
	pastoTexture.LoadTextureA();

	Arbol_Hojas_M = Model();
	Arbol_Hojas_M.LoadModel("Models/Arboles/Arbol/Arbol_Hojas.obj");
	Arbol_Tronco_M = Model();
	Arbol_Tronco_M.LoadModel("Models/Arboles/Arbol/Arbol_Tronco.obj");
	Tronco_Hojas_M = Model();
	Tronco_Hojas_M.LoadModel("Models/Arboles/Tronco/Tronco_Hojas.obj");
	Tronco_Tronco_M = Model();
	Tronco_Tronco_M.LoadModel("Models/Arboles/Tronco/Tronco_Tronco.obj");
	Mesa_Banco_M = Model();
	Mesa_Banco_M.LoadModel("Models/Mesa-Banco/Mesa_Banco.obj");
	Banco_M = Model();
	Banco_M.LoadModel("Models/Banco/Banco.obj");
	BañoH_M = Model();
	BañoH_M.LoadModel("Models/Baños/Hombre/bañoH.obj");
	BañoM_M = Model();
	BañoM_M.LoadModel("Models/Baños/Mujer/bañoM.obj");
	Miche_M = Model();
	Miche_M.LoadModel("Models/Miche/micheladas.obj");

	HotDog_M = Model();
	HotDog_M.LoadModel("Models/Food/Carro_Hotdog.obj");
	Nieves_M = Model();
	Nieves_M.LoadModel("Models/Food/Carro_Helado.obj");
	Cotton_Candy_M = Model();
	Cotton_Candy_M.LoadModel("Models/Food/Carro_AlgodonAzucar.obj");
	Palomitas_M = Model();
	Palomitas_M.LoadModel("Models/Food/Carro_Palomitas.obj");

	//bolos

	Bomba_M = Model();
	Bomba_M.LoadModel("Models/Boliche/Bomba/bomba.obj");
	Linea_M = Model();
	Linea_M.LoadModel("Models/Boliche/Linea/linea.obj");
	Pantalla_M = Model();
	Pantalla_M.LoadModel("Models/Boliche/Pantalla/pantalla.obj");
	Pino_M = Model();
	Pino_M.LoadModel("Models/Boliche/Pino/pino.obj");
	//Jaula de bateo
	Bola_M = Model();
	Bola_M.LoadModel("Models/JaulaBateo/Bola/pinecone.obj");
	Caja_M = Model();
	Caja_M.LoadModel("Models/JaulaBateo/Caja/caja.obj");
	Campo_M = Model();
	Campo_M.LoadModel("Models/JaulaBateo/Campo/campo.obj");
	Cofre_M = Model();
	Cofre_M.LoadModel("Models/JaulaBateo/Cofre/cofre.obj");
	Espada_M = Model();
	Espada_M.LoadModel("Models/JaulaBateo/Espada/espada.obj");
	Reflector_M = Model();
	Reflector_M.LoadModel("Models/JaulaBateo/Reflector/reflector.obj");
	Reja_M = Model();
	Reja_M.LoadModel("Models/JaulaBateo/Reja/reja.obj");
	//HOCEEES
	Banda_M = Model();
	Banda_M.LoadModel("Models/Hoces/Banda/bandaHoces.obj");
	BlancoD_M = Model();
	BlancoD_M.LoadModel("Models/Hoces/Blancos/BlancoDerechoHoces.obj");
	BlancoI_M = Model();
	BlancoI_M.LoadModel("Models/Hoces/Blancos/BlancoIzquierdoHoces.obj");
	CarpaH_M = Model();
	CarpaH_M.LoadModel("Models/Hoces/Carpa/CarpaHoces.obj");
	Hoz_M = Model();
	Hoz_M.LoadModel("Models/Hoces/Hoz/Hoz.obj");
	// DADOOOOOOOOOD
	CarpaD_M = Model();
	CarpaD_M.LoadModel("Models/Dados/Carpa_Dados.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Models/Dados/Dado.obj");
	Letrero1_M = Model();
	Letrero1_M.LoadModel("Models/Dados/Letrero1.obj");
	Letrero2_M = Model();
	Letrero2_M.LoadModel("Models/Dados/Letrero2.obj");
	MesaD_M = Model();
	MesaD_M.LoadModel("Models/Dados/Mesa_Dados.obj");
	PelucheD_M = Model();
	PelucheD_M.LoadModel("Models/Dados/Peluches.obj");
	RepisaR_M = Model();
	RepisaR_M.LoadModel("Models/Dados/Repisa_Roja.obj");



	//link
	CabezaLink_M = Model();
	CabezaLink_M.LoadModel("Models/Link/cabeza.obj");
	CuerpoLink_M = Model();
	CuerpoLink_M.LoadModel("Models/Link/cuerpo.obj");
	BrazoDerLink_M = Model();
	BrazoDerLink_M.LoadModel("Models/Link/brazo_der.obj");
	BrazoIzqLink_M = Model();
	BrazoIzqLink_M.LoadModel("Models/Link/brazo_izq.obj");
	PiernaDerLink_M = Model();
	PiernaDerLink_M.LoadModel("Models/Link/pierna_der.obj");
	PiernaIzqLink_M = Model();
	PiernaIzqLink_M.LoadModel("Models/Link/pierna_izq.obj");
	VainaLink_M = Model();
	VainaLink_M.LoadModel("Models/Link/vaina.obj");
	SombreroLink_M = Model();
	SombreroLink_M.LoadModel("Models/Link/sombrero.obj");



	//GUMABALLL
	Gumball_Carro_M = Model();
	Gumball_Carro_M.LoadModel("Models/Gumball-Car/Gumball-Car.obj");
	Carrie_Krueger_M = Model();
	Carrie_Krueger_M.LoadModel("Models/Carrie-Krueger/Carrie-Krueger.obj");
	Gumball_M = Model();
	Gumball_M.LoadModel("Models/Gumball/gumball.obj");
	Darwin_M = Model();
	Darwin_M.LoadModel("Models/Darwin/Darwin.obj");
	Penny_M = Model();
	Penny_M.LoadModel("Models/Penny/pennyM.obj");
	Pork_Cassidy_M = Model();
	Pork_Cassidy_M.LoadModel("Models/Pork-Cassidy/Pork-Cassidy.obj");
	Teri_M = Model();
	Teri_M.LoadModel("Models/Teri/Teri.obj");

	// Billy Bot
	BillyBotCuerpo_M = Model();
	BillyBotCuerpo_M.LoadModel("Models/BillyBot/BillyBot/Cuerpo/cuerpo.obj");

	BillyBotAbdomen_M = Model();
	BillyBotAbdomen_M.LoadModel("Models/BillyBot/BillyBot/Abdomen/abdomen.obj");

	BillyBotAntena_M = Model();
	BillyBotAntena_M.LoadModel("Models/BillyBot/BillyBot/Antena/antena.obj");

	BillyBotBrazoDerecho_M = Model();
	BillyBotBrazoDerecho_M.LoadModel("Models/BillyBot/BillyBot/Brazos/brazoDerecho.obj");
	BillyBotBrazoIzquierdo_M = Model();
	BillyBotBrazoIzquierdo_M.LoadModel("Models/BillyBot/BillyBot/Brazos/brazoIzquierdo.obj");

	BillyBotNariz_M = Model();
	BillyBotNariz_M.LoadModel("Models/BillyBot/BillyBot/Nariz/nariz.obj");
	BillyBotOjoIzquierdo_M = Model();
	BillyBotOjoIzquierdo_M.LoadModel("Models/BillyBot/BillyBot/OjoIzquierdo/ojoIzquierdo.obj");
	BillyBotPiernaDerecha_M = Model();
	BillyBotPiernaDerecha_M.LoadModel("Models/BillyBot/BillyBot/Piernas/piernaDerecha.obj");

	BillyBotPiernaIzquierda_M = Model();
	BillyBotPiernaIzquierda_M.LoadModel("Models/BillyBot/BillyBot/Piernas/piernaIzquierda.obj");
	BillyBotPinzaSuperiorIzquierda_M = Model();
	BillyBotPinzaSuperiorIzquierda_M.LoadModel("Models/BillyBot/BillyBot/Pinzas/pinzaIzquierdaSuperior.obj");
	BillyBotPinzaSuperiorDerecha_M = Model();
	BillyBotPinzaSuperiorDerecha_M.LoadModel("Models/BillyBot/BillyBot/Pinzas/pinzaDerechaSuperior.obj");
	BillyBotPinzaInferiorIzquierda_M = Model();
	BillyBotPinzaInferiorIzquierda_M.LoadModel("Models/BillyBot/BillyBot/Pinzas/pinzaIzquierdaInferior.obj");

	BillyBotPinzaInferiorDerecha_M = Model();
	BillyBotPinzaInferiorDerecha_M.LoadModel("Models/BillyBot/BillyBot/Pinzas/pinzaDerechaInferior.obj");

	// Mandroid
	MandroidCuerpo_M = Model();
	MandroidCuerpo_M.LoadModel("Models/Mandroid/Mandroid/Cuerpo/cuerpo.obj");

	MandroidCabeza_M = Model();
	MandroidCabeza_M.LoadModel("Models/Mandroid/Mandroid/Cara/cabeza.obj");

	MandroidBrazoDerecho_M = Model();
	MandroidBrazoDerecho_M.LoadModel("Models/Mandroid/Mandroid/Brazos/brazoDerecho.obj");
	MandroidBrazoIzquierdo_M = Model();
	MandroidBrazoIzquierdo_M.LoadModel("Models/Mandroid/Mandroid/Brazos/brazoIzquierdo.obj");

	MandroidPiernaDerecha_M = Model();
	MandroidPiernaDerecha_M.LoadModel("Models/Mandroid/Mandroid/Piernas/piernaDerecha.obj");
	MandroidPiernaIzquierda_M = Model();
	MandroidPiernaIzquierda_M.LoadModel("Models/Mandroid/Mandroid/Piernas/piernaIzquierda.obj");

	MandroidManoIzquierda_M = Model();
	MandroidManoIzquierda_M.LoadModel("Models/Mandroid/Mandroid/Manos/manoIzquierda.obj");
	MandroidManoDerecha_M = Model();
	MandroidManoDerecha_M.LoadModel("Models/Mandroid/Mandroid/Manos/manoDerecha.obj");

	MandroidPieIzquierdo_M = Model();
	MandroidPieIzquierdo_M.LoadModel("Models/Mandroid/Mandroid/Pies/pieIzquierdo.obj");

	MandroidPieDerecho_M = Model();
	MandroidPieDerecho_M.LoadModel("Models/Mandroid/Mandroid/Pies/pieDerecho.obj");

	// ----------------------------------------------------------------------------------------------------------------------------------
   // ----------------------------------------- UNIVERSO PHINEAS & FERB - MODELOS ------------------------------------------------------
   // ----------------------------------------------------------------------------------------------------------------------------------

	edificioDoof_M = Model();
	edificioDoof_M.LoadModel("Models/Ferb/EdificioDoof.obj");
	Ferb_M = Model();
	Ferb_M.LoadModel("Models/Ferb/ferb.obj");
	Perry_M = Model();
	Perry_M.LoadModel("Models/Ferb/perry.obj");
	Phineas_M = Model();
	Phineas_M.LoadModel("Models/Ferb/phineas.obj");
	Candace_M = Model();
	Candace_M.LoadModel("Models/Ferb/candace.obj");
	Isabella_M = Model();
	Isabella_M.LoadModel("Models/Ferb/isabella.obj");
	Baljeet_M = Model();
	Baljeet_M.LoadModel("Models/Ferb/baljeet.obj");
	Bufard_M = Model();
	Bufard_M.LoadModel("Models/Ferb/bufard.obj");
	Doof_M = Model();
	Doof_M.LoadModel("Models/Ferb/doof.obj");
	Doof_bicep_M = Model();
	Doof_bicep_M.LoadModel("Models/Ferb/doof_bicep.obj");
	Doof_brazo_M = Model();
	Doof_brazo_M.LoadModel("Models/Ferb/doof_brazo.obj");
	Doof_muneca_M = Model();
	Doof_muneca_M.LoadModel("Models/Ferb/doof_muneca.obj");
	topo_machine_M = Model();
	topo_machine_M.LoadModel("Models/Ferb/topo_machine.obj");
	planty_M = Model();
	planty_M.LoadModel("Models/Ferb/planty.obj");
	ballony_M = Model();
	ballony_M.LoadModel("Models/Ferb/balloony.obj");
	phineasHouse_M = Model();
	phineasHouse_M.LoadModel("Models/Ferb/phineasHouse.obj");
	reja_madera_M = Model();
	reja_madera_M.LoadModel("Models/Ferb/reja_madera.obj");
	arbol_phineas_M = Model();
	arbol_phineas_M.LoadModel("Models/Ferb/arbol_phineas.obj");
	carrusel_M = Model();
	carrusel_M.LoadModel("Models/Ferb/carrusel.obj");
	techo_carrusel_M = Model();
	techo_carrusel_M.LoadModel("Models/Ferb/techo_carrusel.obj");
	nave1_M = Model();
	nave1_M.LoadModel("Models/Ferb/nave1.obj");
	nave2_M = Model();
	nave2_M.LoadModel("Models/Ferb/nave2.obj");
	nave3_M = Model();
	nave3_M.LoadModel("Models/Ferb/nave3.obj");
	nave4_M = Model();
	nave4_M.LoadModel("Models/Ferb/nave4.obj");
	nave5_M = Model();
	nave5_M.LoadModel("Models/Ferb/nave5.obj");
	nave6_M = Model();
	nave6_M.LoadModel("Models/Ferb/nave6.obj");
	carpa_perry_M = Model();
	carpa_perry_M.LoadModel("Models/Ferb/carpa_perry.obj");
	mesa_perry_M = Model();
	mesa_perry_M.LoadModel("Models/Ferb/mesa_perry.obj");
	letrero_perry_juego_M = Model();
	letrero_perry_juego_M.LoadModel("Models/Ferb/letrero_perry_juego.obj");
	toilet_phineas_M = Model();
	toilet_phineas_M.LoadModel("Models/Ferb/toilet_phineas.obj");
	decoracion_M = Model();
	decoracion_M.LoadModel("Models/Ferb/decoracion.obj");
	puesto_tacos_M = Model();
	puesto_tacos_M.LoadModel("Models/Ferb/puesto_tacos.obj");
	puesto_miches_M = Model();
	puesto_miches_M.LoadModel("Models/Ferb/puesto_miches.obj");
	Ferb_mano_M = Model();
	Ferb_mano_M.LoadModel("Models/Ferb/ferb_mano_der.obj");
	Phineas_mano_M = Model();
	Phineas_mano_M.LoadModel("Models/Ferb/phineas_mano_izq.obj");
	carpa_globo_M = Model();
	carpa_globo_M.LoadModel("Models/Ferb/carpa_globos.obj");
	globo_M = Model();
	globo_M.LoadModel("Models/Ferb/globo.obj");
	dardo_M = Model();
	dardo_M.LoadModel("Models/Ferb/dardo.obj");
	linea_roja_M = Model();
	linea_roja_M.LoadModel("Models/Ferb/linea_roja.obj");
	globo_ponchado_M = Model();
	globo_ponchado_M.LoadModel("Models/Ferb/globo_ponchado.obj");
	//--------------------------------------------------------------



	Puerta_M = Model();
	Puerta_M.LoadModel("Models/puerta.obj");
	Letrero_M = Model();
	Letrero_M.LoadModel("Models/letrero.obj");


	LetrasTexture = Texture("Textures/letras.png");
	LetrasTexture.LoadTextureA();





	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cube_right.png");
	skyboxFaces.push_back("Textures/Skybox/cube_left.png");
	skyboxFaces.push_back("Textures/Skybox/cube_down.png");
	skyboxFaces.push_back("Textures/Skybox/cube_up.png");
	skyboxFaces.push_back("Textures/Skybox/cube_back.png");
	skyboxFaces.push_back("Textures/Skybox/cube_front.png");

	skybox = Skybox(skyboxFaces);

	Material_WindWaker = Material(0.0f, 1);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);
	//contador de luces puntuales




	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	movCoche = 0.0f;
	movOffset = 0.01f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;
	rotExtrLink = 0.0f;
	rotExtrLinkOffset = 2.5f;
	cambio = true;
	limiteExtrLink = true;
	cambioMandroid = true;
	cambioBillyBot = true;


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;
		acumuladorr += deltaTime;


		angulovaria += 0.5f * deltaTime;

		//ANIMACION DE LAS EXTREMIDADES DE LINK
		if (mainWindow.getmovimientoLink() == 1) {
			if (limiteExtrLink)
			{
				if (rotExtrLink > -40.0f)
					rotExtrLink -= rotExtrLinkOffset * deltaTime;
				else
					limiteExtrLink = false;
			}
			else
			{
				if (rotExtrLink < 40.0f)
					rotExtrLink += rotExtrLinkOffset * deltaTime;
				else
					limiteExtrLink = true;
			}
		}

		animaciones_ferb(deltaTime); //animaciones ferb

		// --- Animación de Dados ---
		actualizarAnimacionDados(deltaTime);

		// --- Animación de Hoz ---
		actualizarHoz(deltaTime);


		// Detección de flanco para la tecla U
		static bool uKeyPrev = false;
		bool uKeyNow = mainWindow.getsKeys()[GLFW_KEY_U];
		if (uKeyNow && !uKeyPrev) {
			lanzarDados();
			lanzarHoz();
		}
		uKeyPrev = uKeyNow;


		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 posInicial(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::mat4 modelBillyBot(1.0);


		//Este se hace dentro del while
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 20.0f));     //escalamos el piso por 30 (ahora mide 600 unidades)
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pastoTexture.UseTexture();

		meshList[0]->RenderMesh();

		//Puestos de comida
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 5.52f, 150.0f));
		model = glm::scale(model, glm::vec3(1.35f, 1.35f, 1.35f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		HotDog_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, 5.52f, 135.0f));
		model = glm::scale(model, glm::vec3(1.35f, 1.35f, 1.35f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Nieves_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 3.2f, -10.0f));
		model = glm::scale(model, glm::vec3(1.35f, 1.35f, 1.35f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cotton_Candy_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 5.6f, -10.0f));
		model = glm::scale(model, glm::vec3(1.35f, 1.35f, 1.35f));
		//model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Palomitas_M.RenderModel();




		//HOCEEEEES
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-102.0f, -2.0f, 150.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CarpaH_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(12.91f, 16.078f, -17.016f + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BlancoD_M.RenderModel();
			model = glm::translate(model, glm::vec3(-25.50f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BlancoI_M.RenderModel();
			model = modelaux;

			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Banda_M.RenderModel();
			model = modelaux;
			//oces del lado izquierdo 
			modelaux = model;
			model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 15.504 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 8.452 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-23.691f, 11.312f, 1.1633 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-23.691f, 11.312f, -5.494 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			// oc s lado derecho
			modelaux = model;
			model = glm::translate(model, glm::vec3(23.656f, 11.312f, 15.504 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(23.656f, 11.312f, 8.452 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(23.656f, 11.312f, 1.1633 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(23.656f, 11.312f, -5.494 + 1.95f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(-10.656f, 6.312f, 20.494f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -avanceHoz));
			model = glm::rotate(model, glm::radians(-rotacionHoz), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(10.656f, 6.312f, 20.494f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -avanceHoz));
			model = glm::rotate(model, glm::radians(-rotacionHoz), glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Hoz_M.RenderModel();
			model = modelaux;
		}


		//DADOOOOOS
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(230.0f, -1.80f, -30.0f));
			model = glm::scale(model, glm::vec3(1.7f, 1.7f, 1.7f));
			model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			CarpaD_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(-6.75f, 4.304f, 2.008f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MesaD_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(-6.979f, 7.912f, -7.926f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Letrero1_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(8.825f, 6.124f, -4.528f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Letrero2_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(8.904f, 2.179f, 2.815f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			RepisaR_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(8.526f, 3.183f, 3.698f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			PelucheD_M.RenderModel();
			model = modelaux;

			// DADO 1 (ANIMADO)
			modelaux = model;
			model = glm::translate(model, posDado1);
			model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
			model = glm::rotate(model, glm::radians(rotDado1.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(rotDado1.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotDado1.z), glm::vec3(0, 0, 1));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Dado_M.RenderModel();
			model = modelaux;

			// DADO 2 (ANIMADO)
			modelaux = model;
			model = glm::translate(model, posDado2);
			model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
			model = glm::rotate(model, glm::radians(rotDado2.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(rotDado2.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotDado2.z), glm::vec3(0, 0, 1));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Dado_M.RenderModel();
			model = modelaux;


		}





		// LINK
		{
			// ---------- LINK ----------

			//Cuerpo
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmuevex(), 3.85f, 0.0f + mainWindow.getmuevez()));
			model = glm::scale(model, glm::vec3(2.2f, 2.2f, 2.2f));
			model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			posInicial = model;
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			CuerpoLink_M.RenderModel();
			//Pierna derecha
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.437f, -0.93f, -0.045f));
			model = glm::rotate(model, rotExtrLink * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			PiernaDerLink_M.RenderModel();
			//Pierna izquierda
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.437f, -0.93f, -0.045f));
			model = glm::rotate(model, rotExtrLink * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			PiernaIzqLink_M.RenderModel();
			//Vaina
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.7f));
			model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0, 1.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			VainaLink_M.RenderModel();
			//Brazo derecho
			model = modelaux;
			model = glm::translate(model, glm::vec3(-0.78f, 0.85f, -0.13f));
			model = glm::rotate(model, rotExtrLink * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BrazoDerLink_M.RenderModel();
			//Brazo izquierdo
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.8f, 0.865f, -0.13f));
			model = glm::rotate(model, rotExtrLink * toRadians, glm::vec3(-1.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			BrazoIzqLink_M.RenderModel();
			//Cabeza
			model = posInicial;
			model = glm::translate(model, glm::vec3(0.0f, 1.02f, -0.12f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			modelaux = model;
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			CabezaLink_M.RenderModel();
			glDisable(GL_BLEND);
			//Sombrero
			model = modelaux;
			model = glm::translate(model, glm::vec3(0.0f, 1.4f, -0.02f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Material_WindWaker.UseMaterial(uniformSpecularIntensity, uniformShininess);
			SombreroLink_M.RenderModel();
		}

		// Micheladas
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-220.0f, -2.5f, 122.0f));
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Miche_M.RenderModel();
		}

		//Baño 1
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-150.0f, 6.85f, 100.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}

		//Baño 2
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-180.0f, 6.85f, 0.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Baño 3
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-35.0f, 6.85f, 80.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Baño 4
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-20.0f, 6.85f, -160.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Baño 5
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(130.0f, 6.85f, 10.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Baño 6
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(215.0f, 6.85f, 95.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}
		//Baño 7
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(210.0f, 6.85f, -110.0f));
			model = glm::scale(model, glm::vec3(1.4f, 1.4f, 1.4f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoM_M.RenderModel();
			model = glm::translate(model, glm::vec3(-7.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BañoH_M.RenderModel();
		}


		//Bancos

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 1.21f, -10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-70.0f, 1.21f, -10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 1.21f, -10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 1.21f, -10.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 1.21f, 140.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 1.21f, 130.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-170.0f, 1.21f, -45.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-50.0f, 1.21f, -45.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, 1.21f, -45.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(170.0f, 1.21f, -45.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 1.21f, -150.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(210.0f, 1.21f, -150.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 1.21f, 50.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(250.0f, 1.21f, -100.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		model = glm::rotate(model, 270 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Banco_M.RenderModel();

		//Banca con mesa

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, 3.6f, 80.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, 3.6f, 80.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-190.0f, 3.6f, 50.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-130.0f, 3.6f, 50.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, 3.6f, -100.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-110.0f, 3.6f, -100.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, 3.6f, -60.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-150.0f, 3.6f, -60.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-40.0f, 3.6f, 20.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 3.6f, -60.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 3.6f, -60.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 3.6f, -100.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, 3.6f, -90.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(160.0f, 3.6f, -100.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(60.0f, 3.6f, 20.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.0f, 3.6f, 80.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(130.0f, 3.6f, 40.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(200.0f, 3.6f, 70.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mesa_Banco_M.RenderModel();



		// GUMBALL
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-220.0f, -2.15f, -50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(8.0f, 8.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gumball_Carro_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 1.08f, 50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Gumball_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, 4.1f, -50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Teri_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(120.0f, 5.0f, 70.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Penny_M.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-120.0f, -2.0f, 20.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.8f, 2.8f, 2.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Pork_Cassidy_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(180.0f, 2.60f, 50.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(25.0f, 25.0f, 25.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Darwin_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, 5.0f, -30.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.65f, 0.65f, 0.65f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Carrie_Krueger_M.RenderModel();

		//BillyBot
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(231.25f, -2.1f, movBillyBot));
			if (cambioBillyBot) {
				if (movBillyBot <= 116.593f) {

					movBillyBot += 0.01f;
				}
				else {
					cambioBillyBot = false;
				}
			}
			else {
				if (movBillyBot >= 30.623f) {
					movBillyBot -= 0.01f;
					model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
				}
				else {
					cambioBillyBot = true;
				}
			}
			model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotCuerpo_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, 2.623f, 1.148f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotAbdomen_M.RenderModel();
			model = modelaux;


			// Brazos y Pinzas
			{
				modelBillyBot = model;
				model = glm::translate(model, glm::vec3(-0.91f, 2.557f, -0.804f));
				model = glm::rotate(model, 2.0f * angulovaria * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotBrazoDerecho_M.RenderModel();


				modelaux = model;
				model = glm::translate(model, glm::vec3(-1.593f, -0.004f, -0.027f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotPinzaSuperiorDerecha_M.RenderModel();
				model = modelaux;
				model = glm::translate(model, glm::vec3(-1.583f, 0.001f, -0.012f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotPinzaInferiorDerecha_M.RenderModel();
				model = modelBillyBot;


				modelBillyBot = model;
				model = glm::translate(model, glm::vec3(0.935f, 2.557f, -0.804f));
				model = glm::rotate(model, 2.0f * angulovaria * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotBrazoIzquierdo_M.RenderModel();


				modelaux = model;
				model = glm::translate(model, glm::vec3(1.569f, 0.009f, -0.018f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotPinzaSuperiorIzquierda_M.RenderModel();
				model = modelaux;


				model = glm::translate(model, glm::vec3(1.572f, 0.008f, 0.01f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				BillyBotPinzaInferiorIzquierda_M.RenderModel();
				model = modelBillyBot;
			}
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.628f, 6.28f, 3.425f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotNariz_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.498f, 6.755f, 0.574f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotOjoIzquierdo_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.6f, 0.034f, -0.922f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f * sin(angulovaria * 0.1f)));
			model = glm::translate(model, glm::vec3(0.0f, abs(0.5f * cos(angulovaria * 0.1f)), 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotPiernaDerecha_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.656f, 0.034f, -0.834f));
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f * sin((angulovaria * 0.1f) + (180.0 * toRadians))));
			model = glm::translate(model, glm::vec3(0.0f, abs(0.5f * cos(angulovaria * 0.1f)), 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotPiernaIzquierda_M.RenderModel();
			model = modelaux;

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, 8.188f, -1.285f));
			model = glm::rotate(model, 2.0f * angulovaria * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			BillyBotAntena_M.RenderModel();
			model = modelaux;

		}

		{}


		//Mandroid
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(-86.99f, 1.494f, movMandroid));
			if (cambioMandroid) {
				if (movMandroid <= -39.049f) {
					movMandroid += 0.01f;
				}
				else {
					cambioMandroid = false;
				}
			}
			else {
				if (movMandroid >= -107.782f) {
					movMandroid -= 0.01f;
					model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, -1.0f, 0.0f));
				}
				else {
					cambioMandroid = true;
				}
			}
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MandroidCuerpo_M.RenderModel();

			modelaux = model;
			model = glm::translate(model, glm::vec3(-0.004f, 0.986f, 0.025f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			MandroidCabeza_M.RenderModel();
			model = modelaux;


			// Brazos y Manos
			{
				modelaux = model;
				model = glm::translate(model, glm::vec3(-0.931f, 0.76f, -0.493f));
				model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
				model = glm::rotate(model, 0.5f * sin(angulovaria * 0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidBrazoDerecho_M.RenderModel();

				model = glm::translate(model, glm::vec3(-1.858f, 0.043f, -0.031f));
				//modelaux = model;
				model = glm::rotate(model, angulovaria, glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidManoDerecha_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(0.935f, 0.759f, -0.455f));
				model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
				model = glm::rotate(model, 0.5f * sin(angulovaria * 0.1f + 45 * toRadians), glm::vec3(0.0f, -1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidBrazoIzquierdo_M.RenderModel();

				model = glm::translate(model, glm::vec3(1.843f, -0.021f, 0.038f));
				//modelaux = model;
				model = glm::rotate(model, angulovaria, glm::vec3(1.0f, 0.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidManoIzquierda_M.RenderModel();
				model = modelaux;
			}

			//Piernas y pies
			{
				modelaux = model;
				model = glm::translate(model, glm::vec3(-0.955f, -0.766f, -0.248f));
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f * sin(angulovaria * 0.1f)));
				model = glm::translate(model, glm::vec3(0.0f, abs(0.5f * cos(angulovaria * 0.1f)), 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidPiernaDerecha_M.RenderModel();

				model = glm::translate(model, glm::vec3(0.0, -1.842f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidPieDerecho_M.RenderModel();
				model = modelaux;

				modelaux = model;
				model = glm::translate(model, glm::vec3(0.849f, -0.753f, -0.248f));
				model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.5f * sin((angulovaria * 0.1f) + (180.0 * toRadians))));
				model = glm::translate(model, glm::vec3(0.0f, abs(0.5f * cos(angulovaria * 0.1f)), 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidPiernaIzquierda_M.RenderModel();

				model = glm::translate(model, glm::vec3(0.0f, -1.855f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				MandroidPieIzquierdo_M.RenderModel();
				model = modelaux;
			}
		}

		//Puerta
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-270.0f, -2.0f, -25.0f));
		model = glm::rotate(model, 270.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_M.RenderModel();

		//Letrero
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 13.45f, 1.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Letrero_M.RenderModel();

		//BOLOS 
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(33.0f, 14.40f, 150.0f));
			model = glm::scale(model, glm::vec3(2.7f, 2.7f, 2.7f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pantalla_M.RenderModel();
			//Pista de bolos
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, -5.50f, 18.5f));
			model = glm::scale(model, glm::vec3(0.95f, 0.95f, 0.5f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Linea_M.RenderModel();
			model = modelaux;
			//bolos 
			modelaux = model;
			model = glm::translate(model, glm::vec3(-5.60f, -4.9f, 1.60f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();

			model = glm::translate(model, glm::vec3(-2.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(-1.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(-0.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(2.50f, -4.9f, 1.60f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();

			model = glm::translate(model, glm::vec3(-2.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(-1.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(1.0f, -0.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();
			model = glm::translate(model, glm::vec3(-0.50f, -0.0f, 0.50f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Pino_M.RenderModel();

			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(3.5f, -5.2f, 30.60f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Bomba_M.RenderModel();

			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-3.5f, -5.2f, 30.60f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Bomba_M.RenderModel();
		}

		// ----------------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------- UNIVERSO PHINEAS & FERB - RENDERIZACIÓN-------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------------

////EDIFICIO DE DOOF
//model = glm::mat4(1.0);
//model = glm::translate(model, glm::vec3(-60.0f, 1.2f, 60.0f));
//model = glm::scale(model, glm::vec3(8.0f));
//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
//edificioDoof_M.RenderModel();




//Ferb
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 0.0f, 30.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ferb_M.RenderModel();

		// Ferb mano derecha 
		float angleSaludo = sin(ferbHandTime * 0.25f) * 20.0f; // Oscila entre -20 y +20 grados
		modelaux = model; // guarda el modelo base
		model = glm::translate(model, glm::vec3(-0.169f, 0.942f, 0.019f)); // punto de unión al hombro
		model = glm::rotate(model, glm::radians(angleSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // rotación de saludo
		//model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ferb_mano_M.RenderModel();




		// Phineas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-47.0f, 0.0f, 5.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_M.RenderModel();
		// Phineas mano izquierda
		float anglePhineasSaludo = sin(phineasHandTime * 0.25f) * 25.0f;
		modelaux = model; // Guarda la transformación base
		model = glm::translate(model, glm::vec3(0.126f, 0.912f, 0.035f)); // Punto de unión del brazo
		model = glm::rotate(model, glm::radians(anglePhineasSaludo), glm::vec3(0.0f, 0.0f, 1.0f)); // Rotación tipo saludo
		//model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Phineas_mano_M.RenderModel();



		//Candace
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 0.0f, 20.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Candace_M.RenderModel();

		//Isabella
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 40.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Isabella_M.RenderModel();

		//Bufard
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-26.0f, 0.0f, 64.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Bufard_M.RenderModel();

		//Baljeet
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 40.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Baljeet_M.RenderModel();




		// --------------------------------------------JUEGO DE PERRY ---------------------------------------------------------------------

		//Maquina de perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(5.0f, 2.5f, 8.75f));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		topo_machine_M.RenderModel();

		//Perry
		model = glm::mat4(1.0);
		glm::vec3 basePos = posicionesPerry[perryActual];
		model = glm::translate(model, glm::vec3(basePos.x, basePos.y + perryY, basePos.z));
		//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Perry_M.RenderModel();

		//Carpa Perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -140.0f));
		model = glm::scale(model, glm::vec3(3.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carpa_perry_M.RenderModel();

		//letrero perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-80.0f, 0.0f, -130.0f));
		model = glm::scale(model, glm::vec3(3.75f));
		model = glm::rotate(model, glm::radians(-80.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		letrero_perry_juego_M.RenderModel();

		//Doof
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-90.0f, 0.0f, -128.0f)); // Frente a la máquina
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Mirando hacia atrás (a la máquina)
		model = glm::scale(model, glm::vec3(3.75f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof_M.RenderModel();


		// BICEPS (rotación local en eje X)
		model = glm::translate(modelaux, glm::vec3(-0.497f, 2.205f, -0.066f)); // punto de unión
		model = glm::rotate(model, glm::radians(rotBicep), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof_bicep_M.RenderModel();

		// BRAZO (relativo al bicep)
		model = glm::translate(model, glm::vec3(-0.232f, -0.066f, 0.602f)); // unión
		model = glm::rotate(model, glm::radians(rotBrazo), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof_brazo_M.RenderModel();

		// MUÑECA (relativa al brazo)
		model = glm::translate(model, glm::vec3(-0.100f, 0.465f, 0.290f)); // unión
		model = glm::rotate(model, glm::radians(rotMuneca), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Doof_muneca_M.RenderModel();

		// -----------------------------------------------------------------------------------------------------------------

		//---------------JUEGO DE LOS GLOBOS----------------
		// Carpa Perry
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 0.0f, 120.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		carpa_globo_M.RenderModel();

		// Base inicial después de la carpa
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.2f));
		glm::mat4 modelBase = model;

		// Offsets para columnas (-1, 0, 1 en X), cada una con 3 globos apilados en Y
		float xOffsets[] = { -1.0f, 0.0f, 1.0f };

		for (int col = 0; col < 3; ++col) {
			glm::mat4 colBase = glm::translate(modelBase, glm::vec3(xOffsets[col], 0.0f, 0.0f));
			for (int row = 0; row < 3; ++row) {
				if (!globos[row][col]) continue;  // No dibujar globo si está desactivado

				glm::mat4 globoModel = glm::translate(colBase, glm::vec3(0.0f, row * 1.0f, 0.0f));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(globoModel));
				globo_M.RenderModel();
			}
		}

		for (int col = 0; col < 3; ++col) {
			glm::mat4 colBase = glm::translate(modelBase, glm::vec3(xOffsets[col], 0.0f, 0.0f));
			for (int row = 0; row < 3; ++row) {
				if (globosPonchados[row][col]) {
					glm::mat4 globoPonchadoModel = glm::translate(colBase, glm::vec3(0.0f, row * 1.0f, 0.0f));
					glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(globoPonchadoModel));
					globo_ponchado_M.RenderModel();
				}
			}
		}
		if (dardoEstado == 1) {
			rotacionDardo += velocidadRotacionDardo * deltaTime;
			if (rotacionDardo > 360.0f) rotacionDardo -= 360.0f;
		}
		else if (dardoEstado == 0) {
			rotacionDardo = 0.0f; // reinicia para cada nuevo lanzamiento
		}

		// Render dardo en movimiento
		if (dardoEstado == 1 || dardoEstado == 2) {
			model = glm::mat4(1.0);
			model = glm::translate(model, posDardoActual);
			model = glm::rotate(model, glm::radians(rotacionDardo), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::scale(model, glm::vec3(5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			dardo_M.RenderModel();
		}




		for (const glm::vec3& posFinal : dardosFinales) {
			glm::mat4 modelDardoFinal = glm::mat4(1.0f);
			modelDardoFinal = glm::translate(modelDardoFinal, posFinal);
			modelDardoFinal = glm::scale(modelDardoFinal, glm::vec3(5.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelDardoFinal));
			dardo_M.RenderModel();
		}


		//linea roja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, 0.0f, 110.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		linea_roja_M.RenderModel();


		//---------------------------------------------------------


		//Planty
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-55.0f, 0.0f, 8.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		planty_M.RenderModel();

		//Ballony
		float ballonySpinAngle = fmod(ballonyTime * 0.5f, 360.0f); // velocidad baja
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posX, posY, posZ));
		model = glm::scale(model, glm::vec3(15.0f));
		model = glm::rotate(model, glm::radians(ballonySpinAngle), glm::vec3(0.0f, 1.0f, 0.0f)); // rotación 
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ballony_M.RenderModel();







		//puesto tacos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-45.0f, 1.2f, 50.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_tacos_M.RenderModel();

		//puesto micheladas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, 1.2f, 62.0f));
		model = glm::scale(model, glm::vec3(5.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_miches_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-35.0f, 1.2f, 15.0f));
		model = glm::scale(model, glm::vec3(0.75f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		puesto_miches_M.RenderModel();





		// Base del carrusel (fija)
		glm::mat4 modelCarrusel = glm::mat4(1.0f);
		float anguloCarrusel = fmod(tiempoCarrusel * 1.5f, 360.0f); // 18 grados por segundo
		modelCarrusel = glm::translate(glm::mat4(1.0f), glm::vec3(-190.0f, 0.0f, -130.0f));
		modelCarrusel = glm::scale(modelCarrusel, glm::vec3(5.0f));
		modelCarrusel = glm::rotate(modelCarrusel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCarrusel));
		carrusel_M.RenderModel();
		modelCarrusel = glm::rotate(modelCarrusel, glm::radians(anguloCarrusel), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCarrusel));
		techo_carrusel_M.RenderModel();

		const float VELOCIDAD_OSCILACION_NAVES = 0.05f;
		const float AMPLITUD_OSCILACION_NAVES = 0.3f;
		const float ALTURA_BASE_NAVES = 0.3f;

		for (int i = 0; i < 6; i++) {
			float offsetY = sin(tiempoCarrusel * VELOCIDAD_OSCILACION_NAVES + i) * AMPLITUD_OSCILACION_NAVES;

			glm::mat4 naveModel = glm::mat4(1.0f);
			naveModel = glm::translate(naveModel, glm::vec3(-190.0f, ALTURA_BASE_NAVES + offsetY, -130.0f));
			naveModel = glm::scale(naveModel, glm::vec3(5.0f));
			naveModel = glm::rotate(naveModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			naveModel = glm::rotate(naveModel, glm::radians(anguloCarrusel), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(naveModel));

			switch (i) {
			case 0: nave1_M.RenderModel(); break;
			case 1: nave2_M.RenderModel(); break;
			case 2: nave3_M.RenderModel(); break;
			case 3: nave4_M.RenderModel(); break;
			case 4: nave5_M.RenderModel(); break;
			case 5: nave6_M.RenderModel(); break;
			}
		}

		//JAULA DE BATEO
		{
			model = glm::mat4(1.0);
			model = glm::translate(model, glm::vec3(80.0f, 21.650f, -120.0f));
			model = glm::scale(model, glm::vec3(1.80f, 1.80f, 1.80f));

			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, -12.70f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Campo_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(37.0f, 2.0f, 0.0f));
			model = glm::rotate(model, -180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Reflector_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-37.0f, 2.30f, 0.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Reflector_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-9.50f, -11.90f, 24.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Cofre_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(9.50f, -11.90f, 24.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Caja_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(-3.0f, -11.70f, 24.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Espada_M.RenderModel();
			model = modelaux;
			modelaux = model;
			model = glm::translate(model, glm::vec3(0.0f, -11.70f, 24.0f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			Bola_M.RenderModel();
			model = modelaux;
			modelaux = model;
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDepthMask(GL_FALSE);  // muy importante
			Reja_M.RenderModel();
			glDepthMask(GL_TRUE); // restaurar

		}

		//ARBOLES

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-180.0f, -2.0f, 160.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -2.0f, 60.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-140.0f, -2.0f, -90.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-160.0f, -2.0f, -180.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -2.0f, 150.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-60.0f, -2.0f, 40.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -2.0f, -90.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, -2.0f, 150.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar



		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(170.0f, -2.0f, 50.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(150.0f, -2.0f, -70.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(190.0f, -2.0f, -180.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(280.0f, -2.0f, 120.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(260.0f, -2.0f, -130.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Arbol_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		//Pino arbol

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 20.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -2.0f, -170.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, -2.0f, 30.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(140.0f, -2.0f, -170.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(220.0f, -2.0f, 130.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(240.0f, -2.0f, -160.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(280.0f, -2.0f, 50.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(290.0f, -2.0f, -70.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-280.0f, -2.0f, -65.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-280.0f, -2.0f, 10.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Tronco_M.RenderModel();
		glDepthMask(GL_FALSE);  // muy importante
		model = modelaux;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Tronco_Hojas_M.RenderModel();
		glDepthMask(GL_TRUE); // restaurar


		glDisable(GL_BLEND);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// Rotar el texto cada cierto tiempo
		if (now - tiempoUltimaRotacion >= tiempoRotacion) {
			textoActual = RotarTexto(textoActual); // Rota el texto
			tiempoUltimaRotacion = now; // Actualiza el tiempo de la última rotación
		}

		// Renderizar el texto rotado
		RenderTextoEstatico(textoActual, glm::vec3(-273.5f, 25.4f, -32.0f), 1.0f,
			uniformModel, uniformTextureOffset);


		glDisable(GL_BLEND);









		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}