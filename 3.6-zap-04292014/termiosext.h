#ifndef TERMIOSEXT_H
#define TERMIOSEXT_H

#ifdef Q_OS_ANDROID
static __inline__ int tcdrain(int fd)
{
    return ioctl(fd, TCSBRK, (void *)(intptr_t)1);
}
#endif

#endif // TERMIOSEXT_H
