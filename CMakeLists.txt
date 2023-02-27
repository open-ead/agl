project(agl CXX ASM)

add_library(agl OBJECT
  include/common/aglDisplayList.h
  include/common/aglDrawContext.h
  include/common/aglGPUCommon.hpp
  include/common/aglGPUMemAddr.h
  include/common/aglGPUMemBlock.h
  include/common/aglRenderBuffer.h
  include/common/aglRenderTarget.h
  include/common/aglResBinaryShaderArchive.h
  include/common/aglResBinaryShaderProgram.h
  include/common/aglResCommon.h
  include/common/aglResShaderArchive.h
  include/common/aglResShaderBinary.h
  include/common/aglResShaderMacro.h
  include/common/aglResShaderProgram.h
  include/common/aglResShaderSource.h
  include/common/aglResShaderSymbol.h
  include/common/aglResShaderVariation.h
  include/common/aglShader.h
  include/common/aglShaderCompileInfo.h
  include/common/aglShaderEnum.h
  include/common/aglShaderProgram.h
  include/common/aglShaderProgramArchive.h
  include/common/aglTextureData.h
  include/common/aglTextureDataSerializer.h
  include/common/aglTextureEnum.h

  include/detail/aglFileIOMgr.h
  include/detail/aglGPUMemBlockMgr.h
  include/detail/aglMemoryPoolHeap.h
  include/detail/aglPrivateResource.h
  include/detail/aglShaderHolder.h
  include/detail/aglSurface.h

  include/driver/aglGraphicsDriverMgr.h
  include/driver/aglNVNMgr.h
  include/driver/aglNVNimage.h
  include/driver/aglNVNsampler.h
  include/driver/aglNVNtexture.h

  include/environment/aglEnvObj.h
  include/environment/aglEnvObjBuffer.h
  include/environment/aglEnvObjMgr.h
  include/environment/aglEnvObjSetMgr.h
  include/environment/aglFog.h
  include/environment/aglLight.h
  include/environment/aglProjector.h

  include/effect/aglFxOfxLensFlare.h

  include/g3d/aglNW4FToNN.h

  include/postfx/aglBloom.h
  include/postfx/aglDepthOfField.h

  include/shader_text/aglShaderTextClause.h
  include/shader_text/aglShaderTextDefineLinker.h
  include/shader_text/aglShaderTextExpressionEvaluator.h
  include/shader_text/aglShaderTextLexer.h
  include/shader_text/aglShaderTextPreprocessor.h
  include/shader_text/aglShaderTextSyntaxTree.h

  include/utility/aglAtomicPtrArray.h
  include/utility/aglDevTools.h
  include/utility/aglParameter.h
  include/utility/aglParameterCurve.hpp
  include/utility/aglParameterIO.h
  include/utility/aglParameterList.h
  include/utility/aglParameterObj.h
  include/utility/aglParameterStringMgr.h
  include/utility/aglResParameter.h
  include/utility/aglScreenShotMgr.h
  
  src/detail/aglGPUMemBlockMgr.cpp

  src/driver/aglGraphicsDriverMgr.cpp
  src/driver/aglNVNMgr.cpp

  src/utility/aglAtomicPtrArray.cpp
  src/utility/aglParameter.cpp
  src/utility/aglParameterIO.cpp
  src/utility/aglParameterList.cpp
  src/utility/aglParameterObj.cpp
  src/utility/aglParameterStringMgr.cpp
  src/utility/aglResParameter.cpp
  
  src/utility/common/aglResCommon.cpp
  src/utility/common/aglResShaderArchive.cpp
)

target_compile_options(agl PRIVATE -fno-exceptions)
target_compile_options(agl PRIVATE -fno-strict-aliasing)
target_compile_options(agl PRIVATE -Wno-invalid-offsetof)
target_include_directories(agl PUBLIC include/)

if(NOT TARGET sead)
  add_subdirectory(../sead)
endif()
target_link_libraries(agl PUBLIC sead)
