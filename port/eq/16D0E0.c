#include "common.h"

/* 0x0016D0E0: picks the battle-scene pack entry to load for a stage (obj+0x20 -> id) given the current
 * character code func_00207EC0(*obj). Each stage id has a list of (character code -> entry) pairs, tested in order
 * (the last matching one wins); unknown stages use entry 2 when the pack at obj+0x1C has unread data. */
s32 BtlScene_GetPackEntry(u8 *pack, s32 entry);
s32 func_00207EC0(s32 chr);

typedef struct {
    s32 code;
    s32 entry;
} PackPair;

static const PackPair kStage102[] = {{14, 4}, {24, 5}, {29, 6}, {45, 7}, {54, 8}, {55, 9}, {56, 10},
                                      {59, 11}, {81, 12}, {88, 13}, {90, 14}};
static const PackPair kStage103[] = {{13, 4}, {20, 5}, {39, 6}, {82, 7}};
static const PackPair kStage282[] = {{122, 4}, {123, 5}};
static const PackPair kStage284[] = {{6, 4}, {118, 5}};
static const PackPair kStage285[] = {{50, 4}, {110, 5}};
static const PackPair kStage289[] = {{37, 4}, {101, 5}};
static const PackPair kStage290[] = {{52, 4}, {53, 5}};
static const PackPair kStage291[] = {{18, 4}, {76, 5}, {79, 6}};
static const PackPair kStage296[] = {{1, 4}, {2, 5}, {75, 6}};
static const PackPair kStage306[] = {{61, 29}, {63, 30}, {87, 31}, {115, 32}};
static const PackPair kStage346[] = {{48, 59}, {53, 60}};
static const PackPair kStage350[] = {{50, 24}, {110, 25}};
static const PackPair kStage358[] = {{3, 35}, {75, 36}};

#define PAIRS(t) pairs = (t); n = (s32)(sizeof(t) / sizeof((t)[0]))

s32 func_0016D0E0(u8 *obj) {
    s32 stage = **(s32 **)(obj + 0x20);
    s32 result = 0;
    const PackPair *pairs = 0;
    s32 n = 0;
    s32 i;
    u8 *pack;

    switch (stage) {
    case 102: PAIRS(kStage102); break;
    case 103: PAIRS(kStage103); break;
    case 282: PAIRS(kStage282); break;
    case 284: PAIRS(kStage284); break;
    case 285: PAIRS(kStage285); break;
    case 289: PAIRS(kStage289); break;
    case 290: PAIRS(kStage290); break;
    case 291: PAIRS(kStage291); break;
    case 296: PAIRS(kStage296); break;
    case 306: PAIRS(kStage306); break;
    case 346: PAIRS(kStage346); break;
    case 350: PAIRS(kStage350); break;
    case 358: PAIRS(kStage358); break;
    default: break;
    }

    if (pairs == 0) {
        pack = *(u8 **)(obj + 0x1C);
        if (*(s32 *)(pack + 0xC) != *(s32 *)(pack + 8)) {
            result = BtlScene_GetPackEntry(pack, 2);
        }
        return result;
    }
    for (i = 0; i < n; i++) {
        if (func_00207EC0(*(s32 *)obj) == pairs[i].code) {
            result = BtlScene_GetPackEntry(*(u8 **)(obj + 0x1C), pairs[i].entry);
        }
    }
    return result;
}
