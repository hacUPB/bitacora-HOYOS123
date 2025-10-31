# Actividad 1 y 2

## ¿Qué es la entrada-salida mapeada a memoria?

Es una técnica donde los dispositivos de entrada y salida (como pantalla o teclado) se controlan **leyendo o escribiendo en direcciones de memoria específicas**. No se requieren instrucciones especiales: todo se trata como acceso a memoria.

---

## ¿Cómo se usa en la plataforma Hack?

- **Pantalla (`SCREEN`):**  
  - Dirección inicial: `16384` (decimal) o `0x4000` (hex).  
  - Cada celda representa 16 píxeles.  
  - Escribir en esta región modifica el contenido visible de la pantalla.

- **Teclado (`KBD`):**  
  - Dirección: `24576` (decimal) o `0x6000` (hex).  
  - Leer esta dirección devuelve el código ASCII de la tecla presionada, o `0` si no hay ninguna.

---

# Imagen en el Bitmap Editor

![Imagen](image-1.png)

# Actividad 3

(START)
  @KBD
  D=M
  @DRAW_IMAGE
  D;JEQ
  @100
  D=D-A
  @DRAW_IMAGE
  D;JEQ
  @ERASE_IMAGE
  0;JMP

(DRAW_IMAGE)
  @START
  0;JMP

(ERASE_IMAGE)
  @16384
  D=A
  @R0
  M=D
  @64
  D=A
  @R1
  M=D
(ERASE_LOOP)
  @R0
  A=M
  M=0
  @R0
  M=M+1
  @R1
  M=M-1
  @ERASE_LOOP
  D;JGT
  @START
  0;JMP

# Actividad 4
// Espera una tecla y actúa según la letra
(READ)
@KBD
D=M
@READ
D;JEQ

// Letra 'd'
@100
D=A
@KBD
D=M-D
@DRAW
D;JEQ

// Letra 'e'
@101
D=A
@KBD
D=M-D
@ERASE
D;JEQ

@READ
0;JMP

// Borra toda la pantalla
(ERASE)
@SCREEN
D=A
@SCREEN_PTR
M=D

@8192
D=A
@PIXELS_LEFT
M=D

(CLEAR_LOOP)
@PIXELS_LEFT
D=M
@READ
D;JEQ

@SCREEN_PTR
A=M
M=0

@SCREEN_PTR
M=M+1

@PIXELS_LEFT
M=M-1

@CLEAR_LOOP
0;JMP

// Dibuja la imagen
(DRAW)
@R16
D=A
@BITMAP_PTR
M=D

@SCREEN
D=A
@SCREEN_PTR
M=D

@32
@ROWS_LEFT
M=A

(WRITE_LOOP)
@ROWS_LEFT
D=M
@READ
D;JEQ

@BITMAP_PTR
A=M
D=M

@SCREEN_PTR
A=M
M=D

@BITMAP_PTR
M=M+1

@SCREEN_PTR
D=M
@32
D=D+A
@SCREEN_PTR
M=D

@ROWS_LEFT
M=M-1

@WRITE_LOOP
0;JMP

@32768
D=A
@R16
M=D

@16384
D=A
@R17
M=D

@8192
D=A
@R18
M=D

@4096
D=A
@R19
M=D

@2048
D=A
@R20
M=D

@1024
D=A
@R21
M=D

@512
D=A
@R22
M=D

@256
D=A
@R23
M=D

@128
D=A
@R24
M=D

@64
D=A
@R25
M=D

@32
D=A
@R26
M=D

@16
D=A
@R27
M=D

@8
D=A
@R28
M=D

@4
D=A
@R29
M=D

@2
D=A
@R30
M=D

@1
D=A
@R31
M=D

@1
D=A
@R32
M=D

@2
D=A
@R33
M=D

@4
D=A
@R34
M=D

@8
D=A
@R35
M=D

@16
D=A
@R36
M=D

@32
D=A
@R37
M=D

@64
D=A
@R38
M=D

@128
D=A
@R39
M=D

@256
D=A
@R40
M=D

@512
D=A
@R41
M=D

@1024
D=A
@R42
M=D

@2048
D=A
@R43
M=D

@4096
D=A
@R44
M=D

@8192
D=A
@R45
M=D

@16384
D=A
@R46
M=D

@32768
D=A
@R47
M=D

## Explicación del error en el código de dibujo (Nand2Tetris)

**Profe, es que aquí hay un problema con el ciclo que dibuja la imagen.**  
Resulta que ese ciclo tiene una condición al principio que revisa si ya se acabaron las líneas por dibujar, pero lo hace *antes* de escribir nada. Entonces a veces se sale del ciclo muy pronto, como si ya hubiera terminado, y por eso la imagen no se dibuja completa.
Y también me aseguré de que los valores de las teclas ‘d’ y ‘e’ estén bien puestos, porque si no, el programa no sabría cuándo tiene que dibujar o borrar.
