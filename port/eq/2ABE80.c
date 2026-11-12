#include "common.h"

void func_0028B218(s32 arg0);
s32 BtlStage_IsReady(void);
void BtlScene_Term(void);
void func_00273868(void);
void func_0025BAF0(void);
void func_002A3A80(void);
void BtlChars_OnModelLoaded(s32 arg0);
void func_0028BB60(s32 arg0);
void func_0025E1E8(void);
void func_00262428(void);
extern u8 D_003B2654[] __attribute__((section(".data")));

void func_002ABE80(s32 arg0) {
    u8 *temp_s1;
    void (*temp_v0)(void);

    temp_s1 = *(u8 **)(D_003B2654 + 0x58);
    func_0028B218(arg0);
    if (BtlStage_IsReady() != 0) {
        BtlScene_Term();
    }
    func_00273868();
    func_0025BAF0();
    func_002A3A80();
    BtlChars_OnModelLoaded(*(s32 *)(D_003B2654 + 0xC));
    if (*(s32 *)(D_003B2654 + 0x14) != 0) {
        func_0028BB60(*(s32 *)(D_003B2654 + 0x14));
    }
    temp_v0 = *(void (**)(void))(temp_s1 + 0x14);
    if (temp_v0 != NULL) {
        temp_v0();
    } else {
        func_0025E1E8();
        func_00262428();
    }
    *(s32 *)(D_003B2654 + 0x14) = 0;
}
