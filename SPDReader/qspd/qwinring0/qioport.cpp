#include "qioport.h"

QIOPort::QIOPort()
{
    baseAddress = 0;
}

QIOPort::QIOPort(WORD address)
{
    baseAddress = address;
}

QIOPort::~QIOPort()
{

}
