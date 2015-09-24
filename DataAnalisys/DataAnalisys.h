#pragma once
#include "LidarDLL.h"
#include <math.h>
#include <vector>
//TODO: ARREGLAR TAMAÑO DE MATRIZ
#define tamMatrixFil 50
#define tamMatrixCol 50
#define resolucion 1
#define PI 3.14159265
using namespace std;
using namespace System;
using namespace LidarDLL;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys(Punto3D* matriz[tamMatrixFil][tamMatrixCol]);
	//Se encarga de agrupar puntos en obstaculos
	
	
private:
	int menor = 4;
	static vector<Obstaculo> &Obstaculos;
	static vector<Obstaculo> &ObstaculosvAnt;
	cli::array<int>^ listMenor;
	void Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol]);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j, int VelC, int Res);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo();
	bool puntosCercanos(Punto3D *p1, Punto3D *p2);
};