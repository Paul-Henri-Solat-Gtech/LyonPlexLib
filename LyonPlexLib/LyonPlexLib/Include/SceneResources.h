#pragma once

namespace TEXTURES
{
	enum TEXTURES
	{
		TEST3,
		TEST,
		ARMS,
		GRID,
		NOTEXTURE,
		BOIS,
		EAU,
		CHAMP,
		PARCELLE1,
		PARCELLE2,
		PARCELLE3,
		PARCELLE4,
		CHEMINTERRE,
		PIERRE,
		HERBE,
		PONT,
		MAISON,
		TEMPLE,
		tex0,

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

		EXT_ARBRETEST,
		EXT_CEPHA1,
		EXT_CUBE,
		EXT_TEMPLE,
		EXT_MAISON,
		EXT_ROCKBIG,
		EXT_ROCKLM1,
		EXT_ROCKLM2,
		

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

