#ifndef DECODER_HOOKS_DEF_H
#define DECODER_HOOKS_DEF_H

#include "riscv_decode.h"

static int riscv_hook_nop(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  return 0;
}

#define RV32I_HOOKS_INIT { \
  riscv_decode_rv32i_r, \
  riscv_decode_rv32i_i, \
  riscv_decode_rv32i_s, \
  riscv_decode_rv32i_b, \
  riscv_decode_rv32i_u, \
  riscv_decode_rv32i_j \
}

#define RV64I_HOOKS_INIT { \
  riscv_decode_rv64i_r, \
  riscv_decode_rv64i_i, \
  riscv_decode_rv64i_s, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop \
}

#endif // DECODER_HOOKS_DEF_H
