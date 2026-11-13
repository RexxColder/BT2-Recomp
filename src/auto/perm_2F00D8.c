
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
M2C_UNK func_002E7318();
M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);
extern s32 D_003534A8 __attribute__((section(".data")));
extern M2C_UNK D_003534B0 __attribute__((section(".data")));
void func_002F00D8(void)
{
  unsigned long long new_var;
  new_var = 0;
  if (D_003534A8 == new_var)
  {
    func_002E7318();
    memset(&D_003534B0, new_var, 0xAC0);
  }
  D_003534A8 += 1;
  if (1)
  {
  }
}
