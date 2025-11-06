# Sesión 2: análisis de un caso de estudio

### **Observer:** 
- Conecta el ofApp con todas las partículas. Cuando presiono una tecla, se lanza un evento y todas cambian su estado sin estar directamente ligadas a la app.

### **Factory:** 
- Permite crear partículas de diferentes tipos (star, planet, shooting_star) sin repetir el código de inicialización.

### **State:** 
- Define el comportamiento de cada partícula según su estado (Normal, Attract, Repel, Stop). Con esto, las partículas pueden cambiar su forma de moverse de manera dinámica.

---

# Experimentación con el código.

### Modificaciones:
Al crear un **nuevo tipo de partícula**, que se puede ver que se mueve distinto, cambia un poco lo que se admiraba con el código original para que no todas fueran iguales y así darle más variedad a la simulación.

´´´
class SpecialParticle : public Particle {
public:
    void update() override {
        // Movimiento distinto
        position += velocity * 1.5;  
    }
    void draw() override {
        ofSetColor(255, 0, 0); // Color rojo
        ofDrawCircle(position, radius);
    }
};
´´´

Les añadí un **estado interno**, que es como una condición que define cómo se comportan. Gracias a eso, ahora una misma partícula puede reaccionar de diferentes maneras según lo que pase.

´´´
enum ParticleState { NORMAL, ALERT, INACTIVE };
ParticleState state = NORMAL;
´´´
---

También modifiqué el **comportamiento general** de las partículas para que ya no actúen siempre igual, sino que cambien su movimiento o apariencia dependiendo de su estado.

´´´
void Particle::update() {
    if (state == NORMAL) {
        position += velocity;
    } else if (state == ALERT) {
        position += velocity * 2; // se mueve más rápido
    } else if (state == INACTIVE) {
        // no se mueve
    }
}
´´´

---

Y por último, hice que existan **eventos que avisan a las partículas** sobre lo que ocurre en el entorno, y con esas señales ellas pueden cambiar de estado o reaccionar de manera más dinámica. 


´´´
ofEvent<void> alertEvent;
ofEvent<void> resetEvent;

void ofApp::triggerAlert() {
    ofNotifyEvent(alertEvent);
}

void ofApp::triggerReset() {
    ofNotifyEvent(resetEvent);
}

´´´
---

Y en la partícula:

´´´
ofAddListener(app->alertEvent, this, &Particle::onAlert);
ofAddListener(app->resetEvent, this, &Particle::onReset);

void Particle::onAlert() {
    state = ALERT;
}

void Particle::onReset() {
    state = NORMAL;
}
´´´


Por lo que las partículas ya no son elementos aislados, sino que tienen más vida y responden a lo que pasa alrededor.
