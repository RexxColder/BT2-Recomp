
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
void *func_001272E0();
M2C_UNK func_0012F2C0(void *);
M2C_UNK func_0013BE90(void *);
void func_00126CC8(void)
{
  s32 var_s2;
  void *temp_v0;
  void *var_s0;
  temp_v0 = func_001272E0();
  if (temp_v0 != 0)
  {
    var_s2 = 0;
    if ((*((s32 *) (((u8 *) temp_v0) + 0x6000))) > 0)
    {
      var_s0 = temp_v0;
      do
      {
        var_s2 += 1;
        func_0013BE90(var_s0);
 do { func_0012F2C0(var_s0); } while (0);
        var_s0 += 0x180;
      }
      while (var_s2 < (*((s32 *) (((u8 *) temp_v0) + 0x6000))));
    }
  }
}
