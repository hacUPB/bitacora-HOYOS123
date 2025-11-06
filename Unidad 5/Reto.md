# Proyecto: Juegos Artificiales

El proyecto tiene como objetivo simular fuegos artificiales en un entorno digital usando **OpenFrameworks**.
La idea principal es crear diferentes tipos de explosiones que imiten lo que vemos en los cielos cuando se lanzan fuegos artificiales reales.  

Queremos lograr que el usuario pueda **interactuar** con la simulación:  
- Con el **click izquierdo y derecho del mouse** se lanzan dos tipos distintos de fuegos artificiales.  
- Al presionar la tecla **C (Change)**, el jugador cambia la "carga" o set de fuegos, y así puede acceder a otros dos tipos adicionales.  
- En total, el proyecto tiene **4 tipos de fuegos artificiales**, cada uno con un comportamiento diferente.  

---

## Conceptos de Programación Aplicados  

### Herencia  
- Se creó una clase base llamada `Firework`, que define las propiedades y métodos principales de un fuego artificial (posición, estado, funciones `update()` y `draw()`).  
- A partir de esa clase, se derivan varias clases hijas (`ExplodingFirework`, `FallingFirework`, `SpiralFirework`, `ColorShiftFirework`), cada una con un comportamiento propio.  
- Esto permite **reutilizar código común** y solo modificar lo que cambia en cada tipo de fuego.  

### Polimorfismo  
- Se utilizan punteros a la clase base `Firework` para manejar todos los tipos de fuegos artificiales en un mismo contenedor (`vector<Firework*> fireworks`).  
- Gracias al polimorfismo, aunque el vector almacena punteros de tipo `Firework`, en realidad puede contener cualquier subclase.  
- Cuando se llama a `update()` o `draw()`, se ejecuta la versión correspondiente a cada tipo, logrando que con el mismo código se manejen fuegos de distintos comportamientos.  

### Interactividad  
- El usuario controla los fuegos artificiales mediante el teclado y el mouse.  
- Esto refuerza la idea de un **juego experimental**, donde el jugador puede elegir qué tipo de explosión lanzar y explorar los distintos efectos.

### Encapsulamiento
En el proyecto también se aplicó este principio para mantener un mejor control sobre los datos internos de cada fuego artificial.  
Las propiedades como la posición, velocidad, color y estado se declararon como **privadas o protegidas** dentro de la clase base `Firework`.  
De esta forma, solo se pueden modificar mediante métodos públicos controlados (getters y setters), evitando cambios accidentales y asegurando que el comportamiento de cada fuego se mantenga coherente durante la simulación.

---

### Experimentación y rendimiento
Durante la experimentación se realizaron diferentes pruebas para observar cómo afectaban las decisiones de diseño al rendimiento general.  
Por ejemplo, se comparó el uso de **objetos estáticos** frente a la creación dinámica de partículas, notando que mantener una cantidad limitada de partículas activas en memoria mejora la estabilidad del programa. Cosa que se hace notar casi al final del video demostrativo, que la última carga que fue iniciada tenía demasiadas partículas y esto genera que el programa colapse o simplemente el computador deje de funcionar correctamente.

También se revisó el impacto del uso de **métodos virtuales** dentro del polimorfismo, identificando que, aunque añaden una pequeña sobrecarga, facilitan enormemente la extensibilidad del código.  
Por esa razón, se priorizó la claridad y la reutilización del código sobre la micro-optimización, buscando un equilibrio entre rendimiento y mantenibilidad.

---

## Resultados del Proyecto  
En el proyecto se puede observar lo 2 modos de fuegos artificiales que hay. En cada modo hay 2 estilos diferentes, que forman 4 "Cargas" diferentes... que hacen la acción cuando pulso click derecho o click izquierdo... El botón "C" de CHANGE, hace que estas cargas cambien y aparezcan cargas nuevas, como el siguiente video que voy a mostrar.

# Video demostrativo:
[Video Reto Unidad 5](https://youtu.be/rHvDJOZXW-U)
