#pragma once

#include <gfx/seadColor.h>
#include <hostio/seadHostIOReflexible.h>
#include <math/seadBoundBox.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>

namespace sead {
class Camera;
class Controller;
class LookAtCamera;
class Projection;
class Viewport;
}  // namespace sead

namespace agl {

class CubeMapFace;
class DrawContext;
class RenderBuffer;
class ShaderProgram;
class TextureData;
class TextureSampler;

namespace utl {

// FIXME replace this with the proper include
class ImageFilter2D {
public:
    enum Channel {};
};

namespace DevTools {
enum CameraControlType {};
class PoiningControlBuffer;

void setMeterScale(float scale);
float getMeterScale();
float calcScale(float factor);
float calcMeter(float factor);
sead::SafeString getStringMinMax(float min, float max);
void setFrameSpeed(float frame_speed);
float getFrameSpeed();
void setCameraOperationSpeed(float speed);
float getCameraOperationSpeed();
void genMessage(sead::hostio::Context* context);
void drawCamera(DrawContext*, const sead::Camera&, const sead::Matrix34f&, const sead::Matrix44f&,
                bool, const sead::Color4f&, float);
void drawCamera(DrawContext*, const sead::Matrix34f&, const sead::Vector3f&, const sead::Matrix34f&,
                const sead::Matrix44f&, bool, const sead::Color4f&, float);
void drawCamera_(DrawContext*, const sead::Matrix34f&, const sead::Vector3f&,
                 const sead::Matrix34f&, const sead::Matrix44f&, bool, const sead::Color4f&, float);
void drawFrustum(DrawContext*, const sead::Camera&, const sead::Projection&, const sead::Matrix34f&,
                 const sead::Matrix44f&, bool, const sead::Color4f&);
void drawFrustum_(DrawContext*, const sead::Matrix34f&, const sead::Matrix44f&,
                  const sead::Matrix34f&, const sead::Matrix44f&, bool, const sead::Color4f&);
void drawFrustum(DrawContext*, const sead::Matrix34f&, const sead::Projection&,
                 const sead::Matrix34f&, const sead::Matrix44f&, bool, const sead::Color4f&);
void drawCameraAndFrustum(DrawContext*, const sead::Camera&, const sead::Projection&,
                          const sead::Matrix34f&, const sead::Matrix44f&, bool,
                          const sead::Color4f&, const sead::Color4f&, float);
void beginDrawImm(DrawContext*, const sead::Matrix34f&, const sead::Matrix44f&);
void drawLineImm(DrawContext*, const sead::Vector3f&, const sead::Vector3f&, const sead::Color4f&,
                 float);
void setUniformToDevToolsShader_(DrawContext*, const sead::Matrix34f&, const sead::Matrix34f&,
                                 const sead::Matrix44f&, const sead::Color4f&, const sead::Color4f&,
                                 const sead::Vector3f&);
void drawAxisImm(DrawContext*, const sead::Matrix34f&, float, float, float);
void drawDirectionalLight(DrawContext*, const sead::Vector3f&, const sead::Color4f&,
                          const sead::Color4f&, const sead::Color4f&, const sead::Matrix34f&,
                          const sead::Matrix44f&, float, bool);
void drawPou32Light(DrawContext*, const sead::Vector3f&, float, const sead::Color4f&,
                    const sead::Matrix34f&, const sead::Matrix44f&);
void drawSpotLight(DrawContext*, const sead::Vector3f&, const sead::Vector3f&, const sead::Color4f&,
                   float, float, const sead::Matrix34f&, const sead::Matrix44f&);
void drawProjLight(DrawContext*, const sead::Vector3f&, const sead::Vector3f&,
                   const sead::Vector3f&, const sead::Color4f&, float, float, float, float, float,
                   float, const sead::Vector3f&, bool, const sead::Matrix34f&,
                   const sead::Matrix44f&);
void drawCapsule(DrawContext*, const sead::Vector3f&, const sead::Vector3f&, float,
                 const sead::Color4f&, const sead::Matrix34f&, const sead::Matrix44f&, bool);
void drawArrow(DrawContext*, const sead::Vector3f&, const sead::Vector3f&, const sead::Color4f&,
               const sead::Color4f&, float, const sead::Matrix34f&, const sead::Matrix44f&);
void drawCursor(DrawContext*, const sead::Vector2f&, const sead::Vector2f&, float);
void drawTexture(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                 const sead::Matrix44f&, const sead::Color4f&);
void drawDepthGradation(DrawContext*, const RenderBuffer&, u32, const float*, const sead::Color4f*,
                        float, float);
void controlCamera(sead::LookAtCamera*, const sead::Controller&, float, CameraControlType);
void controlCamera(sead::LookAtCamera*, const sead::Vector2f&, const sead::Vector2f&, float, float,
                   float, bool, CameraControlType);
void controlCameraPou32er(sead::LookAtCamera*, PoiningControlBuffer*, const sead::Viewport&);
void controlCameraPou32er(sead::LookAtCamera*, PoiningControlBuffer*, float, float);
void controlCameraPou32er(sead::LookAtCamera*, PoiningControlBuffer*, bool, bool, bool, bool,
                          const sead::Vector2f&, bool, float, float);
void controlCameraPou32er(sead::LookAtCamera*, const sead::Vector2f&, float, float, float);
void drawFrameBuffer(DrawContext*, const RenderBuffer&, const sead::Viewport&,
                     ImageFilter2D::Channel);
void drawVisualizedDepth(DrawContext*, const TextureData&, s32, const sead::Matrix34f&,
                         const sead::Matrix44f&, const sead::Matrix34f&, const sead::Matrix44f&);
void drawVisualizedDepth(DrawContext*, const TextureData&, s32, const sead::Matrix44f&,
                         const sead::Matrix34f&, const sead::Matrix44f&);
void drawColorQuad(DrawContext*, const sead::Color4f&, const sead::Matrix34f&,
                   const sead::Matrix44f&);
void drawColorQuadTopBottom(DrawContext*, const sead::Color4f&, const sead::Color4f&,
                            const sead::Matrix34f&, const sead::Matrix44f&);
void drawTexture_(DrawContext*, const ShaderProgram&, const TextureSampler&, const sead::Matrix34f&,
                  const sead::Matrix44f&, const sead::Color4f&);
void drawTextureChannel(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                        const sead::Matrix44f&, ImageFilter2D::Channel);
void drawTextureGamma(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                      const sead::Matrix44f&, float);
void drawTextureMipLevel(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                         const sead::Matrix44f&, float);
void drawTexture2DArray(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                        const sead::Matrix44f&, s32, float, const sead::Color4f&);
void drawTexture3D(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                   const sead::Matrix44f&, float, float);
void drawTextureCubeMap(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                        const sead::Matrix44f&, CubeMapFace, float);
void drawTextureCubeArray(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                          const sead::Matrix44f&, s32, CubeMapFace, float);
void drawTextureTexCoord(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                         const sead::Matrix44f&, const sead::Vector2f&, float,
                         const sead::Vector2f&);
void drawTextureTexCoordMultColor(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                                  const sead::Matrix44f&, const sead::Vector2f&, float,
                                  const sead::Vector2f&, const sead::Color4f&);
void drawTextureMSAA(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                     const sead::Matrix44f&);
void drawNV12Decord(DrawContext*, const TextureSampler&, const TextureSampler&,
                    const sead::Matrix34f&, const sead::Matrix44f&);
void drawTextureColorMatrix(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                            const sead::Matrix44f&, const sead::Matrix44f&, const sead::Vector4f&,
                            float);
void drawTexture_(DrawContext*, const ShaderProgram&, const TextureSampler&, const sead::Matrix34f&,
                  const sead::Matrix44f&, const sead::Matrix44f&, const sead::Vector4f&);
void drawTexture2DArrayColorMatrix(DrawContext*, const TextureSampler&, const sead::Matrix34f&,
                                   const sead::Matrix44f&, const sead::Matrix44f&,
                                   const sead::Vector4f&, s32, float);
void drawPou32Imm(DrawContext*, const sead::Vector3f&, const sead::Color4f&, float);
void drawTriangleImm(DrawContext*, const sead::Vector3f&, const sead::Vector3f&,
                     const sead::Vector3f&, const sead::Color4f&);
void drawWireTriangleImm(DrawContext*, const sead::Vector3f&, const sead::Vector3f&,
                         const sead::Vector3f&, const sead::Color4f&, float);
void drawGridImm(DrawContext*, float, float, u32, u32, const sead::Color4f&, float);
void drawWireCircleImm(DrawContext*, const sead::Matrix34f&, const sead::Color4f&, float, u32);
void drawBoundBoxImm(DrawContext*, const sead::BoundBox3f&, const sead::Color4f&, float);
void drawFan(DrawContext*, const sead::Matrix34f&, const sead::Matrix44f&, const sead::Color4f&,
             float, float, u32, float);
void drawFan_(DrawContext*, u32*, const sead::Matrix34f&, const sead::Matrix44f&,
              const sead::Color4f&, float, float, u32, float);
void drawWireFan(DrawContext*, const sead::Matrix34f&, const sead::Matrix44f&, const sead::Color4f&,
                 float, float, u32, float);
void setStickReverse(bool reverse);
bool isStickReverse();
void setRotateLRReverse(bool reverse);
bool isRotateLRReverse();
void setRotateUDReverse(bool reverse);
bool isRotateUDReverse();
}  // namespace DevTools

}  // namespace utl

}  // namespace agl
