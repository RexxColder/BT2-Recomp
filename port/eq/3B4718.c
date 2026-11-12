
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
M2C_UNK BtlLoad_EndStageSwap();
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK gGfx __attribute__((section(".data")));
void func_003B4718(void)
{
  M2C_UNK *new_var;
  sceGsSyncPath(0, 0);
  BtlLoad_EndStageSwap();
  new_var = &gGfx;
  *((s32 *) (0x234 + ((u8 *) new_var))) = (s32) ((*((s32 *) (((u8 *) new_var) + 0x234))) + 1);
}
