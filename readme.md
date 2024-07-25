## Proyecto de la materia de Diseño de Algoritmos

# Juan Ignacio Castore

Proyecto que consiste en la implementación de heurísticas para resolver el problema del viajante de comercio asimétrico. 

## Heurísticas implementadas
- Nearest Neighbour: Selecciona el nodo más cercano al nodo actual y lo agrega al recorrido.

- Probabilistic Greeedy Constructive: Algoritmo diseñado por mi basado en la idea de vecino mas cercano, donde se elige uno entre los N nodos mas cercanos. Esto al correrlo con multiProbMultiSwap() me da soluciones que pueden ser mejores que las de nearest neighbour, a la vez que puede conseguir soluciones dentro del mismo vecindario con la optima, por eso luego se le aplica el multiSwap().

- Metaheurísticas: se implementaron un par de metaheurísticas, Haciendo uso y combinacion de otras heuristicas, como el multiProbMultiSwap() y el multiSwap().
