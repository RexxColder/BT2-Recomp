#include "common.h"
#include "battle/eft_o.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
void *BtlTaskList_AddTail(void *arg0, void *arg1, void *arg2);
extern void *D_003877C4;
extern u8 D_00342018[] __attribute__((section(".data")));

/* 0x00191600 EftBlastObj_Create(arg): copy the 0x30 bytes of the argument block (the asm copies only that far;
 * the header's model field at 0x30 is set to NULL here, as the BT3 version does) and add the task to the blast
 * object list (gp global) with class D_00342018. Returns the task. */
void *EftBlastObj_Create(EftBlastObjArg *arg0) {
    EftBlastObjArg a;

    void *t;
    void bt2_fightlog_note(const char *fmt, ...);
    memcpy(&a, arg0, 0x30);
    a.model = NULL;
    t = BtlTaskList_AddTail(D_003877C4, D_00342018, &a);
    /* B10 log temporal: cada objeto blast creado, quien lo pide y si la lista lo acepto */
    bt2_fightlog_note("B10 BLAST-CREA tarea %p desde %p", t, __builtin_return_address(0));
    return t;
}
