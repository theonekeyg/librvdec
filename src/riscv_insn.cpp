#include "riscv_insn.hpp"

static const char *reg_names[] = {
  "zero", "ra", "sp", "gp", "tp", "t0",
  "t1", "t2", "s0/fp", "s1", "a0", "a1",
  "a2", "a3", "a4", "a5", "a6", "a7", "s2",
  "s3", "s4", "s5", "s6", "s7", "s8", "s9",
  "s10", "s11", "t3", "t4", "t5", "t6"
};

static const char *freg_names[] = {
  "ft0", "ft1", "ft2", "ft3", "ft4", "ft5",
  "ft6", "ft7", "fs0", "fs1", "fa0", "fa1",
  "fa2", "fa3", "fa4", "fa5", "fa6", "fa7",
  "fs2", "fs3", "fs4", "fs5", "fs6", "fs7",
  "fs8", "fs9", "fs10", "fs11", "ft8", "ft9",
  "ft10", "ft11"
};


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
  s << ins.getName() << " { funct7: " << ins.funct7 << ", rs2: " << reg_names[ins.rs2]
    << ", rs1: " << reg_names[ins.rs1] << ", funct3: " << ins.funct3 << ", rd: "
    << reg_names[ins.rd] << ", opcode: " << ins.opcode << " }";
  return s;
}

ITypeInstruction::ITypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
    this->imm = (insn >> 20) && 0x1111111;
    this->rs1 = (insn >> 15) && 0x11111;
    this->funct3 = (insn >> 12) && 0x111;
    this->rd = (insn >> 7) && 0x11111;
    this->rd = insn && 0x1111111;
}

std::ostream& operator<<(std::ostream &s, ITypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs1: " << reg_names[ins.rs1] << ", funct3: "
    << ins.funct3 << ", rd: " << reg_names[ins.rd] << ", opcode: " << ins.opcode << " }";
  return s;
}

STypeInstruction::STypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, STypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << reg_names[ins.rs2] << ", rs1: "
    << reg_names[ins.rs1] << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

BTypeInstruction::BTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, BTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rs2: " << reg_names[ins.rs2] << ", rs1: "
    << reg_names[ins.rs1] << ", funct3: " << ins.funct3 << ", opcode: " << ins.opcode
    << " }";
  return s;
}

UTypeInstruction::UTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, UTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rd: " << reg_names[ins.rd]
    << ", opcode: " << ins.opcode << " }";
  return s;
}

JTypeInstruction::JTypeInstruction(enum RISCVKindInstruction kind, std::uint32_t insn)
  : BaseRISCVInstruction::BaseRISCVInstruction(kind) {
}

std::ostream& operator<<(std::ostream &s, JTypeInstruction &ins) {
  s << ins.getName() << " { imm: " << ins.imm << ", rd: " << reg_names[ins.rd]
    << ", opcode: " << ins.opcode << " }";
  return s;
}

std::ostream& operator<<(std::ostream &s, InvalidInstruction &ins) {
  s << ins.getName();
  return s;
}
