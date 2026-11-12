
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
M2C_UNK func_002E93C0();
M2C_UNK func_002E93D8();
M2C_UNK func_002EA050(M2C_UNK *);
M2C_UNK func_002F4130(void *, s32);
M2C_UNK func_002F43D0();
M2C_UNK func_002F6838(void *, M2C_UNK);
M2C_UNK func_002FFEF8(s32);
M2C_UNK func_00300598(s32, s32);
extern M2C_UNK D_0037C388 __attribute__((section(".data")));
void func_002ED758(void *arg0)
{
  s32 temp_s1;
  u8 *temp_a0;
  s32 new_var;
  temp_s1 = *((s32 *) (((u8 *) arg0) + 0x94));
  if (arg0 == 0)
  {
    func_002EA050(&D_0037C388);
    return;
  }
  func_002F43D0(arg0);
  func_002E93C0();
  new_var = *((s32 *) (((u8 *) arg0) + 0x10));
  *((s8 *) (((u8 *) arg0) + 2)) = 4;
  func_002F4130(arg0, new_var);
  temp_a0 = *((u8 **) (((u8 *) arg0) + 0x14));
  ((M2C_UNK (*)(u8 *))(*(u8 **)(*(u8 **)temp_a0 + 0x14)))(temp_a0);
  func_00300598(temp_s1, (*((s16 *) (((u8 *) arg0) + 0x3E))) << 0xB);
  func_002E93D8();
  func_002FFEF8(temp_s1);
  func_002F6838(arg0, 1);
}
