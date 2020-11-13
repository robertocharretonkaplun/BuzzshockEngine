/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 13/10/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register(t0);
Texture2D txNormal : register(t1);
Texture2D txMetallic : register(t2);
Texture2D txRoughness : register(t3);
SamplerState samLinear : register(s0);

cbuffer cbCamera : register(b0) {
  matrix View;
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b1) {
  matrix World;
};

//--------------------------------------------------------------------------------------
struct VS_INPUT {
  float4 Pos : POSITION;
  float2 Tex : TEXCOORD0;
  float3 Nor : NORMAL0;
  float3 Tan : TANGENT0;
};

struct PS_INPUT {
  float4 Pos : SV_POSITION;
  float3 PosW : TEXCOORD0;
  float2 Tex : TEXCOORD1;
  float3 Nor : NORMAL0;
  float2 TexCoord : TEXCOORD2;
  float3x3 TBN : TEXCOORD3;
};

struct PS_OUTPUT {
  float4 PosRT       : SV_TARGET0;    
  float4 AlbedoRT    : SV_TARGET1;    
  float4 NormalRT    : SV_TARGET2;    
  float4 MetallicRT  : SV_TARGET3;    
  float4 RoughnessRT : SV_TARGET4;    
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input) {
  PS_INPUT output = (PS_INPUT)0;

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
PS_OUTPUT PS(PS_INPUT input) {
  // Get Diffuse Tex Value
  float4 DiffuseTex = txDiffuse.Sample(samLinear, input.Tex.xy);

  // Get Normal Tex Value
  float4 NormalTex = txNormal.Sample(samLinear, input.Tex.xy);

  // Get metallic Tex Value
  float4 MetallicTex = txMetallic.Sample(samLinear, input.Tex.xy);

  // Get Roughness Tex Value
  float4 RoughnessTex = txRoughness.Sample(samLinear, input.Tex.xy);

  // Convert color to linear space
  DiffuseTex.xyz = pow(DiffuseTex.xyz, 2.2f);

  PS_OUTPUT output;
  output.PosRT = float4(input.PosW.xyz, 1.0);
  output.AlbedoRT = DiffuseTex;
  output.NormalRT = NormalTex;
  output.MetallicRT = MetallicTex;
  output.RoughnessRT = RoughnessTex;

 return output;
}