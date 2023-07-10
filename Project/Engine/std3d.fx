#ifndef _STD3D
#define _STD3D

#include "value.fx"
#include "struct.fx"
#include "func.fx"

// �� ������ ���� Light3D���� �ϹǷ� �ʿ����

// Light3DInfo
// ���� ������ ������ ����
//static float3 g_LightDir = float3(1.f, -1.f, 0.f);
//static float4 g_LightColor = float4(1.f, 1., 1.f, 1.f);
// ���� ���� �ʴ� �κе� �ּ����� ������ �ֱ� ���� ȯ�汤
//static float4 g_LightAmb = float4(0.15f, 0.15f, 0.15f, 1.f);

// ========================
// Std3D Shader
//
// g_tex_0 : Color Texture
// g_tex_1 : Normal Texture
// ========================


struct VS_IN
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;
   
    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL; 
    float3 vBinormal : BINORMAL;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV : TEXCOORD;
    // ���� ���� �������� ���� ���� ����
    //float fLightPow : FOG;
    
    
    // �ȼ� ���� �������� ���� ViewPos �� ViewNormal
    float3 vViewPos : POSITION;
    
    float3 vViewTangent : TANGENT;
    float3 vViewNormal : NORMAL;    
    float3 vViewBinormal : BINORMAL;
};

VS_OUT VS_Std3D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;    
    
    //==============================================
    // ���� ���� �������� ���̴� ������ ���� �������� �� 
    // ���� ���� ������ ���X
    //==============================================
    
    //// ���� ���� �������� ���� ���� ���� ���
    //// ����Ʈ �ڻ��ι�Ģ
    //float3 vWorldNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWorld));
    //float3 vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    //
    //// ���� ���� ������ �ƴ� ��ü���� ���� ���ϴ� ����� �븻���ͷ� ���� ���⸦ ����� �� ����.
    //float3 vLightDir = -normalize(g_LightDir);    
    //// saturate�� ���� ���Ⱑ ������ �������� �� ����
    //float  fLightPow = saturate(dot(vWorldNormal, vLightDir));
        
    //output.fLightPow = fLightPow;  
          
    // ���������̽� ���� ��ǥ
    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);          
    output.vUV = _in.vUV;
    

    // �ȼ� �������� ���� View�����̽� ���� pos, Normal���� ���
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
        
    // ���忡 �ִ� ��� Obj�� ���� ��ġ�� ���� �޾ƾ� �ϹǷ� �̵����� �ݿ����� ����.
    // Obj�� ǥ����� ���͸� View Space �������� ������.
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV));
    output.vViewNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));    
    
    return output;
}

// Rasterizer�� ���� ���� �ȼ� ȣ��

float4 PS_Std3D(VS_OUT _in) : SV_Target
{        
    // obj ���� ����(ȸ��)
    float4 vObjectColor = float4(0.4f, 0.4f, 0.4f, 1.f);    
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float3 vViewNormal = _in.vViewNormal;
     
    // �ؽ��İ� ������, �ش� ������ ����Ѵ�.
    if(g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
       
    // NomalMap �� �ִٸ�
    if(g_btex_1)
    {
        // �븻�ؽ��Ŀ� �ִ� ���⺤�͵��� ��ǥ�� �������� x, y, z����
        // �̸� ������ǥ��� �������� ���ؼ��� �ش� �ȼ��� �������� �Űܿ;� ��.
        // �Űܿ��� ���ؼ��� �ش� ���⺤�͵��� ǥ�麤�Ϳ� �°� ȸ������� ������� �ϴµ�
        // ���⺤�͵��� ������ �����ϸ� ������ķ� ���� �� �ְ� ��������� ���ϸ� ���� ��� �״�ΰ� �Ǳ� ������
        // ���� obj �ȼ��� �ִ� ���⺤�Ͱ� �� ȸ������� �ȴ�. ���� ������ ������ ���� ����� ���� �� ������.
        float3x3 matRot =
        {
            // ���� ��� ���� ���ҽ��� OpenGL���� ���Ǵ� ���ҽ���
            // OpenGL�� DirextX�� ���̳븻�� ������ �ݴ��̹Ƿ� ���̳븻�� ��������.
            _in.vViewTangent,          
            -_in.vViewBinormal,
            _in.vViewNormal,
        };

        float3 vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);        
        // ������ǥ ���ؿ� �ִ� ���� ��ġ�� ������ǥ�� �������� �Ű���.
        vNormal = normalize((vNormal * 2.f) - 1.f);
        vViewNormal = mul(vNormal, matRot);       
    }    
    
    tLightColor LightColor = (tLightColor) 0.f;
    
    for (int i = 0; i < g_Light3DCount; ++i)
    {
        CalcLight3D(_in.vViewPos, vViewNormal, i, LightColor);
    }
        
    // ���� ����
    vOutColor.xyz = vObjectColor.xyz * LightColor.vDiffuse.xyz
                    + LightColor.vSpecular.xyz
                    + vObjectColor.xyz * LightColor.vAmbient.xyz;
    
    return vOutColor;
}



#endif