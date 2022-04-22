#include "config.h"

#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

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

#ifdef SUPPORT_COMPRESSED

  if (rvc_decode(insn, (repr >> 16) & 0xffff) != RVINSN_ILLEGAL) {
    return insn->kind;
  }

#endif // SUPPORT_COMPRESSED

  insn->kind = RVINSN_ILLEGAL;
  return insn->kind;
}

int riscv_decode_rv32i_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0110011) {
    uint32_t funct7 = (repr >> 25) & 0b1111111;
    uint32_t funct3 = (repr >> 12) & 0b111;
    switch (funct3) {
      case 0:
        if (funct7 == 0b0000000) {
          riscv_decode_r(insn, RVINSN_ADD, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, RVINSN_SUB, repr, opcode);
          return 1;
        }
        break;
      case 0b001:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_SLL, repr, opcode);
          return 1;
        }
        break;
      case 0b010:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_SLT, repr, opcode);
          return 1;
        }
        break;
      case 0b011:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_SLTU, repr, opcode);
          return 1;
        }
        break;
      case 0b100:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_XOR, repr, opcode);
          return 1;
        }
        break;
      case 0b101:
        if (funct7 == 0b0000000) {
          riscv_decode_r(insn, RVINSN_SRL, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, RVINSN_SRA, repr, opcode);
          return 1;
        }
        break;
      case 0b110:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_OR, repr, opcode);
          return 1;
        }
        break;
      case 0b111:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_AND, repr, opcode);
          return 1;
        }
        break;
    }
  }
  return 0;
}

int riscv_decode_rv32i_i(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 12) & 0b111;
  switch (opcode) {
    case 0b1100111:
      riscv_decode_i(insn, RVINSN_JALR, repr, opcode);
      return 1;
    case 0b0000011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, RVINSN_LB, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i(insn, RVINSN_LH, repr, opcode);
          return 1;
        case 0b010:
          riscv_decode_i(insn, RVINSN_LW, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_i(insn, RVINSN_LBU, repr, opcode);
          return 1;
        case 0b101:
          riscv_decode_i(insn, RVINSN_LHU, repr, opcode);
          return 1;
      }
      break;
    case 0b0010011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, RVINSN_ADDI, repr, opcode);
          return 1;
        case 0b010:
          riscv_decode_i(insn, RVINSN_SLTI, repr, opcode);
          return 1;
        case 0b011:
          riscv_decode_i(insn, RVINSN_SLTIU, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_i(insn, RVINSN_XORI, repr, opcode);
          return 1;
        case 0b110:
          riscv_decode_i(insn, RVINSN_ORI, repr, opcode);
          return 1;
        case 0b111:
          riscv_decode_i(insn, RVINSN_ANDI, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i_shamt(insn, RVINSN_SLLI, repr, opcode, 5);
          return 1;
        case 0b101:
          {
            uint32_t funct7 = (repr >> 25) & 0b1111111;
            if (funct7 == 0) {
              riscv_decode_i_shamt(insn, RVINSN_SRLI, repr, opcode, 5);
            } else {
              riscv_decode_i_shamt(insn, RVINSN_SRAI, repr, opcode, 5);
            }
            return 1;
          }
      }
      break;
    case 0b0001111:
      if(riscv_try_decode_fence(insn, repr, opcode)) {
        return 1;
      }
    case 0b1110011: {
      uint32_t funct7 = (repr >> 20) & 0b1111111;
      if (funct7 == 0) {
        riscv_decode_i(insn, RVINSN_ECALL, repr, opcode);
        return 1;
      } else if (funct7 == 1) {
        riscv_decode_i(insn, RVINSN_EBREAK, repr, opcode);
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
        riscv_decode_s(insn, RVINSN_SB, repr, opcode);
        return 1;
      case 0b001:
        riscv_decode_s(insn, RVINSN_SH, repr, opcode);
        return 1;
      case 0b010:
        riscv_decode_s(insn, RVINSN_SW, repr, opcode);
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
        riscv_decode_b(insn, RVINSN_BEQ, repr, opcode);
        return 1;
      case 0b001:
        riscv_decode_b(insn, RVINSN_BNE, repr, opcode);
        return 1;
      case 0b100:
        riscv_decode_b(insn, RVINSN_BLT, repr, opcode);
        return 1;
      case 0b101:
        riscv_decode_b(insn, RVINSN_BGE, repr, opcode);
        return 1;
      case 0b110:
        riscv_decode_b(insn, RVINSN_BLTU, repr, opcode);
        return 1;
      case 0b111:
        riscv_decode_b(insn, RVINSN_BGEU, repr, opcode);
        return 1;
    }
  }
  return 0;
}

int riscv_decode_rv32i_u(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  switch (opcode) {
    case 0b0110111:
      riscv_decode_u(insn, RVINSN_LUI, repr, opcode);
      return 1;
    case 0b0010111:
      riscv_decode_u(insn, RVINSN_AUIPC, repr, opcode);
      return 1;
  }
  return 0;
}

int riscv_decode_rv32i_j(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b1101111) {
    riscv_decode_j(insn, RVINSN_JAL, repr, opcode);
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
          riscv_decode_r(insn, RVINSN_ADDW, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, RVINSN_SUBW, repr, opcode);
          return 1;
        }
        break;
      case 0b001:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_SLLW, repr, opcode);
          return 1;
        }
        break;
      case 0b101:
        if (funct7 == 0) {
          riscv_decode_r(insn, RVINSN_SRLW, repr, opcode);
          return 1;
        } else if (funct7 == 0b0100000) {
          riscv_decode_r(insn, RVINSN_SRAW, repr, opcode);
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
        riscv_decode_i(insn, RVINSN_LWU, repr, opcode);
        return 1;
      } else if (funct3 == 0b011) {
        riscv_decode_i(insn, RVINSN_LD, repr, opcode);
        return 1;
      }
      break;
    case 0b0010011:
      if (funct3 == 0b001) {
        riscv_decode_i_shamt(insn, RVINSN_SLLI, repr, opcode, 6);
        return 1;
      } else if (funct3 == 0b101) {
        uint32_t funct7 = (repr >> 25) & 0b1111111;
        if (funct7 == 0) {
          riscv_decode_i_shamt(insn, RVINSN_SRLI, repr, opcode, 6);
          return 1;
        } else if (funct7 == 0b010000) {
          riscv_decode_i_shamt(insn, RVINSN_SRAI, repr, opcode, 6);
          return 1;
        }
      }
      break;
    case 0b0011011:
      switch (funct3) {
        case 0b000:
          riscv_decode_i(insn, RVINSN_ADDIW, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_i_shamt(insn, RVINSN_SLLIW, repr, opcode, 5);
          return 1;
        case 0b101:
          {
            uint32_t funct7 = (repr >> 25) & 0b1111111;
            if (funct7 == 0) {
              riscv_decode_i_shamt(insn, RVINSN_SRLIW, repr, opcode, 5);
              return 1;
            } else if (funct7 == 0b0100000) {
              riscv_decode_i_shamt(insn, RVINSN_SRAIW, repr, opcode, 5);
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
      riscv_decode_s(insn, RVINSN_SD, repr, opcode);
      return 1;
    }
  }
  return 0;
}

int riscv_decode_rv32m_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0110011) {
    uint32_t funct7 = (repr >> 25) & 0b1111111;
    if (funct7 == 1) {
      uint32_t funct3 = (repr >> 12) & 0b111;
      switch (funct3) {
        case 0b000:
          riscv_decode_r(insn, RVINSN_MUL, repr, opcode);
          return 1;
        case 0b001:
          riscv_decode_r(insn, RVINSN_MULH, repr, opcode);
          return 1;
        case 0b010:
          riscv_decode_r(insn, RVINSN_MULHSU, repr, opcode);
          return 1;
        case 0b011:
          riscv_decode_r(insn, RVINSN_MULHU, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_r(insn, RVINSN_DIV, repr, opcode);
          return 1;
        case 0b101:
          riscv_decode_r(insn, RVINSN_DIVU, repr, opcode);
          return 1;
        case 0b110:
          riscv_decode_r(insn, RVINSN_REM, repr, opcode);
          return 1;
        case 0b111:
          riscv_decode_r(insn, RVINSN_REMU, repr, opcode);
          return 1;
      }
    }
  }
  return 0;
}

int riscv_decode_rv64m_r(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  if (opcode == 0b0111011) {
    uint32_t funct7 = (repr >> 25) & 0b1111111;
    if (funct7 == 1) {
      uint32_t funct3 = (repr >> 12) & 0b111;
      switch (funct3) {
        case 0b000:
          riscv_decode_r(insn, RVINSN_MULW, repr, opcode);
          return 1;
        case 0b100:
          riscv_decode_r(insn, RVINSN_DIVW, repr, opcode);
          return 1;
        case 0b101:
          riscv_decode_r(insn, RVINSN_DIVUW, repr, opcode);
          return 1;
        case 0b110:
          riscv_decode_r(insn, RVINSN_REMW, repr, opcode);
          return 1;
        case 0b111:
          riscv_decode_r(insn, RVINSN_REMUW, repr, opcode);
          return 1;
      }
    }
  }
  return 0;
}

#ifdef SUPPORT_COMPRESSED

#define RVREG16(reg) (RVREG_s0 + reg)

inline static void riscv_init_r(
    struct riscv_insn *insn,
    int kind,
    uint32_t rs2,
    uint32_t rs1,
    uint32_t rd
) {
  insn->type = INSN_R;
  insn->kind = kind;
  insn->r.rs2 = rs2;
  insn->r.rs1 = rs1;
  insn->r.rd = rd;
}

inline static void riscv_init_i(
    struct riscv_insn *insn,
    int kind,
    uint32_t imm,
    uint32_t rs1,
    uint32_t rd
) {
  insn->type = INSN_I;
  insn->kind = kind;
  insn->i.imm = imm;
  insn->i.rs1 = rs1;
  insn->i.rd = rd;
}

inline static void riscv_init_s(
    struct riscv_insn *insn,
    int kind,
    uint32_t imm,
    uint32_t rs2,
    uint32_t rs1
) {
  insn->type = INSN_S;
  insn->kind = kind;
  insn->s.imm = imm;
  insn->s.rs2 = rs2;
  insn->s.rs1 = rs1;
}

inline static void riscv_init_b(
    struct riscv_insn *insn,
    int kind,
    uint32_t imm,
    uint32_t rs2,
    uint32_t rs1
) {
  insn->type = INSN_B;
  insn->kind = kind;
  insn->b.imm = imm;
  insn->b.rs2 = rs2;
  insn->b.rs1 = rs1;
}


inline static void riscv_init_u(
    struct riscv_insn *insn,
    int kind,
    uint32_t imm,
    uint32_t rd
) {
  insn->type = INSN_U;
  insn->kind = kind;
  insn->u.imm = imm;
  insn->u.rd = rd;
}

inline static void riscv_init_j(
    struct riscv_insn *insn,
    int kind,
    uint32_t imm
) {
  insn->type = INSN_J;
  insn->kind = kind;
  insn->j.imm = imm;
}

static inline int64_t sign_extend_to(int64_t value, int sign_bit_pos, int target_length) {
  // If value had negative bit set, sign-extend it to target length, otherwise it's a nop
  if (value & (1 << (sign_bit_pos))) {
    return ~((value ^ ~(0xffffffffffffffff << sign_bit_pos + 1)));
  }
  return value;
}

int rvc_decode(struct riscv_insn *insn, uint32_t repr) {
  if (repr == 0) {
    return RVINSN_ILLEGAL;
  }

  insn->is_compressed = true;
  uint8_t opcode = repr & 0b11;
  for (int i = 0; i < sizeof(decoder_hooks16) / sizeof(*decoder_hooks16); ++i) {
    if (decoder_hooks16[i].rvc_decode_cr(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_ci(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_css(insn, repr, opcode)) { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_ciw(insn, repr, opcode)) { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_cl(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_cs(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_ca(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_cb(insn, repr, opcode))  { return insn->kind; }
    if (decoder_hooks16[i].rvc_decode_cj(insn, repr, opcode))  { return insn->kind; }
  }

  insn->is_compressed = false;
  return RVINSN_ILLEGAL;
}

int rvc_decode_cr(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  /* uint32_t funct3 = (repr & (0b111 << 12)) >> 12; */
  uint32_t funct3 = (repr >> 13) & 0b111;
  uint32_t funct4 = (repr >> 12) & 1;
  switch (opcode) {
    case 0b10: {
      if (funct3 == 0b100) {
        // C.JR -> `jalr x0, 0(rs1)`
        // | C.JALR -> `jalr x1, 0(rs1)`
        // | C.MV -> `add rd, x0, rs2`
        // | C.ADD -> `add rd, rd, rs2`
        // | C.EBREAK -> `ebreak`
        uint32_t rs2 = (repr >> 2) & 0b11111;
        uint32_t rs1 = (repr >> 7) & 0b11111;

        if (rs1 == 0) {
          if (rs2 == 0 && funct4 == 0b1) {
            // C.EBREAK -> `ebreak`
            riscv_init_i(insn, RVINSN_EBREAK, 0, 0, 0);
            return 1;
          }
          break;
        }

        if (rs2 != 0) {
          if (funct4 == 0b1) {
            // C.ADD -> `add rd, rd, rs2`
            riscv_init_r(insn, RVINSN_ADD, rs2, /* rd */ rs1, /* rd */ rs1);
          } else {
            // C.MV -> `add rd, x0, rs2`
            riscv_init_r(insn, RVINSN_ADD, rs2, /* rs1 */ RVREG_zero, /* rd */ rs1);
          }
          return 1;
        }

        if (funct4 == 0b1) {
          // C.JALR -> `jalr x1, 0(rs1)`
          riscv_init_i(insn, RVINSN_JALR, 0, RVREG_ra, rs1);
        } else {
          // C.JR -> `jalr x0, 0(rs1)`
          riscv_init_i(insn, RVINSN_JALR, 0, RVREG_zero, rs1);
        }
        return 1;
      }
    }
  }
  return 0;
}

int rvc_decode_ci(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b01: {
      if (funct3 == 0b010) {
        // C.LI -> `addi rd, x0, imm[5:0]`
        uint32_t imm = (((repr >> 12) & 1) << 5) | ((repr >> 2) & 0b11111);
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0) {
          // Points to undefined HINT.
          break;
        }
        riscv_init_i(insn, RVINSN_ADDI, imm, /* rs1 */ RVREG_zero, /* rd */ rd);
        return 1;
      } else if (funct3 == 0b011) {
        // C.LUI -> `lui rd, nzimm[17:12]`
        // | C.ADDI16SP -> `addi x2, x2, nzimm[9:4]`
        uint32_t rd = (repr >> 7) & 0b11111;

        if (rd == 2) {
          // C.ADDI16SP -> `addi x2, x2, nzimm[9:4]`
          // TODO: This insrtuction has bit-shuffling in it's immediate,
          // need to implement it, right now it has junk in immediate.
          uint32_t imm = (((repr >> 6) & 1) |
             (((repr >> 2) & 1) << 1) |
             (((repr >> 5) & 1) << 2) |
             (((repr >> 3) & 0b11) << 3) |
             (((repr >> 12) & 1) << 5))
            << 4; // bitshit 4 is declared in abi
          riscv_init_i(insn, RVINSN_ADDI, imm, rd, rd);
          return 1;
        }

        uint32_t imm = (((repr >> 12) & 1) << 5) | ((repr >> 2) & 0b11111);
        if (rd == 0 || imm == 0) {
          // Points to undefined HINT.
          break;
        }

        riscv_init_u(insn, RVINSN_LUI, imm, rd);
        return 1;
      } else if (funct3 == 0b000) {
        // C.ADDI -> `addi rd, rd, nzimm[5:0]`
        // | C.NOP -> `addi x0, x0, 0`
        uint32_t imm = (((repr >> 12) & 1) << 5) | ((repr >> 2) & 0b11111);
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0 && imm == 0) {
          // C.NOP -> `addi x0, x0, 0`
          riscv_init_i(insn, RVINSN_ADDI, imm, rd, rd);
          return 1;
        }
        if (rd == 0 || imm == 0) {
          break;
        }
        riscv_init_i(insn, RVINSN_ADDI, sign_extend_to(imm, 5, 12), rd, rd);
        return 1;
      } else if (funct3 == 0b001) {
        // C.ADDIW -> `addiw rd,rd, imm[5:0]`, when imm == 0 -> `sext.w rd`
        uint32_t imm = (((repr >> 12) & 1) << 5) | ((repr >> 2) & 0b11111);
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0) {
          break;
        }
        riscv_init_i(insn, RVINSN_ADDIW, sign_extend_to(imm, 5, 12), rd, rd);
        return 1;
      }
    }
    case 0b10: {
      if (funct3 == 0b000) {
        // C.SLLI -> `slli rd, rd, shamt[5:0]`
        uint32_t shamt_5 = ((repr >> 12) & 1) << 5;
        uint32_t shamt =  shamt_5 | (((repr >> 2) & 0b11111) << 1);
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0 || shamt == 0) {
          break;
        }

        if (shamt_5 == 1) {
          // Reserved for custom extension
          break;
        }

        riscv_init_i(insn, RVINSN_SLLI, shamt, rd, rd);
        return 1;
      } else if (funct3 == 0b010) {
        // C.LWSP -> `lw rd, offset[7:2](x2)`
        uint32_t imm = ((repr >> 2) & 0b11) |
          (((repr >> 12) & 1) << 2) |
          (((repr >> 4) & 0b111) << 3);
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0) {
          break;
        }
        riscv_init_i(insn, RVINSN_LW, imm, rd, RVREG_sp);
        return 1;
      } else if (funct3 == 0b011) {
        // C.LDSP -> `ld rd, offset[8:3](x2)`
        uint32_t imm = (((repr >> 5) & 0b11) |
          (((repr >> 12) & 1) << 2) |
          (((repr >> 2) & 0b111) << 3)) << 3;
        uint32_t rd = (repr >> 7) & 0b11111;
        if (rd == 0) {
          break;
        }
        riscv_init_i(insn, RVINSN_LD, imm, rd, RVREG_sp);
        return 1;
      } else if (funct3 == 0b001) {
        // C.LQSP -> `lq rd, offset[9:4](x2)`
        // | C.FLDSP ->  `flw rd, offset[7:2](x2)`
        // TODO: Implement RV128I for lq instruction, for now just treat it like illegal instruction.
        // Future: if (rd == 0) {
        //   // Handle C.FLDSP -> `flw rd, offset[7:2](x2)`
        // }
        break;
      } else if (funct3 == 0b011) {
        // C.FLWSP -> `flw rd, offset[7:2](x2)`
        // TODO: implement RV32FC instruction set.
        break;
      }
    }
  }
  return 0;
}

int rvc_decode_css(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b10: {
      if (funct3 == 0b110) {
        // C.SWSP -> `sw rs2, offset[7:2](x2)`
        uint32_t rs2 = (repr >> 2) & 0b11111;
        uint32_t imm =
          (((repr >> 9) & 0b1111) |
          (((repr >> 7) & 0b11) << 4)) << 2;
        riscv_init_s(insn, RVINSN_SW, imm, rs2, RVREG_sp);
        return 1;
      } else if (funct3 == 0b111) {
        // C.SDSP -> `sd rs2, offset[8:3](x2)`
        // Also expands to in RV32I code:
        // C.FSWSP -> `fsw rs2, offset[7:2](x2)`
        // TODO: Implement RV32FC
        uint32_t rs2 = (repr >> 2) & 0b11111;
        uint32_t imm =
          (((repr >> 10) & 0b111) |
          (((repr >> 7) & 0b111) << 3)) << 3;
        riscv_init_s(insn, RVINSN_SD, imm, rs2, RVREG_sp);
        return 1;
      } else if (funct3 == 0b101) {
        // C.SQSP -> `sq rs2, offset[9:4](x2)`
        // TODO: Implement RV128I for sq instruction, for now just treat it like illegal instruction.
        // Also expands to in RV32I code:
        // C.FSDSP -> `fsd rs2, offset[8:3](x2)`
        // TODO: Implement RV32FC
      }
    }
  }
  return 0;
}

int rvc_decode_ciw(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b00: {
      if (funct3 == 0b000) {
        // C.ADDI4SPN -> `addi rd′, x2, nzuimm[9:2]`
        uint32_t rd = (repr >> 2) & 0b111;
        uint32_t imm =
          (((repr >> 6) & 1) |
          (((repr >> 5) & 1) << 1) |
          (((repr >> 11) & 0b11) << 2) |
          (((repr >> 7) & 0b1111) << 4)) << 2;
        riscv_init_i(insn, RVINSN_ADDI, imm, RVREG_sp, RVREG16(rd));
        return 1;
      }
    }
  }
  return 0;
}

int rvc_decode_cl(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b00: {
      if (funct3 == 0b010) {
        // C.LW -> `lw rd′, offset[6:2](rs1′)`
        uint32_t rd = (repr >> 2) & 0b111;
        uint32_t imm =
          (((repr >> 6) & 1) |
           (((repr >> 10) & 0b111) << 1) |
           (((repr >> 5) & 1) << 4)) << 2;
        uint32_t rs1 = (repr >> 7) & 0b111;
        riscv_init_i(insn, RVINSN_LW, imm, RVREG16(rs1), RVREG16(rd));
        return 1;
      } else if (funct3 == 0b011) {
        // C.LD -> `ld rd′, offset[7:3](rs1′)`
        // Also expands to in RV32I code:
        // C.FLW -> `flw rd′, offset[6:2](rs1′)`
        // TODO: Implement RV32FC
        uint32_t rd = (repr >> 2) & 0b111;
        uint32_t imm =
          (((repr >> 10) & 0b111) |
           (((repr >> 5) & 0b11) << 3)) << 3;
        uint32_t rs1 = (repr >> 7) & 0b111;
        riscv_init_i(insn, RVINSN_LD, imm, RVREG16(rs1), RVREG16(rd));
        return 1;
      } else if (funct3 == 0b001) {
        // C.LQ -> `lq rd′, offset[8:4](rs1′)`
        // TODO: Implement RV128I for lq instruction, for now just treat it like illegal instruction.
        // Also expands to in RV32I code:
        // C.FLD -> `fld rd′, offset[6:2](rs1′)`
        // TODO: Implement RV32FC
      }
    }
  }
  return 0;
}

int rvc_decode_cs(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b00: {
      if (funct3 == 0b110) {
        // C.SW -> `sw rs2′, offset[6:2](rs1′)`
        uint32_t rs2 = (repr >> 2) & 0b111;
        uint32_t imm =
          (((repr >> 6) & 1) |
          (((repr >> 10) & 0b111) << 1) |
          (((repr >> 5) & 1) << 4)) << 2;
        uint32_t rs1 = (repr >> 7) & 0b111;
        riscv_init_s(insn, RVINSN_SW, imm, RVREG16(rs2), RVREG16(rs1));
        return 1;
      } else if (funct3 == 0b111) {
        // C.SD -> `sd rs2′, offset[7:3](rs1′)`
        // Also expands to in RV32I code:
        // C.FSW -> `fsw rs2′, offset[6:2](rs1′)`
        // TODO: Implement RV32FC
        uint32_t rs2 = (repr >> 2) & 0b111;
        uint32_t imm =
          (((repr >> 10) & 0b111) |
          (((repr >> 5) & 0b11) << 3)) << 3;
        uint32_t rs1 = (repr >> 7) & 0b111;
        riscv_init_s(insn, RVINSN_SD, imm, RVREG16(rs2), RVREG16(rs1));
        return 1;
      } else if (funct3 == 0b101) {
        // C.SQ -> `sq rs2′, offset[8:4](rs1′)`
        // TODO: Implement RV128I for sq instruction, for now just treat it like illegal instruction.
        // Also expands to in RV32I code:
        // C.FSD -> `fsd rs2′,offset[7:3](rs1′)`
        // TODO: Implement RV32FC
      }
    }
  }
  return 0;
}

int rvc_decode_ca(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  uint32_t funct4 = (repr >> 12) & 1;
  uint32_t funct6 = (repr >> 10) & 0b11;
  switch (opcode) {
    case 0b01: {
      if (funct3 == 0b100) {
        // C.AND -> `and rd′, rd′, rs2′`
        // | C.OR -> `or rd′, rd′, rs2′`
        // | C.XOR -> `xor rd′, rd′, rs2′`
        // | C.SUB -> `sub rd′, rd′, rs2′`
        // | C.ADDW -> `addw rd′, rd′, rs2′`
        // | C.SUBW -> `subw rd′, rd′, rs2′`
        uint32_t funct2 = (repr >> 5) & 0b11;
        uint32_t rs1 = (repr >> 7) & 0b111; // Also `rd`
        uint32_t rs2 = (repr >> 2) & 0b111;
        if (funct6 == 0b11) {
          if (funct4 == 0b0) {
            if (funct2 == 0b11) {
              // C.AND -> `and rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_AND, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            } else if (funct2 == 0b10) {
              // C.OR -> `or rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_OR, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            } else if (funct2 == 0b01) {
              // C.XOR -> `xor rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_XOR, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            } else if (funct2 == 0b00) {
              // C.SUB -> `sub rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_SUB, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            }
          } else {
            if (funct2 == 0b01) {
              // C.ADDW -> `addw rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_ADDW, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            } else if (funct2 == 0b00) {
              // C.SUBW -> `subw rd′, rd′, rs2′`
              riscv_init_r(insn, RVINSN_SUBW, RVREG16(rs2), RVREG16(rs1), RVREG16(rs1));
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

int rvc_decode_cb(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b01: {
      if (funct3 == 0b110) {
        // C.BEQZ -> `beq rs1′, x0, offset[8:1]`
        uint32_t rs1 = (repr >> 7) & 0b111;
        uint32_t imm =
          (((repr >> 3) & 0b11) |
           (((repr >> 10) & 0b11) << 2) |
           (((repr >> 2) & 1) << 4) |
           (((repr >> 5) & 0b11) << 5) |
           (((repr >> 12) & 1) << 7)) << 1;
        riscv_init_b(insn, RVINSN_BEQ, imm, RVREG_zero, RVREG16(rs1));
        return 1;
      } else if (funct3 == 0b111) {
        // C.BNEZ -> `bne rs1′, x0, offset[8:1]`
        uint32_t rs1 = (repr >> 7) & 0b111;
        uint32_t imm =
          (((repr >> 3) & 0b11) |
           (((repr >> 10) & 0b11) << 2) |
           (((repr >> 2) & 1) << 4) |
           (((repr >> 5) & 0b11) << 5) |
           (((repr >> 12) & 1) << 7)) << 1;
        riscv_init_b(insn, RVINSN_BNE, imm, RVREG_zero, RVREG16(rs1));
        return 1;
      } else if (funct3 == 0b100) {
        // C.SRLI -> `srli rd′,rd′, shamt[5:0]`
        // | C.SRAI -> `srai rd′, rd′, shamt[5:0]`
        // | C.ANDI -> `andi rd′, rd′, imm[5:0]`
        uint32_t rd = ((repr >> 7) & 0b111);
        uint32_t shamt = ((repr >> 2) & 0b11111) | (((repr >> 12) & 1) << 5);
        uint32_t funct2 = (repr >> 10) & 0b11;
        if (funct2 == 0b00) {
          // C.SRLI -> srli rd′, rd′, shamt[5:0]
          riscv_init_i(insn, RVINSN_SRLI, shamt, RVREG16(rd), RVREG16(rd));
          return 1;
        } else if (funct2 == 0b01) {
          // C.SRAI -> srai rd′, rd′, shamt[5:0]
          riscv_init_i(insn, RVINSN_SRAI, shamt, RVREG16(rd), RVREG16(rd));
          return 1;
        } else if (funct2 == 0b10) {
          // C.ANDI -> andi rd′, rd′, imm[5:0]
          riscv_init_i(insn, RVINSN_ANDI, sign_extend_to(shamt, 5, 12), RVREG16(rd), RVREG16(rd));
          return 1;
        }
      }
    }
  }
  return 0;
}

int rvc_decode_cj(struct riscv_insn *insn, uint32_t repr, uint32_t opcode) {
  uint32_t funct3 = (repr >> 13) & 0b111;
  switch (opcode) {
    case 0b01: {
      if (funct3 == 0b101) {
        // C.J -> `jal x0, offset[11:1]`
        uint32_t imm =
          (((repr >> 3) & 0b111) |
           (((repr >> 11)  & 1) << 3) |
           (((repr >> 2)  & 1) << 4) |
           (((repr >> 7)  & 1) << 5) |
           (((repr >> 6)  & 1) << 6) |
           (((repr >> 9)  & 0b11) << 7) |
           (((repr >> 8) & 1) << 9) |
           (((repr >> 12) & 1) << 10)) << 1;
        riscv_init_j(insn, RVINSN_JAL, sign_extend_to(imm, 11, 20));
        return 1;
      } else if (funct3 == 0b001) {
        // C.JAL -> `jal x1, offset[11:1]`
        uint32_t imm =
          (((repr >> 3) & 0b111) |
           (((repr >> 11)  & 1) << 3) |
           (((repr >> 2)  & 1) << 4) |
           (((repr >> 7)  & 1) << 5) |
           (((repr >> 6)  & 1) << 6) |
           (((repr >> 9)  & 0b11) << 7) |
           (((repr >> 8) & 1) << 9) |
           (((repr >> 12) & 1) << 10));
        riscv_init_j(insn, RVINSN_JAL, sign_extend_to(imm, 11, 20));
        return 1;
      }
    }
  }
  return 0;
}

#endif // SUPPORT_COMPRESSED
