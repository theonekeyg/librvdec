#include <gtest/gtest.h>
extern "C" {
#include <rvdec/decode.h>
#include <rvdec/instruction.h>
};

namespace rtype_insns {

TEST(rv32i, rtype_instructions_add) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* add a5,a3,s8 */ 0x018687b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_ADD);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 13); // a3
  EXPECT_EQ(ins.r.rs2, 24); // s8
}

TEST(rv32i, rtype_instructions_sub) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sub a3,t1,a2 */ 0x40c306b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SUB);
  EXPECT_EQ(ins.r.rd, 13); // a3
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_sll) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sll a5,a5,a2 */ 0x00c797b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLL);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_slt) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slt a5,a4,a5 */ 0x00f727b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLT);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 14); // a4
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_sltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sltu a5,t1,t3 */ 0x01c337b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLTU);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.r.rs2, 28); // t3
}

TEST(rv32i, rtype_instructions_xor) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* xor s7,s7,a5 */ 0x00fbcbb3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_XOR);
  EXPECT_EQ(ins.r.rd, 23); // s7
  EXPECT_EQ(ins.r.rs1, 23); // s7
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_srl) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srl t1,a2,a6 */ 0x01065333);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SRL);
  EXPECT_EQ(ins.r.rd, 6); // t1
  EXPECT_EQ(ins.r.rs1, 12); // a2
  EXPECT_EQ(ins.r.rs2, 16); // a6
}

TEST(rv32i, rtype_instructions_sra) {
  // FIXME
}

TEST(rv32i, rtype_instructions_or) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* or a5,a5,s3 */ 0x0137e7b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_OR);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 19); // s3
}

TEST(rv32i, rtype_instructions_and) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* and s4,s4,a5 */ 0x00fa7a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_AND);
  EXPECT_EQ(ins.r.rd, 20); // s4
  EXPECT_EQ(ins.r.rs1, 20); // s4
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv64i, rtype_instructions_addw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addw a3,a3,s2 */ 0x012686bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_ADDW);
  EXPECT_EQ(ins.r.rd, 13); // a3
  EXPECT_EQ(ins.r.rs1, 13); // a3
  EXPECT_EQ(ins.r.rs2, 18); // s2
}

TEST(rv64i, rtype_instructions_subw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* subw t3,s0,s7 */ 0x41740e3b);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SUBW);
  EXPECT_EQ(ins.r.rd, 28); // t3
  EXPECT_EQ(ins.r.rs1, 8); // s0
  EXPECT_EQ(ins.r.rs2, 23); // s7
}

TEST(rv64i, rtype_instructions_sllw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sllw a3,s2,a5 */ 0x00f916bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SLLW);
  EXPECT_EQ(ins.r.rd, 13); // a3
  EXPECT_EQ(ins.r.rs1, 18); // s2
  EXPECT_EQ(ins.r.rs2, 15); // a5
}

TEST(rv64i, rtype_instructions_srlw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srlw s2,a4,a0 */ 0x00a7593b);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SRLW);
  EXPECT_EQ(ins.r.rd, 18); // s2
  EXPECT_EQ(ins.r.rs1, 14); // a4
  EXPECT_EQ(ins.r.rs2, 10); // a0
}

TEST(rv64i, rtype_instructions_sraw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sraw a5,a5,a4 */ 0x40e7d7bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, KIND_SRAW);
  EXPECT_EQ(ins.r.rd, 15); // a5
  EXPECT_EQ(ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.r.rs2, 14); // a4
}
} // namespace rtype_insns
