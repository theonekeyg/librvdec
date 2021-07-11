#include <gtest/gtest.h>
extern "C" {
#include "riscv_decode.h"
#include "riscv_insn.h"
};

namespace btype_insns {

TEST(rv32i, btype_instructions_beq) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 142c2: beq a5,a3,142b0 */ 0xfed787e3);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BEQ);
  EXPECT_EQ(ins.b.imm, (0x142b0 - 0x142c2) / 2);
  EXPECT_EQ(ins.b.rs1, 15); // a5
  EXPECT_EQ(ins.b.rs2, 13); // a3
}

TEST(rv32i, btype_instructions_bne) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1437a: bne a3,a5,142ce */ 0xf4f69ae3);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BNE);
  EXPECT_EQ(ins.b.imm, (0x142ce - 0x1437a) / 2);
  EXPECT_EQ(ins.b.rs1, 13); // a3
  EXPECT_EQ(ins.b.rs2, 15); // a5
}

TEST(rv32i, btype_instructions_blt) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1ca0: blt a4,a3,1d38 */ 0x08d74c63);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BLT);
  EXPECT_EQ(ins.b.imm, (0x1d38 - 0x1ca0) / 2);
  EXPECT_EQ(ins.b.rs1, 14); // a4
  EXPECT_EQ(ins.b.rs2, 13); // a3
}

TEST(rv32i, btype_instructions_bge) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 105e6: bge s5,s3,105ec */ 0x013ad363);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BGE);
  EXPECT_EQ(ins.b.imm, (0x105ec - 0x105e6) / 2);
  EXPECT_EQ(ins.b.rs1, 21); // s5
  EXPECT_EQ(ins.b.rs2, 19); // s3
}

TEST(rv32i, btype_instructions_bltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 11400: bltu a5,s8,11822 */ 0x4387e163);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BLTU);
  EXPECT_EQ(ins.b.imm, (0x11822 - 0x11400) / 2);
  EXPECT_EQ(ins.b.rs1, 15); // a5
  EXPECT_EQ(ins.b.rs2, 24); // s8
}

TEST(rv32i, btype_instructions_bgeu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 1295c: bltu s7,a5,12972 */ 0x00fbfb63);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, KIND_BGEU);
  EXPECT_EQ(ins.b.imm, (0x12972 - 0x1295c) / 2);
  EXPECT_EQ(ins.b.rs1, 23); // s7
  EXPECT_EQ(ins.b.rs2, 15); // a5
}
} // namespace btype_insns
