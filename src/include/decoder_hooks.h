#ifndef DECODER_HOOKS_H
#define DECODER_HOOKS_H

#include "config.h"
#include "riscv_insn.h"
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
#ifdef SUPPORT_RV32I
  RV32I_HOOKS_INIT,
#endif
};

#endif // DECODER_HOOKS_H
