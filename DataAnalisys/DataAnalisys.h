#pragma once
#include "Obstaculo.h"
#include <math.h>

//#include <cliext/vector> para clases referenciadas
//TODO: ARREGLAR TAMAÑO DE MATRIZ
#define NUMERO_FILAS 50
#define NUMERO_COLUMNAS 50
#define TAMAÑO_MINIMO_OBSTACULO 20
#define TIEMPO_MARGEN 0.3 //TODO: Ajustar parametro
#define DISTANCIA_MAXIMA 2
#define PI 3.14159265

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
//using namespace cliext;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys();
	void Analisys(List<Punto3D^>^ matriz, double resolucionAngular, double VCoche, double &consigna_velocidad, double &consigna_volante);
	//Se encarga de agrupar puntos en obstaculos/

private:
	int indice;
	int menor;
	double VCOCHE;
	double resolution;
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