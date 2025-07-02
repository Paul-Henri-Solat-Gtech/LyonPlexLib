#pragma once
#include "ECSManager.h"

#include <Windows.h>

class GraphicsDevice;
class CommandManager;


struct CBPerCamera {
    XMFLOAT4X4 view;       // matrice view deja transposee
    XMFLOAT4X4 projection; // matrice proj deja transposee
};

class CameraSystem : public ISystem {
public:
    CameraSystem() {}

    void InitRenderVariables(GraphicsDevice* device, CommandManager* cmdMgr);

    // Appele une seule fois apres avoir ajoute le composant a ECS
    virtual void Init(ECSManager& ecs) override;

    // Appele chaque frame, avant le rendu
    virtual void Update(ECSManager& ecs, float dt) override;

    // Aucun rendu direct dans le CameraSystem
    virtual void Render(ECSManager& ecs) override { }

    ComPtr<ID3D12Resource>& GetCBbuffer() { return m_cameraConstantBuffer; }


private:
    GraphicsDevice* mp_graphicsDevice = nullptr;
    CommandManager* mp_commandManager = nullptr;

    ComPtr<ID3D12Resource> m_cameraConstantBuffer;
    void* m_mappedCBData = nullptr;

    // Remplit cam->viewMatrix (XMFLOAT4X4) en fonction de cam->position / cam->forward / cam->up
    void RecomputeViewMatrix(CameraComponent* cam);

    // Remplit cam->projectionMatrix en fonction de cam->fov / aspectRatio / near / far
    void RecomputeProjectionMatrix(CameraComponent* cam);
};
