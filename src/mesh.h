#pragma once

#include "iostream"
#include "math_headers.h"
#include <igl/read_triangle_mesh.h>

typedef enum{
	MESH_TYPE_OBJ,
	MESH_TYPE_TOTAL_NUM
} MeshType;

class myMesh{
	public:
		myMesh() : m_mesh_type() {}
		myMesh(MeshType mesh_type) : m_mesh_type(mesh_type) {}
		virtual ~myMesh() { Cleanup(); }

		void Reset();
		virtual bool Init() { std::cout << "Warning: reach base class virtual init function." << std::endl; return false; }
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

		virtual void read_from_file(std::string filename) { std::cout << "Warning: reach base class virtual init function." << std::endl; };

};

class myObjMesh : public myMesh {
	public:
		myObjMesh() : myMesh(MESH_TYPE_OBJ) {}
		virtual ~myObjMesh() {}

		virtual bool Init();
	
	protected:
		float m_scaling;

	public:
		virtual void read_from_file(std::string filename);
};