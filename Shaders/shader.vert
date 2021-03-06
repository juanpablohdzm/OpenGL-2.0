#version 410   

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2  tex;
layout (location = 2) in vec3 norm;
layout (location = 3) in vec3 tang;

uniform mat4 model;							
uniform mat4 projection;
uniform mat4 view;	
uniform mat4 directionalLightTransform;
uniform float _time;
uniform int bUseTime;

out mat3 TBN;																										
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragWorldPos;
out vec4 DirectionalLightSpacePos;

											
											
void main()									
{																						
    DirectionalLightSpacePos = directionalLightTransform * model *vec4(pos,1.0f);


    vec3 T = normalize(vec3(model*vec4(tang,0.0f)));
    vec3 N = normalize(vec3(model*vec4(norm,0.0f)));
    vec3 B = normalize(vec3(model*vec4(cross(N,T),0.0f)));
    TBN = mat3(T,B,N);

    TexCoord = tex;
    Normal = mat3(transpose(inverse(model))) * norm;
    FragWorldPos = (model * vec4(pos,1.0f)).xyz; //model multiplication gives us the world position

    vec3 finalPos = bUseTime > 0 ? pos + (0.02f*sin(_time*2.0f)-0.02f)*norm : pos;
    gl_Position = projection* view *model*vec4(finalPos.x, finalPos.y, finalPos.z,1.0);
};