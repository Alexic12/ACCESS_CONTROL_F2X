#include "serial.h"

static void put_c(char c, void* extra_arg);

int printf(Print& serial, const char* format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = vfctprintf(put_c, &serial, format, va);
    return ret;
}

int printlnf(Print& serial, const char* format, ...) {
    va_list va;
    va_start(va, format);
    const int ret = vfctprintf(put_c, &serial, format, va);
    serial.println();
    return ret;
}

static void put_c(char c, void* extra_arg) {
    ((Print*)extra_arg)->print(c);
}