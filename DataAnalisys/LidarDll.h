#pragma once
#ifdef LidarDLL_EXPORTS
#define LidarDLL_API __declspec(dllexport) 
#else
#define LidarDLL_API __declspec(dllimport) 
#endif
#include <vector>
using namespace System;
using namespace std;

namespace LidarDLL {

	public class Punto3D
	{
	public:
		Punto3D(double d, double i, double r);
		Punto3D::Punto3D();

			void setExist(bool ex);
			void setObstacle(int Obs);
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

		bool getExists();
		int getObs();
		double getCoordinatesX();
		double getCoordinatesY();
		double getCoordinatesZ();
		double getDistance();
		double getIntensity();
		double getAzimuth();
		double distanceToPoint(Punto3D p);

	private:
		bool Exist;			// The point exist or not
		int Obstacle;		// Obstacle that contains the point
		double Intensity;	// Bounced beam intensity
		double Distance;	// Distance to the point
		double Azimuth;		// Horizontal angle Y-X
		double Angle;		// Vertical angle Laser Id Z-Y
		double x;			// X coordinate of the point
		double y;			// Y coordinate of the point	
		double z;			// Z coordinate of the point
	};
	public class Obstaculo
	{
	public:
		Obstaculo();

		void setDirection(Punto3D antPosition);//Pone la direccion al obstaculo
		void setVelocity();//Pone la velocidad a partir del modulo del vector de direccion

		Punto3D getCenter();//Devuelve el centro del obstaculo
		Punto3D getPCenter();//Devuelve el centro predicho del obstaculo
		int getVelocity();//Devuelve a la velocidad a la que va el obstaculo

		void prepareObstacle();//Calcula los datos del obstaculo
		void calcCentro();//Calcula el centro del obstaculo
		void calcCentropred();//Calcula el centro predicho a partir de la velocidad del coche y el vector de direccion
		void calcTTC();//Calcula el tiempo de colision del obstaculo con el coche
		std::vector <Punto3D> componentes;
	private:
		Punto3D* North;
		Punto3D* South;
		Punto3D* East;
		Punto3D* West;
		Punto3D Center;
		Punto3D PrediceCenter;
		int Velocity;
	};
}