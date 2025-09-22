# Unidad 5
---

### Sesión 1:

### ¿Qué representa la clase `Particle`?
La clase `Particle` es un **molde** para crear partículas.  
- Define **datos**: `x` y `y` como posición.  
- Define **acciones**: `move()` para el movimiento de la partícula.  

---
### ¿Cómo interactúan sus atributos y métodos?
- Los **atributos** (`x` y `y`) guardan la posición de la partícula.  
- El **método** `move(dx, dy)` cambia esos valores, actualizando la posición.

---
### ¿Qué es un objeto en C++ y cómo se relaciona con una clase?
- Una **clase** es como un molde o plano (define qué datos y qué acciones existen).  
- Un **objeto** es una instancia real creada a partir de esa clase.

---
### Explorando la memoria en C++
- Cada **objeto** ocupa su propio espacio en memoria.  
- Dos instancias (`p1` y `p2`) tienen direcciones diferentes, aunque sean del mismo tipo.  
- Los **atributos** (`x` y `y`) de un mismo objeto suelen estar almacenados de forma contigua.  
- El **sizeof(Particle)** muestra cuántos bytes ocupa la clase en memoria (la suma de sus atributos, considerando alineación).

---
### Análisis de diferencias en memoria

- **Clases simples vs complejas**:  
  - `Simple` con un solo atributo ocupa pocos bytes.  
  - `Complex`, aunque tenga más métodos, el tamaño solo depende de los atributos, no de los métodos.  

- **Datos estáticos**:  
  - Una variable `static` pertenece a la **clase**, no a cada objeto.  
  - Por eso, no aumenta el tamaño de las instancias.  
  - Ejemplo: en `StaticData`, el atributo `s` no cuenta dentro de `sizeof(StaticData)`.  

- **Datos dinámicos**:  
  - En `DynamicData`, el atributo `ptr` es solo un **puntero**, por lo que ocupa lo mismo que un puntero (4 u 8 bytes, según la arquitectura).  
  - La memoria real del arreglo (`new int[10]`) se guarda en el **heap**, no dentro del objeto.  
  - Por eso, el tamaño del objeto no cambia, pero sí la memoria total que consume el programa.

  ### Reflexión

- **¿Qué es un objeto desde la perspectiva de la memoria?**:  
**R//** Es un bloque de memoria que contiene sus atributos. Según cómo se cree, puede estar en el **stack** (si es automático) o en el **heap** (si se usa `new`).  

- **¿Cómo influyen los atributos y métodos en el tamaño y estructura del objeto?**:  
  - Los **atributos** influyen directamente en el tamaño del objeto (`sizeof`).  
  - Los **métodos** no aumentan el tamaño del objeto, porque el código se guarda en otra sección de la memoria (sección de texto/código).  
  - Si hay **punteros dinámicos**, el objeto guarda solo la dirección, mientras que la memoria real se reserva en el heap.  

- **Conclusión**:  
**R//** El diseño de clases debe balancear el uso de atributos normales, estáticos y dinámicos, ya que cada uno impacta distinto la memoria. 
Entender dónde vive cada parte ayuda a evitar fugas de memoria y a optimizar el rendimiento.

---
### Sesión 2:


**Objetivo**: comprender cómo se organizan los objetos en memoria.

**R//** En C++, los **datos de una clase** (atributos) se almacenan en el stack o en el heap dependiendo de cómo se cree el objeto, mientras que los **métodos** se guardan en
la sección de código del programa y son compartidos por todos los objetos.  
Cuando hay **métodos virtuales**, se crea una **vtable** (tabla virtual) que guarda punteros a las funciones. Cada objeto tiene un puntero a esta tabla,
lo que permite decidir en tiempo de ejecución qué versión del método ejecutar.

### Exploración de métodos virtuales

1. **¿Cómo afecta la presencia de métodos virtuales al tamaño del objeto?**  
**R//** Cuando una clase incluye al menos un método virtual, cada objeto de esa clase incorpora un **puntero oculto** (generalmente llamado *vptr*) que apunta a la vtable correspondiente.
Esto incrementa el tamaño del objeto (normalmente del tamaño de un puntero adicional).

2. **¿Qué papel juegan las vtables en el polimorfismo?**  
**R//** Las vtables permiten que en tiempo de ejecución se decida qué método ejecutar, según el tipo real del objeto. Esto hace posible el **polimorfismo dinámico**, es decir,
que un puntero o referencia a una clase base pueda invocar correctamente métodos de una clase derivada.

3. **¿Cómo se implementan los métodos virtuales en C++? Explica el concepto de vtable y cómo se utiliza.**  
**R//** Los métodos virtuales en C++ se manejan con algo llamado **vtable**, que es como una tabla que guarda las direcciones de las funciones. Cada objeto tiene un puntero a esa tabla, y cuando se llama un método virtual,
el programa busca en la vtable cuál función debe ejecutar. De esta forma, se asegura que se llame al método correcto según el tipo real del objeto, logrando el polimorfismo.

### Uso de punteros y referencias

Cuando uso punteros a funciones dentro de una clase, básicamente el objeto tiene que guardar la dirección de esa función en memoria. Eso hace que la instancia pueda ocupar un poco más.  

- En cuanto a la **relación con la vtable**, aunque ambos trabajan con direcciones de funciones, los punteros los asigno manualmente, mientras que la vtable se crea sola para manejar los métodos virtuales.  
- Sobre el **rendimiento**, usar punteros da más flexibilidad, pero la llamada tiene un paso extra y puede ser un poquito más lenta que llamar directo.  
- La **diferencia** está en que los punteros a funciones apuntan a funciones globales o estáticas, mientras que los punteros a métodos de clase además necesitan saber qué objeto están usando, por eso son más complejos.

### Reflexión individual

**¿Dónde residen los datos y métodos de una clase en la memoria?**  
**R//** Los datos de un objeto se guardan en memoria (en el stack o el heap, según cómo lo cree).  
Los métodos no se copian en cada objeto, sino que viven en una parte especial del programa y todos los objetos los comparten.

**¿Cómo interactúan las diferentes partes en tiempo de ejecución?**  
**R//** Cuando el programa corre, los datos del objeto se combinan con el código de los métodos.  
Si hay métodos normales, la llamada es directa.  
Si son virtuales, se usa una tabla (vtable) que decide qué versión del método ejecutar.

**Conclusión: cómo esta comprensión afecta el diseño de sistemas.**  
**R//** Saber dónde se guarda cada cosa y cómo se usa ayuda a pensar mejor las clases.  
Por ejemplo, me hace más consciente de qué atributos agregar, cuándo usar herencia o métodos virtuales, y cómo eso puede afectar memoria y rendimiento.
---

### Sesión 3: Implementación Interna de Encapsulamiento, Herencia y Polimorfismo

**Objetivo:** entender cómo se implementan las abstracciones del encapsulamiento, la herencia y el polimorfismo a nivel interno.

# Encapsulamiento

1. **¿Qué es el encapsulamiento y cuál es su propósito en la POO?**
Es la forma de proteger los datos de una clase, para que solo se usen a través de métodos o interfaces seguras. Sirve para evitar que cualquier parte del programa pueda cambiar valores internos sin control.

2. **¿Por qué es importante proteger los datos de una clase y restringir el acceso desde fuera de la misma?**
Porque mantiene la consistencia y seguridad de los datos. Si cualquiera pudiera modificarlos, sería fácil generar errores o comportamientos inesperados.

3. **¿Qué significa reinterpret_cast y cómo afecta la seguridad del programa?**
Es una forma de forzar la conversión entre punteros o referencias. Aunque permite acceder a memoria privada, rompe totalmente la seguridad que da el compilador, porque ignora las reglas del lenguaje.

4. **¿Por qué crees que se pudo acceder a los miembros privados de MyClass en este experimento, a pesar de que el compilador normalmente lo impediría?**
Porque en realidad los datos privados sí están guardados en el objeto, solo que el compilador bloquea su acceso directo. Usando punteros se puede “brincar” esa barrera, ya que la memoria está ahí físicamente.

5. **¿Cuáles podrían ser las consecuencias de utilizar técnicas como las mostradas en este experimento en un programa real?**
Podría causar errores graves, pérdida de datos, vulnerabilidades de seguridad y código imposible de mantener.

6. **¿Qué implicaciones tiene este experimento sobre la confianza en las barreras de encapsulamiento que proporciona C++?**
Que el encapsulamiento es una barrera lógica impuesta por el compilador, no una barrera física en memoria. Sirve para programar de manera segura, pero no es infalible si alguien decide romper las reglas.

# Herencia y Organización en Memoria

1. **¿Cómo se organizan los atributos en memoria?**
Cuando una clase hereda de otra, el objeto de la derivada primero guarda los atributos de la clase base, y luego sus propios atributos. Es como si la base fuera el “bloque inicial” del objeto, y lo derivado se añadiera después.

2. **¿Qué sucede si agregamos más niveles de herencia?**
La memoria se va organizando en “capas”: primero la base más lejana, después las siguientes, y al final los atributos de la clase más derivada. Esto asegura que siempre se pueda tratar un objeto derivado como si fuera de la base.

3. **¿Cómo se organiza en memoria un objeto de una clase derivada en C++?. ¿Cómo se almacenan los atributos de la clase base y de la derivada?**
Un objeto derivado en C++ se organiza en memoria colocando primero los atributos de la clase base y luego los de la clase derivada, en orden. Si hay varios niveles de herencia, se van sumando en cadena. Así, la parte de la base siempre está al inicio del objeto, lo que permite tratar al derivado como si fuera un objeto de la base.

# Polimorfismo y Vtables

1. **¿Cómo utiliza el programa las vtables para el polimorfismo?**
El programa usa una tabla llamada vtable, que guarda punteros a las funciones virtuales. Cada objeto polimórfico tiene un puntero oculto a su vtable, y cuando se llama a un método virtual, se busca en esa tabla cuál función ejecutar según el tipo real del objeto.

2. **¿Cuál es el impacto en el rendimiento?**
El polimorfismo introduce una pequeña sobrecarga, porque la llamada no es directa, sino que pasa por una consulta en la vtable. Sin embargo, este costo es mínimo y suele ser aceptable en la mayoría de aplicaciones.

3. **¿Cómo funciona el polimorfismo en C++ a nivel interno?**
Internamente, cuando se declara un método virtual, el compilador crea la vtable. Cada clase con métodos virtuales tiene su propia vtable, y cada objeto guarda un puntero a la tabla de su clase. Así, aunque accedas a un objeto a través de un puntero a la clase base, se ejecuta el método correcto de la clase derivada.

4. **¿Cómo se implementan internamente el encapsulamiento, la herencia y el polimorfismo?**
El encapsulamiento se implementa en el compilador: los atributos privados y protegidos siguen estando en memoria, pero no se permite su acceso directo fuera de la clase.
La herencia se refleja en el layout de memoria: primero se guardan los atributos de la clase base y luego los de la derivada.
El polimorfismo se implementa con las vtables, que permiten decidir en tiempo de ejecución qué método ejecutar.

**Análisis: ventajas y desventajas en términos de eficiencia y complejidad**
- Ventajas: más organización, reutilización de código, flexibilidad para manejar jerarquías de clases y escribir programas más modulares.
- Desventajas: aumenta la complejidad interna, puede haber sobrecarga de memoria por las vtables y un pequeño costo de rendimiento en las llamadas virtuales.
