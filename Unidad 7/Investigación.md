# Unidad 7 - Investigación

---

## Actividad 1 – Comprendiendo la GPU

### 1. **¿Qué son los vértices?**
**R//** Los vértices son los puntos que definen la forma de los objetos en 3D. Cada vértice tiene información como su posición, color, coordenadas de textura y normales. Por ejemplo, un triángulo necesita tres vértices para formarse.

---

### 2. **¿Con qué figura geométrica se dibuja en 3D?**
**R//** En 3D todo se dibuja con triángulos. Cualquier figura compleja (como un cubo o una esfera) se compone de muchos triángulos pequeños, porque son la forma más simple y estable para representar superficies planas.

---

### 3. **¿Qué es un shader?**
**R//** Un shader es un pequeño programa que se ejecuta en la GPU y controla cómo se dibujan los gráficos. Con ellos se define el color, la iluminación, las texturas o incluso deformaciones visuales en los objetos. Existen varios tipos, principalmente el **vertex shader** y el **fragment shader**.

---

### 4. **¿Cómo se le llaman a los grupos de píxeles de un mismo triángulo?**
**R//** A esos grupos se les llama **fragmentos**. Cada fragmento representa un píxel potencial del triángulo que se está dibujando.

---

### 5. **¿Qué es un fragment shader?**
**R//** El fragment shader determina el color final de cada fragmento o píxel. Aquí se decide cómo se verá el objeto en pantalla: su color, brillo, iluminación o textura.

---

### 6. **¿Qué es un vertex shader?**
**R//** El vertex shader procesa los vértices del objeto. Se encarga de calcular su posición final en la pantalla aplicando transformaciones como traslación, rotación, escala y proyección.

---

### 7. **¿Al proceso de determinar qué píxeles del display va a cubrir cada triángulo de una mesh se le llama?**
**R//** Este proceso se llama **rasterización**, y consiste en convertir los triángulos en píxeles visibles en la pantalla.

---

### 8. **¿Qué es el render pipeline?**
**R//** El render pipeline es la secuencia de pasos que sigue la GPU desde que recibe los vértices hasta que dibuja los píxeles finales en la pantalla. Incluye etapas como el vertex shading, rasterización, fragment shading y la mezcla final en el framebuffer.

---

### 9. **¿Hay alguna diferencia entre aplicar un color a una superficie de una mesh o aplicar una textura?**
**R//** Sí. Cuando se aplica un color, se usa un valor uniforme para toda la superficie. En cambio, al aplicar una textura, se “pega” una imagen sobre la superficie para darle más detalle visual.

---

### 10. **¿Cuál es la diferencia entre una textura y un material?**
**R//** Una **textura** es una imagen que se mapea sobre la superficie de un objeto, mientras que un **material** define cómo reacciona esa superficie ante la luz (brillo, metal, rugosidad, transparencia, etc.). Un material puede usar varias texturas a la vez.

---

### 11. **¿Qué transformaciones se requieren para mover un vértice del 3D world al View Screen?**
**R//** 
1. **Model transformation**: mueve el objeto dentro del mundo.
2. **View transformation**: posiciona la cámara.
3. **Projection transformation**: proyecta las coordenadas 3D al plano 2D.
4. **Viewport transformation**: ajusta la imagen al tamaño de la pantalla.

---

### 12. **¿Al proceso de convertir los triángulos en fragmentos se le llama?**
**R//** También se llama **rasterización**. Es la etapa donde los triángulos se transforman en fragmentos que luego serán coloreados.

---

### 13. **¿Qué es el framebuffer?**
**R//** El framebuffer es una zona de memoria donde se almacenan los píxeles finales que se van a mostrar en pantalla. Guarda información de color, profundidad y, en algunos casos, transparencia.

---

### 14. **¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?**
**R//** El Z-buffer sirve para saber qué objeto está más cerca de la cámara. Gracias a esto, los objetos del fondo no tapan a los del frente. La GPU compara la profundidad de cada fragmento y solo dibuja el más cercano.

---

### 15. Luego de ver el segundo video entiendes por qué la GPU tiene que funcionar tan rápido y de manera paralela. ¿Por qué?
**R//** La GPU necesita procesar millones de vértices y fragmentos de forma simultánea para generar imágenes en tiempo real. 
A diferencia de la CPU, que trabaja en serie, la GPU tiene miles de núcleos pequeños que calculan en paralelo. Por eso es ideal para tareas gráficas e incluso para inteligencia artificial.

---

---

## Actividad 2 – Primer Shader y Experimento con `draw()`

## **Experimento inicial**
**R//** Al hacer la prueba, primero comenté las líneas donde se iniciaba y terminaba el shader, dejando el método `draw()` así:

```
void ofApp::draw(){
    ofSetColor(255);

    //shader.begin();

    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

    //shader.end();
}
```

(Todo esto antes de ejecutar el código original).

Cuando lo ejecuté, simplemente apareció un rectángulo blanco que ocupaba toda la pantalla.
Nada se movía ni cambiaba de color. Básicamente, el programa estaba dibujando sin pasar por la GPU, o al menos sin aplicar ningún efecto.

---

## **Ejecución del código original**
**R//** Después volví a activar el shader con shader.begin() y shader.end(), y esta vez sí hubo un cambio.
La pantalla empezó a mostrar una variación de colores, como si estuvieran animados.

Ahí entendí que el shader estaba tomando el control del color de los píxeles, y que la GPU era la encargada de hacer todos esos cálculos de manera muy rápida.

---

## **¿Qué entendí del funcionamiento?**
**R//** En este ejercicio pude ver que hay dos partes importantes:

1. La CPU, que es donde corre la aplicación principal. Ella se encarga de decirle a la GPU qué hacer, por ejemplo, cuándo comenzar o terminar el shader.

2. La GPU, que hace los cálculos visuales. En este caso, se encarga de decidir el color de cada punto que se ve en pantalla.

(El shader es como una mini-programa que vive dentro de la GPU y que define cómo se va a ver lo que se dibuja).

---

## **Lo que hace cada shader**

**Vertex Shader:**
**R//** Se encarga de las posiciones de los vértices (los puntos del rectángulo). En este ejemplo, no cambia nada visualmente, solo se asegura de que todo se dibuje bien.

**Fragment Shader:**
**R//** Es el que decide el color final de cada punto (píxel). En el ejemplo original, los colores cambian según el tiempo o las coordenadas de la pantalla, lo que hace que todo se vea dinámico.

---

---

# Actividad 3 – Pasando información personalizada a los shaders

## 1. **¿Qué es un "uniform"?**
**R//** Entendí que un **uniform** es una variable especial que le permite a la CPU enviarle datos a la GPU.  
Por ejemplo, puedo pasarle valores como el tiempo, el color, la posición del mouse o cualquier otra cosa que cambie durante la ejecución del programa.

Lo importante es que los uniforms tienen un solo valor compartido para todos los fragmentos o vértices que el shader está procesando.  
Por eso se llaman así: *“uniformes”*, porque no cambian dentro de un mismo dibujo, aunque sí pueden actualizarse en cada frame.

---

## **¿Cómo funciona la comunicación entre CPU y GPU?**
**R//** La **CPU** (la parte del programa escrita en C++) le envía datos a los shaders mediante comandos como `shader.setUniform1f()` o `shader.setUniform2f()`.  
Luego, en el shader (escrito en GLSL), esos valores se reciben con una variable declarada como `uniform`.

Por ejemplo:

**En el código de aplicación (C++):**

```
shader.begin();
shader.setUniform1f("time", ofGetElapsedTimef());
ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
shader.end();
```

**En el fragment shader (GLSL):**

```
uniform float time;

void main(){
    gl_FragColor = vec4(abs(sin(time)), 0.3, 0.8, 1.0);
}
```

En este caso, el programa le pasa a la GPU el valor del tiempo (time), y el shader lo usa para cambiar los colores con el paso de los segundos.

---

** Mi experimento con el fragment shader**
**R//** Modifiqué el código para que el color de cada píxel dependiera de su posición en pantalla.
Agregué dos uniforms: uno para el ancho de la ventana y otro para la altura. Así pude crear un degradado de color horizontal y vertical.

```
uniform float time;
uniform vec2 resolution;

void main(){
    vec2 st = gl_FragCoord.xy / resolution;
    gl_FragColor = vec4(st.x, st.y, abs(sin(time)), 1.0);
}
```

El resultado fue un fondo con colores que cambiaban lentamente, mezclando tonos según la posición de cada píxel y el tiempo.
Fue interesante ver cómo solo unas pocas líneas podían generar un efecto visual tan dinámico.

---

---

# Actividad 4 – Adding Some Interactivity

## **Lo que buscaba lograr**
**R//** La idea principal era que el color o el efecto del shader reaccionara según la posición del mouse en la pantalla.  
Con esto, uno puede empezar a crear efectos más vivos y dinámicos, donde el usuario tiene cierto control visual.

---

## **¿Cómo lo hice?**
**R//** Primero, en el código de la aplicación (C++), agregué un uniform nuevo que enviara la posición actual del mouse al shader.  
El código quedó así:

```
shader.begin();
shader.setUniform2f("mouse", mouseX, mouseY);
shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
shader.setUniform1f("time", ofGetElapsedTimef());
ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
shader.end();
```

Después, en el fragment shader, recibí esa información y la usé para cambiar los colores según la distancia entre el mouse y cada píxel.

```
uniform vec2 resolution;
uniform vec2 mouse;
uniform float time;

void main() {
    vec2 st = gl_FragCoord.xy / resolution;
    vec2 m = mouse / resolution;

    float dist = distance(st, m);
    vec3 color = vec3(abs(sin(time)) * dist, st.x, st.y);
    
    gl_FragColor = vec4(color, 1.0);
}
```

Así logré que los colores se movieran y cambiaran dependiendo de dónde estaba el mouse, además de tener una animación que variaba con el tiempo.

---


