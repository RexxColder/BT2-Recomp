
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
M2C_UNK BtlPool_SetInitArg(M2C_UNK);
M2C_UNK BtlPool_Term();
M2C_UNK BtlScene_Reset(M2C_UNK);
M2C_UNK BtlTaskList_Destroy(s32);
M2C_UNK EftCam_Term();
M2C_UNK EftHit_Term();
M2C_UNK EftSprAnim_TermPool();
M2C_UNK EftWeather_Term();
M2C_UNK func_001E4C40();
M2C_UNK func_0028BB60(s32 *);
extern s32 *gBtlScene;
void BtlScene_Term(void)
{
  s32 *new_var;
  BtlScene_Reset(0);
  new_var = &(*gBtlScene);
  BtlTaskList_Destroy(*new_var);
  func_001E4C40();
  EftHit_Term();
  EftCam_Term();
  EftWeather_Term();
  EftSprAnim_TermPool();
  BtlPool_Term();
  BtlPool_SetInitArg(0);
  new_var = gBtlScene;
  if (new_var != 0)
  {
    func_0028BB60(gBtlScene);
    gBtlScene = 0;
  }
}
