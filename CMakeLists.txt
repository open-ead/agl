project(agl CXX ASM)

add_library(agl OBJECT
  include/agl/aglDisplayList.h
  include/agl/aglDrawContext.h
  include/agl/aglRenderBuffer.h
  include/agl/aglRenderTargetColor.h
  include/agl/aglRenderTargetDepth.h
  include/agl/aglTextureData.h
  include/agl/gpu.h
  include/agl/util.h
  include/agl/detail/aglFileIOMgr.h
  include/agl/detail/aglMemoryPool.h
  include/agl/detail/aglMemoryPoolHeap.h
  include/agl/detail/aglShaderHolder.h
  include/agl/detail/aglSurface.h
  include/agl/driver/aglNVNimage.h
  include/agl/driver/aglNVNsampler.h
  include/agl/driver/aglNVNtexture.h
  include/agl/shader/aglShader.h
  include/agl/shader/aglShaderCompileInfo.h
  include/agl/shader/aglShaderProgram.h
  include/agl/shader/aglShaderProgramArchive.h
  include/agl/shtxt/aglClause.h
  include/agl/shtxt/aglDefineLinker.h
  include/agl/shtxt/aglExpressionEvaluator.h
  include/agl/shtxt/aglLexer.h
  include/agl/shtxt/aglPreprocessor.h
  include/agl/shtxt/aglSyntaxTree.h
  include/agl/Utils/aglAtomicPtrArray.h
  include/agl/Utils/aglParameter.h
  include/agl/Utils/aglParameterCurve.hpp
  include/agl/Utils/aglParameterIO.h
  include/agl/Utils/aglParameterList.h
  include/agl/Utils/aglParameterObj.h
  include/agl/Utils/aglParameterStringMgr.h
  include/agl/Utils/aglResCommon.h
  include/agl/Utils/aglResParameter.h
  src/Utils/aglAtomicPtrArray.cpp
  src/Utils/aglParameter.cpp
  src/Utils/aglParameterIO.cpp
  src/Utils/aglParameterList.cpp
  src/Utils/aglParameterObj.cpp
  src/Utils/aglParameterStringMgr.cpp
  src/Utils/aglResCommon.cpp
  src/Utils/aglResParameter.cpp

  src/stub.cpp
)

target_compile_options(agl PRIVATE -fno-exceptions)
target_compile_options(agl PRIVATE -fno-strict-aliasing)
target_compile_options(agl PRIVATE -Wno-invalid-offsetof)
target_include_directories(agl PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(agl PUBLIC sead)
