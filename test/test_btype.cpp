#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

namespace btype_insns {

TEST(rv32i, btype_instructions_beq) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 142c2: beq a5,a3,142b0 */ 0xfed787e3);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BEQ);
  EXPECT_EQ(ins.b.imm, (0x142b0 - 0x142c2) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_a5);
  EXPECT_EQ(ins.b.rs2, RVREG_a3);
}

TEST(rv32i, btype_instructions_bne) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1437a: bne a3,a5,142ce */ 0xf4f69ae3);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BNE);
  EXPECT_EQ(ins.b.imm, (0x142ce - 0x1437a) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_a3);
  EXPECT_EQ(ins.b.rs2, RVREG_a5);
}

TEST(rv32i, btype_instructions_blt) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1ca0: blt a4,a3,1d38 */ 0x08d74c63);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BLT);
  EXPECT_EQ(ins.b.imm, (0x1d38 - 0x1ca0) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_a4);
  EXPECT_EQ(ins.b.rs2, RVREG_a3);
}

TEST(rv32i, btype_instructions_bge) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 105e6: bge s5,s3,105ec */ 0x013ad363);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BGE);
  EXPECT_EQ(ins.b.imm, (0x105ec - 0x105e6) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_s5);
  EXPECT_EQ(ins.b.rs2, RVREG_s3);
}

TEST(rv32i, btype_instructions_bltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 11400: bltu a5,s8,11822 */ 0x4387e163);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BLTU);
  EXPECT_EQ(ins.b.imm, (0x11822 - 0x11400) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_a5);
  EXPECT_EQ(ins.b.rs2, RVREG_s8);
}

TEST(rv32i, btype_instructions_bgeu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1295c: bltu s7,a5,12972 */ 0x00fbfb63);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BGEU);
  EXPECT_EQ(ins.b.imm, (0x12972 - 0x1295c) / 2);
  EXPECT_EQ(ins.b.rs1, RVREG_s7);
  EXPECT_EQ(ins.b.rs2, RVREG_a5);
}
} // namespace btype_insns
