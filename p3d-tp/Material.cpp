#include "Material.h"


Material::Material(std::string diffuse_filename)
{

	shader = new Shader("Texture.vert", "Texture.frag");

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

	shader->setVec3("mat.Ka", Ka);
	shader->setVec3("mat.Kd", Kd);
	shader->setVec3("mat.Ks", Ks);
	shader->setFloat("mat.Ns", Ns);


}