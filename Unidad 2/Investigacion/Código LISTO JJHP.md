**ofApp.h**

\#pragma once



\#include "ofMain.h"

\#include <list>

\#include <queue>



// Definición de un círculo

struct Circle {

&nbsp;   float x, y;

&nbsp;   float radius;

&nbsp;   float vx, vy;  // velocidad en x, y

&nbsp;   ofColor color;

};



class ofApp : public ofBaseApp {

public:

&nbsp;   void setup();

&nbsp;   void update();

&nbsp;   void draw();



&nbsp;   void keyPressed(int key);



private:

&nbsp;   std::list<Circle\*> circles;     // Lista de círculos

&nbsp;   std::queue<Circle\*> newCircles; // Para agregar círculos progresivamente



&nbsp;   // Explosión

&nbsp;   uint64\_t lastExplosionTime = 0;

&nbsp;   const uint64\_t explosionCooldown = 10000; // 10 segundos en ms



&nbsp;   // Fuerzas

&nbsp;   float wind = 0.0f;       // viento horizontal

&nbsp;   float gravity = 1.0f;    // factor de caída



&nbsp;   // Métodos auxiliares

&nbsp;   ofColor randomBlue();

&nbsp;   void explode(Circle\* c);

};

**ofApp.cpp**


\#include "ofApp.h"



//--------------------------------------------------------------

void ofApp::setup() {

&nbsp;   ofSetBackgroundColor(0);

}



//--------------------------------------------------------------

void ofApp::update() {

&nbsp;   // Crear un nuevo círculo cada frame

&nbsp;   Circle\* c = new Circle();

&nbsp;   c->x = ofRandomWidth();

&nbsp;   c->y = 0;

&nbsp;   c->radius = ofRandom(5, 15);

&nbsp;   c->vx = 0;

&nbsp;   c->vy = ofRandom(2, 6);

&nbsp;   c->color = randomBlue();

&nbsp;   newCircles.push(c);



&nbsp;   // Pasar de la cola a la lista

&nbsp;   if (!newCircles.empty()) {

&nbsp;       circles.push\_back(newCircles.front());

&nbsp;       newCircles.pop();

&nbsp;   }



&nbsp;   // Actualizar posiciones

&nbsp;   for (auto it = circles.begin(); it != circles.end();) {

&nbsp;       Circle\* c = \*it;



&nbsp;       // aplicar viento y gravedad

&nbsp;       c->x += c->vx + wind;

&nbsp;       c->y += c->vy;

&nbsp;       c->vy += gravity \* 0.05f;



&nbsp;       // eliminar si sale de pantalla

&nbsp;       if (c->y > ofGetHeight() + c->radius ||

&nbsp;           c->x < -c->radius || c->x > ofGetWidth() + c->radius) {

&nbsp;           delete c;

&nbsp;           it = circles.erase(it);

&nbsp;       } else {

&nbsp;           ++it;

&nbsp;       }

&nbsp;   }

}



//--------------------------------------------------------------

void ofApp::draw() {

&nbsp;   for (auto\& c : circles) {

&nbsp;       ofSetColor(c->color);

&nbsp;       ofDrawCircle(c->x, c->y, c->radius);

&nbsp;   }



&nbsp;   // Texto de ayuda

&nbsp;   ofSetColor(200);

&nbsp;   ofDrawBitmapString("Presiona 'c' para limpiar la pantalla", 20, 20);

&nbsp;   ofDrawBitmapString("Presiona 'espacio' para explotar (cada 10s)", 20, 40);



&nbsp;   // Cooldown de explosión

&nbsp;   uint64\_t now = ofGetElapsedTimeMillis();

&nbsp;   int elapsed = (now - lastExplosionTime) / 1000;

&nbsp;   int remaining = explosionCooldown / 1000 - elapsed;



&nbsp;   if (elapsed < (int)(explosionCooldown / 1000)) {

&nbsp;       ofDrawBitmapString("Explosion disponible en: " + ofToString(remaining) + "s", 20, 60);

&nbsp;   } else {

&nbsp;       ofDrawBitmapString("Explosion lista!", 20, 60);

&nbsp;   }



&nbsp;   ofDrawBitmapString("Viento: " + ofToString(wind), 20, 80);

&nbsp;   ofDrawBitmapString("Gravedad: " + ofToString(gravity), 20, 100);

}



//--------------------------------------------------------------

void ofApp::keyPressed(int key) {

&nbsp;   if (key == 'c') {

&nbsp;       for (auto\& c : circles) delete c;

&nbsp;       circles.clear();

&nbsp;       while (!newCircles.empty()) {

&nbsp;           delete newCircles.front();

&nbsp;           newCircles.pop();

&nbsp;       }

&nbsp;   }

&nbsp;   else if (key == ' ') {

&nbsp;       uint64\_t now = ofGetElapsedTimeMillis();

&nbsp;       if (now - lastExplosionTime >= explosionCooldown) {

&nbsp;           lastExplosionTime = now;



&nbsp;           // Explosión de todos los círculos en su lugar

&nbsp;           std::list<Circle\*> temp = circles;

&nbsp;           circles.clear();



&nbsp;           for (auto\& c : temp) {

&nbsp;               explode(c);   // crea fragmentos en el mismo lugar

&nbsp;               delete c;     // elimina el original

&nbsp;           }

&nbsp;       }

&nbsp;   }

&nbsp;   else if (key == OF\_KEY\_LEFT) wind -= 0.5f;

&nbsp;   else if (key == OF\_KEY\_RIGHT) wind += 0.5f;

&nbsp;   else if (key == OF\_KEY\_UP) gravity += 0.1f;

&nbsp;   else if (key == OF\_KEY\_DOWN) gravity = std::max(0.1f, gravity - 0.1f);

}



//--------------------------------------------------------------

ofColor ofApp::randomBlue() {

&nbsp;   return ofColor(0, ofRandom(100, 255), ofRandom(150, 255));

}



//--------------------------------------------------------------

void ofApp::explode(Circle\* c) {

&nbsp;   int numPieces = ofRandom(8, 15);

&nbsp;   for (int i = 0; i < numPieces; i++) {

&nbsp;       Circle\* piece = new Circle();

&nbsp;       piece->x = c->x;

&nbsp;       piece->y = c->y;

&nbsp;       piece->radius = std::max(2.0f, c->radius / 2.0f);

&nbsp;       piece->color = c->color;



&nbsp;       // velocidad radial aleatoria

&nbsp;       float angle = ofRandom(TWO\_PI);

&nbsp;       float speed = ofRandom(2, 6);

&nbsp;       piece->vx = cos(angle) \* speed;

&nbsp;       piece->vy = sin(angle) \* speed;



&nbsp;       circles.push\_back(piece); // directo en la lista (se ve al instante)

&nbsp;   }

}

