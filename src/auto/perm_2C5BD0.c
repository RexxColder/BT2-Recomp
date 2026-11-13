
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
s32 func_002C2FF0(M2C_UNK, M2C_UNK);
s32 func_002C5CB0();
M2C_UNK func_002CBE28();
s32 func_002DFF00(M2C_UNK, M2C_UNK *);
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern s32 D_00346E54 __attribute__((section(".data")));
extern M2C_UNK D_00395928 __attribute__((section(".data")));
extern M2C_UNK D_00399C68 __attribute__((section(".data")));
extern M2C_UNK D_00399C90 __attribute__((section(".data")));
extern M2C_UNK D_00399C98 __attribute__((section(".data")));
s32 func_002C5BD0(void)
{
  s32 temp_v0;
  func_002CBE28();
  if (func_002C5CB0() != 0)
  {
    loop_1:
    goto loop_1;

  }
  temp_v0 = func_002DFF00(8, &D_00395928);
  if (temp_v0 != 0)
  {
    return func_002C2FF0(0, (!((temp_v0 ^ 0xFF03FF05) != 0)) ? (0xFF000F13) : (0xFF000F01));
  }
  memset(&D_00399C68, 0, 0x24);
  memset(&D_00399C90, 0, 8);
  memset(&D_00399C98, 0, 0x40);
  D_00346E54 = 0;
  return 0;
}
