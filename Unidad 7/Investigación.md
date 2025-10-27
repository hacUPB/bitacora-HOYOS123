# Unidad 7 - Investigación

## Actividad 1 – Comprendiendo la GPU

### 1. **¿Qué son los vértices?**
**R//** Los vértices son los puntos que definen la forma de los objetos en 3D. Cada vértice tiene información como su posición, color, coordenadas de textura y normales. Por ejemplo, un triángulo necesita tres vértices para formarse.


### 2. **¿Con qué figura geométrica se dibuja en 3D?**
**R//** En 3D todo se dibuja con triángulos. Cualquier figura compleja (como un cubo o una esfera) se compone de muchos triángulos pequeños, porque son la forma más simple y estable para representar superficies planas.


### 3. **¿Qué es un shader?**
**R//** Un shader es un pequeño programa que se ejecuta en la GPU y controla cómo se dibujan los gráficos. Con ellos se define el color, la iluminación, las texturas o incluso deformaciones visuales en los objetos. Existen varios tipos, principalmente el **vertex shader** y el **fragment shader**.


### 4. **¿Cómo se le llaman a los grupos de píxeles de un mismo triángulo?**
**R//** A esos grupos se les llama **fragmentos**. Cada fragmento representa un píxel potencial del triángulo que se está dibujando.


### 5. **¿Qué es un fragment shader?**
**R//** El fragment shader determina el color final de cada fragmento o píxel. Aquí se decide cómo se verá el objeto en pantalla: su color, brillo, iluminación o textura.


### 6. **¿Qué es un vertex shader?**
**R//** El vertex shader procesa los vértices del objeto. Se encarga de calcular su posición final en la pantalla aplicando transformaciones como traslación, rotación, escala y proyección.


### 7. **¿Al proceso de determinar qué píxeles del display va a cubrir cada triángulo de una mesh se le llama?**
**R//** Este proceso se llama **rasterización**, y consiste en convertir los triángulos en píxeles visibles en la pantalla.


### 8. **¿Qué es el render pipeline?**
**R//** El render pipeline es la secuencia de pasos que sigue la GPU desde que recibe los vértices hasta que dibuja los píxeles finales en la pantalla. Incluye etapas como el vertex shading, rasterización, fragment shading y la mezcla final en el framebuffer.


### 9. **¿Hay alguna diferencia entre aplicar un color a una superficie de una mesh o aplicar una textura?**
**R//** Sí. Cuando se aplica un color, se usa un valor uniforme para toda la superficie. En cambio, al aplicar una textura, se “pega” una imagen sobre la superficie para darle más detalle visual.


### 10. **¿Cuál es la diferencia entre una textura y un material?**
**R//** Una **textura** es una imagen que se mapea sobre la superficie de un objeto, mientras que un **material** define cómo reacciona esa superficie ante la luz (brillo, metal, rugosidad, transparencia, etc.). Un material puede usar varias texturas a la vez.


### 11. **¿Qué transformaciones se requieren para mover un vértice del 3D world al View Screen?**
**R//** 
1. **Model transformation**: mueve el objeto dentro del mundo.
2. **View transformation**: posiciona la cámara.
3. **Projection transformation**: proyecta las coordenadas 3D al plano 2D.
4. **Viewport transformation**: ajusta la imagen al tamaño de la pantalla.


### 12. **¿Al proceso de convertir los triángulos en fragmentos se le llama?**
**R//** También se llama **rasterización**. Es la etapa donde los triángulos se transforman en fragmentos que luego serán coloreados.


### 13. **¿Qué es el framebuffer?**
**R//** El framebuffer es una zona de memoria donde se almacenan los píxeles finales que se van a mostrar en pantalla. Guarda información de color, profundidad y, en algunos casos, transparencia.


### 14. **¿Para qué se usa el Z-buffer o depth buffer en el render pipeline?**
**R//** El Z-buffer sirve para saber qué objeto está más cerca de la cámara. Gracias a esto, los objetos del fondo no tapan a los del frente. La GPU compara la profundidad de cada fragmento y solo dibuja el más cercano.


### 15. Luego de ver el segundo video entiendes por qué la GPU tiene que funcionar tan rápido y de manera paralela. ¿Por qué?
**R//** La GPU necesita procesar millones de vértices y fragmentos de forma simultánea para generar imágenes en tiempo real. 
A diferencia de la CPU, que trabaja en serie, la GPU tiene miles de núcleos pequeños que calculan en paralelo. Por eso es ideal para tareas gráficas e incluso para inteligencia artificial.
