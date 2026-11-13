
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
M2C_UNK func_002F1FC8(void *);
M2C_UNK func_002F3378();
M2C_UNK func_002F3390();
inline u8 *inline_fn(u8 *arg0, int arg1)
{
  return arg0 + arg1;
}

s32 func_002F2038(void *arg0)
{
  func_002F3378(arg0);
  func_002F1FC8(arg0);
  *((s32 *) inline_fn((u8 *) arg0, 0x5C)) = 0xFFFFF;
  func_002F3390();
  return 1;
}
