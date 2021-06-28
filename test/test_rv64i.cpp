#include <gtest/gtest.h>
#include "riscv_decode.hpp"
#include "riscv_insn.hpp"

namespace rtype_insns {

// Something wrong with add instruction parse, haven't figured it out yet
 /*
TEST(rv32i, rtype_instructions_add) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x9696);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_ADD);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 13); // a3
  EXPECT_EQ(ins.ins.r.rs1, 13); // a3
  EXPECT_EQ(ins.ins.r.rs2, 5); // t0
}
*/

TEST(rv32i, rtype_instructions_sub) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x40c306b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_SUB);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 13); // a3
  EXPECT_EQ(ins.ins.r.rs1, 6); // t1
  EXPECT_EQ(ins.ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_sll) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x00c797b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_SLL);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 15); // a5
  EXPECT_EQ(ins.ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.ins.r.rs2, 12); // a2
}

TEST(rv32i, rtype_instructions_slt) {
  // @@@
}

TEST(rv32i, rtype_instructions_sltu) {
  // @@@
}

TEST(rv32i, rtype_instructions_xor) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x00fbcbb3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_XOR);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 23); // s7
  EXPECT_EQ(ins.ins.r.rs1, 23); // s7
  EXPECT_EQ(ins.ins.r.rs2, 15); // a5
}

TEST(rv32i, rtype_instructions_srl) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x01065333);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_SRL);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 6); // t1
  EXPECT_EQ(ins.ins.r.rs1, 12); // a2
  EXPECT_EQ(ins.ins.r.rs2, 16); // a6
}

TEST(rv32i, rtype_instructions_sra) {
  // @@@
}

TEST(rv32i, rtype_instructions_or) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x0137e7b3);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_OR);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 15); // a5
  EXPECT_EQ(ins.ins.r.rs1, 15); // a5
  EXPECT_EQ(ins.ins.r.rs2, 19); // s3
}

TEST(rv32i, rtype_instructions_and) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x00fa7a33);
  EXPECT_EQ(ins.type, INSN_R);
  EXPECT_EQ(ins.ins.r.kind, KIND_AND);
  // check registers
  EXPECT_EQ(ins.ins.r.rd, 20); // s4
  EXPECT_EQ(ins.ins.r.rs1, 20); // s4
  EXPECT_EQ(ins.ins.r.rs2, 15); // a5
}

} // namespace rtype_insns

namespace itype_insns {

TEST(rv32i, itype_instructions_jalr) {
  RISCVDecoder d{USE_RV64I};
  RISCVInstruction ins = d.decode(0x9a02);
  EXPECT_EQ(ins.type, INSN_I);
  EXPECT_EQ(ins.ins.i.kind, KIND_JALR);
  // check registers
}

} // namespace itype_insns
