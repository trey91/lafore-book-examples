﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// 608_project15_headtwo.h

#if !defined( HEADCOM ) // если флаг HEADCOM еще не определен,
#define HEADCOM         // определить его

struct foo              // определение структуры
{
	int member;
};

#endif                  // окончание защитного условия

// В учебнике Лафоре здесь вместо структуры определена глобальная переменная,
// но ранее сам автор не рекомендовал определять глобальные переменные в заголовочных
// файлах, так как возникнет ошибка множественного определения, если такой заголовочный
// файл будет включен в несколько исходных файлов многофайловой программы. Поэтому
// я решил здесь определить структуру.