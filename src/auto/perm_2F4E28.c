
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
M2C_UNK func_002EA050(M2C_UNK *);
s32 func_002F14E0(s32);
extern M2C_UNK D_0037C890 __attribute__((section(".data")));
inline u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

s32 func_002F4E28(void *arg0)
{
  s32 *new_var;
  if (arg0 == 0)
  {
    func_002EA050(&D_0037C890);
    return -1;
  }
 do { if ((*((s8 *) (((u8 *) arg0) + 1))) < 2) { return 0; } new_var = (s32 *) inline_fn(((u8 *) arg0) + 4); } while (0);
  return func_002F14E0(*new_var);
}
