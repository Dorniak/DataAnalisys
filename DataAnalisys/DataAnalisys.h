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
using namespace System::Collections::Generic;
//using namespace cliext;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys(List<Punto3D^>^ matriz, int resolucionAngular, int VCoche);
	//Se encarga de agrupar puntos en obstaculos/

private:
	int minimo;
	int indice;
	int menor = 4;
	List<Obstaculo^>^ Obstaculos = gcnew List<Obstaculo^>();
	List<Obstaculo^>^ ObstaculosvAnt = gcnew List<Obstaculo^>();
	List<double>^ listMenor = gcnew List<double>();
	void Segmentacion(List<Punto3D^>^ matrix);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo();
	bool puntosCercanos(Punto3D^ p1, Punto3D^ p2);
	int convaPos(int a, int b);
};