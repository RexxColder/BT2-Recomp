
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
M2C_UNK func_003D4518(void *);
M2C_UNK func_26EA58(void *);
M2C_UNK func_277E70(s32, M2C_UNK, M2C_UNK);
extern void *D_00423120 __attribute__((section(".data")));
void func_003D0298(void)
{
  int new_var;
  s32 var_s1;
  s32 var_s2;
  void *temp_a0;
  new_var = (var_s2 = 0);
  var_s1 = 7;
  func_277E70(*((s32 *) (((u8 *) D_00423120) + 0x170)), 0, 0x80);
  func_003D4518(D_00423120);
  do
  {
    var_s1 -= 1;
    temp_a0 = D_00423120 + var_s2;
    var_s2 += 0x28;
    func_26EA58(temp_a0 + 0x30);
  }
  while (var_s1 >= new_var);
}
