
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
s32 BtlStage_IsReady();
M2C_UNK func_003126C8(M2C_UNK *, M2C_UNK *);
extern M2C_UNK D_00344BA0 __attribute__((section(".data")));
extern void *gBtlStage;
void func_002767A8(M2C_UNK *arg0)
{
  void *temp_v0;
  if (BtlStage_IsReady() == 0)
  {
    func_003126C8(arg0, &D_00344BA0);
    return;
  }
  temp_v0 = *((void **) (((u8 *) gBtlStage) + 4));
  *((f32 *) (((u8 *) arg0) + 0)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x30)));
  *((f32 *) (((u8 *) arg0) + 4)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x34)));
  *((f32 *) (((u8 *) arg0) + 8)) = (f32) (*((f32 *) (((u8 *) temp_v0) + 0x38)));
  *((f32 *) (((u8 *) arg0) + 0xC)) = 1.0f;
  func_003126C8(&D_00344BA0, arg0);
}
