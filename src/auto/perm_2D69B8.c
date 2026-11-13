
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
M2C_UNK func_002D71D0();
M2C_UNK func_002D7240();
M2C_UNK func_002D8CF8();
M2C_UNK func_002E0D18();
extern s32 D_00346E98 __attribute__((section(".data")));
void func_002D69B8(void)
{
  int new_var;
  new_var = 0;
  if (D_00346E98 > new_var)
  {
    func_002D7240();
    func_002E0D18();
    func_002D71D0();
    new_var = 0;
    func_002D8CF8();
 do { D_00346E98 -= 1; } while (new_var);
  }
}
