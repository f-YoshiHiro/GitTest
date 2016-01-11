#include "mesh.h"

#pragma region Mesh
void Mesh::Reset() {
	Cleanup();
	Init();
}

void Mesh::Cleanup() {
}
#pragma endregion

#pragma region ObjMesh
bool ObjMesh::Init() {
	return true;
}

void ObjMesh::read_from_file(char* filename) {

	std::vector <glm::vec3> positions;	positions.clear();
	std::vector <glm::vec3> normals;		normals.clear();
	std::vector <int> indices;				indices.clear();

	glm::vec3 mat_color(0.6);
	// vertices and color

	std::ifstream infile(filename);
	if (!infile.good())
	{
		printf("Error in loading file %s\n", filename);
		exit(0);
	}
	char buffer[256];
	unsigned int ip0, ip1, ip2;
	unsigned int n0, n1, n2;
	glm::vec3 pos;

	while (!infile.getline(buffer, 255).eof())
	{
		buffer[255] = '\0';
		if (buffer[0] == 'v' && (buffer[1] == ' ' || buffer[1] == 32))
		{
			if (sscanf_s(buffer, "v %f %f %f", &pos.x, &pos.y, &pos.z) == 3)
			{
				pos = m_scaling * pos;
				positions.push_back(pos);
			}
			else
			{
				printf("Vertex is not in desired format.\n");
				exit(0);
			}
		}
		else if (buffer[0] == 'v' && buffer[1] == 'n' && (buffer[2] == ' ' || buffer[2] == 32))
		{
			// load normals from obj file.
		}
		else if (buffer[0] == 'f' && (buffer[1] == ' ' || buffer[1] == 32))
		{
			if (sscanf_s(buffer, "f %u %u %u", &ip0, &ip1, &ip2) == 3)
			{
				indices.push_back(--ip0);
				indices.push_back(--ip1);
				indices.push_back(--ip2);
			}
			else if (sscanf_s(buffer, "f %u//%u %u//%u %u//%u", &ip0, &n0, &ip1, &n1, &ip2, &n2) == 6)
			{
				indices.push_back(--ip0);
				indices.push_back(--ip1);
				indices.push_back(--ip2);
			}
			else if (sscanf_s(buffer, "f %u/%u %u/%u %u/%u", &ip0, &n0, &ip1, &n1, &ip2, &n2) == 6)
			{
				indices.push_back(--ip0);
				indices.push_back(--ip1);
				indices.push_back(--ip2);
			}
			else
			{
				printf("Triangle indices is not in desired format.\n");
				exit(0);
			}
		}
	}
	// normals

	unsigned int id, size;
	bool vert_norm = (normals.size() != positions.size());
	if (vert_norm)
		normals.resize(positions.size(), glm::vec3(0.0f));

	size = indices.size();
	glm::uvec3 triangle;
	glm::vec3 p0, p1, p2;
	glm::vec3 norm;
	float phi0, phi1, phi2;
	float pi = glm::radians(180.0f);
	for (id = 0; id < size; id += 3)
	{
		triangle = glm::uvec3(indices[id], indices[id + 1], indices[id + 2]);
		p0 = positions[triangle.x];
		p1 = positions[triangle.y];
		p2 = positions[triangle.z];
		norm = glm::normalize(glm::cross(p1 - p0, p2 - p0));
		// calculate vertex normal
		if (vert_norm)
		{
			phi0 = std::acos(glm::dot(p1 - p0, p2 - p0) / (glm::length(p1 - p0) * glm::length(p2 - p0)));
			phi1 = std::acos(glm::dot(p0 - p1, p2 - p1) / (glm::length(p0 - p1) * glm::length(p2 - p1)));
			phi2 = pi - phi0 - phi1;

			normals[triangle.x] += phi0 * norm;
			normals[triangle.y] += phi1 * norm;
			normals[triangle.z] += phi2 * norm;
		}
	}
	// re-normalize all normals
	for (std::vector<glm::vec3>::iterator iter = normals.begin(); iter != normals.end(); ++iter)
	{
		*iter = glm::normalize(*iter);
		//m_colors.push_back(mat_color);
		//m_colors.push_back(*iter);
	}

	// convert to mat --------------------------
	m_V.resize(positions.size(), 3);
	m_N.resize(normals.size(), 3);
	m_F.resize((int)(indices.size() / 3.0), 3);

	for (int i = 0; i < m_V.rows(); ++i)
	{
		EigenVector3 EigenPos  = EigenVector3(positions[i][0], positions[i][1], positions[i][2]);
		EigenVector3 EigenNorm = EigenVector3(normals[i][0], normals[i][1], normals[i][2]);

		m_V.row(i) = EigenPos.transpose();
		m_N.row(i) = EigenNorm.transpose();
	}

	for (int i = 0; i < (int)(indices.size() / 3.0); ++i)
	{
		m_F(i, 0) = indices[3*i + 0];
		m_F(i, 1) = indices[3*i + 1];
		m_F(i, 2) = indices[3*i + 2];
	}

}
#pragma endregion