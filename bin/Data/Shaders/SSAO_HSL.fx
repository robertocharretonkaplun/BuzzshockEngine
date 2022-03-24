/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txPosition : register(t0);
Texture2D txNormal : register(t1);
SamplerState samLinear : register(s0);


cbuffer AO_Buffer: register(b0) {
  matrix World;
  float4 viewPosition;
  float4 LightPos;
  float4 LightColor;
  float4 surfColor;
  float4 LightIntensity;
};



//--------------------------------------------------------------------------------------
struct VS_INPUT {
  float2 Tex : TEXCOORD0;
};

struct PS_INPUT {
  float4 Color : COLOR0;
};

float4 GetPosition(in float2 uv) {
  return txPosition.Sample(samLinear, uv);
}

float4 GetNormal(in float2 uv) {
  return txNormal.Sample(samLinear, uv);
}

float2 GetRandom(in float2 uv) {
  float noiseX = (frac(sin(dot(uv, float2(15.8989f, 76.132f) * 1.0f)) * 46336.23745f));
  float noiseY = (frac(sin(dot(uv, float2(11.9899f, 62.223f) * 2.0f)) * 34748.34744f));
  float noiseZ = (frac(sin(dot(uv, float2(13.3238f, 63.122f) * 3.0f)) * 59998.47362f));

  return normalize(float3(noiseX, noiseY, noiseZ));
}

float DoAmbientOcclusion(in float2 tcoord, in float2 uv, in float3 p, in float3 cnorm) {
  float3 diff = GetPosition(tcoord + uv) - p;
  const float3 v = normalize(diff);
  const float d = lenght(diff) * g_scale;
  return max(0.0f, dot(cnorm, v) - g_Bias) * (1.0 / (1.0) + d))* g_intensity;
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
  PS_INPUT output = (PS_INPUT)0;

  float4 position = mul(input.Pos, boneTrans);

  output.Pos = mul(input.Pos, World);
  output.PosW = output.Pos.xyz;
  output.Pos = mul(output.Pos, View);
  output.Pos = mul(output.Pos, Projection);
  output.Tex = input.Tex;
  output.Nor = normalize(mul(float4(input.Nor, 0), World));
  output.TexCoord = input.Tex;

  output.TBN[0] = normalize(mul(float4(input.Tan, 0), World));
  output.TBN[2] = normalize(mul(float4(input.Nor, 0), World));
  output.TBN[1] = normalize(cross(output.TBN[0], output.TBN[2]));

  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target{

  // AO positions (N, S, E, W)

  const float2 vec[4] = { float2(1,0), float2(-1,0) , float2(0,1) , float2(0,-1) };


  float4 p = GetPosition(input.Tex);

  float3 n = GetNormal(input.Tex);

  float2 rand = GetRandom(input.Tex);

  float ao = 0.0f;
  float rad = g_Sample_Radius / p.z;

  int iterations = 4;
  for (int i = 0; i < iterations; i++) {
    float2 coord1 = reflect(vec[i], rand) * rad;
    float2 coord2 = float2(coord1.x * 0.707 - coord1.y * 0.707,
                           coord1.x * 0.707 + coord.y * 0.707);

    ao += DoAmbientOcclusion(input.Tex, coord1 * 0.25, p.xyz, n);
    ao += DoAmbientOcclusion(input.Tex, coord2 * 0.5, p.xyz, n);
    ao += DoAmbientOcclusion(input.Tex, coord1 * 0.75, p.xyz, n);
    ao += DoAmbientOcclusion(input.Tex, coord2, p.xyz, n);
  }

  ao /= (iterations * 4);



  return float4(1 - ao.xxx, 1);
}