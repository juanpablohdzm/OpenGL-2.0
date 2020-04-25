#version 410   						
out vec4 colour;


in vec2 TexCoord;
in vec3 Normal;
in vec3 FragWorldPos;
in vec4 DirectionalLightSpacePos;
in mat3 TBN;

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

struct OmniShadowMap
{
	samplerCube shadowMap;
	float farPlane;
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
uniform OmniShadowMap omniShadowMaps[3];

uniform sampler2D theTexture; //This is going through GL_TEXTURE0
uniform sampler2D normalTexture;
uniform sampler2D directionalShadowMap;
uniform int useNormalTexture;

uniform Material material;
uniform  vec3 eyePosition;


float CalcDirectionalShadowFactor(DirectionalLight light, vec3 normal)
{
	vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w;
	projCoords = (projCoords* 0.5f)+0.5f;


	float current = projCoords.z;

	normal = normalize(normal);
	vec3 lightDir = normalize(light.direction);
	float bias = max(0.05f*(1-dot(normal,-lightDir)),0.005f);

	float shadow =0.0f;

	vec2 texelSize = 1.0f / textureSize(directionalShadowMap,0);
	for(int x = -1; x<= 1; x++)
	{
		for(int y = -1; y<= 1; y++)
		{
			float pcfDepth = texture(directionalShadowMap, projCoords.xy+ vec2(x,y)* texelSize).r;
			shadow += current - bias > pcfDepth ? 1.0f : 0.0f;
		}
	}

	shadow /= 9.0f;

	if(projCoords.z > 1.0f)
	{
		shadow = 0.0f;
	}

	return shadow;

}

float CalcOmniShadowFactor(PointLight light, int shadowIndex)
{
	vec3 fragToLight  = FragWorldPos - light.position;
	float closest = texture(omniShadowMaps[shadowIndex].shadowMap,fragToLight).r;

	closest *= omniShadowMaps[shadowIndex].farPlane;

	float current = length(fragToLight); 

	float bias  = 0.05f;
	float shadow = current - bias > closest ? 1.0f : 0.0f;

	return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction,vec3 normal, float shadowFactor)
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

	return ambientColour + (1.0f-shadowFactor)*(diffuseColour + specularColour);
}

vec4 CalcDirectionalLight(vec3 normal)
{
	float shadow = CalcDirectionalShadowFactor(directionalLight,normal);
	return CalcLightByDirection(directionalLight.base,directionalLight.direction, normal,shadow);
}

vec4 CalcPointLight(PointLight pLight, vec3 normal, int shadowIndex)
{
	vec3 direction = FragWorldPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	float shadowFactor = CalcOmniShadowFactor(pLight,shadowIndex);

	vec4 colour = CalcLightByDirection(pLight.base,direction,normal,shadowFactor);
	float attenuation = pLight.exponent * distance * distance + pLight.linear *distance + pLight.constant;

	return (colour / attenuation);

}

vec4 CalcSpotLight(SpotLight sLight,vec3 normal, int shadowIndex)
{
	vec3 rayDirection = normalize(FragWorldPos - sLight.base.position);
	float slFactor = dot(rayDirection,normalize(sLight.direction));

	if(slFactor > sLight.edge)
	{
		vec4 colour = CalcPointLight(sLight.base,normal,shadowIndex);
		return colour *(1.0f-(1.0f-slFactor)*(1.0f/(1.0f-sLight.edge)));
	}
	return vec4(0.0f,0.0f,0.0f,0.0f);
}

vec4 CalcPointLights(vec3 normal)
{
	vec4 totalColour = vec4(0,0,0,0);
	for(int i=0; i< pointLightCount; i++)
	{
		totalColour += CalcPointLight(pointLights[i],normal,i);

	}

	return totalColour;
}

vec4 CalcSpotLights(vec3 normal)
{
	vec4 totalColour = vec4(0,0,0,0);
	for(int i=0; i< spotLightCount; i++)
	{
		totalColour += CalcSpotLight(spotLights[i],normal,i+pointLightCount);

	}

	return totalColour;
}


void main()									
{	

	vec4 normal = texture2D(normalTexture,TexCoord);
	vec3 newNormal = useNormalTexture != 0 ? normalize(TBN*vec3(normal)) : Normal;
	vec4 finalColour = vec4(0.0f,0.0f,0.0f,0.0f);
	finalColour += CalcDirectionalLight(newNormal);
	finalColour += CalcPointLights(newNormal);
	finalColour += CalcSpotLights(newNormal);
	colour = texture(theTexture,TexCoord) * finalColour;										
};