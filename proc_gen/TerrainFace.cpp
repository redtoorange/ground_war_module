#include "TerrainFace.h"

#include "scene/resources/surface_tool.h"

void TerrainFace::_bind_methods() {
	ClassDB::bind_method(D_METHOD("initialize_data", "mesh_instance", "resolution", "local_up"), &TerrainFace::initializeData);
	ClassDB::bind_method(D_METHOD("construct_mesh"), &TerrainFace::constructMesh);
}

void TerrainFace::initializeData(Node *p_meshInstance, int p_resolution, const Vector3 &p_localUp) {
	meshInstance = cast_to<MeshInstance3D>(p_meshInstance);
	resolution = p_resolution;
	localUp = p_localUp;

	axisA = Vector3(localUp.y, localUp.z, localUp.x);
	axisA = localUp.cross(axisA);
}

void TerrainFace::constructMesh() {
	Vector<Vector3> vertices;
	vertices.resize(resolution * resolution);
	Vector<int> triangles;
	triangles.resize((resolution - 1) * (resolution - 1) * 6);
	int triIndex = 0;

	for (int y = 0; y < resolution; y++) {
		for (int x = 0; x < resolution; x++) {
			int i = x + y * resolution;
			const Vector2 percent = Vector2(x, y) / (resolution - 1);
			Vector3 pointOnUnitCube = localUp + (percent.x - 0.5) * 2 * axisA + (percent.y - 0.5) * 2 * axisB;
			Vector3 pointOnUnitSphere = pointOnUnitCube.normalized();
			vertices.set(i, pointOnUnitSphere);

			if (x != resolution - 1 && y != resolution - 1) {
				triangles.set(triIndex + 0, i);
				triangles.set(triIndex + 1, i + resolution);
				triangles.set(triIndex + 2, i + resolution + 1);

				triangles.set(triIndex + 3, i);
				triangles.set(triIndex + 4, i + resolution + 1);
				triangles.set(triIndex + 5, i + 1);

				triIndex += 6;
			}
		}
	}

	SurfaceTool surfaceTool;
	surfaceTool.begin(Mesh::PRIMITIVE_TRIANGLES);

	for (int v = 0; v < vertices.size(); v++) {
		surfaceTool.add_vertex(vertices[v]);
	}
	for (int t = 0; t < triangles.size(); t++) {
		surfaceTool.add_index(triangles[t]);
	}

	surfaceTool.generate_normals();
	localMesh = surfaceTool.commit();
	meshInstance->set_mesh(localMesh);
}
