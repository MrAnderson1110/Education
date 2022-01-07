Data SEGMENT		; Сегмент данных

; Вариант 3
; Решить уравнение вида:
; (1 + A/5)*B-C*D, где:

	A DB 150d
	B DB 111b
	C DB 48h
	D DB 3d
	X DW ?
Data ENDS

Ourstack SEGMENT Stack	; Сегмент стека
		; Выделили 100h (256) байт под стек
	DB 100h DUP (?)	
Ourstack ENDS

		; Привязываем имена к регистрам
ASSUME CS:Code, DS:Data, SS:Ourstack 

Code SEGMENT		; Сегмент кода
Start:

	mov AX, Data	; Загрузка сегмента данных
	mov DS, AX
	xor AX, AX	; Очистка регистра AX
			
	mov AL, A	; Делим A на 5 используя регистры AL и BL
	mov BL, 5	; с сохранением ответа в AH:AL
	div BL		; по условию используем только частное (AL)
			
	mov BL, AL	; Сохраняем полученный ответ (частное) в BL
			
	add BL, 1	; Прибавляем к полученному ответу 1
	mov AL, B	; Сохраняем (В == 111b) в AL 
	mul BL		; и умножаем на полученный при вычислениях выше результат в AL
	mov X, AX	; Сохраняем результат в X
	
	mov AL, C	
	mov BL, D	; Вычисляем (C * D) с использованием регистров AL и BL
	mul BL		; результат умножения сохраняется в AX
	
	sub X, AX	; Полученное произведение складываем с результатом вычеслений в X
			; Получили ответ, завершаем программу.
	mov AL, 0
	mov AH, 4Ch
	int 21h	
Code ENDS
END Start
