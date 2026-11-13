
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
s32 func_00207EC0();
s32 func_001E74A0(unsigned long r_a0) { /* asm: a0 arrive and pass through untouched */
  int new_var;
  s32 temp_v0;
  s32 var_a0;
  temp_v0 = func_00207EC0(r_a0);
  var_a0 = 0;
  new_var = temp_v0 < 0x76;
  if (new_var)
  {
    temp_v0 = temp_v0 < 0x74;
    var_a0 = temp_v0 == 0;
  }
  return var_a0;
}
