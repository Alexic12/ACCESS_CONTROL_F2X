#include "utils.h"
#include "../ext_libs/printf.h"
#include "../global_config.h"
#include "error.h"

#define LEN_DID_STR 20
#define LEN_VER_STR 12

const char* get_FW_ver() {
    static char ver_str[LEN_VER_STR];
    static bool str_set = false;

    if (!str_set) {
        assert(snprintf_(ver_str, LEN_VER_STR, "%u.%u.%u-%u", V_MAYOR, V_MINOR, V_PATCH, V_VARIANT) < LEN_VER_STR);
        str_set = true;
    }
    return (const char*)ver_str;
}

const char* get_HW_ver() {
    if (HW_VER == HW_V1_0_0_0) {
        return "1.0.0-0";
    }
    assert(false);
}

