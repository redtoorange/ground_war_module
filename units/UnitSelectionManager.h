#ifndef UNIT_MANAGER_H
#define UNIT_MANAGER_H

#include "BaseUnit.h"
#include "scene/2d/node_2d.h"

class UnitSelectionManager : public Node2D  {
	GDCLASS(UnitSelectionManager, Node2D);

public:
	void SelectUnits(const Rect2& selectionArea);
	void AddUnit(BaseUnit* newUnit);
	void RemoveUnit(BaseUnit* unit);
	void DeselectAll();

protected:
	static void _bind_methods();
	void _notification(int p_what);
	void _ready();

private:
	Vector<BaseUnit*> allUnits;
	Vector<BaseUnit*> selectedUnits;
};

#endif

