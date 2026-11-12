
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
void *func_002F9120();
M2C_UNK strncpy(void *, s32, M2C_UNK);
extern s32 D_0039D6EC __attribute__((section(".data")));
s32 func_002F9208(s32 arg0, s32 arg1)
{
  s32 var_v0;
  void *temp_v0;
  var_v0 = -1;
  if (D_0039D6EC != 0)
  {
    temp_v0 = func_002F9120();
    var_v0 = -2;
    if (temp_v0 != 0)
    {
      var_v0 = 0;
      strncpy(temp_v0, arg0, 0xC);
      *((s32 *) (((u8 *) temp_v0) + 0xC)) = arg1;
    }
  }
  return var_v0;
}
