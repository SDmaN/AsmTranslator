#ifndef VMEXECUTABLE_H
#define VMEXECUTABLE_H

#include <ostream>
#include "TypeDefines.h"

typedef std::vector<Address> RelativesTable;

/*
 * Структура:
 * [IP] - 2 БАЙТА
 * [Количество записей в таблице] - 4 байта
 * [Таблица (адреса последовательно)] - Каждый адрес 2 байта
 * [Код] - до конца файла
 */

// Исполняемый модуль интерпретатора
class VmExecutable
{
public:
    VmExecutable();

    Address ip() const;
    void setIp(Address ip);

    void appendRelativeAddress(Address relative); // Добавляет адрес в таблицу
    void appendBytes(const ByteArray &bytes); // Добавляет массив байт к программе

    bool empty() const; // Проверяет, пуст ли модуль
    void clear(); // Очищает модуль

    bool ipIsSet() const; // Проверяет, установлен ли IP

    void write(std::ostream &s); // Записывает исполняемый файл в поток
    void write(const std::string &fileName); // Записывает исполняемый файл на диск

private:
    RelativesTable m_relativesTable; // Таблица относительных адресов
    Address m_ip;
    ByteArray m_programBytes; // Машинный код программы

    bool m_ipIsSet; // Определяет, установлен ли IP

    void writeIp(std::ostream &s); // Записывает IP в выходной файл
    void writeTableSize(std::ostream &s);
    void writeTable(std::ostream &s);
    void writeProgramBytes(std::ostream &s);
};

#endif //VMEXECUTABLE_H
