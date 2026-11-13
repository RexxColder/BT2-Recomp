
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
s32 func_002F1748(s32);
extern M2C_UNK D_0037C8C0 __attribute__((section(".data")));
inline int inline_fn(void *arg0, int arg1)
{
  return (*((s8 *) (((u8 *) arg0) + arg1))) < 2;
}

s32 func_002F4EB0(void *arg0)
{
  int new_var;
  new_var = 0;
  if (arg0 == 0)
  {
    func_002EA050(&D_0037C8C0);
    return -1;
  }
 do { if (inline_fn(arg0, 1)) { return 0; } } while (new_var);
  return func_002F1748(*((s32 *) (((u8 *) arg0) + 4)));
}
