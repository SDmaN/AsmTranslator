#include "VmExecutable.h"

Address VmExecutable::ip() const
{
    return m_ip;
}

void VmExecutable::setIp(Address ip)
{
    m_ip = ip;
}

void VmExecutable::appendRelativeAdress(Address relative)
{
    m_relativesTable.push_back(relative);
}

void VmExecutable::appendProgramBytes(const ByteArray &bytes)
{
    m_programBytes.insert(std::begin(m_programBytes), std::begin(bytes), std::end(bytes));
}

void VmExecutable::appendProgramByte(Byte byte)
{
    m_programBytes.push_back(byte);
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
