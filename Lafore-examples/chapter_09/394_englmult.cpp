﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// englmult.cpp
// демонстрация множественного наследования с участием класса, представляющего
// интервалы в английских мерах длины

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <string> // для работы со строками wstring
using namespace std;

class Type // вид пиломатериала
{
private:
	wstring dimensions; // размеры пиломатериала
	wstring grade;      // сорт (категория) пиломатериала
public:
	// конструктор без аргументов
	Type() : dimensions(L"нет данных"), grade(L"нет данных")
		{ }
	// конструктор с двумя аргументами
	Type(wstring di, wstring gr) : dimensions(di), grade(gr)
		{ }
	void gettype() // ввод полей с клавиатуры
	{
		wcout << L" Введите номинальные размеры (2x4 и т.п.): "; wcin >> dimensions;
		wcout << L" Введите сорт (необработанный, строительный и т.п.): "; wcin >> grade;
	}
	void showtype() const // вывод полей на экран
	{
		wcout << L"\n Размеры: " << dimensions;
		wcout << L"\n Сорт: " << grade;
	}
};

class Distance // интервал в английских мерах длины
{
private:
	int feet;     // футы (1 фут = 12 дюймов)
	float inches; // дюймы
public:
	// конструктор без аргументов
	Distance() : feet(0), inches(0.0)
		{ }
	// конструктор с двумя аргументами
	Distance(int ft, float in) : feet(ft), inches(in)
		{ }
	void getdist() // ввод полей с клавиатуры
	{
		wcout << L" Введите число футов: "; wcin >> feet;
		wcout << L" Введите число дюймов: "; wcin >> inches;
	}
	void showdist() const // вывод полей на экран
		{ wcout << feet << L"\'-" << inches << L'\"'; }
};

// Класс Lumber (пиломатериал) представляет собой скорее складскую позицию, то есть
// объект этого класса содержит в двух собственных полях количество хранящегося
// на некоем складе пиломатериала и цену за единицу пиломатериала. Благодаря
// наследованию вида public от класса Type (вид пиломатериала) у объекта класса
// Lumber от базового класса доступны два поля, содержащие размеры и сорт (категорию)
// пиломатериала. Благодаря наследованию вида public от класса Distance у объекта
// класса Lumber от этого базового класса доступны два поля (футы и дюймы),
// выражающие длину пиломатериала в английских мерах длины.

// Почему у пиломатериала есть характеристика «размеры» и характеристика «длина»?
// Характеристика «размеры» выражает размеры сечения пиломатериала, а под «длиной»
// подразумевается именно длина пиломатериала (доски, бруса и т.п.).

class Lumber : public Type, public Distance // пиломатериал
{
private:
	int quantity; // количество в штуках
	double price; // цена за штуку, в рублях
public:
	// конструктор без аргументов
	Lumber() : Type(), Distance(), quantity(0), price(0.0)
		{ }
	// конструктор с шестью аргументами
	Lumber(wstring di, wstring gr, // аргументы для полей класса Type
		int ft, float in,          // аргументы для полей класса Distance
		int qu, float prc) :       // аргументы для собственных полей класса Lumber
		Type(di, gr),              // вызов конструктора класса Type
		Distance(ft, in),          // вызов конструктора класса Distance
		quantity(qu), price(prc)   // инициализация собственных полей класса Lumber
		{ }
	void getlumber()
	{
		Type::gettype();
		Distance::getdist();
		wcout << L" Введите количество, шт.: "; wcin >> quantity;
		wcout << L" Введите цену за штуку, руб: "; wcin >> price;
	}
	void showlumber() const
	{
		Type::showtype();
		wcout << L"\n Длина: "; Distance::showdist();
		wcout << L"\n Стоимость " << quantity << L" штук: " << (price * quantity) << L" руб";
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	// используем конструктор без аргументов
	Lumber siding; // деревянный сайдинг, использующийся для обшивки домов

	wcout << L"Введите информацию о деревянном сайдинге\n";
	siding.getlumber(); // получаем данные от пользователя

	// используем конструктор с шестью аргументами
	// (размеры, сорт (категория), длина (футы, дюймы), количество, цена)
	Lumber studs(L"2x4", L"строительный", 8, 0.0, 200, 4.45F); // деревянный брус

	// выведем информацию о хранящихся на складе пиломатериалах на экран
	wcout << L"\nДеревянный сайдинг"; siding.showlumber();
	wcout << L"\nДеревянный брус"; studs.showlumber();
	wcout << endl;

	return 0;
}