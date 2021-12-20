#ifndef PLANET_H
#define PLANET_H

#include "ColorSettings.h"
#include "ShapeGenerator.h"
#include "ShapeSettings.h"
#include "TerrainFace.h"
#include "scene/3d/mesh_instance_3d.h"
#include "scene/3d/node_3d.h"

#include <vector>

class Planet : public Node3D {
	GDCLASS(Planet, Node3D);

public:
	Planet();

	void GeneratePlanet();

	// void onShapeSettingsChanged();
	//
	// void onColorSettingsChanged();

	void SetResolution(int p_resolution);
	int GetResolution() const { return resolution; }

	void SetPlanetMaterial(Ref<Material> p_material);
	Ref<Material> GetPlanetMaterial() const { return planetMaterial; }

	void SetColorSettings(Ref<ColorSettings> p_colorSettings);
	Ref<ColorSettings> GetColorSettings() const { return colorSettings; }

	void SetShapeSettings(Ref<ShapeSettings> p_shapeSettings);
	Ref<ShapeSettings> GetShapeSettings() const { return shapeSettings; }

	bool GetIsMeshDirty() const;
	void SetIsMeshDirty(bool p_isMeshDirty);
protected:
	static void _bind_methods();

	void _notification(int p_what);

private:
	Ref<Material> planetMaterial;

	int resolution = 10;
	bool isMeshDirty = false;

	void CreateOrPopulateMeshInstances();
	void CreateTerrainFaces();
	void GenerateMesh();
	void GenerateColors();

	void _process(float delta);
	void _ready();

	Vector<MeshInstance3D *> meshInstances;
	std::vector<TerrainFace> terrainFaces;

	Ref<ShapeSettings> shapeSettings;
	Ref<ColorSettings> colorSettings;
};

#endif
