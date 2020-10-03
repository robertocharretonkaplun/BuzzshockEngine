/**
* @file CubeProjectFor.fx
* @version 1.0
* @date 25/07/2020
* @author Roberto Charreton Kaplun (idv17c.rcharreton@uartesdigitales.edu.mx)
*/
Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer cbNeverChanges : register( b0 )
{
    matrix View;
};

cbuffer cbChangeOnResize : register( b1 )
{
    matrix Projection;
};

cbuffer cbChangesEveryFrame : register( b2 )
{
    matrix World;
    float4 vMeshColor;
};

cbuffer cbBonesTransform : register ( b3 )
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
  float f = dot(lightDir, surfNormal) * 4 + 0.5; // This is for toon shading
  f = int(f);
  return max(0.0f, f * .25);
}

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;

    matrix boneTrans = Identity;
    for (int i = 0; i < 4; i++) {
      if (input.BonesIDs[i] > 1000) {
        break;
      }
      boneTrans += boneTransform[input.BonesIDs[i]] * input.Weights[i];
    }
   
    float4 position = mul(input.Pos, boneTrans);

    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
    output.Tex = input.Tex;
    output.Nor = normalize(mul(float4(input.Nor, 0), World));

    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PS_INPUT input) : SV_Target
{
  float3 LightPos = float3(-100, 0, 0);

  float3 surfColor = float3(1, 0,0);

  float3 LightDir = normalize(LightPos - input.Pos);

  float kD = Lambert_Diffuse(LightDir, input.Nor);

  float3 finalColor = surfColor * kD * 0.8f;

  float3 texColor = txDiffuse.Sample(samLinear, input.Tex) * finalColor;
  return float4(finalColor, 1);
  //return txDiffuse.Sample(samLinear, input.Tex) * vMeshColor;
}
