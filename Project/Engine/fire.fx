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
    
    // Instancing 당 데이터
    //row_major matrix matWorld : WORLD;
    //row_major matrix matWV : WV;
    //row_major matrix matWVP : WVP;
    //int iRowIdx : ROWINDEX; // Animaion 행렬 행

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
    float4 vColor : SV_Target4;
    float4 vDiff : SV_Target0;
    float4 vNormal : SV_Target1;
    float4 vPosition : SV_Target2;
    float4 vDiffLight : SV_Target3; //디퍼드 단계에서 미리 빛을 라이트 타겟에 넣어놓아 그림자에 걸릴일이 없어진다 . 
                                    //또한 , 라이트 타겟을 가져와 블룸처리를 할수도 있다 
    
    float4 pDOFDepthTex : SV_Target4;
};

VS_OUT VS_Fire(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vPos, 1.f), g_matWVP);
    output.vUV = _in.vUV;
    
    // 로컬 스페이스의 위치 및 법선 벡터를 ViewSpace 까지 변환 후 픽셀 쉐이더로 전달
    output.vViewPos = mul(float4(_in.vPos, 1.f), g_matWV).xyz;
    output.vVeiwNormal = normalize(mul(float4(_in.vNormal, 0.f), g_matWV)).xyz;
    output.vViewTangent = normalize(mul(float4(_in.vTangent, 0.f), g_matWV)).xyz;
    output.vViewBinormal = normalize(mul(float4(_in.vBinormal, 0.f), g_matWV)).xyz;

    return output;
}

float2 hash(float2 p)
{
    p = float2(dot(p, float2(127.1, 311.7)),
			 dot(p, float2(269.5, 183.3)));
    return -1.0 + 2.0 * frac(sin(p) * 43758.5453123);
}

float noise(in float2 p)
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;
	
    float2 i = floor(p + (p.x + p.y) * K1);
	
    float2 a = p - i + (i.x + i.y) * K2;
    float2 o = (a.x > a.y) ? float2(1.0, 0.0) : float2(0.0, 1.0);
    float2 b = a - o + K2;
    float2 c = a - 1.0 + 2.0 * K2;
	
    float3 h = max(0.5 - float3(dot(a, a), dot(b, b), dot(c, c)), 0.0);
	
    float3 n = h * h * h * h * float3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));
	
    return dot(n, float3(70.0, 70.0, 70.0));
}

float fbm(float2 uv)
{
    float f;
    float2x2 m = float2x2(1.6, 1.2, -1.2, 1.6);
    f = 0.5000 * noise(uv);
    uv = mul(uv, m);
    f += 0.2500 * noise(uv);
    uv = mul(uv, m);
    f += 0.1250 * noise(uv);
    uv = mul(uv, m);
    f += 0.0625 * noise(uv);
    uv = mul(uv, m);
    f = 0.5 + 0.5 * f;
    return f;

}
#define BLUE_FLAME col = col.zyx;    
#define GREEN_FLAME col = 0.85 * col.yxz;

PS_OUT PS_Fire(VS_OUT _in) : SV_Target
{
    PS_OUT output = (PS_OUT) 0.f;
    
    // 물체 기준으로 변경
    float2 uv = _in.vPosition.xy / g_Resolution.xy;
    uv.y = 1.f - uv.y;
    float2 q = uv;
    q.y *= 0.5f;
    float strength = floor(q.x + 1.);
    float T3 = max(3., 1.25 * strength) * g_AccTime;
    q.x = frac(q.x) - 0.5;
    q.y -= 0.25;
    float n = fbm(strength * q - float2(0, T3));
    float c = 1. - 16. * pow(max(0., length(q * float2(1.8 + q.y * 1.5, .75)) - n * max(0., q.y + .25)), 1.2);
    float c1 = n * c * (1.5 - pow(2.50 * uv.y, 4.));
    c1 = clamp(c1, 0., 1.);

    float3 col = float3(1.5 * c1,   1.5 * c1 * c1 * c1,   c1 * c1 * c1 * c1 * c1 * c1);
    col = col.zyx;
        
    float a = c * (1. - pow(uv.y, 3.));
    float3 mix = lerp(float3(0.f, 0.f, 0.f), col, a);
    
    output.vColor = float4(mix, 1.0);
    output.vDiff = float4(mix, 1.0);
    output.vNormal = float4(_in.vVeiwNormal, 1.f);
    output.vPosition = float4(_in.vViewPos, 1.f);
    
    return output;
    
    // 전에 있던 테스트 코드
    //float3 vViewNormal = _in.vVeiwNormal;
    //
    //float4 BrighterColor = g_vDiff;
    //float4 MiddleColor = g_vAmb;
    //float4 DarkerColor = g_vSpec;
    //
    //float2 UV = _in.vUV + float2(0, g_AccTime / 2.f);
    //
    //float NoiseTex = g_tex_0.Sample(g_sam_0, UV).x;
    //float gradientValue = g_tex_1.Sample(g_sam_0, _in.vUV).x;
    //
    //float step1 = step(NoiseTex, gradientValue);
    //float step2 = step(NoiseTex, gradientValue - 0.3);
    //float step3 = step(NoiseTex, gradientValue - 0.5);
    //
    ////if (step1 == 0.0f) 
    ////    clip(-1);
    //
    //float4 c = float4(lerp(BrighterColor, DarkerColor, step1 - step2));
    //
    //output.vDiff.xyz = lerp(c.rgb, MiddleColor.rgb, step2 - step3);
    //
    //if (_in.vUV.x < 0.3f)
    //{
    //    output.vDiff.xyz = g_vEmv;
    //}
    //
    //      
    ////output.vDiff = vObjectColor;
    //output.vNormal.xyz = vViewNormal;
    //output.vPosition.xyz = _in.vViewPos;
    //
    //
    // {
    //    //float4 vWorldPos = mul( , g_matViewInv); // 메인카메라 view 역행렬을 곱해서 월드좌표를 알아낸다.
    //    float4 vProj = mul(float4(_in.vViewPos, 1.f), g_matProj); // 투영시킨 좌표 구하기
    //    float fDepth = vProj.z / vProj.w; // w 로 나눠서 실제 투영좌표 z 값을 구한다.(올바르게 비교하기 위해서)
    //    
    //    
    //    float4 fDOFDistance = float4(fDepth, 0.f, 0.f, 0.f);
    //    
    //    float Distance = (float) fDOFDistance;
    //    
    //    if (Distance + 0.0015f < fDepth)
    //    {
    //        float Diff = (fDepth - 0.0015f - Distance) * 2000.f;
    //    //output.vDiff = float4(1.0f, 0.0f, 1.0f - Diff, 1.0f);
    //        output.pDOFDepthTex.r = Diff;
    //    }
    //}

}

#endif