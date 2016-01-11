#pragma once

#include "iostream"
#include "math_headers.h"
#include <igl/read_triangle_mesh.h>

typedef enum{
	MESH_TYPE_OBJ,
	MESH_TYPE_TOTAL_NUM
} MeshType;

class Mesh{
	public:
		Mesh() : m_mesh_type() {}
		Mesh(MeshType mesh_type) : m_mesh_type(mesh_type) {}
		virtual ~Mesh() { Cleanup(); }

		void Reset();
		virtual bool Init() { std::cout << "Warning: reach base class virtual init function." << std::endl; }
		virtual void Cleanup();

	protected:
		MeshType m_mesh_type;

		EigenMatrixXs m_V0;	// rest pose
		EigenMatrixXs m_V;	// current pose
		EigenMatrixXs m_N;	// current normal
		EigenMatrixXi m_F;  // tri index
		EigenMatrixXi m_T;  // tet index

	public:	// get method
		int GetVertNum() const { return (int)m_V.rows(); }
		int GetTriNum()  const { return (int)m_F.rows(); }
		int GetTetNum()  const { return (int)m_T.rows(); }

};

class ObjMesh : public Mesh {
	public:
		ObjMesh() : Mesh(MESH_TYPE_OBJ) {}
		virtual ~ObjMesh() {}

		virtual bool Init();
	
	protected:
		float m_scaling;

	public:
		void read_from_file(char* filename);
};