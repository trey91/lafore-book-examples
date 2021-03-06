﻿// исходный текст программы сохранен в кодировке UTF-8 с сигнатурой

// elev_app.h
// клиентский заголовочный файл для программы «ELEV» (симулятор системы из
// нескольких лифтов в многоэтажном здании)

// Данный файл создан в процессе выполнения упражнения (проекта) 2 к главе 16
// учебника Лафоре. Задание из этого упражнения требует написания только лишь
// заголовочных файлов с объявлениями классов (интерфейс библиотеки классов)
// по диаграмме прецедентов и диаграмме классов. Поэтому данный код нельзя
// считать законченной программой, это всего лишь заготовка.

// клиентский заголовочный файл содержит лишь константы, характеризующие
// конкретное здание, и пишется программистом-клиентом (клиентом в том смысле,
// что этот программист использует написанную другими программистами библиотеку
// классов)

// клиентский заголовочный файл с именем elev_app.h заранее включен авторами
// библиотеки классов в заголовочный файл (интерфейс) библиотеки классов

const int NUM_ELEVATORS = 4; // количество лифтов в здании
const int NUM_FLOORS = 20;   // количество этажей в здании