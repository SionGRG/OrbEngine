// -----------------------------------
// - ORB 2D -
// Renderer2D Line Shader
// -----------------------------------

#type vertex
#version 450 core


layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_StartPosition;
layout(location = 2) in vec3 a_EndPosition;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in float a_Thickness;
layout(location = 5) in int a_EntityID;

layout(std140, binding = 1) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec3 WorldPosition;
	vec3 StartPosition;
	vec3 EndPosition;
	vec4 Color;
	float Thickness;
};

layout(location = 0) out VertexOutput Output;
layout(location = 5) out flat int v_EntityID;

void main()
{
	Output.StartPosition = a_StartPosition;
	Output.EndPosition = a_EndPosition;
	Output.Color = a_Color;
	Output.Thickness = a_Thickness;
	
	v_EntityID = a_EntityID;
	
	//gl_Position = u_ViewProjection * vec4(a_StartPosition, 1.0);
	//gl_Position = u_ViewProjection * vec4(a_EndPosition, 1.0);
	
	gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
	Output.WorldPosition = a_WorldPosition;
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec3 WorldPosition;
	vec3 StartPosition;
	vec3 EndPosition;
	vec4 Color;
	float Thickness;
};

layout(location = 0) in VertexOutput Input;
layout(location = 5) in flat int v_EntityID;

layout(binding = 0) uniform sampler2D u_Textures[32];

/*
void DrawLine(vec3 p1, vec3 p2, vec4 color, float thickness)
{
	vec3 p3 = vec3(2, 1, 0);
	vec3 p12 = p2 - p1;
	vec3 p13 = p3 - p1;

	float d = dot(p12, p13) / length(p12); // = length(p13) * cos(angle)
	vec3 p4 = p1 + normalize(p12) * d;
	if (length(p4 - p3) < thickness
		&& length(p4 - p1) <= length(p12)
		&& length(p4 - p2) <= length(p12))
	{
		o_Color += color;
	}
}
*/

void main()
{
	// o_Color = Input.Color;

	// DrawLine(Input.StartPosition, Input.EndPosition, Input.Color, Input.Thickness);
	/*
//	vec3 p3 = vec3(gl_FragCoord.x, gl_FragCoord.y, 0);
	vec3 p3 = Input.WorldPosition;
	vec3 p12 = Input.EndPosition - Input.StartPosition;
	vec3 p13 = p3 - Input.StartPosition;

	float d = dot(p12, p13) / length(p12); // = length(p13) * cos(angle)
	vec3 p4 = Input.StartPosition + normalize(p12) * d;
	if (length(p4 - p3) < Input.Thickness
		&& length(p4 - Input.StartPosition) <= length(p12)
		&& length(p4 - Input.EndPosition) <= length(p12))
	{
		o_Color += Input.Color;
	}
	*/

	vec3 lineVector = Input.EndPosition - Input.StartPosition;
    vec3 normal = normalize(cross(lineVector, Input.WorldPosition - Input.StartPosition));
    float dist = abs(dot(normal, Input.WorldPosition - Input.StartPosition));
    
	if (dist < Input.Thickness / 2.0f)
        o_Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    else
        discard;


	o_EntityID = v_EntityID; // placeholder for the entity ID
}
