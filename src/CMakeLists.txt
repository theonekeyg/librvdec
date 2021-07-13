add_library(rvdec riscv_decode.c riscv_insn.c)

set_target_properties(rvdec
  PROPERTIES PUBLIC_HEADER "${rvdec_headers}"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)
install(TARGETS rvdec
  LIBRARY DESTINATION ${LIBDIR}
)
