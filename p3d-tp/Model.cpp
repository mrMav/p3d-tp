#include "Model.h"

#define OBJL_CONSOLE_OUTPUT
#include "OBJ_Loader.h"

Model::Model(std::string directory, std::string filename)
{
	
	m_directory = directory;
	m_filename = filename;
	
	/* load 3d model */
	objl::Loader loader;
	
	// use the library to load the obj model
	// we will need to then, build the model with
	// our own structure
	bool sucess = loader.LoadFile((m_directory + "\\" + m_filename).c_str());
	
	if (sucess) {

		// if sucess, we can now build our own meshes
		// lets build the meshes
		for (int i = 0; i < loader.LoadedMeshes.size(); i++) {

			std::vector<VertexPositionNormalTexture> vertices;
			std::vector<unsigned int> indices;

			// create an array of our own vertexPositionNormalTexture
			for (int j = 0; j < loader.LoadedMeshes[i].Vertices.size(); j++) {

				objl::Vertex _v = loader.LoadedMeshes[i].Vertices[j];

				VertexPositionNormalTexture v{
					glm::vec3(_v.Position.X, _v.Position.Y, _v.Position.Z),
					glm::vec3(_v.Normal.X, _v.Normal.Y, _v.Normal.Z),
					glm::vec2(_v.TextureCoordinate.X , _v.TextureCoordinate.Y)
				};

				vertices.push_back(v);

			}

			// we will now build an indices vector.
			// the loaded indices are built in CCW
			// but we are using CW winding in this application
			for (int k = loader.LoadedMeshes[i].Indices.size() - 1; k >= 0; k--) {

				indices.push_back(loader.LoadedMeshes[i].Indices[k]);

			}

			// the mesh
			Mesh* m = new Mesh(vertices, indices);
			m->model = glm::scale(m->model, glm::vec3(0.5f)); // scale it 

			// the loaded material
			objl::Material lm = loader.LoadedMeshes[i].MeshMaterial;

			// our new material for this mesh
			Material* mat = new Material((m_directory + "\\" + lm.map_Kd).c_str());

			mat->SetName(lm.name);

			mat->Ka = glm::vec3(lm.Ka.X, lm.Ka.Y, lm.Ka.Z);
			mat->Kd = glm::vec3(lm.Kd.X, lm.Kd.Y, lm.Kd.Z);
			mat->Ks = glm::vec3(lm.Ks.X, lm.Ks.Y, lm.Ks.Z);

			mat->Ns = lm.Ns;

			m->material = mat;

			meshes.push_back(m);  // push to the mesh list
		}

	}
	else {

		printf("Loading model error: $s\n", m_filename.c_str());

	}

}

Model::~Model()
{



}

void Model::Draw(glm::mat4 &view, glm::mat4 &projection, float deltatime) {

	// render all meshes

	int size = meshes.size();
	for (int i = 0; i < size; i++) {

		meshes[i]->Draw(view, projection, deltatime);

	}

}
