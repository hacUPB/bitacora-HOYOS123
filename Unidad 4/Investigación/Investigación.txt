# Serpiente en C++ con openFrameworks

# ACTIVIDAD 1
## Preguntas

### Sobre la estructura de datos

A)  **¿Qué representa un `Node` en el programa?**\
    **R//** Un segmento de la serpiente, con su posición `(x, y)` y un puntero
    al siguiente segmento.
------------------------------------------------------------------------
### Sobre el ciclo de la aplicación

B)  **¿Qué función se repite en cada frame para actualizar la lógica del
    juego?**
    **R//** `update()`.

------------------------------------------------------------------------
### Sobre el movimiento

C)  **¿De dónde obtiene su nueva posición cada nodo que *no* es la
    cabeza?**\
    **R//** De la posición previa de su nodo anterior.

D)  **¿Qué pasa con el espaciado entre los nodos si mueves el mouse muy
    rápido?**\
    **R//** Los nodos se separan más, porque cada uno copia la posición
    antigua del anterior (queda más distancia).

------------------------------------------------------------------------
### Sobre la interacción

E) **¿Qué sucede al presionar la tecla `c`?**\
    **R//** Se borra la lista completa: desaparece la serpiente.

------------------------------------------------------------------------
## Pregunta 

A) **¿Qué es una lista enlazada y en qué se diferencia de un arreglo en cuanto a la forma en que los elementos están almacenados en la memoria?**
**R//** Yo entendí que una lista enlazada es una estructura donde cada elemento (nodo) guarda sus datos y una referencia al siguiente. A diferencia de un arreglo, los nodos no están en posiciones contiguas de memoria; pueden estar dispersos, y lo único que los une son los punteros.

B) **¿Cómo se vinculan los nodos entre sí?**
**R//** Vi que se hace con punteros. Cada nodo tiene un Node* next que apunta al nodo siguiente. Así se arma la cadena.

C) **¿Cómo se gestiona la memoria en una lista enlazada?**
**R//** Yo aprendí que cuando hago new Node(...), el nodo se crea en el heap. Luego, cuando ya no lo necesito, debo usar delete para liberar ese espacio. Por eso en clear() se recorre la lista y se hace delete nodo por nodo.

D) **¿Qué ventajas tiene frente a un arreglo al insertar o eliminar elementos intermedios?**
**R//** Me quedó claro que en un arreglo hay que mover muchos elementos para abrir espacio o para cerrar huecos. En la lista enlazada solo cambio punteros: quito o pongo un nodo sin mover el resto.

E) **¿Cómo se asegura que no haya fugas de memoria en el código?**
**R//** Entendí que gracias al destructor ~LinkedList() que llama a clear(). Así cada nodo que se creó con new se destruye con delete. Eso evita que queden bloques de memoria ocupados sin usarse.

F) **¿Qué pasa en la memoria cuando invoco clear()?**
**R//** Yo lo veo así:

- Empiezo en head.
- Guardo un puntero al siguiente nodo.
- Borro el actual con delete.
- Paso al siguiente.
- Repito hasta llegar al final.
- Al terminar, head y tail quedan en nullptr y la memoria de todos los nodos fue liberada.

G) **¿Qué pasa en memoria al agregar un nuevo nodo al final?**
**R//** Cuando hago addNode, se crea un nuevo Node con new. Luego tail->next apunta a él, y tail ahora es ese nodo. Esto es muy rápido (O(1)) porque siempre sé dónde está el último.

H) **¿Cuándo usaría una lista enlazada en vez de un arreglo?**
**R//** Yo lo usaría cuando voy a insertar o eliminar elementos en medio de la colección muchas veces. Ahí la lista es más eficiente, porque en un arreglo habría que mover todo.

I) **¿Cómo aplicaría este conocimiento en otra estructura personalizada?**
**R//** Si quiero diseñar mi propia estructura, tendría en cuenta:

- Siempre borrar lo que creo con new.
- Tener un clear() y un destructor que limpien todo.
- Pensar si necesito acceso rápido por índice (me conviene arreglo) o flexibilidad en insertar/eliminar (me conviene lista).

J) **Diferencias entre C++ y C# en memoria**
**R//** En C# hay recolector de basura, entonces no me preocupo por delete. En C++ tengo más control, pero también más responsabilidad. La ventaja es optimización fina, el reto es no olvidar liberar memoria.

K) **Arte generativo con listas enlazadas**
**R//** Yo tendría cuidado de no crear nodos infinitamente sin borrarlos. Me aseguraría de llamar clear() cuando ya no los necesito, y tal vez reciclar nodos en vez de destruirlos, para no estar pidiendo memoria al sistema todo el tiempo.

L) **Pruebas**
**R//** Si quisiera probar el programa:

- Probaría crear la lista y verificar que size crece al agregar nodos.
- Llamaría a clear() y revisaría que size sea 0.
- Haría update() con el mouse quieto y vería que los nodos se alinean.
- Movería el mouse rápido y comprobaría que los nodos se separan.
- Probaría presionar c y luego r para ver si la serpiente desaparece y se reinicia bien.

---------------------------------------------

# ACTIVIDAD 2

## Preguntas sobre el programa en C++ y openFrameworks

A) **¿Cuál es la diferencia entre cómo funciona la pila (`Stack`) y la cola (`Queue`) en este programa?**  
   **R//** La pila funciona con la lógica *LIFO* (el último en entrar es el primero en salir), mientras que la cola usa *FIFO* (el primero en entrar es el primero en salir).  

B) **¿Qué papel cumple el puntero `next` dentro de la clase `Node`?**  
   **R//** Sirve para enlazar un nodo con el siguiente, formando la lista enlazada que sostiene tanto la pila como la cola.  

C) **¿Por qué en `push` (pila) el nuevo nodo se conecta con el que antes era `top`?**  
   **R//** Porque en una pila los nuevos elementos siempre se agregan arriba, entonces el nodo nuevo debe apuntar al que antes estaba en la cima.  

D) **¿Qué pasaría si no se usara `delete` en `pop()` o `dequeue()`?**  
   **R//** Se generaría una fuga de memoria, porque los nodos eliminados seguirían ocupando espacio aunque ya no los use el programa.  

E) **¿Qué función cumple `display()` en la visualización de los nodos en pantalla?**  
  **R//** Recorre todos los nodos y dibuja un círculo en la posición que tiene guardada cada uno.  

F) **¿Qué sucede en pantalla al presionar `'a'` y qué sucede al presionar `'d'` en cada una de las estructuras?**  
   **R//** Con `'a'` se crea un círculo en la posición del mouse y se agrega a la estructura (pila o cola). Con `'d'`, en la pila se elimina el último círculo agregado, y en la cola se elimina el primero que había entrado.

# Pruebas y Reflexión sobre el Stack en C++

## 1. ¿Cómo probar las partes del programa y el programa completo?

### a) Pruebas unitarias de las funciones
- **push()**  
  Acción: Apilar un nodo con coordenadas conocidas (ej. `push(100,200)`).  
  Resultado esperado: `top->position == (100,200)`.

- **pop()**  
  Acción: Apilar 3 nodos y luego desapilar 1.  
  Resultado esperado: El nuevo `top` corresponde al penúltimo nodo apilado.

- **clear()**  
  Acción: Apilar varios nodos y luego llamar a `clear()`.  
  Resultado esperado: `top == nullptr` y no hay fugas de memoria.

- **display()**  
  Acción: Apilar nodos en diferentes posiciones y dibujar.  
  Resultado esperado: Se ven los círculos en la pantalla en las posiciones correctas.

### b) Prueba integrada del programa completo
1. Ejecutar la aplicación.
2. Presionar `'a'` varias veces en diferentes posiciones del mouse.  
   - **Esperado**: aparecen círculos en esas posiciones.  
3. Presionar `'d'` varias veces.  
   - **Esperado**: los círculos desaparecen en orden inverso a cómo se agregaron.  
4. Cerrar el programa.  
   - **Esperado**: no hay errores de memoria reportados (se verifica con herramientas como *Valgrind* o el debugger).

---

## 2. Preguntas de reflexión para el stack

1. **¿Cómo se gestiona la memoria en una implementación manual de un stack en C++?**  
   **R//** Se gestiona con `new` al crear nodos y `delete` al desapilarlos. Esto da control total, pero aumenta el riesgo de fugas o *dangling pointers* si no se libera memoria correctamente.

2. **¿Por qué es importante liberar la memoria cuando se desapila un nodo en un stack?**  
   **R//** Porque si no se libera, los nodos eliminados siguen ocupando memoria (fugas). En programas de larga duración esto puede saturar la RAM.

3. **¿Qué diferencias existen entre usar un stack de la STL (`std::stack`) y crear un stack manualmente?**  
   **R//** `std::stack` abstrae la gestión de memoria y es más seguro, pero no da control sobre cómo se almacenan los datos. Una implementación manual permite optimizar o personalizar, a costa de mayor riesgo de errores.

4. **¿Cómo afecta la estructura de un stack al orden de acceso y eliminación de elementos?**  
   **R//** El acceso es *LIFO*: siempre se elimina el último que entró. Esto es ideal para problemas como deshacer acciones (undo), recorridos en profundidad (DFS), o evaluación de expresiones.

5. **¿Cómo podrías modificar el stack para almacenar tipos de datos más complejos?**  
   **R//** Podría usar punteros a objetos o plantillas (`template<class T>`). Para evitar fugas, sería recomendable usar *smart pointers* (`std::unique_ptr` o `std::shared_ptr`).

---

## 3. Preguntas de autoevaluación

1. ¿Puedo explicar detalladamente cómo funciona el proceso de apilar y desapilar nodos en un stack, incluyendo la gestión de memoria?
**R//**   
2. ¿Soy capaz de identificar y corregir una fuga de memoria en una implementación de stack manual?
**R//** 
3. ¿Puedo modificar el stack para que incluya una función que busque un elemento específico, sin alterar el orden de los elementos apilados?
**R//**   
4. ¿Entiendo cómo la estructura LIFO del stack afecta el flujo de datos y puedo dar ejemplos de problemas que se resuelvan mejor con un stack?
**R//**   
5. ¿Puedo implementar y depurar un stack para tipos de datos más complejos, asegurándome de que no haya fugas de memoria ni errores de puntero?
**R//** 
