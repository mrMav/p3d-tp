#include "Material.h"


Material::Material(std::string diffuse_filename)
{

	// material constructor

	// creates the sahder used by this material
	// more advance applications would require
	// a more robust implementation
	// this one will work just fine.
	shader = new Shader("EffectVertex.vert", "Texture.frag");

	// load the diffuse map
	m_diffuseMap = new Texture2D(diffuse_filename.c_str());

	// set some light behaviour data
	Ka = glm::vec3(0.5f);
	Kd = glm::vec3(1.0f);
	Ks = glm::vec3(1.0f);
	Ns = 32.0f;

}


Material::~Material()
{

	free(shader);
	free(m_diffuseMap);

}

// activate the material means to send the data to the shader
void Material::Activate(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, float deltaTime) {

	shader->use();
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	shader->setInt("material.diffuseMap", 0);

	glActiveTexture(GL_TEXTURE0);
	m_diffuseMap->bind();  // bind the texture to the desired channel

	shader->setVec3("material.Ka", Ka);
	shader->setVec3("material.Kd", Kd);
	shader->setVec3("material.Ks", Ks);
	shader->setFloat("material.Ns", Ns);


}