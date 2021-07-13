#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include "decoder_hooks.h"

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
