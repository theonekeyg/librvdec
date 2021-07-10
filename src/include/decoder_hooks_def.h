#ifndef DECODER_HOOKS_DEF_H
#define DECODER_HOOKS_DEF_H

#include "riscv_decode.h"

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
  riscv_decode_rv64i_b, \
  riscv_decode_rv64i_u, \
  riscv_decode_rv64i_j \
}

#endif // DECODER_HOOKS_DEF_H
