
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
M2C_UNK func_002E93C0();
M2C_UNK func_002E93D8();
M2C_UNK func_002EA050(M2C_UNK *);
M2C_UNK func_002F4130(void *, s32);
M2C_UNK func_002F44D0();
M2C_UNK func_002F6878(void *, M2C_UNK);
extern M2C_UNK D_0037C790 __attribute__((section(".data")));
void func_002F4348(void *arg0, s32 arg1)
{
  int new_var;
  new_var = 3;
  if ((arg0 == 0) || (arg1 == 0))
  {
    func_002EA050(&D_0037C790);
    return;
  }
  func_002F44D0();
  func_002E93C0();
  *((s8 *) (((u8 *) arg0) + 2)) = new_var;
  func_002F4130(arg0, arg1);
  func_002F6878(arg0, 1);
  func_002E93D8();
}
