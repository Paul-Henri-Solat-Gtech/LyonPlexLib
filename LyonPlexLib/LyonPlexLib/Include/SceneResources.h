#pragma once

namespace TEXTURES
{
	enum TEXTURES
	{
		tex0,
		test,
		bras,
		grid,
		noTexture,
		iceCream,
		start,

		idleArm1,
		idleArm2,
		idleArm3,
		idleArm4,
		idleArm5,
		idleArm6,
		idleArm7,
		idleArm8,
		idleArm9,
		idleArm10,
		idleArm11,
		idleArm12,
		idleArm13,
		idleArm14,
		idleArm15,
		idleArm16,
		idleArm17,
		idleArm18,
		idleArm19,
		idleArm20,
		idleArm21,
		idleArm22,
		idleArm23,
		idleArm24,


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

