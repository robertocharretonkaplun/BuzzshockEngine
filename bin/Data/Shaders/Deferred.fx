#define M_PI 3.1415966538
#define EPSILON 0.00001
/**
* @file Deferred.fx
* @version 1.0
* @date 15/11/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txPosition   : register(t0);
Texture2D txAlbedo     : register(t1);
Texture2D txNormal     : register(t2);
SamplerState samLinear : register(s0);

cbuffer cbCamera : register(b0) {
  matrix View;
  matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b1) {
  matrix World;
};

// Vertex Shader input
struct VS_INPUT {
  float4 Pos      : POSITION;
  float2 Tex      : TEXCOORD0;
  float3 Nor      : NORMAL0;
  float3 Tan      : TANGENT0;
  uint4 BonesIDs  : BLENDINDICES0;
  float4 Weights  : BLENDWEIGHT0;
};

// Pixel shader input
struct PS_INPUT {
  float4 Pos      : SV_POSITION;
  float3 PosW     : TEXCOORD0;
  float2 Tex      : TEXCOORD1;
  float3 Nor      : NORMAL0;
  float2 TexCoord : TEXCOORD2;
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

  return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target{

  // Get Position Tex Value
  float4 PositionTex = txPosition.Sample(samLinear, input.Tex.xy);

  // Get ALbedo Tex Value
  float4 AlbedoTex = txAlbedo.Sample(samLinear, input.Tex.xy);

  // Get Normal Tex Value
  float4 NormalTex = txNormal.Sample(samLinear, input.Tex.xy);

 return float4(PositionTex.xyz, 1.0f);
}