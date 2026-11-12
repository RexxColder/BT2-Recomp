
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
M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK);
s32 func_002C3210();
M2C_UNK func_002CCC70(void *);
M2C_UNK func_002CE648(void *);
s32 func_002D07B0(void *, M2C_UNK);
void func_002CE5C8(void *arg0)
{
  int new_var;
  if (func_002C3210(arg0) != 0)
  {
    func_002C2FF0(0, 0xFF000132);
    return;
  }
  if (func_002D07B0(arg0, 0x2F) == (new_var = 1))
  {
    func_002CCC70(arg0);
  }
  else
  {
    func_002CE648(arg0);
  }
  *((s32 *) (((u8 *) arg0) + 0x44)) = (new_var = 1);
}
