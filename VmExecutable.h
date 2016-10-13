#ifndef VMEXECUTABLE_H
#define VMEXECUTABLE_H

#include "TypeDefines.h"

typedef std::vector<Address> RelativesTable;

// Исполняемый модуль интерпретатора
class VmExecutable
{
public:
    VmExecutable();

    Address ip() const;
    void setIp(Address ip);

    void appendRelativeAddress(Address relative); // Добавляет адрес в таблицу
    void appendBytes(const ByteArray &bytes); // Добавляет массив байт к программе
    void appendByte(Byte byte); // Добавляет байт к программе (например для однобайтовых команд)
    void appendZeroBytes(std::size_t count); // Добавляет нулевые байты к программе

    bool empty() const; // Проверяет, пуст ли модуль
    void clear(); // Очищает модуль

private:
    RelativesTable m_relativesTable; // Таблица относительных адресов
    Address m_ip;
    ByteArray m_programBytes; // Машинный код программы
};

#endif //VMEXECUTABLE_H
