
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
Texture2D textures[150] : register(t0);
SamplerState linearClamp : register(s0);

struct VSInput // VSmain in
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};
struct PSInput // VSmain out
{
    float4 posH : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};


PSInput VSMain2D(VSInput input)
{
    PSInput output;
    // étend en 3D : Z=0, W=1
    float4 worldPos = mul(float4(input.position, 1.0f), worldMatrix);
    output.posH = mul(worldPos, orthoMatrix);
    output.uv = input.uv;
    output.color = input.color;
    return output;
}

float4 PSMain2D(PSInput input) : SV_TARGET
{
    //return input.color;
    //return textures[materialIndex].Sample(linearClamp, input.uv);
    float4 c = textures[materialIndex].Sample(linearClamp, input.uv);
    c.rgb = pow(c.rgb, 1.0 / 2.2); // format lineraire a RGB
    return c;
}