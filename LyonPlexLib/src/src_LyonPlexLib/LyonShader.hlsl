

//------------------------------------------------------------------------------
// 1) Camera : slot b0
//------------------------------------------------------------------------------
cbuffer CameraBuffer : register(b0)
{
    float4x4 viewMatrix;
    float4x4 projectionMatrix;
};   // <-- point-virgule manquant ajoute

//------------------------------------------------------------------------------
// 2) Per-Object Constants : slot b1
//------------------------------------------------------------------------------
cbuffer ObjectBuffer : register(b1)
{
    float4x4 worldMatrix;
};   // <-- point-virgule ajoute

//------------------------------------------------------------------------------
// 3) Donnees « par-vertex »
//------------------------------------------------------------------------------
struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct PSInput
{
    float4 positionH : SV_POSITION;
    float4 color : COLOR;
};

//------------------------------------------------------------------------------
// 4) Vertex Shader : VSMain
//------------------------------------------------------------------------------
PSInput VSMain(VSInput input)
{
    PSInput output;

    // etape A : local → monde
    float4 worldPos = mul(float4(input.position, 1.0f), worldMatrix);

    // etape B : monde → camera
    float4 viewPos = mul(worldPos, viewMatrix);

    // etape C : projection camera → clip
    output.positionH = mul(viewPos, projectionMatrix);

    output.color = input.color;
    return output;
}

//------------------------------------------------------------------------------
// 5) Pixel Shader simple
//------------------------------------------------------------------------------
float4 PSMain(PSInput input) : SV_TARGET
{
    return input.color;
}
