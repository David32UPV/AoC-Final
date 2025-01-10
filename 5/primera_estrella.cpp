#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

// En esta nueva versión del problema, se simplifica el grafo para representar las reglas de las rutas. Es decir, en vez de calcular un orden topologico global, 
// y verificar si el update sigue el orden que marca una rule, simplemente verificamos para cada par (x, y) en el update, x precede a y según las rules.

// Aquí es válido el uso de tabla hash porque usamos las funciones insert y find (search) de la estructura de datos unordered_set, que tienen una complejidad de O(1) en promedio.

// Clase Grafo simplificado para representar las reglas de las rutas
class GrafoSimplificado {
private:
	// Usamos una estructura de datos llamada unordered_map, el cual se basa en una tabla hash para almacenar los pares clave-valor, pero no garantiza un orden en los elementos.
	// En este caso, cada nodo del grafo tiene una lista de nodos vecinos o adyacentes, que representan las rutas válidas.
	// Usamos una estructura de datos llamada unordered_set, que es una tabla hash que almacena elementos únicos (NO pares clave-valor), y no garantiza un orden en los elementos.
    std::unordered_map<int, std::unordered_set<int>> rutas;

public:
	// Método para agregar una regla al grafo: una regla es un enlace (origen, destino)
    void agregarRegla(int origen, int destino) {
        rutas[origen].insert(destino);
    }
	
	// Método para verificar si un update sigue las reglas de las rutas. Usamos size_t y ++i para mejorar la eficiencia y evitar problemas con tipos de datos al acceder 
	// a contenedores STL(e.g. el tamaño de un vector).
    bool updateValido(const std::vector<int>& update) {
        // Verificar si el update sigue las reglas de las rutas
        for (size_t i = 0; i < update.size(); ++i) {
            for (size_t j = i + 1; j < update.size(); ++j) {
                int origen = update[i];
                int destino = update[j];	// Destino va una posición más adelante que origen
				// Si NO hay una ruta válida entre origen y destino, el update es inválido
				// rutas[origen] es un unordered_set que almacena los nodos vecinos de origen, y find(destino) busca si destino está en el conjunto
				// Si find(destino) no encuentra destino en el conjunto, devuelve un end que indica que no se encontró el elemento
                if (rutas[origen].find(destino) == rutas[origen].end()) {
                    return false;
                }
            }
        }
		// Si tras recorrer el update no se encontró ninguna violación a las reglas, el update es válido
        return true;
    }
};

// Función para cargar las reglas y los updates desde el archivo
void cargarDatos(const std::string& nombreArchivo, GrafoSimplificado& grafo, std::vector<std::vector<int>>& updates) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }

    std::string linea;
    bool leyendoRules = true;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) {
            leyendoRules = false; // Cambiamos a leer updates
            continue;
        }
		// No nos hace falta crearnos rules como un vector de pares pues para esto están los nodos del grafo
        if (leyendoRules) {
            // Leer reglas
            std::istringstream ss(linea);
            int x, y;
            ss >> x;
            ss.ignore(1, '|'); // Ignorar el delimitador '|'
            ss >> y;
            grafo.agregarRegla(x, y);
        } else {
            // Leer updates
            std::istringstream ss(linea);
            std::vector<int> update;
            int num;
            while (ss >> num) {
                update.push_back(num);
                if (ss.peek() == ',') {
                    ss.ignore(); // Ignorar comas
                }
            }
            updates.push_back(update);
        }
    }
	// Importante cerrar el archivo siempre que se termine de usar
	archivo.close();
}

// Método principal para verificar si un update es correcto o no
void correctUpdate() {
    GrafoSimplificado grafo;
    std::vector<std::vector<int>> updates;

    // Cargar datos del archivo
	try{
    	cargarDatos("input.txt", grafo, updates);
	}
	catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << std::endl;
    }

	int total = 0;
	for(size_t i = 0; i < updates.size(); ++i){
		if(grafo.updateValido(updates[i])){
			// Si el update es válido, lo imprimimos por pantalla
			std::cout << "El update: ";
			// Ahora tenemos que obtener el elemento situado en la posición media de los updates correctos
			for(size_t j = 0; j < updates[i].size(); ++j){
				std::cout << updates[i][j];
				if(j != updates[i].size()-1){
					std::cout << ',';
				}
			}
			std::cout << " es válido porque cumple todas las condiciones" << std::endl;
			int pos_medio = updates[i].size() / 2;
			std::cout << updates[i][pos_medio] << std::endl;
			total += updates[i][pos_medio];
		}
		else{
			std::cout << "El update: "; 
			for(size_t j = 0; j < updates[i].size(); ++j){
				std::cout << updates[i][j];
				if(j != updates[i].size()-1){
					std::cout << ',';
				}
			}
			std::cout << " NO es válido porque NO cumple todas las condiciones" << std::endl;
		}
	}
	std::cout << total << std::endl;
}

int main() {
  correctUpdate();
  return 0;
}

