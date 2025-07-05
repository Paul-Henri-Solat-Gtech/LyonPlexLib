
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
//Texture2D textures[150] : register(t0);
Texture2D textures : register(t0);

// slot s0 : sampler lineaire
SamplerState linearClamp : register(s0);


//-----------------------------------------------------------------------------//
// Structs hlsl
//-----------------------------------------------------------------------------//

struct VSInput // VSmain in
{
    float3 position : POSITION;
    float4 color    : COLOR;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL; // ajoutÅE
    //uint   material : TEXCOORD1;
};
struct PSInput // VSmain out
{
    float4 positionH : SV_POSITION; 
    float4 color     : COLOR; 
    float2 uv : TEXCOORD0;
    //float3 normal : NORMAL; // Pas besoin car on utilise directement input.normal dans VSMain
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
    //if (materialIndex == -1)
    //    return input, input.color;
    
    //return float4(input.uv.x, // R = U
    //          0.0f, // G = 0
    //          input.uv.y, // B = V
    //          1.0f);
    
    //return float4(input.uv.x, input.uv.y, 0, 1);
    
    return textures.Sample(linearClamp, input.uv);
    
    //float2 planUV = input.positionH.xz * (1 / 2) + float2(0.5, 0.5);
    //return textures.Sample(linearClamp, planUV);
    
    //return textures[materialIndex].Sample(linearClamp, input.uv);
    //float4 c = textures[materialIndex].Sample(linearClamp, input.uv);
    //c.rgb = pow(c.rgb, 1.0 / 2.2); // format lineraire a RGB
    //return c;
    //return textures[idx].Sample(linearClamp[idx], uv);
    
}