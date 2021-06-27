#include "riscv_insn.hpp"

RTypeInstruction::RTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
    this->funct7 = (insn >> 24) & 0b1111111;
    this->rs2 = (insn >> 20) & 0b11111;
    this->rs1 = (insn >> 15) & 0b11111;
    this->funct3 = (insn >> 12) & 0b111;
    this->rd = (insn >> 7) & 0b11111;
    this->opcode = insn & 0b1111111;
}

std::ostream& operator<<(std::ostream &s, RTypeInstruction &ins) {
  s << ins.getName() << " { funct7: " << ins.funct7 << ", rs2: " << ins.rs2 << ", rs1: "
    << ins.rs1 << ", funct3: " << ins.funct3 << ", rd: " << ins.rd << ", opcode: " << ins.opcode
    << " }";
  return s;
}

ITypeInstruction::ITypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, ITypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs1: " << ins.rs1 << ", funct3: "
    << ins.funct3 << ", rd: " << ins.rd << ", opcode: " << ins.opcode << " }";
  return s;
}

STypeInstruction::STypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, STypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << ins.rs2 << ", rs1: "
    << ins.rs1 << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

BTypeInstruction::BTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, BTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << ins.rs2 << ", rs1: "
    << ins.rs1 << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

UTypeInstruction::UTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, UTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rd: " << ins.rd
    << ", opcode: " << ins.opcode << " }";
  return s;
}

JTypeInstruction::JTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, JTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rd: " << ins.rd
    << ", opcode: " << ins.opcode << " }";
  return s;
}

std::ostream& operator<<(std::ostream &s, InvalidInstruction &ins) {
  s << ins.getName();
  return s;
}
