#ifndef TERRAIN_FACE_H
#define TERRAIN_FACE_H

#include "core/object/ref_counted.h"
#include "core/math/vector3.h"
#include "scene/3d/mesh_instance_3d.h"

class TerrainFace : public RefCounted {
	GDCLASS(TerrainFace, RefCounted);

public:
	void constructMesh();
	void initializeData(Node *p_meshInstance, int p_resolution, const Vector3 &p_localUp);

protected:
	static void _bind_methods();

private:
	Vector3 localUp;
	Vector3 axisA;
	Vector3 axisB;
	int resolution = 0;

	MeshInstance3D *meshInstance = nullptr;
	Ref<ArrayMesh> localMesh;

};

#endif
