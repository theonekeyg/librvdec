add_library(riscv_decoder_libs riscv_decode.cpp riscv_insn.cpp)
# target_compile_options(riscv_decoder_libs PUBLIC -fno-rtti)
set_target_properties(riscv_decoder_libs PROPERTIES LINKER_LANGUAGE CXX)
