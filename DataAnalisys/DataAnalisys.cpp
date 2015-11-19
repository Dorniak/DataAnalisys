#include "DataAnalisys.h"
DataAnalisys::DataAnalisys()
{
	indice = -1;
	menor = -1;
	for (int k = 0; k < 4; k++)
	{
		listMenor[k] = 0;
	}
}
//matriz::Lista de puntos
//resolucionAngular::resolucion del laser
//Vcoche::velocidad actual del coche
//consigna velocidad:: puntero para devolucion de parametro de velocidad
//consigna volante:: puntero para devolucion de parametro de volante
//apertura::Angulo de interes de lectura en grados
void DataAnalisys::Analisys(List<Punto3D^>^ matriz, double resolucionAngular, double VCoche, double &consigna_velocidad, double &consigna_volante, double apertura)
{
	VCOCHE = VCoche;
	resolution = resolucionAngular;
	NUMERO_COLUMNAS = matriz->Count/NUMERO_FILAS;
	if (VCOCHE > 5) {
		if (!comprobarBloqueo(matriz))
		{
			Segmentacion(matriz,apertura);
			//TODO::Identificar tipo de obstaculo
			EliminarObstaculos();
			prepararObstaculos();
			RelacionarObstaculos();
			//TODO::Hacer el adelantamiento al final
			//TODO::Calcular TTC y actualizar consignas
		}
		else consigna_velocidad = 0;
	}
	ObstaculosvAnt = Obstaculos;
	Obstaculos->Clear();
}

void DataAnalisys::Segmentacion(List<Punto3D^>^ matrix,double apertura)
{
	int aprr = (apertura / 2)/resolution;
	int inicio = (NUMERO_COLUMNAS / 2)-aprr;
	int final= (NUMERO_COLUMNAS / 2)+aprr;
	//Se recorre la matriz linealmente
	for (int i = 0; i <= NUMERO_FILAS; i++)
	{
		for (int j = inicio; j < final; j++)
		{
			//Se comprubea si el punto a tratar Existe
			if (matrix[convaPos(i, j)]->getDistance() > 0)
			{
				//En caso de que sea el primer punto se asigna directamente al obstaculo 1
				if (i == 0 && j == 0)
				{
					//Mete al final del vector de obstaculos un obstaculo que crea
					Obstaculos->Add(gcnew Obstaculo());
					matrix[convaPos(i, j)]->setObstacle(0);
					//Accede al obstaculo 0, al vector de componentes, mente el punto en el vector de componentes
					Obstaculos[0]->components->Add(matrix[convaPos(i, j)]);
				}
				else {
					//Se compara cada punto a tratar con sus puntos adyacentes ya tratados
					if (i > 0)
					{//Pultiplicar a cada punto por un valor de rango para hacer el tanto por 1
						//Punto de encima
						if (matrix[convaPos(i - 1, j)]->getDistance() > 0)
						{
							listMenor[2] = matrix[convaPos(i, j)]->distanceToPoint(matrix[convaPos(i + 1, j)]);//   /2
						}
						if (j > 0)
						{
							//Punto de encima a la izquierda
							if (matrix[convaPos(i - 1, j - 1)]->getDistance() > 0)
							{
								listMenor[1] = matrix[convaPos(i, j)]->distanceToPoint(matrix[convaPos(i - 1, j - 1)]);  // //2*res h
							}
						}
						if (i > 0 && j < NUMERO_COLUMNAS)
						{
							//Punto de encima a la derecha
							if (matrix[convaPos(i - 1, j + 1)]->getDistance() < 0)
								listMenor[3] = matrix[convaPos(i, j)]->distanceToPoint(matrix[convaPos(i - 1, j + 1)]);// /2*res h
						}
					}
					if (j > 0)
					{
						//Punto de la izquierda
						if (matrix[convaPos(i, j - 1)]->getDistance()>0)
							listMenor[4] = matrix[convaPos(i, j)]->distanceToPoint(matrix[convaPos(i, j - 1)]);// /res h
					}
					//Se coge el punto mas cercano al que estamos tratando y se incluye en su obstaculo
					if (listMenor[0] != 0) { menor = 0; }
					else if (listMenor[1] != 0) { menor = 1; }
					else if (listMenor[2] != 0) { menor = 2; }
					else if (listMenor[3] != 0) { menor = 3; }
					//Si los puntos adyacentes no existen se incluye este punto en un obstaculo
					if (menor != -1)
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
						if (puntosCercanos(matrix[convaPos(i, j)], matrix[convaPos(i + t, j + s)]))
						{
							int p = matrix[convaPos(i + t, j + s)]->getObstacle();
							matrix[convaPos(i, j)]->setObstacle(p);
							Obstaculos[p]->components->Add(matrix[convaPos(i, j)]);
						}
						//A pesar de tener puntos cerca no cumplen la condicion de vecindad por tanto se crea un nuevo obstaculo
						else
						{
							Obstaculos->Add(gcnew Obstaculo());
							matrix[convaPos(i, j)]->setObstacle((int)Obstaculos->Count);
							Obstaculos[Obstaculos->Count]->components->Add(matrix[convaPos(i, j)]);
						}
					}//En este caso el punto no tiene puntos validos a su alrededor
					else
					{
						Obstaculos->Add(gcnew Obstaculo());
						matrix[convaPos(i, j)]->setObstacle((int)Obstaculos->Count);
						Obstaculos[Obstaculos->Count]->components->Add(matrix[convaPos(i, j)]);
					}
				}

				menor = -1;
			}
		}
	}
}
void DataAnalisys::prepararObstaculos()
{
	for (int i = 0; i < Obstaculos->Count; i++)
	{
		Obstaculos[i]->prepareObstacle();//TODO::Calcular centro,cubo,y todo lo necesario
	}
}
void DataAnalisys::EliminarObstaculos()
{
	for (int p = 0; p < Obstaculos->Count; p++)
	{
		if (Obstaculos[p]->components->Count < TAMAÑO_MINIMO_OBSTACULO)
		{
			//TODO::Ajustar el numero minimo de puntos para considerarlo un obstaculo
			Obstaculos->RemoveAt(p);
			p--;
		}
	}
}
void DataAnalisys::RelacionarObstaculos()
{
	//TODO::Ajustar variables para este laser
	//TODO::Revisar la manera en la que se trata el plano
	//fabs(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentropred())) < (VCOCHE / 3.6)*0.3
	for (int i = 0; i < Obstaculos->Count; i++)
	{
		indice = -1;
		for (int j = 0; j < ObstaculosvAnt->Count; j++)
		{
			if (ObstaculosvAnt[j]->getVelocity() >= 1)
			{
				//0.3 es la distancia maxima que que puede recorrer entre barridos
				if (Obstaculos[i]->getCenter()->distanceToPoint(ObstaculosvAnt[j]->getPrediceCenter()) < (VCOCHE / 3.6) * TIEMPO_MARGEN)// POrque 0.3??  = 0.0833
				{
					relacionarVel(i, j);
					indice = j;
				}
			}
			else if (Obstaculos[i]->getCenter()->distanceToPoint(ObstaculosvAnt[j]->getCenter()) < DISTANCIA_MAXIMA /*&& fabs(Obstaculos[i].getYaw() - Obstaculos[i].getYaw()) < 5*/)
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
	Obstaculos[i]->setDirection(ObstaculosvAnt[j]->getCenter());
	Obstaculos[i]->calculatePrediceCenter();
	Obstaculos[i]->setVelocity(VCOCHE, resolution);
	Obstaculos[i]->calculateTimeToCollision(VCOCHE);
}
void DataAnalisys::relacionarPos(int i, int j, int VelC, int Res)
{
	//TODO::crear las funciones y añadir parametros
	Obstaculos[i]->setDirection(ObstaculosvAnt[j]->getCenter());
	Obstaculos[i]->calculatePrediceCenter();
	Obstaculos[i]->setVelocity(VCOCHE, resolution);
}
bool DataAnalisys::comprobarBloqueo(List<Punto3D^>^ matriz)
{
	//TODO::revisar si hay algo delante del coche y mandar señal de frenado
	//Devuelve true cuando hay bloqueo
	int medio = matriz->Count / 2;
	for (int k = medio - 20; k < medio + 20; k++) {
		for (int i = 0; i < NUMERO_FILAS; i++) {
			if (matriz[convaPos(i, k)]->getDistance() < 15) {
				return true;
			}
		}
	}
	return false;
}
bool DataAnalisys::puntosCercanos(Punto3D^ p1, Punto3D^ p2)
{
	double s0 = 1.4;
	double s1 = sqrt(2 - (2 * cos(2 * resolution*PI / 180)));
	double r = p1->getDistance();
	if (p1->getDistance() > p2->getDistance())
		r = p2->getDistance();
	double tolererancia = s0 + (s1 * r);

	return (tolererancia > p1->distanceToPoint(p2));
}
int DataAnalisys::convaPos(int a, int b) {
	return (a - 1) * 16 + b;
}