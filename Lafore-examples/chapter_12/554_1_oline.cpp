﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// oline.cpp
// вывод строк, содержащих пробелы, в файл

// я добавил в программу две строки для работы с локалью, чтобы можно было
// записать в файл русские буквы в кодировке UTF-8

#include <fstream>   // для файлового ввода/вывода
#include <codecvt>   // для работы с фасетом codecvt_utf8 локали
// #include <locale> // не понадобился
using namespace std;

int main()
{
	// создаем константу, содержащую локаль с нужным фасетом для
	// преобразования символов при сохранении в файл в кодировке UTF-8
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());

	wofstream outfile(L"тестовый файл.txt"); // создать выходной файл
	outfile.imbue(utf8_locale);              // связываем наш поток с нужной локалью
	
	// отправить текст в файл (отрывок из стихотворения Иосифа Бродского, 1961 год)
	outfile << L"Приходит март. Я сызнова служу.\n";
	outfile << L"В несчастливом кружении событий\n";
	outfile << L"изменчивую прелесть нахожу\n";
	outfile << L"в смешеньи незначительных наитий.\n";

	return 0;
}