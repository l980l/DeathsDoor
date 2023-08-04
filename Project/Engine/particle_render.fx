#ifndef _PARTICLE_RENDER
#define _PARTICLE_RENDER

#include "value.fx"
#include "struct.fx"


// ========================
// Particle Render Shader
// mesh : RectMesh

// Parameter
// g_int_0 : Particle Index
// =========================

StructuredBuffer<tParticle> ParticleBuffer : register(t20);
StructuredBuffer<tParticleModule> ParticleModuleData : register(t21);
#define ModuleData                  ParticleModuleData[0]

struct VS_IN
{
    float3 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

struct VS_OUT
{
    float3 vPos : POSITION;
    uint iInstID : SV_InstanceID;
};

VS_OUT VS_ParticleRender(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
     
    output.vPos = _in.vPos;
    output.iInstID = _in.iInstID;
    
    return output;
}

// GeometryShader ���
// 1. ���������� ����
// 2. ������ ó�� (ī�޶� �ٶ󺸴�..)
struct GS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    uint iInstID : SV_InstanceID;
};

[maxvertexcount(6)]
void GS_ParticleRender(point VS_OUT _in[1], inout TriangleStream<GS_OUT> _outstream)
{
    uint id = _in[0].iInstID;
    
    if (0 == ParticleBuffer[id].Active)
        return;
    tParticle particle = ParticleBuffer[id];
    
    float3 vParticleViewPos = mul(float4(particle.vWorldPos.xyz, 1.f), g_matView).xyz;
    float2 vParticleScale = particle.vWorldScale.xy * particle.ScaleFactor;
   
    // 0 -- 1
    // |    |
    // 3 -- 2
    float3 NewPos[4] =
    {
        float3(-vParticleScale.x / 2.f, +vParticleScale.y / 2.f, 0.f),
        float3(+vParticleScale.x / 2.f, +vParticleScale.y / 2.f, 0.f),
        float3(+vParticleScale.x / 2.f, -vParticleScale.y / 2.f, 0.f),
        float3(-vParticleScale.x / 2.f, -vParticleScale.y / 2.f, 0.f)
    };
    
  
    if (ModuleData.Render)
    {
        if (ModuleData.VelocityScale)
        {
            // ���� ��ƼŬ�� �ӷ��� �˾Ƴ���.
            float fCurSpeed = length(particle.vVelocity);
            if (ModuleData.MaxSpeed < fCurSpeed)
                fCurSpeed = ModuleData.MaxSpeed;
            
            // �ִ�ӵ� ��� ���� �ӵ��� ������ ���Ѵ�.
            float fRatio = saturate(fCurSpeed / ModuleData.MaxSpeed);
          
            // ������ �´� ũ�⺯ȭ���� ���Ѵ�.
            float3 vDefaultScale = float3(1.f, 1.f, 1.f);
            float3 fScale = vDefaultScale + (ModuleData.vMaxVelocityScale.xyz - vDefaultScale) * fRatio;
                      
            NewPos[0] = NewPos[0] * fScale;
            NewPos[3] = NewPos[3] * fScale;
        }
        
        
        if (ModuleData.VelocityAlignment)
        {
            // ��ƼŬ ���� ���� �ӵ��� View �������� ��ȯ
            float3 vVelocity = normalize(particle.vVelocity);
            vVelocity = mul(float4(vVelocity, 0.f), g_matView).xyz;
                       
            // ��ƼŬ Right ����� �̵� ������ �����ؼ� �� ������ ������ ���Ѵ�.
            float3 vRight = float3(1.f, 0.f, 0.f);
            float fTheta = acos(dot(vRight, vVelocity));
            
            // ������ ����� �ڻ��� ������ �������� �ϱ� ������, 2���� ���� �ݴ�� ������ �ش�.
            if (vVelocity.y < vRight.y)
            {
                fTheta = (2.f * 3.1415926535f) - fTheta;
            }
            
            // ���� ������ Z �� ȸ�� ����� �����.
            float3x3 matRotZ =
            {
                cos(fTheta), sin(fTheta), 0,
                -sin(fTheta), cos(fTheta), 0,
                          0, 0, 1.f,
            };
            
            // 4���� ������ ȸ����Ų��.
            for (int i = 0; i < 4; ++i)
            {
                NewPos[i] = mul(NewPos[i], matRotZ);
            }
        }
    }
        
    GS_OUT output[4] = { (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f, (GS_OUT) 0.f };
    
    if (ModuleData.Animation)
    {
        int CurFrm = int(particle.NomalizedAge * ModuleData.FrmCount);
        float2 LeftTop = ModuleData.LeftTop;
        float2 Slice = ModuleData.Slice;
        int YCount = 0;
        if (CurFrm >= ModuleData.XCount)
        {
            YCount = CurFrm / ModuleData.XCount;
            while (CurFrm < ModuleData.XCount)
            {
                CurFrm -= ModuleData.XCount;
            }
        }
        LeftTop = float2(LeftTop.x + (CurFrm * Slice.x), LeftTop.y + (YCount * Slice.y));
        
        output[0].vUV = LeftTop - ModuleData.Offset;
        output[1].vUV = float2(LeftTop.x + Slice.x, LeftTop.y) - ModuleData.Offset;
        output[2].vUV = LeftTop + Slice - ModuleData.Offset;
        output[3].vUV = float2(LeftTop.x, LeftTop.y + Slice.y) - ModuleData.Offset;
    }
    else
    {
        output[0].vUV = float2(0.f, 0.f);
        output[1].vUV = float2(1.f, 0.f);
        output[2].vUV = float2(1.f, 1.f);
        output[3].vUV = float2(0.f, 1.f);
    }
    
    output[0].vPosition = mul(float4(NewPos[0] + vParticleViewPos, 1.f), g_matProj);
    output[0].vUV = float2(0.f, 0.f);
    output[0].iInstID = id;
    
    output[1].vPosition = mul(float4(NewPos[1] + vParticleViewPos, 1.f), g_matProj);
    output[1].vUV = float2(1.f, 0.f);
    output[1].iInstID = id;
    
    output[2].vPosition = mul(float4(NewPos[2] + vParticleViewPos, 1.f), g_matProj);
    output[2].vUV = float2(1.f, 1.f);
    output[2].iInstID = id;
    
    output[3].vPosition = mul(float4(NewPos[3] + vParticleViewPos, 1.f), g_matProj);
    output[3].vUV = float2(0.f, 1.f);
    output[3].iInstID = id;
    
    
    // ���� ����
    _outstream.Append(output[0]);
    _outstream.Append(output[1]);
    _outstream.Append(output[2]);
    _outstream.RestartStrip();
    
    _outstream.Append(output[0]);
    _outstream.Append(output[2]);
    _outstream.Append(output[3]);
    _outstream.RestartStrip();
}

struct PS_OUT
{
    float4 vColor : SV_Target0;
    float4 vEmissive : SV_Target4;
};

PS_OUT PS_ParticleRender(GS_OUT _in)
{
    float4 vOutColor = float4(1.f, 0.f, 1.f, 1.f);
    
    if (g_btex_0)
    {
        vOutColor = g_tex_0.Sample(g_sam_0, _in.vUV);
        vOutColor.rgb *= ParticleBuffer[_in.iInstID].vColor.rgb;
    }
    
    PS_OUT output = (PS_OUT) 0.f;
    
    if (g_int_0)
    {
        output.vEmissive = float4(vOutColor);
    }
    else
    {
        output.vColor = float4(vOutColor);
        output.vEmissive = float4(0.f, 0.f, 0.f, 1.f);
    }
        
    
    return output;
}


#endif
