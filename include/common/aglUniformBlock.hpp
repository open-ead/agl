#pragma once

#include "common/aglDrawContext.h"
#include "driver/aglNVNMgr.h"

#ifndef AGL_COMMON_UNIFORMBLOCK_H_
#include "common/aglUniformBlock.h"
#endif

namespace agl {

bool UniformBlock::setUniform(DrawContext* context, const NVNbufferAddress& address,
                              const ShaderLocation& location, u32 offset, size_t size) const {
    if (!location.isValid()) {
        return false;
    }

    NVNbufferAddress targetAddress = address + offset;
    NVNcommandBuffer* commandBuffer = context->getCommandBuffer()->ToData()->pNvnCommandBuffer;

    for (s32 i = 0; i < cShaderType_Num; i++) {
        auto type = static_cast<ShaderType>(i);
        if (location.getLocation(type) != -1) {
            bindBufferNVN_(commandBuffer, driver::NVNMgr::getNVNshaderStage(type),
                           location.getLocation(type), targetAddress, size);
        }
    }

    return true;
}

}  // namespace agl