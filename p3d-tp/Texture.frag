/*
Shader inspiration and structure influence from:
https://learnopengl.com/Lighting/Multiple-lights
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

};

struct DirectionalLight {

    vec3 direction;

    vec3 diffuse;
    vec3 specular;
};

struct OmniLight {

    vec3 position;
	
    float constant;
    float linear;
    float quadratic;
	
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
  
    vec3 diffuse;
    vec3 specular;       
};

uniform vec3 viewPos;
//uniform AmbientLight ambientLight;
uniform DirectionalLight dirLight;
//uniform OmniLight omniLight;
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
	result += GetDirectionalLightInfluence(dirLight, norm, viewDir);
	
	// output color
	FragColor = vec4(result, 1.0);

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
    vec3 lightDir = normalize(-light.direction);
    
	// diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    
	// specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.Ns);
    
	// combine results
    //vec3 diffuse = light.diffuse * diff;
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoord));
    //vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuseMap, TexCoord));
    vec3 specular = light.specular * spec * material.Ks;
    return (diffuse + specular);
}