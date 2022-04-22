#ifndef DECODER_HOOKS_DEF_H
#define DECODER_HOOKS_DEF_H

#include <rvdec/decode.h>

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

#define RV32M_HOOKS_INIT { \
  riscv_decode_rv32m_r, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop \
}

#define RV64M_HOOKS_INIT { \
  riscv_decode_rv64m_r, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop, \
  riscv_hook_nop \
}

#define RVC_HOOKS_INIT_RV32 { \
    rvc_decode_cr_rv32, \
    rvc_decode_ci_rv32, \
    rvc_decode_css_rv32, \
    rvc_decode_ciw_rv32, \
    rvc_decode_cl_rv32, \
    rvc_decode_cs_rv32, \
    rvc_decode_ca_rv32, \
    rvc_decode_cb_rv32, \
    rvc_decode_cj_rv32 \
}

#define RVC_HOOKS_INIT_RV64 { \
    riscv_hook_nop, \
    rvc_decode_ci_rv64, \
    rvc_decode_css_rv64, \
    riscv_hook_nop, \
    rvc_decode_cl_rv64, \
    rvc_decode_cs_rv64, \
    rvc_decode_ca_rv64, \
    riscv_hook_nop, \
    rvc_decode_cj_rv64 \
}

#endif // DECODER_HOOKS_DEF_H
