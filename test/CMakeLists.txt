include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(riscv_decoder_test
  test_rtype.cpp
  test_itype.cpp
  test_stype.cpp
  test_btype.cpp
  test_utype.cpp
  test_jtype.cpp
)

target_link_libraries(riscv_decoder_test gtest_main)
target_link_libraries(riscv_decoder_test rvdec)

include(GoogleTest)
gtest_discover_tests(riscv_decoder_test)
