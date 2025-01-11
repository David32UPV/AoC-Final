# Memoria día 11 del AoC
## Descripción básica del problema
En el problema propuesto (hablamos de la segunda estrella), nos piden determinar el número de piedras resultantes tras hacer 75 pestañeos, de forma que las piedras se 
mantengan en una línea recta perfecta(esta última parte es la que más problemas y bloqueos nos ha dado para poder resolver el problema de forma eficiente). 
Por cada pestañeo, las piedras cambian simultáneamente de acuerdo con la primera regla aplicable de la lista de casos dada por el enunciado del problema.

## Descripción técnica + Alternativas/Evolución del código
En la carpeta encontramos 5 ficheros de código, de los cuales el definitivo es "primera_estrella.cpp", siendo el resto y como su nombre indica, intentos que no funcionaban
correctamente, a excecpión del fichero "intento_arboles.cpp", con el cual intentamos resolver el problema usando una clase que representa un arbol binario de búsqueda y vimos que
el codigo ni siquiera funcionaba. Nos gustaría destacar que nos quedamos atascados en el fichero "primer_intento.cpp" durante un par de días porque no lográbamos entender cómo 
mejorar la memoización si la recursividad funcionaba. Preguntando a amigos que ya habian solucionado el problema pudimos mejorar la eficiencia. Como en el enunciado
pone que las piedras debían mantenerse perfectas en su arreglo (vector de piedras), al principio pensamos que el numero de pestanyeos debía decrementar en uno
cada vez que se recorría el vector de piedras (caso base: ini > fin), y que la funcion de memoria debía de guardarse en cada llamada recursiva el tamaño del vector de piedras
y el numero de pestañeos restantes a dicho tamaño del vector (para que así al final de la recursión me devolviera el número total de piedras en el vector de piedras). 
Sin embargo, ésto no mejoraba la eficiencia del código, ya que no servía de nada lo que se guardaba la matriz de memoria M, pues no evitaba recalculos en las llamadas recursivas. 

A continuación, se nos ocurrió crear otra matriz de memoria booleana que me guardara las posiciones de la matriz de memoria principal que habia visitado para asi evitar volver a 
hacer cálculos (matriz visitados), pero como ya he mencionado previamente, al estar mal interpretada mi matriz de memoria, esta matriz adicional no produjo ningún efecto innovador
en la ejecución del programa. 

Como no sabiamos cómo mejorar la matriz de memoria, pedimos ayuda a unos amigos que nos dieron otro enfoque del problema un poco distinto. Se trataba de que en vez de reducir
el número de pestañeos cada vez que recorro todo el vector de piedras, lo redujeramos cada vez que procesamos una piedra, de forma que calculamos directamente el número
de piedras resultantes de dividir o procesar una piedra individual durante cada pestañeo. De esta forma reducimos los pestañeos de forma más localizada, piedra por piedra, y 
solo hacemos el trabajo necesario para calcular el resultado de cada piedra. 
Por otro lado, nos dimos cuenta que al procesar piedra por piedra teníamos que cambiar la estructura de nuestra función de memoria (memo o M). Para que fuera más eficiente,
la transformamos en un unordered_map anidado, para así asociar el número de piedras resultantes a 2 claves independientes: el tamaño y el número de pestañeos de la piedra actual,
tal que el primer mapa (memo[tamano]) almacena información sobre el tamaño de la piedra, y el segundo mapa (memo[tamano][pestanyeos]) almacena información sobre el número de 
pestañeos restantes para dicho tamaño de piedra. 

La función recursiva calcularPiedras() también la modificamos dentro de este nuevo contexto de la resolución del problema. Primero y lo más obvio que no se nos ocurrió era
que el número total de piedras devuelto por la función iba a ser muy grande, por lo que éste no cabe en un int. Por ello, tuvimos que cambiar la cabecera de la función a 
long long para que el resultado cupiera en el tipo de datos devuelto por la función (long long total). Tambien modificamos el caso base de la función de memoria: 
al tratarse de un mapa anidado y no de un vector de vectores (matriz dinámica), en vez de hacer el típico caso base de if(memo[tamano][pestanyeos] != -1) -> 
return memo[tamano][pestanyeos]; verificamos si existe la clave pestanyeos dentro del submapa asociado a la clave tamano en memo. Así, evitamos insertar valores por defecto
en memo (como -1 si no hemos visitado esa posición en la función de memoria).
Esto lo conseguimos con la función count() que podemos usar en un std::unordered_map (if(memo[tamano].count(pestanyeos)) -> return memo[tamano][pestanyeos];

El siguiente caso es cuando el numero de la piedra es 0, en el que simplemente hay que sustituirlo por un 1, pero ahora como los pestañeos se decrementan al procesar cada
piedra, debemos decrementar el numero de pestañeos.

Siguiendo con la explicación del código de "primera_estrella.cpp", para saber si el número de la piedra es par, lo que hacemos es almacenarnos en un vector de enteros el número
de dígitos del tamaño de la piedra, llamando a la función obtenerDigitos(). A continuación, si el tamaño de dicho vector es par, dividimos la piedra en 2 mitades llamando
a la función divisionPiedra(), la cual me devuelve un par de valores tal que el primer valor es el numero de la nueva piedra izquierda y el segundo valor es el numero de
la nueva piedra derecha. Posteriormente, incrementamos la variable total de tipo long long (para que quepa el resultado final en ella) las llamadas recursivas de procesar
la piedra izquierda, por un lado, y la piedra derecha, por otro lado. Este procedimiento que hacemos aquí se basa en la técnica algorítmica de Divide y Vencerás, ya que 
dividimos las piedras en 2 mitades y procesamos cada mitad por separado, para luego sumar los resultados de ambas mitades en la variable total (también decrementamos
el numero de pestañeos en 1 para cada una de las 2 mitades).
Da la casualidad de que este enfique se asemeja a un recorrido en preorden de un arbol binario de búsqueda (recorrido en profundidad que va desde la raíz [la cual 
sería cada piedra inicial del vector de piedras inicial] hasta las hojas [piedras que tienen pestañeo = 0]), ya que primero procesamos las piedras de la izquierda y 
luego las de la derecha, pero en sí es una aplicación de la técnica de Divide y Vencerás.

Finalmente, queda el caso que surge cuando no se cumplen ninguno de los 2 anteriores, el cual multiplica el número de la piedra actual (tamano) por 2024 (hemos puesto un 
cast para que no hayan problemas de desbordamiento en la multiplicación), y, al igual que pasa con el caso en el que el tamaño de la piedra es 1, 
aquí también decrementamos el número de pestañeos en 1.

En la función principal, no podemos llamar a la función recursiva una vez y ya está, puesto que hay que tener en cuenta el tamaño de cada piedra del vector de piedras 
que leemos del fichero input.txt. Por eso llamamos a la función dentro de un bucle for de tipo rango: para cada tamaño de piedra, calculamos el número de piedras resultantes
(llamando a la función recursiva) y eso lo sumamos al número total de piedras tras completar los pestañeos pedidos (en nuestro caso 75). 

Como adición, podemos oberservar que en los ficheros de segundo y tercer intentos intentamos arreglar el problema usando simplemente un unordered_map para la función de 
memoria y un tipo de datos long long para la cabecera de la función recursiva, pero como no modificamos la estructura de la función de memoria en sí (seguiamos procesando
todo el vector de piedras y no piedra por piedra puesto que los pestañeos solo los decrementamos al final de la funcion recursiva), pues el código seguía sin ser eficiente
para poder resolver el problema.

## Justificación de por qué hemos elegido este problema entre el resto de retos del AoC
El enunciado y la traza del problema son muy claros a la vista de que hay que usar recursividad para resolverlos. Es de los problemas más fáciles de ver en los que 
se puede aplicar programación dinámica y sobre todo cuando al ejecutar el código no para de salirte el mensaje de "segmentation fault", con lo que tras verlo ya sabes
que solo usar recursividad no es suficiente. Tras ir solucionandolo y ver qué podíamos aplicar tabla hash en forma de unordered_map en la función de memoria para mejorar la 
eficiencia en vez de un vector de vectores, además de la técnica de Divide y Vencerás, vimos que este problema tenía un gran potencial, comparado con el resto de problemas
del calendario, para poder aplicar varios temas de los vistos en clase.

## Valoración personal
Lo más importante que hemos aprendido resolviendo este problema ha sido manejar la frustación de no saber cómo mejorar la eficiencia de un código cuya recrusividad
funciona, pero que no es lo suficientemente eficiente para resolver el problema. Tras quedarnos atascados en el mismo problema durate varios días y no saber cómo mejorarlo, 
pudimos, gracias a la ayuda de otros compañeros, envolver la solución del problema en otro contexto para mejorar la funcion de memoria. Por otro lado, hemos aprendido 
la importancia del uso de std::unordered-map en un lenguaje como C++ para mejorar la eficiencia del código, y del tipo de datos long long para evitar tener problemas de 
desbordamiento. 

