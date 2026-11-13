
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
void func_002C0E78(s32 arg0, s32 arg1, s32 arg2)
{
  int new_var;
  if (arg1 != 8)
  {
    new_var = (*((s32 *) (((u8 *) (arg0 + (arg1 * 0x74))) - -0x131C)) = arg2);
  }
}
