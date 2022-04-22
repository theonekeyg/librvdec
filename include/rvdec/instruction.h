#ifndef RISCV_INSN_H
#define RISCV_INSN_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

enum InstructionType {
  INSN_UNDEFINED,
  INSN_R,
  INSN_I,
  INSN_S,
  INSN_B,
  INSN_U,
  INSN_J,
  INSN_FENCE
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
  "RVINSN_ILLEGAL"
};

struct riscv_insn {
  int type;
  int kind;
  bool is_compressed;
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


#ifdef SUPPORT_COMPRESSED

/* CR (Register) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * |   funct4     |    rd/rs1     |    rs2      |  op  |
 * -----------------------------------------------------
 */
    struct cr {
      uint32_t funct3 : 4;
      uint32_t rd : 5;
      uint32_t rs2 : 5;
      uint32_t op : 2;
    } cr;

/* CI (Immediate) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |imm |    rd/rs1     |    imm      |  op  |
 * -----------------------------------------------------
 */
    struct ci {
      uint32_t funct3 : 3;
      int32_t imm : 6;
      uint32_t rd : 5;
      uint32_t op : 2;
    } ci;

/* CSS (Stack-relative Store) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |       imm          |    rs2      |  op  |
 * -----------------------------------------------------
 */
    struct css {
      uint32_t funct3 : 3;
      int32_t imm : 6;
      uint32_t rs2 : 5;
      uint32_t op : 2;
    } css;

/* CIW (Wide Immediate) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |           imm            |  rd'  |  op  |
 * -----------------------------------------------------
 */
    struct ciw {
      uint32_t funct3 : 3;
      int32_t imm : 8;
      uint32_t rd : 3;
      uint32_t op : 2;
    } ciw;

/* CL (Load) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |    imm     |  rs1' | imm |  rd'  |  op  |
 * -----------------------------------------------------
 */
    struct cl {
      uint32_t funct3 : 3;
      int32_t imm : 5;
      uint32_t rs1 : 3;
      uint32_t rd : 3;
      uint32_t op : 2;
    } cl;

/* CS (Store) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |    imm     |  rs1' | imm |  rs2' |  op  |
 * -----------------------------------------------------
 */
    struct cs {
      uint32_t funct3 : 3;
      int32_t imm : 5;
      uint32_t rs1 : 3;
      uint32_t rs2 : 3;
      uint32_t op : 2;
    } cs;

/* CA (Arithmetic) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * |        funct6        |rd/rs1'|func2|  rs2' |  op  |
 * -----------------------------------------------------
 */
    struct ca {
      uint32_t funct6 : 6;
      uint32_t rd : 3;
      uint32_t funct2 : 2;
      uint32_t rs2 : 3;
      uint32_t op : 2;
    } ca;

/* CB (Branch) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |   offset   |  rs1' |   offset    |  op  |
 * -----------------------------------------------------
 */
    struct cb {
      uint32_t funct3 : 3;
      uint32_t offset : 8;
      uint32_t rs1 : 3;
      uint32_t op : 2;
    } cb;

/* CJ (Jump) Type Instruction
 *  15 14 13   12   11 10   9 8 7   6 5   4 3 2   1  0
 * -----------------------------------------------------
 * | funct3  |           jump target            |  op  |
 * -----------------------------------------------------
 */
    struct cj {
      uint32_t funct3 : 3;
      uint32_t target : 11;
      uint32_t op : 2;
    } cj;

#endif // SUPPORT_COMPRESSED

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

#ifdef __cplusplus
}
#endif

#endif // RISCV_INSN_H
