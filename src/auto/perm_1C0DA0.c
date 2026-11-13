
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
M2C_UNK func_0014EAE8(s32, void *);
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
void func_001C0DA0(void *arg0, void *arg1)
{
  s64 *new_var;
  void *temp_s0;
  temp_s0 = *((void **) (((u8 *) arg0) + 0x38));
  memset(temp_s0, 0, 0xAD0);
  *((s32 *) (((u8 *) temp_s0) + 0)) = (s32) (*((s32 *) (((u8 *) arg1) + 0)));
  *((s32 *) (((u8 *) temp_s0) + 4)) = (s32) (*((s32 *) (((u8 *) arg1) + 4)));
  *((f32 *) (((u8 *) temp_s0) + 0x60)) = (f32) (*((f32 *) (((u8 *) arg1) + 0x60)));
  *((s32 *) (((u8 *) temp_s0) + 0x64)) = (s32) (*((s32 *) (((u8 *) arg1) + 0x64)));
  *((s64 *) (((u8 *) temp_s0) + 0xA70)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x10)));
  *((s64 *) (((u8 *) temp_s0) + 0xA78)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x18)));
  *((s64 *) (((u8 *) temp_s0) + 0xA80)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x20)));
  *((s64 *) (((u8 *) temp_s0) + 0xA88)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x28)));
  new_var = (s64 *) (((u8 *) temp_s0) + 0xAB0);
  *((s64 *) (((u8 *) temp_s0) + 0xA90)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x30)));
  *((s64 *) (((u8 *) temp_s0) + 0xA98)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x38)));
  *((s64 *) (((u8 *) temp_s0) + 0xAA0)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x40)));
  *((s64 *) (((u8 *) temp_s0) + 0xAA8)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x48)));
  *new_var = (s64) (*((s64 *) (((u8 *) arg1) + 0x50)));
  *((s64 *) (((u8 *) temp_s0) + 0xAB8)) = (s64) (*((s64 *) (((u8 *) arg1) + 0x58)));
  *((s32 *) (((u8 *) temp_s0) + 0xACC)) = 1;
  func_0014EAE8(*((s32 *) (((u8 *) arg1) + 4)), temp_s0 + 0x70);
}
