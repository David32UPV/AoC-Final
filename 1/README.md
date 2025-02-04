# Memoria día 1 del AoC
## Descripción básica del problema
En el problema propuesto (hablamos de la primera estrella), nos piden sacar la diferencia entre: el elemento más pequeño del array/vector izquierdo y el elemento más pequeño
del array/vector derecho, el segundo elemento más pequeño del vector izquierdo con el segundo elemento más pequeño del vector derecho, y así sucesivamente hasta
llegar a los elementos más grandes de ambos vectores. Finalmente, nos piden devolver la suma de las diferencias realizadas.

## Descripción técica + Alternativas 
A primera vista el problema puede parecer lioso en el sentido de tener que relacionar los elementos de los 2 vectores en función de su tamaño, pero la solución es
bastante sencilla si ordenas ambos arrays. Al ordenarlos, simplemente tienes que sacar la diferencia entre los elementos de cada uno de los arrays e ir sumando
esas diferencias en una variable total. Para realizar esta ordenación de los 2 vectores podríamos haber utilizado la función sort() que ofrece la biblioteca "algorithm"
de C++ como alternativa. Sin embargo, al hacer esto no controlamos cómo se ordena el vector. Por ello, pensamos en que es preferible implementar de forma eficiente 
dicha ordenación mediante el algoritmo de quicksort usando la técnica algorítmica de Divide y Vencerás. 

De forma resumida, la aplicación de Divide y Vencerás en este algoritmo de ordenar un vector se basa en lo siguiente: utilizamos uno de los 
elementos del mismo como pivote (en nuestro caso usamos el primer elemento), y mediante swaps() conseguimos situar el pivote en una posición del vector de
forma que los elementos a la izquierda del pivote son menores que éste, y los situados a la derecha de éste son mayores. 
Tras esto, ordenamos los elementos situados a la izquierda del pivote, luego los situados a la derecha, y al final juntamos ambos resultados de forma que obtendríamos 
el vector resultante ordenado de menor a mayor.

## Justificación de por qué hemos elegido este problema entre el resto de retos del AoC
Como éste es el primer día del Advent of Code y se puede aplicar DyV de forma sencilla, nos decantamos por este problema para aplicar esta técnica algorítmica. Sin embargo,
en el día 11 también hemos aplicado Divide y Vencerás de una forma más elegante para que el programa fuera lo suficientemete eficiente como para poder resolver el problema.

## Valoración personal
Finalmente, la resolución de este problema aplicando DyV nos ha dado el primer acelerón necesario para poder resolver los días posteriores del AoC con un 
enfoque recursivo y con código modulable en funciones. Por ejemplo, en este primer problema definimos una función para cargar el archivo que más o menos reutilizamos 
en el resto de problemas, además de una función para imprimir el vector del fichero input.txt. 
