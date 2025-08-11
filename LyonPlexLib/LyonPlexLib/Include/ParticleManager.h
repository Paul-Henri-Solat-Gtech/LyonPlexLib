//#pragma once
//
//// Max particles & compute thread-group
//constexpr UINT kMaxParticles = 1000;
//constexpr UINT kCSGroupSize = 256;
//
//// Interface
//enum class BlendMode : uint32_t { Alpha, Additive };
//
//struct Particle
//{
//	XMFLOAT3 position;
//	XMFLOAT3 velocity;
//	XMFLOAT4 color;
//	float size;
//	float age;
//	float lifetime;
//};
//static_assert(sizeof(Particle) == 52, "Doit être à 52 bytes pour matcher le HLSL");
//
//
//struct ParticleParam 
//{
//	float sizeMultiplier;
//	float gravity;
//	float padding[2]; // align to 16 bytes
//	XMFLOAT4 globalColor;
//	BlendMode blendMode;
//	uint32_t padding2[3];
//};
//
//class ParticleManager
//{
//	using TextureID = ResourceManager<TextureData, std::string>::ResourceID;
//
//	GraphicsDevice*		mp_graphicsDevice		= nullptr;
//	CommandManager*		mp_cmdManager			= nullptr;
//	DescriptorManager*	mp_descriptorManager	= nullptr;
//	TextureManager*		mp_textureManager		= nullptr;
//
//	// Buffers
//	ComPtr<ID3D12Resource> g_particleBuffer;
//	ComPtr<ID3D12Resource> g_particleUploadBuffer;
//
//	ComPtr<ID3D12Resource> m_quadUploadBuffer;
//	ComPtr<ID3D12Resource> g_quadVB;
//
//	// Constant buffer for dynamic parameters
//	ComPtr<ID3D12Resource> g_paramBuffer;
//
//	ComPtr<ID3D12Resource> g_computeParamBuffer;    // Compute shader CBV buffer
//
//	// PSO & Root Signatures
//	ComPtr<ID3D12RootSignature> g_computeRootSig;
//	ComPtr<ID3D12PipelineState> g_computePSO;
//
//	ComPtr<ID3D12RootSignature> g_graphicsRootSig;
//
//	ComPtr<ID3D12PipelineState> g_graphicsPSO_Alpha;
//	ComPtr<ID3D12PipelineState> g_graphicsPSO_Additive;
//
//	// Descriptor strides
//	UINT g_cbvSrvDescriptorSize = 0;
//
//	void CreateParticleBuffers();
//
//	void CreateParamBuffer();
//
//	void CreateComputeParamBuffer();
//
//	void CreateQuadVertexBuffer();
//
//	void CreateRootSignaturesAndPSOs();
//
//	uint32_t idTemp = 0;
//
//	UINT m_smokeSrvIndex = 0;
//
//public:
//
//	void MapUploadBuffer(TextureManager* textureManager);
//
//	void Init(GraphicsDevice* graphicsDevice, CommandManager* cmdManager, DescriptorManager* descriptorManager);
//	void CreateParticles(TextureManager* textureManager);
//	void UpdateParticles(float deltaTime, float totalTime, float gravity);
//	void RenderParticles(const D3D12_VIEWPORT& vp, const D3D12_RECT& scissor, const D3D12_GPU_VIRTUAL_ADDRESS viewProjCBAdress, const D3D12_GPU_DESCRIPTOR_HANDLE srvHandle, const ParticleParam& params);
//
//};
//

/* ParticleManager.h */
#pragma once
#include <RenderingManager.h>
//#include <d3d12.h>
//#include <wrl.h>
//using Microsoft::WRL::ComPtr;

struct Particle {
    float position[3];
    float size;
    float color[4];
};

class ParticleManager {
public:
    void Initialize(GraphicsDevice* graphicsDevice, CommandManager* cmdManager, DescriptorManager* descriptorManager /*ID3D12DescriptorHeap* srvHeap,*/ );
    void Render(ID3D12GraphicsCommandList* cmdList, D3D12_GPU_DESCRIPTOR_HANDLE bufferHandle,
                const D3D12_VIEWPORT& vp, const D3D12_RECT& scissor, D3D12_GPU_VIRTUAL_ADDRESS viewProjCB);

private:
    //static const UINT kNumParticles = 1;
    //ComPtr<ID3D12Resource> m_vertexBuffer;
    //ComPtr<ID3D12Resource> m_vertexUpload;
    //ComPtr<ID3D12Resource> m_indexBuffer;
    //ComPtr<ID3D12Resource> m_indexUpload;
    //ComPtr<ID3D12Resource> m_particleBuffer;
    //ComPtr<ID3D12Resource> m_particleUpload;
    //ComPtr<ID3D12Resource> m_particleSRVBuffer;

    //ComPtr<ID3D12RootSignature> m_rootSig;
    //ComPtr<ID3D12PipelineState> m_pso;
    //UINT m_srvDescriptorSize;
    //ID3D12DescriptorHeap* m_srvHeap;
    static const UINT kNumParticles = 1;
    ComPtr<ID3D12Resource> m_particleBuffer;
    ComPtr<ID3D12Resource> m_particleUpload;
    ComPtr<ID3D12Resource> m_quadVB;

    ComPtr<ID3D12RootSignature> m_rootSig;
    ComPtr<ID3D12PipelineState> m_pso;
    UINT m_srvDescriptorSize;
    ID3D12DescriptorHeap* m_srvHeap;

    GraphicsDevice* m_graphicsDevice = nullptr;
    DescriptorManager* m_descMgr = nullptr;
    CommandManager* m_cmdMgr = nullptr;
};





struct ParticleData
{
    XMFLOAT4 position;
    XMFLOAT4 velocity;
};

struct ParticleParameter
{
    XMFLOAT4X4 viewProj;
    XMFLOAT3 gravity;
    float deltaTime;
};