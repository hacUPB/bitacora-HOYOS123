####Lenguaje de alto nivel

## **Investigación**

### Actividad 1

# **¿Cuál es el resultado que se obtiene al ejecutar este programa? (Punto 4)**
**R//** Al compilar el fondo se hizo de color negro y el cursor del Mouse se convirtió en un círculo blanco de radio 20 que se mueve en el eje X y Y.

### Actividad 2

# **¿Qué fue lo que incluimos en el archivo .h?**
**R//** Incluimos que el Mouse se mueva y genere una serie de partículas que pueden cambiar de color.

# **¿Cómo funciona la aplicación?**
**R//** Estas partículas aparecen dejando un rastro del camino que trazó el cursor.

# **¿Qué hace la función mouseMoved?**
**R//** Esta función hace que el cursor (Círculo) se mueva en el eje X y el eje Y.

# **¿Qué hace la función mousePressed?**
**R//** Cuando los botones de el Mouse son presionados, el círculo cambia a cualquier color (Random).

# **¿Qué hace la función setup?**
**R//** Declara el color del fondo y el color con el que inicia la partícula.

# **¿Qué hace la función update?**
**R//** Los valores almacenados los va actualizando dependiendo de las variables

# **¿Qué hace la función draw?**
**R//** Dibuja el círculo y sus partículas (El rastro de este).

### Actividad 3

**R//** Este proyecto en OpenFrameworks crea una app donde, al mover el mouse, se van dibujando círculos en las posiciones por donde pasa. Estos círculos se guardan en una lista, pero solo se muestran los últimos 100 para que no se acumulen demasiados.

Al hacer clic con el mouse, todos los círculos cambian de color a uno aleatorio. Al inicio, el fondo es negro y los círculos son blancos, pero con cada clic cambian de color.

### Actividad 4

**Ver videos**

### Actividad 5

# **¿Cuál es la definición de un puntero?**
**R//** Un puntero es como una flecha que apunta a donde está guardado un objeto en la memoria.

# **¿Dónde está el puntero?**
**R//** El puntero apunta a la esfera seleccionada y selecciona una con el mouse y la mueve.

# **¿Cómo se inicializa el puntero?**
**R//** Un puntero se inicializa asignándole una dirección de memoria o un valor especial.

# **¿Para qué se está usando el puntero?**
**R//** Para poder seleccionar y mover una esfera con el mouse, sin necesidad de copiar o duplicar el objeto.

# **¿Qué es exactamente lo que está almacenado en el puntero?**
**R//** Lo que está almacenado en el puntero es una dirección de memoria. Es decir, el puntero no guarda el objeto como tal, sino la ubicación en la memoria donde vive ese objeto.

### Actividad 6
# **El código anterior tiene un problema. ¿Puedes identificar cuál es? ¿Cómo lo solucionarías? Recuerda que deberías poder seleccionar una esfera y moverla con el mouse.**
**R//** El problema es que cuando selecciono una esfera con el clic, esta se queda pegada al mouse y nunca se suelta. Eso pasa porque en el código no está la función para “liberar” la esfera cuando levanto el clic, entonces para solucionar esto necesito decirle al programa que suelte la esfera cuando yo suelto el clic.

### Actividad 7

## Caso 1: Objeto se crea en el **stack**
**R//**
- Al presionar la tecla "c", la esfera se crea como variable local.  
- Sucede cuando la función termina, la variable desaparece y el puntero que guardé queda apuntando a un espacio de memoria que ya no es válido.
- cuando luego trato de dibujarla o acceder a sus datos, estoy usando un puntero colgado (dangling pointer). Eso causa comportamientos raros, errores y/o crasheos.

## Caso 2: Objeto se crea en el **heap**
**R//**
- Cuando presiono la tecla “c” en la versión corregida, ahora la esfera se crea con new. 
- Eso significa que el objeto vive en el heap, no en el stack, y su memoria sigue existiendo aunque termine la función.  
- El puntero que guardo en el globalVector sigue siendo válido, entonces puedo acceder a la esfera y dibujarla sin problemas.
- Como resultado la esfera aparece en pantalla y no hay error.

### Actividad 8

# **Objetos en el stack**
**R//**
- Los objetos creados en el stack (como variables locales) se destruyen cuando termina la función. Si guardas su dirección, quedas con un puntero inválido (dangling pointer).
Esto es útil cuando el objeto solo se necesita dentro de una función temporalmente.

# **Objetos en el heap**
**R//**
- Los objetos creados en el heap sobreviven después de salir de la función. Son útiles cuando necesitas que vivan dinámicamente durante la ejecución, pero requieren que tú te encargues de liberar la memoria.
Esto es útil para estructuras dinámicas, como listas de objetos que cambian en tiempo de ejecución.

# **Objetos en memoria global**
**R//**
Los objetos globales existen toda la vida del programa. Se inicializan antes de main() y se destruyen al final.
Esto es útil para recursos que deben estar siempre disponibles (ejemplo: configuraciones, constantes gráficas, etc...).

## Ejemplo (Experimento)
**R//**
- **stack**
```cpp
void funcion() {
    Sphere s(100, 100, 30); // vive solo en esta función
    s.draw();
} // aquí s se destruye automáticamente
```

- **Heap**
**R//**
```
Sphere* s = new Sphere(200, 200, 30);
s->draw();
delete s; // liberar memoria
```

- **Global**
**R//**
```
Sphere globalSphere(300, 300, 40); // existe todo el programa
```

# **¿Cuándo usar cada uno?**
**R//**
- **Stack**: objetos temporales que viven solo dentro de una función.  
- **Heap**: objetos dinámicos que viven más allá de una función (se deben liberar).  
- **Global**: objetos que viven durante toda la ejecución del programa.

### Actividad 9
# **¿Qué sucede cuando presionas la tecla “F”?**
**R//** Al presionar **“f”** se borra del heap el último objeto creado (círculo) y se quita su puntero del vector. 

# **Analiza detalladamente la parte del código:**
**R//** El bloque primero libera la memoria del último objeto en el heap y luego elimina su puntero del vector, evitando fugas y punteros colgantes.
- `delete heapObjects.back();` libera la memoria en el heap.  
- `heapObjects.pop_back();` elimina el puntero del vector.  
- El orden es importante: primero liberar memoria, luego quitar el puntero.  
- Así se evita fuga de memoria o punteros colgantes.

# Actividad 10
**R//** Si llegué a este punto, la recomendación es seguir viendo los videos de **Mike Shah** sobre C++.  
Estos recursos ayudan a reforzar conceptos clave como manejo de memoria, punteros, referencias, stack vs heap, uso de RAII, y buenas prácticas en programación con C++.
