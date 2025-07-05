#pragma once

namespace TEXTURES
{
	enum TEXTURES
	{
		tex0,
		test,
		bras,

		// A REMPLIR
		TotalTextureCount
	};
}

namespace MESHES
{
	enum MESHES
	{
		LOCAL_TRIANGLE,
		LOCAL_SQUARE,
		LOCAL_CUBE,
		Mesh0,

		// A REMPLIR
		TotalMeshCount
	};
}



class SceneResources
{
public:
	bool Init(GameManager* gameManager);


private:

	bool InitTextureResources(TextureManager& txtMngr);

	bool InitImportedMeshResources(MeshManager& meshMngr);
	bool InitLocalMeshResources(MeshManager& meshMngr);

	GameManager* mp_gameManager;

};

