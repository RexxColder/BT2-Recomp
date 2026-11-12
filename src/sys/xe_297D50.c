#define func_002967C0 sceSdRemote  /* fix_targets */ /* the original uses 0x314dc0 here */
/*
 * Sound effects: EE side of the game's own IOP driver SOUNDS.IRX.   0x123F48..0x125568
 *
 * Three layers, in address order:
 *   0x123F48..0x1245F0  the RPC stubs (Snd_Rpc*, Snd_Queue*, Snd_SpuTransfer*)
 *   0x1245F0..0x1253F8  the bank manager and the calls the game uses (Snd_*)
 *   0x1253F8..0x125568  readers for the Sony HD header inside a bank file (SndHd_*)
 *
 * What a port has to replace
 * --------------------------
 * RPC link. One client bound to server id 0x2000004 (Snd_RpcInit retries the bind until SOUNDS.IRX answers). Every
 * command goes through Snd_RpcCall(fno, gSndRpcBuf, size): sceSifCallRpc with mode 0, i.e. the caller is blocked until
 * the IOP has run the command; 0x40 bytes come back and the first word is the result. No command is sent
 * asynchronously and none has an end callback. Commands (payload = little-endian s32 words unless noted):
 *     0x0  INIT        4 bytes, unused             once, from Snd_RpcInit
 *     0x1  TERM        4 bytes, unused             Snd_Term (never called)
 *     0x2  RESET       4 bytes, unused             Snd_Reset: stop everything
 *     0x3  SET_BANK    mask, spuAddr, hdIopAddr, seqIopAddr      a bank's data is in place
 *     0x4  FREE_BANK   mask
 *     0x5  SET_MONO    0 = stereo, 1 = mono
 *     0x6  SET_PAUSE   mask, on                    pause / resume the voices of those banks
 *     0x7  SET_VOLUME  mask, volume 0..0x7F        only ever sent as (0xFF, 0x7F) at start-up
 *     0x8  ?           one word                    never sent
 *     0x9  TICK        4 bytes, unused             every frame, before the queue
 *     0xA  STOP_BANK   mask                        stop the voices of those banks
 *     0xB  ?           two words                   never sent
 *     0xC  ?           one word                    never sent
 *     0xD  QUEUE       SndQueue, 0x184 bytes       every frame that queued something
 *     0xE  ?           4 bytes, unused             never sent
 *     0xF  FIGHTERS    s16 count, s16 id[count], 0x18 bytes sent      every battle frame
 * "mask" is a bank bit mask; the driver takes several bits at once in 6, 7 and 0xA (0x3C, 0xFF).
 *
 * Per-frame queue. Playing and stopping a sound never talks to the IOP directly: Snd_PlaySeEx / Snd_StopSe /
 * Snd_StopHandle append a 12-byte SndCmd to gSndRpc->queue (32 at most; a 33rd is dropped and the play returns -1).
 * Snd_Update sends TICK, then the whole queue (count + 32 entries) as one QUEUE command, then clears it. So a sound
 * starts on the next Snd_Update and at most 32 voice commands fit in a frame. A PLAY entry carries the bank mask, the
 * sample number, volume 0..0x7F, pan 0..0x7F (0x40 centre), pitch in cents (-1200..1200), the sample's loop flag and
 * a 16-bit handle. The handle is made up here (gSndSerial, +1 per PLAY, wraps at 0x10000) and is what Snd_PlaySeEx
 * returns; STOP_HANDLE names a voice by it.
 *
 * Banks. Eight slots; a bank is always named by the mask 1 << slot (Snd_BankIndex gives the slot of the lowest set
 * bit). A bank file is { u32 ?, bodyOfs, hdOfs, seqOfs, endOfs } followed by three sections:
 *     body  the ADPCM samples; uploaded to SPU2 RAM (SPU heap SpuHeap_Alloc, addresses 0x5010 up)
 *     hd    a Sony HD header (SCEIVers / SCEIHead ...); copied to an IOP heap block
 *     seq   a third table, contents not looked at here (the name is a guess); copied to an IOP heap block
 * Snd_LoadBank allocates the three blocks, copies hd and seq with sceSifSetDma (Dma_SendToIop), then either uploads
 * the body at once (sync: EE -> the 0xA4800-byte IOP staging buffer -> sceSdVoiceTrans to the SPU, wait) or marks the
 * bank pending, and finally sends SET_BANK. A pending bank refuses to play; Snd_Update uploads pending bodies one bank
 * at a time and polls sceSdVoiceTransStatus each frame. Slots 3, 4 and 5 (masks 8, 0x10, 0x20) get fixed-size blocks
 * (SPU 0x13800 / 0x8F000 / 0x8F000 bytes) so that Snd_ReloadBank can swap their contents without reallocating.
 * Slot 0 (mask 1) is the common bank, file 0x14B, loaded at boot.
 * The only thing the EE reads from the header is the vag-info chunk: the highest sample number and each sample's
 * loop flag. So a sound "id" is the sample (VAG) index inside its bank, 0..255.
 *
 * Snd_PlaySe(mask, id) = Snd_PlaySeEx(mask, id, 0x40, 0, 0).
 * Snd_PlaySeEx(mask, id, volume, pan, pitch):
 *     volume  0..0x7F; sent as volume * gSndBankVolume[slot] * save->seVolume / 0x480 clamped to 0..0x7F
 *             (gSndBankVolume = { 0xD8, 0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0 }; seVolume 0..9, so 0x480 = 128 * 9)
 *     pan     -0x40..0x3F, 0 = centre; sent as pan + 0x40 clamped to 0..0x7F
 *     pitch   1/64 octave steps; sent as (s32)(pitch * 18.75f) cents clamped to -1200..1200
 *     returns the handle, or -1: bank not loaded, bank still pending, bank 0x10 / 0x20 while BtlScript_IsSlotBusy(0 / 1, 0)
 *             is set (per-side mute), queue full, or id / volume / pan / pitch out of range.
 *
 * Verified by the matching C: everything above about what the EE does. Inferred: the meaning of each command on the
 * IOP side (from its arguments and callers; SOUNDS.IRX was not read), the Sony HD layout (the offsets used match it)
 * and the names sceSdRemote / sceSdRemoteCallbackInit / sceSifCheckStatRpc / sceSifAllocIopHeap for the callees.
 */
#include "common.h"
#include "sys/snd.h"
#include "sys/adx.h"
#include "sys/dma.h"
#include "sys/file.h"
#include "sys/heap.h"
#include "sys/save.h"

extern void *memset(void *dst, s32 value, u32 size);
extern void FlushCache(s32 mode);
extern void sceSifInitRpc(s32 mode);
extern s32 sceSifBindRpc(SndSifClient *client, s32 id, s32 mode);
extern s32 sceSifCallRpc(SndSifClient *client, s32 fno, s32 mode, void *send, s32 sendSize, void *recv, s32 recvSize,
                         void *endFunc, void *endParam);
extern s32 func_002B4AF0(SndSifClient *client); /* sceSifCheckStatRpc */
extern s32 sceSdRemoteInit(void);
extern s32 func_00296B48(s32 priority);          /* sceSdRemoteCallbackInit */
extern s32 func_002967C0(s32 block, s32 cmd, ...); /* sceSdRemote */

extern void *IopHeap_Alloc(s32 size);  /* sceSifAllocIopHeap wrapper */
extern void IopHeap_Free(void *addr); /* sceSifFreeIopHeap wrapper */
extern void SpuHeap_Init(void);       /* SPU RAM heap: init (0x5010..0x1F0FD0 + 0x5010) */
extern s32 SpuHeap_Alloc(s32 size);    /* SPU RAM heap: alloc, returns the SPU address */
extern void SpuHeap_Free(s32 addr);   /* SPU RAM heap: free */
extern s32 SpuHeap_GetFreeSize(void);        /* SPU RAM heap: bytes in use */

extern s32 BtlScript_IsSlotBusy(s32 side, s32 idx);
extern s32 BtlCharApi_GetSoundCount(s32 side);
extern void BtlCharApi_GetSound(s32 side, s32 idx, s32 *id, s32 *a3, s32 *a4);


/* Polls the SPU upload: sceSdRemote(1, rSdVoiceTransStatus, core 1, check); 1 = finished. */
s32 Snd_SpuTransferCheck(void) {
    return func_002967C0(1, 0x80F0, 1, 0);
}
