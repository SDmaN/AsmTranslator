#include "Utils.h"

union BytesAddress
{
    Byte bytes[2];
    Address address;
};

ByteArray addressToBytes(Address address)
{
    BytesAddress converter;
    converter.address = address;

    return { converter.bytes[0], converter.bytes[1] };
}