/*********************************************

	Calculo posición de un objeto a partir de un dato
	obtenido desde un sensor.

	Realizado por David Ortiz.

**********************************************/

// Librerías estándard
#include <iostream>
#include <cmath>

// Librerías Eigen
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Geometry>


int main()
{
	// Variables para guardar los resultados
	Eigen::Vector3d qB, qO;

	// Variables localización
	double Delta_Degree = 30; // Valor en grados
	Eigen::Vector3d pO; // Posición del coche

	// Se incializa el valor de pO
	pO << 50, 25, 1; // Valor en metros

	// Variables de calibración
	double Beta_Degree = 25; // Valor en grados
	Eigen::Vector3d mB;// Posición del sensor respecto el coche

	// Se inicializa el valor de mB
	mB << 1.5, 0.75, 1; // Valor en metros

	// Variable para la posición del objeto a detectar
	Eigen::Vector3d qS;

	// Se inicializa el valor de qS
	qS << 12, 5, 1;

	// Se pasan los valores de grados a radianes
	double Delta = (Delta_Degree*M_PI) / 180;
	double Beta = (Beta_Degree*M_PI) / 180;

	// Se crean la matriz de S a B
	Eigen::Matrix3d Ts_b;
	// Se incializa la matriz
	Ts_b << 	cos(Beta),	-sin(Beta),	mB(0),
				sin(Beta), 	cos(Beta), 	mB(1),
				0, 			0, 			mB(2);

	// Se crea la matriz de B a O
	Eigen::Matrix3d Tb_o;
	// Se inicializa la matriz
	Tb_o << 	cos(Delta),		-sin(Delta),	pO(0),
				sin(Delta), 	cos(Delta), 	pO(1),
				0, 				0, 				pO(2);			

	// Se calcula la distancia del objeto con el centro 
	// del coche
	qB = Ts_b * qS;

	// Se imprime por pantalla el resultado
	std::cout << "La distancia del coche al objeto es: \n" << qB << std::endl;

	// Se calcula la distancia del objeto con el centro del plano
	qO = Tb_o * qB;

	// Se imprime por pantalla el resultado
	std::cout << "La distancia del objeto con el centro de coordenadas es:\n"  << qO << std::endl;

	// Per comprobar que funciona igual multiplicando las matrices entre ellas y luego encontrar el valor directamente
	Eigen::Matrix3d Ts_o;

	// Se obtiene el valor combinado de las dos matrices de rotación
	Ts_o = Tb_o * Ts_b;

	// El resultado de esta manera queda
	Eigen::Vector3d qO_prima;
	qO_prima = Ts_o *qS;

	std::cout << "El resultado multiplicando las matrices entre si, y luego multiplicando con qS: \n" << qO_prima << std::endl;

	// Se finaliza el programa
	return 0;
}