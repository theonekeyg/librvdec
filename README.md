# librvdec - Library for decoding RISC-V ISA.

Here is the [manual](https://github.com/theonekeyg/librvdec/wiki/riscv-spec-20191213.pdf)
that was used for implementing the ISA standard.

**Currently only RV32I, RV64I, RV32M and RV64M instruction sets are implemented.**

## Installation

The library provides a way of selecting which instruction sets should be
supported for decoding. Simply comment unwanted instruction sets in `config.h`,
or just use all instruction sets, which is the default.

Clone the repo.

`$ git clone https://github.com/theonekeyg/librvdec.git`

Invoke cmake.

`$ mkdir build && cd build && cmake ..`

Compile and install the library.

`$ make && make install`

Tests are not built by default. To compile and run testsuite:

`$ cd build/test && make && make test`

## Usage

To decode an instruction, simply use
```c
int riscv_decode(struct riscv_insn *, uint32_t)
```
It will check if the
passed instruction belongs to one of the supported instruction sets. If it does,
it parses the instruction, sets the appropriate `riscv_insn` fields and returns
it's kind, otherwise it just returns `RVINSN_ILLEGAL`.

Example usage:

```c
#include <assert.h>
#include <rvdec/decode.h>
#include <rvdec/instruction.h>
#include <rvdec/register.h>

int main() {
  struct riscv_insn ins;

  if (riscv_decode(&ins, /* addi a5,s0,-200 */ 0xf3840793) != RVINSN_ILLEGAL) {
    assert(ins.kind == RVINSN_ADDI);
    assert(ins.i.imm == -200);
    assert(ins.i.rd == RVREG_a5);
    assert(ins.i.rs1 == RVREG_s0);
  } else {
    printf("ILLEGAL INSTRUCTION\n");
    return 1;
  }

  return 0;
}
```

## Forking

The library was designed with a goal to make adding/modifying instruction
sets (and instruction types) as easy as possible. Which also makes it easy to
fork the library to add specific RISC-V extensions, or reuse the design for
other ISAs.

I can write a more complete guideline for such integrations, so if you're
interested in forking the library for your needs, feel free to open the issue on
[github](https://github.com/theonekeyg/librvdec), so I'll know there is demand for it.
