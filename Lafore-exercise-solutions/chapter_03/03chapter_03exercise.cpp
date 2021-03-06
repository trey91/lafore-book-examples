﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 03chapter_03exercise.cpp
// Программа, считывающая цифры, вводимые пользователем,
// считывание должно производиться с помощью функции _getwche.
// Из введенных цифр следует составить число и вывести его на экран.
// При вычислении итогового числа предыдущее значение следует умножить на 10
// и прибавить очередную введенную цифру. Перевод очередного полученного символа-цифры
// в число осуществить вычитанием из его кода кода символа-цифры '0' или числа 48

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
// #include <conio.h> // для функции _getwche не понадобился
using namespace std;

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	wchar_t ch; // вводимый пользователем символ-цифра
	unsigned long n = 0; // итоговое число
	wcout << L"Введите число: ";
	while ((ch = _getwche()) != L'\r') // цикл для считывания символов-цифр
		                               // выход из цикла по клавише Enter
		n = n * 10 + (ch - L'0');
	wcout << L"\nВы ввели число: " << n << endl;

	return 0;
}