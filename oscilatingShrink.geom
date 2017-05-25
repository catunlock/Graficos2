#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform float speed = 0.2f;
uniform float time;


void main( void )
{
	float t = mod(time, 2.0f);
	vec4 c = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0f ;
	
	float a = sin(fract(time*speed));


	if (0 <= t && t < 1.0f/speed) {
		
		if (gl_PrimitiveIDIn % 2 == 0) 
		{
			for( int i = 0 ; i < 3 ; i++ )
			{
				gfrontColor = vfrontColor[i];
				gl_Position = gl_in[i].gl_Position;
				EmitVertex();
			}
			EndPrimitive();
		}
		else {
			
			for( int i = 0 ; i < 3 ; i++ )
			{
				gfrontColor = vfrontColor[i];
				vec3 newV = mix(gl_in[i].gl_Position.xyz, c.xyz, a);
				gl_Position = vec4(newV,1);
				gl_Position = mix(gl_in[i].gl_Position, c, a);
				EmitVertex();
			}
			EndPrimitive();
		}
	}

	if (1.0f/speed <= t && t < 2.0f/speed) {
		if (gl_PrimitiveIDIn % 2 == 1) 
		{
			for( int i = 0 ; i < 3 ; i++ )
			{
				gfrontColor = vfrontColor[i];
				gl_Position = gl_in[i].gl_Position;
				EmitVertex();
			}
			EndPrimitive();
		}
		else {
			for( int i = 0 ; i < 3 ; i++ )
			{
				gfrontColor = vfrontColor[i];
				gl_Position = mix(gl_in[i].gl_Position, c, a);
				EmitVertex();
			}
			EndPrimitive();
		}
	}

	
}
