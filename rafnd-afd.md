## Algoritmo de Conversión: AFND a AFD (Construcción de Subconjuntos)

La conversión hacia un modelo determinista utiliza una Búsqueda en Profundidad (DFS). El objetivo es descubrir y mapear combinaciones de estados del AFND original para convertirlos en nuevos estados únicos y deterministas en el AFD resultante.

El siguiente diagrama ilustra cómo fluye la función `dfsConstruccion` y cómo se apoya en la estructura `HistorialProcesados` para enlazar estados y evitar ciclos infinitos:

```text
   AFND (Subconjuntos)         HistorialProcesados          AFD Resultante
  (tData actualNFA)              (Linked List)               (AutomataPtr)
=======================      =======================      ===================

1. ESTADO INICIAL
   +---------------+         +-------------------+        +-----------------+
   | Conjunto:     |         | Nodo Procesado    |        | StateNode       |
   | {q0}          | ------> | conjunto: {q0}    | -----> | name: "p0"      |
   +---------------+         | nombreDFA: "p0"   |        | isFinal: 0      |
           |                 +-------------------+        +-----------------+
           |                                                       |
           | Función: estadosAlcanzables({q0}, '0')                | d(p0, '0')
           v                                                       v

2. DESCUBRE NUEVO CAMINO
   +---------------+         +-------------------+        +-----------------+
   | Conjunto:     |         | Nodo Procesado    |        | StateNode       |
   | {q0, q1}      | ------> | conjunto: {q0,q1} | -----> | name: "p1"      |
   +---------------+         | nombreDFA: "p1"   |        | isFinal: 0      |
           |                 +-------------------+        +-----------------+
           |                                                       |
           | Función: estadosAlcanzables({q0,q1}, '0')             | d(p1, '0')
           v                                                       v

3. DETECCIÓN DE CICLO
   +---------------+         +-------------------+
   | Conjunto:     |         | Función:          |        (Crea transición
   | {q0, q1}      | ------> | buscarProcesado() | ----->  hacia "p1" sin
   +---------------+         | Retorna -> "p1"   |         crear nuevo nodo)
                             +-------------------+
