#ifndef PLANET_H
#define PLANET_H

#include "TerrainFace.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/3d/node_3d.h"

class Planet : public Node3D {
	GDCLASS(Planet, Node3D);

public:
	Planet();

	void setResolution(int p_resolution);
	int getResolution() const;

protected:
	static void _bind_methods();

	void _notification(int p_what);

private:
	int resolution = 10;
	bool isMeshDirty = true;
	bool isInitialized = false;
	bool inTree = false;


	void _initialize();
	void _createMeshInstances();
	void _createTerrainFaces();
	void _process();
	void _generateMesh();

	Vector<MeshInstance3D *> meshInstances;
	Vector<Ref<TerrainFace>> terrainFaces;

	Vector3 directions[6] = {
		{ 0, 1, 0 },
		{ 0, -1, 0 },
		{ -1, 0, 0 },
		{ 1, 0, 0 },
		{ 0, 0, -1 },
		{ 0, 0, 1 }
	};
};

#endif
