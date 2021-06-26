#ifndef RISCV_DECODE_H
#define RISCV_DECODE_H

#include "riscv_insn.hpp"
#include <vector>
#include <optional>

#define USE_RV32I 0x1
#define USE_RV64I 0x3

class BaseRISCVDecoder {
public:
  std::optional<RTypeInstruction> decodeRType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<RTypeInstruction>(); };
  std::optional<ITypeInstruction> decodeIType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<ITypeInstruction>(); };
  std::optional<STypeInstruction> decodeSType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<STypeInstruction>(); };
  std::optional<BTypeInstruction> decodeBType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<BTypeInstruction>(); };
  std::optional<UTypeInstruction> decodeUType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<UTypeInstruction>(); };
  std::optional<JTypeInstruction> decodeJType(std::uint32_t insn, std::uint32_t opcode)
      { return std::optional<JTypeInstruction>(); };
};

class RISCVDecoder : public BaseRISCVDecoder {
private:
  std::vector<BaseRISCVDecoder> decoders;

public:
  RISCVDecoder(std::uint32_t &decoderMask);
  RISCVDecoder(std::initializer_list<BaseRISCVDecoder> decoders)
    : decoders(decoders) {};
  RISCVDecoder(std::vector<BaseRISCVDecoder> &&decoders)
    : decoders(std::move(decoders)) {};

  RISCVInstruction decode(std::uint32_t insn);
};

#define INSN(insn, type) class insn : public type { using type::type; };
#define CUSTOM_ABI_INSN(insn, type) class insn : public type { using type::type; };

class RV32IDecoder : public BaseRISCVDecoder {
public:
#include "insn_set_defs/rv32i.def"
#undef INSN
#undef CUSTOM_ABI_INSN

  std::optional<RTypeInstruction> decodeRType(std::uint32_t insn, std::uint32_t opcode);
  std::optional<ITypeInstruction> decodeIType(std::uint32_t insn, std::uint32_t opcode);
  std::optional<STypeInstruction> decodeSType(std::uint32_t insn, std::uint32_t opcode);
  std::optional<BTypeInstruction> decodeBType(std::uint32_t insn, std::uint32_t opcode);
  std::optional<UTypeInstruction> decodeUType(std::uint32_t insn, std::uint32_t opcode);
  std::optional<JTypeInstruction> decodeJType(std::uint32_t insn, std::uint32_t opcode);
};

class RV64IDecoder : public BaseRISCVDecoder {
};

#endif // RISCV_DECODE_H
