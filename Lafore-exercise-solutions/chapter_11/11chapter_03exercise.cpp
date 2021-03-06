﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 11chapter_03exercise.cpp
// В задании для этого упражнения дан текст программы-примера 531_clarray.cpp, в котором
// создается класс Array, моделирующий массив целых чисел в C++. Требуется перегрузить
// для этого класса оператор присваивания и копирующий конструктор. Затем следует
// написать в main выражения для проверки работы этих перегруженных функций. Также
// следует протестировать случай присвоения массиву одного размера массива другого,
// не совпадающего с первым, размера.

// В конце задания для этого упражнения задан вопрос: что случится, если массиву одного
// размера присваивается массив другого (большего или меньшего) размера? Ответ: в обеих
// перегруженных функциях (оператор присваивания и копирующий конструктор), которые
// мы напишем, будет создан новый объект такого же размера, как и присваиваемый. Поэтому
// никаких проблем в случае присваивания массива большего или меньшего размера не возникнет.
// (В операторе присваивания перед созданием нового мы удалим старый массив, которому
// присваивается заданный.)

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
using namespace std;

class Array // класс, моделирующий обычный массив целых чисел в C++
{
private:
	int* ptr; // указатель на содержимое массива
	int size; // количество элементов в массиве
public:
	Array() : ptr(0), size(0)     // конструктор без аргументов
		{ }
	Array(int s)                  // конструктор с одним аргументом
	{
		size = s;                 // аргументом задается количество элементов в массиве
		ptr = new int[s];         // выделим память под наш массив
	}
	Array(Array& arr)             // перегруженный копирующий конструктор
	{
		size = arr.size;          // копируем количество элементов присваиваемого массива
		ptr = new int[size];      // выделим память под новый массив
		for (int i = 0; i < size; i++)   // скопируем заданный аргументом массив
			*(ptr + i) = *(arr.ptr + i); // в наш новый массив поэлементно
	}
	~Array()                      // деструктор
		{ delete[] ptr; }
	int& operator[] (int j)       // перегруженный оператор обращения к элементу массива
		{ return *(ptr + j); }
	Array& operator= (Array& arr) // перегруженный оператор присваивания
	{
		// проверка на присваивание самому себе
		if (this == &arr) return *this;
		
		delete[] ptr;             // освободим память, выделенную ранее под массив в конструкторе
		                          // массива, которому присваиваем заданный массив
		size = arr.size;          // копируем количество элементов присваиваемого массива
		ptr = new int[size];      // выделим память под новый массив
		for (int i = 0; i < size; i++)   // скопируем заданный аргументом массив
			*(ptr + i) = *(arr.ptr + i); // в наш новый массив поэлементно
		return *this;             // возвращаем текущий объект
	}
	void display()                // вывод элементов массива на экран
	{
		for (int i = 0; i < size; i++)
			wcout << *(ptr + i) << L' ';
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);

	const int ASIZE = 10; // количество элементов в массиве
	Array arr1(ASIZE);     // создаем массив arr1

	for (int j = 0; j < ASIZE; j++) // заполним массив arr1 квадратами целых чисел,
		arr1[j] = j * j;            // начав с нуля и двигаясь в положительную сторону

	// выведем на экран содержимое массива arr1
	wcout << L"arr1 = "; arr1.display(); wcout << endl;

	// тестируем копирующий конструктор
	Array arr2(arr1);
	// Array arr2 = arr1; // альтернативная форма вызова копирующего конструктора
	// выведем на экран содержимое массива arr2
	wcout << L"arr2 = "; arr2.display(); wcout << endl;

	// тестируем операцию присваивания массивов
	Array arr3(10), arr4(5), arr5(15);
	arr3 = arr1; // при равном количестве элементов
	arr4 = arr1; // количество элементов в присваиваемом массиве больше
	arr5 = arr1; // количество элементов в присваиваемом массиве меньше
	// выведем на экран содержимое массивов arr3, arr4, arr5
	wcout << L"arr3 = "; arr3.display(); wcout << endl;
	wcout << L"arr4 = "; arr4.display(); wcout << endl;
	wcout << L"arr5 = "; arr5.display(); wcout << endl;

	// тестируем присваивание самому себе
	arr1 = arr1;
	// выведем на экран содержимое массива arr1
	wcout << L"arr1 = "; arr1.display(); wcout << endl;

	// тестируем множественное присваивание
	Array arr6, arr7;
	arr7 = arr6 = arr1;
	// выведем на экран содержимое массивов arr6, arr7
	wcout << L"arr6 = "; arr6.display(); wcout << endl;
	wcout << L"arr7 = "; arr7.display(); wcout << endl;
	
	return 0;
}