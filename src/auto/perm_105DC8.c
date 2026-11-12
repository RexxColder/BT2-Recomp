
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
void *func_00105A88();
s32 func_00105DC8(void)
{
  u8 *new_var;
  int new_var2;
  new_var2 = 0x8000;
  new_var = ((u8 *) func_00105A88()) + 4;
  return ((*((s32 *) new_var)) & new_var2) != 0;
}
