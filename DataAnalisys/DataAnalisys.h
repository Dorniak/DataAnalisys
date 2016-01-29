#pragma once
#include "Obstaculo.h"
#include <math.h>

//#include <cliext/vector> para clases referenciadas
#define NUMERO_FILAS 16 //Coincide con el numero de canales
#define TAMAÑO_MINIMO_OBSTACULO 20
#define TIEMPO_MARGEN 0.3 //TODO: Ajustar parametro
#define DISTANCIA_MAXIMA 2
#define PI 3.14159265

using namespace std;
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;
//using namespace cliext;
ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys();
	void Analisys(cli::array<Object^>^ data);
	void AnalisysThread();
	//void Analisys(List<Punto3D^>^ matriz, double resolucionAngular, double VCoche, double &consigna_velocidad, double &consigna_volante, double apertura);
	//Se encarga de agrupar puntos en obstaculos/

private:
	double ^ consigna_velocidad;
	double ^ consigna_volante;
	double apertura;
	int indice;
	int menor;
	double VCOCHE;
	double resolution;
	int NUMERO_COLUMNAS;//numero de barridos que es variable por la configuracion del laser
	List<Obstaculo^>^ Obstaculos = gcnew List<Obstaculo^>();
	List<Obstaculo^>^ ObstaculosvAnt = gcnew List<Obstaculo^>();
	List<double>^ listMenor = gcnew List<double>();
	void Segmentacion(List<Punto3D^>^ matrix,double apertura);
	void prepararObstaculos();
	void EliminarObstaculos();
	void RelacionarObstaculos();
	void relacionarVel(int i, int j);
	void relacionarPos(int i, int j, int VelC, int Res);
	bool comprobarBloqueo(List<Punto3D^>^ matriz);
	bool puntosCercanos(Punto3D^ p1, Punto3D^ p2);
	int convaPos(int a, int b);
	List<Punto3D^>^ matriz;
	Thread^ thread_analysis;
	cli::array<Object^> ^ parameters_in;
};