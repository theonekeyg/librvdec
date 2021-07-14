#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

namespace itype_insns {

TEST(rv32i, itype_instructions_jalr) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* jalr -94(a3) */ 0xfa2680e7);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_JALR);
  EXPECT_EQ(ins.i.imm, -94);
  EXPECT_EQ(ins.i.rs1, RVREG_a3);
}

TEST(rv32i, itype_instructions_lb) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lb s7,0(s8) */ 0x000c0b83);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LB);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rd, RVREG_s7);
  EXPECT_EQ(ins.i.rs1, RVREG_s8);
}

TEST(rv32i, itype_instructions_lh) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lh a5,-210(s0) */ 0xf2e41783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LH);
  EXPECT_EQ(ins.i.imm, -210);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
}

TEST(rv32i, itype_instructions_lw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lw a5,-44(s0) */ 0xfd442783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LW);
  EXPECT_EQ(ins.i.imm, -44);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
}

TEST(rv32i, itype_instructions_lbu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lbu a5,0(a5) */ 0x0007c783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LBU);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
}

TEST(rv32i, itype_instructions_lhu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lhu a5,2(a5) */ 0x0027d783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LHU);
  EXPECT_EQ(ins.i.imm, 2);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
}

TEST(rv32i, itype_instructions_addi) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi a5,s0,-200 */ 0xf3840793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_ADDI);
  EXPECT_EQ(ins.i.imm, -200);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
}

TEST(rv32i, itype_instructions_slti) {
  // FIXME
}

TEST(rv32i, itype_instructions_sltiu) {
  // FIXME
}

TEST(rv32i, itype_instructions_xori) {
  // FIXME
}

TEST(rv32i, itype_instructions_ori) {
  // FIXME
}

TEST(rv32i, itype_instructions_andi) {
  // FIXME
}

TEST(rv32i, itype_instructions_slli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slli a5,a3,0x20 */ 0x02069793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SLLI);
  EXPECT_EQ(ins.i.imm, 0x20);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a3);
}

TEST(rv32i, itype_instructions_srli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srli a5,a4,0x1e */ 0x01e75793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRLI);
  EXPECT_EQ(ins.i.imm, 0x1e);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a4);
}

TEST(rv32i, itype_instructions_srai) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srai s3,s3,0x3f */ 0x43f9d993);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRAI);
  EXPECT_EQ(ins.i.imm, 0x3f);
  EXPECT_EQ(ins.i.rd, RVREG_s3);
  EXPECT_EQ(ins.i.rs1, RVREG_s3);
}

TEST(rv32i, itype_instructions_fence) {
  // FIXME
}

TEST(rv32i, itype_instructions_ecall) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* ecall */ 0x00000073);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_ECALL);
}

TEST(rv32i, itype_instructions_ebreak) {
  // FIXME
}

TEST(rv64i, itype_instructions_lwu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lwu a5,-292(s0) */ 0xedc46783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LWU);
  EXPECT_EQ(ins.i.imm, -292);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
}

TEST(rv64i, itype_instructions_ld) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* ld a4,-224(s0) */ 0xf2043703);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LD);
  EXPECT_EQ(ins.i.imm, -224);
  EXPECT_EQ(ins.i.rd, RVREG_a4);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
}

TEST(rv64i, itype_instructions_slli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slli a5,a3,0x20 */ 0x02069793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SLLI);
  EXPECT_EQ(ins.i.imm, 0x20);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a3);
}

TEST(rv64i, itype_instructions_srli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srli s3,s3,0x3 */ 0x0039d993);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRLI);
  EXPECT_EQ(ins.i.imm, 0x3);
  EXPECT_EQ(ins.i.rd, RVREG_s3);
  EXPECT_EQ(ins.i.rs1, RVREG_s3);
}

TEST(rv64i, itype_instructions_srai) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srai s3,s3,0x3f */ 0x43f9d993);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRAI);
  EXPECT_EQ(ins.i.imm, 0x3f);
  EXPECT_EQ(ins.i.rd, RVREG_s3);
  EXPECT_EQ(ins.i.rs1, RVREG_s3);
}

TEST(rv64i, itype_instructions_addiw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addiw a5,a3,289 */ 0x1216879b);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_ADDIW);
  EXPECT_EQ(ins.i.imm, 289);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a3);
}

TEST(rv64i, itype_instructions_slliw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slliw a5,a5,0x10 */ 0x0107979b);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SLLIW);
  EXPECT_EQ(ins.i.imm, 0x10);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
}

TEST(rv64i, itype_instructions_srliw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srliw a5,s10,0x1f */ 0x01fd579b);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRLIW);
  EXPECT_EQ(ins.i.imm, 0x1f);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_s10);
}

TEST(rv64i, itype_instructions_sraiw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srliw a5,a5,0x10 */ 0x4107d79b);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRAIW);
  EXPECT_EQ(ins.i.imm, 0x10);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
}
} // namespace itype_insns
