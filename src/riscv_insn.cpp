#include "riscv_insn.hpp"

RTypeInstruction::RTypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
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

ITypeInstruction::ITypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
}

std::ostream& operator<<(std::ostream &s, ITypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs1: " << ins.rs1 << ", funct3: "
    << ins.funct3 << ", rd: " << ins.rd << ", opcode: " << ins.opcode << " }";
  return s;
}

STypeInstruction::STypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
}

std::ostream& operator<<(std::ostream &s, STypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << ins.rs2 << ", rs1: "
    << ins.rs1 << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

BTypeInstruction::BTypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
}

std::ostream& operator<<(std::ostream &s, BTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << ins.rs2 << ", rs1: "
    << ins.rs1 << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

UTypeInstruction::UTypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
}

std::ostream& operator<<(std::ostream &s, UTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rd: " << ins.rd
    << ", opcode: " << ins.opcode << " }";
  return s;
}

JTypeInstruction::JTypeInstruction(const char *name, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(name) {
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
