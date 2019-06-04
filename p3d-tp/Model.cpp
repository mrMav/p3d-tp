#include "Model.h"

Model::Model()
{

	model = glm::mat4(1.0f);

}

Model::~Model()
{



}

void Model::Draw(glm::mat4 &view, glm::mat4 &projection, float deltatime) {

	int size = meshes.size();
	for (int i = 0; i < size; i++) {

		meshes[i]->Draw(view, projection, deltatime);

	}

}
