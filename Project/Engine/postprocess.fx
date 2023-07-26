#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "value.fx"

static float2 PixelKernel[13] =
{
    { -6, 0 },
    { -5, 0 },
    { -4, 0 },
    { -3, 0 },
    { -2, 0 },
    { -1, 0 },
    { 0, 0 },
    { 1, 0 },
    { 2, 0 },
    { 3, 0 },
    { 4, 0 },
    { 5, 0 },
    { 6, 0 },
};

static float BlurWeights[13] =
{
    0.002216f, 0.008764f, 0.026995f, 0.064759f, 0.120985f, 0.176033f, 0.199471f, 0.176033f, 0.120985f, 0.064759f,
    0.026995f, 0.008764f, 0.002216f,

};

struct VS_IN
{
	float3 vLocalPos : POSITION;
	float2 vUV : TEXCOORD;	
};

struct VS_OUT
{
	float4 vPosition : SV_Position;
	float2 vUV : TEXCOORD;
};

struct PS_OUT
{
    float4 vBloom : SV_Target0;
};
// ============================
// GrayShader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// ============================
VS_OUT VS_GrayShader(VS_IN _in)
{
	VS_OUT output = (VS_OUT)0.f;

	output.vPosition = float4(_in.vLocalPos * 2.f, 1.f);
	output.vUV = _in.vUV;

	return output;
}

float4 PS_GrayShader(VS_OUT _in) : SV_Target
{
	float4 vColor = g_tex_0.Sample(g_sam_0, _in.vUV);

	float vAver = (vColor.r + vColor.g + vColor.b) / 3.f;

	vColor = float4(vAver, vAver, vAver, 1.f);

	return vColor;
}


// ============================
// Distortion Shader
// mesh : RectMesh
// Domain : DOMAIN_POSTPROCESS
// g_tex_0 : RederTarget Copy Texture
// g_tex_1 : Noise Texture
// ============================
VS_OUT VS_Distortion(VS_IN _in)
{
	VS_OUT output = (VS_OUT)0.f;

	output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);	
	output.vUV = _in.vUV;

	return output;
}

float4 PS_Distortion(VS_OUT _in) : SV_Target
{
	float2 vUV = _in.vPosition.xy / g_Resolution;
	
	// Noise Texture �� ������ �Ǿ� �ִٸ�
	if (g_btex_1)
	{
		float2 vNoiseUV = float2(_in.vUV.x - (g_AccTime * 0.2f), _in.vUV.y);
		float4 vNoise = g_tex_1.Sample(g_sam_0, vNoiseUV);

		vNoise = (vNoise - 0.5f) * 0.02f;		

		vUV += vNoise.r;
	}

	float4 vColor = g_tex_0.Sample(g_sam_0, vUV);

	return vColor;
}
//=========

VS_OUT VS_Bloom(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;

    output.vPosition = mul(float4(_in.vLocalPos, 1.f), g_matWVP);
    //output.vPosition.zw = 1.f;
    output.vUV = _in.vUV;
    return output;
}



PS_OUT PS_Bloom(VS_OUT _in)
{
    PS_OUT output = (PS_OUT)0.f;
    
    float Directions = 8.0;
    float4 BloomColor = 0.f;
    float2 vFullUV = _in.vUV;
   // _in.vPosition.xy / g_Resolution * 4.f;
    
    if (g_int_0 == 0)
    {
        for (int index = 0; index < 13; ++index)
        {
            BloomColor += g_tex_0.Sample(g_sam_0, float2(vFullUV.x + (PixelKernel[index].x / g_Resolution.x * 4.f), vFullUV.y)) * BlurWeights[index];
            BloomColor += g_tex_0.Sample(g_sam_0, float2(vFullUV.x, vFullUV.y + (PixelKernel[index].x / g_Resolution.y * 4.f))) * BlurWeights[index];
        }
        
        //�÷� ���� 
        float red = BloomColor.x;
        float green = BloomColor.y;
        float blue = BloomColor.z;
        
        float sum = red + green + blue;
        
        red /= sum;
        green /= sum;
        blue /= sum;
        
        red += 1.f;
        green += 1.f;
        blue += 1.f;
        
        //�帰 �� ��ȭ 
        BloomColor = sqrt(BloomColor);
                
        BloomColor.x *= pow(red, 20);
        BloomColor.y *= pow(green, 20);
        BloomColor.z *= pow(blue, 20);
       
        BloomColor /= 10.7f;
        
        
        if (BloomColor.w > 0.f)        
            output.vBloom = BloomColor;
        else
        {
            output.vBloom = float4(0.f, 0.f, 0.f, 0.f);
        }
    }
    
    return output;
}

//float4 PS_ShockWaveShader(VS_OUT _in) : SV_Target
//{
	//// Ư�� ��ġ���� ����ó�� ���������� ȿ���� ��.
  
 //   float3 WaveParams = float3(10.0, 1.f, 0.1f);

 //   float ratio = 1.f;

	////���콺 ��ġ�� �������� ������ �Ϸ��� �Ʒ� ���� ���
	////float2 WaveCentre = float2( iMouse.xy / iResolution.xy );

 //   float2 WaveCentre = float2(0.5, 0.5);
 //   WaveCentre.y *= ratio;

 //   float2 texCoord = _in.vPosition.xy / g_Resolution.xy;
 //   texCoord.y *= ratio;
 //   float Dist = distance(texCoord, WaveCentre);


 //   float4 Color = g_tex_0.Sample(g_sam_0, texCoord);

	////�߽ɿ��� ���� �Ÿ� ���� �ȼ��� �ְ���.
 //   if ((Dist <= ((CurrentTime) + (WaveParams.z))) &&
	//(Dist >= ((CurrentTime) - (WaveParams.z))))
 //   {
	//	// �ȼ� ������ �Ÿ�
 //       float Diff = (Dist - CurrentTime);
 //       float ScaleDiff = (1.f - pow(abs(Diff * WaveParams.x), WaveParams.y));
 //       float DiffTime = (Diff * ScaleDiff);

	//	// �ְ� ����
 //       float2 DiffTexCoord = normalize(texCoord - WaveCentre);

	//	// �ð��� �������� ���� �������� ��.
 //       texCoord += ((DiffTexCoord * DiffTime) / (CurrentTime * Dist * 40.f));
 //       Color = g_tex_0.Sample(g_sam_0, texCoord);
 //       Color += (Color * ScaleDiff) / (CurrentTime * Dist * 40.f);
 //   }

 //   return Color;
//}









#endif