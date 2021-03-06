#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

namespace utype_insns {

TEST(rv32i, utype_instructions_lui) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* lui a3,0x1f */ 0x0001f6b7);
  EXPECT_EQ(ins.type, INSN_U);
  EXPECT_EQ(ins.kind, RVINSN_LUI);
  EXPECT_EQ(ins.u.imm, 0x1f);
  EXPECT_EQ(ins.u.rd, RVREG_a3);
}

TEST(rv32i, utype_instructions_auipc) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* auipc a5,0x5 */ 0x00005797);
  EXPECT_EQ(ins.type, INSN_U);
  EXPECT_EQ(ins.kind, RVINSN_AUIPC);
  EXPECT_EQ(ins.u.imm, 0x5);
  EXPECT_EQ(ins.u.rd, RVREG_a5);
}
} // namespace utype_insns
