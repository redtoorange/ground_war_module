#include "Planet.h"

#include "thirdparty/xatlas/xatlas.h"

Planet::Planet() {
	set_process(true);
}

void Planet::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetIsMeshDirty", "is_dirty"), &Planet::SetIsMeshDirty);
	ClassDB::bind_method(D_METHOD("GetIsMeshDirty"), &Planet::GetIsMeshDirty);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "mesh_is_dirty"), "SetIsMeshDirty", "GetIsMeshDirty");

	ClassDB::bind_method(D_METHOD("setResolution", "resolution"), &Planet::SetResolution);
	ClassDB::bind_method(D_METHOD("getResolution"), &Planet::GetResolution);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Resolution"), "setResolution", "getResolution");

	ClassDB::bind_method(D_METHOD("setPlanetMaterial", "plant_material"), &Planet::SetPlanetMaterial);
	ClassDB::bind_method(D_METHOD("getPlanetMaterial"), &Planet::GetPlanetMaterial);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Material", PROPERTY_HINT_RESOURCE_TYPE, "Material"), "setPlanetMaterial", "getPlanetMaterial");

	ADD_GROUP("Settings", "settings_");

	ClassDB::bind_method(D_METHOD("setColorSettings", "color_settings"), &Planet::SetColorSettings);
	ClassDB::bind_method(D_METHOD("getColorSettings"), &Planet::GetColorSettings);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "settings_color", PROPERTY_HINT_RESOURCE_TYPE, "ColorSettings"), "setColorSettings", "getColorSettings");

	ClassDB::bind_method(D_METHOD("setShapeSettings", "shape_settings"), &Planet::SetShapeSettings);
	ClassDB::bind_method(D_METHOD("getShapeSettings"), &Planet::GetShapeSettings);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "settings_shape", PROPERTY_HINT_RESOURCE_TYPE, "ShapeSettings"), "setShapeSettings", "getShapeSettings");
}

void Planet::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE:
			if (Engine::get_singleton()->is_editor_hint()) {
				CreateOrPopulateMeshInstances();
			}
			GeneratePlanet();
			break;
		case NOTIFICATION_PROCESS:
			_process(get_process_delta_time());
			break;
		case NOTIFICATION_READY:
			_ready();
		default:
			break;
	}
}


void Planet::_ready() {
	GeneratePlanet();
}

void Planet::_process(float delta) {
	if (isMeshDirty) {
		isMeshDirty = false;
		GeneratePlanet();
	}
}

void Planet::GeneratePlanet() {
	CreateTerrainFaces();
	GenerateMesh();
	GenerateColors();
}

void Planet::CreateOrPopulateMeshInstances() {
	if (get_child_count() > 0) {
		for (int c = 0; c < get_child_count(); c++) {
			MeshInstance3D *child = cast_to<MeshInstance3D>(get_child(c));
			if (child) {
				meshInstances.append(child);
			}
		}
	}

	if (meshInstances.size() == 0) {
		for (int i = 0; i < 6; i++) {
			MeshInstance3D *instance = memnew(MeshInstance3D);
			instance->set_name(String("Mesh_Instance_") + itos(meshInstances.size()));
			if (planetMaterial.is_valid()) {
				instance->set_material_override(planetMaterial);
			}
			this->add_child(instance);
			instance->set_owner(get_tree()->get_edited_scene_root());
			meshInstances.append(instance);
			print_line("Added Mesh Instance");
		}
	}
}


Vector<Vector3> GetDirections() {
	Vector<Vector3> directions;

	directions.append({ 1, 0, 0 });
	directions.append({ -1, 0, 0 });
	directions.append({ 0, 1, 0 });
	directions.append({ 0, -1, 0 });
	directions.append({ 0, 0, 1 });
	directions.append({ 0, 0, -1 });

	return directions;
}

void Planet::CreateTerrainFaces() {
	const Vector<Vector3> directions = GetDirections();
	terrainFaces.clear();

	for (int i = 0; i < directions.size(); i++) {
		terrainFaces.emplace_back(resolution, directions[i]);
	}
}

void Planet::GenerateMesh() {
	for (int i = 0; i < meshInstances.size(); i++) {
		terrainFaces[i].ConstructMesh(ShapeGenerator(shapeSettings), meshInstances.get(i));
	}
}

void Planet::GenerateColors() {
	if (planetMaterial.is_valid()) {
		Ref<BaseMaterial3D> mat = planetMaterial;
		if (mat.is_valid()) {
			mat->set_albedo(colorSettings->getPlanetColor());
		}
	}
}

void Planet::SetResolution(int p_resolution) {
	resolution = p_resolution;
}

void Planet::SetPlanetMaterial(Ref<Material> p_material) {
	planetMaterial = p_material;
	for (int i = 0; i < meshInstances.size(); i++) {
		MeshInstance3D *instance = meshInstances.get(i);
		instance->set_material_override(planetMaterial);
	}
}

void Planet::SetColorSettings(Ref<ColorSettings> p_colorSettings) {
	colorSettings = p_colorSettings;
	GenerateColors();
}

void Planet::SetShapeSettings(Ref<ShapeSettings> p_shapeSettings) {
	shapeSettings = p_shapeSettings;
}

bool Planet::GetIsMeshDirty() const {
	return isMeshDirty;
}

void Planet::SetIsMeshDirty(bool p_isMeshDirty) {
	isMeshDirty = p_isMeshDirty;
}
