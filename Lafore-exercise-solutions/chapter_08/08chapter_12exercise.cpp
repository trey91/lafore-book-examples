﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 08chapter_12exercise.cpp
// Написать программу, которая включает класс bMoney из упражнения 8 этой (8-й) главы
// и класс sterling из упражнения 11 этой же главы. Написать операции преобразования
// между объектами этих классов, считая, что 1 фунт = 50 долларов. Написать программу
// в main, позволяющую пользователю ввести сумму и ее валюту, после чего программа
// должна вывести сумму в другой валюте.

// Для решения задачи создана константа RATE (курс обмена валют), перенесены классы сначала
// sterling из упражнения 11, затем bMoney из упражнения 8 этой главы. Порядок расположения
// классов важен: определенный в программе раньше класс не "видит" класс, определенный
// после первого. Оба преобразования располагаем поэтому во втором классе, который "видит"
// первый. То есть преобразования располагаем в нашем случае в классе bMoney. Для
// преобразования bMoney -> sterling используем operator sterling(). Для преобразования
// sterling -> bMoney используем новый конструктор с одним аргументом.

// Если поменять классы местами, то написать решение тоже возможно, но оно у меня
// получается более трудозатратным, поэтому я его отбросил.

#include <io.h> // для функции _setmode
#include <fcntl.h> // для константы _O_U16TEXT
#include <iostream>
#include <iomanip> // для манипуляторов setiosflags, setprecision
#include <sstream> // для стандартного класса wstringstream
using namespace std;

const double RATE = 50.0; // курс обмена валют: 1 фунт = 50 долларов

class sterling // класс, представляющий денежную сумму в старой английской системе
{
private:
	long pounds;   // фунты (1 фунт = 20 шиллингов = 240 пенсов)
	int shillings; // шиллинги (1 шиллинг = 12 пенсов)
	int pences;    // пенсы
public:
	// конструктор без аргументов
	sterling() : pounds(0), shillings(0), pences(0)
		{ }
	// конструктор с одним аргументом
	// (для преобразования десятичных фунтов в денежную сумму в старой системе)
	sterling(double df)
	{
		// в этих формулах используется то обстоятельство, что при присвоении
		// целочисленной переменной вещественного значения дробная часть отбрасывается
		pounds = df;
		shillings = (df - pounds) * 20;
		// в случае пенсов необходимо округление до ближайшего целого (функция round),
		// а не отбрасывание дробной части
		pences = round(((df - pounds) * 20 - shillings) * 12);
	}
	// конструктор с тремя аргументами
	sterling(long ps, int s, int p) : pounds(ps), shillings(s), pences(p)
		{ }
	// метод для получения от пользователя денежной суммы в старой системе
	// в формате "£9.19.11"
	void getSterling()
	{
		// чтобы символ фунта отобразился в консоли, шрифт в консоли должен быть юникодным,
		// например, шрифт "Lucida Console" или "Consolas"

		wchar_t separator; // для точки, разделяющей фунты, шиллинги и пенсы
		wcout << L"Введите сумму (фунты, шиллинги и пенсы через точку): £";
		wcin >> pounds >> separator >> shillings >> separator >> pences;
	}
	// метод для вывода денежной суммы в старой системе на экран
	// в формате "£9.19.11"
	void putSterling() const
	{
		// чтобы символ фунта отобразился в консоли, шрифт в консоли должен быть юникодным,
		// например, шрифт "Lucida Console" или "Consolas"

		wcout << L"£" << pounds << L"." << shillings << L"." << pences;
	}
	// операция преобразования объекта класса (денежной суммы в старой системе)
	// в число типа double (денежную сумму в десятичных фунтах)
	operator double() const
	{
		// так как в этом арифметическом выражении используются вещественные числа
		// (по умолчанию это тип double), то результат выражения тоже будет приведен
		// к вещественному типу (double в данном случае)
		return (pounds + shillings / 20.0 + pences / 240.0);
	}
	// перегрузка операции сложения (+) для сложения двух объектов класса
	// (результат тоже будет объектом класса)
	sterling operator+ (sterling s) const
	{
		// 1) sterling(pounds, shillings, pences) — создание безымянного объекта класса
		// с помощью конструктора с тремя аргументами. Обозначим это выражение как s1

		// 2) double(s1) и double(s) — создание безымянных переменных типа double с
		// помощью операции преобразования объекта класса в число типа double,
		// определенной выше (сумма из старой системы преобразуется в десятичные фунты)

		// 3) sterling(double(s1) + double(s)) — создание безымянного объекта класса
		// с помощью конструктора с одним аргументом (из десятичных фунтов в сумму
		// в старой системе)

		return sterling(double(sterling(pounds, shillings, pences)) + double(s));
	}
	// перегрузка операции вычитания (-) для нахождения разности двух объектов класса
	// (результат тоже будет объектом класса)
	sterling operator- (sterling s) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) - double(s));
	}
	// перегрузка операции умножения (*) для нахождения произведения объекта класса
	// и числа типа double (результатом будет объект класса)
	sterling operator* (double n) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) * n);
	}
	// перегрузка операции деления (/) для нахождения частного от деления объекта
	// класса на другой объект класса (результатом будет число типа double)
	double operator/ (sterling s) const
	{
		return (double(sterling(pounds, shillings, pences)) / double(s));
	}
	// перегрузка операции деления (/) для нахождения частного от деления объекта
	// класса на число типа double (результатом будет объект класса)
	sterling operator/ (double n) const
	{
		return sterling(double(sterling(pounds, shillings, pences)) / n);
	}
};

class bMoney // класс, представляющий денежную сумму в долларах и центах
{
private:
	long double sum; // денежная сумма в долларах и центах
public:
	bMoney() // конструктор без параметров
		{ sum = 0.0L; }
	// конструктор с одним параметром (преобразование из long double в bMoney)
	// (с помощью служебного слова explicit делаем возможным использование
	// конструктора только в виде конструктора, а не для неявных преобразований)
	explicit bMoney(long double n) : sum(n)
		{ }
	bMoney(const wchar_t s[]) // конструктор с одним параметром (денежная строка)
		{ mstold(s); }
	// метод преобразует денежную строку в число типа long double
	long double mstold(const wchar_t []); // прототип
	// метод преобразует число типа long double (sum) в денежную строку и
	// возвращает эту строку через первый параметр
	void ldtoms(wchar_t []); // прототип
	// метод для получения денежной строки от пользователя с клавиатуры
	// и сохранения ее в поле sum класса
	void getmoney()
	{
		wchar_t tms[80]; // для строки с денежной суммой
		wcout << L"Введите денежную сумму (пример: '$1,234,567.99'):\n";
		wcin >> tms; // получаем денежную строку
		mstold(tms); // преобразуем денежную строку в long double и сохраняем в sum
	}
	// метод для вывода поля sum класса на экран в виде денежной строки
	void putmoney()
	{
		wchar_t tms[80]; // для строки с денежной суммой
		ldtoms(tms);     // преобразуем поле sum класса (long double) в денежную строку
		wcout << tms;    // выводим денежную строку на экран
	}
	// операция сложения двух объектов класса
	bMoney operator+ (bMoney m) const
		// используем конструктор с одним параметром для преобразования long double в bMoney
		{ return bMoney(sum + m.sum); }
	// операция нахождения разности двух объектов класса
	bMoney operator- (bMoney m) const
		{ return bMoney(sum - m.sum); }
	// операция нахождения произведения объекта класса и числа типа long double
	bMoney operator* (long double n) const
		{ return bMoney(sum * n); }
	// операция нахождения частного от деления объекта класса на другой объект класса
	long double operator/ (bMoney m) const
		{ return sum / m.sum; }
	// операция нахождения частного от деления объекта класса на число типа long double
	bMoney operator/ (long double n) const
		{ return bMoney(sum / n); }
	// конструктор с одним параметром
	// (преобразование из класса sterling в текущий класс bMoney)
	bMoney(sterling s)
	{
		// преобразование double(s) определено в классе sterling, в результате получаем
		// сумму в десятичных фунтах, умножая которую на константу RATE переводим ее в доллары
		sum = double(s) * RATE;
	}
	// операция преобразования объекта текущего класса в объект класса sterling
	operator sterling()
	{
		// выражение (sum / RATE) — перевод суммы в долларах в десятичные фунты,
		// далее создаем безымянный объект класса sterling с помощью конструктора
		// с одним аргументом, который преобразует десятичные фунты в фунты,
		// шиллинги и пенсы старой английской системы
		return sterling(sum / RATE);
	}
};

int main()
{
	// переключение стандартного потока вывода в формат Юникода
	_setmode(_fileno(stdout), _O_U16TEXT);
	// переключение стандартного потока ввода в формат Юникода
	_setmode(_fileno(stdin), _O_U16TEXT);

	wchar_t ans;  // для ответа пользователя о продолжении ввода (д/н)
	int currency; // номер валюты
	bMoney sd;    // денежная сумма в долларах
	sterling sf;  // денежная сумма в фунтах, шиллингах и пенсах

	// в цикле, чтобы можно было проверить работу программы на разных
	// исходных данных
	do {

		wcout << L"Введите номер валюты (1 — доллар, 2 — фунт): ";
		wcin >> currency;

		if (currency == 1) // в долларах
		{
			sd.getmoney(); // запрашиваем сумму в долларах
			sf = sd;       // для преобразования используем
			               // operator sterling() из класса bMoney
			wcout << L"В старой английской системе: "; sf.putSterling();
		}
		else if (currency == 2) // в фунтах, шиллингах и пенсах
		{
			sf.getSterling(); // запрашиваем сумму в фунтах, шиллингах и пенсах
			sd = sf;          // для преобразования используем
			                  // конструктор с одним аргументом из класса bMoney
			wcout << L"В долларах: "; sd.putmoney();
		}
		else // пользователь ввел не 1 и не 2
			wcout << L"Ошибка, вы ввели не 1 и не 2!";
		wcout << endl;

		wcout << L"Попробовать ещё (д/н)? "; wcin >> ans; wcout << endl;
	} while (ans != L'н');

	return 0;
}

// метод преобразует заданную строку в число типа long double и возвращает это число;
// предполагается, что заданная строка представляет денежную сумму,
// например, "$1,234,567,890,123.99";
// mstold расшифровывается как "money string to long double"
long double bMoney::mstold(const wchar_t str[])
{
	wchar_t temp[80]; // временная строка
	int j = 0;        // индекс для временной строки (массива символов)
	// обрабатываем денежную строку-параметр как массив символов
	for (int i = 0; i < wcslen(str); i++)
	{
		wchar_t ch = str[i]; // возьмем очередной символ из массива (строки)

		if ((ch >= L'0') && (ch <= L'9')) // если он является цифрой,
			temp[j++] = ch;               // то добавить его к временной строке,
		else if (ch == L'.')              // иначе, если он является точкой,
			temp[j++] = ch;               // то тоже добавить к временной строке,
		                                  // остальные символы игнорировать
	}
	temp[j] = L'\0'; // завершаем временную строку нулевым символом

	wchar_t *stop;
	// преобразуем временную строку в числовое значение типа long double
	sum = wcstold(temp, &stop);

	// В книге Лафоре рекомендует использовать библиотечную функцию _atold для
	// преобразования строки в виде массива типа char в число типа long double.
	// Однако, нужно учитывать, что Лафоре пользовался при написании книги
	// средой Microsoft Visual C++ версии 6.0, вышедшей в 1998 году.
	// На сегодня (2019 год) в среде Visual Studio Community 2017 библиотечная функция
	// _atold отсутствует.
	
	// Есть функция atof, принимающая в качестве аргумента массив типа char, но
	// она возвращает число типа double, а не long double.

	// Еще есть функция _atoldbl, которая принимает вторым аргументом массив типа
	// char и возвращает в первом аргументе значение типа указатель на _LDOUBLE.

	// Еще есть функция strtold, которая принимает первым аргументом массив типа
	// char и возвращает число типа long double. Ее аналогом для широких символов
	// является функция wcstold.

	// Для преобразования массива типа wchar_t (широких символов) я нашел и
	// применил (см. выше) библиотечную функцию wcstold. Эта функция принимает
	// массив типа wchar_t первым аргументом и возвращает соответствующее число
	// типа long double. Второй параметр обязателен, но для наших целей НЕ
	// ИМЕЕТ ЗНАЧЕНИЯ (в нем возвращается адрес первого символа в строке
	// такого, что не может являться частью числа). Для понимания второго
	// параметра нужно понимание указателей, которые будут разбираться позже,
	// в девятой главе книги.

	// Ну и ВАЖНО понимать, что тип long double поддерживался как 80-битное представление
	// числа с плавающей запятой только в старых версиях Microsoft Visual C++.
	// В последних версиях, в том числе и в Visual Studio Community 2017, тип
	// long double хоть и поддерживается и отличается компилятором от типа double,
	// однако, на деле является таким же 64-битным представлением числа с плавающей
	// запятой, как и double. Эти типы в указанной среде разработки идентичны и
	// значения таких типов занимают по 8 байт (64 бита) каждое.

	// Размер 8 байт (64 бита) позволяет оперировать числами длиной в 15-16 значимых
	// десятичных разрядов (включая разряды после десятичной точки). То есть, к примеру,
	// получив на вход строку "$123,456,789,012,345.62" наш метод mstold вернет
	// число типа long double = 123456789012345.63
	// Из этого примера видно, что в последнем, 17-м разряде, вместо цифры "2" стоит
	// цифра "3". То есть ручаться можно только за точность первых 15-16 разрядов.

	return sum; // возвращаем полученное значение
}

// метод преобразует число типа long double (поле sum класса bMoney) в денежную строку
// и возвращает эту строку через первый параметр
void bMoney::ldtoms(wchar_t str[])
{
	// В условиях упражнения в книге сказано, что при преобразовании числа в строку
	// можно использовать объект класса ostrstream "как рассматривалось ранее в этой главе".
	// На самом деле в главе 7, к которой идет это упражнение, и ранее Лафоре ничего
	// не писал об этом. Автор перепутал с 12-й главой, а конкретнее — см. стр.585 книги.

	// Итак, объект класса ostrstream можно здесь рассматривать как аналог стандартных
	// потоков ввода и вывода cin и cout. Для его использования нужно включить в программу
	// заголовочный файл <strstream>. Однако, нужно учитывать, что использование класса
	// ostrstream не одобряется, начиная со стандарта C++98.

	// Вместо класса ostrstream стандарт языка C++ рекомендует использовать ostringstream,
	// который требует включения в программу заголовочного файла <sstream>. Оба класса
	// (ostrstream и ostringstream) работают со строками-массивами типа char. Для широких
	// символов типа wchar_t можно использовать класс wostringstream, тоже требующий включения
	// в программу заголовочного файла <sstream>.

	// Вместо wostringstream я взял класс wstringstream, с объектом которого можно использовать
	// и вывод (оператор вставки), и ввод (оператор извлечения из потока).
	
	wchar_t ustring[80]; // временная строка
	wstringstream woss;  // создадим объект стандартного класса wstringstream
	
	// преобразуем число sum типа long double в строку, указав, что нужен неэкспоненциальный
	// вид числа и количество знаков после десятичной точки должно быть 2
	woss << setiosflags(ios::fixed) << setprecision(2) << sum;
	// загрузим полученную строку из потока во временную строку
	woss >> ustring;

	int i = 0, n = 0, j;       // индексы строк str и ustring соответственно
	int len = wcslen(ustring); // длина временной строки ustring
	wchar_t delim3 = L',';     // символ, разделяющий тройки разрядов (разделитель)
	
	str[i++] = L'$';  // первым в денежной строке идет символ доллара

	// выражение (len - 3) означает количество знаков числа
	// без десятичной точки и двух разрядов после точки

	if (len > 6) // если в числе требуются разделители
	{
		if ((len - 3) % 3 == 2)      // если старших разрядов до разделителя два,
		{
			str[i++] = ustring[n++]; // то переписать два старших разряда
			str[i++] = ustring[n++];
			str[i++] = delim3;       // и вписать разделитель
		}
		else if ((len - 3) % 3 == 1) // иначе, если старший разряд до разделителя один,
		{
			str[i++] = ustring[n++]; // то переписать старший разряд
			str[i++] = delim3;       // и вписать разделитель
		}
	}

	for (j = n; j < len - 3; j++) // переберем оставшиеся символы в цикле
	{
		str[i++] = ustring[j];    // перепишем очередной разряд
		// после каждой тройки разрядов вставляем разделитель, если
		// только это не последняя тройка разрядов
		if (((j - n + 1) % 3 == 0) && (j != len - 3 - 1))
			str[i++] = delim3;
	}

	str[i++] = ustring[j++]; // перепишем точку и два
	str[i++] = ustring[j++]; // разряда после точки (центы)
	str[i++] = ustring[j];
	str[i]   = L'\0';        // последним вписываем нулевой символ
}