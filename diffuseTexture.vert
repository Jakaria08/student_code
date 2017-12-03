
// A super simple vertex shader that just mimics exactly what OpenGL's 
// default fixed pipeline does
// Lighting code taken and modified from the reference given in problem description

void main() 
{                
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NdotL;


	normal = normalize(gl_NormalMatrix * gl_Normal);
	

	lightDir = normalize(vec3(gl_LightSource[0].position));
	
	NdotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;
	

	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

