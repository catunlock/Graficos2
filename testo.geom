#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float time;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();

	if (gl_PrimitiveIDIn < 1000* time) {

		for( int i = 0 ; i < 3 ; i++ )
		{
			gfrontColor = 0.5*vfrontColor[i];
			gl_Position = gl_in[i].gl_Position + vec4(7, 0,0 ,0);
			EmitVertex();
		}
		EndPrimitive();
	}
}
