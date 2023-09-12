// -----------------------------------
// - ORB 2D -
// Renderer2D Poly Line Shader
// -----------------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_LocalPosition;
layout(location = 2) in vec3 a_StartPosition;
layout(location = 3) in vec3 a_EndPosition;
layout(location = 4) in vec4 a_Color;
layout(location = 5) in float a_Thickness;
layout(location = 6) in int a_EntityID;

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
};

layout(location = 0) out VertexOutput Output;
layout(location = 5) out flat int v_EntityID;

void main()
{
	Output.LocalPosition = a_LocalPosition;
	Output.StartPosition = a_StartPosition;
	Output.EndPosition = a_EndPosition;
	Output.Color = a_Color;
	Output.Thickness = a_Thickness;
	
	v_EntityID = a_EntityID;
	
	gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
	
	//Output.StartPosition = (u_ViewProjection * vec4(a_StartPosition, 1.0)).xyz;
	//Output.EndPosition = (u_ViewProjection * vec4(a_EndPosition, 1.0)).xyz;


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
};

layout(location = 0) in VertexOutput Input;
layout(location = 5) in flat int v_EntityID;

void main()
{
    o_Color = vec4(1.0, 1.0, 1.0, 0.25);        
	
	/*
	vec3 p3 = Input.LocalPosition;
    vec3 p12 = Input.EndPosition - Input.StartPosition;
    vec3 p13 = p3 - Input.StartPosition;

    float d = dot(p12, p13) / length(p12); // = length(p13) * cos(angle)
    vec3 p4 = Input.StartPosition + normalize(p12) * d;
    
	if (length(p4 - p3) < Input.Thickness
	///* * sin01(iTime * 4.0 + length(p4 - p1)* 0.02)*
          //&& length(p4 - Input.StartPosition) <= length(p12)
          //&& length(p4 - Input.EndPosition) <= length(p12)
		  )
	{
        o_Color += Input.Color;
    }
	*/
	/*
	float fade = 0.005;
	// Calculate distance and fill circle with the color
    float distance = 1.0 - length(Input.LocalPosition.xy);
    float circle = smoothstep(0.0, fade, distance);
    circle *= smoothstep(Input.Thickness + fade, Input.Thickness, distance);
    
	if (circle == 0.0f)
		discard;

    // Set Output color
    o_Color = Input.Color;
    o_Color.a *= circle;

    o_Color = vec4(1.0, 1.0, 1.0, 0.25);        
	
    vec3 p_1 = vec3(200.0, 200.0, 0);
    vec3 p_2 = vec3(200.0, 400.0, 0);
    
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
	*/

    vec3 p3 = Input.LocalPosition;
    vec3 p12 = Input.EndPosition - Input.StartPosition;
    vec3 p13 = p3 - Input.StartPosition;
    
    float p12_length = length(p12);
    vec3 p12_normed = p12 / p12_length;
    vec3 perp_to_p12_normed = vec3(p12_normed.y, -p12_normed.x, p12_normed.z);
    
    // Project p12 onto the perpendicular to the line
    if (abs(dot(perp_to_p12_normed, p13)) < Input.Thickness)
    {
        // t value for the projection onto p12
        float t = dot(p13, p12_normed);
        if (0.0 <= t && t <= p12_length) // in range of p1 -> p2
            o_Color += Input.Color;        
    }

	o_EntityID = v_EntityID; // placeholder for the entity ID
}
