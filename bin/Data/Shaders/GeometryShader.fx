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
  matrix WorldViewProj = mul(World, View);
  WorldViewProj = mul(WorldViewProj, Projection);
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
    output.PosH = mul(v[i], WorldViewProj);
    output.PosW - v[i].xyz;
    output.NormalW = look;
    output.texCoord = tex[i];
    
    triStream.Append(output);
  }
}

struct PS_OUTPUT {
  float4 Color : SV_Target0;
};
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
PS_OUTPUT PS(GS_OUTPUT input) {
  PS_OUTPUT output = (PS_OUTPUT)0;

  output.Color = float4(255, 0, 0, 255);
  return output;
}