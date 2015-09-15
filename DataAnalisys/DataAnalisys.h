#pragma once
#include "LidarDLL.h"
#include <math.h>
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
	//Eliminate los puntos no validos 
	void QuitarPuntos(Punto3D* matrix[tamMatrixFil][tamMatrixCol]);
	//Se encarga de agrupar puntos en obstaculos
	void Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol]);
private:
	int menor;

	array<int>^ listMenor;
	bool puntosCercanos(Punto3D *p1, Punto3D *p2);
};