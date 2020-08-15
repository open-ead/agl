project(agl CXX ASM)

add_library(agl OBJECT
  include/agl/Utils/aglParameter.h
  src/Utils/aglParameter.cpp
)

target_compile_options(agl PRIVATE -fno-exceptions)
target_compile_options(agl PRIVATE -Wno-invalid-offsetof)
target_include_directories(agl PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(agl PUBLIC sead)
