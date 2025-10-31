# Reto UNIDAD 7

---

El proyecto consiste en una aplicación creada con openFrameworks que simula el movimiento de una bandera ondulante del MEJOR EQUIPO DE COLOMBIA mediante el uso de shaders. 
En el diseño, se utiliza una malla plana con textura que se deforma dinámicamente en el vertex shader para generar un efecto de ondas que imita el movimiento del viento sobre una tela,
mientras que el fragment shader aplica los colores y detalles visuales a partir de una imagen.

## **Imagen del mejor equipo de Colombia** (Imagen de la textura utilizada)
**R//** ATLÉTICO NACIONAL
![BANDERA ATLÉTICO NACIONAL](https://github.com/user-attachments/assets/e6355e36-579d-42a5-96f6-b4ffeb0d0277)

---

## RAE1
La aplicación consiste en una bandera ondulante en 3D creada con C++ y openFrameworks, 
utilizando shaders para modificar tanto los vértices como los colores de la textura. 
En el setup(), se cargan los shaders, la textura y se genera una malla plana que servirá como superficie de la bandera:

```
void ofApp::setup() {
    if (ofIsGLProgrammableRenderer()) {
        shader.load("shadersGL3/shader");
    } else {
        shader.load("shadersGL2/shader");
    }

    ofDisableArbTex();
    texture.load("fulbito.jpg");

    mesh = ofMesh::plane(600, 400, 40, 30, OF_PRIMITIVE_TRIANGLES);
}

```
En el método draw(), se activa el shader y se envía información como el tiempo transcurrido y la textura.
Luego se dibuja la malla dentro de una cámara para permitir una vista libre del objeto. 
El vertex shader se encarga de alterar las posiciones de los vértices con funciones seno y coseno, simulando el movimiento del viento, mientras que el fragment shader aplica la textura:

```
void ofApp::draw() {
    ofBackground(0, 50, 100);

    shader.begin();
    shader.setUniform1f("time", ofGetElapsedTimef());
    shader.setUniformTexture("tex0", texture.getTexture(), 0);

    cam.begin();
    mesh.draw();
    cam.end();

    shader.end();
}
```

---

## Códigos 

**ofApp.cpp:**

```
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	if (ofIsGLProgrammableRenderer()) {
		shader.load("shadersGL3/shader");
	} else {
		shader.load("shadersGL2/shader");
	}

	ofDisableArbTex(); 
	texture.load("anFlag.jpg");

	
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	
	mesh.addVertex(glm::vec3(-200, -100, 0)); 
	mesh.addVertex(glm::vec3(200, -100, 0)); 
	mesh.addVertex(glm::vec3(200, 100, 0));
	mesh.addVertex(glm::vec3(-200, 100, 0)); 

	
	mesh.addTexCoord(glm::vec2(0, 1));
	mesh.addTexCoord(glm::vec2(1, 1));
	mesh.addTexCoord(glm::vec2(1, 0));
	mesh.addTexCoord(glm::vec2(0, 0));

	
	mesh.addIndex(0);
	mesh.addIndex(1);
	mesh.addIndex(2);
	mesh.addIndex(2);
	mesh.addIndex(3);
	mesh.addIndex(0);
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor(255, 150, 100), ofColor(50, 50, 150), OF_GRADIENT_LINEAR);



	shader.begin();

	
	shader.setUniform1f("time", ofGetElapsedTimef());
	shader.setUniformTexture("tex0", texture.getTexture(), 0);

	cam.begin();

	mesh.draw();

	cam.end();

	shader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) { }
void ofApp::keyReleased(int key) { }
void ofApp::mouseMoved(int x, int y) { }
void ofApp::mouseDragged(int x, int y, int button) { }
void ofApp::mousePressed(int x, int y, int button) { }
void ofApp::mouseReleased(int x, int y, int button) { }
void ofApp::windowResized(int w, int h) { }
void ofApp::gotMessage(ofMessage msg) { }
void ofApp::dragEvent(ofDragInfo dragInfo) { }

```

**main.cpp:**

```
#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {

#ifdef OF_TARGET_OPENGLES
	ofGLESWindowSettings settings;
	settings.glesVersion = 2;
#else
	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
#endif

	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();
}

```

**ofApp.h:**

```
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofShader shader;
	ofMesh mesh;
	ofImage texture;
	ofEasyCam cam;
};
```
**shader.frag:**

```
OF_GLSL_SHADER_HEADER

out vec4 outputColor;

uniform sampler2D tex0;
in vec2 vTexCoord;
 
void main()
{
    vec4 texColor = texture(tex0, vTexCoord);
    outputColor = texColor;
}

```

**shader.vert:**
```
#version 150

uniform mat4 modelViewProjectionMatrix;
uniform float time;

in vec4 position;
in vec2 texcoord;

out vec2 vTexCoord;

void main() {
    vec4 pos = position;
    
    
    float waveAmplitudeZ = 80.0;   
    float waveAmplitudeY = 40.0;   
    float waveFrequency = 0.15;    
    float waveSpeed = 4.0;         

    
    pos.z += sin((pos.x + pos.y * 0.5) * waveFrequency + time * waveSpeed) * waveAmplitudeZ;

    
    pos.y += cos((pos.x * 0.8) * waveFrequency + time * waveSpeed * 0.8) * waveAmplitudeY;

    
    vTexCoord = texcoord;
    gl_Position = modelViewProjectionMatrix * pos;
}
```

---


# Video 
[Evidencia Bandera ondulante de Atlético Nacional el mejor equipo de Colombia](https://youtu.be/1pYsxhaKcj4)

---

# RAE2

##  **¿Cómo probé la aplicación ofApp.cpp?**
**R//** Para probar la aplicación primero verifiqué que todos los archivos estuvieran en sus carpetas correspondientes, especialmente los shaders dentro de bin/data/shadersGL3/ y la imagen en bin/data/. 
Luego revisé que el código estuviera bien escrito y que no hubiera errores de sintaxis o rutas incorrectas. Después compilé el proyecto para asegurarme de que los shaders se cargaran correctamente y no generaran advertencias. 
Finalmente, ejecuté la aplicación y comprobé que se mostrara una bandera con textura moviéndose de forma ondulante, con un fondo degradado que se asemeja a un atardecer y una cámara libre que permite rotar la vista del objeto.

## **¿Cómo probé el vertex shader?**
**R//** Lo primero que hice fue revisar el código del setup() para asegurarme de que el shader se estuviera cargando correctamente y también verifiqué que los archivos shader.vert y shader.frag estuvieran dentro de la carpeta bin/data/shadersGL3/.

Después revisé en el draw() que el shader se activara antes de dibujar la malla. Una vez comprobado eso, ejecuté la aplicación y observé si la bandera se movía con una ondulación continua, lo cual me confirmó que el vertex shader estaba funcionando correctamente, ya que ese movimiento depende de las funciones seno y coseno que modifican los vértices de la malla en tiempo real.

## **¿Cómo probé el fragment shader?**
**R//** Lo primero que hice fue ejecutar la aplicación y verificar si la textura se aplicaba correctamente sobre la bandera, comprobando que no hubiera deformaciones, cortes o zonas sin imagen.




