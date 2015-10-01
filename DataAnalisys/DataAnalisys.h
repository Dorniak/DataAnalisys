#pragma once
#include "Obstaculo.h"
#include <math.h>
#include <vector>
//TODO: ARREGLAR TAMAÑO DE MATRIZ
#define tamMatrixFil 50
#define tamMatrixCol 50
#define PI 3.14159265
extern int resolution;
extern int VCOCHE = 1;
using namespace std;
using namespace System;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys(Punto3D* matriz[tamMatrixFil][tamMatrixCol],int resolucionAngular,int VCoche);
	//Se encarga de agrupar puntos en obstaculos/
	
private:
	int minimo;
	int indice;
	int menor = 4;
	static vector<Obstaculo> &Obstaculos;
	static vector<Obstaculo> &ObstaculosvAnt{ };
	cli::array<double>^ listMenor;
	void Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol]);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo();
	bool puntosCercanos(Punto3D *p1, Punto3D *p2);
};