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
    m_programBytes.insert(std::begin(m_programBytes), std::begin(bytes), std::end(bytes));
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
    s.write(reinterpret_cast<char *>(&m_ip), sizeof(m_ip)); // Сначала IP

    std::size_t relativeTableSize = m_relativesTable.size();
    s.write(reinterpret_cast<char *>(&relativeTableSize), sizeof(relativeTableSize));

    for(Byte b : m_programBytes)
        s.write(&b, sizeof(b));
}

void VmExecutable::write(const std::string &fileName)
{
    std::fstream file(fileName);

    if(file.is_open())
        write(file);

    throw FileNotFoundException("Не удалось открыть файл " + fileName);
}
