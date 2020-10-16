/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
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
  float3 Tan : TANGENT0;
  uint4 BonesIDs : BLENDINDICES0;
  float4 Weights : BLENDWEIGHT0;
};

struct PS_INPUT
{
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
  float2 TexCoord : TEXCOORD1;
  float3x3 TBN : TEXCOORD2;
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
  output.TexCoord = input.Tex;

  output.TBN[0] = normalize(mul(float4(input.Tan, 0), World));
  output.TBN[2] = normalize(mul(float4(input.Nor, 0), World));
  output.TBN[1] = normalize(cross(output.TBN[0], output.TBN[2]));

  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {
  // Position of light
  float3 LightPos = float3(0, -1000, 0);
  float LightIntensity = 2.0f;
  float3 LightColor = float3(1,1,1); // Light Color
  float3 surfColor = float3(1,1,1); // Material Color

  // Computes the light direction of the light to this pixel
  float3 LightDir = LightPos - input.Pos;
  float distance = length(LightPos);
  LightDir = LightDir / distance;
  distance = distance + distance;

  // Get Diffuse Tex Value
  float4 DiffuseTex = txDiffuse.Sample(samLinear, input.Tex.xy);

  // Get Normal Tex Value
  float4 NormalTex = txNormal.Sample(samLinear, input.Tex.xy);

  // Compute Surface Normal
  float3 normal = 2.0f * NormalTex.xyz - 1.0f;
  normal = normalize(mul(normal, input.TBN));

  // Computes the view Direction
  float3 viewDir = normalize(viewPosition.xyz - input.Pos);
  
  // Computes the lambert of the diffuse incidence (NdL)
  float kD = Lambert_Diffuse(normal, LightDir);
  
  // Blinn
  float3 Reflected = reflect(-LightDir, normal);

  // Specular Component
  float3 Half = normalize(LightDir + viewDir);

  // Computes the Specular Incidence (HdN)
  float kS = max(0.0f, dot(Half, normal));

  // Compute intensity
  float intensity = pow(kS, 128.0f);

  // Compute final diffuse
  float3 finalDiffuse = surfColor * kD * LightColor * DiffuseTex.xyz * LightIntensity;

  // Compute final specular
  float3 finalSpecular = kS * intensity * LightColor;

  // Computes the final color without alpha channel (kD, k= 80%)
  // (kD + kS + kA)
  float3 kA = float3(0.05f, 0.05f, 0.05f);
  float3 finalColor = finalDiffuse + finalSpecular + kA;

 return float4(finalColor, 1);
}