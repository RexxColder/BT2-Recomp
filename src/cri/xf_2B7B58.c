#include "common.h"

int sceDmaGetChan(int id);
int sceDmaSync(int ch, int mode, int timeout);

/* Waits until DMA channel `id` is idle. */
void func_002B7B58(int id) {
    int ch = sceDmaGetChan(id);
    while (sceDmaSync(ch, 1, 30) != 0) {
    }
}

/* Polls DMA channel `id` once and stores the busy state in *busy. */
void func_002B7BA0(int id, int *busy) {
    *busy = sceDmaSync(sceDmaGetChan(id), 1, 30);
}
