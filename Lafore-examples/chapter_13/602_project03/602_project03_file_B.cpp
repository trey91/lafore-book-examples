﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 602_project03_file_B.cpp

extern int globalVar; // только объявление
                      // (так как эта переменная уже определена в файле A)

int main()
{
	globalVar = 3;    // теперь здесь нет ошибки
}