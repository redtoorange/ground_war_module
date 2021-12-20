#ifndef TERRAIN_FACE_H
#define TERRAIN_FACE_H

#include "ShapeGenerator.h"
#include "core/math/vector3.h"
#include "scene/3d/mesh_instance_3d.h"

class TerrainFace {

public:
	TerrainFace(int p_resolution, const Vector3 &p_localUp):
		resolution(p_resolution),
		localUp(p_localUp) {

		axisA = Vector3(localUp.y, localUp.z, localUp.x);
		axisB = localUp.cross(axisA);
	}

	void ConstructMesh(ShapeGenerator p_shapeGenerator, MeshInstance3D *p_meshInstance);

private:
	Vector3 localUp;
	Vector3 axisA;
	Vector3 axisB;
	int resolution = 0;
};

#endif
