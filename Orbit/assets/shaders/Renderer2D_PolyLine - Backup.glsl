// -----------------------------------
// - ORB 2D -
// Renderer2D Line Shader
// -----------------------------------

#type vertex
#version 450 core


layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_Resolution;
layout(location = 2) in float a_Thickness;
layout(location = 3) in vec4 a_Color;
layout(location = 4) in int a_EntityID;

layout(std140, binding = 0) buffer Vertices
{
   vec4 b_Vertex[]; 
};

layout(std140, binding = 1) uniform Camera
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

//	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
	
	// Compute the index of the line segment, where the vertex coordinate belongs to and the index of the point in the 2 triangles
	int line_index = gl_VertexIndex / 6;
	int triangle_index = gl_VertexIndex % 6;

	vec4 va[4]; // vertex array
	for (int i=0; i<4; ++i)
	{
		va[i] = u_ViewProjection * b_Vertex[line_index+i];
		va[i].xyz /= va[i].w;
		va[i].xy = (va[i].xy + 1.0) * 0.5 * a_Resolution;
	}

	vec2 v_line = normalize(va[2].xy - va[1].xy);
	vec2 nv_line = vec2(-v_line.y, v_line.x);

//	vec4 pos; // position
	vec4 pos = vec4(a_Position.x,a_Position.y,a_Position.z, 0.0f); // position
	if (triangle_index == 0 || triangle_index == 1 || triangle_index == 3)
	{
		vec2 v_pred  = normalize(va[1].xy - va[0].xy);
        vec2 v_miter = normalize(nv_line + vec2(-v_pred.y, v_pred.x));

        pos = va[1];
        pos.xy += v_miter * a_Thickness * (triangle_index == 1 ? -0.5 : 0.5) / dot(v_miter, nv_line);
	}
	else
	{
		vec2 v_succ = normalize(va[3].xy - va[2].xy);
        vec2 v_miter = normalize(nv_line + vec2(-v_succ.y, v_succ.x));

        pos = va[2];
        pos.xy += v_miter * a_Thickness * (triangle_index == 5 ? 0.5 : -0.5) / dot(v_miter, nv_line);
	}
		
    pos.xy = pos.xy / a_Resolution * 2.0 - 1.0;
    pos.xyz *= pos.w;
    gl_Position = pos;
}

 /*--------------------------------------------------------------
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in int a_EntityID;

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

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}	


//---------------------------------------------------------------
layout(std430, binding = 0) buffer TVertex
{
   vec4 vertex[]; 
};

uniform mat4  u_mvp;
uniform vec2  u_resolution;
uniform float u_thickness;

void main()
{
    int line_i = gl_VertexID / 6;
    int tri_i  = gl_VertexID % 6;

    vec4 va[4];
    for (int i=0; i<4; ++i)
    {
        va[i] = u_mvp * vertex[line_i+i];
        va[i].xyz /= va[i].w;
        va[i].xy = (va[i].xy + 1.0) * 0.5 * u_resolution;
    }

    vec2 v_line  = normalize(va[2].xy - va[1].xy);
    vec2 nv_line = vec2(-v_line.y, v_line.x);

    vec4 pos;
    if (tri_i == 0 || tri_i == 1 || tri_i == 3)
    {
        vec2 v_pred  = normalize(va[1].xy - va[0].xy);
        vec2 v_miter = normalize(nv_line + vec2(-v_pred.y, v_pred.x));

        pos = va[1];
        pos.xy += v_miter * u_thickness * (tri_i == 1 ? -0.5 : 0.5) / dot(v_miter, nv_line);
    }
    else
    {
        vec2 v_succ  = normalize(va[3].xy - va[2].xy);
        vec2 v_miter = normalize(nv_line + vec2(-v_succ.y, v_succ.x));

        pos = va[2];
        pos.xy += v_miter * u_thickness * (tri_i == 5 ? 0.5 : -0.5) / dot(v_miter, nv_line);
    }

    pos.xy = pos.xy / u_resolution * 2.0 - 1.0;
    pos.xyz *= pos.w;
    gl_Position = pos;
}


 */ //--------------------------------------------------------------

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

layout(binding = 0) uniform sampler2D u_Textures[32];

void main()
{
	o_Color = Input.Color;

	o_EntityID= v_EntityID; // placeholder for the entity ID
}
