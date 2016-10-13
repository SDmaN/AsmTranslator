#include "VmExecutable.h"

VmExecutable::VmExecutable()
        : m_ip(0)
{
}

Address VmExecutable::ip() const
{
    return m_ip;
}

void VmExecutable::setIp(Address ip)
{
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

void VmExecutable::appendByte(Byte byte)
{
    m_programBytes.push_back(byte);
}

void VmExecutable::appendZeroBytes(std::size_t count)
{
    while(count-- > 0)
        appendByte(0);
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
}
