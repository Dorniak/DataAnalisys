#include "DataAnalisys.h"
DataAnalisys::DataAnalisys(Punto3D* matriz[tamMatrixFil][tamMatrixCol])
{
	menor = 4;
	for (int k = 0; k < listMenor->Length; k++)
		listMenor[k] = 0;
}
void DataAnalisys::QuitarPuntos(Punto3D* matrix[tamMatrixFil][tamMatrixCol])
{

}
void DataAnalisys::Segmentacion(Punto3D* matrix[tamMatrixFil][tamMatrixCol])
{
	for (int i = 0; i <= tamMatrixFil; i++) {
		for (int j = 0; j <= tamMatrixCol; i++) {
			if (matrix[i][j]->existe != 0){
				if (i == 0 && j == 0)
					int a = 1;//TODO:quitar esto hacer lo del sig coment
					//asignar punto a grupo 1
				else {
					if (i > 0) {
						if (matrix[i - 1][j - 1]->existe != 0)
							listMenor[1] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j - 1]);
						if (matrix[i - 1][j]->existe != 0)
							listMenor[2] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j]);
						if (matrix[i - 1][j + 1]->existe != 0)
							listMenor[3] = matrix[i][j]->distanceToPoint(*matrix[i - 1][j + 1]);
					}
					if (j > 0) {
						if (matrix[i][j - 1]->existe != 0)
							listMenor[4] = matrix[i][j]->distanceToPoint(*matrix[i][j - 1]);
					}
					if (listMenor[0] != 0) { menor = 0; }
					else if (listMenor[1] != 0) { menor = 1; }
					else if (listMenor[2] != 0) { menor = 2; }
					else if (listMenor[3] != 0) { menor = 3; }
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
							//Se supone que el punto con el que relacionas ya debe tener objeto asignado
							//por lo tanto solo hay que añadir este punto a ese objeto
						}//TODO:Falta crear la clase objeto
						else int aaa = 1;//TODO:en este caso crear un grupo para este punto
					}
					else int aaa = 1;//TODO:en este caso crear un grupo para este punto
				}
				for (int k = 0; k < listMenor->Length; k++)
					listMenor[k] = 0;
				menor = 4;
			}
		}
	}
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