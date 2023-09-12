// -----------------------------------
// - ORB 2D -
// Renderer2D Circle Shader
// -----------------------------------

#type vertex
#version 450 core
 
layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_LocalPosition;
layout(location = 2) in vec4 a_Color;
layout(location = 3) in float a_Thickness;
layout(location = 4) in float a_Fade;
layout(location = 5) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec3 LocalPosition;
	vec3 StartPosition;
	vec3 EndPosition;
	vec4 Color;
	float Thickness;
	float Fade;
};

layout(location = 0) out VertexOutput Output;
layout(location = 6) out flat int v_EntityID;

void main()
{
	Output.LocalPosition = a_LocalPosition;
	Output.Color = a_Color;
	Output.Thickness = a_Thickness;
	Output.Fade = a_Fade;

	v_EntityID = a_EntityID;

	//gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
		
	vec3 a_StartPosition = vec3(0.0, 2.0, 0.0);
	vec3 a_EndPosition = vec3(5.0, 20.0, 0.0);

	Output.StartPosition = (u_ViewProjection * vec4(a_StartPosition, 1.0)).xyz;
	Output.EndPosition = (u_ViewProjection * vec4(a_EndPosition, 1.0)).xyz;
}	

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	vec3 LocalPosition;
	vec3 StartPosition;
	vec3 EndPosition;
	vec4 Color;
	float Thickness;
	float Fade;
};

layout(location = 0) in VertexOutput Input;
layout(location = 6) in flat int v_EntityID;

void main()
{
	/*
    // Calculate distance and fill circle with the color
    float distance = 1.0 - length(Input.LocalPosition);
    float circle = smoothstep(0.0, Input.Fade, distance);
    circle *= smoothstep(Input.Thickness + Input.Fade, Input.Thickness, distance);
    
	if (circle == 0.0f)
		discard;

    // Set Output color
    o_Color = Input.Color;
    o_Color.a *= circle;
	*/
	/// ---------------------------------------------------------
    o_Color = vec4(1.0, 1.0, 1.0, 0.25);        

	vec3 p_1 = Input.StartPosition;
    vec3 p_2 = Input.EndPosition;
    
    vec3 p3 = Input.LocalPosition;
    vec3 p12 = p_2 - p_1;
    vec3 p13 = p3 - p_1;
    
    float p12_length = length(p12);
    vec3 p12_normed = p12 / p12_length;
    vec3 perp_to_p12_normed = vec3(p12_normed.y, -p12_normed.x, p12_normed.z);
    
    // Project p12 onto the perpendicular to the line
    if (abs(dot(perp_to_p12_normed, p13)) < Input.Thickness)
    {
        // t value for the projection onto p12
        float t = dot(p13, p12_normed);
        if (0.0 <= t && t <= p12_length) // in range of p1 -> p2
            o_Color += vec4(0.0, 1.0, 0.0, 1.0);        
    }

	/// ---------------------------------------------------------
	// placeholder for the entity ID
	o_EntityID = v_EntityID;
}
