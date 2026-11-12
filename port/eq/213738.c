#include "common.h"

s32 BtlObjXf_Update(void *a0);
s32 func_001FA3A8(s32 a0);
s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);
s32 func_00217488(void *a0);

void func_00213738(void *arg0) {
    s32 v;

    /* block 1 */
    v = func_00217488(arg0);
    if (v != 0x46) {
        if (v < 0x47) {
            if (v < 0xF) {
                if (v >= 0xD) {
                    func_002113C0(arg0, 1, 2, 1);
                } else if (v >= 0xB || v < 9) {
                    func_002113C0(arg0, 1, 2, 0);
                }
            } else if (v == 0x45) {
                func_002113C0(arg0, 1, 2, 1);
            } else {
                func_002113C0(arg0, 1, 2, 0);
            }
        } else if (v < 0x89) {
            if (v == 0x63) {
                func_002113C0(arg0, 1, 2, 1);
            } else if (v != 0x65) {
                func_002113C0(arg0, 1, 2, 0);
            }
        } else if (v < 0x8B) {
            /* nothing */
        } else if (v < 0x8D) {
            func_002113C0(arg0, 1, 2, 1);
        } else {
            func_002113C0(arg0, 1, 2, 0);
        }
    }

    /* block 2 */
    v = func_00217488(arg0);
    if (v == 0x46) {
        func_002113C0(arg0, 1, 4, 1);
    } else if (v < 0x47) {
        if (v < 0xF) {
            if (v >= 0xD) {
                if (func_00211310(arg0, 0, 2) != 0) {
                    func_002113C0(arg0, 1, 4, 0);
                }
            } else if (v >= 0xB || v < 9) {
                func_002113C0(arg0, 1, 4, 0);
            } else {
                func_002113C0(arg0, 1, 4, 1);
            }
        } else if (v == 0x45) {
            if (func_00211310(arg0, 0, 2) != 0) {
                func_002113C0(arg0, 1, 4, 0);
            }
        } else {
            func_002113C0(arg0, 1, 4, 0);
        }
    } else if (v < 0x89) {
        if (v == 0x63) {
            if (func_00211310(arg0, 0, 2) != 0) {
                func_002113C0(arg0, 1, 4, 0);
            }
        } else if (v == 0x65) {
            func_002113C0(arg0, 1, 4, 1);
        } else {
            func_002113C0(arg0, 1, 4, 0);
        }
    } else if (v < 0x8B) {
        func_002113C0(arg0, 1, 4, 1);
    } else if (v < 0x8D) {
        if (func_00211310(arg0, 0, 2) != 0) {
            func_002113C0(arg0, 1, 4, 0);
        }
    } else {
        func_002113C0(arg0, 1, 4, 0);
    }

    /* block 3 */
    v = func_00217488(arg0);
    if (v == 0x63) {
        func_002113C0(arg0, 1, 8, 1);
    } else if (v < 0x64) {
        if (v < 0xF) {
            if (v >= 0xD) {
                func_002113C0(arg0, 1, 8, 1);
            } else if (v != 0xA) {
                func_002113C0(arg0, 1, 8, 0);
            }
        } else if (v == 0x45) {
            func_002113C0(arg0, 1, 8, 1);
        } else if (v != 0x46) {
            func_002113C0(arg0, 1, 8, 0);
        }
    } else if (v >= 0x8D) {
        func_002113C0(arg0, 1, 8, 0);
    } else if (v >= 0x8B) {
        func_002113C0(arg0, 1, 8, 1);
    } else if (v >= 0x89) {
        /* nothing */
    } else if (v != 0x65) {
        func_002113C0(arg0, 1, 8, 0);
    }

    /* block 4 */
    v = func_00217488(arg0);
    if (v == 0x63) {
        /* nothing */
    } else if (v < 0x64) {
        if (v < 0xF) {
            if (v < 0xD && v != 0xA) {
                func_002113C0(arg0, 5, 0x10, 0);
            }
        } else if (v == 0x45) {
            /* nothing */
        } else if (v == 0x46) {
            func_002113C0(arg0, 5, 0x10, 1);
        } else {
            func_002113C0(arg0, 5, 0x10, 0);
        }
    } else if (v >= 0x8D) {
        func_002113C0(arg0, 5, 0x10, 0);
    } else if (v >= 0x8B) {
        /* nothing */
    } else if (v >= 0x89) {
        func_002113C0(arg0, 5, 0x10, 1);
    } else if (v == 0x65) {
        func_002113C0(arg0, 5, 0x10, 1);
    } else {
        func_002113C0(arg0, 5, 0x10, 0);
    }

    if (func_001FA3A8(BtlObjXf_Update(arg0)) & 0x100010) {
        return;
    }
    func_002113C0(arg0, 1, 0x40000, 0);
    func_002113C0(arg0, 1, 0x80000, 0);
}
