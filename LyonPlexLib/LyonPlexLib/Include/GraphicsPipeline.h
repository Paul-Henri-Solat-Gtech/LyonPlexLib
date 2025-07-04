#pragma once

class GraphicsPipeline
{
public:
	void Init(GraphicsDevice* graphicsDevice, DescriptorManager* descriptorManager, CommandManager* commandManager);

	void CreatePipeline(bool seeThrough = false);

	//void CreatePipeline3D();
	void CreatePipeline2D();

	ComPtr<ID3D12RootSignature>& GetRootSignature() { return m_rootSignature; };
	ComPtr<ID3D12PipelineState>& GetPipelineState() { return m_pipelineState; };

private:
	void CreateRootSignature();
	void CompileShader();
	void CreatePipelineStateObject();

	void CreatePipelineStateObject_SeeThrough();

	/*void CreateRootSignature3D();
	void CompileShaders3D();
	void CreatePipelineStateObject3D();*/

	void CreateRootSignature2D();
	void CompileShaders2D();
	void CreatePipelineStateObject2D();

	GraphicsDevice* mp_graphicsDevice;
	DescriptorManager* mp_descriptorManager;
	CommandManager* mp_commandManager;

	ComPtr<ID3DBlob> m_vsBlob;							// bytecode du vertex shader
	ComPtr<ID3DBlob> m_psBlob;							// bytecode du pixel shader
	ComPtr<ID3DBlob> m_errorBlob;						// messages d’erreur de compilation

	ComPtr<ID3D12RootSignature> m_rootSignature;		// Decrit les ressources accessibles par les shaders
	ComPtr<ID3D12PipelineState> m_pipelineState;		// Contient l'etat complet du pipeline graphique
};

