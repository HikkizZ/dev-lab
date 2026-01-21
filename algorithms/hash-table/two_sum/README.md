# Two Sum

## 📌 Enunciado del problema

Dado un arreglo de enteros `nums` y un entero `target`, se deben retornar los índices de dos números **distintos** tales que su suma sea igual a `target`.

Restricciones:

- Existe **exactamente una solución válida**
- No se puede reutilizar el mismo elemento
- El orden de los índices retornados no es relevante

Ejemplos:

```text
Entrada:  nums = [2, 7, 11, 15], target = 9
Salida:   [0, 1]

Entrada:  nums = [3, 2, 4], target = 6
Salida:   [1, 2]

Entrada:  nums = [3, 3], target = 6
Salida:   [0, 1]
```

---

## 🎯 Contexto y objetivo

Este problema es un ejercicio algorítmico clásico, comúnmente utilizado para evaluar:

- Capacidad de descomposición de problemas
- Uso adecuado de estructuras de datos
- Comprensión de trade-offs entre tiempo y espacio
- Habilidad para pasar de una solución ingenua a una optimizada

El objetivo no es únicamente obtener una solución correcta, sino justificar una aproximación eficiente considerando las restricciones del problema.

---

## 🧠 Enfoques de solución

### 1. Enfoque base — Fuerza bruta

La solución más directa consiste en evaluar **todas las combinaciones posible**s de pares mediante dos bucles anidados.

**Idea princiapal:**
Para cada elemento del arreglo, se verifica si existe otro elemento cuya suma sea igual al `target`.

**Características:**

- Fácil de implementar
- Útil como línea base de corrección
- No escala adecuadamente para entradas grandes

**Complejidad:**

- Tiempo: O(n²)
- Espacio: O(1)

Este enfoque no cumple con el requerimiento adicional de optimización.

---

### 2. Enfoque optimizado — Uso de Hash Map

**Idea principal:**

Se recorre el arreglo una sola vez mientras se almacenan los valores previamente visitados en una estructura de acceso rápido (hash map).

Para cada elemento `x`:

- Se calcula su complemento: `target - x`
- Se verifica si dicho complemento ya fue visto
- Si existe, se retorna el índice almacenado y el índice actual

---

## 🧩 ¿Por qué usar un Hash Map?

El uso de un hash map permite:

- Búsquedas en tiempo constante promedio O(1)
- Evitar comparaciones redundantes
- Reducir significativamente la complejidad temporal del algoritmo

Este enfoque transforma el problema de:

> Comparar todos los pares posibles

a:

> Verificar si el complemento requerido ya existe

---

## ⚖️ Análisis de trade-offs

| Aspecto              | Fuerza bruta | Hash Map |
| :------------------- | :----------- | :------- |
| Complejidad temporal | O(n²)        | O(n)     |
| Complejidad espacial | O(1)         | O(n)     |
| Escalabilidad        | Baja         | Alta     |
| Uso de memoria       | Mínimo       | Mayor    |

La solución optimizada **intercambia memoria por rendimiento**, un trade-off común y aceptable en sistemas reales.

---

⏱️ Complejidad de la solución optimizada

- Tiempo: O(n)
- Espacio: O(n)

Esta complejidad cumple con el requisito de ser más eficiente que O(n²).

---

📝 Notas finales

- La solución por fuerza bruta es útil como punto de partida conceptual, pero no es adecuada para escenarios con grandes volúmenes de datos.
- El enfoque basado en hash map demuestra el uso eficiente de estructuras de datos para optimizar el rendimiento.
- Este problema ejemplifica un patrón fundamental en algoritmia: **sacrificar espacio para ganar tiempo.**
