#include <gtest/gtest.h>
extern "C" {
#include <rvdec/decode.h>
#include <rvdec/instruction.h>
};

namespace stype_insns {

TEST(rv32i, stype_instructions_sb) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sb a1,13(a4) */ 0x00b706a3);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, KIND_SB);
  EXPECT_EQ(ins.s.imm, 13);
  EXPECT_EQ(ins.s.rs1, 14); // a4
  EXPECT_EQ(ins.s.rs2, 11); // a1
}

TEST(rv32i, stype_instructions_sh) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sh a5,16(sp) */ 0x00f11823);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, KIND_SH);
  EXPECT_EQ(ins.s.imm, 16);
  EXPECT_EQ(ins.s.rs1, 2); // sp
  EXPECT_EQ(ins.s.rs2, 15); // a5
}

TEST(rv32i, stype_instructions_sw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sw a5,-372(s0) */ 0xe8f42623);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, KIND_SW);
  EXPECT_EQ(ins.s.imm, -372);
  EXPECT_EQ(ins.s.rs1, 8); // s0
  EXPECT_EQ(ins.s.rs2, 15); // a5
}

TEST(rv64i, stype_instructions_sd) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sd s0,1216(sp) */ 0x4c813023);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, KIND_SD);
  EXPECT_EQ(ins.s.imm, 1216);
  EXPECT_EQ(ins.s.rs1, 2); // sp
  EXPECT_EQ(ins.s.rs2, 8); // s0
}
} // namespace stype_insns
