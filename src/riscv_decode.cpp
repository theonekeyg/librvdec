#include "riscv_decode.hpp"
#include "riscv_insn.hpp"

RISCVInstruction RISCVDecoder::decode(std::uint32_t insn) {
  RISCVInstruction ins{};
  std::uint32_t opcode = insn & 0b1111111;
  switch (OPCODE_TYPES_TABLE[opcode]) {
    case INSN_R:
      for (auto decoder : decoders) {
        std::optional<RTypeInstruction> decoded_insn
          = decoder.decodeRType(insn, opcode);
        if (decoded_insn) {
          ins.setRType(decoded_insn.value());
        }
      }
      break;
    case INSN_I:
      for (auto decoder : decoders) {
        std::optional<ITypeInstruction> decoded_insn
          = decoder.decodeIType(insn, opcode);
        if (decoded_insn) {
          ins.setIType(decoded_insn.value());
        }
      }
      break;
    case INSN_S:
      for (auto decoder : decoders) {
        std::optional<STypeInstruction> decoded_insn
          = decoder.decodeSType(insn, opcode);
        if (decoded_insn) {
          ins.setSType(decoded_insn.value());
        }
      }
      break;
    case INSN_B:
      for (auto decoder : decoders) {
        std::optional<BTypeInstruction> decoded_insn
          = decoder.decodeBType(insn, opcode);
        if (decoded_insn) {
          ins.setBType(decoded_insn.value());
        }
      }
      break;
    case INSN_U:
      for (auto decoder : decoders) {
        std::optional<UTypeInstruction> decoded_insn
          = decoder.decodeUType(insn, opcode);
        if (decoded_insn) {
          ins.setUType(decoded_insn.value());
        }
      }
      break;
    case INSN_J:
      for (auto decoder : decoders) {
        std::optional<JTypeInstruction> decoded_insn
          = decoder.decodeJType(insn, opcode);
        if (decoded_insn) {
          ins.setJType(decoded_insn.value());
        }
      }
      break;
  }
  return ins;
}

std::optional<RTypeInstruction> RV32IDecoder::decodeRType(
    std::uint32_t insn, std::uint32_t opcode) {
  std::uint32_t funct7 = (insn >> 25) & 0b1111111;
  std::uint32_t funct3 = (insn >> 12) & 0b111;
  switch (funct3) {
    case 0:
      if (funct7 == 0b0000000) {
        return std::optional(ADD(KIND_ADD, insn));
      } else if (funct7 == 0b0100000) {
        return std::optional(SUB(KIND_SUB, insn));
      }
      break;
    case 0b001:
      return std::optional(SLL(KIND_SLL, insn));
    case 0b010:
      return std::optional(SLT(KIND_SLT, insn));
    case 0b011:
      return std::optional(SLTU(KIND_SLTU, insn));
    case 0b100:
      return std::optional(XOR(KIND_XOR, insn));
    case 0b101:
      if (funct7 == 0b0000000) {
        return std::optional(SRL(KIND_SRL, insn));
      } else if (funct7 == 0b0100000) {
        return std::optional(SRA(KIND_SRA, insn));
      }
      break;
    case 0b110:
      return std::optional(OR(KIND_OR, insn));
    case 0b111:
      return std::optional(AND(KIND_AND, insn));
  }
  return std::optional<RTypeInstruction>();
}

std::optional<ITypeInstruction> RV32IDecoder::decodeIType(
    std::uint32_t insn, std::uint32_t opcode) {
  std::uint32_t funct3 = (insn >> 12) & 0b111;
  switch (opcode) {
    case 0b1100111:
      return std::optional(JALR(KIND_JALR, insn));
    case 0b0000011:
      switch (funct3) {
        case 0b000:
          return std::optional(LB(KIND_LB, insn));
        case 0b001:
          return std::optional(LH(KIND_LH, insn));
        case 0b010:
          return std::optional(LW(KIND_LW, insn));
        case 0b100:
          return std::optional(LBU(KIND_LBU, insn));
        case 0b101:
          return std::optional(LHU(KIND_LHU, insn));
      }
      break;
    case 0b0010011:
      switch (funct3) {
        case 0b000:
          return std::optional(ADDI(KIND_ADDI, insn));
        case 0b010:
          return std::optional(SLTI(KIND_SLTI, insn));
        case 0b011:
          return std::optional(SLTIU(KIND_SLTIU, insn));
        case 0b100:
          return std::optional(XORI(KIND_XORI, insn));
        case 0b110:
          return std::optional(ORI(KIND_ORI, insn));
        case 0b111:
          return std::optional(ANDI(KIND_ANDI, insn));
      }
    case 0b0001111:
      return std::optional(FENCE(KIND_FENCE, insn));
    case 0b1110011: {
      std::uint32_t imm = (insn >> 20) && 0x1111111;
      if (imm) {
        return std::optional(EBREAK(KIND_EBREAK, insn));
      }
      return std::optional(ECALL(KIND_ECALL, insn));
    }
  }
  return std::optional<ITypeInstruction>();
}

std::optional<STypeInstruction> RV32IDecoder::decodeSType(
    std::uint32_t insn, std::uint32_t opcode) {
  return std::optional<STypeInstruction>();
}

std::optional<BTypeInstruction> RV32IDecoder::decodeBType(
    std::uint32_t insn, std::uint32_t opcode) {
  return std::optional<BTypeInstruction>();
}

std::optional<UTypeInstruction> RV32IDecoder::decodeUType(
    std::uint32_t insn, std::uint32_t opcode) {
  return std::optional<UTypeInstruction>();
}

std::optional<JTypeInstruction> RV32IDecoder::decodeJType(
    std::uint32_t insn, std::uint32_t opcode) {
  return std::optional<JTypeInstruction>();
}
