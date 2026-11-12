
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
M2C_UNK func_003126C8(void *, M2C_UNK);
void func_001E6920(void *arg0, s32 arg1)
{
  u8 *new_var;
  s64 *temp_a0;
  new_var = (u8 *) arg0;
  if (arg0 != 0)
  {
    temp_a0 = *((s64 **) (new_var + 0x38));
    if (((*temp_a0) & 5) == 1)
    {
      func_003126C8((new_var = temp_a0) + 0x30, arg1);
    }
  }
}
