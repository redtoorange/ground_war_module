#include "Planet.h"

Planet::Planet() {
	set_process_internal(true);
	_createMeshInstances();
}

void Planet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setResolution", "resolution"), &Planet::setResolution);
	ClassDB::bind_method(D_METHOD("getResolution"), &Planet::getResolution);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Resolution"), "setResolution", "getResolution");
}

void Planet::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_INTERNAL_PROCESS:
			if(Engine::get_singleton()->is_editor_hint()) {
				_process();
			}
			break;
		case NOTIFICATION_ENTER_TREE:
			break;
		default:
			break;
	}
}

void Planet::_process() {
	if (!is_inside_tree()) {
		return;
	}

	if (isMeshDirty) {
		print_line("Mesh Dirty");

		isMeshDirty = false;

		// _createMeshInstances();
		_createTerrainFaces();
		_generateMesh();
		print_line("Done!");
	}
}

void Planet::_initialize() {
	print_line("Initializing");
	isInitialized = true;
}

void Planet::_createMeshInstances() {
	print_line("Making Mesh Instances");
	meshInstances.clear();

	for (int i = 0; i < 6; i++) {
		MeshInstance3D *instance = memnew(MeshInstance3D);
		instance->set_name(String("Mesh_Instance_") + itos(i));
		this->add_child(instance);
		instance->set_owner(this);
		meshInstances.append(instance);
		print_line("Added Mesh Instance");
	}
	print_tree_pretty();
}

void Planet::_createTerrainFaces() {
	print_line("Making Terrain Faces");
	terrainFaces.clear();

	for (int i = 0; i < 6; i++) {
		Ref<TerrainFace> terrainFace;
		terrainFace.instantiate();
		terrainFace->initializeData(meshInstances.get(i), resolution, directions[i]);
		terrainFaces.append(terrainFace);
	}
}

void Planet::_generateMesh() {
	print_line("Constructing Face Meshs");
	for (int i = 0; i < 6; i++) {
		terrainFaces.get(i)->constructMesh();
	}
}

void Planet::setResolution(int p_resolution) {
	resolution = p_resolution;
	isMeshDirty = true;
}

int Planet::getResolution() const {
	return resolution;
}
