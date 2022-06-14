; Realizar a subtração de 1790 - 980 e 1372 - 1913
; Para as operações vamos usar R1 e R0 para o primeiro número e R3 e R2 para o segundo número.

; Inicializando os registrados para o primeiro cálculo
; 1790 = 6FE
MOV R0, #0FEh
MOV R1, #06h

; 980 = 3D4
MOV R2, #0D4h
MOV R3, #03h
 
; Realiza a subtração
MOV A, R0
SUBB A, R2
MOV R6, A

MOV A, R1
SUBB A, R3
MOV R7, A
; Ao debbugar vemos que a resposta está correta (0x32A)


; Repetindo a lógica para a segunda subtração:
; 1372 = 0x55C
MOV R0, #5Ch
MOV R1, #05h

; 1913 = 0x779
MOV R2, #79h
MOV R3, #07h
 
; Realiza a subtração
MOV A, R0
SUBB A, R2
MOV R6, A

MOV A, R1
SUBB A, R3
MOV R7, A
; Ao debbugar vemos que a resposta está correta (0xFDE3)


END