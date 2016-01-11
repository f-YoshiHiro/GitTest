#include "mesh.h"

#pragma region Mesh
void myMesh::Reset() {
	Cleanup();
	Init();
}

void myMesh::Cleanup() {
}
#pragma endregion

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#pragma region ObjMesh
bool myObjMesh::Init() {
	return true;
}

void myObjMesh::read_from_file(std::string filename) {
	
	std::cout << "reading Obj file by libigl..." << std::endl;

	igl::readOBJ(filename, m_V, m_F);

}
#pragma endregion