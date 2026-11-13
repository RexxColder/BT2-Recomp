
asm(".include \"labels.inc\"\n");;
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
extern void *D_003878E4;
void func_001E4C80(s32 arg0, s32 arg1, s32 arg2)
{
  void *temp_v1;
  if ((arg0 != 0) || (arg1 != 0))
  {
    temp_v1 = D_003878E4 + ((*((s32 *) (((u8 *) D_003878E4) + 0x600))) * 0xC);
    *((s32 *) (((u8 *) temp_v1) + 0)) = arg0;
    *((s32 *) (((u8 *) temp_v1) + 4)) = arg1;
    *((s32 *) (((u8 *) temp_v1) + 8)) = arg2;
    *((s32 *) (((u8 *) D_003878E4) + 0x600)) = (s32) ((*((s32 *) (((u8 *) D_003878E4) + 0x600))) + 1);
  }
}
