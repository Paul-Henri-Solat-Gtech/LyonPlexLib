
static const uint MAX_LIGHTS = 2;


//-----------------------------------------------------------------------------//
// Data provenant du moteur
//-----------------------------------------------------------------------------//

cbuffer CameraBuffer : register(b0)
{
    float4x4 viewMatrix;
    float4x4 projectMatrix;
    float3 camPos;
    float _camCBpad; 
};
cbuffer ObjectBuffer : register(b1)
{
    float4x4 worldMatrix;
    uint materialIndex;
    float alpha;
    uint materialFlags; // bit 0 = useQuickGamma
    float _objectCBpad[1];
};

struct Light
{
    uint type;
    float3 color;
    float intensity;
    float3 direction;
    float range;
    float _pad[3];
};

// CBV #1 : juste le count
cbuffer LightCountCB : register(b2)
{
    uint lightCount;
    float3 _pad; // pour aligner  16
};

// CBV #2 : juste l�array
cbuffer LightArrayCB : register(b3)
{
    Light lights[MAX_LIGHTS]; // 8x48 = 384 bytes
};

// slot t0 : table SRV textures
Texture2D textures : register(t0);

// slot s0 : sampler lineaire
SamplerState linearClamp : register(s0);


//-----------------------------------------------------------------------------//
// Structs hlsl
//-----------------------------------------------------------------------------//

struct VSInput
{
    float3 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PSInput
{
    float4 positionH : SV_POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
    float3 worldPos : TEXCOORD1;
    float3 worldN : TEXCOORD2;
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
    const float GAMMA = 2.3;
    float4 tex = textures.Sample(linearClamp, input.uv);
    float outAlpha = tex.a * alpha;
    if (outAlpha < 0.001)
        discard;

    float3 baseColor = tex.rgb;

    bool useQuick = (materialFlags & 1) != 0;

    if (outAlpha < 0.999)
    {
        // ambient only pour pixels partiellement transparents
        float3 ambient = float3(0.6, 0.6, 0.6);
        float3 result = baseColor * ambient;
        if (useQuick)
            result = pow(result, 1.0 / GAMMA);
        return float4(result, outAlpha);
    }

    // opaque : éclairage complet
    float3 N = normalize(input.worldN);
    float3 V = normalize(camPos - input.worldPos);
    float3 accum = float3(0.6, 0.6, 0.6);
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

        // Blinn-Phong spec
        float3 H = normalize(Ldir + V);
        float NdotH = saturate(dot(N, H));
        float shininess = 32.0;
        float3 spec = L.color * L.intensity * pow(NdotH, shininess) * att;

        accum += diff + spec;
    }

    float3 lit = baseColor * accum;
    if (useQuick)
        lit = pow(lit, 1.0 / GAMMA);

    return float4(lit, outAlpha);
}
