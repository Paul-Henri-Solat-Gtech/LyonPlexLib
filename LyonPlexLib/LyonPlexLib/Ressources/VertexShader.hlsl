
static const uint MAX_LIGHTS = 8;


//-----------------------------------------------------------------------------//
// Data provenant du moteur
//-----------------------------------------------------------------------------//

cbuffer CameraBuffer : register(b0)
{
    float4x4 viewMatrix;
    float4x4 projectMatrix;
    float3   camPos; 
    float    _camCBpad; // padding
};
cbuffer ObjectBuffer : register(b1)
{
    float4x4 worldMatrix;
    uint     materialIndex;
    float    alpha;
    float   _objectCBpad; // padding 16 bytes
};

struct Light
{
    uint    type; // 0 = dir, 1 = point
    float3  color;
    float   intensity;
    float3  direction; // ou position si point
    float   range;
};

cbuffer LightBuffer : register(b2)
{
    Light   lights[MAX_LIGHTS];
    uint    lightCount;
};

// slot t0 : table SRV textures
Texture2D textures : register(t0);

// slot s0 : sampler lineaire
SamplerState linearClamp : register(s0);


//-----------------------------------------------------------------------------//
// Structs hlsl
//-----------------------------------------------------------------------------//

//struct VSInput // VSmain in
//{
//    float3 position : POSITION;
//    float4 color    : COLOR;
//    float2 uv : TEXCOORD0;
//    float3 normal : NORMAL; // ajouté
//    //uint   material : TEXCOORD1;
//};
//struct PSInput // VSmain out
//{
//    float4 positionH : SV_POSITION; 
//    float4 color     : COLOR; 
//    float2 uv : TEXCOORD0;
//};
struct VSInput
{
    float3 position : POSITION;
    float4 color    : COLOR;
    float2 uv       : TEXCOORD0;
    float3 normal   : NORMAL;
};

struct PSInput
{
    float4 positionH : SV_POSITION;
    float4 color     : COLOR;
    float2 uv        : TEXCOORD0;
    float3 worldPos  : TEXCOORD1;
    float3 worldN    : TEXCOORD2;
};



//-----------------------------------------------------------------------------//
// Fonctions hlsl
//-----------------------------------------------------------------------------//

PSInput VSMain(VSInput input)
{
    PSInput output;

    // monde -> clip
    float4 worldPos = mul(float4(input.position, 1), worldMatrix);
    output.positionH = mul(mul(worldPos, viewMatrix), projectMatrix);

    output.uv = input.uv;
    output.color = input.color;
    output.worldPos = worldPos.xyz;

    // transforme la normale (pas de translation)
    output.worldN = normalize(mul(float4(input.normal, 0), worldMatrix).xyz);

    return output;
}

float4 PSMain(PSInput input) : SV_Target
{
    //float4 c = textures.Sample(linearClamp, input.uv);
    //c.a *= alpha;
    //return c;
    
    // sample albedo
    float3 baseColor = textures.Sample(linearClamp, input.uv).rgb;

    //float3 camPos = mul(float4(0, 0, 0, 1), invViewMatrix).xyz;

    float3 N = normalize(input.worldN);
    float3 V = normalize(camPos - input.worldPos);

    float3 accum = float3(0, 0, 0);

    [unroll]
    for (int i = 0; i < lightCount; ++i)
    {
        Light L = lights[i];

        float3 Ldir;
        float att = 1.0;

        if (L.type == 0) // directionnelle
        {
            Ldir = normalize(-L.direction);
        }
        else // ponctuelle
        {
            float3 toL = L.direction - input.worldPos;
            float dist = length(toL);
            if (dist > L.range)
                continue;
            Ldir = toL / dist;
            att = saturate(1 - dist / L.range);
        }

        // Lambert
        float NdotL = saturate(dot(N, Ldir));
        float3 diff = L.color * L.intensity * NdotL * att;

        // Blinn?Phong
        float3 H = normalize(Ldir + V);
        float NdotH = saturate(dot(N, H));
        float shininess = 32; // ou a tex­turer plus tard
        float3 spec = L.color * L.intensity * pow(NdotH, shininess) * att;

        accum += diff + spec;
    }

    float3 litColor = baseColor * accum;
    return float4(litColor, alpha);
}
