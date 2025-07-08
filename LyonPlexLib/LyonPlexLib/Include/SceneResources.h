#pragma once

namespace TEXTURES
{
	enum TEXTURES
	{
		NOTEXTURE,
		TEST3,
		TEST,
		ARMS,
		GRID,
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
		CEPHA,

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

		ARBRETEST,
		CEPHA1,
		CUBE,
		TEMPLE,
		MAISON,
		ROCKBIG,
		ROCKLM1,
		ROCKLM2,

		CEPHA_GROS,
		CEPHA_PETIT,
		CYPRESS_GROS,
		CYPRESS_PETIT,
		MASTICS,
		OLIVIER,
		BUISSON_FLEUR,
		BUISSON_FLEUR_GROS,
		BUISSON_GROS,
		BUISSON_MOYEN_FLEUR,
		BUISSON_MOYEN,
		BUISSON_PETIT,
		CAILLOUX_SOL1,
		CAILLOUX_SOL2,
		CAILLOUX_SOL3,
		CAILLOUX1,
		CAILLOUX2,
		CAILLOUX3,
		CAILLOUX4,
		

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

