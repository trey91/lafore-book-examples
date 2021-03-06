﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// missarg.cpp
// применение аргументов по умолчанию

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

void repchar(wchar_t = L'*', int = 45); // прототип с аргументами по умолчанию

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	repchar();         // печатает символ '*' 45 раз
	repchar(L'=');     // печатает символ '=' 45 раз
	repchar(L'+', 30); // печатает символ '+' 30 раз

	return 0;
}

// функция выводит на экран заданный символ заданное число раз
void repchar(wchar_t ch, int n) // при необходимости будут
{                               // использоваться значения по умолчанию
	for (int j = 0; j < n; j++) // цикл, выполняющийся n раз
		wcout << ch;            // вывод заданного символа
	wcout << endl;
}