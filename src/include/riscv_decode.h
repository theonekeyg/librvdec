#ifndef RISCV_DECODE_H
#define RISCV_DECODE_H

#include <stdint.h>
#include "riscv_insn.h"

int riscv_decode(struct riscv_insn *insn, uint32_t repr);
void riscv_decode_r(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);
void riscv_decode_i(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);
void riscv_decode_s(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);
void riscv_decode_b(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);
void riscv_decode_u(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);
void riscv_decode_j(struct riscv_insn *insn, int kind, uint32_t repr, uint32_t opcode);

int riscv_decode_rv32i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_b(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_u(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv32i_j(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

int riscv_decode_rv64i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_b(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_u(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);
int riscv_decode_rv64i_j(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

#endif // RISCV_DECODE_H
