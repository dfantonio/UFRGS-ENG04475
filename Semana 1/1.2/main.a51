// Aponta para inicio da lista
MOV DPTR, #LISTA
//Move para A índice da lista
MOV A, #0
// Le valor
MOVC A, @A+DPTR









LISTA:
DB 23, 8, 10, 68, 31, 17, 9, 36, 19, 37
	
	
END