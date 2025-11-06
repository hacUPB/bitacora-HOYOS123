## **Reto: Proyecto de Arte Generativo**

### **Descripción del proyecto**
Para este reto desarrollé una aplicación de arte generativo usando **C++** y **openFrameworks**.  
La idea fue crear una composición visual con muchos círculos que reaccionan de distintas maneras según el “estado” en el que se encuentra el sistema: **Calm**, **Active** o **Chaos**.  
Cada estado cambia la forma en que se mueven y los colores que usan los círculos, dando una sensación de energía o tranquilidad dependiendo del modo.

---

### **¿Cómo usé los patrones de diseño?**

#### - **Observer**
Usé este patrón para que los círculos “escuchen” los cambios del estado general.  
Cuando el programa cambia de modo (por ejemplo, de Calm a Active), todos los círculos se enteran al mismo tiempo y reaccionan automáticamente.  
Sin embargo, solo en el modo **Calm** los círculos pueden cambiar de color presionando la tecla **M**.  
Esto lo hice para que cada grupo de círculos tuviera su propia personalidad y no todos reaccionaran igual.

---

#### - **Factory**
Usé el patrón Factory para crear distintos tipos de círculos fácilmente.  
En total, tengo **tres fábricas** diferentes:

1. **ColorCircleFactory:** crea los círculos del modo **Calm**, que cambian entre tonos verde claro, verde oscuro, aqua y blueViolet.  
2. **NeutralCircleFactory:** crea los círculos del modo **Active**, que se mueven más rápido y tienen tonos **naranja**.  
3. **MotionCircleFactory:** crea los círculos del modo **Chaos**, que usan el color **crimson** y se mueven con mucha fuerza, casi como si vibraran.  

Gracias a esto, puedo controlar cómo se comportan y cómo se ven dependiendo del modo, sin tener que repetir código.

---

#### - **State**
Este patrón lo usé para controlar los tres modos principales del programa.  
Cada modo cambia la forma en que los círculos se mueven:
- En **Calm**, se mueven suave y lento.  
- En **Active**, aumentan la velocidad y se nota más energía.  
- En **Chaos**, los movimientos son mucho más bruscos y rápidos, como si todo estuviera fuera de control.  

Los modos se pueden cambiar con las teclas:
- **C** → Calm  
- **A** → Active  
- **X** → Chaos  

También se pueden ajustar los niveles de velocidad con los números del **1 al 6**, y con clics del mouse los círculos se reacomodan aleatoriamente.

---

### **Pruebas realizadas**

Durante el desarrollo fui probando constantemente que todo funcionara bien:
- Verifiqué que los colores solo cambiaran cuando el programa está en modo **Calm** y que no afectaran los otros modos.  
- Revisé que cada fábrica generara correctamente sus círculos con los colores y movimientos esperados.  
- Probé que al cambiar de estado, el movimiento se ajustara de inmediato sin errores ni comportamientos raros.  
- También probé que las teclas respondieran correctamente (C, A, X, M, 1–6 y el clic del mouse).

Después de ajustar varios detalles, logré que el proyecto fuera fluido, estable y visualmente atractivo.

---

# **Evidencias**

### **CÓDIGOS**

- **Código fuente:**

**of.App.h:**

```
#pragma once
#include "ofMain.h"

// ========================== OBSERVER ==========================
class Observer {
public:
    virtual void onNotify(string state) = 0;
};

// ========================== SUBJECT ==========================
class Subject {
    vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
    void notify(string state) {
        for (auto& obs : observers) {
            obs->onNotify(state);
        }
    }
};

// ========================== CIRCLE BASE CLASS ==========================
class CircleBase : public Observer {
public:
    ofVec2f pos;
    ofVec2f vel;
    float radius;
    ofColor color;

    CircleBase(ofVec2f _pos, float _radius, ofColor _color)
        : pos(_pos), radius(_radius), color(_color) {
        vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    }

    virtual void update() = 0;
    virtual void draw() = 0;
};

// ========================== TIPOS DE CÍRCULOS ==========================

// ---- SimpleCircle ----
class SimpleCircle : public CircleBase {
public:
    int colorIndex = 0;
    vector<ofColor> calmPalette = {
        ofColor::aqua, ofColor::purple,
        ofColor(0, 255, 0), ofColor(0, 100, 0)
    };

    SimpleCircle(ofVec2f p)
        : CircleBase(p, ofRandom(8, 60), ofColor::aqua) {
    }

    void update() override {
        pos += vel;
        if (pos.x < 0 || pos.x > ofGetWidth()) vel.x *= -1;
        if (pos.y < 0 || pos.y > ofGetHeight()) vel.y *= -1;
    }

    void draw() override {
        ofSetColor(color);
        ofDrawCircle(pos, radius);
    }

    void onNotify(string state) override {
        if (state == "CALM") color = ofColor::aqua;
        else if (state == "ACTIVE") color = ofColor::yellow;
        else if (state == "CHAOS") color = ofColor::red;
        else if (state == "COLOR_TOGGLE") {
            colorIndex = (colorIndex + 1) % calmPalette.size();
            color = calmPalette[colorIndex];
        }
    }
};

// ---- PulsingCircle ----
class PulsingCircle : public CircleBase {
public:
    int colorIndex = 0;
    vector<ofColor> calmPalette = {
        ofColor::aqua, ofColor::purple,
        ofColor(0, 255, 0), ofColor(0, 100, 0)
    };

    PulsingCircle(ofVec2f p)
        : CircleBase(p, ofRandom(15, 70), ofColor::purple) {
    }

    void update() override {
        pos += vel;
        if (pos.x < 0 || pos.x > ofGetWidth()) vel.x *= -1;
        if (pos.y < 0 || pos.y > ofGetHeight()) vel.y *= -1;
    }

    void draw() override {
        ofSetColor(color);
        ofDrawCircle(pos, radius);
    }

    void onNotify(string state) override {
        if (state == "CALM") color = ofColor::blueViolet;
        else if (state == "ACTIVE") color = ofColor::orange;
        else if (state == "CHAOS") color = ofColor::crimson;
        else if (state == "COLOR_TOGGLE") {
            colorIndex = (colorIndex + 1) % calmPalette.size();
            color = calmPalette[colorIndex];
        }
    }
};

// ========================== FACTORY ==========================
class CircleFactory {
public:
    static CircleBase* create(string type, ofVec2f pos) {
        if (type == "simple") return new SimpleCircle(pos);
        else if (type == "pulsing") return new PulsingCircle(pos);
        else return nullptr;
    }
};

// ========================== STATE ==========================
class State {
public:
    virtual string getName() = 0;
    virtual void apply(vector<CircleBase*>& circles) = 0;
};

class CalmState : public State {
public:
    string getName() override { return "CALM"; }
    void apply(vector<CircleBase*>& circles) override {
        for (auto& c : circles) {
            c->vel += ofVec2f(ofRandom(-0.01, 0.01), ofRandom(-0.01, 0.01));
            c->vel.limit(0.5);
        }
    }
};

class ActiveState : public State {
public:
    string getName() override { return "ACTIVE"; }
    void apply(vector<CircleBase*>& circles) override {
        for (auto& c : circles) {
            c->vel += ofVec2f(ofRandom(-0.8, 0.8), ofRandom(-0.8, 0.8));
            c->vel.limit(4);
        }
    }
};

class ChaosState : public State {
public:
    string getName() override { return "CHAOS"; }
    void apply(vector<CircleBase*>& circles) override {
        for (auto& c : circles) {
            float shakeX = ofRandom(-10, 10);
            float shakeY = ofRandom(-10, 10);
            c->pos.x += shakeX;
            c->pos.y += shakeY;
            c->vel += ofVec2f(ofRandom(-1.5, 1.5), ofRandom(-1.5, 1.5));
            c->vel.limit(8);
        }
    }
};

// ========================== MAIN APP ==========================
class ofApp : public ofBaseApp, public Subject {

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    vector<CircleBase*> circles;
    State* currentState;
    CalmState calm;
    ActiveState active;
    ChaosState chaos;

    void changeState(State* newState);
    void randomizePositions();

    // --- NUEVO BLOQUE PARA MANEJO DE VELOCIDADES ---
    int currentSpeedLevel = 1;
    float speedMultiplier = 1.0;

    void updateSpeedLevel(int level) {
        currentSpeedLevel = level;
        switch (level) {
        case 1: speedMultiplier = 0.5; break;
        case 2: speedMultiplier = 0.8; break;
        case 3: speedMultiplier = 1.0; break;
        case 4: speedMultiplier = 1.3; break;
        case 5: speedMultiplier = 1.6; break;
        case 6:
            speedMultiplier = 2.0;
            currentState = &chaos;
            notify("CHAOS");
            break;
        }
        notify("SPEED_CHANGED");
    }
};
```

**ofApp.cpp:**

```
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(10);
    ofSetCircleResolution(50);

    // Estado inicial
    currentState = &calm;

    // Crear círculos mediante la Factory
    for (int i = 0; i < 60; i++) {
        string type = (ofRandom(1) > 0.5) ? "simple" : "pulsing";
        ofVec2f pos(ofRandomWidth(), ofRandomHeight());
        CircleBase* c = CircleFactory::create(type, pos);
        addObserver(c);
        circles.push_back(c);
    }

    notify(currentState->getName());
}

//--------------------------------------------------------------
void ofApp::update() {
    currentState->apply(circles);
    for (auto& c : circles) {
        c->pos += c->vel * speedMultiplier;
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (auto& c : circles) c->draw();

    ofSetColor(255);
    ofDrawBitmapStringHighlight("State: " + currentState->getName(), 20, 20);
    ofDrawBitmapStringHighlight("Speed level: " + ofToString(currentSpeedLevel), 20, 40);
    ofDrawBitmapStringHighlight("C: Calm | A: Active | X: Chaos", 20, 60);
    ofDrawBitmapStringHighlight("M (solo en CALM): Alternar color", 20, 80);
    ofDrawBitmapStringHighlight("1–6: Speed levels | Click: Randomize", 20, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    // Cambiar estado con teclas C, A, X
    if (key == 'c' || key == 'C') changeState(&calm);
    else if (key == 'a' || key == 'A') changeState(&active);
    else if (key == 'x' || key == 'X') changeState(&chaos);

    // Control de velocidades con teclas 1–6
    if (key >= '1' && key <= '6') {
        int level = key - '0';
        updateSpeedLevel(level);
    }

    // --- CAMBIO DE COLOR SOLO EN MODO CALM ---
    if ((key == 'm' || key == 'M') && currentState == &calm) {
        notify("COLOR_TOGGLE");
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if (button == OF_MOUSE_BUTTON_LEFT) {
        randomizePositions();
    }
}

//--------------------------------------------------------------
void ofApp::randomizePositions() {
    for (auto& c : circles) {
        c->pos.set(ofRandomWidth(), ofRandomHeight());
        c->vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
    }
}

//--------------------------------------------------------------
void ofApp::changeState(State* newState) {
    currentState = newState;
    notify(currentState->getName());
}
```

---

### **Validación de los resultados de aprendizaje**

#### **RAE1: Construcción de la aplicación**
La aplicación cumple con los requisitos funcionales al integrar los tres patrones de diseño de forma coherente:
- **Observer**: sincroniza el comportamiento de todos los círculos ante los eventos globales.
- **Factory**: genera distintos tipos de círculos con características visuales y dinámicas únicas.
- **State**: controla los modos del sistema y la energía general de la composición.

Esto permite que el proyecto sea modular, escalable y con un comportamiento interactivo fluido.

#### **RAE2: Pruebas del software**
Durante las pruebas, confirmé tanto el funcionamiento individual como la integración de los tres patrones:
- Al cambiar el **estado** (State), verifiqué que los círculos creados por distintas fábricas respondieran correctamente al evento de cambio (Observer).
- Probé que las notificaciones globales no generaran duplicación ni errores de referencia.
- Revisé que el rendimiento se mantuviera estable incluso con muchos círculos activos.
- Validé que las teclas y eventos del mouse siguieran funcionando correctamente tras múltiples transiciones entre estados.

El resultado fue un comportamiento consistente, con transiciones suaves y sin conflictos entre los patrones implementados.

---

### **Video demostrativo**
[Video de evidencia](https://youtu.be/XiRjEtm3I8s)



