#pragma once

// Use GRAPHICSTHREAD_IMMEDIATE from the main thread and when draaing to backbuffer
// Use the others from other threads in conjunction aith GraphicsDevice::FinishCommandList and ExecuteCommandLists
enum GRAPHICSTHREAD
{
	GRAPHICSTHREAD_IMMEDIATE,
	GRAPHICSTHREAD_SHADOWS,
	GRAPHICSTHREAD_REFLECTIONS,
	GRAPHICSTHREAD_SCENE,
	GRAPHICSTHREAD_MISC1,
	GRAPHICSTHREAD_MISC2,
	GRAPHICSTHREAD_COUNT
};

// Common blendmodes used across multiple systems
enum BLENDMODE
{
	BLENDMODE_OPAQUE,
	BLENDMODE_ALPHA,
	BLENDMODE_PREMULTIPLIED,
	BLENDMODE_ADDITIVE,
	BLENDMODE_COUNT
};

// Do not alter order or value because it is bound to lua manually!
enum RENDERTYPE
{
	RENDERTYPE_VOID = 0,
	RENDERTYPE_OPAQUE = 1,
	RENDERTYPE_TRANSPARENT = 2,
	RENDERTYPE_WATER = 4,
	RENDERTYPE_ALL = RENDERTYPE_OPAQUE | RENDERTYPE_TRANSPARENT | RENDERTYPE_WATER
};

enum RENDERPASS
{
	RENDERPASS_TEXTURE,
	RENDERPASS_DEFERRED,
	RENDERPASS_FORWARD,
	RENDERPASS_TILEDFORWARD,
	RENDERPASS_DEPTHONLY,
	RENDERPASS_ENVMAPCAPTURE,
	RENDERPASS_SHADOW,
	RENDERPASS_SHADOWCUBE,
	RENDERPASS_VOXELIZE,
	RENDERPASS_COUNT
};

// engine stencil reference values. These can be in range of [0, 15].
// Do not alter order or value because it is bound to lua manually!
enum STENCILREF
{
	STENCILREF_EMPTY = 0,
	STENCILREF_SKY = 1,
	STENCILREF_DEFAULT = 2,
	STENCILREF_SKIN = 3,
	STENCILREF_LAST = 15
};

// constant buffers
enum CBTYPES
{
	CBTYPE_FRAME,
	CBTYPE_CAMERA,
	CBTYPE_MISC,
	CBTYPE_VOLUMELIGHT,
	CBTYPE_DECAL,
	CBTYPE_CUBEMAPRENDER,
	CBTYPE_API,
	CBTYPE_TESSELLATION,
	CBTYPE_DISPATCHPARAMS,
	CBTYPE_CLOUDGENERATOR,
	CBTYPE_RAYTRACE,
	CBTYPE_MIPGEN,
	CBTYPE_FILTERENVMAP,
	CBTYPE_COPYTEXTURE,
	CBTYPE_FORWARDENTITYMASK,
	CBTYPE_LAST
};

// resource buffers (StructuredBuffer, Buffer, etc.)
enum RBTYPES
{
	RBTYPE_ENTITYARRAY,
	RBTYPE_ENTITYTILES_OPAQUE,
	RBTYPE_ENTITYTILES_TRANSPARENT,
	RBTYPE_VOXELSCENE,
	RBTYPE_MATRIXARRAY,
	RBTYPE_LAST
};

// textures
enum TEXTYPES
{
	TEXTYPE_2D_DEBUGUAV,
	TEXTYPE_3D_VOXELRADIANCE,
	TEXTYPE_3D_VOXELRADIANCE_HELPER,
	TEXTYPE_2D_CLOUDS,
	TEXTYPE_2D_IMPOSTORARRAY,
	TEXTYPE_CUBEARRAY_ENVMAPARRAY,
	TEXTYPE_LAST
};

// vertex shaders
enum VSTYPES
{
	VSTYPE_NULL,
	VSTYPE_OBJECT_DEBUG,
	VSTYPE_OBJECT_COMMON,
	VSTYPE_OBJECT_SIMPLE,
	VSTYPE_OBJECT_POSITIONSTREAM,
	VSTYPE_OBJECT_COMMON_TESSELLATION,
	VSTYPE_OBJECT_SIMPLE_TESSELLATION,
	VSTYPE_SHADOW,
	VSTYPE_SHADOW_ALPHATEST,
	VSTYPE_SHADOW_TRANSPARENT,
	VSTYPE_SHADOWCUBEMAPRENDER,
	VSTYPE_SHADOWCUBEMAPRENDER_ALPHATEST,
	VSTYPE_IMPOSTOR,
	VSTYPE_LINE,
	VSTYPE_TRAIL,
	VSTYPE_WATER,
	VSTYPE_DIRLIGHT,
	VSTYPE_POINTLIGHT,
	VSTYPE_SPOTLIGHT,
	VSTYPE_LIGHTVISUALIZER_SPOTLIGHT,
	VSTYPE_LIGHTVISUALIZER_POINTLIGHT,
	VSTYPE_LIGHTVISUALIZER_SPHERELIGHT,
	VSTYPE_LIGHTVISUALIZER_DISCLIGHT,
	VSTYPE_LIGHTVISUALIZER_RECTANGLELIGHT,
	VSTYPE_LIGHTVISUALIZER_TUBELIGHT,
	VSTYPE_SKY,
	VSTYPE_DECAL,
	VSTYPE_ENVMAP,
	VSTYPE_ENVMAP_SKY,
	VSTYPE_SPHERE,
	VSTYPE_CUBE,
	VSTYPE_VOXELIZER,
	VSTYPE_VOXEL,
	VSTYPE_FORCEFIELDVISUALIZER_POINT,
	VSTYPE_FORCEFIELDVISUALIZER_PLANE,
	VSTYPE_RENDERLIGHTMAP,
	VSTYPE_RAYTRACE_SCREEN,
	VSTYPE_LAST
};
// pixel shaders
enum PSTYPES
{
	PSTYPE_NULL,
	PSTYPE_OBJECT_DEFERRED,
	PSTYPE_OBJECT_DEFERRED_NORMALMAP,
	PSTYPE_OBJECT_DEFERRED_POM,
	PSTYPE_OBJECT_DEFERRED_PLANARREFLECTION,
	PSTYPE_OBJECT_DEFERRED_NORMALMAP_POM,
	PSTYPE_OBJECT_DEFERRED_NORMALMAP_PLANARREFLECTION,
	PSTYPE_IMPOSTOR_DEFERRED,

	PSTYPE_OBJECT_FORWARD,
	PSTYPE_OBJECT_FORWARD_NORMALMAP,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT_NORMALMAP,
	PSTYPE_OBJECT_FORWARD_PLANARREFLECTION,
	PSTYPE_OBJECT_FORWARD_NORMALMAP_PLANARREFLECTION,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT_PLANARREFLECTION,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT_NORMALMAP_PLANARREFLECTION,
	PSTYPE_OBJECT_FORWARD_POM,
	PSTYPE_OBJECT_FORWARD_NORMALMAP_POM,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT_POM,
	PSTYPE_OBJECT_FORWARD_TRANSPARENT_NORMALMAP_POM,
	PSTYPE_OBJECT_FORWARD_WATER,
	PSTYPE_IMPOSTOR_FORWARD,

	PSTYPE_OBJECT_TILEDFORWARD,
	PSTYPE_OBJECT_TILEDFORWARD_NORMALMAP,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT_NORMALMAP,
	PSTYPE_OBJECT_TILEDFORWARD_PLANARREFLECTION,
	PSTYPE_OBJECT_TILEDFORWARD_NORMALMAP_PLANARREFLECTION,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT_PLANARREFLECTION,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT_NORMALMAP_PLANARREFLECTION,
	PSTYPE_OBJECT_TILEDFORWARD_POM,
	PSTYPE_OBJECT_TILEDFORWARD_NORMALMAP_POM,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT_POM,
	PSTYPE_OBJECT_TILEDFORWARD_TRANSPARENT_NORMALMAP_POM,
	PSTYPE_OBJECT_TILEDFORWARD_WATER,
	PSTYPE_IMPOSTOR_TILEDFORWARD,

	PSTYPE_OBJECT_HOLOGRAM,

	PSTYPE_OBJECT_DEBUG,
	PSTYPE_OBJECT_SIMPLEST,
	PSTYPE_OBJECT_BLACKOUT,
	PSTYPE_OBJECT_TEXTUREONLY,
	PSTYPE_OBJECT_ALPHATESTONLY,
	PSTYPE_IMPOSTOR_ALPHATESTONLY,
	PSTYPE_IMPOSTOR_SIMPLE,
	PSTYPE_IMPOSTOR_aiRE,

	PSTYPE_SHADOW_ALPHATEST,
	PSTYPE_SHADOW_TRANSPARENT,
	PSTYPE_SHADOW_WATER,

	PSTYPE_LINE,
	PSTYPE_TRAIL,
	PSTYPE_ENVIRONMENTALLIGHT,
	PSTYPE_DIRLIGHT,
	PSTYPE_POINTLIGHT,
	PSTYPE_SPOTLIGHT,
	PSTYPE_SPHERELIGHT,
	PSTYPE_DISCLIGHT,
	PSTYPE_RECTANGLELIGHT,
	PSTYPE_TUBELIGHT,
	PSTYPE_LIGHTVISUALIZER,
	PSTYPE_VOLUMETRICLIGHT_DIRECTIONAL,
	PSTYPE_VOLUMETRICLIGHT_POINT,
	PSTYPE_VOLUMETRICLIGHT_SPOT,
	PSTYPE_SHADOWCUBEMAPRENDER,
	PSTYPE_SHADOWCUBEMAPRENDER_ALPHATEST,
	PSTYPE_DECAL,
	PSTYPE_SKY_STATIC,
	PSTYPE_SKY_DYNAMIC,
	PSTYPE_SUN,
	PSTYPE_ENVMAP,
	PSTYPE_ENVMAP_SKY_STATIC,
	PSTYPE_ENVMAP_SKY_DYNAMIC,
	PSTYPE_CUBEMAP,
	PSTYPE_CAPTUREIMPOSTOR_ALBEDO,
	PSTYPE_CAPTUREIMPOSTOR_NORMAL,
	PSTYPE_CAPTUREIMPOSTOR_SURFACE,
	PSTYPE_VOXELIZER,
	PSTYPE_VOXEL,
	PSTYPE_FORCEFIELDVISUALIZER,
	PSTYPE_RENDERLIGHTMAP_INDIRECT,
	PSTYPE_RENDERLIGHTMAP_DIRECT,
	PSTYPE_RAYTRACE_DEBUGBVH,
	PSTYPE_LAST
};
// geometry shaders
enum GSTYPES
{
	GSTYPE_NULL,
	GSTYPE_SHADOWCUBEMAPRENDER,
	GSTYPE_SHADOWCUBEMAPRENDER_ALPHATEST,
	GSTYPE_ENVMAP,
	GSTYPE_ENVMAP_SKY,
	GSTYPE_VOXELIZER,
	GSTYPE_VOXEL,
	GSTYPE_LAST
};
// hull shaders
enum HSTYPES
{
	HSTYPE_NULL,
	HSTYPE_OBJECT,
	HSTYPE_LAST
};
// domain shaders
enum DSTYPES
{
	DSTYPE_NULL,
	DSTYPE_OBJECT,
	DSTYPE_LAST
};
// compute shaders
enum CSTYPES
{
	CSTYPE_LUMINANCE_PASS1,
	CSTYPE_LUMINANCE_PASS2,
	CSTYPE_TILEFRUSTUMS,
	CSTYPE_RESOLVEMSAADEPTHSTENCIL,
	CSTYPE_VOXELSCENECOPYCLEAR,
	CSTYPE_VOXELSCENECOPYCLEAR_TEMPORALSMOOTHING,
	CSTYPE_VOXELRADIANCESECONDARYBOUNCE,
	CSTYPE_VOXELCLEARONLYNORMAL,
	CSTYPE_GENERATEMIPCHAIN2D_UNORM4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAIN2D_FLOAT4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAIN2D_UNORM4_GAUSSIAN,
	CSTYPE_GENERATEMIPCHAIN2D_FLOAT4_GAUSSIAN,
	CSTYPE_GENERATEMIPCHAIN2D_UNORM4_BICUBIC,
	CSTYPE_GENERATEMIPCHAIN2D_FLOAT4_BICUBIC,
	CSTYPE_GENERATEMIPCHAIN3D_UNORM4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAIN3D_FLOAT4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAIN3D_UNORM4_GAUSSIAN,
	CSTYPE_GENERATEMIPCHAIN3D_FLOAT4_GAUSSIAN,
	CSTYPE_GENERATEMIPCHAINCUBE_UNORM4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAINCUBE_FLOAT4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAINCUBEARRAY_UNORM4_SIMPLEFILTER,
	CSTYPE_GENERATEMIPCHAINCUBEARRAY_FLOAT4_SIMPLEFILTER,
	CSTYPE_FILTERENVMAP,
	CSTYPE_COPYTEXTURE2D_UNORM4,
	CSTYPE_COPYTEXTURE2D_FLOAT4,
	CSTYPE_COPYTEXTURE2D_UNORM4_BORDEREXPAND,
	CSTYPE_COPYTEXTURE2D_FLOAT4_BORDEREXPAND,
	CSTYPE_SKINNING,
	CSTYPE_SKINNING_LDS,
	CSTYPE_CLOUDGENERATOR,
	CSTYPE_RAYTRACE_CLEAR,
	CSTYPE_RAYTRACE_LAUNCH,
	CSTYPE_RAYTRACE_KICKJOBS,
	CSTYPE_RAYTRACE_PRIMARY,
	CSTYPE_RAYTRACE_LIGHTSAMPLING,
	CSTYPE_LAST
};

// vertex layouts
enum VLTYPES
{
	VLTYPE_NULL,
	VLTYPE_OBJECT_DEBUG,
	VLTYPE_OBJECT_POS,
	VLTYPE_OBJECT_POS_TEX,
	VLTYPE_OBJECT_ALL,
	VLTYPE_SHADOW_POS,
	VLTYPE_SHADOW_POS_TEX,
	VLTYPE_RENDERLIGHTMAP,
	VLTYPE_LINE,
	VLTYPE_TRAIL,
	VLTYPE_LAST
};
// rasterizer states
enum RSTYPES
{
	RSTYPE_FRONT,
	RSTYPE_BACK,
	RSTYPE_DOUBLESIDED,
	RSTYPE_aiRE,
	RSTYPE_aiRE_SMOOTH,
	RSTYPE_aiRE_DOUBLESIDED,
	RSTYPE_aiRE_DOUBLESIDED_SMOOTH,
	RSTYPE_SHADOW,
	RSTYPE_SHADOW_DOUBLESIDED,
	RSTYPE_OCCLUDEE,
	RSTYPE_VOXELIZE,
	RSTYPE_SKY,
	RSTYPE_LAST
};
// depth-stencil states
enum DSSTYPES
{
	DSSTYPE_DEFAULT,
	DSSTYPE_SHADOW,
	DSSTYPE_XRAY,
	DSSTYPE_DEPTHREAD,
	DSSTYPE_DIRLIGHT,
	DSSTYPE_LIGHT,
	DSSTYPE_DECAL,
	DSSTYPE_STENCILREAD_MATCH,
	DSSTYPE_DEPTHREADEQUAL,
	DSSTYPE_ENVMAP,
	DSSTYPE_CAPTUREIMPOSTOR,
	DSSTYPE_LAST
};
// blend states
enum BSTYPES
{
	BSTYPE_OPAQUE,
	BSTYPE_TRANSPARENT,
	BSTYPE_INVERSE,
	BSTYPE_ADDITIVE,
	BSTYPE_PREMULTIPLIED,
	BSTYPE_COLORWRITEDISABLE,
	BSTYPE_DEFERREDLIGHT,
	BSTYPE_ENVIRONMENTALLIGHT,
	BSTYPE_DECAL,
	BSTYPE_MULTIPLY,
	BSTYPE_TRANSPARENTSHADOWMAP,
	BSTYPE_LAST
};
// custom sample states
enum CSSTYPES
{
	SSTYPE_MAXIMUM_CLAMP,
	SSTYPE_LAST
};