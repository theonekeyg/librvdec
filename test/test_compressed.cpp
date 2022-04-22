#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

#include "config.h"

namespace compressed_insns {

// The last 2 bytes at the end represent the following instruction,
// to test ability to disambiguate compressed instruction from regular
// 32 bit binary. So only high 16 bits matter in those tests.

namespace test_rvc_cr {

TEST(rvc_cr, C_JALR) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* jalr a4 */ 0x97020165);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_JALR);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rs1, RVREG_ra);
  EXPECT_EQ(ins.i.rd, RVREG_a4);
}

TEST(rvc_cr, C_JR) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* jalr a5 */ 0x8782fce5);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_JALR);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rs1, RVREG_zero);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
}

TEST(rvc_cr, C_MV) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* add a5,zero,a2 */ 0x87b20107);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_ADD);
  EXPECT_EQ(ins.r.rs1, RVREG_zero);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
}

TEST(rvc_cr, C_ADD) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* add s6,s6,s0 */ 0x9b221d20);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_ADD);
  EXPECT_EQ(ins.r.rs1, RVREG_s6);
  EXPECT_EQ(ins.r.rs2, RVREG_s0);
  EXPECT_EQ(ins.r.rd, RVREG_s6);
}

TEST(rvc_cr, C_EBREAK) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* ebreak */ 0x900297a2);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_EBREAK);
  EXPECT_EQ(ins.r.rs1, 0);
  EXPECT_EQ(ins.r.rs2, 0);
  EXPECT_EQ(ins.r.rd, 0);
}
} // namespace test_rvc_cr

namespace test_rvc_ci {

TEST(rvc_ci, C_LI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi a5,x0,14 */ 0x47b9874a);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDI);
  EXPECT_EQ(ins.i.imm, 14);
  EXPECT_EQ(ins.i.rs1, RVREG_zero);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
}

TEST(rvc_ci, C_LUI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /*  lui a1,0x1d */ 0x65f58885);
  EXPECT_EQ(ins.type, INSN_U);
  EXPECT_EQ(ins.kind, RVINSN_LUI);
  EXPECT_EQ(ins.u.imm, 0x1d);
  EXPECT_EQ(ins.u.rd, 11);
}

TEST(rvc_ci, C_ADDISP16) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi sp,sp,80 */ 0x61618082);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDI);
  EXPECT_EQ(ins.i.imm, 80);
  EXPECT_EQ(ins.i.rs1, RVREG_sp);
  EXPECT_EQ(ins.i.rd, RVREG_sp);
}

TEST(rvc_ci, C_ADDI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi a2,a2,-2 */ 0x167992c1);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDI);
  EXPECT_EQ(ins.i.imm, -2);
  EXPECT_EQ(ins.i.rs1, RVREG_a2);
  EXPECT_EQ(ins.i.rd, RVREG_a2);
}

TEST(rvc_ci, C_NOP) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi x0,x0,0 */ 0x000192c1);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDI);
  EXPECT_EQ(ins.i.imm, 0);
  EXPECT_EQ(ins.i.rs1, RVREG_zero);
  EXPECT_EQ(ins.i.rd, RVREG_zero);
}

TEST(rvc_ci, C_ADDIW) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addiw s2,s2,1 */ 0x2905fdfd);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDIW);
  EXPECT_EQ(ins.i.imm, 1);
  EXPECT_EQ(ins.i.rs1, RVREG_s2);
  EXPECT_EQ(ins.i.rd, RVREG_s2);
}

TEST(rvc_ci, C_SLLI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* slli s2,s2,0x20 */ 0x19020209);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_SLLI);
  EXPECT_EQ(ins.i.imm, 0x20);
  EXPECT_EQ(ins.i.rs1, RVREG_s2);
  EXPECT_EQ(ins.i.rd, RVREG_s2);
}

TEST(rvc_ci, C_LDSP) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* ld a5,288(sp) */ 0x77921181);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_LD);
  EXPECT_EQ(ins.i.imm, 288);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
  EXPECT_EQ(ins.i.rd, RVREG_sp);
}

} // namespace test_rvc_ci

namespace test_rvc_css {

TEST(rvc_css, C_SWSP) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sw a4,232(sp) */ 0xd5ba98ba);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, RVINSN_SW);
  EXPECT_EQ(ins.s.imm, 232);
  EXPECT_EQ(ins.s.rs1, RVREG_sp);
  EXPECT_EQ(ins.s.rs2, RVREG_a4);
}

TEST(rvc_css, C_SDSP) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sd a5,176(sp) */ 0xf93e018c);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, RVINSN_SD);
  EXPECT_EQ(ins.s.imm, 176);
  EXPECT_EQ(ins.s.rs1, RVREG_sp);
  EXPECT_EQ(ins.s.rs2, RVREG_a5);
}
} // namespace test_rvc_css

namespace test_rvc_ciw {

TEST(rvc_ciw, C_ADDI4SPN) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addi a0,sp,208 */ 0x0988f20f);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ADDI);
  EXPECT_EQ(ins.i.imm, 208);
  EXPECT_EQ(ins.i.rs1, RVREG_sp);
  EXPECT_EQ(ins.i.rd, RVREG_a0);
}
} // namespace test_rvc_ciw

namespace test_rvc_cl {

TEST(rvc_cl, C_LW) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lw a5,80(a0) */ 0x493c0086);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_LW);
  EXPECT_EQ(ins.i.imm, 80);
  EXPECT_EQ(ins.i.rs1, RVREG_a0);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
}

TEST(rvc_cl, C_LD) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* ld a3,16(a0) */ 0x6914020d);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_LD);
  EXPECT_EQ(ins.i.imm, 16);
  EXPECT_EQ(ins.i.rs1, RVREG_a0);
  EXPECT_EQ(ins.i.rd, RVREG_a3);
}
} // namespace test_rvc_cl

namespace test_rvc_cs {

TEST(rvc_cs, C_SW) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sw a4,24(s1) */ 0xcc98bfc1);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, RVINSN_SW);
  EXPECT_EQ(ins.s.imm, 24);
  EXPECT_EQ(ins.s.rs1, RVREG_s1);
  EXPECT_EQ(ins.s.rs2, RVREG_a4);
}

TEST(rvc_cs, C_SD) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sd a3,8(a4) */ 0xe714d4b2);
  EXPECT_EQ(ins.type, INSN_S);
  EXPECT_EQ(ins.kind, RVINSN_SD);
  EXPECT_EQ(ins.s.imm, 8);
  EXPECT_EQ(ins.s.rs1, RVREG_a4);
  EXPECT_EQ(ins.s.rs2, RVREG_a3);
}
} // namespace test_rvc_cs

namespace test_rvc_ca {

TEST(rvc_ca, C_AND) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* and a3,a3,a2 */ 0x8ef16c1c);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_AND);
  EXPECT_EQ(ins.r.rs1, RVREG_a3);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
  EXPECT_EQ(ins.r.rd, RVREG_a3);
}

TEST(rvc_ca, C_OR) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* or a2,a2,a5 */ 0x8e5dca01);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_OR);
  EXPECT_EQ(ins.r.rs1, RVREG_a2);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
  EXPECT_EQ(ins.r.rd, RVREG_a2);
}

TEST(rvc_ca, C_XOR) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* xor a5,a5,a2 */ 0x8fb100f7);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_XOR);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_a2);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
}

TEST(rvc_ca, C_SUB) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* sub a5,a5,a3 */ 0x8f958f8d);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SUB);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_a3);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
}

TEST(rvc_ca, C_ADDW) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* addw a5,a5,s1 */ 0x9fa502a0);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_ADDW);
  EXPECT_EQ(ins.r.rs1, RVREG_a5);
  EXPECT_EQ(ins.r.rs2, RVREG_s1);
  EXPECT_EQ(ins.r.rd, RVREG_a5);
}

TEST(rvc_ca, C_SUBW) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* subw a1,a1,a5 */ 0x9d9d8722);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.kind, RVINSN_SUBW);
  EXPECT_EQ(ins.r.rs1, RVREG_a1);
  EXPECT_EQ(ins.r.rs2, RVREG_a5);
  EXPECT_EQ(ins.r.rd, RVREG_a1);
}
} // namespace test_rvc_ca

namespace test_rvc_cb {

TEST(rvc_cb, C_BEQZ) {
  uint32_t pc = 0x14604;
  struct riscv_insn ins;
  riscv_decode(&ins, /* beqz a5,146c2 */ 0xcfdd65f1);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BEQ);
  EXPECT_EQ(ins.b.rs1, RVREG_a5);
  EXPECT_EQ(ins.b.rs2, RVREG_zero);
  EXPECT_EQ(pc + ins.b.imm, 0x146c2);
}

TEST(rvc_cb, C_BNEZ) {
  uint32_t pc = 0x14706;
  struct riscv_insn ins;
  riscv_decode(&ins, /* bnez a5,147a2 */ 0xefd11998);
  EXPECT_EQ(ins.type, INSN_B);
  EXPECT_EQ(ins.kind, RVINSN_BNE);
  EXPECT_EQ(ins.b.rs1, RVREG_a5);
  EXPECT_EQ(ins.b.rs2, RVREG_zero);
  EXPECT_EQ(pc + ins.b.imm, 0x147a2);
}

TEST(rvc_cb, C_SRLI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srli a4,a4,0x30 */ 0x934112e1);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_SRLI);
  EXPECT_EQ(ins.i.rs1, RVREG_a4);
  EXPECT_EQ(ins.i.rd, RVREG_a4);
  EXPECT_EQ(ins.i.imm, 0x30);
}

TEST(rvc_cb, C_SRAI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* srai s0,s0,0x1 */ 0x8405070e);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_SRAI);
  EXPECT_EQ(ins.i.rs1, RVREG_s0);
  EXPECT_EQ(ins.i.rd, RVREG_s0);
  EXPECT_EQ(ins.i.imm, 1);
}

TEST(rvc_cb, C_ANDI) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* andi a5,a5,-4 */ 0x9bf10047);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.kind, RVINSN_ANDI);
  EXPECT_EQ(ins.i.rs1, RVREG_a5);
  EXPECT_EQ(ins.i.rd, RVREG_a5);
  EXPECT_EQ(ins.i.imm, -4);
}
} // namespace test_rvc_cb

namespace test_rvc_cj {

TEST(rvc_cj, C_J) {
  uint32_t pc = 0x10170;
  struct riscv_insn ins;
  riscv_decode(&ins, /* j 100e8 */ 0xbfa51141);
  EXPECT_EQ(ins.type, INSN_J);
  EXPECT_EQ(ins.kind, RVINSN_JAL);
  EXPECT_EQ(ins.j.rd, RVREG_zero);
  EXPECT_EQ(pc + ins.j.imm, 0x100e8);
}

#if defined(SUPPORT_RV32I) && !defined(SUPPORT_RV64I)
TEST(rvc_cj, C_JAL) {
  uint32_t pc = 0x10170;
  struct riscv_insn ins;
  riscv_decode(&ins, /* jal 100e8 */ 0x3fa51141);
  EXPECT_EQ(ins.type, INSN_J);
  EXPECT_EQ(ins.kind, RVINSN_JAL);
  EXPECT_EQ(ins.j.rd, RVREG_zero);
  EXPECT_EQ(pc + ins.j.imm, 0x100e8);
}
#endif
}; // namespace test_rvc_cj

} // namespace btype_insns
