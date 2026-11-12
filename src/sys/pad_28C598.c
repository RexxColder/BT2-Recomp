#include "common.h"
#include "sys/pad.h"

extern void *memset(void *dst, s32 value, u32 size);
extern f32 sqrtf(f32 x);

extern s32 sceDbcInit(void);
extern s32 scePad2Init(s32 mode);
extern s32 scePad2CreateSocket(Pad2SocketParam *param, void *work);
extern s32 scePad2Read(s32 socket, u8 *data);
extern s32 scePad2GetButtonProfile(s32 socket, void *profile);
extern s32 scePad2GetState(s32 socket);
extern s32 sceVibGetProfile(s32 socket, u8 *profile);
extern s32 sceVibSetActParam(s32 socket, s32 profileSize, u8 *profile, s32 dataSize, void *data);

extern u32 Pad_CalcRepeat(u32 held, u32 pressed, s32 *timer, u32 *last, s32 delay, s32 interval);
extern void Pad_UpdateGameButtons(s32 pad);

/* Starts libdbc/libpad2, opens one socket per controller port and sets the default key repeat. */
void Pad_Init(void);

/* Empty. */
void Pad_Stub0(void);

/* Empty. */
void Pad_Stub1(void);

/* Empty. */
void Pad_Stub2(void);

/* Empty. */
void Pad_Stub3(void);

/* Once per frame: polls both controllers, builds the stick values and the held/pressed/repeat words, sends vibration. */
void Pad_Update(void);

/* True when any button of mask is down. */
s32 Pad_IsHeld(s32 pad, u32 mask);

/* True when any button of mask went down this frame. */
s32 Pad_IsPressed(s32 pad, u32 mask);

/* True when any button of mask went down or auto-repeated this frame. */
s32 Pad_IsRepeat(s32 pad, u32 mask);

/* Copies the left and right stick vectors (x, y in -1..1). */
void Pad_GetSticks(s32 pad, f32 *left, f32 *right);

/* Adds to this frame's vibration request: large motor power (summed, capped at 1) and the small motor flag. */
void Pad_AddVibration(s32 pad, s32 small, f32 power);

/* Reads the controller's actuator profile. */
s32 Pad_GetVibProfile(s32 pad);

/* Sends the accumulated vibration request to the controller and clears it. */
void Pad_SendActuator(s32 pad);

/* Puts a port into the "nothing connected" state: no buttons, centred sticks. */
void Pad_Reset(s32 pad);

/* True when the button profile is F9 FF 00 00: every digital button except L3/R3 and no analog input.
   (The four byte tests compile to one masked 64-bit compare.) */
s32 Pad_IsDigitalOnly(s32 pad);

/* True when bits and mask have a bit in common. */
s32 Pad_TestMask(s32 pad, u32 bits, u32 mask);

/* Converts a raw stick byte to -1..1 with a dead zone around the centre (127.5). */
f32 Pad_StickToFloat(u8 raw, s32 deadzone) {
    f32 value = (f32)raw - 127.5f;

    if (0.0f < value) {
        value -= (f32)deadzone;
        if (value < 0.0f) {
            value = 0.0f;
        }
    } else {
        value += (f32)deadzone;
        if (0.0f < value) {
            value = 0.0f;
        }
    }
    return value / (127.5f - (f32)deadzone);
}
