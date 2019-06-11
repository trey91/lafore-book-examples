﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 06chapter_02exercise.cpp
// создать класс tollBooth, представляющий пункт взимания платежей за проезд по автостраде

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
// #include <conio.h> // для функции _getwche не понадобился
#include <iomanip> // для манипулятора setprecision
using namespace std;

class tollBooth // класс, представляющий пункт взимания платежей за проезд по автостраде
{
private:
	unsigned int ncars; // число проехавших автомобилей
	double sump;        // сумма оплат за проезд (50 центов за машину, но платят не все)
public:
	// конструктор без параметров, инициализирующий значения полей нулями
	tollBooth() : ncars(0), sump(0)
		{ }
	// метод регистрирует проехавшую машину, водитель которой оплатил проезд
	void payingCar()
		{ ncars++; sump += 0.50; }
	// метод регистрирует проехавшую машину, водитель которой НЕ оплатил проезд
	void nopayCar()
		{ ncars++; }
	// константный метод выводит значения полей на экран
	void display() const
	{
		wcout << L"Число проехавших автомобилей: " << ncars
			  << L", сумма оплат за проезд: $" << fixed << setprecision(2) << sump << endl;
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	wcout << L"Демонстрация работы пункта взимания платежей за проезд по автостраде.\n"
		  << L"Нажатие клавиш \'д\' (да) и \'н\' (нет) будет означать соответственно автомобиль\n"
		  << L"оплатившего и не оплатившего проезд водителя. Нажатие Esc приведет к\n"
		  << L"выводу результата работы пункта и выходу из программы.\n\n";
	wcout << L"ПОЕХАЛИ: ";

	wchar_t ch;   // для символов, вводимых пользователем
	tollBooth tb; // объект, представляющий пункт взимания платежей

	// цикл, имитирующий движение автомобилей через пункт взимания платежей
	do {
		ch = _getwche(); // получаем очередной символ от пользователя
		// регистрируем автомобиль либо с оплатой, либо без оплаты
		switch (ch)
		{
		case L'д': tb.payingCar(); break;
		case L'н': tb.nopayCar(); break;
		// любой другой символ не будет иметь значения
		}
	} while (ch != L'\x1B'); // выход из цикла по нажатию Esc

	// выводим на экран результат работы пункта
	wcout << endl; tb.display();

	return 0;
}