#ifndef RISCV_DECODE_H
#define RISCV_DECODE_H

#include "riscv_insn.hpp"
#include <vector>
#include <optional>

#define USE_RV32I 0x1
#define USE_RV64I 0x2

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

enum DecoderTypes {
  RV32I,
  RV64I
};
/* I think this is a wrong solution to represent different types as one argument,
 * this is a temporary solution which should consider to be changed to
 * something more appropriate */
class GenericDecoder : public BaseRISCVDecoder {
public:
  int type;
  union decoders {
    RV32IDecoder rv32i;
    RV64IDecoder rv64i;

    decoders() = default;
    ~decoders() {};
  } decs;

  GenericDecoder(int type) : type(type) {};

  std::optional<RTypeInstruction> decodeRType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeRType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeRType(insn, opcode);
    }
    return std::optional<RTypeInstruction>();
  }
  std::optional<ITypeInstruction> decodeIType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeIType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeIType(insn, opcode);
    }
    return std::optional<ITypeInstruction>();
  }
  std::optional<STypeInstruction> decodeSType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeSType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeSType(insn, opcode);
    }
    return std::optional<STypeInstruction>();
  }
  std::optional<BTypeInstruction> decodeBType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeBType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeBType(insn, opcode);
    }
    return std::optional<BTypeInstruction>();
  }
  std::optional<UTypeInstruction> decodeUType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeUType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeUType(insn, opcode);
    }
    return std::optional<UTypeInstruction>();
  }
  std::optional<JTypeInstruction> decodeJType(std::uint32_t insn, std::uint32_t opcode) {
    switch (type) {
      case RV32I:
        return decs.rv32i.decodeJType(insn, opcode);
      case RV64I:
        return decs.rv64i.decodeJType(insn, opcode);
    }
    return std::optional<JTypeInstruction>();
  }
};

class RISCVDecoder : public BaseRISCVDecoder {
private:
  std::vector<GenericDecoder> decoders;

public:
  RISCVDecoder(std::uint32_t decoderMask) {
    if (decoderMask & USE_RV64I) {
      decoders.push_back(GenericDecoder{RV32I});
      decoders.push_back(GenericDecoder{RV64I});
    }
    else if (decoderMask & USE_RV32I) {
      decoders.push_back(GenericDecoder{RV32I});
    }
  }

  RISCVInstruction decode(std::uint32_t insn);
};

#endif // RISCV_DECODE_H
