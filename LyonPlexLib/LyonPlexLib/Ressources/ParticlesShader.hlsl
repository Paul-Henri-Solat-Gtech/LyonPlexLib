
//static const uint kMaxParticles = 1000;

//struct Particle
//{
//    float3 position;
//    float3 velocity;
//    float4 color;
//    float size;
//    float age;
//    float lifetime;
//};

//// Compute
//cbuffer CSParams : register(b0)
//{
//    float dt;
//    float totalTime;
//    float gravity;
//};

//RWStructuredBuffer<Particle> particlesCompute : register(u0);


//[numthreads(256, 1, 1)]
//void CSMain(uint3 id : SV_DispatchThreadID)
//{
//    if (id.x >= kMaxParticles)
//        return;
    
//    Particle p = particlesCompute[id.x];
//    p.age += dt;   
    
//    if (p.age >= p.lifetime)
//    {
//        //p.position = float3(0, 4, 0);
//        p.position = float3(320, 3, 60);
//        p.velocity = float3(0, 0, 0);
//        //p.velocity = float3(frac(sin(id.x * 12.9898) * 43758), frac(cos(id.x * 78) * 43758), 0) * 0.5;
//        //p.velocity = float3(frac(sin(id.x * 12.9898) * 43758.5453), frac(cos(id.x * 78.233) * 43758.5453), 0) * 0.5;
//        p.age = 0;
//        p.lifetime = 1 + frac(sin(totalTime * 1.3)) * 0.5;
//        p.color = float4(1, 1, 1, 1);
//        //p.size = 0.1;
//        p.size = 2.0;
//    }
//    else
//    {
//        p.velocity += float3(0, gravity, 0) * dt;
//        p.position += p.velocity * dt;
//    }
    
//    if (id.x == 0)
//    {
//        p.position = float3(0, 0, 5); // au centre, Z=5
//        p.position = float3(320, 4, 65);
//        p.size = 1.0; // taille visible
//        p.color = float4(1, 1, 1, 1);
//        p.age = 0;
//        p.lifetime = 1000;
//    }
//    particlesCompute[id.x] = p;
//}

//// Rendering
//Texture2D smokeTex : register(t0);
//StructuredBuffer<Particle> particlesRender : register(t1);
//SamplerState samp : register(s0);
//cbuffer VSParams : register(b1)
//{
//    matrix viewProj;
//};
//cbuffer PSParams : register(b2)
//{
//    float sizeMultiplier;
//    float gravity_PS;       // SUPPR ?
//    float4 globalColor;
//    uint blendMode;
//};
//struct VSIn
//{
//    uint vId : SV_VertexID;
//    uint iId : SV_InstanceID;
//};
//struct VSOut
//{
//    float4 pos : SV_Position;
//    float2 uv : TEXCOORD0;
//    float4 col : COLOR;
//};
////VSOut VSMain(VSIn IN)
////{
////    VSOut O;
////    Particle p = particlesRender[IN.iId];
////    p.size *= sizeMultiplier;
////    p.color *= globalColor;
////    float2 q[4] = { { -0.5, -0.5 }, { -0.5, 0.5 }, { 0.5, -0.5 }, { 0.5, 0.5 } };
////    float2 loc = q[IN.vId] * p.size;
////    float4 wp = float4(p.position.xy + loc, p.position.z, 1);
////    O.pos = mul(wp, viewProj);
////    O.uv = float2(loc.x < 0 ? 0 : 1, loc.y < 0 ? 1 : 0);
////    O.col = p.color;
////    return O;
////}

//VSOut VSMain(VSIn IN)
//{
//    VSOut O;
//    Particle p = particlesRender[IN.iId];

//    // coins du quad centré
//    float2 quad[4] =
//    {
//        { -0.5, -0.5 },
//        { -0.5, +0.5 },
//        { +0.5, -0.5 },
//        { +0.5, +0.5 }
//    };

//    float2 loc = quad[IN.vId] * p.size;
//    float4 worldPos = float4(p.position.xy + loc, p.position.z, 1);
//    O.pos = mul(worldPos, viewProj);
//    O.uv = quad[IN.vId] * 0.5f + 0.5f; // de [-.5,.5] à [0,1]
//    O.col = p.color;
//    return O;
//}

//float4 PSMain(VSOut IN) : SV_Target
//{
//    float4 t = smokeTex.Sample(samp, IN.uv);
//    return t * IN.col;
//}

/* ParticlesShader.hlsl */
//struct Particle
//{
//    float3 position;
//    float size;
//    float4 color;
//};
//cbuffer VSParams : register(b0)
//{
//    matrix viewProj;
//};
//StructuredBuffer<Particle> buf : register(t0);

//struct VSOut
//{
//    float4 pos : SV_POSITION;
//    float4 col : COLOR;
//};
//VSOut VSMain(uint vID : SV_VertexID, uint iID : SV_InstanceID)
//{
//    Particle p = buf[iID];
//    float2 quad[4] = { { -0.5, -0.5 }, { 0.5, -0.5 }, { -0.5, 0.5 }, { 0.5, 0.5 } };
//    float2 loc = quad[vID] * p.size;
//    float4 wp = float4(p.position.xy + loc, p.position.z, 1);
//    VSOut o;
//    o.pos = mul(wp, viewProj);
//    o.col = p.color;
//    return o;
//}
//float4 PSMain(VSOut IN) : SV_TARGET
//{
//    return IN.col;
//}

// ParticlesShader.hlsl
struct Particle
{
    float3 position;
    float size;
    float4 color;
};

cbuffer VSParams : register(b0)
{
    matrix viewProj;
};

StructuredBuffer<Particle> buf : register(t0);

struct VSOut
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

VSOut VSMain(uint vID : SV_VertexID, uint iID : SV_InstanceID)
{
    Particle p = buf[iID];
    float2 quad[4] = { { -0.5, -0.5 }, { 0.5, -0.5 }, { -0.5, 0.5 }, { 0.5, 0.5 } };
    float2 loc = quad[vID] * p.size;
    float4 wp = float4(p.position.xy + loc, p.position.z, 1);
    VSOut o;
    o.pos = mul(wp, viewProj);
    o.col = p.color;
    return o;
}

float4 PSMain(VSOut IN) : SV_TARGET
{
    return IN.col;
}