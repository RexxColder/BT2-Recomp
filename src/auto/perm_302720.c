
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
extern s32 D_0035D220 __attribute__((section(".data")));
extern s32 D_0035D228 __attribute__((section(".data")));
void func_00302720(void *arg0, u32 arg1)
{
  u8 temp_v1;
  if (((D_0035D228 != 1) || (D_0035D220 > 0)) && (arg1 < 2U))
  {
    temp_v1 = (u8) (*((s8 *) (((u8 *) arg0) + 0x56)));
    if ((*((s8 *) (((u8 *) arg0) + 0x56))) != arg1)
    {
      *((u8 *) (((u8 *) arg0) + 1)) = temp_v1;
      *((s8 *) (((u8 *) arg0) + 0x56)) = (s8) arg1;
    }
  }
}
