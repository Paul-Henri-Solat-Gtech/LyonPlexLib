
cbuffer OrthoBuffer : register(b0)
{
    float4x4 orthoMatrix;
};
cbuffer ObjectBuffer : register(b1)
{
    float4x4 worldMatrix;
    uint materialIndex;
};

// slot t0 : textures, et sampler s0
Texture2D textures[15] : register(t0);
SamplerState linearClamp : register(s0);

struct VSInput
{
    float2 position : POSITION; // XY
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 posH : SV_POSITION;
    float2 uv : TEXCOORD0;
};


PSInput VSMain2D(VSInput input)
{
    PSInput output;
    // étend en 3D : Z=0, W=1
    float4 worldPos = mul(float4(input.position, 0.0f, 1.0f), worldMatrix);
    output.posH = mul(worldPos, orthoMatrix);
    output.uv = input.uv;
    return output;
}

float4 PSMain2D(PSInput input) : SV_TARGET
{
    return textures[materialIndex].Sample(linearClamp, input.uv);
}