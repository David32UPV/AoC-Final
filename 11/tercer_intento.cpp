#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

// Función para imprimir un vector
void imprimirVector(const std::vector<int>& A) {
    for (int num : A) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Función para dividir una piedra en dos
std::pair<int, int> divisionPiedra(const std::vector<int>& A, int ini, int fin) {
    int m = ini + (fin - ini) / 2;
    int izquierda = 0, derecha = 0;
    for (int i = ini; i <= m; ++i) {
        izquierda = izquierda * 10 + A[i];
    }
    for (int i = m + 1; i <= fin; ++i) {
        derecha = derecha * 10 + A[i];
    }
    return {izquierda, derecha};
}

// Función para obtener los dígitos de un número
std::vector<int> obtenerDigitos(int numero) {
    std::vector<int> digitos;
    while (numero > 0) {
        digitos.insert(digitos.begin(), numero % 10);
        numero /= 10;
    }
    return digitos;
}

// Función para convertir un vector a un string (para usar como clave en memoización)
std::string vectorToString(const std::vector<int>& A) {
    std::string s;
    for (int num : A) {
        s += std::to_string(num) + ",";
    }
    return s;
}

void cargarArchivo(std::vector<int>& A) {
	std::string linea;
	std::ifstream archivo("input.txt");
	if (!archivo.is_open()) {
		throw std::runtime_error("No se ha podido abrir el fichero");
	}

	while (getline(archivo, linea)) {
		std::istringstream ss(linea);
		int numero;
		while (ss >> numero) {
			A.push_back(numero);
		}
	}
	archivo.close();
}

// Función recursiva con memoización para calcular el número de piedras
long long numeroPiedras(int pestanyeos, std::vector<int>& A, std::unordered_map<std::string, std::unordered_map<int, long long>>& memo) {
    std::string A_str = vectorToString(A);
    if (memo[A_str].find(pestanyeos) != memo[A_str].end()) {
        return memo[A_str][pestanyeos];
    }

    if (pestanyeos == 0) {
        memo[A_str][pestanyeos] = A.size();
        return A.size();
    }

    for (size_t i = 0; i < A.size(); ++i) {
        if (A[i] == 0) {
            A[i] = 1;
        } else {
            std::vector<int> digitos = obtenerDigitos(A[i]);
            if ((digitos.size() % 2) == 0) {
                auto [izquierda, derecha] = divisionPiedra(digitos, 0, digitos.size() - 1);
                A[i] = izquierda;
                A.insert(A.begin() + i + 1, derecha);
                ++i; // Saltar la piedra recién añadida
            } else {
                A[i] *= 2024;
            }
        }
    }

    memo[A_str][pestanyeos] = numeroPiedras(pestanyeos - 1, A, memo);
    return memo[A_str][pestanyeos];
}

// Función principal para leer el archivo y ejecutar el cálculo
void numPiedrasTotales() {
    std::string linea;
    std::vector<int> piedras;
	cargarArchivo(piedras);

    int num_blinking = 25;
    std::unordered_map<std::string, std::unordered_map<int, long long>> memo;
    int numero_piedras_totales = numeroPiedras(num_blinking, piedras, memo);
    std::cout << "Número de piedras totales: " << numero_piedras_totales << std::endl;
}

int main() {
    try {
        numPiedrasTotales();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

