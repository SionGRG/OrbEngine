// -----------------------------------
// - ORB 2D -
// Renderer2D Poly Line Shader
// -----------------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_StartPosition;
layout(location = 1) in vec3 a_EndPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Thickness;
layout(location = 4) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 Color;
};

layout(location = 0) out VertexOutput Output;
layout(location = 1) out flat int v_EntityID;

void main()
{
	Output.Color = a_Color;
	v_EntityID = a_EntityID;
	
	vec4 p0 = u_ViewProjection * vec4(a_StartPosition, 1.0); // first point of the line in clip space
    vec4 p1 = u_ViewProjection * vec4(a_EndPosition, 1.0); // second point of the line in clip space
    vec3 dir = normalize(p1.xyz - p0.xyz); // direction of the line
    vec3 normal = cross(dir, vec3(0.0, 0.0, 1.0)); // normal vector of the line

    // generate four vertices for the quad
    gl_Position = p0 + vec4(normal * a_Thickness / 2.0, 0.0);
    //EmitVertex();
    gl_Position = p0 - vec4(normal * a_Thickness / 2.0, 0.0);
    //EmitVertex();
    gl_Position = p1 + vec4(normal * a_Thickness / 2.0, 0.0);
    //EmitVertex();
    gl_Position = p1 - vec4(normal * a_Thickness / 2.0, 0.0);
    //EmitVertex();
    //EndPrimitive();
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec4 Color;
};

layout(location = 0) in VertexOutput Input;
layout(location = 1) in flat int v_EntityID;

void main()
{
	o_Color = Input.Color;
    
	o_EntityID = v_EntityID; // placeholder for the entity ID
}
