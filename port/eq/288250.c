#include "common.h"

void func_00325830(void *arg0, void *arg1, s32 arg2);
s32 strlen(void *arg0);
extern u8 D_00377370[];
extern u8 D_00377388[];
extern u8 D_003773A0[];
extern u8 D_003773B8[];
extern u8 D_003773D0[];
extern u8 D_003773E8[];
extern u8 D_00377400[];
extern u8 D_00389450[];

void *func_00288250(void *arg0) {
    func_00325830(D_00389450, D_00377370, *(s32 *)((u8 *)arg0 + 0));
    func_00325830(D_00389450 + strlen(D_00389450), D_00377388, *(s32 *)((u8 *)arg0 + 4));
    func_00325830(D_00389450 + strlen(D_00389450), D_003773A0, *(s32 *)((u8 *)arg0 + 8));
    func_00325830(D_00389450 + strlen(D_00389450), D_003773B8, *(s32 *)((u8 *)arg0 + 0xC));
    func_00325830(D_00389450 + strlen(D_00389450), D_003773D0, *(s32 *)((u8 *)arg0 + 0x14));
    func_00325830(D_00389450 + strlen(D_00389450), D_003773E8, *(s32 *)((u8 *)arg0 + 0x10));
    func_00325830(D_00389450 + strlen(D_00389450), D_00377400, *(s32 *)((u8 *)arg0 + 0x18));
    return D_00389450;
}
