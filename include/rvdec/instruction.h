#ifndef RISCV_INSN_H
#define RISCV_INSN_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum InstructionType {
  INSN_R,
  INSN_I,
  INSN_S,
  INSN_B,
  INSN_U,
  INSN_J,
  INSN_UNDEFINED
};

#define INSN(insn, type) RVINSN_##insn,
#define INSN_REDECL(insn, type)
#define CUSTOM_ABI_INSN(insn, type) RVINSN_##insn,
enum RISCVKindInstruction {
#include "insn_set_defs/rv32i.def"
#include "insn_set_defs/rv64i.def"
#include "insn_set_defs/rv32m.def"
#include "insn_set_defs/rv64m.def"
#undef INSN
#undef CUSTOM_ABI_INSN
  RVINSN_ILLEGAL
};

#define INSN(insn, type) #insn,
#define INSN_REDECL(insn, type)
#define CUSTOM_ABI_INSN(insn, type) #insn,
static const char *riscv_kind_names[] = {
#include "insn_set_defs/rv32i.def"
#include "insn_set_defs/rv64i.def"
#include "insn_set_defs/rv32m.def"
#include "insn_set_defs/rv64m.def"
#undef INSN
#undef CUSTOM_ABI_INSN
};

struct riscv_insn {
  int type;
  int kind;
  union {
/* R Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * |    funct7     |  rs2  |  rs1  |  funct3  |      rd      | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      uint32_t funct7 : 7;
      uint32_t rs2 : 5;
      uint32_t rs1 : 5;
      uint32_t funct3 : 3;
      uint32_t rd : 5;
      uint32_t opcode : 7;
    } r;
/* I Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * |       imm[11:0]       |  rs1  |  funct3  |      rd      | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      int32_t imm : 12;
      uint32_t rs1 : 5;
      uint32_t funct3 : 3;
      uint32_t rd : 5;
      uint32_t opcode : 7;
    } i;
/* S Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * |   imm[11:5]   |  rs2  |  rs1  |  funct3  |   imm[4:0]   | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      int32_t imm : 12;
      uint32_t rs2 : 5;
      uint32_t rs1 : 5;
      uint32_t funct3 : 3;
      uint32_t opcode : 7;
    } s;
/* B Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * | imm[12][10:5] |  rs2  |  rs1  |  funct3  | imm[4:1][11] | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      int32_t imm : 12;
      uint32_t rs2 : 5;
      uint32_t rs1 : 5;
      uint32_t funct3 : 3;
      uint32_t opcode : 7;
    } b;
/* U Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * |                imm[31:12]                |      rd      | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      int32_t imm : 20;
      uint32_t rd : 5;
      uint32_t opcode : 7;
    } u;
/* J Type Instruction
 *  31           25 24   20 19   15 14      12 11           7 6      0
 * --------------------------------------------------------------------
 * |         imm[20][10:1][11][19:12]         |      rd      | opcode |
 * --------------------------------------------------------------------
 */
    struct {
      int32_t imm : 20;
      uint32_t rd : 5;
      uint32_t opcode : 7;
    } j;

    /* The latter structures are meant to be used to specific ABI instructions.
     * Handling them this way may not be ideal, as it requires to have
     * separate structure for each weird instruction and some of
     * the RISCV extensions are full of them. */

    struct {
      uint32_t fm : 4;
      uint32_t pred : 4;
      uint32_t succ : 4;
      uint32_t rs1 : 5;
      uint32_t funct3 : 3;
      uint32_t rd : 5;
      uint32_t opcode : 7;
    } fence;

  };
};

void riscv_decode_r(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_i(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_i_shamt(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode, int shamt_bits_size);
void riscv_decode_s(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_b(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_u(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_j(struct riscv_insn *insn, int kind, uint32_t repr,
    uint32_t opcode);
void riscv_decode_fence(struct riscv_insn *insn, uint32_t repr, uint32_t opcode);

#ifdef __cplusplus
}
#endif

#endif // RISCV_INSN_H
