#include <iostream>
#include <cstdlib>
#include <ctime>

void cleanArr(int *Arr, const int *EndPos) {
	for (; Arr != EndPos; Arr++)
		*Arr = 0;
}

void function(int *Input, int *Output_1, int *Output_2, int Tam, bool (*pf)(int)) {
	int *Temp1 = Output_1 + Tam;
	int *Temp2 = Output_2 + Tam;

	for (int *Temp = Input; Temp != Input + Tam; Temp++) {
		if ((*pf)(*Temp)) {
			*(Output_1++) = *Temp;
		} else {
			*(Output_2++) = *Temp;
		}
	}
//	cleanArr(Output_1, Output_1 + Tam);
//	cleanArr(Output_2, Output_2 + Tam);
	cleanArr(Output_2, Temp2);
	cleanArr(Output_1, Temp1);
}

void fillArr(int *Arr, int tam) {
	int *temp = Arr;
	int *EndPos = Arr + tam;
	srand((int) time(0));
	for (; temp != EndPos; temp++)
		*temp = (rand() % 999) + 1;
}

void printArr(std::string Name, int *Arr, int Tam) {
	int *temp = Arr;
	int *EndPos = Arr + Tam;

	std::cout << Name << ": ";
	for (; temp != EndPos; temp++)
		std::cout << *temp << " ";
	std::cout << std::endl;
}

bool isEven(int value) {
	return value % 2 == 0;
}

bool isMultipleOf3(int value) {
	return value % 3 == 0;
}

bool isLeapYear(int value) {
	return value % 4 == 0 and value % 100 != 0 or value % 400 == 0;
}

int main() {
	int tam;
	int op;

	do {
		std::cout << "Introduzca tamaño del array: ";
		std::cin >> tam;
		bool (*pFunction)(int);
		int *arrInp = new int[tam];
		int *arrOut1 = new int[tam];
		int *arrOut2 = new int[tam];

		fillArr(arrInp, tam);
		printArr("Input   ", arrInp, tam);
		printArr("Output 1", arrOut1, tam);
		printArr("Output 2", arrOut2, tam);
		std::cout << "1. Es numero par" << std::endl;
		std::cout << "2. Es multiplo de 3" << std::endl;
		std::cout << "3. Es un año bisiesto" << std::endl;
		std::cout << "4. Salir" << std::endl;
		std::cout << "Elija una opcion: " << std::endl;
		std::cin >> op;
		switch (op) {
			case 1:
				pFunction = isEven;
				break;
			case 2:
				pFunction = isMultipleOf3;
				break;
			case 3:
				pFunction = isLeapYear;
				break;
			default:
				return 0;
		}
		function(arrInp, arrOut1, arrOut2, tam, pFunction);
		printArr("Input   ", arrInp, tam);
		printArr("Output 1", arrOut1, tam);
		printArr("Output 2", arrOut2, tam);
		std::cout << "\n\n\n\n";
	} while (true);
}