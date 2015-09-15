#pragma once
#include <vector>
#ifdef LidarDLL_EXPORTS
#define LidarDLL_API __declspec(dllexport) 
#else
#define LidarDLL_API __declspec(dllimport) 
#endif
using namespace System;

namespace LidarDLL {

	public class Punto3D
	{
	public:
		Punto3D(double d, double i, double r);
		void setCoordinatesX(double cx);
		void setCoordinatesY(double cy);
		void setCoordinatesZ(double cz);
		static LidarDLL_API void setDistance(double d);
		void setIntensity(double i);
		void setAzimuth(double r);
		void setDistance(Byte i, Byte j);
		void setIntensity(Byte i);
		void setAzimuth(Byte i, Byte j);
		void visualize();

		double getCoordinatesX();
		double getCoordinatesY();
		double getCoordinatesZ();
		double getDistance();
		double getIntensity();
		double getAzimuth();
		double distanceToPoint(Punto3D p);

	private:
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
		std::vector <Punto3D> componentes;
	private:
		Punto3D* North;
		Punto3D* South;
		Punto3D* East;
		Punto3D* West;
		Punto3D Center;
	};
}