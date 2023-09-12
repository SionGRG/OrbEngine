// -----------------------------------
// - ORB 2D -
// Renderer2D Poly Line Shader
// -----------------------------------

#type vertex
#version 450 core

layout(location = 0) in vec3 a_WorldPosition;
layout(location = 1) in vec3 a_StartPosition;
layout(location = 2) in vec3 a_EndPosition;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in float a_Thickness;
layout(location = 5) in int a_EntityID;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	// vec3 WorldPosition;
	// vec3 StartPosition;
	//vec3 EndPosition;
	vec4 ClipA;
	vec4 ClipB;
	vec4 Color;
	float Thickness;
};

layout(location = 0) out VertexOutput Output;
layout(location = 5) out flat int v_EntityID;

void main()
{
	//Output.WorldPosition = a_WorldPosition;
	//Output.StartPosition = a_StartPosition;
	//Output.EndPosition = a_EndPosition;
	Output.Color = a_Color;
	Output.Thickness = a_Thickness;
	
	v_EntityID = a_EntityID;
	
	
	// transform the points A and B to clip space
	Output.ClipA = u_ViewProjection * vec4(a_StartPosition, 1.0);
	Output.ClipB = u_ViewProjection * vec4(a_EndPosition, 1.0);

	gl_Position = u_ViewProjection * vec4(a_WorldPosition, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 o_Color;
layout(location = 1) out int o_EntityID;

struct VertexOutput
{
	//vec3 WorldPosition;
	//vec3 StartPosition;
	//vec3 EndPosition;
	vec4 ClipA;
	vec4 ClipB;
	vec4 Color;
	float Thickness;
};

layout(location = 0) in VertexOutput Input;
layout(location = 5) in flat int v_EntityID;

// a function that returns the distance from a point p to a line segment AB
float distanceToLineSegment(vec3 p, vec3 A, vec3 B) {
    vec3 AP = p - A;
    vec3 AB = B - A;
    float t = clamp(dot(AP, AB) / dot(AB, AB), 0.0, 1.0);
    return length(AP - AB * t);
}

void main()
{
	// transform the points A and B to clip space
    // vec4 clipA = mvp * vec4(A, 1.0);
    // vec4 clipB = mvp * vec4(B, 1.0);

    // divide by w to get the normalized device coordinates
    vec3 ndcA = Input.ClipA.xyz / Input.ClipA.w;
    vec3 ndcB = Input.ClipB.xyz / Input.ClipB.w;

    // get the current fragment position in normalized device coordinates
    vec3 ndcP = gl_FragCoord.xyz / gl_FragCoord.w;

    // calculate the distance from the fragment to the line segment
    float d = distanceToLineSegment(ndcP, ndcA, ndcB);

    // if the distance is less than the half of the thickness, draw the line
    if (d < Input.Thickness / 2.0) {
//        o_Color = vec4(1.0, 1.0, 1.0, 1.0); // white color
        o_Color = Input.Color; // white color
    } else {
        discard; // discard the fragment
    }

	o_EntityID = v_EntityID; // placeholder for the entity ID
}
