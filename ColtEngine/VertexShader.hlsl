/////////////////////////////
// Filename: VertexShader.hlsl
/////////////////////////////

// cbuffer (Constant Buffer)
// Allows us to define a buffer of individual variables which will hold data from our C++ code
cbuffer externalData : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

// Struct representing a single vertex worth of data that matches the vertex definition in our C++ code
struct VertexShaderInput
{
	float3 position		: POSITION;     // XYZ position
	float2 uv			: TEXCOORD;		// UV
	float3 normal		: NORMAL;       // Normal
};

// Struct representing the data we're sending down the pipeline that matches our pixel shader's input
struct VertexToPixel
{
	float4 position		: SV_POSITION;	// XYZW position (System Value Position)
	float2 uv			: TEXCOORD;		// UV
	float3 normal		: NORMAL;		// Normal
	float4 color		: COLOR;        // RGBA color
};

VertexToPixel main(VertexShaderInput input)
{
	// Set up output struct
	VertexToPixel output;

	// Convert the vertex's position to world then camera then screen space coords by calculating the world * view * projection matrix
	matrix worldViewProj = mul(mul(world, view), projection);

	// Then convert the position to a 4-component vector to multiply it by our new matrix
	// Screen coords are X,Y and distance from camera (depth) is Z
	output.position = mul(float4(input.position, 1.0f), worldViewProj);

	// Pass the color through 
	// The values will be interpolated per-pixel by the rasterizer
	// We don't need to alter it here, but we do need to send it to the pixel shader
	output.color = float4(0, 0, 1, 1);

	// Calculate the transformed normal
	output.normal = mul(input.normal, (float3x3)world);

	// Pass the UVs through
	output.uv = input.uv;

	// Whatever we return will make its way through the pipeline to the next programmable stage we're using
	return output;
}