
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
M2C_UNK func_249548();
M2C_UNK func_24C030();
M2C_UNK func_26E908(void *);
M2C_UNK func_28BB60(void *);
extern void *D_00427334 __attribute__((section(".data")));
void func_003DFFC8(void)
{
  s32 var_s0;
  s32 var_s1;
  void *temp_a0;
  var_s1 = 0;
  var_s0 = 1;
  func_249548();
  func_24C030();
  do
  {
    var_s0 -= 1;
    temp_a0 = D_00427334 + var_s1;
    var_s1 += 0x28;
    func_26E908(temp_a0 + 0x10);
  }
  while (var_s0 >= 0);
  func_28BB60(*((void **) (((u8 *) D_00427334) + 4)));
  func_28BB60(D_00427334);
}
