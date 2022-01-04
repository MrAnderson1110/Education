Data SEGMENT

; Вариант 3
; Решить уравнение вида:
; (1 + A/5)*B-C*D, где:

	A DB 150d
	B DB 111b
	C DB 48h
	D DB 3d
	X DW ?
Data ENDS

Ourstack SEGMENT Stack
	DB 100h DUP (?)
Ourstack ENDS

ASSUME CS:Code, DS:Data, SS:Ourstack 

Code SEGMENT

Start:

	mov AX, Data
	mov DS, AX
	xor AX, AX	; Подготовили сегмент данных
			
	mov AL, A	; Делим A на 5 используя регистры AL и BL
	mov BL, 5	; с сохранение ответа в AL
	div BL	
			
	mov BL, AL	; Сохраняем полученный ответ в BL
			
	add BL, 1	; Прибавляем к X 1
	mov AL, B	; Сохраняем В == 111b в AL 
	mul BL		; и умножаем на полученный при вычислениях выше результат в AL
	mov X, AX	; Сохраняем результат в X
	
	mov AL, C	; Вычисляем (C * D) с использованием регистров AL и BL
	mov BL, D
	mul BL
	
	sub X, AX	; Полученное произведение складываем с результатом вычеслений в X
			; Получили ответ, завершаем программу.
	mov AL, 0
	mov AH, 4Ch
	int 21h
	
Code ENDS

END Start
