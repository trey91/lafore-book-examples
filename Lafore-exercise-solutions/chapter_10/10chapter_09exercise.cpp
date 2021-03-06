﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 10chapter_09exercise.cpp
// Имеется задача сохранения 100 целых чисел. Поставлено условие:
// наибольший массив, который можно использовать, имеет размер в 10 элементов.

// Для решения данной задачи предлагается определить 10 массивов типа int,
// каждый размером в 10 элементов. Еще один массив размером в 10 элементов
// должен содержать указатели на первые десять массивов.

// Требуется в main написать программу для тестирования полученной структуры.

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

const int SIZE = 10; // количество элементов в массиве

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	// определим десять массивов нужного размера
	int a0[SIZE], a1[SIZE], a2[SIZE], a3[SIZE], a4[SIZE],
		a5[SIZE], a6[SIZE], a7[SIZE], a8[SIZE], a9[SIZE];

	// массив указателей на массивы
	int *ap[] = {a0, a1, a2, a3, a4, a5, a6, a7, a8, a9};

	int j, k; // индексы для обращения к элементам массивов

	// заполним массивы тестовыми данными
	for (j = 0; j < SIZE; j++)
		for (k = 0; k < SIZE; k++)
			ap[j][k] = (j * 10 + k) * 10;

	// выведем тестовые данные, хранящиеся в массивах, на экран
	for (j = 0; j < SIZE; j++)
		for (k = 0; k < SIZE; k++)
			wcout << ap[j][k] << ((k == SIZE - 1) ? L'\n' : L' ');

	return 0;
}