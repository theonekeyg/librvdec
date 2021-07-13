#include <gtest/gtest.h>

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

namespace jtype_insns {

TEST(rv32i, jtype_instructions_jal) {
  struct riscv_insn ins;
  riscv_decode(&ins, /* 19e24: jal ra,196f2 */ 0x8cfff0ef);
  EXPECT_EQ(ins.type, INSN_J);
  EXPECT_EQ(ins.kind, KIND_JAL);
  EXPECT_EQ(ins.j.imm, (0x196f2 - 0x19e24) / 2);
  EXPECT_EQ(ins.j.rd, RVREG_ra);
}
} // namespace jtype_insns
