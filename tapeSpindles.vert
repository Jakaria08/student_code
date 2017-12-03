
// A super simple vertex shader that just mimics exactly what OpenGL's 
// default fixed pipeline does

uniform float currentTime;

void main() 
{
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient, spindle;
	float NdotL, theta = 0.0;


	normal = normalize(gl_NormalMatrix * gl_Normal);
	

	lightDir = normalize(vec3(gl_LightSource[0].position));
	
	NdotL = max(dot(normal, lightDir), 0.0);

	diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;
	globalAmbient = gl_LightModel.ambient * gl_FrontMaterial.ambient;
	gl_FrontColor =  NdotL * diffuse + globalAmbient + ambient;
	
	theta = theta+10.0;
	spindle = gl_MultiTexCoord0;
    	spindle.x = gl_MultiTexCoord0.x*cos(currentTime) - gl_MultiTexCoord0.y*sin(currentTime);
    	spindle.y = gl_MultiTexCoord0.y*cos(currentTime) + gl_MultiTexCoord0.x*sin(currentTime);
    
    	gl_TexCoord[0] = spindle ;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

