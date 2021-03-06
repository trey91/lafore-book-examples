﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 09chapter_02exercise_ver1.cpp
// Используя в качестве базового класс String из примера strconv.cpp главы 8,
// создать производный класс Pstring (защищенная строка) с защитой строки от
// переполнения при ее определении. Написать программу для тестирования объектов
// этого класса строками различной длины.

// Я написал два решения этого упражнения, первое из которых обозначено в названии файла
// как ver1 (версия 1), второе — как ver2 (версия 2). Различия следует искать в конструкторе
// производного класса Pstring.

// Описание к примеру strconv.cpp главы 8:
// преобразование обычных строк (массив типа wchar_t) в объекты класса String и наоборот:
// 1) преобразование массива типа wchar_t в объект класса String выполняется в конструкторе
//    с одним параметром;
// 2) преобразование объекта класса String в массив типа wchar_t выполняется в функции
//    с заголовком operator wchar_t* ().

// для использования небезопасной функции wcscpy
#define _CRT_SECURE_NO_WARNINGS

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;
// #include <string.h> // для функции wcscpy не понадобился

class String // класс, представляющий строку (массив символов)
{
protected:                    // исправлено с private на protected, чтобы эти поля были
	                          // доступны в производном классе

	// enum { SZ = 80 }; // максимальный размер строки (нестандартный синтаксис)
	static const int SZ = 80; // максимальный размер строки
							  // (одна константа для всех объектов, статическая)
	wchar_t str[SZ];          // сама строка
public:
	String() // конструктор без параметров
		{ str[0] = L'\0'; }
	String(const wchar_t s[]) // конструктор с одним параметром
	{
		wcscpy(str, s);
		// wcscpy_s(str, SZ, s); // рекомендуемый более безопасный вариант
	}
	void display() const // показ строки на экране
		{ wcout << str; }
	// преобразование объекта класса String к обычной строке (массив типа wchar_t)
	operator wchar_t* ()
		{ return str; }
};

// класс, представляющий «защищенную» строку (с защитой от переполнения массива символов)
class Pstring : public String
{
public:
	Pstring() : String() // конструктор без параметров
		{ }
	Pstring(const wchar_t s[]) // конструктор с одним параметром
	{
		// если длина полученной для определения нашего объекта строки позволяет ей поместиться
		// в массив символов нашего объекта,
		if (wcslen(s) < SZ)
			wcscpy(str, s);              // то повторяем код конструктора базового класса,
		                                 // то есть копируем заданную строку s полностью
			
			// тут хотелось бы вызвать конструктор базового класса, например:
			// String(s); или String::String(s);
			// но это является ошибкой, так как это было бы нарушением принципа,
			// по которому работа конструктора базового класса должна завершиться до
			// начала работы конструктора производного класса

		else // если не помещается,
		{
			int i;                       // то копируем столько символов, сколько может
			for (i = 0; i < SZ - 1; i++) // поместиться, то есть (SZ - 1) символов
				str[i] = s[i];
			str[i] = L'\0';              // последнее место в массиве оставляем для
			                             // нулевого символа
		}
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	// РАЗДЕЛ, который использовался для тестирования в примере strconv.cpp главы 8:
	// (я только заменил класс String на Pstring, чтобы показать, что он работает точно так же)

	Pstring s1; // используем конструктор без параметров

	wchar_t xstr[] = L"Ура, товарищи! "; // создаем обычную строку

	s1 = xstr; // неявно используем конструктор с одним параметром

	s1.display(); // показываем строку

	Pstring s2 = L"Мы победим!"; // снова используем конструктор с одним параметром

	// используем оператор преобразования типов для преобразования объекта типа String
	// в обычную строку (массив типа wchar_t)
	wcout << static_cast<wchar_t*>(s2);
	wcout << endl;

	// РАЗДЕЛ для тестирования защитных свойств класса Pstring в случае определения объекта
	// строками длиной больше (SZ - 1)

	Pstring s3 = L"Эта строка имеет очень большую длину и мы можем быть уверены, что она не "
	              "уместится в отведенный буфер, что приведет к непредсказуемым последствиям.";
	
	s3.display(); // на экран будет выведено только 79 символов (80-е место занимает символ L'\0')
	wcout << endl;

	return 0;
}