/*
 * Stage rigid bodies, first part (0x242948..0x2435E0): the list of falling debris pieces. BT3's stg_d.c
 * (0x22FD10..), see battle/stg_d.h for the pool layout. StgRigid_Release..StgRigid_GetSphere follow in
 * src/battle/stg_d_2435E0.c / xd_243680.c / stg_d_243778.c.
 *
 * BT2 differs from BT3 in three places: StgRigid_Create takes its rotation from a global identity matrix
 * (D_00344BF0) instead of building one on the stack; StgRigid_Launch / StgRigid_LaunchSpin draw their random
 * numbers as rand() / 2147483520.0f instead of Rand_FloatRange(0, 1); and the spin vector of
 * StgRigid_Launch is built before the velocity is cleared.
 */
#include "common.h"
#include "sys/math3d.h"
#include "sys/rigid.h"
#include "battle/stg_d.h"
#include "sys/xd_lit.h"

extern void *memset(void *dst, s32 c, u32 n);
extern f32 sqrtf(f32 x);

extern void func_003126C8(Vec4 *dst, Vec4 *src);                 /* Vec4_Copy */
extern void func_00312650(Vec4 *dst, Vec4 *a, Vec4 *b);          /* Vec4_Sub */
extern f32 sceVu0InnerProduct(Vec4 *a, Vec4 *b);
extern void ColSphere_Set(RigidSphere *out, Vec4 *center, f32 radius);
extern s32 ColSphere_TestTri(Vec4 *out, RigidSphere *sphere, StgRigidTri *tri);
extern void func_0011E320(RigidSphere *sphere, s32 hits);        /* StgCol_CollectSphere */
extern void func_00296910(RigidBody *body, Vec4 *point, Vec4 *normal, f32 restitution, f32 friction,
                          f32 depth);                            /* Rigid_AddContact */
extern void func_00297228(RigidBody *body, s32 user, f32 radius, f32 density); /* Rigid_Init */
extern s32 func_00296F70(RigidBody *body);                       /* Rigid_CheckRest */
extern void *func_0028BAA8(u32 size);                            /* heap allocation */
extern void func_0028BB60(void *p);                              /* heap free */

extern s32 BtlStage_IsReady(void);
extern f32 func_00272FA8(void);                                  /* BtlStage_GetInnerRadius */
extern s32 EftWater_GetSurfaceY(f32 *level);

extern s32 StgRigidList_Count(StgRigidNode *head);
extern StgRigidNode *StgRigid_AllocNode(void);

extern Mtx44 D_00344BF0;                                         /* identity matrix */

/* .lit4 constants of this range (values checked against 283E00.lit4.s) */
extern const f32 D_00386D34; /* 0.1 */
extern const f32 D_00386D38; /* 0.0015 */
extern const f32 D_00386D3C; /* 0.1115 */
extern const f32 D_00386D40; /* 0.016676664 (1/60 + 0.00001) */
extern const f32 D_00386D44; /* 0.0015 */

/* Last node of a list, NULL when it is empty. */
StgRigidNode *StgRigidList_Last(StgRigidNode *head) {
    StgRigidNode **link = &head;
    StgRigidNode *last = NULL;

    while (*link != NULL) {
        last = *link;
        link = &last->next;
    }
    return last;
}

/* The active body with this id, NULL when there is none. */
StgRigidNode *StgRigid_Find(s32 id) {
    StgRigidNode *head = gStgRigid->active;
    StgRigidNode **link = &head;
    StgRigidNode *n;

    while (*link != NULL) {
        n = *link;
        if (n->id == id) {
            return n;
        }
        link = &n->next;
    }
    return NULL;
}

/* Keeps the body inside the stage cylinder: x and z scaled back, both angular velocities halved. */
void StgRigid_ClampToStage(RigidBody *body) {
    Vec4 v;
    f32 dist;
    f32 limit;

    v.y = 0.0f;
    v.x = body->pos.x;
    v.z = body->pos.z;
    dist = sqrtf(v.x * v.x + v.z * v.z) + body->prevSphere.radius;
    limit = func_00272FA8();
    if (limit < dist) {
        f32 k = limit / dist;

        body->pos.x *= k;
        body->pos.z *= k;
        body->angVel.x *= 0.5f;
        body->angVel.y *= 0.5f;
        body->angVel.z *= 0.5f;
        body->angVelBody.x *= 0.5f;
        body->angVelBody.y *= 0.5f;
        body->angVelBody.z *= 0.5f;
        Rigid_SyncSpheres(body);
    }
}

/* Start of a frame for every body: remembers the transform, collects nearby triangles, chooses the drag. */
void StgRigidList_BeginFrame(StgRigidNode *head) {
    RigidSphere sphere;
    f32 water;
    StgRigidNode *n;
    StgRigidNode **link;
    s32 hasWater;

    hasWater = EftWater_GetSurfaceY(&water);
    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        Rigid_BeginFrame(&n->body);
        Rigid_SyncSpheres(&n->body);
        if (n->resting) {
            continue;
        }
        if (n->body.user != 0 && BtlStage_IsReady()) {
            ColSphere_Set(&sphere, &n->body.prevSphere.center, n->body.prevSphere.radius + n->body.moved + LIT4(D_00386D34));
            func_0011E320(&sphere, n->body.user);
        }
        n->damp = LIT4(D_00386D38);
        if (BtlStage_IsReady() && hasWater) {
            if (n->body.user != 0 && water < n->body.prevSphere.center.y) {
                n->damp = LIT4(D_00386D3C);
            }
        }
    }
}

/* Sub-step, first pass: world-space centre of mass and collision spheres of every moving body. */
void StgRigidList_UpdateCenters(StgRigidNode *head) {
    StgRigidNode *n;
    StgRigidNode **link;

    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        if (n->resting) {
            continue;
        }
        Rigid_UpdateCenter(&n->body);
        Rigid_SyncSpheres(&n->body);
    }
}

/* Sub-step, second pass: a contact force for every collected triangle the body's sphere touches. */
void StgRigidList_Collide(StgRigidNode *head) {
    Vec4 hit;
    Vec4 d;
    Vec4 point;
    StgRigidNode *n;
    StgRigidNode **link;
    u32 i;

    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        if (!BtlStage_IsReady()) {
            continue;
        }
        if (n->resting) {
            continue;
        }
        if (n->body.user == 0) {
            continue;
        }
        for (i = 0; i < ((StgRigidHits *)n->body.user)->count; i++) {
            if (ColSphere_TestTri(&hit, &n->body.prevSphere, &((StgRigidHits *)n->body.user)->tri[i])) {
                f32 depth;

                func_00312650(&d, &n->body.prevSphere.center, &hit);
                depth = n->body.prevSphere.radius - sqrtf(sceVu0InnerProduct(&d, &d));
                point.x = n->body.prevSphere.center.x + -((StgRigidTri *)((u8 *)n->body.user + 0x10))[i].normal.x * n->body.prevSphere.radius;
                point.y = n->body.prevSphere.center.y + -((StgRigidTri *)((u8 *)n->body.user + 0x10))[i].normal.y * n->body.prevSphere.radius;
                point.z = n->body.prevSphere.center.z + -((StgRigidTri *)((u8 *)n->body.user + 0x10))[i].normal.z * n->body.prevSphere.radius;
                point.w = 1.0f;
                func_00296910(&n->body, &point, &((StgRigidHits *)n->body.user)->tri[i].normal, gStgRigidRestitution,
                              gStgRigidFriction, depth);
            }
        }
    }
}

/* Sub-step, third pass: gravity and drag on every moving body. */
void StgRigidList_AddForces(StgRigidNode *head) {
    StgRigidNode *n;
    StgRigidNode **link;

    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        if (n->resting) {
            continue;
        }
        Rigid_AddGravity(&n->body);
        Rigid_Damp(&n->body, n->damp);
    }
}

/* Sub-step, last pass: integrates every moving body over 1/60 + 0.00001 s. */
void StgRigidList_Step(StgRigidNode *head) {
    StgRigidNode *n;
    StgRigidNode **link;

    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        if (n->resting) {
            continue;
        }
        Rigid_Step(&n->body, D_00386D40);
    }
}

/* End of a frame: stage clamp, then the rest test (only bodies with a hit buffer can come to rest). */
void StgRigidList_EndFrame(StgRigidNode *head) {
    StgRigidNode *n;
    StgRigidNode **link;

    for (link = &head; *link != NULL; link = &n->next) {
        n = *link;
        if (n->resting) {
            continue;
        }
        StgRigid_ClampToStage(&n->body);
        if (n->body.user != 0) {
            n->resting = func_00296F70(&n->body);
        } else {
            n->resting = 0;
        }
    }
}

/* Forgets every body: both lists empty, the pool unused. */
void StgRigid_Reset(void) {
    gStgRigid->used = 0;
    gStgRigid->free = NULL;
    gStgRigid->active = NULL;
}

/* Allocates the pool and numbers its nodes 1..128. */
void StgRigid_Init(void) {
    s32 i;

    gStgRigid = func_0028BAA8(sizeof(StgRigidPool));
    memset(gStgRigid, 0, sizeof(StgRigidPool));
    for (i = 0; i < STG_RIGID_MAX; i++) {
        gStgRigid->nodes[i].id = i + 1;
    }
    StgRigid_Reset();
}

/* Frees the pool. */
void StgRigid_Term(void) {
    func_0028BB60(gStgRigid);
    gStgRigid = NULL;
}

/* New body at `pos`, unrotated and at rest, appended to the active list. Returns its id, -1 when the pool is full. */
s32 StgRigid_Create(Vec4 *pos, f32 radius, s32 user) {
    StgRigidNode *n;
    StgRigidNode *last;

    n = StgRigid_AllocNode();
    if (n == NULL) {
        return -1;
    }
    last = StgRigidList_Last(gStgRigid->active);
    if (last == NULL) {
        gStgRigid->active = n;
        n->prev = NULL;
    } else {
        last->next = n;
        n->prev = last;
    }
    n->next = NULL;
    func_00297228(&n->body, user, radius, gStgRigidDensity);
    Rigid_SetTransform(&n->body, pos, &D_00344BF0);
    Rigid_SyncSpheres(&n->body);
    n->damp = D_00386D44;
    return n->id;
}
