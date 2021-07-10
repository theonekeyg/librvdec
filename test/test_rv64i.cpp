#include <gtest/gtest.h>
extern "C" {
#include "riscv_decode.h"
#include "riscv_insn.h"
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
} // namespace rtype_insns

namespace itype_insns {

TEST(rv32i, itype_instructions_jalr) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* jalr -94(a3) */ 0xfa2680e7);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_JALR);
  EXPECT_EQ(ins.i.imm, -94);
  EXPECT_EQ(ins.i.rs1, 13); // a3
}

TEST(rv32i, itype_instructions_lb) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lb s7,0(s8) */ 0x000c0b83);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LB);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rd, 23); // s7
  EXPECT_EQ(ins.i.rs1, 24); // s8
}

TEST(rv32i, itype_instructions_lh) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lh a5,-210(s0) */ 0xf2e41783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LH);
  EXPECT_EQ(ins.i.imm, -210);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
}

TEST(rv32i, itype_instructions_lw) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lw a5,-44(s0) */ 0xfd442783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LW);
  EXPECT_EQ(ins.i.imm, -44);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
}

TEST(rv32i, itype_instructions_lbu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lbu a5,0(a5) */ 0x0007c783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LBU);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 15); // a5
}

TEST(rv32i, itype_instructions_lhu) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lhu a5,2(a5) */ 0x0027d783);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_LHU);
  EXPECT_EQ(ins.i.imm, 2);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 15); // a5
}

TEST(rv32i, itype_instructions_addi) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lhu a5,s0,-200 */ 0xf3840793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_ADDI);
  EXPECT_EQ(ins.i.imm, -200);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 8); // s0
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
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 13); // a3
}

TEST(rv32i, itype_instructions_srli) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srli a5,a4,0x1e */ 0x01e75793);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRLI);
  EXPECT_EQ(ins.i.imm, 0x1e);
  EXPECT_EQ(ins.i.rd, 15); // a5
  EXPECT_EQ(ins.i.rs1, 14); // a4
}

TEST(rv32i, itype_instructions_srai) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srai s3,s3,0x3f */ 0x43f9d993);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, KIND_SRAI);
  EXPECT_EQ(ins.i.imm, 0x3f);
  EXPECT_EQ(ins.i.rd, 19); // s3
  EXPECT_EQ(ins.i.rs1, 19); // s3
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
} // namespace itype_insns

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
} // namespace stype_insns

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

namespace utype_insns {

TEST(rv32i, utype_instructions_lui) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lui a3,0x1f */ 0x0001f6b7);
  EXPECT_EQ(ins.type, INSN_U);
  EXPECT_EQ(ins.kind, KIND_LUI);
  EXPECT_EQ(ins.u.imm, 0x1f);
  EXPECT_EQ(ins.u.rd, 13); // a3
}

TEST(rv32i, utype_instructions_auipc) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* auipc a5,0x5 */ 0x00005797);
  EXPECT_EQ(ins.type, INSN_U);
  EXPECT_EQ(ins.kind, KIND_AUIPC);
  EXPECT_EQ(ins.u.imm, 0x5);
  EXPECT_EQ(ins.u.rd, 15); // a5
}
} // namespace utype_insns

namespace jtype_insns {

TEST(rv32i, jtype_instructions_jal) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 19e24: jal ra,196f2 */ 0x8cfff0ef);
  EXPECT_EQ(ins.type, INSN_J);
  EXPECT_EQ(ins.kind, KIND_JAL);
  EXPECT_EQ(ins.j.imm, (0x196f2 - 0x19e24) / 2);
  EXPECT_EQ(ins.j.rd, 1); // ra
}
} // namespace jtype_insns
