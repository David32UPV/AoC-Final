# Memoria día 5 del AoC
## Descripción básica del problema
En el problema propuesto (hablamos de la primera estrella), nos piden que unas páginas deben ser impresar en un orden específico. Para ello nos dan una serie de reglas
y unas actualizaciones (el orden de impresión de las páginas). Por ejemplo, si tenemos la regla 47|53, ésta nos indica que si los 2 numeros de página aparecen en una misma
actualización, la página número 47 debe aparecer antes que la 53 en algún punto de la actualización. Siguiendo éstas indicaciones, debemos determinar los updates que son
correctos, sacar el elemento del medio de dichos updates y sumarlos entre sí.

## Descripción técnica + Alternativas/Evolución del código
En la carpeta encontramos 3 ficheros de código: "fuerza-bruta.cpp", "prueba-grafos.cpp" y "primera-estrella.cpp". El primero es la primera implementación que se nos ocurrió
para resolver el problema, la cual consiste en recorrer todas las posibles combinaciones de los updates y comprobar si son correctos o no con 3 bucles anidados(el 
primer bucle recorre las rules para cada update, el segundo recorre los updates[filas de la matriz de updates], y el tercero recorre los elementos de cada update
[columnas de la matriz de updates]), lo cual es bastante ineficiente pero resuelve el problema de forma correcta. 

El segundo fichero es un intento de resolver el problema con grafos usando orden topologico, pero no conseguimos implementarlo correctamente para el 
input.txt pero sí para el ejemplo.txt. 
Pudimos observar que éste es un buen método para resolver el problema, pues las reglas no son más que enlaces (X|Y = (X, Y)), donde X e Y son nodos del grafo (números de páginas).
Tras mandar un correo al profesor explicandole nuestra situación, nos dijo que ésto sucedía porque en el input.txt no hay ningún nodo inicial con grado de entrada 0, 
luego no se puede aplicar un orden topológico como tal. Tras que nos sugiriera que intentaramos resolverlo con un orden topológico simplificado, pensamos en cómo sería 
aplicar esto a nuestro problema. 

De esta última idea surge el tercer fichero, que es el definitivo y el que sí funciona para input.txt. Como se puede observar, la clase grafo se ha simplificado para
que en vez de hacer un orden topológico, simplemente verifique que para cada par (x, y) en el update, x preceda a y según las reglas. Para garantizar una mayor eficiencia,
almacenamos en un unordered-map (que se basa en una tabla hash) las rutas válidas, representadas por la lista de nodos vecinos que tiene cada nodo del grafo. Con esta 
estructura de datos (unordered-map), podemos, de manera sencilla, agregar reglas o enlaces al grafo con insert() y buscar un elemento en un conjunto con find() para 
comprobar si un update es o no válido. Como el resultado del problema radica en la función updateValido(), pasemos a analizarla profundamente. Primero debemos recorrer las
filas de la matriz de updates, y nos guardamos en la variable origen el primer elemento de la fiña y en destino el elemento siguiente (i+1). rutas[origen] es un unordered-set
(tabla hash que almacena elementos únicos [como si fuera un cojunto de valores]), que almacena los nodos vecinos de origen, y find(destino) busca si destino está en 
dicho conjunto. Si no está, devolvemos false, si está, seguimos con el siguiente update. Si hemos recorrido todos los updates y no hemos devuelto false, devolvemos true.

## Valoración personal
Una de las diferencias que podemos encontrar en el código final con respecto a los anteriores es el uso de size-t y ++i en vez de int y i++ en los bucles for, 
lo cual es una buena práctica de programación en C++ que hemos podido descubrir a la hora de buscar la precaucion y la eficiencia en el código.
Lo más importante que hemos aprendido resolviendo este problema ha sido pasar de un código ineficiente pero funcional hecho en fuerza bruta a un código eficiente usando 
estructuras de datos avanzadas como grafos y tablas hash. 


