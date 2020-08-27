project(agl CXX ASM)

add_library(agl OBJECT
  include/agl/Utils/aglAtomicPtrArray.h
  include/agl/Utils/aglParameter.h
  include/agl/Utils/aglParameterStringMgr.h
  src/Utils/aglAtomicPtrArray.cpp
  src/Utils/aglParameter.cpp
  src/Utils/aglParameterStringMgr.cpp
)

target_compile_options(agl PRIVATE -fno-exceptions)
target_compile_options(agl PRIVATE -fno-strict-aliasing)
target_compile_options(agl PRIVATE -Wno-invalid-offsetof)
target_include_directories(agl PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(agl PUBLIC sead)
