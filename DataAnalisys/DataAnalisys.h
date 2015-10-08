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
class DataAnalisys {
public:
	//Constructor
	DataAnalisys(Punto3D* matriz[tamMatrixFil][tamMatrixCol], int resolucionAngular, int VCoche);
	//Se encarga de agrupar puntos en obstaculos/

private:
	int minimo;
	int indice;
	int menor = 4;
	vector<Obstaculo> Obstaculos;
	//cliext::vector<Obstaculo> Obstaculos;para clases referenciadas
	vector<Obstaculo> ObstaculosvAnt;
	double listMenor[4];
	void Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol]);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo();
	bool puntosCercanos(Punto3D *p1, Punto3D *p2);
};