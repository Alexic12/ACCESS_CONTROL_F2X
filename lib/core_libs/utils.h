#ifndef UTILS_H
#define UTILS_H
#include "Arduino.h"
// Acá van funciones y macros de utilidad para todo el programa

// TODO: Probar con diferentes tipos de dato
#define GET_BIT(reg, bit_i) (((reg) >> (bit_i)) & 1u)
#define SET_BIT(reg, bit_i) ((reg) |= (1u << (bit_i)))
#define CLEAR_BIT(reg, bit_i) ((reg) &= ~(1u << (bit_i)))
#define ASSIGN_BIT(reg, bit_i, val) (val ? SET_BIT(reg, bit_i) : CLEAR_BIT(reg, bit_i))
#define IS_NUM(a) (a >= 48 && a <= 57)
#define TO_NUM(a) (a - 48)

const char* get_FW_ver();
const char* get_HW_ver();


#endif