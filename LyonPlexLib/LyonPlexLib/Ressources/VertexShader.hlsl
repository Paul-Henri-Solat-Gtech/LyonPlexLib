
//-----------------------------------------------------------------------------//
// Data provenant du moteur
//-----------------------------------------------------------------------------//

cbuffer CameraBuffer : register(b0)
{
    float4x4 viewMatrix;
    float4x4 projectMatrix;
};
cbuffer ObjectBuffer : register(b1)
{
    float4x4 worldMatrix;
    uint materialIndex;
};

// slot t0 : table SRV textures
Texture2D textures[15] : register(t0);
//Texture2D textures[] : register(t0);

// slot s0 : sampler lineaire
SamplerState linearClamp : register(s0);
//SamplerState linearClamp[1] : register(s0);


//-----------------------------------------------------------------------------//
// Structs hlsl
//-----------------------------------------------------------------------------//

struct VSInput // VSmain in
{
    float3 position : POSITION;
    float4 color    : COLOR;
    float2 uv       : TEXCOORD0;
    //uint   material : TEXCOORD1;
};
struct PSInput // VSmain out
{
    float4 positionH : SV_POSITION; 
    float4 color     : COLOR; 
    float2 uv        : TEXCOORD0;
    //uint   material  : TEXCOORD1; 
};



//-----------------------------------------------------------------------------//
// Fonctions hlsl
//-----------------------------------------------------------------------------//

PSInput VSMain(VSInput input)
{
    PSInput output;
    float4 worldPos = mul(float4(input.position, 1.0f), worldMatrix);
    float4 viewPos = mul(worldPos, viewMatrix);
    output.positionH = mul(viewPos, projectMatrix);
    
    output.uv = input.uv;
    
    output.color = input.color;
    return output;    
};

float4 PSMain(PSInput input) : SV_Target
{
    // On echantillonne la bonne texture
    return textures[materialIndex].Sample(linearClamp, input.uv);
    //return textures[idx].Sample(linearClamp[idx], uv);
    
}