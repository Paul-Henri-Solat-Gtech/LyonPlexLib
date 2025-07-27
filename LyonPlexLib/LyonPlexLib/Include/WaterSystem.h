#pragma once



class WaterSystem : public ISystem
{
public:
    void Init(ECSManager& ecs) override;
    void Update(ECSManager& ecs, float dt) override;

private:


};

