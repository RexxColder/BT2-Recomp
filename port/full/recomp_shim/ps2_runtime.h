// Shim minimo de ps2_runtime.h para el relleno temporal (docs/agents/FALLBACK_SPEC.md): lo que usa el C++ generado por
// PS2Recomp, sin el runtime real. rdram == nullptr (identidad: direccion PS2 == direccion del host).
#ifndef PS2_RUNTIME_H
#define PS2_RUNTIME_H
#include <cstring>
#include <cstdint>
#include <cmath>
#include <immintrin.h>
#include <smmintrin.h>
constexpr uint32_t PS2_RAM_SIZE = 32u * 1024u * 1024u;
constexpr uint32_t PS2_RAM_MASK = PS2_RAM_SIZE - 1u;
enum PS2Exception { EXCEPTION_TLB_REFILL = 0x02, EXCEPTION_ADDRESS_ERROR_LOAD = 0x04, EXCEPTION_ADDRESS_ERROR_STORE = 0x05,
    EXCEPTION_SYSCALL = 0x08, EXCEPTION_BREAKPOINT = 0x09, EXCEPTION_RESERVED_INSTRUCTION = 0x0A,
    EXCEPTION_INTEGER_OVERFLOW = 0x0C, EXCEPTION_TRAP = 0x0D };
// PS2 CPU context (R5900)
struct alignas(16) R5900Context
{
    // General Purpose Registers (128-bit)
    __m128i r[32]; // Main registers

    // Control registers
    uint32_t pc;         // Program counter
    uint64_t insn_count; // Instruction counter
    uint64_t hi, lo;     // HI/LO registers for mult/div results
    uint64_t hi1, lo1;   // Secondary HI/LO registers for MULT1/DIV1
    uint32_t sa;         // Shift amount register

    // VU0 registers (when used in macro mode)
    __m128 vu0_vf[32];        // VU0 vector float registers
    uint16_t vi[16];          // VU0 vector integer registers
    float vu0_q;              // VU0 Q register (quotient)
    float vu0_p;              // VU0 P register (EFU result)
    float vu0_i;              // VU0 I register (integer value)
    __m128 vu0_r;             // VU0 R register
    __m128 vu0_acc;           // VU0 ACC accumulator register
    uint16_t vu0_status;      // VU0 status register
    uint32_t vu0_mac_flags;   // VU0 MAC flags
    uint32_t vu0_clip_flags;  // VU0 clipping flags
    uint32_t vu0_clip_flags2; // VU0 clipping flags
    uint32_t vu0_cmsar0;      // VU0 microprogram start address
    uint32_t vu0_cmsar1;      // VU0 microprogram start address
    uint32_t vu0_cmsar2;      // VU0 microprogram start address
    uint32_t vu0_cmsar3;      // VU0 microprogram start address
    uint32_t vu0_vpu_stat;
    uint32_t vu0_vpu_stat2; // extra VPU status (used by CR_VPU_STAT2)
    uint32_t vu0_vpu_stat3; // extra VPU status 3
    uint32_t vu0_vpu_stat4; // extra VPU status 4
    uint32_t vu0_tpc;       // TPC (VU0 PC)
    uint32_t vu0_tpc2;      // second TPC
    uint32_t vu0_fbrst;     // VIF/VU reset register
    uint32_t vu0_fbrst2;    // FBRST2
    uint32_t vu0_fbrst3;    // FBRST3
    uint32_t vu0_fbrst4;    // FBRST4
    uint32_t vu0_itop;
    uint32_t vu0_top;
    uint32_t vu0_info;
    uint32_t vu0_xitop; // VU0 XITOP - input ITOP for VIF/VU sync
    uint32_t vu0_pc;

    float vu0_cf[4]; // VU0 FMAC control floating-point registers

    // COP0 System control registers
    uint32_t cop0_index;
    uint32_t cop0_random;
    uint32_t cop0_entrylo0;
    uint32_t cop0_entrylo1;
    uint32_t cop0_context;
    uint32_t cop0_pagemask;
    uint32_t cop0_wired;
    uint32_t cop0_badvaddr;
    uint32_t cop0_count;
    uint32_t cop0_entryhi;
    uint32_t cop0_compare;
    uint32_t cop0_status;
    uint32_t cop0_cause;
    uint32_t cop0_epc;
    uint32_t cop0_prid;
    uint32_t cop0_config;
    uint32_t cop0_badpaddr;
    uint32_t cop0_debug;
    uint32_t cop0_perf;
    uint32_t cop0_taglo;
    uint32_t cop0_taghi;
    uint32_t cop0_errorepc;

    // LL/SC reservation state (not part of COP0 Status bits).
    uint32_t llbit;
    uint32_t lladdr;

    // Delay slot state tracking
    bool in_delay_slot;
    uint32_t branch_pc;

    // COP2 control registers (VU0 integer + control)
    uint32_t cop2_ccr[32];

    // FPU registers (COP1)
    float f[32];
    float f_acc;    // FPU accumulator
    uint32_t fcr31; // Control/status register

    R5900Context()
    {
        std::memset(this, 0, sizeof(*this));

        // Initialize VU0 registers
        vu0_q = 1.0f; // Q register usually initialized to 1.0

        // Reset COP0 registers
        cop0_random = 47; // Start at maximum value
        // Status as the EE kernel leaves it at handoff. IE (bit 0) and EIE
        // (bit 16) are separate enables and guest code reads both; libkernel's
        // StartThread refuses to run while IE is clear.
        cop0_status = 0x00010001; // EIE | IE
        cop0_prid = 0x00002e20; // CPU ID for R5900

        in_delay_slot = false;
        branch_pc = 0;
    }

    ~R5900Context() = default;
};

inline uint32_t getRegU32(const R5900Context *ctx, int reg)
{
    // Check if reg is valid (0-31)
    if (reg < 0 || reg > 31)
        return 0;
    if (reg == 0)
        return 0;
    return static_cast<uint32_t>(_mm_extract_epi32(ctx->r[reg], 0));
}

inline void setReturnU32(R5900Context *ctx, uint32_t value)
{
    // R5900 sign-extends 32-bit results into 64-bit GPR, even for unsigned values.
    ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(static_cast<int32_t>(value))); // $v0
}

inline void setReturnS32(R5900Context *ctx, int32_t value)
{
    // Signed 32-bit return should be sign-extended when observed as 64-bit.
    ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(value)); // $v0
}

inline void setReturnU64(R5900Context *ctx, uint64_t value)
{
    // Keep both conventions: full 64-bit value in $v0 and high 32-bit in $v1.
    ctx->r[2] = _mm_set_epi64x(0, static_cast<int64_t>(value));
    ctx->r[3] = _mm_set_epi64x(0, static_cast<int64_t>(static_cast<uint32_t>(value >> 32)));
}


inline void ps2TraceGuestWrite(uint8_t *, uint32_t, uint32_t, uint64_t, uint64_t, const char *, const R5900Context *) {}
inline void ps2TraceGuestRangeWrite(uint8_t *, uint32_t, uint32_t, const char *, const R5900Context *) {}

class PS2Runtime
{
public:
    using RecompiledFunction = void (*)(uint8_t *, R5900Context *, PS2Runtime *);
    enum class GuestBranchKind { DirectJump, DirectCall, IndirectJump, IndirectCall, Return };
    bool dispatchGuestBranch(uint8_t *rdram, R5900Context *ctx, uint32_t targetPc, uint32_t sourcePc, uint32_t fallthroughPc,
                             GuestBranchKind kind, const char *debugName);
    void SignalException(R5900Context *ctx, PS2Exception exception);
    void handleSyscall(uint8_t *rdram, R5900Context *ctx);
    void handleSyscall(uint8_t *rdram, R5900Context *ctx, uint32_t encodedSyscallId);
    void handleBreak(uint8_t *rdram, R5900Context *ctx);
    void clearLLBit(R5900Context *ctx);
    bool eeCheckpointDue(uint32_t cycles = 32u) noexcept;
    uint8_t Load8(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr);
    uint16_t Load16(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr);
    uint32_t Load32(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr);
    uint64_t Load64(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr);
    __m128i Load128(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr);
    void Store8(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr, uint8_t value);
    void Store16(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr, uint16_t value);
    void Store32(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr, uint32_t value);
    void Store64(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr, uint64_t value);
    void Store128(uint8_t *rdram, R5900Context *ctx, uint32_t vaddr, __m128i value);
    // Registros de hardware (0x1xxxxxxx) y scratchpad (0x7xxxxxxx): no caben en la mascara de 32 MB de la RAM.
    static inline bool isSpecialAddress(uint32_t addr) { uint32_t t = addr >> 28; return t == 1u || t == 7u; }
};
#endif
