# Informe de Análisis: Estructuras para el Modelado de Autómatas Finitos en C

El presente informe analiza cinco enfoques distintos para implementar la estructura de datos de un Autómata Finito, y evalúa la eficiencia de cada modelo para definir la arquitectura base del proyecto.

---

## Objetivo

Construir estructuras para representar:

- **AFD** — Autómatas Finitos Deterministas
- **AFND** — Autómatas Finitos No Deterministas

Utilizando la definición formal:

$$A = (Q,\ \Sigma,\ \delta,\ q_0,\ F)$$

| Componente | Descripción |
|:---:|---|
| `Q` | Conjunto de estados |
| `Σ` | Alfabeto |
| `δ` | Función de transición |
| `q₀` | Estado inicial |
| `F` | Conjunto de estados de aceptación |

---

## Propuestas Analizadas

### 1. Lista de Transiciones Global

Consiste en guardar absolutamente todas las transiciones del autómata en una única lista general.

- ✅ **Lo bueno:** Es facilísimo de programar y de leer al principio.
- ❌ **Lo malo:** Es muy lento. Cada vez que el autómata lee un símbolo, tiene que recorrer la lista entera para saber hacia dónde moverse. Sirve, pero es ineficiente en autómatas grandes.

---

### 2. Transiciones dentro de cada Estado ⭐ *(La Mejor Opción)*

Plantea al autómata como lo que realmente es: un **grafo**. En lugar de una lista global, cada estado guarda internamente solo las transiciones que salen de él.

- ✅ **Lo bueno:** Es la opción más lógica y eficiente. El programa solo busca entre las opciones del estado actual, ahorrando muchísimo tiempo.
  Además, se adapta perfectamente a los TAD que pide la cátedra (usando `SET` para los destinos de un AFND). Iterar sobre estas transiciones locales va a ser directo y limpio.

---

### 3. Matriz Dispersa (Tabla de Transiciones)

Es llevar la clásica tabla del pizarrón al código. Se accede a los destinos cruzando `matriz[estado][símbolo]`.

- ✅ **Lo bueno:** Es rapidísimo — el acceso es instantáneo.
- ❌ **Lo malo:** Como los estados y símbolos son cadenas de texto (`STR`) y no números, armar una matriz en C obliga a programar diccionarios extra para traducir textos como `"q0"` a índices numéricos. Esto complica el código considerablemente.

---

### 4. Enfoque Funcional

Consiste en modelar la matemática pura, tratando a `δ(q, a)` estrictamente como una función de mapeo.

- ✅ **Lo bueno:** Teóricamente es muy prolijo.
- ❌ **Lo malo:** En la práctica, con C puro, se termina cayendo en los mismos problemas de lentitud que la Propuesta 1 (recorriendo estructuras para buscar la tupla exacta).

---

### 5. Estados Compuestos *(Solo para Determinizar)*

No es una opción para guardar el autómata base, sino una **herramienta temporal**. Agrupa varios estados del AFND en un solo *"Súper Estado"*.

- 🔧 **Para qué sirve:** Se usará exclusivamente como complemento cuando el algoritmo necesite convertir el autómata no determinista en uno determinista.

---

## Conclusión

> **La Propuesta 2** es la que ofrece el mejor equilibrio: es eficiente, mantiene el código ordenado y aprovecha al máximo la estructura de los TAD proporcionados.

La **Propuesta 5** queda reservada únicamente para resolver el proceso de determinización.
