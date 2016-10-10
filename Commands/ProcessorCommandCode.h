#ifndef PROCESSORCOMMANDCODE_H
#define PROCESSORCOMMANDCODE_H

#include "../TypeDefines.h"

const uByte highBit = 0x80; // Самый старший бит "b"

// Коды команд. xR - команда, где бит b установлен
enum ProcessorCommandCode : uByte
{
    // (8 бит)
    Nop = 0, // Ничего не делает
    Stop = 1, // Остановка работы процессора

    // Целая арифметика (24 бит)
    AddI = 2, // Сложение
    AddIR = AddI | highBit,
    SubI = 3, // Вычитание
    SubIR = SubI | highBit,
    MulI = 4, // Умножение
    MulIR = MulI | highBit,
    DivI = 5, // Деление
    DivIR = DivI | highBit,
    ModI = 6, // Остаток от деления
    ModIR = ModI | highBit,

    // Дробная арифметика (24 бит)
    AddF = 7, // Сложение
    AddFR = AddF | highBit,
    SubF = 8, // Вычитание
    SubFR = SubF | highBit,
    MulF = 9, // Умножение
    MulFR = MulF | highBit,
    DivF = 10, //Деление
    DivFR = DivF | highBit,

    // Пересылки (24 бит)
    LoadS = 11, // Загрузка в сумматор
    LoadSR = LoadS | highBit,
    UnloadS = 12, // Выгрузка из сумматора
    UnloadSR = UnloadS | highBit,
    LoadA = 13, // Загрузка в адресный
    LoadAR = LoadA | highBit,
    UnloadA = 14, // Выгрузка из адресного
    UnloadAR = UnloadA | highBit,

    // Приведение типов (8 бит)
    ItF = 15, // Целое к дробному
    FtI = 16, // Дробное к целому

    // Сравнения (24 бит)
    CmpI = 17, // Сравнение целых
    CmpIR = CmpI | highBit,
    CmpF = 18, // Сравнение дробных
    CmpFR = CmpF | highBit,

    // Ввод вывод (8 бит)
    InI = 19, // Ввод целых
    OutI = 20, // Вывод целых
    InF = 21, // Ввод дробных
    OutF = 22, // Вывод дробных

    // Переходы (24 бит)
    Jmp = 23, // Переход к адресу
    JmpR = Jmp | highBit,
    Je = 24, // Переход, если равно
    JeR = Je | highBit,
    Jne = 25, // Переход, если не равно
    JneR = Jne | highBit,
    Jl = 26, // Переход, если меньше
    JlR = Jl | highBit,
    Jg = 27, // Переход, если больше
    JgR = Jg | highBit,
    Jle = 28, // Переход, если меньше или равно
    JleR = Jle | highBit,
    Jge = 29, // Переход, если больше или равно
    JgeR = Jge | highBit,
    Call = 30, // Вызов подпрограммы

    // (8 бит)
    Ret = 31, // Возврат из подпрограммы
};

#endif //PROCESSORCOMMANDCODE_H
