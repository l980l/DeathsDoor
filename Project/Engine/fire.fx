#ifndef _FIRE
#define _FIRE

#include "value.fx"
#include "func.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
    
    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;
    
    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;
    
    // Instancing �� ������
    //row_major matrix matWorld : WORLD;
    //row_major matrix matWV : WV;
    //row_major matrix matWVP : WVP;
    //int iRowIdx : ROWINDEX; // Animaion ��� ��

    uint iInstanceID : SV_InstanceID;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    
    float3 vViewPos : POSITION;
    
    float3 vVeiwNormal : NORMAL;
    float3 vViewTangent : TANGENT;
    float3 vViewBinormal : BINORMAL;
};

struct PS_OUT
{
    float4 vDiff : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
    float4 vDiffLight : SV_Target3; //���۵� �ܰ迡�� �̸� ���� ����Ʈ Ÿ�ٿ� �־���� �׸��ڿ� �ɸ����� �������� . 
                                    //���� , ����Ʈ Ÿ���� ������ ���ó���� �Ҽ��� �ִ� 
    
    float4 pDOFDepthTex : SV_Target4;
};

VS_OUT VS_Fire(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    // ���� �����̽��� ��ġ �� ���� ���͸� ViewSpace ���� ��ȯ �� �ȼ� ���̴��� ����
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    output.vVeiwNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;

    return output;
}

PS_OUT PS_Fire(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT) 0.f;
    
    float3 vViewNormal = _in.vVeiwNormal;
    
    float4 BrighterColor = g_vDiff;
    float4 MiddleColor = g_vAmb;
    float4 DarkerColor = g_vSpec;
  
    float2 UV = _in.vUV + float2(0, g_AccTime / 2.f);
    
    float NoiseTex = g_tex_0.Sample(g_sam_0, UV).x;
    float gradientValue = g_tex_1.Sample(g_sam_0, _in.vUV).x;

    float step1 = step(NoiseTex, gradientValue);
    float step2 = step(NoiseTex, gradientValue - 0.3);
    float step3 = step(NoiseTex, gradientValue - 0.5);
    
    //if (step1 == 0.0f) 
    //    clip(-1);
  
    float4 c = float4(lerp(BrighterColor, DarkerColor, step1 - step2));
    
    output.vDiff.xyz = lerp(c.rgb, MiddleColor.rgb, step2 - step3);
    
    if (_in.vUV.x < 0.3f)
    {
        output.vDiff.xyz = g_vEmv;
    }
 
          
    //output.vDiff = vObjectColor;
    output.vNormal.xyz = vViewNormal;
    output.vPosition.xyz = _in.vViewPos;
    
    
     {
        //float4 vWorldPos = mul( , g_matViewInv); // ����ī�޶� view ������� ���ؼ� ������ǥ�� �˾Ƴ���.
        float4 vProj = mul(float4(_in.vViewPos, 1.f), g_matProj); // ������Ų ��ǥ ���ϱ�
        float fDepth = vProj.z / vProj.w; // w �� ������ ���� ������ǥ z ���� ���Ѵ�.(�ùٸ��� ���ϱ� ���ؼ�)
        
        
        float4 fDOFDistance = float4(fDepth, 0.f, 0.f, 0.f);
        
        float Distance = (float) fDOFDistance;
        
        if (Distance + 0.0015f < fDepth)
        {
            float Diff = (fDepth - 0.0015f - Distance) * 2000.f;
        //output.vDiff = float4(1.0f, 0.0f, 1.0f - Diff, 1.0f);
            output.pDOFDepthTex.r = Diff;
        }
    }

    return output;
}

#endif