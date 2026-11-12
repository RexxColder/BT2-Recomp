#include "common.h"

s32 func_002AC668(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 var_t0;
    s32 var_t1;
    s32 var_v0;

    var_t1 = 0;
    if (arg0 < 0x54) {
        var_t0 = 0;
        var_v0 = 0x21;
        goto block_125;
    }
    if (arg0 >= 0x5D) {
        if (arg0 >= 0x66) {
            if (arg0 >= 0x6F) {
                if (arg0 >= 0xAB) {
                    if (arg0 >= 0xB4) {
                        if (arg0 >= 0xC3) {
                            if (arg0 >= 0xD8) {
                                if (arg0 >= 0xE1) {
                                    if (arg0 >= 0x129) {
                                        if (arg0 >= 0x138) {
                                            if (arg0 >= 0x14D) {
                                                if (arg0 >= 0x156) {
                                                    if (arg0 >= 0x16E) {
                                                        if (arg0 >= 0x1AD) {
                                                            if (arg0 >= 0x1BF) {
                                                                if (arg0 >= 0x1E0) {
                                                                    if (arg0 >= 0x1F5) {
                                                                        if (arg0 >= 0x204) {
                                                                            if (arg0 >= 0x216) {
                                                                                if (arg0 >= 0x228) {
                                                                                    if (arg0 >= 0x243) {
                                                                                        if (arg0 >= 0x25E) {
                                                                                            if (arg0 >= 0x273) {
                                                                                                var_t0 = 0x18;
                                                                                                if (arg0 < 0x28E) {
                                                                                                    var_v0 = 0x273;
                                                                                                    goto block_125;
                                                                                                }
                                                                                                if (arg1 != NULL) {
                                                                                                    *arg1 = -1;
                                                                                                }
                                                                                                if (arg2 != NULL) {
                                                                                                    *arg2 = -1;
                                                                                                }
                                                                                                if (arg3 != NULL) {
                                                                                                    *arg3 = -1;
                                                                                                }
                                                                                                return 0;
                                                                                            }
                                                                                            var_t0 = 0x17;
                                                                                            var_v0 = 0x25E;
                                                                                            goto block_125;
                                                                                        }
                                                                                        var_t0 = 0x16;
                                                                                        var_v0 = 0x243;
                                                                                        goto block_125;
                                                                                    }
                                                                                    var_t0 = 0x15;
                                                                                    var_v0 = 0x228;
                                                                                    goto block_125;
                                                                                }
                                                                                var_t0 = 0x14;
                                                                                var_v0 = 0x216;
                                                                                goto block_125;
                                                                            }
                                                                            var_t0 = 0x13;
                                                                            var_v0 = 0x204;
                                                                            goto block_125;
                                                                        }
                                                                        var_t0 = 0x12;
                                                                        var_v0 = 0x1F5;
                                                                        goto block_125;
                                                                    }
                                                                    var_t0 = 0x11;
                                                                    var_v0 = 0x1E0;
                                                                    goto block_125;
                                                                }
                                                                var_t0 = 0x10;
                                                                var_v0 = 0x1BF;
                                                                goto block_125;
                                                            }
                                                            var_t0 = 0xF;
                                                            var_v0 = 0x1AD;
                                                            goto block_125;
                                                        }
                                                        var_t0 = 0xE;
                                                        var_v0 = 0x16E;
                                                        goto block_125;
                                                    }
                                                    var_t0 = 0xD;
                                                    var_v0 = 0x156;
                                                    goto block_125;
                                                }
                                                var_t0 = 0xC;
                                                var_v0 = 0x14D;
                                                goto block_125;
                                            }
                                            var_t0 = 0xB;
                                            var_v0 = 0x138;
                                            goto block_125;
                                        }
                                        var_t0 = 0xA;
                                        var_v0 = 0x129;
                                        goto block_125;
                                    }
                                    var_t0 = 9;
                                    var_v0 = 0xE1;
                                    goto block_125;
                                }
                                var_t0 = 8;
                                var_v0 = 0xD8;
                                goto block_125;
                            }
                            var_t0 = 7;
                            var_v0 = 0xC3;
                            goto block_125;
                        }
                        var_t0 = 6;
                        var_v0 = 0xB4;
                        goto block_125;
                    }
                    var_t0 = 5;
                    var_v0 = 0xAB;
                    goto block_125;
                }
                var_t0 = 4;
                var_v0 = 0x6F;
                goto block_125;
            }
            var_t0 = 3;
            var_v0 = 0x66;
            goto block_125;
        }
        var_t0 = 2;
        var_v0 = 0x5D;
        goto block_125;
    }
    var_t0 = 1;
    var_v0 = 0x54;
block_125:
    if (var_v0 != arg0) {
        do {
            var_v0 += 1;
            var_t1 += 1;
        } while (var_v0 != arg0);
    }
    if (arg1 != NULL) {
        *arg1 = var_t0;
    }
    if (arg2 != NULL) {
        *arg2 = var_t1 / 3;
    }
    if (arg3 != NULL) {
        *arg3 = var_t1 % 3;
    }
    return 1;
}
