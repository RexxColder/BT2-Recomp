#include "common.h"

/* 0x0018D760 EftPart10_UnlinkGroup(head, tail, p): a doubly linked list of groups with next at +0xF4 and prev at
 * +0xF8 (not the BT3 struct offsets). Returns when *head is NULL. Otherwise removes p: with a prev, it links prev
 * and next (*tail = prev and prev->next = 0 when there is no next); without a prev, *head = next (and *tail = 0
 * when there is no next either, with *head = 0), and next->prev = 0. */
void func_0018D760(s32 *arg0, s32 *arg1, u8 *arg2) {
    s32 prev;
    s32 next;

    if (*arg0 == 0) {
        return;
    }
    prev = *(s32 *)(arg2 + 0xF8);
    if (prev != 0) {
        next = *(s32 *)(arg2 + 0xF4);
        if (next != 0) {
            *(s32 *)((u8 *)next + 0xF8) = prev;
            *(s32 *)((u8 *)prev + 0xF4) = next;
        } else {
            *arg1 = prev;
            *(s32 *)((u8 *)prev + 0xF4) = 0;
        }
    } else {
        next = *(s32 *)(arg2 + 0xF4);
        if (next != 0) {
            *arg0 = next;
            *(s32 *)((u8 *)next + 0xF8) = 0;
        } else {
            *arg0 = 0;
            *arg1 = 0;
        }
    }
}
