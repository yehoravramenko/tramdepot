cbuffer MatrixBuffer : register(b0)
{
    matrix g_WorldViewProjection;
};

struct VSInput
{
    float3 pos : POSITION;
    float4 col : COLOR;
};

struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.pos = mul(float4(input.pos, 1.0f), g_WorldViewProjection);
    output.col = input.col;
    return output;
}

float4 PSMain(VSOutput input) : SV_TARGET
{
    return input.col;
}