#ifndef RISCV_DECODE_H
#define RISCV_DECODE_H

#include <stdint.h>
#include <rvdec/instruction.h>

#ifdef __cplusplus
extern "C" {
#endif

int riscv_decode(struct riscv_insn *insn, uint32_t repr);

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

#ifdef __cplusplus
}
#endif

#endif // RISCV_DECODE_H
