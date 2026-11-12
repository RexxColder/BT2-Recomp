#include "common.h"

/* EftShotNullGroup_Init */
u32 EftShotNullGroup_Init(u32 a0) { return BtlTask_CreateChildList(a0, 2, 8); }
