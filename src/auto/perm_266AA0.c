
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
void func_00266AA0(void *arg0, s32 arg1)
{
  *((s32 *) (((u8 *) arg0) + 0x10)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x14)) = 0;
  if (!(arg1 & 0xFF))
  {
    *((s32 *) (((u8 *) arg0) + 0x1C)) = 0;
  }
  *((f32 *) (((u8 *) arg0) + 0x20)) = 2.0f;
  *((s32 *) (((u8 *) arg0) + 0x24)) = 0;
  *((s32 *) (((u8 *) arg0) + 0x28)) = 0;
}
