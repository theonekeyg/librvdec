#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

namespace rtype_insns {

TEST(rv32i, rtype_instructions_add) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* add a5,a3,s8 */ 0x018687b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_ADD);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a3);
  EXPECT_EQ(ins.r.rs2, RVREG_s8);
}

TEST(rv32i, rtype_instructions_sub) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sub a3,t1,a2 */ 0x40c306b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SUB);
  EXPECT_EQ(ins.r.rd, RVREG_a3);
  EXPECT_EQ(ins.r.rs1, RVREG_t1);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
}

TEST(rv32i, rtype_instructions_sll) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sll a5,a5,a2 */ 0x00c797b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SLL);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
}

TEST(rv32i, rtype_instructions_slt) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slt a5,a4,a5 */ 0x00f727b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SLT);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a4);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
}

TEST(rv32i, rtype_instructions_sltu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sltu a5,t1,t3 */ 0x01c337b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SLTU);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_t1);
  EXPECT_EQ(ins.r.rs2, RVREG_t3);
}

TEST(rv32i, rtype_instructions_xor) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* xor s7,s7,a5 */ 0x00fbcbb3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_XOR);
  EXPECT_EQ(ins.r.rd, RVREG_s7);
  EXPECT_EQ(ins.r.rs1, RVREG_s7);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
}

TEST(rv32i, rtype_instructions_srl) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srl t1,a2,a6 */ 0x01065333);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SRL);
  EXPECT_EQ(ins.r.rd, RVREG_t1);
  EXPECT_EQ(ins.r.rs1, RVREG_a2);
  EXPECT_EQ(ins.r.rs2, RVREG_a6);
}

TEST(rv32i, rtype_instructions_sra) {
  // FIXME
}

TEST(rv32i, rtype_instructions_or) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* or a5,a5,s3 */ 0x0137e7b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_OR);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_s3);
}

TEST(rv32i, rtype_instructions_and) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* and s4,s4,a5 */ 0x00fa7a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_AND);
  EXPECT_EQ(ins.r.rd, RVREG_s4);
  EXPECT_EQ(ins.r.rs1, RVREG_s4);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
}

TEST(rv64i, rtype_instructions_addw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addw a3,a3,s2 */ 0x012686bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_ADDW);
  EXPECT_EQ(ins.r.rd, RVREG_a3);
  EXPECT_EQ(ins.r.rs1, RVREG_a3);
  EXPECT_EQ(ins.r.rs2, RVREG_s2);
}

TEST(rv64i, rtype_instructions_subw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* subw t3,s0,s7 */ 0x41740e3b);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SUBW);
  EXPECT_EQ(ins.r.rd, RVREG_t3);
  EXPECT_EQ(ins.r.rs1, RVREG_s0);
  EXPECT_EQ(ins.r.rs2, RVREG_s7);
}

TEST(rv64i, rtype_instructions_sllw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sllw a3,s2,a5 */ 0x00f916bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SLLW);
  EXPECT_EQ(ins.r.rd, RVREG_a3);
  EXPECT_EQ(ins.r.rs1, RVREG_s2);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
}

TEST(rv64i, rtype_instructions_srlw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srlw s2,a4,a0 */ 0x00a7593b);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SRLW);
  EXPECT_EQ(ins.r.rd, RVREG_s2);
  EXPECT_EQ(ins.r.rs1, RVREG_a4);
  EXPECT_EQ(ins.r.rs2, RVREG_a0);
}

TEST(rv64i, rtype_instructions_sraw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sraw a5,a5,a4 */ 0x40e7d7bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SRAW);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_a4);
}

TEST(rv32m, rtype_instructions_mul) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* mul t0,t3,t6 */ 0x03fe02b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_MUL);
  EXPECT_EQ(ins.r.rd, RVREG_t0);
  EXPECT_EQ(ins.r.rs1, RVREG_t3);
  EXPECT_EQ(ins.r.rs2, RVREG_t6);
}

TEST(rv32m, rtype_instructions_mulh) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* mulh a4,s4,a3 */ 0x02da1733);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_MULH);
  EXPECT_EQ(ins.r.rd, RVREG_a4);
  EXPECT_EQ(ins.r.rs1, RVREG_s4);
  EXPECT_EQ(ins.r.rs2, RVREG_a3);
}

TEST(rv32m, rtype_instructions_mulhsu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* mulhsu a6,a2,ra */ 0x02162833);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_MULHSU);
  EXPECT_EQ(ins.r.rd, RVREG_a6);
  EXPECT_EQ(ins.r.rs1, RVREG_a2);
  EXPECT_EQ(ins.r.rs2, RVREG_ra);
}

TEST(rv32m, rtype_instructions_mulhu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* mulhu s2,s5,t5 */ 0x03eab933);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_MULHU);
  EXPECT_EQ(ins.r.rd, RVREG_s2);
  EXPECT_EQ(ins.r.rs1, RVREG_s5);
  EXPECT_EQ(ins.r.rs2, RVREG_t5);
}

TEST(rv32m, rtype_instructions_div) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* div s8,sp,s2 */ 0x03214c33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_DIV);
  EXPECT_EQ(ins.r.rd, RVREG_s8);
  EXPECT_EQ(ins.r.rs1, RVREG_sp);
  EXPECT_EQ(ins.r.rs2, RVREG_s2);
}

TEST(rv32m, rtype_instructions_divu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* divu a0,tp,a6 */ 0x03025533);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_DIVU);
  EXPECT_EQ(ins.r.rd, RVREG_a0);
  EXPECT_EQ(ins.r.rs1, RVREG_tp);
  EXPECT_EQ(ins.r.rs2, RVREG_a6);
}

TEST(rv32m, rtype_instructions_rem) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* rem s4,s2,a2 */ 0x02c96a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_REM);
  EXPECT_EQ(ins.r.rd, RVREG_s4);
  EXPECT_EQ(ins.r.rs1, RVREG_s2);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
}

TEST(rv32m, rtype_instructions_remu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* remu s4,s2,s5 */ 0x03597a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_REMU);
  EXPECT_EQ(ins.r.rd, RVREG_s4);
  EXPECT_EQ(ins.r.rs1, RVREG_s2);
  EXPECT_EQ(ins.r.rs2, RVREG_s5);
}

TEST(rv64m, rtype_instructions_mulw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* mulw s3,t3,sp */ 0x022e09bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_MULW);
  EXPECT_EQ(ins.r.rd, RVREG_s3);
  EXPECT_EQ(ins.r.rs1, RVREG_t3);
  EXPECT_EQ(ins.r.rs2, RVREG_sp);
}

TEST(rv64m, rtype_instructions_divw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* divw a6,t0,a0 */ 0x02a2c83b);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_DIVW);
  EXPECT_EQ(ins.r.rd, RVREG_a6);
  EXPECT_EQ(ins.r.rs1, RVREG_t0);
  EXPECT_EQ(ins.r.rs2, RVREG_a0);
}

TEST(rv64m, rtype_instructions_divuw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* divuw a5,a2,s4 */ 0x034657bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_DIVUW);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
  EXPECT_EQ(ins.r.rs1, RVREG_a2);
  EXPECT_EQ(ins.r.rs2, RVREG_s4);
}

TEST(rv64m, rtype_instructions_remw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* remw s7,a6,a2 */ 0x02c86bbb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_REMW);
  EXPECT_EQ(ins.r.rd, RVREG_s7);
  EXPECT_EQ(ins.r.rs1, RVREG_a6);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
}

TEST(rv64m, rtype_instructions_remuw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* remuw a7,s2,t1 */ 0x026978bb);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_REMUW);
  EXPECT_EQ(ins.r.rd, RVREG_a7);
  EXPECT_EQ(ins.r.rs1, RVREG_s2);
  EXPECT_EQ(ins.r.rs2, RVREG_t1);
}
} // namespace rtype_insns
