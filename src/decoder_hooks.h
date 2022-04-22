#ifndef _DECODER_HOOKS_H
#define _DECODER_HOOKS_H

#include <rvdec/instruction.h>
#include <rvdec/decode.h>

#include "decoder_hooks_def.h"

struct decoder_hooks {
  /* Hooks must return 1 if instruction is identified, parsed and stored to `insn`
   * and 0 if it's undefined */
  int (*riscv_decode_r)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*riscv_decode_i)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*riscv_decode_s)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*riscv_decode_b)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*riscv_decode_u)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*riscv_decode_j)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
};

struct decoder_hooks decoder_hooks[] = {
#ifdef SUPPORT_RV64I
  RV64I_HOOKS_INIT,
#endif

#if defined(SUPPORT_RV32I) || defined(SUPPORT_RV64I)
  RV32I_HOOKS_INIT,
#endif

#ifdef SUPPORT_RV64M
  RV64M_HOOKS_INIT,
#endif

#if defined(SUPPORT_RV32M) || defined(SUPPORT_RV64M)
  RV32M_HOOKS_INIT,
#endif
};

#ifdef SUPPORT_COMPRESSED

// Hooks for 16-bit compressed instructions
struct decoder_hooks16 {
  /* Hooks must return 1 if instruction is identified, parsed and stored to `insn`
   * and 0 if it's undefined */
  int (*rvc_decode_cr) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_ci) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_css)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_ciw)(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_cl) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_cs) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_ca) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_cb) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
  int (*rvc_decode_cj) (struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
};

struct decoder_hooks16 decoder_hooks16[] = {
  {
    rvc_decode_cr,
    rvc_decode_ci,
    rvc_decode_css,
    rvc_decode_ciw,
    rvc_decode_cl,
    rvc_decode_cs,
    rvc_decode_ca,
    rvc_decode_cb,
    rvc_decode_cj
  }
};

#endif // SUPPORT_COMPRESSED

#endif // _DECODER_HOOKS_H
