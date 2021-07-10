#include <limits.h>

#include "riscv_insn.h"

static const char *reg_names[] = {
  "zero", "ra", "sp", "gp", "tp", "t0",
  "t1", "t2", "s0/fp", "s1", "a0", "a1",
  "a2", "a3", "a4", "a5", "a6", "a7", "s2",
  "s3", "s4", "s5", "s6", "s7", "s8", "s9",
  "s10", "s11", "t3", "t4", "t5", "t6"
};

static const char *freg_names[] = {
  "ft0", "ft1", "ft2", "ft3", "ft4", "ft5",
  "ft6", "ft7", "fs0", "fs1", "fa0", "fa1",
  "fa2", "fa3", "fa4", "fa5", "fa6", "fa7",
  "fs2", "fs3", "fs4", "fs5", "fs6", "fs7",
  "fs8", "fs9", "fs10", "fs11", "ft8", "ft9",
  "ft10", "ft11"
};


void riscv_decode_r(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
  insn->type = INSN_R;
  insn->kind = kind;
  insn->r.funct7 = (repr >> 25) & 0b1111111;
  insn->r.rs2 = (repr >> 20) & 0b11111;
  insn->r.rs1 = (repr >> 15) & 0b11111;
  insn->r.funct3 = (repr >> 12) & 0b111;
  insn->r.rd = (repr >> 7) & 0b11111;
  insn->r.opcode = opcode;
}

void riscv_decode_i(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
  insn->type = INSN_I;
  insn->kind = kind;
  insn->i.imm = (repr >> 20) & 0b111111111111;
  insn->i.rs1 = (repr >> 15) & 0b11111;
  insn->i.funct3 = (repr >> 12) & 0b111;
  insn->i.rd = (repr >> 7) & 0b11111;
  insn->i.opcode = opcode;
}

void riscv_decode_i_shamt(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode, int shamt_bits_size) {
  insn->type = INSN_I;
  insn->kind = kind;
  // Keep only shamt bits
  insn->i.imm = (repr >> 20) & (~(UINT_MAX << (shamt_bits_size+1)));
  insn->i.rs1 = (repr >> 15) & 0b11111;
  insn->i.funct3 = (repr >> 12) & 0b111;
  insn->i.rd = (repr >> 7) & 0b11111;
  insn->i.opcode = opcode;
}

void riscv_decode_s(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
  insn->type = INSN_S;
  insn->kind = kind;
  insn->s.imm = ((repr >> 7) & 0b11111) | ((repr >> 25) & 0b1111111);
  insn->s.rs2 = (repr >> 20) & 0b11111;
  insn->s.rs1 = (repr >> 15) & 0b11111;
  insn->s.funct3 = (repr >> 12) & 0b111;
  insn->s.opcode = opcode;
}

void riscv_decode_b(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
  insn->type = INSN_B;
  insn->kind = kind;
  int32_t imm12_105 = (repr >> 25) & 0b1111111;
  int32_t imm41_11 = (repr >> 7) & 0b11111;
  insn->b.imm = ((imm41_11 >> 1) & 0b1111) | ((imm12_105 & 0b111111) << 4)
              | ((imm41_11 & 1) << 10) | (((imm12_105 >> 6) & 1) << 11);
  insn->b.rs2 = (repr >> 20) & 0b11111;
  insn->b.rs1 = (repr >> 15) & 0b11111;
  insn->b.funct3 = (repr >> 12) & 0b111;
  insn->b.opcode = opcode;
}

void riscv_decode_u(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
}

void riscv_decode_j(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode) {
}

void riscv_decode_fence(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  insn->type = INSN_I;
  insn->kind = KIND_FENCE;
  insn->fence.fm = (repr >> 28) & 0b1111;
  insn->fence.pred = (repr >> 24) & 0b1111;
  insn->fence.succ = (repr >> 20) & 0b1111;
  insn->fence.rs1 = (repr >> 15) & 0b11111;
  insn->fence.funct3 = (repr >> 12) & 0b111;
  insn->fence.rd = (repr >> 7) & 0b11111;
  insn->fence.opcode = opcode;
}
