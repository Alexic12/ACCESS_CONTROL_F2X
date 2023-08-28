#ifndef SERIAL_H
#define SERIAL_H
#include "Arduino.h"
#include "../ext_libs/printf.h"

int printf(Print& serial, const char* format, ...);
int printlnf(Print& serial, const char* format, ...);

#endif