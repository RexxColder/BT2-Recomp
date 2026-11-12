
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
M2C_UNK func_00260A50(s32);
s32 func_00261060(s32);
M2C_UNK func_003126C8(s32, M2C_UNK);
extern s32 D_003B2654 __attribute__((section(".data")));
void func_002613F8(s32 arg0, M2C_UNK arg1)
{
  s32 temp_v0;
  int new_var;
  new_var = arg0 & 0xFFFF;
  if (!(D_003B2654 & 0x100))
  {
    temp_v0 = func_00261060(new_var);
    func_003126C8(temp_v0 + 0x9B0, arg1);
    func_00260A50(temp_v0);
  }
}
