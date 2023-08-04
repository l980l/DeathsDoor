#ifndef _LIGHT
#define _LIGHT

#include "value.fx"
#include "struct.fx"
#include "func.fx"

// ========================
// Directional Light Shader
// mesh : RectMesh
// g_int_0 : Light Index
// g_mat_0 : (LightView * LightProj) Matrix
// 
// g_tex_0 : Position Target
// g_tex_1 : Normal Target
// g_tex_3 : Shadow DepthMap
// ========================

struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV  : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV       : TEXCOORD;
};

VS_OUT VS_DirLightShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ȭ�� ��ü�� �ȼ��� ȣ���ϱ� ���� RectMesh�� 
    // ���� ������ 2��� Ȯ����� MDC ��ǥ�� ��ü�� Ȯ��
    output.vPosition = float4(_in.vPos.xyz * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}


struct PS_OUT
{
    float4 vDiffuse  : SV_Target0;
    float4 vSpecular : SV_Target1;
};

PS_OUT PS_DirLightShader(VS_OUT _in)
{ 
    PS_OUT output = (PS_OUT) 0.f;
    
    // Position ����
    float3 vViewPos = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;
    
    // �޾ƿ� ��ġ ������ ���ٸ�(0.f, 0.f, 0.f) ȣ������ ����.
    if (!any(vViewPos.xyz))
        discard;
    
    // ������� �Դٸ� ��ġ ������ �ִ� ���̹Ƿ� ���� ��ġ�� �븻���� �����ͼ� ��������� ��.
    float3 vViewNormal = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
    
    tLightColor lightcolor = (tLightColor) 0.f;
    CalcLight3D(vViewPos, vViewNormal, g_int_0, lightcolor);
    
    // �׸��� ����
    // ViewPos -> WorldPos 
    float3 vWorldPos = mul(float4(vViewPos.xyz, 1.f), g_matViewInv).xyz;
    
    // WorldPos -> Light ����
    float4 vLightProj = mul(float4(vWorldPos, 1.f), g_mat_0);

    // w �� ������ ���� xy ������ǥ�� ����
    vLightProj.xyz /= vLightProj.w;

    // ���ø��� ���� ������ǥ�踦 UV ��ǥ��� ��ȯ
    float fShadowPow = 0.f;
    float2 vDepthMapUV = float2((vLightProj.x / 2.f) + 0.5f, -(vLightProj.y / 2.f) + 0.5f);
    float fDepth = g_tex_3.Sample(g_sam_0, vDepthMapUV).r;

    // ������ ��ϵ� ���̺��� ��ü�� ���̰� �� �� ��, �׸��� ����
    if (0.f != fDepth
        && 0.f <= vDepthMapUV.x && vDepthMapUV.x <= 1.f
        && 0.f <= vDepthMapUV.y && vDepthMapUV.y <= 1.f
        && vLightProj.z >= fDepth + 0.0001f)
    {
        fShadowPow = 0.9f;
    }
    
    output.vDiffuse = lightcolor.vDiffuse * saturate(1.f - fShadowPow) + lightcolor.vAmbient;
    output.vDiffuse = ceil(output.vDiffuse * 3) / 3.f;
    output.vSpecular = lightcolor.vSpecular * saturate(1.f - fShadowPow);
      
    // ImGui���� Ȯ���� �� �ֵ��� ���İ��� 1�� �־���.
    output.vDiffuse.a = 1.f;
    output.vSpecular.a = 1.f;
    
    return output;
}


//BLOOM======================
//VS_OUT VS_Bloom(VS_IN _in)
//{
//    VS_OUT output = (VS_OUT) 0.f;

//    float3 dirX = g_matWV[0];
//    float3 dirY = g_matWV[1];
    
//    float radius = 30.f;
    
//    float3 pos = _in.vPos + radius * (output.vPosition.x * dirX + output.vPosition.y * dirY);
//    output.vPosition = mul(g_matProj, float4(pos, 1));
//    output.vUV = 0.5 * output.vPosition.xy + 0.5;
//    return output;
//}


//PS_OUT PS_Bloom(VS_OUT _in)
//{
//    PS_OUT output = (PS_OUT) 0.f;
//    float4 corona = g_tex_2.Sample(g_sam_0, _in.vUV);
//    float strenth = 2.64f;
    
//     // Position ����
//    float3 vViewPos = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;
    
//    // �޾ƿ� ��ġ ������ ���ٸ�(0.f, 0.f, 0.f) ȣ������ ����.
//    if (!any(vViewPos.xyz))
//        discard;
    
//    // ������� �Դٸ� ��ġ ������ �ִ� ���̹Ƿ� ���� ��ġ�� �븻���� �����ͼ� ��������� ��.
//    float3 vViewNormal = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
    
//    tLightColor lightcolor = (tLightColor) 0.f;
//    CalcLight3D(vViewPos, vViewNormal, g_int_0, lightcolor);
    
//    output.vDiffuse = strenth * pow(0.8, 10.4) * corona * lightcolor.vDiffuse;
//    return output;
//}



// ========================
// Point Light Shader
// mesh : SphereMesh
// g_int_0 : Light Index
// g_tex_0 : Position Target
// g_tex_1 : Normal Target
// ========================
VS_OUT VS_PointLightShader(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // PointLight�� ȭ�� �Ϻθ� �����ϴ� Light�̱� ������
    // ȭ���� ��� �κп� �����ϴ� �� �� �� �ִ� �ȼ� ��ǥ�� ��ȯ�Ͽ� �Ѱ���.
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
        
    return output;
}

PS_OUT PS_PointLightShader(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    // �ȼ� ��ǥ�� �ػ󵵷� ���� ȭ�� ������ �����ġ�� �˰� ��.
    // �ش� Obj�� ��ġ�� �ƴ� Obj�� ��ġ�� ���Ե� ��ó�� ���̴� �ȼ��� ��ġ�� ���ϱ� ���� ���
    float2 vUV = _in.vPosition.xy / g_Resolution;
    
    float3 vViewPos = g_tex_0.Sample(g_sam_0, vUV).xyz;    
    float3 vWorldPos = mul(float4(vViewPos, 1.f), g_matViewInv);
    float3 vLocalPos = mul(float4(vWorldPos, 1.f), g_matWorldInv);
    
    // ���� ��鿡�� Sphere ���� �ȿ� ���Ե� �ȼ���
    // Sphere Mesh�� ���� ��ǥ��� �Ű��� �� Sphere ���� �ȿ� ���Եȴٸ�
    // ���� �ȿ� �ִ� ���̹Ƿ� ������ ����ϰ� �ƴ϶�� discard
    if (length(vLocalPos) <= 0.5f)
    {
        tLightColor lightcolor = (tLightColor) 0.f;
        float3 vViewNormal = g_tex_1.Sample(g_sam_0, vUV).xyz;
        CalcLight3D(vViewPos, vViewNormal, g_int_0, lightcolor);
        
        output.vDiffuse  = lightcolor.vDiffuse + lightcolor.vAmbient;
        output.vSpecular = lightcolor.vSpecular;
        
        output.vDiffuse.a  = 1.f;
        output.vSpecular.a = 1.f;
    }
    // �޾ƿ� ��ġ ������ ���ٸ�(0.f, 0.f, 0.f) ȣ������ ����.
    else
    {
        discard;
    }
    
    return output;
}

// ========================
// Spot Light Shader
// mesh : Cone
// g_int_0 : Light Index
// g_tex_0 : Position Target
// g_tex_1 : Normal Target
// ========================

VS_OUT VS_SpotLight(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // PointLight�� ȭ�� �Ϻθ� �����ϴ� Light�̱� ������
    // ȭ���� ��� �κп� �����ϴ� �� �� �� �ִ� �ȼ� ��ǥ�� ��ȯ�Ͽ� �Ѱ���.
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    
    return output;
}
    
PS_OUT PS_SpotLight(VS_OUT _in)
{
    PS_OUT output = (PS_OUT) 0.f;
    
    // �ȼ� ��ǥ�� �ػ󵵷� ���� ȭ�� ������ �����ġ�� �˰� ��.
    // �ش� Obj�� ��ġ�� �ƴ� Obj�� ��ġ�� ���Ե� ��ó�� ���̴� �ȼ��� ��ġ�� ���ϱ� ���� ���
    float2 vUV = _in.vPosition.xy / g_Resolution;
    
    float3 vViewPos =  g_tex_0.Sample(g_sam_0, vUV).xyz;
    float3 vWorldPos = mul(float4(vViewPos,  1.f), g_matViewInv);
    float3 vLocalPos = mul(float4(vWorldPos, 1.f), g_matWorldInv);
    
    // ���� ��鿡�� Sphere ���� �ȿ� ���Ե� �ȼ���
    // Sphere Mesh�� ���� ��ǥ��� �Ű��� �� Sphere ���� �ȿ� ���Եȴٸ�
    // ���� �ȿ� �ִ� ���̹Ƿ� ������ ����ϰ� �ƴ϶�� discard
    if (length(vLocalPos) <= 0.5f)
    {
        tLightColor lightcolor = (tLightColor) 0.f;
        float3 vViewNormal = g_tex_1.Sample(g_sam_0, vUV).xyz;
        CalcLight3D(vViewPos, vViewNormal, g_int_0, lightcolor);
        
        output.vDiffuse = lightcolor.vDiffuse + lightcolor.vAmbient;
        output.vSpecular = lightcolor.vSpecular;
        
        output.vDiffuse.a  = 1.f;
        output.vSpecular.a = 1.f;
    }
    else
    {
        discard;
    }
    
    return output;
}


// ========================
// Light Merge Shader
// mesh : RectMesh
// g_tex_0 : ColorTarget
// g_tex_1 : DiffuseTarget
// g_tex_2 : SpecularTarget
// g_tex_3 : EmissiveTarget
// ========================
VS_OUT VS_LightMerge(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.vPosition = float4(_in.vPos.xyz * 2.f, 1.f);
    output.vUV = _in.vUV;
    
    return output;
}

float4 PS_LightMerge(VS_OUT _in) : SV_Target0
{
    float4 vOutColor = (float4) 0.f;
    
    // MRT�� ��ϵ� ���� �� ��¿� �ʿ��� Color, Light ������ ���� �����.
    float3 Color    = g_tex_0.Sample(g_sam_0, _in.vUV).xyz;
    float3 Diffuse  = g_tex_1.Sample(g_sam_0, _in.vUV).xyz;
    float3 Specular = g_tex_2.Sample(g_sam_0, _in.vUV).xyz;
    float3 Emissive = g_tex_3.Sample(g_sam_0, _in.vUV).xyz;
    
    vOutColor.xyz = (Color * Diffuse) + Emissive + Specular;
    vOutColor.a = 1.f;
    
    return vOutColor;
}


// ===============
// DepthMap Shader
// MRT : ShadowMap MRT
// RS : CULL_BACK
// BS : Default
// DS : Less
// ===============
struct VS_DEPTH_IN
{
    float3 vPos : POSITION;
   
    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;

    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;
};

struct VS_DEPTH_OUT
{
    float4 vPosition : SV_Position;
    float4 vProjPos : POSITION;
};

VS_DEPTH_OUT VS_DepthMap(VS_DEPTH_IN _in)
{
    VS_DEPTH_OUT output = (VS_DEPTH_OUT) 0.f;
        
    if (g_iAnim)
    {
        Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices, 0);
    }
    
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vProjPos  = output.vPosition;

    return output;
}

float PS_DepthMap(VS_DEPTH_OUT _in) : SV_Target
{
    float fOut = 0.f;
    fOut = _in.vProjPos.z / _in.vProjPos.w;
    return fOut;
}

#endif