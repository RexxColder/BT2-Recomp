
asm(".include \"labels.inc\"\n");;
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
M2C_UNK func_0028BB60(s32);
extern M2C_UNK D_00388A48 __attribute__((section(".data")));
void func_00262460(s32 arg0)
{
  s32 temp_v0;
  s32 temp_v0_2;
  s32 temp_v0_3;
  void *temp_s0;
  temp_s0 = &D_00388A48;
  temp_s0 = temp_s0 + (arg0 * 0x30);
  if ((*((s32 *) (((u8 *) temp_s0) + 0))) & 1)
  {
    temp_v0 = *((s32 *) (((u8 *) temp_s0) + 0x24));
    if (temp_v0 != 0)
    {
      func_0028BB60(temp_v0);
      *((s32 *) (((u8 *) temp_s0) + 0x24)) = 0;
    }
    temp_v0_2 = *((s32 *) (((u8 *) temp_s0) + 0x28));
    if (temp_v0_2 != 0)
    {
      func_0028BB60(temp_v0_2);
      *((s32 *) (((u8 *) temp_s0) + 0x28)) = 0;
    }
    temp_v0_3 = *((s32 *) (((u8 *) temp_s0) + 0x2C));
    if (temp_v0_3 != 0)
    {
      func_0028BB60(temp_v0_3);
      *((s32 *) (((u8 *) temp_s0) + 0x2C)) = 0;
    }
    *((s32 *) (((u8 *) temp_s0) + 0)) = (s32) ((*((s32 *) (((u8 *) temp_s0) + 0))) & (~1));
  }
}
