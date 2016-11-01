#include <fstream>

#include "VmExecutable.h"
#include "ErrorsHandling/Exceptions/FileNotFoundException.h"

VmExecutable::VmExecutable()
        : m_ip(0), m_ipIsSet(false)
{
}

Address VmExecutable::ip() const
{
    return m_ip;
}

void VmExecutable::setIp(Address ip)
{
    m_ipIsSet = true;
    m_ip = ip;
}

void VmExecutable::appendRelativeAddress(Address relative)
{
    m_relativesTable.push_back(relative);
}

void VmExecutable::appendBytes(const ByteArray &bytes)
{
    // Вставляем в конец вектора дополнительные байты
    m_programBytes.insert(std::end(m_programBytes), std::begin(bytes), std::end(bytes));
}

bool VmExecutable::empty() const
{
    return m_programBytes.empty();
}

void VmExecutable::clear()
{
    m_programBytes.clear();
    m_relativesTable.clear();
    m_ip = 0;
    m_ipIsSet = false;
}

bool VmExecutable::ipIsSet() const
{
    return m_ipIsSet;
}

void VmExecutable::write(std::ostream &s)
{
    writeIp(s); // Сначала IP, 2 байта
    writeTableSize(s); // Размер таблицы, 4 байта
    writeTable(s); // Таблица адресов. n * 2 байт (n - количество записей в таблице)
    writeProgramBytes(s); // Байты программы
}

void VmExecutable::writeProgramBytes(std::ostream &s)
{
    for(Byte b : m_programBytes)
        s.write(&b, sizeof(b));
}

void VmExecutable::writeTable(std::ostream &s)
{
    for(Address address : m_relativesTable)
        s.write(reinterpret_cast<char *>(&address), sizeof(address));
}

void VmExecutable::writeTableSize(std::ostream &s)
{
    std::size_t relativeTableSize = m_relativesTable.size();
    s.write(reinterpret_cast<char *>(&relativeTableSize), sizeof(relativeTableSize));
}

void VmExecutable::writeIp(std::ostream &s)
{
    s.write(reinterpret_cast<char *>(&m_ip), sizeof(m_ip));
}

void VmExecutable::write(const std::string &fileName)
{
    std::ofstream file(fileName, std::ios::binary | std::ofstream::out);

    if(!file.is_open())
        throw FileNotFoundException("Не удалось открыть файл " + fileName);

    write(file);
}
