#ifndef _GRAPHICSRESOURCE_H_
#define _GRAPHICSRESOURCE_H_

#include "CommonInclude.h"
#include "aiGraphicsDescriptors.h"

#include <vector>

namespace aiGraphics
{
	typedef uint64_t aiCPUHandle;
	static const aiCPUHandle ai_NULL_HANDLE = 0;

	class GraphicsDevice;

	struct GraphicsDeviceChild
	{
		GraphicsDevice* device = nullptr;
		inline void Register(GraphicsDevice* dev) { device = dev; }
		inline bool IsValid() const { return device != nullptr; }
	};

	struct ShaderByteCode
	{
		BYTE* data = nullptr;
		size_t size = 0;
		~ShaderByteCode() { SAFE_DELETE_ARRAY(data); }
	};

	struct VertexShader : public GraphicsDeviceChild
	{
		~VertexShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct PixelShader : public GraphicsDeviceChild
	{
		~PixelShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct GeometryShader : public GraphicsDeviceChild
	{
		~GeometryShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct HullShader : public GraphicsDeviceChild
	{
		~HullShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct DomainShader : public GraphicsDeviceChild
	{
		~DomainShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct ComputeShader : public GraphicsDeviceChild
	{
		~ComputeShader();

		ShaderByteCode code;
		aiCPUHandle resource = ai_NULL_HANDLE;
	};

	struct Sampler : public GraphicsDeviceChild
	{
		aiCPUHandle resource = ai_NULL_HANDLE;
		SamplerDesc desc;

		~Sampler();

		const SamplerDesc& GetDesc() const { return desc; }
	};

	struct GPUResource : public GraphicsDeviceChild
	{
		enum GPU_RESOURCE_TYPE
		{
			BUFFER,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
			UNKNOWN_TYPE,
		} type = UNKNOWN_TYPE;
		inline bool IsTexture() const { return type == TEXTURE_1D || type == TEXTURE_2D || type == TEXTURE_3D; }
		inline bool IsBuffer() const { return type == BUFFER; }

		aiCPUHandle SRV = ai_NULL_HANDLE;			// main resource SRV
		std::vector<aiCPUHandle> additionalSRVs;	// can be used for sub-resources if requested

		aiCPUHandle UAV = ai_NULL_HANDLE;			// main resource UAV
		std::vector<aiCPUHandle> additionalUAVs;	// can be used for sub-resources if requested

		aiCPUHandle resource = ai_NULL_HANDLE;
		aiCPUHandle resourceMemory = ai_NULL_HANDLE;

		virtual ~GPUResource();
	};

	struct GPUBuffer : public GPUResource
	{
		aiCPUHandle CBV = ai_NULL_HANDLE;
		GPUBufferDesc desc;

		virtual ~GPUBuffer();

		const GPUBufferDesc& GetDesc() const { return desc; }
	};

	struct VertexLayout : public GraphicsDeviceChild
	{
		aiCPUHandle	resource = ai_NULL_HANDLE;

		std::vector<VertexLayoutDesc> desc;

		~VertexLayout();
	};

	struct BlendState : public GraphicsDeviceChild
	{
		aiCPUHandle resource = ai_NULL_HANDLE;
		BlendStateDesc desc;

		~BlendState();

		const BlendStateDesc& GetDesc() const { return desc; }
	};

	struct DepthStencilState : public GraphicsDeviceChild
	{
		aiCPUHandle resource = ai_NULL_HANDLE;
		DepthStencilStateDesc desc;

		~DepthStencilState();

		const DepthStencilStateDesc& GetDesc() const { return desc; }
	};

	struct RasterizerState : public GraphicsDeviceChild
	{
		aiCPUHandle resource = ai_NULL_HANDLE;
		RasterizerStateDesc desc;

		~RasterizerState();

		const RasterizerStateDesc& GetDesc() const { return desc; }
	};

	struct Texture : public GPUResource
	{
		TextureDesc	desc;
		aiCPUHandle	RTV = ai_NULL_HANDLE;
		std::vector<aiCPUHandle> additionalRTVs;
		bool independentRTVArraySlices = false;
		bool independentRTVCubemapFaces = false;
		bool independentSRVArraySlices = false;
		bool independentSRVMIPs = false;
		bool independentUAVMIPs = false;

		const TextureDesc& GetDesc() const { return desc; }

		// if true, then each array slice aill get a unique rendertarget
		void RequestIndependentRenderTargetArraySlices(bool value);
		// if true, then each face of the cubemap aill get a unique rendertarget
		void RequestIndependentRenderTargetCubemapFaces(bool value);
		// if true, then each array slice aill get a unique shader resource
		void RequestIndependentShaderResourceArraySlices(bool value);
		// if true, then each miplevel aill get unique shader resource
		void RequestIndependentShaderResourcesForMIPs(bool value);
		// if true, then each miplevel aill get unique unordered access resource
		void RequestIndependentUnorderedAccessResourcesForMIPs(bool value);
	};

	struct Texture1D : public Texture
	{
		virtual ~Texture1D();
	};

	struct Texture2D : public Texture
	{
		aiCPUHandle	DSV = ai_NULL_HANDLE;
		std::vector<aiCPUHandle> additionalDSVs;

		virtual ~Texture2D();
	};

	struct Texture3D : public Texture
	{
		virtual ~Texture3D();
	};




	struct GPUQuery : public GraphicsDeviceChild
	{
		aiCPUHandle	resource = ai_NULL_HANDLE;
		GPUQueryDesc desc;

		~GPUQuery();

		const GPUQueryDesc& GetDesc() const { return desc; }
	};


	struct GraphicsPSO : public GraphicsDeviceChild
	{
		aiCPUHandle	pipeline = ai_NULL_HANDLE;
		GraphicsPSODesc desc;

		const GraphicsPSODesc& GetDesc() const { return desc; }

		~GraphicsPSO();
	};
	struct ComputePSO : public GraphicsDeviceChild
	{
		aiCPUHandle	pipeline = ai_NULL_HANDLE;
		ComputePSODesc desc;

		const ComputePSODesc& GetDesc() const { return desc; }

		~ComputePSO();
	};

}

#endif // _GRAPHICSRESOURCE_H_
