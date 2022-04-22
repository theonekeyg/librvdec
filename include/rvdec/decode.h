#ifndef RISCV_DECODE_H
#define RISCV_DECODE_H

#include <stdint.h>
#include <rvdec/instruction.h>

#ifdef __cplusplus
extern "C" {
#endif

int riscv_decode(struct riscv_insn *insn, uint32_t repr);

void riscv_decode_r(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_i(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_i_shamt(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode, int shamt_bits_size);
void riscv_decode_s(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_b(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_u(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_j(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
int riscv_try_decode_fence(struct riscv_insn *insn, uint32_t repr,
    uint32_t opcode);

int riscv_decode_rv32i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_b(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_u(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_j(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

int riscv_decode_rv64i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

int riscv_decode_rv32m_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

int riscv_decode_rv64m_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

#ifdef SUPPORT_COMPRESSED

int rvc_decode(struct riscv_insn *insn, uint32_t repr);
int rvc_decode_cr_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ci_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_css_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ciw_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cl_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cs_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ca_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cb_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cj_rv32(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

int rvc_decode_cr_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ci_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_css_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ciw_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cl_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cs_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_ca_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cb_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int rvc_decode_cj_rv64(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

#endif // SUPPORT_COMPRESSED

#ifdef __cplusplus
}
#endif

#endif // RISCV_DECODE_H
