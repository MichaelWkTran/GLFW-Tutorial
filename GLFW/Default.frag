#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 crntPos;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 PointLight(float _fAmbient)
{
	vec3 v3LightVec = lightPos - crntPos;
	float fLightDistance = length(v3LightVec);
	float fA = 3.0f;
	float fB = 0.7f;
	float fIntensity = 1.0f / ((fA * fLightDistance * fLightDistance) + (fB * fLightDistance) + 1.0f);

	vec3 v3Normal = normalize(Normal);
	vec3 v3lightDirection = normalize(lightPos - crntPos);
	float fDiffuse = max(dot(v3Normal, v3lightDirection), 0.0f);

	float fSpecularLight = 0.5f;
	vec3 v3ViewDirection = normalize(camPos - crntPos);
	vec3 v3ReflectionDirection = reflect(-v3lightDirection, v3Normal);
	float fSpecAmount = pow(max(dot(v3ViewDirection, v3ReflectionDirection), 0.0f), 16);
	float fSpecular = fSpecAmount * fSpecularLight;

	return (texture(tex0, texCoord) * color * lightColor * ((fDiffuse  * fIntensity) + _fAmbient)) + 
	       (texture(tex1, texCoord).r * fSpecular * fIntensity);
}

vec4 DirectionalLight(float _fAmbient)
{
	vec3 v3Normal = normalize(Normal);
	vec3 v3lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float fDiffuse = max(dot(v3Normal, v3lightDirection), 0.0f);

	float fSpecularLight = 0.5f;
	vec3 v3ViewDirection = normalize(camPos - crntPos);
	vec3 v3ReflectionDirection = reflect(-v3lightDirection, v3Normal);
	float fSpecAmount = pow(max(dot(v3ViewDirection, v3ReflectionDirection), 0.0f), 16);
	float fSpecular = fSpecAmount * fSpecularLight;

	return (texture(tex0, texCoord) * color * lightColor * (fDiffuse + _fAmbient)) + 
	       (texture(tex1, texCoord).r * fSpecular);
}

vec4 SpotLight(float _fAmbient)
{
	float fOuterCone = 0.9f;
	float fInnerCone = 0.95f;

	vec3 v3Normal = normalize(Normal);
	vec3 v3lightDirection = normalize(lightPos - crntPos);
	float fDiffuse = max(dot(v3Normal, v3lightDirection), 0.0f);

	float fSpecularLight = 0.5f;
	vec3 v3ViewDirection = normalize(camPos - crntPos);
	vec3 v3ReflectionDirection = reflect(-v3lightDirection, v3Normal);
	float fSpecAmount = pow(max(dot(v3ViewDirection, v3ReflectionDirection), 0.0f), 16);
	float fSpecular = fSpecAmount * fSpecularLight;

	float fAngle = dot(vec3(0.0f, -1.0f, 0.0f), -v3lightDirection);
	float fIntensity = clamp((fAngle - fOuterCone) / (fInnerCone - fOuterCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * color * lightColor * ((fDiffuse  * fIntensity) + _fAmbient)) + 
	       (texture(tex1, texCoord).r * fSpecular * fIntensity);
}

void main()
{
	float fAmbient = 0.2f;

	FragColor = SpotLight(fAmbient);
}