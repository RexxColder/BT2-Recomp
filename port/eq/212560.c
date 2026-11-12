#include "common.h"

s32 BtlObjXf_Update(s32 arg0);

u32 func_00212560(s32 arg0) {
    s32 t = BtlObjXf_Update(arg0);
    u32 r;

    r = (u32)t - 0x133;
    if (r < 5) {
        return r;
    }
    r = (u32)t - 0x155;
    if (r < 5) {
        return r;
    }
    r = (u32)t - 0x177;
    if (r < 5) {
        return r;
    }
    r = (u32)t - 0x138;
    if (r < 5) {
        return r;
    }
    r = (u32)t - 0x15A;
    if (r < 5) {
        return r;
    }
    r = (u32)t - 0x17C;
    if (r < 5) {
        return r;
    }
    return 0;
}
