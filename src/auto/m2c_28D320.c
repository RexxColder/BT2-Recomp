#include "m2c_macros.h"

extern s32 gColMeshBase;

s32 ColMesh_GetPoly(void *arg0, s32 arg1) {
    return gColMeshBase + (M2C_FIELD(arg0, s32 *, 0x10) * 4) + (arg1 << 5);
}
