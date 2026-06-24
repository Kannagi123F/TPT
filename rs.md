## Arquitectura de Memoria: Soporte para AFND

Para permitir el comportamiento de un Autómata Finito No Determinista (AFND), implementamos una estructura dinámica basada en **listas de listas**. En lugar de que una transición apunte a un único estado destino, apunta a un conjunto (`tData SET`), lo que permite múltiples ramificaciones simultáneas para un mismo símbolo.

A continuación, se ilustra cómo se mapea en memoria un estado `q0` que transita hacia `{q1, q2}` leyendo `'a'`, y hacia `{q3}` leyendo `'b'`:

```text
ESTADO PRINCIPAL
+-----------------+
| StateNode: "q0" |
| isFinal: 0      |
| transitions: ---+--- (Apunta a la lista de opciones)
+-----------------+  |
                     |
   +-----------------+
   |
   v
+------------------+         next         +------------------+
| Struct Transition| -------------------> | Struct Transition| ---> NULL
+------------------+                      +------------------+
| symbol = 'a'     |                      | symbol = 'b'     |
| to = (tData SET) |                      | to = (tData SET) |
+---------+--------+                      +---------+--------+
          |                                         |
          | (Apunta a los destinos)                 |
          v                                         v
   +--------------+                          +--------------+
   |   Nodo: "q1" |                          |   Nodo: "q3" |
   |   sig: ------+---+                      |   sig: NULL  |
   +--------------+   |                      +--------------+
                      v
               +--------------+
               |   Nodo: "q2" |
               |   sig: NULL  |
               +--------------+
