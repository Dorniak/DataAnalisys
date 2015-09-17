// PointDll.h

#pragma once
#include <vector>

using namespace System;
using namespace std;

namespace LidarDLL {

	public class Punto3D
	{

#define MIN_DISTANCE 1		// Minimum valid distance
#define MAX_DISTANCE 80		// Maximum valid distance

	public:
		Punto3D(double d, double i, double r);
		Punto3D::Punto3D();
		void setExiste(bool existe);
		void setObs(int Obs);
		void setCoordinatesX(double cx);
		void setCoordinatesY(double cy);
		void setCoordinatesZ(double cz);
		void setDistance(double d);
		void setIntensity(double i);
		void setAzimuth(double r);
		void setDistance(Byte i, Byte j);
		void setIntensity(Byte i);
		void setAzimuth(Byte i, Byte j);
		
		void visualize();

		//Cambiar
		
		bool getExiste();
		int getObs();
		double getCoordinatesX();
		double getCoordinatesY();
		double getCoordinatesZ();
		double getDistance();
		double getIntensity();
		double getAzimuth();
		double distanceToPoint(Punto3D p);

	private:
		bool existe;
		int Obs;			//Obstaculo al que pertenece el punto
		double Intensity;	// Bounced beam intensity
		double Distance;	// Distance to the point
		double Azimuth;		// Horizontal angle Y-X
		double Angle;		// Vertical angle Laser Id Z-Y
		double x;			//X coordinate of the point
		double y;			//Y coordinate of the point	
		double z;			//Z coordinate of the point
	};
	public class Obstaculo
	{
	public:
		Obstaculo();
		double get;
		void calcCentro();
		void calcCentropred();
		vector <Punto3D> componentes;
	private:
		Punto3D* North;
		Punto3D* South;
		Punto3D* East;
		Punto3D* West;
		Punto3D Center;
	};
}