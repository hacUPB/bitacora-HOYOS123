# Bitácora

## 1. Código fuente de la aplicación

La aplicación desarrollada en **openFrameworks** cumple con los siguientes requisitos:

- Generación de esferas en una cuadrícula 3D utilizando bucles anidados.
- Almacenar las posiciones en un `vector<ofVec3f>`.
- Interacción con el ratón para seleccionar una esfera y mostrar sus coordenadas.
- Interacción con el teclado para modificar parámetros (separación entre esferas, amplitud en eje Z, etc.).
- Visualización con cámara 3D (`ofEasyCam`) para explorar la escena.

## Código fuente:
```
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(200);
	ofSetFrameRate(60);

	cam.setDistance(600);

	xStep = yStep = 20;
	distDiv = 50;
	amplitud = 150;

	generateSpheres();
}

//--------------------------------------------------------------
void ofApp::generateSpheres() {
	spherePositions.clear();
	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += xStep) {
		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += yStep) {
			float z = cos(ofDist(x, y, 0, 0) / distDiv) * amplitud;
			spherePositions.push_back(glm::vec3(x, y, z));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() { }

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();

	for (auto & pos : spherePositions) {
		if (sphereSelected && pos == selectedSphere) {
			ofSetColor(0, 0, 255); // azul si está seleccionada
		} else {
			float c = ofMap(pos.z, -amplitud, amplitud, 0, 255);
			ofSetColor(255 - c, c, 0);
		}
		ofDrawSphere(pos, 5);
	}

	cam.end();

	// Información en pantalla
	ofSetColor(0);
	ofDrawBitmapString("FPS: " + ofToString(ofGetFrameRate()), 20, 20);
	ofDrawBitmapString("Step (x,y): " + ofToString(xStep), 20, 40);
	ofDrawBitmapString("distDiv: " + ofToString(distDiv), 20, 60);
	ofDrawBitmapString("amplitud: " + ofToString(amplitud), 20, 80);

	if (sphereSelected) {
		ofDrawBitmapString("Seleccionada: (" + ofToString(selectedSphere.x) + ", " + ofToString(selectedSphere.y) + ", " + ofToString(selectedSphere.z) + ")", 20, 100);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'w') amplitud += 5;
	if (key == 's') amplitud -= 5;
	if (key == 'd') distDiv += 5;
	if (key == 'a') distDiv -= 5;
	if (key == '+') {
		xStep += 2;
		yStep += 2;
	}
	if (key == '-') {
		xStep = max(2, xStep - 2);
		yStep = max(2, yStep - 2);
	}

	generateSpheres();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	glm::vec3 rayStart, rayEnd;
	convertMouseToRay(x, y, rayStart, rayEnd);

	sphereSelected = false;
	for (auto & pos : spherePositions) {
		glm::vec3 intersectionPoint;
		if (rayIntersectsSphere(rayStart, rayEnd - rayStart, pos, 5.0, intersectionPoint)) {
			selectedSphere = pos;
			sphereSelected = true;
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd) {
	glm::mat4 modelview = cam.getModelViewMatrix();
	glm::mat4 projection = cam.getProjectionMatrix();
	ofRectangle viewport = ofGetCurrentViewport();

	float x = 2.0f * (mouseX - viewport.x) / viewport.width - 1.0f;
	float y = 1.0f - 2.0f * (mouseY - viewport.y) / viewport.height;

	glm::vec4 rayStartNDC(x, y, -1.0f, 1.0f);
	glm::vec4 rayEndNDC(x, y, 1.0f, 1.0f);

	glm::vec4 rayStartWorld = glm::inverse(projection * modelview) * rayStartNDC;
	glm::vec4 rayEndWorld = glm::inverse(projection * modelview) * rayEndNDC;

	rayStartWorld /= rayStartWorld.w;
	rayEndWorld /= rayEndWorld.w;

	rayStart = glm::vec3(rayStartWorld);
	rayEnd = glm::vec3(rayEndWorld);
}

//--------------------------------------------------------------
bool ofApp::rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
	const glm::vec3 & sphereCenter, float sphereRadius,
	glm::vec3 & intersectionPoint) {
	glm::vec3 oc = rayStart - sphereCenter;

	float a = glm::dot(rayDir, rayDir);
	float b = 2.0f * glm::dot(oc, rayDir);
	float c = glm::dot(oc, oc) - sphereRadius * sphereRadius;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return false;
	} else {
		float t = (-b - sqrt(discriminant)) / (2.0f * a);
		intersectionPoint = rayStart + t * rayDir;
		return true;
	}
}

```

```
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void generateSpheres();
	void convertMouseToRay(int mouseX, int mouseY, glm::vec3 & rayStart, glm::vec3 & rayEnd);
	bool rayIntersectsSphere(const glm::vec3 & rayStart, const glm::vec3 & rayDir,
		const glm::vec3 & sphereCenter, float sphereRadius,
		glm::vec3 & intersectionPoint);

	ofEasyCam cam;
	vector<glm::vec3> spherePositions;

	int xStep, yStep;
	float distDiv, amplitud;

	bool sphereSelected = false;
	glm::vec3 selectedSphere;

private:
	vector<ofVec2f> particles;
	ofColor particleColor;
};
```
---

## 2. Informe de manejo de memoria

Durante la implementación y pruebas con el depurador, encontré lo siguiente:

- El vector de **`ofVec3f`** se almacena en el **heap**, porque es una estructura dinámica que puede crecer o reducirse en tiempo de ejecución.  
- Las variables locales se almacenan en el **stack**.  
- Los objetos globales o estáticos (por ejemplo, la cámara `ofEasyCam`) se reservan en la **memoria global** al inicio de la ejecución.  
- Al seleccionar una esfera con el ratón, se accede a su referencia dentro del vector que está en el **heap**, pero la variable que la contiene temporalmente está en el **stack**.  

El `std::vector` distribuye los datos clave así:
- **Heap:** almacenamiento dinámico de las posiciones de las esferas.  
- **Stack:** variables locales, temporales y parámetros de funciones.  
- **Memoria global:** objetos persistentes durante toda la ejecución. 
---

## 3. Video de demostración
Puedes ver el video aquí: [YouTube](https://youtu.be/UDA7U48PpUQ)
