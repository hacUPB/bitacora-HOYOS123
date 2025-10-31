**of.App.h:**



\#pragma once

\#include "ofMain.h"

\#include <list>

\#include <queue>



struct Circle {

&nbsp;	float x, y;

&nbsp;	float radius;

&nbsp;	float speed;

&nbsp;	ofColor color;

&nbsp;	float vx = 0, vy = 0; // velocidad extra para explosión

};



class ofApp : public ofBaseApp {

public:

&nbsp;	void setup();

&nbsp;	void update();

&nbsp;	void draw();

&nbsp;	void keyPressed(int key);



&nbsp;	// Lista enlazada para círculos en pantalla

&nbsp;	std::list<Circle \*> circles;



&nbsp;	// Cola para círculos nuevos

&nbsp;	std::queue<Circle \*> newCircles;



&nbsp;	// Función para crear azules dinámicos

&nbsp;	ofColor randomBlue();



&nbsp;	// Explosión

&nbsp;	void explode(Circle \* c);

&nbsp;	bool explosionMode = false;



&nbsp;	// Cooldown de explosión

&nbsp;	uint64\_t lastExplosionTime = 0; // tiempo de la última explosión

&nbsp;	int explosionCooldown = 10000; // 10 segundos

};


**of.App.cpp**

#include "ofApp.h"



//--------------------------------------------------------------

void ofApp::setup() {

&nbsp;	ofSetFrameRate(60);

&nbsp;	ofBackground(10, 10, 30); // fondo oscuro

}



//--------------------------------------------------------------

ofColor ofApp::randomBlue() {

&nbsp;	int r = ofRandom(0, 50); // poco rojo

&nbsp;	int g = ofRandom(80, 180); // un poco de verde

&nbsp;	int b = ofRandom(180, 255); // mucho azul

&nbsp;	return ofColor(r, g, b);

}



//--------------------------------------------------------------

void ofApp::update() {

&nbsp;	if (!explosionMode) {

&nbsp;		// Crear nuevos círculos cada frame

&nbsp;		Circle \* c = new Circle();

&nbsp;		c->x = ofRandomWidth();

&nbsp;		c->y = 0;

&nbsp;		c->radius = ofRandom(5, 15);

&nbsp;		c->speed = ofRandom(2, 6);

&nbsp;		c->color = randomBlue();

&nbsp;		newCircles.push(c);



&nbsp;		// Pasar círculos de la cola a la lista

&nbsp;		if (!newCircles.empty()) {

&nbsp;			circles.push\_back(newCircles.front());

&nbsp;			newCircles.pop();

&nbsp;		}



&nbsp;		// Actualizar posiciones normales

&nbsp;		for (auto it = circles.begin(); it != circles.end();) {

&nbsp;			Circle \* c = \*it;

&nbsp;			c->y += c->speed;



&nbsp;			if (c->y > ofGetHeight() + c->radius) {

&nbsp;				delete c; // liberar memoria

&nbsp;				it = circles.erase(it);

&nbsp;			} else {

&nbsp;				++it;

&nbsp;			}

&nbsp;		}

&nbsp;	} else {

&nbsp;		// Actualizar explosión

&nbsp;		for (auto it = circles.begin(); it != circles.end();) {

&nbsp;			Circle \* c = \*it;

&nbsp;			c->x += c->vx;

&nbsp;			c->y += c->vy;

&nbsp;			c->vy += 0.1; // gravedad ligera



&nbsp;			c->radius \*= 0.96; // se encogen poco a poco



&nbsp;			if (c->radius < 1) {

&nbsp;				delete c;

&nbsp;				it = circles.erase(it);

&nbsp;			} else {

&nbsp;				++it;

&nbsp;			}

&nbsp;		}



&nbsp;		// Si ya no quedan partículas, volver al modo normal

&nbsp;		if (circles.empty()) {

&nbsp;			explosionMode = false;

&nbsp;		}

&nbsp;	}

}



//--------------------------------------------------------------

void ofApp::draw() {

&nbsp;	for (auto \& c : circles) {

&nbsp;		ofSetColor(c->color);

&nbsp;		ofDrawCircle(c->x, c->y, c->radius);

&nbsp;	}



&nbsp;	// Texto de interacción

&nbsp;	ofSetColor(200);

&nbsp;	ofDrawBitmapString("Presiona 'c' para limpiar la pantalla", 20, 20);

&nbsp;	ofDrawBitmapString("Presiona 'espacio' para explotar (cada 10s)", 20, 40);



&nbsp;	// Mostrar cuenta regresiva o "Explosión lista!"

&nbsp;	uint64\_t now = ofGetElapsedTimeMillis();

&nbsp;	int elapsed = (now - lastExplosionTime) / 1000; // segundos desde la última explosión

&nbsp;	int remaining = explosionCooldown / 1000 - elapsed;



&nbsp;	if (elapsed < explosionCooldown / 1000) {

&nbsp;		// Mostrar cuenta regresiva solo de 10 a 0

&nbsp;		ofDrawBitmapString("Explosion disponible en: " + ofToString(remaining) + "s", 20, 60);

&nbsp;	} else {

&nbsp;		// Cuando ya pasó el cooldown

&nbsp;		ofDrawBitmapString("Explosion lista!", 20, 60);

&nbsp;	}

}







//--------------------------------------------------------------

void ofApp::keyPressed(int key) {

&nbsp;	if (key == 'c') {

&nbsp;		for (auto \& c : circles)

&nbsp;			delete c;

&nbsp;		circles.clear();

&nbsp;		while (!newCircles.empty()) {

&nbsp;			delete newCircles.front();

&nbsp;			newCircles.pop();

&nbsp;		}

&nbsp;		explosionMode = false;

&nbsp;	} else if (key == ' ') {

&nbsp;		uint64\_t now = ofGetElapsedTimeMillis();

&nbsp;		if (now - lastExplosionTime >= explosionCooldown) {

&nbsp;			explosionMode = true;

&nbsp;			lastExplosionTime = now; // registrar tiempo de la explosión



&nbsp;			// Explota cada círculo en partículas

&nbsp;			std::list<Circle \*> temp = circles;

&nbsp;			circles.clear();



&nbsp;			for (auto \& c : temp) {

&nbsp;				explode(c);

&nbsp;				delete c; // eliminar el círculo original

&nbsp;			}

&nbsp;		} else {

&nbsp;			ofLogNotice() << "Explosion en cooldown. Espera un momento...";

&nbsp;		}

&nbsp;	}

}



//--------------------------------------------------------------

void ofApp::explode(Circle \* c) {

&nbsp;	int numParticles = ofRandom(5, 12);

&nbsp;	for (int i = 0; i < numParticles; i++) {

&nbsp;		Circle \* p = new Circle();

&nbsp;		p->x = c->x;

&nbsp;		p->y = c->y;

&nbsp;		p->radius = c->radius / 2;

&nbsp;		float angle = ofRandom(TWO\_PI);

&nbsp;		float speed = ofRandom(2, 6);

&nbsp;		p->vx = cos(angle) \* speed;

&nbsp;		p->vy = sin(angle) \* speed;

&nbsp;		p->color = c->color;

&nbsp;		circles.push\_back(p);

&nbsp;	}

}





