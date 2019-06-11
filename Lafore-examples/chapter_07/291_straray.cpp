﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// straray.cpp
// массив строк

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	const int DAYS = 7; // количество строк в массиве
	const int MAX = 12; // максимальная длина каждой из строк:
	
	// длина самой длинной строки ("Воскресенье" или "Понедельник") в символах
	// составляет 11, плюс еще одно место отводится под нулевой символ,
	// поэтому максимальная длина каждой из строк выбрана в 12 символов
	
	// массив строк
	wchar_t star[DAYS][MAX] =
	{
		L"Понедельник", L"Вторник", L"Среда", L"Четверг",
		L"Пятница", L"Суббота", L"Воскресенье"
	};

	// вывод всех строк на экран
	for (int j = 0; j < DAYS; j++)
		wcout << star[j] << endl;

	return 0;
}