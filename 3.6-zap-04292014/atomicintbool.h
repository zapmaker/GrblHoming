#ifndef ATOMICINTBOOL_H
#define ATOMICINTBOOL_H

#include <QAtomicInt>

// we wrap QAtomicInt because it is possible to accidentally
// access the non-atomic operations of the class (look at the
// header for QAtomicInt to see what I mean, and thus setting
// a value directly against one of these variables will access
// the non-atomic method)
class AtomicIntBool
{
public:
    AtomicIntBool(int newValue = 0);
    void set(int newValue);
    int get();

private:
    QAtomicInt value;
};

#endif // ATOMICINTBOOL_H
