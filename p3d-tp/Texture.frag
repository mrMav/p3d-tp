/*
Shader inspiration and structure influence from:
https://learnopengl.com/Lighting/Multiple-lights
phong shading based on:
https://en.wikipedia.org/wiki/Phong_reflection_model
using mathematic model from:
OpenGL Programming Guide version 4.3, chapter 7, Multiple Lights and Materials
*/

#version 440 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

struct Mat {

	sampler2D diffuseMap;

	vec3 Ka;
	vec3 Kd;
	vec3 Ks;

	float Ns;

};

struct AmbientLight {

	vec3 ambient;

	float intensity;

};

struct DirectionalLight {

    vec3 direction;

	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct OmniLight {

    vec3 position;
	
    float constant;
    float linear;
    float quadratic;
	
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {

    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

uniform vec3 viewPos;
uniform AmbientLight ambLight;
uniform DirectionalLight dirLight;
uniform OmniLight omniLight;
//uniform SpotLight spotLight;
uniform Mat material;

vec3 GetAmbientLightInfluence(AmbientLight light);
vec3 GetDirectionalLightInfluence(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 GetOmniLightInfluence(OmniLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 GetSpotLightInfluence(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {

	// the normalized normal
    vec3 norm = normalize(Normal);

	// the direction of from the fragment position to the camera
    vec3 viewDir = normalize(viewPos - FragPos);

	// the resulting color
	vec3 result = vec3(0);

	// calculate the influence of the directional light
	result += GetAmbientLightInfluence(ambLight);
	result += GetDirectionalLightInfluence(dirLight, norm, viewDir);
	result += GetOmniLightInfluence(omniLight, norm, FragPos, viewDir);
	
	// output color
	FragColor = vec4(result, 1.0);

}

/*
simply returns the ambient color multiplied by an intensity
*/
vec3 GetAmbientLightInfluence(AmbientLight light) {
	
	return light.ambient * light.intensity * vec3(texture(material.diffuseMap, TexCoord));

}

/*
Computes the influence of a directional light.
A directional light will haveall its rays parallel
to each other.
The function uses the normal of the fragment to get 
the diffuse shading, taking into account the light position (ray direction)
and camera position
*/
vec3 GetDirectionalLightInfluence(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 texel = vec3(texture(material.diffuseMap, TexCoord));

    vec3 lightDir = normalize(-light.direction);
    
	// diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Ns);
    
	// combine results
    vec3 ambient = light.ambient * texel;
    vec3 diffuse = light.diffuse * diff * texel;
    vec3 specular = light.specular * spec * material.Ks;
    return (ambient + diffuse + specular);
}

vec3 GetOmniLightInfluence(OmniLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

	vec3 texel = vec3(texture(material.diffuseMap, TexCoord));

    vec3 lightDir = normalize(light.position - fragPos);

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Ns);

    //attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	
    //combine
    vec3 ambient  = light.ambient  * texel;
    vec3 diffuse  = light.diffuse  * diff * texel;
    vec3 specular = light.specular * spec * texel;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);

}