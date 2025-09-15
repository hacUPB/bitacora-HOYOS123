# Reto

### Obra de arte generativo:

## **Descripción del proyecto**
El proyecto consiste en una **lluvia de círculos azules** que caen desde la parte superior de la pantalla.  
Los círculos pueden **explotar** en partículas dinámicas, ser **revividos** desde una pila,  
y su movimiento está influenciado por **gravedad** y **viento**.  

La interacción del usuario permite modificar el comportamiento de la obra en tiempo real.  
Además, se maneja memoria dinámica, que cuidadosamente libera cada objeto creado.

---

## **Cumplimiento de requisitos**

### 1. **Combinación de estructuras de datos**
- **Lista enlazada (`std::list<Circle*>`)** Que maneja los circulos en la pantalla.  **lista = vida**

- **Cola (`std::queue<Circle*>`)** Almacena temporalmente nuevas gotas antes de ser integradas en la lista principal.  **cola = entrada**

- **Pila (`CircleStack`)** Guarda copias de las gotas que explotaron y permite “revivirlas”.  **pila = memoria**

- **Arreglo dinámico (`std::vector<ofColor>`)** Define la **paleta de colores azules** que le da la identidad estética a la lluvia.  **vector = estética**

---

### 2. **Interactividad**
Se puede modificar el proyecto con estas teclas: 
- **Espacio** → Explosión de todas las gotas (Genera un cooldown de 10s).  
- **R** → Revive la última gota que explotó (usando la pila).  
- **C** → Limpia toda la pantalla (lista, cola y pila).  
- **Flechas ←/→** → Cambian la fuerza del viento.  
- **Flechas ↑/↓** → Modifican la gravedad.

---

### 3. **Gestión de memoria**
- Cada círculo que aparece en la pantalla se crea en el momento en que lo necesito.
- Cuando ya el círculo no me sirve (porque salió de la pantalla, explotó o limpié todo), lo elimino para que no quede ocupando espacio.
- La pila también se encarga de borrar lo que guarda cuando ya no lo necesito.
- Además, hice una función que limpia todo de una sola vez, asegurándome de que nada se quede guardado por error.

---

## **Preguntas guía y respuestas**

1. **Exploración creativa:**  
   El objetivo fue lograr un efecto visual que contenga la **lluvia** porque quería hacer que la lluvia funcionara tal cual como si uno la moviera.  
   Las estructuras de datos ayudan a organizar estos comportamientos:  
   la lista mantiene la lluvia viva, la pila conserva memoria de explosiones y el vector define la estética.  

2. **Gestión de memoria:**  
   Se usó `delete` en todos los lugares donde un objeto ya no era útil.  
   También se implementó un destructor en la pila.  
   Con esto se evita acumulación innecesaria y fugas de memoria.  

3. **Interacción y dinamismo:**  
   - La explosión elimina de la lista y pasa copias a la pila.  
   - Revivir extrae de la pila y regresa a la lista.  
   - El viento y la gravedad afectan a todos los elementos de la lista.  

4. **Optimización:**  
   - Se usa `std::list` porque permite eliminar elementos sin recorrer todo el arreglo.  
   - Se implementó un **cooldown** para evitar saturación de partículas.  
   - Los objetos se destruyen en cuanto dejan de ser útiles, liberando memoria.  

---

## **Evidencia de resultados de aprendizaje**

[**Video**](https://youtu.be/xeBr2ALVj6E)

---
