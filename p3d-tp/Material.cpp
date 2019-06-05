#include "Material.h"


Material::Material(std::string diffuse_filename)
{

	shader = new Shader("EffectVertex.vert", "Texture.frag");

	m_diffuseMap = new Texture2D(diffuse_filename.c_str());

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

void Material::Activate(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, float deltaTime) {

	shader->use();
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	shader->setInt("material.diffuseMap", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_diffuseMap->textureID);

	shader->setVec3("material.Ka", Ka);
	shader->setVec3("material.Kd", Kd);
	shader->setVec3("material.Ks", Ks);
	shader->setFloat("material.Ns", Ns);


}