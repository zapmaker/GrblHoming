#include "atomicintbool.h"

AtomicIntBool::AtomicIntBool(int newValue /* = 0 */)
    : value(newValue)
{
}

void AtomicIntBool::set(int newValue)
{
    value.fetchAndStoreRelaxed(newValue);
}

int AtomicIntBool::get()
{
    return value.fetchAndAddRelaxed(0);
}
/*
int AtomicIntBool::getAndClear()
{
    return value.fetchAndStoreRelease(0);
}
*/
