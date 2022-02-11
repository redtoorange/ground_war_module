#pragma once

#include "scene/3d/node_3d.h"

class UnitSelectionManager;

class UnitMovementController : public Node3D {
	GDCLASS(UnitMovementController, Node3D);

public:
	void SetUnitSelectionManagerPath(const NodePath &p_unitSelectionManagerPath) { unitSelectionManagerPath = p_unitSelectionManagerPath; }
	NodePath GetUnitSelectionManagerPath() const { return unitSelectionManagerPath; }

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _ready();

private:
	NodePath unitSelectionManagerPath;
	UnitSelectionManager *unitSelectionManager;
};

