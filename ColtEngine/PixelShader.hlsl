/////////////////////////////
// Filename:PixelShader.hlsl
/////////////////////////////

// Struct representing the data we expect to receive from earlier pipeline stages
struct VertexToPixel
{
	float4 position		: SV_POSITION;	// XYZW Position
	float2 uv			: TEXCOORD;		// UV
	float3 normal		: NORMAL;		// Normal
	float4 color		: COLOR;		// RGBA Color
};

float4 main(VertexToPixel input) : SV_TARGET
{
	float4 finalColor = input.color;
	return finalColor;
}