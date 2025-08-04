## Mini reto 1: Sumar los primeros 100 números naturales (`while`)

**R//**
```
@1
D=A
@i
M=D
@0
D=A
@sum
M=D
(LOOP)
@i
D=M
@101
D=D-A
@END
D;JGT
@sum
D=M
@i
D=D+M
@sum
M=D
@i
M=M+1
@LOOP
0;JMP
(END)
@END
0;JMP
```

### Preguntas respondidas

- **¿Cómo están implementadas las variables `i` y `sum`?**  
**R//** Están implementadas como etiquetas usadas con nombres simbólicos, y el valor se guarda en direcciones de memoria RAM.

- **¿En qué direcciones de memoria están estas variables?**  
**R//** Las variables `i` y `sum` se almacenan en direcciones que el sistema asigna a partir de la RAM[16] en adelante.

- **¿Cómo está implementado el ciclo `while`?**  
**R//** Se usa una etiqueta que marca el inicio del ciclo, y un salto condicional que verifica si `i <= 100`. Si no se cumple, salta al final.

- **¿Cómo se implementa la variable `i`?**  
**R//** Primero se asigna el valor 1, y luego se va incrementando en cada iteración con `i = i + 1`.

- **¿En qué parte de la memoria se almacena la variable `i`?**  
**R//** El sistema la guarda en una dirección libre de RAM, normalmente desde la posición 16 si no hay otras variables.

- **Después de todo lo que has hecho, ¿qué es entonces una variable?**  
**R//** Es un espacio de memoria donde puedo guardar un valor y cambiarlo cuando quiera.

## Mini retos 2 y 3: Escribir un programa en lenguaje ensamblador para que utilice un ciclo for en vez de un ciclo while.

**R//**
```
@0
D=A
@sum
M=D
@1
D=A
@i
M=D
(LOOP)
@i
D=M
@101
D=D-A
@END
D;JGT
@sum
D=M
@i
D=D+M
@sum
M=D
@i
M=M+1
@LOOP
0;JMP
(END)
@END
0;JMP
```

## Mini retos 4 y 5: Punteros

### Preguntas respondidas
- **¿Cómo se declara un puntero en C++?**
**R//** Con int *punt;, eso indica que punt va a guardar la dirección de una variable entera.

- **¿Cómo se define un puntero en C++?**
**R//** Con punt = &var;, es decir, que el punt debe guardar la dirección de var.

- **¿Cómo se almacena en C++ la dirección de memoria de una variable?**
**R//** Usando el operador &, como en &var.

- **¿Cómo se escribe el contenido de la variable a la que apunta un puntero?**
**R//** Usando *punt = 20;, o sea, cambio el valor de lo que hay en la dirección a la que apunta punt.

```
@10
D=A
@var
M=D
@var
D=A
@punt
M=D
@20
D=A
@punt
A=M
M=D
```
