project(agl CXX ASM)

add_library(agl OBJECT
  include/aglGPUCommon.hpp

  include/common/aglDisplayList.h
  include/common/aglDrawContext.h
  include/common/aglGPUMemAddr.h
  include/common/aglGPUMemBlock.h
  include/common/aglRenderBuffer.h
  include/common/aglRenderTarget.h
  include/common/aglShader.h
  include/common/aglShaderCompileInfo.h
  include/common/aglShaderProgram.h
  include/common/aglShaderProgramArchive.h
  include/common/aglTextureData.h
  include/common/aglTextureEnum.h

  include/detail/aglFileIOMgr.h
  include/detail/aglGPUMemBlockMgr.h
  include/detail/aglMemoryPoolHeap.h
  include/detail/aglPrivateResource.h
  include/detail/aglSurface.h

  include/driver/aglGraphicsDriverMgr.h
  include/driver/aglNVNMgr.h
  include/driver/aglNVNimage.h
  include/driver/aglNVNsampler.h
  include/driver/aglNVNtexture.h

  include/env/aglEnvObj.h
  include/env/aglEnvObjBuffer.h
  include/env/aglEnvObjMgr.h
  include/env/aglEnvObjSetMgr.h
  include/env/aglFog.h
  include/env/aglLight.h
  include/env/aglProjector.h

  include/fx/aglFxOfxLensFlare.h

  include/g3d/aglNW4FToNN.h

  include/pfx/aglBloom.h
  include/pfx/aglDepthOfField.h

  include/shader_text/aglShaderTextClause.h
  include/shader_text/aglShaderTextDefineLinker.h
  include/shader_text/aglShaderTextExpressionEvaluator.h
  include/shader_text/aglShaderTextLexer.h
  include/shader_text/aglShaderTextPreprocessor.h
  include/shader_text/aglShaderTextSyntaxTree.h

  include/texture/aglTextureDataSerializer.h

  include/utl/aglAtomicPtrArray.h
  include/utl/aglParameter.h
  include/utl/aglParameterCurve.hpp
  include/utl/aglParameterIO.h
  include/utl/aglParameterList.h
  include/utl/aglParameterObj.h
  include/utl/aglParameterStringMgr.h
  include/utl/aglResCommon.h
  include/utl/aglResParameter.h
  include/utl/aglScreenShotMgr.h
  
  src/detail/aglGPUMemBlockMgr.cpp

  src/driver/aglGraphicsDriverMgr.cpp
  src/driver/aglNVNMgr.cpp

  src/utl/aglAtomicPtrArray.cpp
  src/utl/aglParameter.cpp
  src/utl/aglParameterIO.cpp
  src/utl/aglParameterList.cpp
  src/utl/aglParameterObj.cpp
  src/utl/aglParameterStringMgr.cpp
  src/utl/aglResCommon.cpp
  src/utl/aglResParameter.cpp
)

target_compile_options(agl PRIVATE -fno-exceptions)
target_compile_options(agl PRIVATE -fno-strict-aliasing)
target_compile_options(agl PRIVATE -Wno-invalid-offsetof)
target_include_directories(agl PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(agl PUBLIC sead)
