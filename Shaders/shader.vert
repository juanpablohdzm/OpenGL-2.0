#version 410   

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2  tex;
layout (location = 2) in vec3 norm;

uniform mat4 model;							
uniform mat4 projection;
uniform mat4 view;	
uniform mat4 directionalLightTransform;
																												
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragWorldPos;
out vec4 DirectionalLightSpacePos;

											
											
void main()									
{																						
    gl_Position = projection* view *model*vec4(pos.x, pos.y, pos.z,1.0);
    DirectionalLightSpacePos = directionalLightTransform * model *vec4(pos,1.0f);

    TexCoord = tex;
    Normal = mat3(transpose(inverse(model))) * norm;
    FragWorldPos = (model * vec4(pos,1.0f)).xyz; //model multiplication gives us the world position
};