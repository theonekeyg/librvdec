#include <gtest/gtest.h>
extern "C" {
#include "riscv_decode.h"
#include "riscv_insn.h"
};

namespace rtype_insns {

// Something wrong with add instruction parse, haven't figured it out yet
TEST(rv32i, rtype_instructions_add) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* add a5,a3,s8 */ 0x018687b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_ADD);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 13); // a3
  EXPECT_EQ(ins.r.rs2, 24); // s8
}

TEST(rv32i, rtype_instructions_sub) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sub a3,t1,a2 */ 0x40c306b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SUB);
  // check registers
  EXPECT_EQ(ins.r.rd, 13); // a3
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_sll) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sll a5,a5,a2 */ 0x00c797b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLL);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_slt) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slt a5,a4,a5 */ 0x00f727b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLT);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 14); // a4
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_sltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sltu a5,t1,t3 */ 0x01c337b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLTU);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 28); // t3
}

TEST(rv32i, rtype_instructions_xor) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* xor s7,s7,a5 */ 0x00fbcbb3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_XOR);
  // check registers
  EXPECT_EQ(ins.r.rd, 23); // s7
  EXPECT_EQ(ins.r.rs1, 23); // s7
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_srl) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srl t1,a2,a6 */ 0x01065333);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SRL);
  // check registers
  EXPECT_EQ(ins.r.rd, 6); // t1
  EXPECT_EQ(ins.r.rs1, 12); // a2
  EXPECT_EQ(ins.r.rs2, 16); // a6
}

TEST(rv32i, rtype_instructions_sra) {
  // @@@
}

TEST(rv32i, rtype_instructions_or) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* or a5,a5,s3 */ 0x0137e7b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_OR);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 19); // s3
}

TEST(rv32i, rtype_instructions_and) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* and s4,s4,a5 */ 0x00fa7a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_AND);
  // check registers
  EXPECT_EQ(ins.r.rd, 20); // s4
  EXPECT_EQ(ins.r.rs1, 20); // s4
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

} // namespace rtype_insns

namespace itype_insns {

TEST(rv32i, itype_instructions_jalr) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* jalr -94(a3) */ 0xfa2680e7);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_JALR);
  EXPECT_EQ(ins.i.imm, -94);
  // check registers
  EXPECT_EQ(ins.i.rs1, 13); // a3
}

TEST(rv32i, itype_instructions_lb) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lb s7,0(s8) */ 0x000c0b83);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LB);
  EXPECT_EQ(ins.i.imm, 0);
  // check registers
  EXPECT_EQ(ins.i.rd, 23); // s7
  EXPECT_EQ(ins.i.rs1, 24); // s8
}

TEST(rv32i, itype_instructions_lh) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lh a5,-210(s0) */ 0xf2e41783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LH);
  EXPECT_EQ(ins.i.imm, -210);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
}

TEST(rv32i, itype_instructions_lw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lw a5,-44(s0) */ 0xfd442783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LW);
  EXPECT_EQ(ins.i.imm, -44);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
}

TEST(rv32i, itype_instructions_lbu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lbu a5,0(a5) */ 0x0007c783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LBU);
  EXPECT_EQ(ins.i.imm, 0);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 15); // a5
}

TEST(rv32i, itype_instructions_lhu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lhu a5,2(a5) */ 0x0027d783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LHU);
  EXPECT_EQ(ins.i.imm, 2);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 15); // a5
}

TEST(rv32i, itype_instructions_addi) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lhu a5,s0,-200 */ 0xf3840793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_ADDI);
  EXPECT_EQ(ins.i.imm, -200);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
}

TEST(rv32i, itype_instructions_slti) {
  // @@@
}

TEST(rv32i, itype_instructions_sltiu) {
  // @@@
}

TEST(rv32i, itype_instructions_xori) {
  // @@@
}

TEST(rv32i, itype_instructions_ori) {
  // @@@
}

TEST(rv32i, itype_instructions_andi) {
  // @@@
}

TEST(rv32i, itype_instructions_slli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slli a5,a3,0x20 */ 0x02069793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SLLI);
  EXPECT_EQ(ins.i.imm, 0x20);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 13); // a3
}

TEST(rv32i, itype_instructions_srli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srli a5,a4,0x1e */ 0x01e75793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRLI);
  EXPECT_EQ(ins.i.imm, 0x1e);
  // check registers
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 14); // a4
}

TEST(rv32i, itype_instructions_srai) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srai s3,s3,0x3f */ 0x43f9d993);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRAI);
  EXPECT_EQ(ins.i.imm, 0x3f);
  // check registers
  EXPECT_EQ(ins.i.rd, 19); // s3
  EXPECT_EQ(ins.i.rs1, 19); // s3
}

TEST(rv32i, itype_instructions_fence) {
  // @@@
}

} // namespace itype_insns
