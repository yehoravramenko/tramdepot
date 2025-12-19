float4 VS(float4 inPos : POSITION) : SV_Position
{
    return inPos;
}

float4 PS() : SV_Target
{
    return float4(0.0f, 0.3f, 0.0f, 1.0f);
}