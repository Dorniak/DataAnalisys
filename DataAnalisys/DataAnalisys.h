#pragma once
#include "Obstaculo.h"
#include <math.h>

//#include <cliext/vector> para clases referenciadas
//TODO: ARREGLAR TAMAÑO DE MATRIZ
#define tamMatrixFil 50
#define tamMatrixCol 50
#define PI 3.14159265
static int resolution = 1;
static int VCOCHE = 1;
using namespace std;
using namespace System;
//using namespace cliext;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys(cliext::vector<cliext::vector<Punto3D>> matriz, int resolucionAngular, int VCoche);
	//Se encarga de agrupar puntos en obstaculos/

private:
	int minimo;
	int indice;
	int menor = 4;
	cliext::vector<Obstaculo> Obstaculos;
	//cliext::vector<Obstaculo> Obstaculos;para clases referenciadas
	cliext::vector<Obstaculo> ObstaculosvAnt;
	double listMenor[4];
	void Segmentacion(cliext::vector<cliext::vector<Punto3D>> matrix);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo();
	bool puntosCercanos(Punto3D p1, Punto3D p2);
};