
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
M2C_UNK func_0029BAB0(void *);
void func_00281F00(void *arg0)
{
  s32 var_s1;
  void *var_s0;
  void *temp_a0;
  var_s1 = 3;
  *((s32 *) (((u8 *) arg0) + 0x180)) = 0;
  var_s0 = arg0;
  do
  {
    *((s8 *) (((u8 *) var_s0) + 0x58)) = 0;
    temp_a0 = var_s0 + 0x40;
    var_s1 -= 1;
    var_s0 += 0x60;
    func_0029BAB0(temp_a0);
  }
  while (var_s1 >= 0);
}
