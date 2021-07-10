#include <gtest/gtest.h>
extern "C" {
#include "riscv_decode.h"
#include "riscv_insn.h"
};

namespace rtype_insns {

// Something wrong with add instruction parse, haven't figured it out yet
TEST(rv32i, rtype_instructions_add) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x018687b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_ADD);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 13); // a3
  EXPECT_EQ(ins.r.rs2, 24); // s8
}

TEST(rv32i, rtype_instructions_sub) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x40c306b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SUB);
  // check registers
  EXPECT_EQ(ins.r.rd, 13); // a3
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_sll) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x00c797b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLL);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_slt) {
  // @@@
}

TEST(rv32i, rtype_instructions_sltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x01c337b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLTU);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 28); // t3
}

TEST(rv32i, rtype_instructions_xor) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x00fbcbb3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_XOR);
  // check registers
  EXPECT_EQ(ins.r.rd, 23); // s7
  EXPECT_EQ(ins.r.rs1, 23); // s7
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_srl) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x01065333);
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
  riscv_decode(&ins, 0x0137e7b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_OR);
  // check registers
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 19); // s3
}

TEST(rv32i, rtype_instructions_and) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x00fa7a33);
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
  riscv_decode(&ins, 0xfa2680e7);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_JALR);
  EXPECT_EQ(ins.i.imm, -94);
  // check registers
  EXPECT_EQ(ins.i.rs1, 13); // a3
}

TEST(rv32i, itype_instructions_lb) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x000c0b83);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LB);
  EXPECT_EQ(ins.i.imm, 0);
  // check registers
  EXPECT_EQ(ins.i.rd, 23); // s7
  EXPECT_EQ(ins.i.rs1, 24); // s8
}

TEST(rv32i, itype_instructions_lb) {
  struct riscv_insn ins;
  riscv_decode(&ins, 0x000c0b83);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LB);
  EXPECT_EQ(ins.i.imm, 0);
  // check registers
  EXPECT_EQ(ins.i.rd, 23); // s7
  EXPECT_EQ(ins.i.rs1, 24); // s8
}

} // namespace itype_insns
