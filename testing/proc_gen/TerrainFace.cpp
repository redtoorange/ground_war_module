#include "TerrainFace.h"

#include "scene/resources/surface_tool.h"

void TerrainFace::ConstructMesh(ShapeGenerator p_shapeGenerator, MeshInstance3D *p_meshInstance) {
	Vector<Vector3> vertices;
	Vector<int> triangles;

	for (int y = 0; y < resolution; y++) {
		for (int x = 0; x < resolution; x++) {
			const Vector2 percent = Vector2(x, y) / (resolution - 1);
			Vector3 pointOnUnitCube = localUp + (percent.x - 0.5f) * 2 * axisA + (percent.y - 0.5f) * 2 * axisB;
			Vector3 pointOnUnitSphere = pointOnUnitCube.normalized();
			vertices.append(p_shapeGenerator.calculatePointOnPlanet(pointOnUnitSphere));

			if (x != resolution - 1 && y != resolution - 1) {
				int i = x + y * resolution;
				triangles.append(i);
				triangles.append(i + resolution);
				triangles.append(i + resolution + 1);

				triangles.append(i);
				triangles.append(i + resolution + 1);
				triangles.append(i + 1);
			}
		}
	}

	// Generate Mesh with Surface Tool
	Ref<SurfaceTool> surfaceTool;
	surfaceTool.instantiate();
	surfaceTool->begin(Mesh::PRIMITIVE_TRIANGLES);
	for (int v = 0; v < vertices.size(); v++) {
		surfaceTool->add_vertex(vertices[v]);
	}
	for (int t = 0; t < triangles.size(); t++) {
		surfaceTool->add_index(triangles[t]);
	}
	surfaceTool->generate_normals();

	p_meshInstance->set_mesh(surfaceTool->commit());
}
