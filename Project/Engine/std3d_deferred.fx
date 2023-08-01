#ifndef _DEFERRED
#define _DEFERRED

#include "value.fx"
#include "func.fx"
#include "struct.fx"
#define WIDTH   g_Resolution.x
#define HEIGHT g_Resolution.y
// ========================
// Std3D Deferred Shader
//
// g_tex_0 : Color Texture
// g_tex_1 : Normal Texture
// g_tex_2 : Bloom  Texture
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
    
    // 픽셀 라이팅을 위한 View스페이스 기준 pos, Normal벡터 계산
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV);
        
    // 월드에 있는 모든 Obj가 같은 위치의 빛을 받아야 하므로 이동값을 반영하지 않음.
    // Obj의 표면상의 벡터를 View Space 기준으로 변경함.
    output.vViewTangent =  normalize(mul(float4(_in.vTangent, 0.f), g_matWV));
    output.vViewNormal =   normalize(mul(float4(_in.vNormal, 0.f), g_matWV));
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV));
        
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

float4 GaussianBlurHorizontal(float2 texCoord, float pixelSize, int blurRadius)
{
    float4 blurColor = 0;
    
    for (int i = -blurRadius; i <= blurRadius; i++)
    {
        float2 offset = float2(i * pixelSize, 0);
        blurColor += g_tex_2.Sample(g_sam_0, texCoord + offset);
    }
    
    return blurColor / float(blurRadius * 2 + 1);
}

float4 GaussianBlurVertical(float2 texCoord, float pixelSize, int blurRadius)
{
    float4 blurColor = 0;
    
    for (int i = -blurRadius; i <= blurRadius; i++)
    {
        float2 offset = float2(0, i * pixelSize);
        blurColor += g_tex_2.Sample(g_sam_0, texCoord + offset);
    }
    
    return blurColor / float(blurRadius * 2 + 1);
}

// Function to perform 4x4 down-sampling
//float4 DownSample4x4(float2 texCoord)
//{
//    //float2 texelSize = 1.0 / g_tex_2.GetDimensions();

//    float4 sum = 0;
    
//    // Sample the 16 neighboring texels and sum their color values
//    for (int x = 0; x < 4; x++)
//    {
//        for (int y = 0; y < 4; y++)
//        {
//            float2 offset = float2(x, y) * texelSize * 0.25; // Divide by 4 to get the average
//            sum += g_tex_2.Sample(g_sam_0, texCoord + offset);
//        }
//    }

//    return sum * 0.0625; // Divide by 16 (4x4) to get the average
//}

//float4 UpSample4x4(float2 texCoord)
//{
//    //float2 texelSize = 1.0 / g_tex_2.GetDimensions(texCoord.x, texCoord.y);
    
//    float4 color = 0;

//    // Sample the four corner texels of the 4x4 region
//    color += g_tex_2.Sample(g_sam_0, texCoord);
//    color += g_tex_2.Sample(g_sam_0, texCoord + float2(texelSize.x * 3, 0));
//    color += g_tex_2.Sample(g_sam_0, texCoord + float2(0, texelSize.y * 3));
//    color += g_tex_2.Sample(g_sam_0, texCoord + float2(texelSize.x * 3, texelSize.y * 3));

//    // Average the colors to get the interpolated result
//    color *= 0.25; // Divide by 4 to get the average

//    return color;
//}

PS_OUT PS_Std3D_Deferred(VS_OUT _in) : SV_Target
{
    // obj 색상 설정(회색)
    float4 vObjectColor = float4(0.6f, 0.6f, 0.6f, 1.f);
    float4 vBloomColor = float4(0.f, 0.f, 0.f, 0.f);
    float4 vOutColor = float4(0.f, 0.f, 0.f, 1.f);
    
    float3 vViewNormal = _in.vViewNormal;
    float4 blurColor = float4(0.f, 0.f, 0.f, 0.f);
    // 텍스쳐가 있으면, 해당 색상을 사용한다.
    if (g_btex_0)
    {
        vObjectColor = g_tex_0.Sample(g_sam_0, _in.vUV);
    }
    
    if (g_btex_2)
    {   
       // vBloomColor = DownSample4x4(_in.vUV);
        //vBloomColor = UpSample4x4(_in.vUV);
        vBloomColor = g_tex_2.Sample(g_sam_0, _in.vUV);
        
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
    
    PS_OUT output = (PS_OUT) 0.f;
    //===============
    //0.5 넘어서는 부분을
    float Brigtness = (vBloomColor.x + vBloomColor.y + vBloomColor.z) / 3.f;
    if (Brigtness > 0.3f)
    {
        float2 Pos = (_in.vUV - 0.5f * g_Resolution.xy) / g_Resolution.y;
        float Size = 0.1f + 0.5f * pow(1. - abs(frac(0.45f) - 0.5f), 3.f);
    
        float Dist = length(max(abs(Pos) - Size, 0.f));
        float Glow = .5f / (Dist * 25.f + 0.5f);
    
        vBloomColor = float4(Glow * float3(g_float_0, g_float_1, g_float_2), 1.f); //컬러
        vBloomColor = Fade_In_Out(vBloomColor, g_int_0, g_int_1); //강도
        
        //vBloomColor += GaussianBlurVertical(_in.vUV, 2.f, 4);
        
       //============================================================
        
    }
    //1.texture를 down sampling
    //2.인접 픽셀들의 가중 평균을 구하는 것
    
    //===============
    //output.vColor = float4(vBloomColor.xyz, 1.f);
    output.vColor = float4(vObjectColor.xyz, 1.f) ;
    output.vNormal =   float4(vViewNormal.xyz, 1.f);
    output.vPosition = float4(_in.vViewPos.xyz, 1.f);
    output.vData =     float4(0.f, 0.f, 0.f, 1.f);
    //output.vEmissive = vBloomColor;
    output.vEmissive = float4(0.f, 0.f, 0.f, 1.f) + (vBloomColor);
        
    return output;
}

#endif
