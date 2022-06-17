//Objetivo: Encontrar o menor e o maior valor da lista salvando em R0 e R1 respectivamente:
//Aponta para inicio da lista
MOV DPTR, #LISTA
//Usaremos R3 como auxiliar para fazer incrementos e ir passando os valores da lista
MOV R3, #0

//Move para A índice da lista
MOV A, R3

//Le o primeiro valor
MOVC A, @A+DPTR

//O primeiro valor é salvo tanto como maior e como menor
MOV R0, A
MOV R1, A

//Segundo valor, o R3 é incrementado para andarmos uma posição na lista
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

//Caso R0 seja maior que A teremos que passar o valor do acumulador para o R0
//Para isso usamos o JNC que irá pular caso não tenha borrow/carry (caso de R0 menor que A)
MOV A, R3
MOVC A, @A+DPTR
JNC MENOR1
MOV R0, A
MENOR1:

CLR C

SUBB A, R1

//Caso R1 seja menor que A teremos que passar o valor do acumulador para o R1
//Para isso usamos o JC que irá pular caso tenha borrow/carry (caso de R1 maior que A)
MOV A, R3
MOVC A, @A+DPTR
JC MAIOR1
MOV R1, A
MAIOR1:

CLR C

// Terceiro valor, aqui são repetidos os mesmos passos que para o segundo valor, até o décimo
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR2
MOV R0, A
MENOR2:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR2
MOV R1, A
MAIOR2:

CLR C

//Quarto valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR3
MOV R0, A
MENOR3:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR3
MOV R1, A
MAIOR3:

CLR C

//Quinto valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR4
MOV R0, A
MENOR4:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR4
MOV R1, A
MAIOR4:

CLR C

//Sexto valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR5
MOV R0, A
MENOR5:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR5
MOV R1, A
MAIOR5:

CLR C

//Sétimo valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR6
MOV R0, A
MENOR6:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR6
MOV R1, A
MAIOR6:

CLR C

//Oitavo valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR7
MOV R0, A
MENOR7:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR7
MOV R1, A
MAIOR7:

CLR C

//Nono valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR8
MOV R0, A
MENOR8:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR8
MOV R1, A
MAIOR8:

CLR C

//Décimo valor
INC R3
MOV A, R3

MOVC A, @A+DPTR

SUBB A, R0

MOV A, R3
MOVC A, @A+DPTR
JNC MENOR9
MOV R0, A
MENOR9:

CLR C

SUBB A, R1

MOV A, R3
MOVC A, @A+DPTR
JC MAIOR9
MOV R1, A
MAIOR9:

CLR C

LISTA:
DB 13, 9, 3, 49, 10, 2, 37, 21, 8, 21	

END
