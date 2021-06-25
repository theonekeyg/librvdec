#include "riscv_insn.hpp"

RTypeInstruction::RTypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
    this->funct7 = (insn >> 24) & 0b1111111;
    this->rs2 = (insn >> 20) & 0b11111;
    this->rs1 = (insn >> 15) & 0b11111;
    this->funct3 = (insn >> 12) & 0b111;
    this->rd = (insn >> 7) & 0b11111;
    this->opcode = insn & 0b1111111;
}

ITypeInstruction::ITypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
}

STypeInstruction::STypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
}

BTypeInstruction::BTypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
}

UTypeInstruction::UTypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
}

JTypeInstruction::JTypeInstruction(const char *name, std::uint32_t insn)
  : RISCVInstruction::RISCVInstruction(name) {
}
