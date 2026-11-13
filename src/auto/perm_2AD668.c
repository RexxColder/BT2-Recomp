
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
M2C_UNK func_002ADBD0(M2C_UNK);
extern void *D_00387A40;
extern s32 D_003B26A4 __attribute__((section(".data")));
void func_002AD668(void)
{
  int new_var;
  s32 var_a0;
  s32 var_a1;
  void *temp_v1;
  D_003B26A4 = 0;
  func_002ADBD0(3);
  new_var = 1;
  var_a1 = 0;
  var_a0 = 2;
  do
  {
    temp_v1 = (*((s32 *) (((u8 *) D_00387A40) + 8))) + var_a1;
    var_a1 += 0x1520;
    if (((*((s32 *) (((u8 *) temp_v1) + 0xC))) != 0) && ((*((s32 *) (((u8 *) temp_v1) + 0xAF0))) & 2))
    {
      *((s32 *) (((u8 *) temp_v1) + 0x14)) = new_var;
    }
    var_a0 -= new_var;
  }
  while (var_a0 >= 0);
}
