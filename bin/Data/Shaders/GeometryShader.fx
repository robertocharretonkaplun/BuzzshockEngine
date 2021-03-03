/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbCamera: register(b0) {
  matrix View;
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b1) {
  matrix World;
  /*float4 viewPosition;
  float4 LightPos;
  float4 LightColor;
  float4 surfColor;
  float4 LightIntensity;*/
};

cbuffer cbBonesTransform : register (b2) {
  matrix boneTransform[100];
};

cbuffer LightBuffer : register (b3) {
  float4 viewPosition;
  float4 LightPos;
  float4 LightColor;
  float4 surfColor;
  float4 LightIntensity;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT {
  float4 Pos : POSITION;
  float2 Size : SIZE;
};

struct VS_OUTPUT {
  float4 Center : POSITION;
  float2 Size : SIZE;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT input) {
  VS_OUTPUT output = (VS_OUTPUT)0;

  output.Center = input.Pos;
  output.Size = input.Size;

  return output;
}

// Geometry Shader
struct GS_OUTPUT {
  float4 PosH : SV_POSITION;
  float3 PosW : POSITION;
  float3 NormalW : NORMAL;
  float2 TexCoord : TEXCOORD;
};

[maxvertexcount(4)]
void GS_Billboard(point VS_OUTPUT input[1], inout TriangleStream<GS_OUTPUT> OutputStream) {
  float3 up = float3(0.0f, 1.0f, 0.0f);

  float3 look = (viewPosition - input[0].Center).xyz;

  look.y = 0.0f;

  look = normalize(look);


  float3 right = cross(up, look);

  float halfWidth = 0.5f * input[0].Size.x;
  float halfHeight = 0.5f * input[0].Size.y;

  float4 v[4];
  float3 center = input[0].Center.xyz;
  v[0] = float4(input[0].Center + halfWidth * right - halfHeight * up, 1.0f);
  v[1] = float4(input[0].Center + halfWidth * right + halfHeight * up, 1.0f);
  v[2] = float4(input[0].Center - halfWidth * right - halfHeight * up, 1.0f);
  v[3] = float4(input[0].Center - halfWidth * right + halfHeight * up, 1.0f);

  float tex[4] = {
    float2(0.0f, 1.0f),
    float2(0.0f, 0.0f),
    float2(1.0f, 1.0f),
    float2(1.0f, 0.0f),
  };

  GS_OUTPUT output;

  [unroll]
  for (int i = 0; i < 4; ++i) {
    output.PosH = mul(v[i], );
    output.PosW - v[i].xyz;
    output.NormalW = look;
    output.texCoord = tex[i];
    
    triStream.Append(output);
  }
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target {
  // Position of light
  // Computes the light direction of the light to this pixel
  float3 LightDir = LightPos - input.PosW;
  float distance = length(LightPos);
  LightDir = LightDir / distance;
  distance = distance + distance;

  // AO positions (N, S, E, W)
  const float2 vec[4] = { float2(1,0), float2(-1,0) , float2(0,1) , float2(0,-1) };


  //float4 AOPos = getPosition();
  // Get Diffuse Tex Value
  float4 DiffuseTex = txDiffuse.Sample(samLinear, input.Tex.xy);

  // Get Normal Tex Value
  float4 NormalTex = txNormal.Sample(samLinear, input.Tex.xy);
  
  // Get Specular / metallic Tex Value
  float4 SpecularTex = txSpecular.Sample(samLinear, input.Tex.xy);
  
  // Get Roughness Tex Value
  float4 RoughnessTex = txRoughness.Sample(samLinear, input.Tex.xy);
  

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
  float3 viewDir = normalize(viewPosition.xyz - input.PosW);
  
  // Computes the reflect 
  float3 reflejo = reflect(viewDir,  input.Nor);
  // Get cube map Tex Value
  float4 CubeMapTex = txCubeMap.Sample(samLinear, reflejo);
  //float4 CubeMapTex2 = txDiffuse.Sample(samLinear, normal) ;
  //return float4(CubeMapTex);

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
  
  
  // Absorsion factor
  float3 kD = lerp(float3(1, 1, 1), float3(0, 0, 0), metallic);
  float3 DiffuseBRDF = DiffuseTex.xyz * kD * LightColor.xyz * surfColor.xyz * LightIntensity[0];


 return float4(pow((DiffuseBRDF + specularBRDF /*+ CubeMapTex.xyz*/) * NdL, 1.0f / 2.2f), DiffuseTex.w);
}