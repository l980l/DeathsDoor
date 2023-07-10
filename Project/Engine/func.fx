#ifndef _FUNC
#define _FUNC

#include "value.fx"

void CalcLight2D(float3 _vWorldPos, inout tLightColor _Light)
{       
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        // Directional ����
        if (g_Light2DBuffer[i].LightType == 0)
        {
            //��ü�� ���� ���� �ֺ����� �����Ŵ
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb;
            _Light.vAmbient.rgb += g_Light2DBuffer[i].Color.vAmbient.rgb;
        }
        // Point ����
        else if (g_Light2DBuffer[i].LightType == 1)
        {
            // ������ ��ġ�� �ȼ��� ��ġ�� ������
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);
            
            // ������ �ȼ��� �Ÿ� ������ ���� ���� ���⸦ ������
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
        
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fPow;
        }
        // Spot ����
        else if (g_Light2DBuffer[i].LightType == 2)
        {
            // ������ ��ġ�� �ȼ��� ��ġ�� ������
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);
            
            // ������ �캤�� ���������� ������
            float vLightDir = normalize(g_Light2DBuffer[i].vWorldDir);
            
            float2 lightDir = normalize(vWorldPos.xy - vLightWorldPos.xy);
            float2 fWorldDir = normalize(g_Light2DBuffer[i].vWorldDir.xy);
            float fAngle = cos(g_Light2DBuffer[i].Angle / 2.f);
            if (dot(normalize(lightDir), normalize(g_Light2DBuffer[i].vWorldDir.xy)) < cos(g_Light2DBuffer[i].Angle / 2.f))
            {
                _Light.vDiffuse.rgba += float4(0.f, 0.f, 0.f, 1.f); //outside of radius make it black
            }
            else
            {
                float fAnglePow = saturate(1.f - (fAngle / dot(lightDir, fWorldDir)) * 0.9f);
          
                // ������ �ȼ��� �Ÿ� ������ ���� ���� ���⸦ ������
                float fDistance = abs(distance(vWorldPos, vLightWorldPos));
                float fPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
            
                _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fPow * fAnglePow;
            }
        }
    }    
}

void CalcLight2D(float3 _vWorldPos, float3 _vWorldDir, inout tLightColor _Light)
{
    for (int i = 0; i < g_Light2DCount; ++i)
    {
        if (g_Light2DBuffer[i].LightType == 0)
        {
            float fDiffusePow = saturate(dot(-g_Light2DBuffer[i].vWorldDir.xyz, _vWorldDir));
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fDiffusePow;                        
            _Light.vAmbient.rgb += g_Light2DBuffer[i].Color.vAmbient.rgb;
        }
        else if (g_Light2DBuffer[i].LightType == 1)
        {
            float3 vLightWorldPos = float3(g_Light2DBuffer[i].vWorldPos.xy, 0.f);
            float3 vWorldPos = float3(_vWorldPos.xy, 0.f);

            // ���� �߽ɿ��� ��ü�� ���ϴ� ����
            float3 vLight = normalize(vWorldPos - vLightWorldPos);
            float fDiffusePow = saturate(dot(-vLight, _vWorldDir));
            
            float fDistance = abs(distance(vWorldPos, vLightWorldPos));
            float fDistPow = saturate(1.f - (fDistance / g_Light2DBuffer[i].Radius));
        
            _Light.vDiffuse.rgb += g_Light2DBuffer[i].Color.vDiffuse.rgb * fDiffusePow * fDistPow;
        }
        else if (g_Light2DBuffer[i].LightType == 2)
        {
            
        }
    }
}

void CalcLight3D(float3 _vViewPos, float3 _vViewNormal, int LightIdx, inout tLightColor _LightColor)
{
    tLightInfo LightInfo = g_Light3DBuffer[LightIdx];
 
    float3 vLightDir = (float3) 0.f;
    
    // �������� ������ ���� ����
    float fDiffusePow = 0.f;
    
    // POINT, SPOT�� ��� �������� �Ÿ��� ���� ����
    // DIRECTIONAL�� ��� �ش���� �������� 1�� �ʱ�ȭ
    float fDistPow = 1.f;
    // SPOT�� Angle�� ���� ����
    float fAnglePos = 1.f;
 
    // Directional Light
    if (0 == LightInfo.LightType)
    {
        vLightDir = mul(float4(LightInfo.vWorldDir.xyz, 0.f), g_matView);
    }
     
    // Point Light
    else if (1 == LightInfo.LightType)
    {
       // ���� ��ġ�� View Space�� �ű�
        float4 vLightViewPos = mul(float4(LightInfo.vWorldPos.xyz, 1.f), g_matView);
    
       // ǥ����ġ - ������ġ
       vLightDir = normalize(_vViewPos - vLightViewPos.xyz);
    
       // �Ÿ��� ���� ���� ��ȭ
       float fDist = distance(_vViewPos, vLightViewPos.xyz);
    
        fDistPow = 1.f - saturate(fDist / LightInfo.Radius);
    }
     
    // Spot Light
    else if (2 == LightInfo.LightType)
    {
       // ���� ViewSpace ���� ��ġ ����
       float4 vLightViewPos = mul(float4(LightInfo.vWorldPos.xyz, 1.f), g_matView);
        
       // ���� ���⺤��(�� -> obj)
       vLightDir = normalize(_vViewPos - vLightViewPos.xyz);
       float3 vLightViewDir = normalize(mul(float4(LightInfo.vWorldDir.xyz, 0.f), g_matView));
        
       // ���� ���⺤�Ϳ� ������ ǥ���� ���͸� ������
       float fAngle = acos(dot(vLightDir, vLightViewDir));
        
       // ������ ���� Angle �̳���� ���� ���⸦ Angle���� �°� ���� ���̶�� 0
       if (fAngle <= LightInfo.Angle)
           fAnglePos = 1.f - saturate(fAngle / LightInfo.Angle);
       else
           fAnglePos = 0.f;
        
       // �Ÿ��� ���� ���� ����
       float fDist = distance(_vViewPos, vLightViewPos.xyz);
       fDistPow = 1.f - saturate(fDist / LightInfo.Radius);
    }
 
    // Diffuse Power ���
    fDiffusePow = saturate(dot(-vLightDir, _vViewNormal));
 
    // Specular ���
    float3 vViewReflect = normalize(vLightDir + 2.f * (dot(-vLightDir, _vViewNormal)) * _vViewNormal);
 
    // ī�޶󿡼� �ȼ��� �ٶ󺸴� �ü� ����
    float3 vEye = -normalize(_vViewPos);
 
    // �ݻ籤 ����
    float fReflectPow = pow(saturate(dot(vViewReflect, vEye)), 10);
 
    // ����� ����
    _LightColor.vDiffuse += LightInfo.Color.vDiffuse * fDiffusePow * fDistPow * fAnglePos;
    _LightColor.vSpecular += LightInfo.Color.vSpecular * fReflectPow * fDistPow * fAnglePos;
    _LightColor.vAmbient += LightInfo.Color.vAmbient * fAnglePos;
}




// ======
// Random
// ======
static float GaussianFilter[5][5] =
{
    0.003f,  0.0133f, 0.0219f, 0.0133f, 0.003f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.0219f, 0.0983f, 0.1621f, 0.0983f, 0.0219f,
    0.0133f, 0.0596f, 0.0983f, 0.0596f, 0.0133f,
    0.003f,  0.0133f, 0.0219f, 0.0133f, 0.003f,
};

void GaussianSample(in Texture2D _NoiseTex, float2 _vResolution, float _NomalizedThreadID, out float3 _vOut)
{
    float2 vUV = float2(_NomalizedThreadID, 0.5f);       
    
    vUV.x += g_AccTime * 0.5f;
    
    // sin �׷����� �ؽ����� ���ø� ��ġ UV �� ���
    vUV.y -= (sin((_NomalizedThreadID - (g_AccTime/*�׷��� ���� �̵� �ӵ�*/)) * 2.f * 3.1415926535f * 10.f/*�ݺ��ֱ�*/) / 2.f);
    
    if( 1.f < vUV.x)
        vUV.x = frac(vUV.x);
    else if(vUV.x < 0.f)
        vUV.x = 1.f + frac(vUV.x);
    
    if( 1.f < vUV.y)
        vUV.y = frac(vUV.y);
    else if (vUV.y < 0.f)
        vUV.y = 1.f + frac(vUV.y);
        
    int2 pixel = vUV * _vResolution;           
    int2 offset = int2(-2, -2);
    float3 vOut = (float3) 0.f;    
    
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {            
            vOut += _NoiseTex[pixel + offset + int2(j, i)] * GaussianFilter[i][j];
        }
    }        
    
    _vOut = vOut;    
}



int IntersectsLay(float3 _vertices[3], float3 _vStart, float3 _vDir, out float3 _vCrossPoint, out float _fResult)
{
    // vertices�� ���� ������ġ�� �̿��� �� 2�� ����
    float3 edge[2] = { (float3) 0.f, (float3) 0.f };
    edge[0] = _vertices[1].xyz - _vertices[0].xyz;
    edge[1] = _vertices[2].xyz - _vertices[0].xyz;

    // �� 2���� �̿��� ���� normal������ �˾Ƴ�
    float3 normal = normalize(cross(edge[0], edge[1]));
    
    // normal�� ray�� ������ ����
    float b = dot(normal, _vDir);
    
    // ȣ��� �ȼ����� ray�� ������������ ���� ������ ����.
    float3 w0 = _vStart - _vertices[0].xyz;
    
    // normal�� �ȼ�->ray Start�� ����
    float a = -dot(normal, w0);
    
    // �����Ͽ� ���� ���� normal, ray������ ������ ������ ����
    float t = a / b;

    _fResult = t;
    
    // ������������ ����������� t��ŭ �̵��� ���� ������
    float3 p = _vStart + t * _vDir;

    _vCrossPoint = p;

    float uu, uv, vv, wu, wv, inverseD;
    uu = dot(edge[0], edge[0]);
    uv = dot(edge[0], edge[1]);
    vv = dot(edge[1], edge[1]);

    float3 w = p - _vertices[0].xyz;
    wu = dot(w, edge[0]);
    wv = dot(w, edge[1]);
    inverseD = uv * uv - uu * vv;
    inverseD = 1.0f / inverseD;

    float u = (uv * wv - vv * wu) * inverseD;
    if (u < 0.0f || u > 1.0f)
    {
        return 0;
    }

    float v = (uv * wu - uu * wv) * inverseD;
    if (v < 0.0f || (u + v) > 1.0f)
    {
        return 0;
    }

    return 1;
}


float GetTessFactor(float3 _vPos, int _iMinLevel, int _iMaxLevel, float _MinDistance, float _MaxDistance)
{
    float fDistance = abs(length(_vPos));

    if (_MaxDistance < fDistance)
    {
        return 0.f;
    }     
    else if (fDistance < _MinDistance)
    {
        return _iMaxLevel;
    }
    else
    {
        float fLevel = _iMaxLevel - (_iMaxLevel - _iMinLevel) * ((fDistance - _MinDistance) / (_MaxDistance - _MinDistance));

        return fLevel;
    }
}



matrix GetBoneMat(int _iBoneIdx, int _iRowIdx)
{
    return g_arrBoneMat[(g_iBoneCount * _iRowIdx) + _iBoneIdx];
}

void Skinning(inout float3 _vPos, inout float3 _vTangent, inout float3 _vBinormal, inout float3 _vNormal
    , inout float4 _vWeight, inout float4 _vIndices
    , int _iRowIdx)
{
    tSkinningInfo info = (tSkinningInfo)0.f;

    if (_iRowIdx == -1)
        return;

    for (int i = 0; i < 4; ++i)
    {
        if (0.f == _vWeight[i])
            continue;

        matrix matBone = GetBoneMat((int)_vIndices[i], _iRowIdx);

        info.vPos += (mul(float4(_vPos, 1.f), matBone) * _vWeight[i]).xyz;
        info.vTangent += (mul(float4(_vTangent, 0.f), matBone) * _vWeight[i]).xyz;
        info.vBinormal += (mul(float4(_vBinormal, 0.f), matBone) * _vWeight[i]).xyz;
        info.vNormal += (mul(float4(_vNormal, 0.f), matBone) * _vWeight[i]).xyz;
    }

    _vPos = info.vPos;
    _vTangent = normalize(info.vTangent);
    _vBinormal = normalize(info.vBinormal);
    _vNormal = normalize(info.vNormal);
}


#endif