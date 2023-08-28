#ifndef ERROR_H
#define ERROR_H
#include "Arduino.h"

#define ERROR_MAX_FILES 100


#undef assert
#define assert(expr) \
    if (expr) {      \
    } else           \
        aFailed((uint8_t *)__FILE__, __LINE__)



#define CONFIG_ERROR()                                                \
    static const char *__file_name = Error::_get_file_name(__FILE__); \
    static const uint16_t __file_id = Error::_get_file_id(__file_name);


#define THROW(err)                                 \
    {                                              \
        err_t __err = err;                         \
        assert(__err != E_OK);                     \
        Error::_throw(__err, __file_id, __LINE__); \
        return __err;                              \
    }

#define THROW_IF(err, cond) \
    {                       \
        if (cond) {         \
            THROW(err);     \
        }                   \
    }


#define RETHROW(err)                                     \
    {                                                    \
        err_t __err = err;                               \
        if (__err != E_OK) {                             \
            Error::_rethrow(__err, __file_id, __LINE__); \
            return __err;                                \
        }                                                \
    }

#define CAPTURE(err)                                     \
    ({                                                   \
        err_t __err = err;                               \
        if (__err != E_OK) {                             \
            Error::_capture(__err, __file_id, __LINE__); \
        }                                                \
        __err != E_OK;                                   \
    })

#define NOERR() \
    return E_OK

typedef enum {
    E_OK,

    // I2C
    E_I2C_TRANSMIT,
    E_I2C_RECEIVE,

    // Expanders
    E_EXP_HW_FAULT,
    _ERR_T_LEN,

    // Oled
    E_OLED_RES_FAULT,
    E_OLED_EN_ERR,
    E_OLED_INIT_ERR
} err_t;


// Forward declaration
void aFailed(uint8_t *file, uint32_t line);

class Error {
   public:
    static void print_file_table();
    static void _throw(err_t error, uint16_t file_id, uint32_t line);
    static void _rethrow(err_t error, uint16_t file_id, uint32_t line);
    static void _capture(err_t error, uint16_t file_id, uint32_t line);
    static const char *_get_file_name(const char *full_name);
    static uint16_t _get_file_id(const char *file_name);

   private:
    static const char *file_names[ERROR_MAX_FILES];
    // static const char *error_names[_ERR_T_LEN];
    static uint16_t n_files;
    Error();
};


#endif