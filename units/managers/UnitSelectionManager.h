#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "SelectionSquareManager.h"
#include "modules/ground_war/units/BaseUnit.h"
#include "modules/ground_war/units/UnitController.h"
#include "scene/2d/node_2d.h"

class UnitSelectionManager : public Node2D {
	GDCLASS(UnitSelectionManager, Node2D);

public:
	void SelectUnits(const Rect2 &selectionArea);

	void DeselectAll();

	Vector<BaseUnit *> GetSelectedUnits() { return selectedUnits; }

	void SetUnitControllerPath(const NodePath &p_path) { unitControllerPath = p_path; }
	NodePath GetUnitControllerPath() const { return unitControllerPath; }

	void SetSelectionSquareManagerPath(const NodePath &p_path) { selectionSquareManagerPath = p_path; }
	NodePath GetSelectionSquareManagerPath() const { return selectionSquareManagerPath; }

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _ready();

private:
	NodePath selectionSquareManagerPath;
	SelectionSquareManager *selectionSquareManager;

	NodePath unitControllerPath;
	UnitController *unitController;

	Vector<BaseUnit *> selectedUnits;
};

#endif
