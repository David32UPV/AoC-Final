#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <map>

// Función para obtener los dígitos de un número
std::vector<int> obtenerDigitos(long long numero) {
    std::vector<int> digitos;
    while (numero > 0) {
        digitos.insert(digitos.begin(), numero % 10);
        numero /= 10;
    }
    return digitos;
}

// Función para dividir una piedra en dos
std::pair<int, int> divisionPiedra(const std::vector<int>& A) {
    int m = A.size() / 2;
    int izquierda = 0, derecha = 0;
    for (int i = 0; i < m; ++i) {
		// Reconstruimos los números de forma que en la izquierda estarán los digitos del indice 0 a la mitad del vector de A
        izquierda = izquierda * 10 + A[i];
    }
    for (int i = m; i < A.size(); ++i) {
        derecha = derecha * 10 + A[i];
    }
    return {izquierda, derecha};
}

// Función para cargar datos desde un archivo
void cargarArchivo(std::vector<int>& piedras) {
    std::ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        throw std::runtime_error("No se ha podido abrir el fichero");
    }

    int numero;
    while (archivo >> numero) {
        piedras.push_back(numero);
    }
    archivo.close();
}

// Mapa para memoización: memo[tamaño_piedra][pestañeos] = número de piedras resultantes
// Utilizamos un mapa anidado para asociar el numero de piedras resultantes a 2 claves independientes: el tamaño de la piedra (tamano) y el número de pestañeos(pestanyeos)
// El primer mapa (memo[tamano]) almacena información sobre el tamaño de la piedra, y el segundo mapa (memo[tamano][pestanyeos]) almacena información sobre el número de pestañeos
// para dicho tamaño de piedra
std::unordered_map<long long, std::unordered_map<int, long long>> memo;

// Función recursiva con memoización para calcular el número de piedras resultantes
// En esta versión definitiva, en vez de restar el numero de pestañeos cada vez que recorremos el vector de piedras, lo hacemos cada vez que procesmos una piedra (lo cual es
// más eficiente)
long long calcularPiedras(long long tamano, int pestanyeos) {
    // Caso base: Cuando hemos acabado todos los pestanyeos, devolvemos 1 que representa la piedra final
    if (pestanyeos == 0) {
        return 1;
    }

    // Esto sería parecido a hacer memo[tamano][pestanyeos] != 0, pero para hacerlo de forma eficiente (y aprovechando que tenemos un mapa anidado), verificamos si
	// existe la clave pestanyeos dentro del submapa asociado a la clave tamano en memo. Así, evitamos insertar valores por defecto en memo (e.g. 0) si la clave no está
    if (memo[tamano].count(pestanyeos)) {
        return memo[tamano][pestanyeos];
    }

    // Proceso recursivo
    long long total = 0;
	
	// Si el tamaño de la piedra es 0, lo convertimos a piedra de tamaño 1 y restamos un pestañeo pues hemos procesado una piedra
    if (tamano == 0) {
        total = calcularPiedras(1, pestanyeos - 1);
    } else {
        // Dividir en dígitos
        std::vector<int> digitos = obtenerDigitos(tamano);
        // Si el número de dígitos de la piedra es par, dividimos la piedra en dos mitades y calculamos el número de piedras resultantes para cada mitad
		if ((digitos.size() % 2) == 0) {
			// Usamos auto o std::pair para almacenar los valores de la división de la piedra (izquierda y derecha)
            auto [izquierda, derecha] = divisionPiedra(digitos);
			// La llamada recursiva procesa primero la mitad izquierda de la piedra, y luego la mitad derecha, y al final se suman los resultados. Este esquema
			// se asemeja a un recorrido en preorden de un árbol binario (recorrido en profundidad que va desde la raiz hasta las hojas (cuando pestanyeos == 0)),
			// pero en verdad usamos la técnica de Divide y Vencerás para dividir la piedra en mitades y procesarlas por separado.
            total += calcularPiedras(izquierda, pestanyeos - 1);
            total += calcularPiedras(derecha, pestanyeos - 1);
        } else {
            // Si no se cumple ningún caso, multiplicamos el tamaño de la piedra por 2024 y restamos un pestañeo. Para la multiplicación, usamos static_cast<long long> para
			// evitar desbordamientos en la multiplicación
            total += calcularPiedras(static_cast<long long>(tamano) * 2024, pestanyeos - 1);
        }
    }

	// Tras las llamadas recursivas, almacenamos el resultado en memo[tamano][pestanyeos] para evitar recalcularlo en futuras llamadas, y lo devolvemos
    memo[tamano][pestanyeos] = total;
    return total;
}

// Función principal para calcular el número total de piedras
void numPiedrasTotales() {
    std::vector<int> piedras;
	try{
    	cargarArchivo(piedras);
	}catch(const std::exception& e){
		std::cerr << "Error: " << e.what() << std::endl;
	}

    int num_blinking = 75;
    long long totalPiedras = 0;

	// Para cada tamaño de piedra, calculamos el número de piedras resultantes y lo sumamos al total
	for (int tamano : piedras) {
		totalPiedras += calcularPiedras(tamano, num_blinking);
	}
	std::cout << "Número de piedras totales: " << totalPiedras << std::endl;

}

int main() {
    numPiedrasTotales();
    return 0;
}

