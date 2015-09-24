#include "DataAnalisys.h"
DataAnalisys::DataAnalisys(Punto3D* matriz[tamMatrixFil][tamMatrixCol])
{
	//TODO::Hacer esto en un bucle que se active al recibir una nueva matriz si se hace en un thread separado
	//TODO::Si se hace como función no es necesario
	if (!comprobarBloqueo()) {
		Segmentacion(matriz);
		/*for (int k = 0; k < listMenor->Length; k++)
			listMenor[k] = 0;*/
		EliminarObstaculos();
		prepararObstaculos();
		RelacionarObstaculos();
	}
	ObstaculosvAnt = Obstaculos;
	Obstaculos.clear;
	//TODO::Hacer el adelantamiento al final
}

void DataAnalisys::Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol])
{
	//Se recorre la matriz linealmente
	for (int i = 0; i <= tamMatrixFil; i++) {
		for (int j = 0; j <= tamMatrixCol; i++) {
			//Se comprubea si el punto a tratar Existe
			if (matrix[i][j]->getExiste) {
				//En caso de que sea el primer punto se asigna directamente al obstaculo 1
				if (i == 0 && j == 0) {
					//Mete al final del vector de obstaculos un obstaculo que crea
					Obstaculos.push_back(Obstaculo());
					matrix[i][j]->setObs(0);
					//Accede al obstaculo 0, al vector de componentes, mente el punto en el vector de componentes
					Obstaculos[0].componentes.push_back(*matrix[i][j]);
				}
					//TODO:quitar esto hacer lo del sig coment
							  //asignar punto a obstaculo 1
				else {
					//Se compara cada punto a tratar con sus puntos adyacentes ya tratados
					if (i > 0) {
						if (matrix[i - 1][j]->getExiste)
							listMenor[2] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j]);
						if (j > 0) {
							if (matrix[i - 1][j - 1]->getExiste)
								listMenor[1] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j - 1]);
						}
						if (i > 0 && j < tamMatrixCol) {
							if (matrix[i - 1][j + 1]->getExiste)
								listMenor[3] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j + 1]);
						}
					}
					if (j > 0) {
						if (matrix[i][j - 1]->getExiste)
							listMenor[4] = matrix[i][j]->distanceToPoint(*matrix[i][j - 1]);
					}
					//Se coge el punto mas cercano al que estamos tratando y se incluye en su obstaculo
					if (listMenor[0] != 0) { menor = 0; }
					else if (listMenor[1] != 0) { menor = 1; }
					else if (listMenor[2] != 0) { menor = 2; }
					else if (listMenor[3] != 0) { menor = 3; }
					//Si los puntos adyacentes no getExisten se incluye este punto en un obstaculo
					if (menor != 4) {
						for (int b = menor; b < 4; b++) {
							if (listMenor[b] != 0 && (listMenor[b]<listMenor[menor])) { menor = b; }
						}
						int t, s;
						if (menor = 0) { t = -1, s = -1; }
						if (menor = 1) { t = -1, s = 0; }
						if (menor = 2) { t = -1, s = 1; }
						if (menor = 3) { t = 0, s = -1; }
						//TODO:
						if (puntosCercanos(matrix[i][j],matrix[i+t][j+s])) {
							int p = matrix[i + t][j + s]->getObs();
							matrix[i][j]->setObs(p);
							Obstaculos[p].componentes.push_back(*matrix[i][j]);
							//Se supone que el punto con el que relacionas ya debe tener objeto asignado
							//por lo tanto solo hay que añadir este punto a ese objeto
						}//TODO:Falta crear la clase objeto
						else {//TODO:en este caso crear un grupo para este punto
							Obstaculos.push_back(Obstaculo());
							matrix[i][j]->setObs(Obstaculos.size);
							Obstaculos[Obstaculos.size].componentes.push_back(*matrix[i][j]);
						}
					}
					else { Obstaculos.push_back(Obstaculo());
					matrix[i][j]->setObs(Obstaculos.size);
					Obstaculos[Obstaculos.size].componentes.push_back(*matrix[i][j]);
					}//TODO:en este caso crear un grupo para este punto

				}
				for (int k = 0; k < listMenor->Length; k++)
					listMenor[k] = 0;
				menor = 4;
			}
		}
	}
}
void DataAnalisys::prepararObstaculos() {
	for (int i = 0; i < Obstaculos.size; i++) {
		Obstaculos[i].prepararObs();//TODO::Calcular centro,cubo,y todo lo necesario
	}

}
void DataAnalisys::EliminarObstaculos()
{
	//TODO::Eliminar obastaculos pequeños o no validos
	for (int p = 0; p < Obstaculos.size; p++) {
		if (Obstaculos[p].componentes.size<20) {//TODO::Ajustar el numero minimo de puntos para considerarlo un obstaculo
			Obstaculos.erase(Obstaculos.begin()+p);
			p--;
		}
	}
	
}
void DataAnalisys::RelacionarObstaculos() {//TODO::Ajustar variables para este laser 
	//TODO::Revisar la manera en la que se trata el plano
	//fabs(matrix[i][0].getCentro()->distanciaPunto(matrix[j][1].getCentropred())) < (VCOCHE / 3.6)*0.3
	for (int i = 0; i < Obstaculos.size; i++) {
		for (int j = 0; j < ObstaculosvAnt.size; j++) {
			if (ObstaculosvAnt[j].getVelocidad() >= 1)
			{
				if (Obstaculos[i].getCentro().distanceToPoint(ObstaculosvAnt[j].getCentroPred) < (VCOCHE / 3.6)*0.3) {
					relacionarVel(i, j, VCOCHE, resolucionAngular);
				}
				else if (Obstaculos[i].getCentro().distanceToPoint(ObstaculosvAnt[j].getCentro< minimo)) {
					relacionarPos(i, j, VCOCHE, resolucionAngular);
				}

			}
		}
	}
}
void DataAnalisys::relacionarVel(int i,int j,int VelC,int Res) {//TODO::crear las funciones y añadir parametros
	Obstaculos[i].setDireccion(ObstaculosvAnt[j].getCentro());
	Obstaculos[i].calcCentropred();
	Obstaculos[i].setVelocidad();
	Obstaculos[i].calcTTC();

}
void DataAnalisys::relacionarPos(int i, int j, int VelC, int Res) {//TODO::crear las funciones y añadir parametros
	Obstaculos[i].setDireccion(ObstaculosvAnt[j].getCentro());
	Obstaculos[i].calcCentropred();
	Obstaculos[i].setVelocidad();
}
bool DataAnalisys::comprobarBloqueo()
{
	//TODO::revisar si hay algo delante del coche y mandar señal de frenado
	//Devuelve true cuando hay bloqueo
	return false;
}
bool DataAnalisys::puntosCercanos(Punto3D *p1, Punto3D *p2)
{
	float s0 = 1.4;
	float s1 = sqrt(2 - (2 * cos(2 * resolucion*PI / 180)));
	float r = p1->getDistance();
	if (p1->getDistance() > p2->getDistance())
		r = p2->getDistance();
	float tolererancia = s0 + (s1 * r);

	return (tolererancia > p1->distanceToPoint(*p2));
}