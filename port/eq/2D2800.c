#include "common.h"

s64 func_002D2750(void);
extern s64 D_00399D40 __attribute__((section(".data")));

s64 func_002D2800(void) {
    s64 v = D_00399D40;

    if (v == 0) {
        func_002D2750();
        v = D_00399D40;
    }
    return v;
}
