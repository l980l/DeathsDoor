#ifndef _DEFERRED
#define _DEFERRED

#include "value.fx"
#include "func.fx"
#include "struct.fx"

// ========================
// Std3D Deferred Shader
//
// g_tex_0 : Color Texture
// g_tex_1 : Normal Texture
// ========================
struct VS_IN
{
    float3 vPos     : POSITION;
    float2 vUV      : TEXCOORD;
   
    float3 vTangent : TANGENT;
    float3 vNormal  : NORMAL;
    float3 vBinormal : BINORMAL;

    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;
};

struct VTX_IN_INST
{
    float3 vPos : POSITION;
    float2 vUV : TEXCOORD;

    float3 vTangent : TANGENT;
    float3 vNormal : NORMAL;
    float3 vBinormal : BINORMAL;

    float4 vWeights : BLENDWEIGHT;
    float4 vIndices : BLENDINDICES;

    // Per Instance Data
    row_major matrix matWorld : WORLD;
    row_major matrix matWV : WV;
    row_major matrix matWVP : WVP;
    uint iRowIndex : ROWINDEX;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float2 vUV       : TEXCOORD;
    
    // 픽셀 단위 라이팅을 위한 ViewPos 및 ViewNormal
    float3 vViewPos  : POSITION;
        
    float3 vViewTangent  : TANGENT;
    float3 vViewNormal   : NORMAL;
    float3 vViewBinormal : BINORMAL;
};

VS_OUT VS_Std3D_Deferred(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
        
    if (g_iAnim)
    {
        Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices, 0);
    }

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos         =           mul(float4(_in.vPos,      1.f), g_matWV);
    output.vViewTangent     = normalize(mul(float4(_in.vTangent,  0.f), g_matWV));
    output.vViewNormal      = normalize(mul(float4(_in.vNormal,   0.f), g_matWV));
    output.vViewBinormal    = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));
    
    return output;
}

VS_OUT VS_Std3D_Deferred_Inst(VTX_IN_INST _in)
{
    VS_OUT output = (VS_OUT)0.f;

    if (g_iAnim)
    {
        Skinning(_in.vPos, _in.vTangent, _in.vBinormal, _in.vNormal, _in.vWeights, _in.vIndices, _in.iRowIndex);
    }

    output.vPosition = mul(float4(_in.vPos, 1.f), _in.matWVP);
    output.vUV = _in.vUV;
    
    output.vViewPos         =           mul(float4(_in.vPos,      1.f), g_matWV);
    output.vViewTangent     = normalize(mul(float4(_in.vTangent,  0.f), g_matWV));
    output.vViewNormal      = normalize(mul(float4(_in.vNormal,   0.f), g_matWV));
    output.vViewBinormal    = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));

    return output;
}


// Rasterizer로 정점 사이 픽셀 호출

struct PS_OUT
{
    float4 vColor       : SV_Target0;
    float4 vNormal      : SV_Target1;
    float4 vPosition    : SV_Target2;
    float4 vData        : SV_Target3;
    float4 vEmissive    : SV_Target4;
};

PS_OUT PS_Std3D_Deferred(VS_OUT _in) : SV_Target
{
    // obj 색상 설정(회색)
    float4 vObjectColor = float4(0.6f, 0.6f, 0.6f, 1.f);
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float3 vViewNormal = _in.vViewNormal;
     
    // 텍스쳐가 있으면, 해당 색상을 사용한다.
    if (g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
       
    // NomalMap 이 있다면
    if (g_btex_1)
    {
        float3x3 matRot =
        {
            // 현재 사용 중인 리소스가 OpenGL에서 사용되는 리소스임
            // OpenGL은 DirextX와 바이노말의 방향이 반대이므로 바이노말을 뒤집어줌.
            _in.vViewTangent,
            -_in.vViewBinormal,
            _in.vViewNormal,
        };

        float3 vNormal = g_tex_1.Sample(g_sam_0, _in.vUV);
        // 로컬좌표 기준에 있는 정점 위치를 투영좌표계 기준으로 옮겨줌.
        vNormal = normalize((vNormal * 2.f) - 1.f);
        vViewNormal = mul(vNormal, matRot);
    }
    
    // 7번 텍스쳐 레지스터에 값이 있다면 CrackTexture임. 이걸 사용.
    if (g_btex_7)
    {
        float4 vCrackTextureColor = g_tex_7.Sample(g_sam_0, _in.vUV);
        
        // 값이 0이 아니라면.
        if (any(vCrackTextureColor))
        {
            vCrackTextureColor *= float4(1.f, 0.1f, 0.35f, 1.f);
            vCrackTextureColor *= (1.f - g_float_0);
            vObjectColor = vObjectColor + vCrackTextureColor;
        }
        
        // paperburn 시작 시간이 들어왔다면.
        if (g_float_1 > 0.f)
        {
            static float fFirstTime = g_float_1;
            
            // 6번 텍스쳐는 NoiseTexture.
            float4 vNoiseTextureColor = g_tex_6.Sample(g_sam_0, _in.vUV);
            float fGrey = (vNoiseTextureColor.r + vNoiseTextureColor.g + vNoiseTextureColor.b) / 3.f;
            
            //threshold on sin time
            float thresh = (1.f - (g_AccTime - fFirstTime) * 0.5f)
            +0.5f;
            float thresh2 = ((1.f - (g_AccTime - fFirstTime) + 0.1f) * 0.5f)
            +0.5f;
    
            if (fGrey > thresh2)
            {
                vObjectColor.r = 1.f;
                vObjectColor.g = 0.1f;
                vObjectColor.b = 0.35f;
            }
    
            if (fGrey > thresh)
            {
                vObjectColor.r = 0.f;
                vObjectColor.g = 0.f;
                vObjectColor.b = 0.f;
                vObjectColor.a = 0.f;
            }
        }
    }
    
    PS_OUT output = (PS_OUT) 0.f;
    
    // 텍스쳐를 이용해서 Emissive를 추출하는 경우.
    if(g_int_0)
    {
        // 알파 값이 양수라면, Color와 Emissive 모두 넣기. Emissive는 0.5만 추출. 이게 원본 게임의 칼과 더 비슷한 느낌이 나기 때문에. 칼을 제외한 bloom 효과들은 텍스쳐를 사용하지 않아서 상관없다.
        if (vObjectColor.a > 0.f)
        {
            output.vColor = float4(vObjectColor);
            output.vNormal = float4(vViewNormal.xyz, 1.f);
            output.vPosition = float4(_in.vViewPos.xyz, 1.f);
            output.vData = float4(0.f, 0.f, 0.f, 1.f);
            output.vEmissive = float4(vObjectColor * 0.5f);
        }
        
        // 칼 texture가 알파값을 1로 줘야 색이 나오게 되어있다.
        else
        {
            output.vColor = float4(vObjectColor.rgb, 1.f);
            output.vNormal = float4(vViewNormal.xyz, 1.f);
            output.vPosition = float4(_in.vViewPos.xyz, 1.f);
            output.vData = float4(0.f, 0.f, 0.f, 1.f);
            output.vEmissive = float4(0.f, 0.f, 0.f, 1.f);
        }
    }
    
    // 인자로 들어온 색상으로 Emissive 값을 주고 싶은 경우. 
    else if (g_int_1)
    {
        // Vec4로 들어온 색상을 Emissive 타겟에 저장해준다.
        output.vColor = float4(vObjectColor);
        output.vNormal = float4(vViewNormal.xyz, 1.f);
        output.vPosition = float4(_in.vViewPos.xyz, 1.f);
        output.vData = float4(0.f, 0.f, 0.f, 1.f);
        output.vEmissive = g_vec4_0;
    }
    
    else
    {
        output.vColor = float4(vObjectColor);
        output.vNormal = float4(vViewNormal.xyz, 1.f);
        output.vPosition = float4(_in.vViewPos.xyz, 1.f);
        output.vData = float4(0.f, 0.f, 0.f, 1.f);
        output.vEmissive = float4(0.f, 0.f, 0.f, 1.f);
    }
        
    return output;
}

#endif
