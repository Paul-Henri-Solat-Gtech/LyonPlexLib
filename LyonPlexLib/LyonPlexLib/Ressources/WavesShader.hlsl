//// WaterVS.hlsl
//tcbuffer CB : register(b0) {float4x4 worldViewProj;float2 scrollOffset;};
//struct VS_IN
//{
//    float3 pos : POSITION;
//    float2 uv : TEXCOORD;
//};
//struct PS_IN
//{
//    float4 pos : SV_POSITION;
//    float2 uv : TEXCOORD;
//};
//PS_IN main(VS_IN input)
//{
//    PS_IN o;
//    o.pos = mul(worldViewProj, float4(input.pos, 1));
//    o.uv = input.uv + scrollOffset;
//    return o;
//}

//// WaterPS.hlsl
//texture2D normalMap : register(t0);
//textureCube envMap : register(t1);
//sampler samp : register(s0);
//struct PS_IN
//{
//    float4 pos : SV_POSITION;
//    float2 uv : TEXCOORD;
//};
//float4 main(PS_IN input) : SV_TARGET
//{
//    float3 normal = normalize(normalMap.Sample(samp, input.uv).xyz * 2 - 1);
//    float3 viewDir = float3(0, 1, 0); // caméra au-dessus
//    float3 reflDir = reflect(viewDir, normal);
//    float4 refl = envMap.Sample(samp, reflDir);
//    float3 baseColor = float3(0.0, 0.3, 0.5);
//    float3 color = baseColor + refl.rgb * 0.5;
//    return float4(color, 1);
//}


//// WaterVS.hlsl

//cbuffer CameraCB : register(b0)
//{
//    float4x4 view;
//    float4x4 proj;
//    float3 camPos;
//};

//cbuffer CB : register(b1)
//{
//    float4x4 world;
//    float2 scrollOffset;
//};

//struct VS_IN
//{
//    float3 pos : POSITION;
//    float2 uv : TEXCOORD;
//};

//struct PS_IN
//{
//    float4 pos : SV_POSITION;
//    float2 uv : TEXCOORD;
//};

//PS_IN VSMain(VS_IN input)
//{
    
//    PS_IN output;

//    float4 worldPos = mul(float4(input.pos, 1.0), world);
//    float4 viewPos = mul(worldPos, view);
//    float4 projPos = mul(viewPos, proj);
//    output.pos = projPos;
//    output.uv = input.uv + scrollOffset;
    
//    return output;
//}

//// WaterPS.hlsl
//Texture2D normalMap : register(t0);
//TextureCube envMap : register(t1);
//SamplerState samp : register(s0);


//float4 PSMain(PS_IN input) : SV_TARGET
//{
//    float3 n = normalize(normalMap.Sample(samp, input.uv).xyz * 2 - 1);
//    float3 viewDir = float3(0, 1, 0);
//    float3 r = reflect(viewDir, n);
//    float4 refl = envMap.Sample(samp, r);
//    float3 baseColor = float3(0.0, 0.3, 0.5);
//    return float4(baseColor + refl.rgb * 0.8, 1);
//}

cbuffer CameraCB : register(b0)
{
    float4x4 view;
    float4x4 projection;
    float3 camPos;
    float _pad1; // alignement 16 bytes
};

cbuffer WaveCB : register(b1)
{
    float4x4 world;
    float2 scrollOffset;
    float2 _pad2; // alignement 16 bytes
};

Texture2D normalMap : register(t0);
TextureCube envMap : register(t1);

SamplerState sampler0 : register(s0);

struct VSInput
{
    float3 position : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

struct VSOutput
{
    float4 position : SV_POSITION;
    float3 worldPos : TEXCOORD0;
    float2 uv : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

//VSOutput VSMain(VSInput input)
//{
//    VSOutput output;

//    float4 worldPos = mul(float4(input.position, 1.0f), world);
//    float4 viewPos = mul(worldPos, view);
//    float4 projPos = mul(viewPos, projection);

//    output.position = projPos;
//    output.worldPos = worldPos.xyz;
//    output.uv = input.uv + scrollOffset;
    
//    float3 worldNormal = mul(input.normal, (float3x3) world);
//    output.normal = normalize(worldNormal);

//    return output;
//}
VSOutput VSMain(VSInput input)
{
    VSOutput output;

    float4 worldPos = mul(float4(input.position, 1), world);
    float4 viewPos = mul(worldPos, view);

    // Clamp z pour éviter w négatif
    viewPos.z = max(viewPos.z, 0.001f);

    float4 projPos = mul(viewPos, projection);
    projPos.w = max(projPos.w, 0.1f);
    output.position = projPos;
    output.worldPos = worldPos.xyz;
    output.uv = input.uv + scrollOffset;
    
    float3 worldNormal = mul(input.normal, (float3x3) world);
    output.normal = normalize(worldNormal);
    return output;
    
    // ---------
    
    //VSOutput o;
    //o.position = mul(float4(input.position, 1), world); // world CB
    //o.position = mul(o.position, view); // CameraCB.view
    //o.position = mul(o.position, projection); // CameraCB.proj
    //return o;
    
    //float3 N = normalize(normalMap.Sample(sampler0, input.uv).xyz * 2.0 - 1.0);
    //float3 V = normalize(camPos - input.position);

    //// Réflexion simple avec cubemap
    //float3 R = reflect(-V, N);
    //float3 envColor = envMap.Sample(sampler0, R).rgb;

    //float3 baseColor = float3(0.0, 0.3, 0.5);
    //return float4(envColor, 1.0);
}

float4 PSMain(VSOutput input) : SV_TARGET
{
    //float3 N = normalize(normalMap.Sample(sampler0, input.uv).xyz * 2.0 - 1.0);
    //float3 V = normalize(camPos - input.worldPos);

    //// Réflexion simple avec cubemap
    //float3 R = reflect(-V, N);
    //float3 envColor = envMap.Sample(sampler0, R).rgb;

    //// Couleur finale
    //return float4(envColor, 1.0);
    
    // ---------
    
    //return float4(0, 0, 1, 1);
    
    
    // 1) Sample la normal map et reconstruis la normale perturbée
    float3 N = normalize(normalMap.Sample(sampler0, input.uv).xyz * 2.0 - 1.0);

    // 2) Couleur de base de l'eau
    float3 baseColor = float3(0.0, 0.3, 0.5);

    // 3) Effet d'éclat selon l'inclinaison (faux fresnel)
    float fresnel = pow(1 - saturate(N.y), 3);
    float3 colorNear = baseColor * 0.8; // zones “plates”
    float3 colorSlope = baseColor * 1.2; // zones “inclinées”
    float3 finalColor = lerp(colorNear, colorSlope, fresnel);

    // 4) Retourne la couleur finale
    return float4(finalColor, 0.8);
}