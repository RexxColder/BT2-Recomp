
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
M2C_UNK DemoCam_Term();
M2C_UNK ObjOutline_Term_25A468();
M2C_UNK func_0025E5D8();
M2C_UNK func_00261D10();
M2C_UNK func_00280DE8();
M2C_UNK func_0028BB60(void *);
M2C_UNK func_002A8648();
extern void *D_003876B0;
void func_00105200(void)
{
  u8 *new_var;
  new_var = (u8 *) D_003876B0;
  func_0028BB60(*((void **) (new_var + 0x3C)));
  new_var = (u8 *) D_003876B0;
  func_0028BB60(*((void **) (new_var + 8)));
  func_0028BB60(D_003876B0);
  D_003876B0 = 0;
  ObjOutline_Term_25A468();
  func_00280DE8();
  func_0025E5D8();
  func_00261D10();
  func_002A8648();
  DemoCam_Term();
}
