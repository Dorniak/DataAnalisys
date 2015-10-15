#include "DataAnalisys.h"
DataAnalisys::DataAnalisys(cliext::vector<cliext::vector<Punto3D>> matriz, int resolucionAngular, int VCoche)
{
	((cliext::vector<Punto3D>)matriz[1])[1].getAngle;
	VCOCHE = VCoche;
	resolution = resolucionAngular;
	if (!comprobarBloqueo())
	{
		Segmentacion(matriz);
		EliminarObstaculos();
		prepararObstaculos();
		RelacionarObstaculos();
	}
	ObstaculosvAnt = Obstaculos;
	Obstaculos.clear();
	//TODO::Hacer el adelantamiento al final
	//TODO::Calcular TTC
}

void DataAnalisys::Segmentacion(cliext::vector<cliext::vector<Punto3D>> matrix)
{
	//Se recorre la matriz linealmente
	for (int i = 0; i <= tamMatrixFil; i++)
	{
		for (int j = 0; j <= tamMatrixCol; i++)
		{
			//Se comprubea si el punto a tratar Existe
			if (((cliext::vector<Punto3D>)matrix[i])[j].getExists())
			{
				//En caso de que sea el primer punto se asigna directamente al obstaculo 1
				if (i == 0 && j == 0)
				{
					//Mete al final del vector de obstaculos un obstaculo que crea
					Obstaculos.push_back(gcnew Obstaculo());
					((cliext::vector<Punto3D>)matrix[i])[j].setObstacle(0);
					//Accede al obstaculo 0, al vector de componentes, mente el punto en el vector de componentes
					Obstaculos[0].componentes.push_back((Punto3D)(((cliext::vector<Punto3D>)matrix[i])[j]));
				}
				else {
					//Se compara cada punto a tratar con sus puntos adyacentes ya tratados
					if (i > 0)
					{
						//Punto de encima
						if (((cliext::vector<Punto3D>)matrix[i-1])[j].getExists())
						{
							listMenor[2] = ((cliext::vector<Punto3D>)matrix[i])[j].distanceToPoint(((cliext::vector<Punto3D>)matrix[i-1])[j]);
						}
						if (j > 0)
						{
							//Punto de encima a la izquierda
							if (((cliext::vector<Punto3D>)matrix[i - 1])[j - 1].getExists())
							{
								listMenor[1] = ((cliext::vector<Punto3D>)matrix[i])[j].distanceToPoint(((cliext::vector<Punto3D>)matrix[i-1])[j - 1]);
							}
						}
						if (i > 0 && j < tamMatrixCol)
						{
							//Punto de encima a la derecha
							if (((cliext::vector<Punto3D>)matrix[i-1])[j + 1].getExists())
								listMenor[3] = ((cliext::vector<Punto3D>)matrix[i])[j].distanceToPoint(((cliext::vector<Punto3D>)matrix[i-1])[j + 1]);
						}
					}
					if (j > 0)
					{
						//Punto de la izquierda
						if (((cliext::vector<Punto3D>)matrix[i])[j - 1].getExists())
							listMenor[4] = ((cliext::vector<Punto3D>)matrix[i])[j].distanceToPoint(((cliext::vector<Punto3D>)matrix[i])[j - 1]);
					}
					//Se coge el punto mas cercano al que estamos tratando y se incluye en su obstaculo
					if (listMenor[0] != 0) { menor = 0; }
					else if (listMenor[1] != 0) { menor = 1; }
					else if (listMenor[2] != 0) { menor = 2; }
					else if (listMenor[3] != 0) { menor = 3; }
					//Si los puntos adyacentes no existen se incluye este punto en un obstaculo
					if (menor != 4)
					{
						for (int b = menor; b < 4; b++)
						{
							if (listMenor[b] != 0 && (listMenor[b] < listMenor[menor])) { menor = b; }
						}
						int t, s;
						if (menor = 0) { t = -1, s = -1; }
						if (menor = 1) { t = -1, s = 0; }
						if (menor = 2) { t = -1, s = 1; }
						if (menor = 3) { t = 0, s = -1; }
						if (puntosCercanos(((cliext::vector<Punto3D>)matrix[i])[j], ((cliext::vector<Punto3D>)matrix[i+t])[j + s]))
						{
							int p = ((cliext::vector<Punto3D>)matrix[i+t])[j + s].getObs();
							((cliext::vector<Punto3D>)matrix[i])[j].setObstacle(p);
							Obstaculos[p].componentes.push_back(((cliext::vector<Punto3D>)matrix[i])[j]);
						}
						//A pesar de tener puntos cerca no cumplen la condicion de vecindad por tanto se crea un nuevo obstaculo
						else
						{
							Obstaculos.push_back(gcnew Obstaculo());
							((cliext::vector<Punto3D>)matrix[i])[j]->setObstacle((int)Obstaculos.size());
							Obstaculos[Obstaculos.size()].componentes.push_back(((cliext::vector<Punto3D>)matrix[i])[j]);
						}
					}//En este caso el punto no tiene puntos validos a su alrededor
					else
					{
						Obstaculos.push_back(gcnew Obstaculo());
						((cliext::vector<Punto3D>)matrix[i])[j]->setObstacle((int)Obstaculos.size());
						Obstaculos[Obstaculos.size()].componentes.push_back(((cliext::vector<Punto3D>)matrix[i])[j]);
					}
				}
				for (int k = 0; k < 4; k++)
				{
					listMenor[k] = 0;
				}
				menor = 4;
			}
		}
	}
}
void DataAnalisys::prepararObstaculos()
{
	for (int i = 0; i < Obstaculos.size(); i++)
	{
		Obstaculos[i].prepareObstacle();//TODO::Calcular centro,cubo,y todo lo necesario
	}
}
void DataAnalisys::EliminarObstaculos()
{
	for (int p = 0; p < Obstaculos.size(); p++)
	{
		if (Obstaculos[p].componentes.size() < 20)
		{
			//TODO::Ajustar el numero minimo de puntos para considerarlo un obstaculo
			Obstaculos.erase(Obstaculos.begin() + p);
			p--;
		}
	}
}
void DataAnalisys::RelacionarObstaculos()
{
	//TODO::Ajustar variables para este laser
	//TODO::Revisar la manera en la que se trata el plano
	//fabs(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentropred())) < (VCOCHE / 3.6)*0.3
	for (int i = 0; i < Obstaculos.size(); i++)
	{
		minimo = 2;
		indice = -1;
		for (int j = 0; j < ObstaculosvAnt.size(); j++)
		{
			if (ObstaculosvAnt[j].getVelocity() >= 1)
			{
				if (Obstaculos[i].getCenter()->distanceToPoint(ObstaculosvAnt[j].getPCenter()) < (VCOCHE / 3.6)*0.3)
				{
					relacionarVel(i, j);
					indice = j;
				}
			}
			else if (Obstaculos[i].getCenter()->distanceToPoint(ObstaculosvAnt[j].getCenter()) < minimo /*&& fabs(Obstaculos[i].getYaw() - Obstaculos[i].getYaw()) < 5*/)
			{
				relacionarPos(i, j, VCOCHE, resolution);
				indice = j;
			}
		}
	}
}
void DataAnalisys::relacionarVel(int i, int j)
{
	//TODO::crear las funciones y añadir parametros
	Obstaculos[i].setDirection(ObstaculosvAnt[j].getCenter());
	Obstaculos[i].calculatePrediceCenter();
	Obstaculos[i].setVelocity(/*VCOCHE,resolution*/);
	Obstaculos[i].calcTTC(/*VCOCHE*/);
}
void DataAnalisys::relacionarPos(int i, int j, int VelC, int Res)
{
	//TODO::crear las funciones y añadir parametros
	Obstaculos[i].setDirection(ObstaculosvAnt[j].getCenter());
	Obstaculos[i].calculatePrediceCenter();
	Obstaculos[i].setVelocity();
}
bool DataAnalisys::comprobarBloqueo()
{
	//TODO::revisar si hay algo delante del coche y mandar señal de frenado
	//Devuelve true cuando hay bloqueo
	return false;
}
bool DataAnalisys::puntosCercanos(Punto3D p1, Punto3D p2)
{
	double s0 = 1.4;
	double s1 = sqrt(2 - (2 * cos(2 * resolution*PI / 180)));
	double r = p1.getDistance();
	if (p1.getDistance() > p2.getDistance())
		r = p2.getDistance();
	double tolererancia = s0 + (s1 * r);

	return (tolererancia > p1.distanceToPoint(p2));
}