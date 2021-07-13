#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include "decoder_hooks.h"

static const enum InstructionType OPCODE_TYPES_TABLE[] = {
  /* 0b0000000 */ INSN_UNDEFINED,
  /* 0b0000001 */ INSN_UNDEFINED,
  /* 0b0000010 */ INSN_UNDEFINED,
  /* 0b0000011 */ INSN_I,
  /* 0b0000100 */ INSN_UNDEFINED,
  /* 0b0000101 */ INSN_UNDEFINED,
  /* 0b0000110 */ INSN_UNDEFINED,
  /* 0b0000111 */ INSN_UNDEFINED,
  /* 0b0001000 */ INSN_UNDEFINED,
  /* 0b0001001 */ INSN_UNDEFINED,
  /* 0b0001010 */ INSN_UNDEFINED,
  /* 0b0001011 */ INSN_UNDEFINED,
  /* 0b0001100 */ INSN_UNDEFINED,
  /* 0b0001101 */ INSN_UNDEFINED,
  /* 0b0001110 */ INSN_UNDEFINED,
  /* 0b0001111 */ INSN_I,
  /* 0b0010000 */ INSN_UNDEFINED,
  /* 0b0010001 */ INSN_UNDEFINED,
  /* 0b0010010 */ INSN_UNDEFINED,
  /* 0b0010011 */ INSN_I,
  /* 0b0010100 */ INSN_UNDEFINED,
  /* 0b0010101 */ INSN_UNDEFINED,
  /* 0b0010110 */ INSN_UNDEFINED,
  /* 0b0010111 */ INSN_U,
  /* 0b0011000 */ INSN_UNDEFINED,
  /* 0b0011001 */ INSN_UNDEFINED,
  /* 0b0011010 */ INSN_UNDEFINED,
  /* 0b0011011 */ INSN_I,
  /* 0b0011100 */ INSN_UNDEFINED,
  /* 0b0011101 */ INSN_UNDEFINED,
  /* 0b0011110 */ INSN_UNDEFINED,
  /* 0b0011111 */ INSN_UNDEFINED,
  /* 0b0100000 */ INSN_UNDEFINED,
  /* 0b0100001 */ INSN_UNDEFINED,
  /* 0b0100010 */ INSN_UNDEFINED,
  /* 0b0100011 */ INSN_S,
  /* 0b0100100 */ INSN_UNDEFINED,
  /* 0b0100101 */ INSN_UNDEFINED,
  /* 0b0100110 */ INSN_UNDEFINED,
  /* 0b0100111 */ INSN_UNDEFINED,
  /* 0b0101000 */ INSN_UNDEFINED,
  /* 0b0101001 */ INSN_UNDEFINED,
  /* 0b0101010 */ INSN_UNDEFINED,
  /* 0b0101011 */ INSN_UNDEFINED,
  /* 0b0101100 */ INSN_UNDEFINED,
  /* 0b0101101 */ INSN_UNDEFINED,
  /* 0b0101110 */ INSN_UNDEFINED,
  /* 0b0101111 */ INSN_UNDEFINED,
  /* 0b0110000 */ INSN_UNDEFINED,
  /* 0b0110001 */ INSN_UNDEFINED,
  /* 0b0110010 */ INSN_UNDEFINED,
  /* 0b0110011 */ INSN_R,
  /* 0b0110100 */ INSN_UNDEFINED,
  /* 0b0110101 */ INSN_UNDEFINED,
  /* 0b0110110 */ INSN_UNDEFINED,
  /* 0b0110111 */ INSN_U,
  /* 0b0111000 */ INSN_UNDEFINED,
  /* 0b0111001 */ INSN_UNDEFINED,
  /* 0b0111010 */ INSN_UNDEFINED,
  /* 0b0111011 */ INSN_R,
  /* 0b0111100 */ INSN_UNDEFINED,
  /* 0b0111101 */ INSN_UNDEFINED,
  /* 0b0111110 */ INSN_UNDEFINED,
  /* 0b0111111 */ INSN_UNDEFINED,
  /* 0b1000000 */ INSN_UNDEFINED,
  /* 0b1000001 */ INSN_UNDEFINED,
  /* 0b1000010 */ INSN_UNDEFINED,
  /* 0b1000011 */ INSN_UNDEFINED,
  /* 0b1000100 */ INSN_UNDEFINED,
  /* 0b1000101 */ INSN_UNDEFINED,
  /* 0b1000110 */ INSN_UNDEFINED,
  /* 0b1000111 */ INSN_UNDEFINED,
  /* 0b1001000 */ INSN_UNDEFINED,
  /* 0b1001001 */ INSN_UNDEFINED,
  /* 0b1001010 */ INSN_UNDEFINED,
  /* 0b1001011 */ INSN_UNDEFINED,
  /* 0b1001100 */ INSN_UNDEFINED,
  /* 0b1001101 */ INSN_UNDEFINED,
  /* 0b1001110 */ INSN_UNDEFINED,
  /* 0b1001111 */ INSN_UNDEFINED,
  /* 0b1010000 */ INSN_UNDEFINED,
  /* 0b1010001 */ INSN_UNDEFINED,
  /* 0b1010010 */ INSN_UNDEFINED,
  /* 0b1010011 */ INSN_UNDEFINED,
  /* 0b1010100 */ INSN_UNDEFINED,
  /* 0b1010101 */ INSN_UNDEFINED,
  /* 0b1010110 */ INSN_UNDEFINED,
  /* 0b1010111 */ INSN_UNDEFINED,
  /* 0b1011000 */ INSN_UNDEFINED,
  /* 0b1011001 */ INSN_UNDEFINED,
  /* 0b1011010 */ INSN_UNDEFINED,
  /* 0b1011011 */ INSN_UNDEFINED,
  /* 0b1011100 */ INSN_UNDEFINED,
  /* 0b1011101 */ INSN_UNDEFINED,
  /* 0b1011110 */ INSN_UNDEFINED,
  /* 0b1011111 */ INSN_UNDEFINED,
  /* 0b1100000 */ INSN_UNDEFINED,
  /* 0b1100001 */ INSN_UNDEFINED,
  /* 0b1100010 */ INSN_UNDEFINED,
  /* 0b1100011 */ INSN_B,
  /* 0b1100100 */ INSN_UNDEFINED,
  /* 0b1100101 */ INSN_UNDEFINED,
  /* 0b1100110 */ INSN_UNDEFINED,
  /* 0b1100111 */ INSN_I,
  /* 0b1101000 */ INSN_UNDEFINED,
  /* 0b1101001 */ INSN_UNDEFINED,
  /* 0b1101010 */ INSN_UNDEFINED,
  /* 0b1101011 */ INSN_UNDEFINED,
  /* 0b1101100 */ INSN_UNDEFINED,
  /* 0b1101101 */ INSN_UNDEFINED,
  /* 0b1101110 */ INSN_UNDEFINED,
  /* 0b1101111 */ INSN_J,
  /* 0b1110000 */ INSN_UNDEFINED,
  /* 0b1110001 */ INSN_UNDEFINED,
  /* 0b1110010 */ INSN_UNDEFINED,
  /* 0b1110011 */ INSN_I,
  /* 0b1110100 */ INSN_UNDEFINED,
  /* 0b1110101 */ INSN_UNDEFINED,
  /* 0b1110110 */ INSN_UNDEFINED,
  /* 0b1110111 */ INSN_UNDEFINED,
  /* 0b1111000 */ INSN_UNDEFINED,
  /* 0b1111001 */ INSN_UNDEFINED,
  /* 0b1111010 */ INSN_UNDEFINED,
  /* 0b1111011 */ INSN_UNDEFINED,
  /* 0b1111100 */ INSN_UNDEFINED,
  /* 0b1111101 */ INSN_UNDEFINED,
  /* 0b1111110 */ INSN_UNDEFINED,
  /* 0b1111111 */ INSN_UNDEFINED
};

int riscv_decode(struct riscv_insn *insn, uint32_t repr) {
  uint32_t opcode = repr & 0b1111111;
  switch (OPCODE_TYPES_TABLE[opcode]) {
    case INSN_R:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_r(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
    case INSN_I:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_i(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
    case INSN_S:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_s(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
    case INSN_B:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_b(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
    case INSN_U:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_u(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
    case INSN_J:
      for (int i = 0; i < sizeof(decoder_hooks) / sizeof(*decoder_hooks); ++i) {
        if (decoder_hooks[i].riscv_decode_j(insn, repr, opcode)) {
          return insn->kind;
        }
      }
      break;
  }
  insn->kind = KIND_ILLEGAL;
  return insn->kind;
}

int riscv_decode_rv32i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct7 = (repr >> 25) & 0b1111111;
  uint32_t funct3 = (repr >> 12) & 0b111;
  switch (funct3) {
    case 0:
      if (funct7 == 0b0000000) {
        riscv_decode_r(insn, KIND_ADD, repr, opcode);
        return 1;
      } else if (funct7 == 0b0100000) {
        riscv_decode_r(insn, KIND_SUB, repr, opcode);
        return 1;
      }
      break;
    case 0b001:
      riscv_decode_r(insn, KIND_SLL, repr, opcode);
      return 1;
    case 0b010:
      riscv_decode_r(insn, KIND_SLT, repr, opcode);
      return 1;
    case 0b011:
      riscv_decode_r(insn, KIND_SLTU, repr, opcode);
      return 1;
    case 0b100:
      riscv_decode_r(insn, KIND_XOR, repr, opcode);
      return 1;
    case 0b101:
      if (funct7 == 0b0000000) {
        riscv_decode_r(insn, KIND_SRL, repr, opcode);
        return 1;
      } else if (funct7 == 0b0100000) {
        riscv_decode_r(insn, KIND_SRA, repr, opcode);
        return 1;
      }
      break;
    case 0b110:
      riscv_decode_r(insn, KIND_OR, repr, opcode);
      return 1;
    case 0b111:
      riscv_decode_r(insn, KIND_AND, repr, opcode);
      return 1;
  }
  return 0;
}

int riscv_decode_rv32i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 12) & 0b111;
  switch (opcode) {
    case 0b1100111:
      riscv_decode_i(insn, KIND_JALR, repr, opcode);
      return 1;
    case 0b0000011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, KIND_LB, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i(insn, KIND_LH, repr, opcode);
          return 1;
        case 0b010:
          riscv_decode_i(insn, KIND_LW, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_i(insn, KIND_LBU, repr, opcode);
          return 1;
        case 0b101:
          riscv_decode_i(insn, KIND_LHU, repr, opcode);
          return 1;
      }
      break;
    case 0b0010011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, KIND_ADDI, repr, opcode);
          return 1;
        case 0b010:
          riscv_decode_i(insn, KIND_SLTI, repr, opcode);
          return 1;
        case 0b011:
          riscv_decode_i(insn, KIND_SLTIU, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_i(insn, KIND_XORI, repr, opcode);
          return 1;
        case 0b110:
          riscv_decode_i(insn, KIND_ORI, repr, opcode);
          return 1;
        case 0b111:
          riscv_decode_i(insn, KIND_ANDI, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i_shamt(insn, KIND_SLLI, repr, opcode, 5);
          return 1;
        case 0b101:
          {
            uint32_t funct7 = (repr >> 25) & 0b1111111;
            if (funct7 == 0) {
              riscv_decode_i_shamt(insn, KIND_SRLI, repr, opcode, 5);
            } else {
              riscv_decode_i_shamt(insn, KIND_SRAI, repr, opcode, 5);
            }
            return 1;
          }
      }
      break;
    case 0b0001111:
      riscv_decode_i(insn, KIND_FENCE, repr, opcode);
      return 1;
    case 0b1110011: {
      uint32_t funct7 = (repr >> 20) & 0b1111111;
      if (funct7 == 0) {
        riscv_decode_i(insn, KIND_ECALL, repr, opcode);
        return 1;
      } else if (funct7 == 1) {
        riscv_decode_i(insn, KIND_EBREAK, repr, opcode);
        return 1;
      }
      break;
    }
  }
  return 0;
}

int riscv_decode_rv32i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0100011) {
    uint32_t funct3 = (repr >> 12) & 0b111;
    switch (funct3) {
      case 0b000:
        riscv_decode_s(insn, KIND_SB, repr, opcode);
        return 1;
      case 0b001:
        riscv_decode_s(insn, KIND_SH, repr, opcode);
        return 1;
      case 0b010:
        riscv_decode_s(insn, KIND_SW, repr, opcode);
        return 1;
    }
  }
  return 0;
}

int riscv_decode_rv32i_b(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b1100011) {
    uint32_t funct3 = (repr >> 12) & 0b111;
    switch (funct3) {
      case 0b000:
        riscv_decode_b(insn, KIND_BEQ, repr, opcode);
        return 1;
      case 0b001:
        riscv_decode_b(insn, KIND_BNE, repr, opcode);
        return 1;
      case 0b100:
        riscv_decode_b(insn, KIND_BLT, repr, opcode);
        return 1;
      case 0b101:
        riscv_decode_b(insn, KIND_BGE, repr, opcode);
        return 1;
      case 0b110:
        riscv_decode_b(insn, KIND_BLTU, repr, opcode);
        return 1;
      case 0b111:
        riscv_decode_b(insn, KIND_BGEU, repr, opcode);
        return 1;
    }
  }
  return 0;
}

int riscv_decode_rv32i_u(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  switch (opcode) {
    case 0b0110111:
      riscv_decode_u(insn, KIND_LUI, repr, opcode);
      return 1;
    case 0b0010111:
      riscv_decode_u(insn, KIND_AUIPC, repr, opcode);
      return 1;
  }
  return 0;
}

int riscv_decode_rv32i_j(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b1101111) {
    riscv_decode_j(insn, KIND_JAL, repr, opcode);
    return 1;
  }
  return 0;
}

int riscv_decode_rv64i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0111011) {
    uint32_t funct7 = (repr >> 25) & 0b1111111;
    uint32_t funct3 = (repr >> 12) & 0b111;
    switch (funct3) {
      case 0b000:
        if (funct7 == 0) {
          riscv_decode_r(insn, KIND_ADDW, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, KIND_SUBW, repr, opcode);
          return 1;
        }
        break;
      case 0b001:
        riscv_decode_r(insn, KIND_SLLW, repr, opcode);
        return 1;
      case 0b101:
        if (funct7 == 0) {
          riscv_decode_r(insn, KIND_SRLW, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, KIND_SRAW, repr, opcode);
          return 1;
        }
        break;
    }
  }
  return 0;
}

int riscv_decode_rv64i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 12) & 0b111;
  switch (opcode) {
    case 0b0000011:
      if (funct3 == 0b110) {
        riscv_decode_i(insn, KIND_LWU, repr, opcode);
        return 1;
      } else if (funct3 == 0b011) {
        riscv_decode_i(insn, KIND_LD, repr, opcode);
        return 1;
      }
      break;
    case 0b0010011:
      if (funct3 == 0b001) {
        riscv_decode_i_shamt(insn, KIND_SLLI, repr, opcode, 6);
        return 1;
      } else if (funct3 == 0b101) {
        uint32_t funct7 = (repr >> 25) & 0b1111111;
        if (funct7 == 0) {
          riscv_decode_i_shamt(insn, KIND_SRLI, repr, opcode, 6);
          return 1;
        } else if (funct7 == 0b010000) {
          riscv_decode_i_shamt(insn, KIND_SRAI, repr, opcode, 6);
          return 1;
        }
      }
      break;
    case 0b0011011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, KIND_ADDIW, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i_shamt(insn, KIND_SLLIW, repr, opcode, 5);
          return 1;
        case 0b101:
          {
            uint32_t funct7 = (repr >> 25) & 0b1111111;
            if (funct7 == 0) {
              riscv_decode_i_shamt(insn, KIND_SRLIW, repr, opcode, 5);
              return 1;
            } else if (funct7 == 0b0100000) {
              riscv_decode_i_shamt(insn, KIND_SRAIW, repr, opcode, 5);
              return 1;
            }
          }
          break;
      }
      break;
  }
  return 0;
}

int riscv_decode_rv64i_s(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0100011) {
    uint32_t funct3 = (repr >> 12) & 0b111;
    if (funct3 == 0b011) {
      riscv_decode_s(insn, KIND_SD, repr, opcode);
      return 1;
    }
  }
  return 0;
}
