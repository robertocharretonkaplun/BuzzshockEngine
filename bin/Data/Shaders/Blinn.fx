/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbNeverChanges : register(b0)
{
  matrix View;
};

cbuffer cbChangeOnResize : register(b1)
{
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b2)
{
  matrix World;
  float4 vMeshColor;
  float4 viewPosition;
};

cbuffer cbBonesTransform : register (b3)
{
  matrix boneTransform[100];
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
  float4 Pos : POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
  uint4 BonesIDs : BLENDINDICES0;
  float4 Weights : BLENDWEIGHT0;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
};

matrix Identity =
{
    { 1, 0, 0, 0 },
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 },
    { 0, 0, 0, 1 }
};

// Lamber Diffuse Method
float
Lambert_Diffuse(in float3 lightDir, in float3 surfNormal) {
  return max(0.0f, dot(lightDir, surfNormal)); // .25 is the number of divisions
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
  PS_INPUT output = (PS_INPUT)0;

  matrix boneTrans = Identity;
  for (int i = 0; i < 4; i++) {
    if (input.BonesIDs[i] > 1000) {
      break;
    }
    boneTrans += boneTransform[input.BonesIDs[i]] * input.Weights[i];
  }

  float4 position = mul(input.Pos, boneTrans);

  output.Pos = mul(input.Pos, World);
  output.Pos = mul(output.Pos, View);
  output.Pos = mul(output.Pos, Projection);
  output.Tex = input.Tex;
  output.Nor = normalize(mul(float4(input.Nor, 0), World));

  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {
  // Position of light
  float3 LightPos = float3(0, -1000, 0);

  float3 LightColor = float3(1,1,1); // Light Color
  float3 surfColor = float3(0,1,0); // Material Color

  // Computes the light direction of the light to this pixel
  float3 LightDir = LightPos - input.Pos;
  float distance = length(LightPos - input.Pos);
  LightDir = LightDir / distance;
  distance = distance + distance;

  // Computes the view Direction
  float3 viewDir = normalize(viewPosition.xyz - input.Pos);
  
  // Computes the lambert of the diffuse incidence (NdL)
  float kD = Lambert_Diffuse(input.Nor, LightDir);
  
  // Blinn
  float3 Reflected = normalize(reflect(-LightDir, input.Nor));

  // Specular Component
  float3 Half = normalize(LightDir + viewDir);

  // Computes the Specular Incidence (HdN)
  float kS = max(0.0f, dot(Half, input.Nor));

  // Compute intensity
  float intensity = pow(kS, 64.0f);

  // Compute final diffuse
  float3 finalDiffuse = surfColor * kD * LightColor * 0.8f;

  // Compute final specular
  float3 finalSpecular = kS * intensity * LightColor;

  // Computes the final color without alpha channel (kD, k= 80%)
  // (kD + kS + kA)
  float3 finalColor = finalDiffuse + finalSpecular;

 //float3 texColor = txDiffuse.Sample(samLinear, input.Tex) * finalColor;
 return float4(finalColor, 1);
}