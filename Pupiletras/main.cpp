#include <iostream>
/*Estas librerias son para la aleatoriedad*/
#include <cstdlib>
#include <ctime>

#define N 40
#define M 40
#define MOV 4

using namespace std;

void imprimeMenu() {
	cout << "Bienvenido al juego de la Sopa de Letras o PUPI-LPOO." << endl;
	cout << "Menu de opciones: " << endl;
	cout << "Crear Tablero (T) " << endl;
	cout << "Jugar (J) " << endl;
	cout << "Salir (S) " << endl;
	cout << "Ingrese su opcion: ";
}

void crearTablero(char tablero[N][M], int filas, int columnas) {
	/*Inicializar todo el tablero en blanco*/
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			tablero[i][j] = ' ';
		}
	}
	/*Ahora voy a crear de manera aleatoria las letras para el tablero de filas y columnas*/
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			tablero[i][j] = 'A' + rand() % 26;
		}
	}
}

void imprimeTablero(char tablero[N][M], int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			cout << tablero[i][j] << " ";
		}
		cout << endl;
	}
}

void buscaPalabra(char tablero[N][M], int filas, int columnas, int movimientos[MOV][2], char palabra[N], int* posIniX, int* posIniY, int* posFinX, int* posFinY) {
	int avanzarX, avanzarY, auxI, auxJ, indice, palabraExiste=0;
	//Vamos a suponer inicialmente que la palabra no se encuentra
	*posIniX = -1;
	*posIniY = -1;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			//Si la letra del tablero es igual a la primera letra de la palabra a buscar
			if (tablero[i][j] == palabra[0]) {
				/*Esta letra podria ser el inicio de la palabra correcta en el tablero*/
				/*Voy a procesar los 4 movimientos en los que puedo buscar*/
				for (int k = 0; k < MOV; k++) {
					/*Direccion en la que me voy a mover*/
					avanzarX = movimientos[k][0];
					avanzarY = movimientos[k][1];
					/*Procesar el primer movimiento*/
					auxI = i;
					auxJ = j;
					indice = 1;
					palabraExiste = 1;
					/*Voy a buscar las demas letras de la palabra en el tablero, en la direccion establecida por movimientos*/
					while (palabra[indice] != '\0') {
						auxI = auxI + avanzarX;
						auxJ = auxJ + avanzarY;
						/*Cuando avance, llegue a una posicion correcta*/
						if ((auxI >= 0 && auxI < filas) && (auxJ >= 0 && auxJ < columnas)){
							if (palabra[indice] != tablero[auxI][auxJ]) {
								palabraExiste = 0;
								break;
							}
							else {
								indice++;
							}
						}
						else {
							palabraExiste = 0;
							break;
						}
					}
					if (palabraExiste) {
						*posIniX = i;
						*posIniY = j;
						*posFinX = auxI;
						*posFinY = auxJ;
						break;
					}
				}
				if (palabraExiste) {
					break;
				}
			}
		}
		if (palabraExiste) {
			break;
		}
	}
}

void crearMovimientos(int movimientos[MOV][2]) {
	//Abajo
	movimientos[0][0] = 1;
	movimientos[0][1] = 0;
	//Arriba
	movimientos[1][0] = -1;
	movimientos[1][1] = 0;
	//Izquierda
	movimientos[2][0] = 0;
	movimientos[2][1] = -1;
	//Derecha
	movimientos[3][0] = 0;
	movimientos[3][1] = 1;
}

void main() {
	//Declaración de variables de contol de nuestro algoritmo
	int centinela = 1, filas, columnas, centinela2, cantPalabras, posIniX, posIniY, posFinX, posFinY;
	char opcion, nivel, tablero[N][M], palabra[N];
	int aciertos, movimientos[MOV][2];

	srand(time(NULL)); /*Esto siembra la semilla de la aleatoriedad, solo se debe colocar 1 vez*/
	
	while (centinela) {
		imprimeMenu();
		cin >> opcion;
		switch (opcion) {
			case 'T': {
				cout << "Elija el nivel del tablero: " << endl;
				cout << "[X] Experto" << endl;
				cout << "[P] Personalizado" << endl;
				cout << "Ingrese nivel: ";
				cin >> nivel;
				if (nivel == 'P') {
					//P-Personalizado
					centinela2 = 1;
					while (centinela2) {
						cout << "Ingrese el numero de filas: ";
						cin >> filas;
						cout << "Ingrese el numero de columnas: ";
						cin >> columnas;
						//Aplicando reglas de validación
						if ((filas >= 1 && filas <= 40) && (columnas >= 1 && columnas <= 40)) {
							centinela2 = 0;
						}
						else {
							cout << "Las filas y/o columnas ingresadas no son correctas" << endl;
						}
					}
				}
				else {
					//X-Experto
					filas = 30;
					columnas = 30;
				}
				crearTablero(tablero, filas, columnas);
				cout << "A continuacion se muestra el tablero generado: " << endl;
				imprimeTablero(tablero, filas, columnas);
				break;
			}
			case 'J': {
				cout << "Ingrese la cantidad de palabras a buscar: ";
				cin >> cantPalabras;
				aciertos = 0;
				crearMovimientos(movimientos);
				for (int i = 1; i <= cantPalabras; i++) {
					cout << "Ingrese la palabra " << i << ": ";
					cin >> palabra;
					buscaPalabra(tablero, filas, columnas, movimientos, palabra, &posIniX, &posIniY, &posFinX, &posFinY);
					if (posIniX == -1 && posIniY == -1) {
						cout << "La palabra no se encuentra en el tablero" << endl;
					}
					else {
						cout << "La palabra se encuentra en el tablero, inicia en la posicion (" << posIniX << "," << posIniY << ") y termina en la posicion (" << posFinX << "," << posFinY << ")." << endl;
						aciertos++;
					}
				}
				double porcentaje = (double)aciertos / cantPalabras;
				if (porcentaje >= 0.5) {
					cout << "El jugador gana porque ha encontrado el " << porcentaje * 100 << " de las palabras" << endl;
				}
				break;
			}
			case 'S': {
				centinela = 0;
				break;
			}
			default: {
				cout << "La opcion ingresada no es correcta" << endl << endl;
				break;
			}
		}
	}
}