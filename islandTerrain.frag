
uniform sampler2D textureSample_0;
uniform sampler2D textureSample_1;

varying vec2 TexCoord0;

void main() 
{

	vec4 texel0, texel1, resultColor;
     	
     	texel0 = texture2D(textureSample_0, TexCoord0);
     	texel1 = texture2D(textureSample_1, TexCoord0*10.0);
	float alpha = texture2D(textureSample_1, TexCoord0).a;
    	vec4 textureF = vec4(texel0.rgb*(1.0-alpha) + texel1.rgb*alpha, 1.0);
     
     	resultColor = mix(texel0, textureF, textureF.a);
     	gl_FragColor = gl_Color * resultColor;
     	
}

