#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))

void *memcpy(void *dst, const void *src, u32 n);
u32 strlen(const char *s);
void func_002F9660(void *s);

/* 0x002F9B38: splits the string arg2 at its first ':' (at most 0x129 characters are looked at). Without a colon
 * the whole string goes to arg1 and arg0 is emptied. With a colon the part before it goes to arg0 (a one-char
 * part, like a drive letter, is dropped: the whole string is then the second part) and the rest to arg1; arg0
 * is then upper-cased by func_002F9660. */
void func_002F9B38(s32 arg0, s32 arg1, s32 arg2) {
    u8 *buf1;
    u8 *buf2;
    u8 *src;
    s32 i;
    s32 j;
    s32 start;
    s32 v;

    buf1 = PTR(arg0);
    buf2 = PTR(arg1);
    src = PTR(arg2);
    if (src == NULL) {
        return;
    }

    i = 0;
    if (src[0] == ':') {
        i = 0;
    } else if (src[0] == 0) {
        i = 0;
    } else {
        for (;;) {
            buf1[i] = src[i];
            i++;
            if (i >= 0x129) {
                break;
            }
            v = src[i];
            if (v == ':' || v == 0) {
                break;
            }
        }
    }
    v = src[i];

    if (v != 0) {
        buf1[i] = 0;
        start = i + 1;
        if (start == 2) {
            buf1[0] = 0;
            start = 0;
        }
        j = start;
        while (j < 0x129 && src[j] != 0) {
            buf2[j - start] = src[j];
            j++;
        }
        buf2[j - start] = 0;
        func_002F9660(buf1);
        return;
    }

    buf1[i] = 0;
    memcpy(buf2, buf1, strlen((const char *)buf1) + 1);
    buf1[0] = 0;
}
