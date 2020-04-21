#version 410   						
out vec4 colour;


in vec2 TexCoord;
in vec3 Normal;
in vec3 FragWorldPos;

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 3;

struct Light
{	
	vec3 colour;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float exponent;
	float linear;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float roughness;
};

uniform DirectionalLight directionalLight;
uniform int pointLightCount;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int spotLightCount;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture; //This is going through GL_TEXTURE0
uniform sampler2D normalTexture;
uniform int useNormalTexture;

uniform Material material;
uniform  vec3 eyePosition;

vec4 CalcLightByDirection(Light light, vec3 direction,vec3 normal)
{
	vec4 ambientColour = vec4(light.colour,1.0f) * light.ambientIntensity;
	
	float diffuseFactor = max(dot(normalize(normal),normalize(-direction)),0.0f);
	vec4 diffuseColour = vec4(light.colour,1.0f)*light.diffuseIntensity*diffuseFactor;


	vec4 specularColour = vec4(0.0, 0.0, 0.0, 1.0);
	if(diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragWorldPos);
		vec3 reflectedLight = normalize(reflect(direction,normalize(normal)));

		float specularFactor = dot(fragToEye, reflectedLight);
		if(specularFactor> 0.0f)
		{
			specularFactor = pow(specularFactor,material.roughness);
			specularColour = vec4(light.colour,1.0f)* specularFactor * material.specularIntensity;
		}
	}

	return ambientColour + diffuseColour + specularColour;
}

vec4 CalcDirectionalLight(vec3 normal)
{
	return CalcLightByDirection(directionalLight.base,directionalLight.direction, normal);
}

vec4 CalcPointLight(PointLight pLight, vec3 normal)
{
	vec3 direction = FragWorldPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 colour = CalcLightByDirection(pLight.base,direction,normal);
	float attenuation = pLight.exponent * distance * distance + pLight.linear *distance + pLight.constant;

	return (colour / attenuation);

}

vec4 CalcSpotLight(SpotLight sLight,vec3 normal)
{
	vec3 rayDirection = normalize(FragWorldPos - sLight.base.position);
	float slFactor = dot(rayDirection,normalize(sLight.direction));

	if(slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base,normal);
		return colour *(1.0f-(1.0f-slFactor)*(1.0f/(1.0f-sLight.edge)));
	}
	return vec4(0.0f,0.0f,0.0f,0.0f);
}

vec4 CalcPointLights(vec3 normal)
{
	vec4 totalColour = vec4(0,0,0,0);
	for(int i=0; i< pointLightCount; i++)
	{
		totalColour += CalcPointLight(pointLights[i],normal);

	}

	return totalColour;
}

vec4 CalcSpotLights(vec3 normal)
{
	vec4 totalColour = vec4(0,0,0,0);
	for(int i=0; i< spotLightCount; i++)
	{
		totalColour += CalcSpotLight(spotLights[i],normal);

	}

	return totalColour;
}


void main()									
{	

	vec4 normal = texture2D(normalTexture,TexCoord);
	vec3 newNormal = useNormalTexture != 0 ? normalize(normal.xyz+Normal) : Normal;
	vec4 finalColour = vec4(0.0f,0.0f,0.0f,0.0f);
	finalColour += CalcDirectionalLight(newNormal);
	finalColour += CalcPointLights(newNormal);
	finalColour += CalcSpotLights(newNormal);
	colour = texture(theTexture,TexCoord) * finalColour;										
};