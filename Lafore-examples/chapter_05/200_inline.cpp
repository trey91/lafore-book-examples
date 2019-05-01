﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// inline.cpp
// применение встраиваемых (подставляемых) функций

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

// функция переводит фунты в килограммы
inline float lbstokg(float pounds)
{
	return 0.453592 * pounds;
}

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	float lbs;
	wcout << L"Введите вес в фунтах: "; wcin >> lbs;
	wcout << L"Вес в килограммах равен " << lbstokg(lbs) << endl;

	return 0;
}