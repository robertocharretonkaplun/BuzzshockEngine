/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txSpecular : register(t2);
Texture2D txRoughness : register(t3);
Texture2D txCubeMap : register(t4);
SamplerState samLinear : register(s0);

cbuffer cbCamera: register(b0) {
  matrix View;
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b1) {
  matrix World;
  float4 viewPosition;
  float3 LightPos;
  float3 LightColor;
  float3 surfColor;
  float4 LightIntensity;
};

cbuffer cbBonesTransform : register (b2) {
  matrix boneTransform[100];
};


//--------------------------------------------------------------------------------------
struct VS_INPUT {
  float4 Pos : POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
  float3 Tan : TANGENT0;
  uint4 BonesIDs : BLENDINDICES0;
  float4 Weights : BLENDWEIGHT0;
};

struct PS_INPUT {
  float4 Pos : SV_POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
  float2 TexCoord : TEXCOORD1;
  float3x3 TBN : TEXCOORD2;
};

matrix Identity = {
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

#define M_PI 3.1415966538
#define EPSILON 0.00001
// Normal Disstribution function - GGX
float
ndf_GGX(float NdH, float roughness) {
  float alpha = roughness * roughness;
  float alphaSqr = alpha * alpha;

  float denom = (NdH * NdH) * (alphaSqr - 1.0) + 1.0f;
  return alphaSqr / (M_PI * denom * denom);
}

// Schlick aproximation of the Fresnel factor
float3 
fresnelSchlick(float3 F0, float cosTheta) {
  return F0 + (1.0f - F0) * pow(1.0f - cosTheta, 5.0f);
}


float
ga_SchlickG1(float cosTheta, float k) {
  return cosTheta / (cosTheta * (1.0f - k) + k);
}

float 
ga_SchlickGGX(float cosLi, float cosLo, float roughness) {
  float r = roughness + 1.0f;

  // Epic suggest using this roughness remaping for analytic light
  float k = (r * r) / 8.0f;
  return ga_SchlickG1(cosLi, k) * ga_SchlickG1(cosLo, k);
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
  // Computes the light direction of the light to this pixel
  float3 LightDir = LightPos - input.Pos;
  float distance = length(LightPos);
  LightDir = LightDir / distance;
  distance = distance + distance;

  // Get Diffuse Tex Value
  float4 DiffuseTex = txDiffuse.Sample(samLinear, input.Tex.xy);

  // Get Normal Tex Value
  float4 NormalTex = txNormal.Sample(samLinear, input.Tex.xy);
  
  // Get Specular / metallic Tex Value
  float4 SpecularTex = txSpecular.Sample(samLinear, input.Tex.xy);
  
  // Get Roughness Tex Value
  float4 RoughnessTex = txRoughness.Sample(samLinear, input.Tex.xy);
  
  // Get cube map Tex Value
  float4 CubeMapTex = txCubeMap.Sample(samLinear, input.Nor);

  float metallic = SpecularTex.r;
  float roughness = RoughnessTex.r;
  

  // Convert color to linear space
  DiffuseTex.xyz = pow(DiffuseTex.xyz, 2.2f);

  // Fresnel factor in 0 angle
  float3 F0 = lerp(0.04f, DiffuseTex.xyz, metallic);

  // Compute Surface Normal
  float3 normal = 2.0f * NormalTex.xyz - 1.0f;
  normal = normalize(mul(normal, input.TBN));

  // Computes the view Direction
  float3 viewDir = normalize(viewPosition.xyz - input.Pos);
  
  // Computes the reflect 
  //float3 reflejo = reflect(viewDir, input.Nor);
  //float4 cube = texCUBElod(CubeMapTex, reflejo);
  return float4(CubeMapTex);

  // Computes the lambert of the diffuse incidence (NdL)
  float NdL = Lambert_Diffuse(normal, LightDir);
  
  // Blinn
  float3 Reflected = reflect(-LightDir, normal);

  // Specular Component
  float3 Half = normalize(LightDir + viewDir);

  // Computes the Specular Incidence (HdN)
  float kS = max(0.0f, dot(Half, normal));
  float NdV = max(0.0f, dot(normal, viewDir));
  float HdV = max(0.0f, dot(Half, viewDir));

  float D = ndf_GGX(kS, roughness); 

  float3 F = fresnelSchlick(F0, HdV);

  float G = ga_SchlickGGX(NdL, NdV, roughness);

  float3 specularBRDF = (D * F * G) / max(EPSILON, 4.0f * NdL * NdV);
  
  
  // Compute intensity
  //float intensity = pow(kS, metallic * 255.0f) * SpecularTex.xyz;

  // Compute final diffuse
  //float3 finalDiffuse = surfColor * NdL * LightColor * DiffuseTex.xyz * LightIntensity[0] ;
  // Absorsion factor
  float3 kD = lerp(float3(1, 1, 1), float3(0, 0, 0), metallic);
  float3 DiffuseBRDF = DiffuseTex.xyz * kD * LightColor * surfColor * LightIntensity[0];


 return float4(pow((DiffuseBRDF + specularBRDF) * NdL, 1.0f / 2.2f), DiffuseTex.w);
}