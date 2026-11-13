
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
M2C_UNK func_001601A0(void *);
void *func_001F3758();
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);
void func_001606C8(void *arg0, void *arg1)
{
  s32 temp_s3;
  void *temp_s0;
  void *temp_v0;
  temp_s3 = *((s32 *) (((u8 *) func_001F3758(arg0)) + 0x38));
  temp_s0 = *((void **) (((u8 *) arg0) + 0x38));
  memset(temp_s0, 0, 0xB30);
  *((void **) (((u8 *) temp_s0) + 0x100)) = arg1;
  temp_v0 = *((void **) (((u8 *) arg1) + 0x24));
  *((f32 *) (((u8 *) temp_s0) + 0x18)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 8)));
  *((f32 *) (((u8 *) temp_s0) + 0x1C)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 4)));
  *((f32 *) (((u8 *) temp_s0) + 0x20)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 4)));
  func_001601A0(arg0);
  func_0014EAE8(temp_s3, temp_s0 + 0x104);
}
