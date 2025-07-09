#include "pch.h"
#include "CameraSystem.h"

void CameraSystem::InitRenderVariables(GraphicsDevice* device, CommandManager* cmdMgr)
{
	mp_graphicsDevice = device;
	mp_commandManager = cmdMgr;
}

void CameraSystem::Init(ECSManager& ecs)
{
	// Creer un seul buffer upload pour la camera (view+proj)
	UINT64 sizeCB = (sizeof(CBPerCamera) + 255) & ~255;
	CD3DX12_HEAP_PROPERTIES heapProps(D3D12_HEAP_TYPE_UPLOAD);
	CD3DX12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(sizeCB);

	HRESULT hr = mp_graphicsDevice->GetDevice()->CreateCommittedResource(
		&heapProps, D3D12_HEAP_FLAG_NONE, &desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&m_cameraConstantBuffer)
	);
	assert(SUCCEEDED(hr));

	// On mappe une fois pour pouvoir faire memcpy plus tard
	CD3DX12_RANGE readRange(0, 0);
	hr = m_cameraConstantBuffer->Map(
		0, &readRange,
		reinterpret_cast<void**>(&m_mappedCBData)
	);
	assert(SUCCEEDED(hr));
}

void CameraSystem::Update(ECSManager& ecs, float dt)
{
	// 1) On recherche l'entite qui a un CameraComponent.
	//    (On suppose qu段l n馳 a qu置ne seule entite 田amera・active.)
	ComponentMask camMask = (1ULL << CameraComponent::StaticTypeID | 1ULL << TransformComponent::StaticTypeID);
	ecs.ForEach(camMask, [&](Entity e) 
	{
		auto* cam = ecs.GetComponent<CameraComponent>(e);
		auto* tComp = ecs.GetComponent<TransformComponent>(e);
		if (!cam) return;

		// 2) ici la liaison entre la pos et orientation
        {
            if (tComp->parent.id != UINT32_MAX)
            {
                Entity eParent;
                eParent.id = tComp->parent.id;
                auto* tParent = ecs.GetComponent<TransformComponent>(eParent);

                cam->position = tParent->position;
                cam->position.x += tComp->position.x;
                cam->position.y += tComp->position.y;
                cam->position.z += tComp->position.z;
            }
            else
            {
                // Copier la position directement
                cam->position = tComp->position;
            }

            // Charger le quaternion de rotation
            XMVECTOR qRot = XMLoadFloat4(&tComp->rotation);

            // Vecteurs de base (dans l'espace local de la camera)
            static const XMVECTOR defaultForward = XMVectorSet(0.f, 0.f, 1.f, 0.f);
            static const XMVECTOR defaultUp = XMVectorSet(0.f, 1.f, 0.f, 0.f);
            static const XMVECTOR defaultRight = XMVectorSet(1.f, 0.f, 0.f, 0.f);

            // Tourner ces vecteurs par le quaternion
            XMVECTOR vForward = XMVector3Rotate(defaultForward, qRot);
            XMVECTOR vUp = XMVector3Rotate(defaultUp, qRot);
            XMVECTOR vRight = XMVector3Rotate(defaultRight, qRot);

            // Stocker les resultats dans le CameraComponent
            XMStoreFloat3(&cam->forward, vForward);
            XMStoreFloat3(&cam->up, vUp);
            XMStoreFloat3(&cam->right, vRight);

            // Indiquer que la vue doit etre recalculee
            cam->viewDirty = true;
        }


		// 3) Si necessaire, recalculer la matrice view
		if (cam->viewDirty) {
			RecomputeViewMatrix(cam);
			cam->viewDirty = false;
		}
		// 4) Si necessaire, recalculer la matrice projection
		if (cam->projectionDirty) {
			RecomputeProjectionMatrix(cam);
			cam->projectionDirty = false;
		}

		// 5) Copier view et proj transposees dans le CB GPU
		CBPerCamera cbData;
		cbData.view = cam->viewMatrix;       // deja transposee
		cbData.projection = cam->projectionMatrix;  // deja transposee
		cbData.camPos = cam->position;      
		memcpy(m_mappedCBData, &cbData, sizeof(CBPerCamera));
		//memcpy(m_mappedCBData, &cbData, sizeof(cbData));

	});
}

void CameraSystem::RecomputeViewMatrix(CameraComponent* cam)
{
	XMVECTOR pos = XMLoadFloat3(&cam->position);
	XMVECTOR forward = XMVector3Normalize(XMLoadFloat3(&cam->forward));
	XMVECTOR up = XMVector3Normalize(XMLoadFloat3(&cam->up));
	XMMATRIX view = XMMatrixLookToLH(pos, forward, up);
	view = XMMatrixTranspose(view); // HLSL attend column-major
	XMStoreFloat4x4(&cam->viewMatrix, view);
}

void CameraSystem::RecomputeProjectionMatrix(CameraComponent* cam)
{
	float fovRad = XMConvertToRadians(cam->fovDegrees);
	XMMATRIX proj = XMMatrixPerspectiveFovLH(
		fovRad,
		cam->aspectRatio,
		cam->nearPlane,
		cam->farPlane
	);
	proj; // transpose pour HLSL
	proj = XMMatrixTranspose(proj);
	XMStoreFloat4x4(&cam->projectionMatrix, proj);
}

