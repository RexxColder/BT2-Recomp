#include "common.h"

/* 0x00147CB0 EftShot_AttrMaskFromBits(bits): bit 1 of bits goes to 0x200 ((bits << 8) & 0x200); bit 2 adds 0x400,
 * bit 3 adds 0x800, bit 4 adds 0x1000, bit 5 adds 0x2000 and bit 6 adds 0x4000. Returns the mask. */
u64 EftShot_AttrMaskFromBits(u64 arg0) {
    u64 bits = arg0;
    u64 mask = (bits << 8) & 0x200;

    if (bits & 0x4) {
        mask |= 0x400;
    }
    if (bits & 0x8) {
        mask |= 0x800;
    }
    if (bits & 0x10) {
        mask |= 0x1000;
    }
    if (bits & 0x20) {
        mask |= 0x2000;
    }
    if (bits & 0x40) {
        mask |= 0x4000;
    }
    return mask;
}
