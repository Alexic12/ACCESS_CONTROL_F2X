#include "error.h"
#include "serial.h"

const char* Error::file_names[ERROR_MAX_FILES] = {};
// const char* error_names[_ERR_T_LEN] = {""};
uint16_t Error::n_files = 0;

void Error::print_file_table() {
    Serial.println("File table:");
    for (uint16_t i = 0; i < n_files; i++) {
        printlnf(Serial, "  -%I16u: %s", i, file_names[i]);
    }
}

uint16_t Error::_get_file_id(const char* file_name) {
    assert(n_files < ERROR_MAX_FILES);
    file_names[n_files] = file_name;
    return n_files++;
}

const char* Error::_get_file_name(const char* full_name) {
    size_t len = strlen(full_name);
    size_t i = len - 1;
    while (full_name[i] != '/' && full_name[i] != '\\' && i > 0) {
        i--;
    }
    return full_name + i + 1;
}

void Error::_throw(err_t error, uint16_t file_id, uint32_t line) {
    printlnf(Serial, "Error #%I32u thrown in file %s and line %I32u.", (uint32_t)error, file_names[file_id], line);
}

void Error::_rethrow(err_t error, uint16_t file_id, uint32_t line) {
    printlnf(Serial, "Error #%I32u re-thrown in file %s and line %I32u.", (uint32_t)error, file_names[file_id], line);
}

void Error::_capture(err_t error, uint16_t file_id, uint32_t line) {
    printlnf(Serial, "Error #%I32u captured in file %s and line %I32u.", (uint32_t)error, file_names[file_id], line);
}

// Acá entra cuando falla un assert
void aFailed(uint8_t* file, uint32_t line) {
    while (1) {
        printf(Serial, "ERROR: Assert failed on file %s and line %I32u\n", file, line);
        delay(1000);
    }
}