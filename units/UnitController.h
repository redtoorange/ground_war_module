﻿#pragma once

#include "scene/2d/node_2d.h"
#include "BaseUnit.h"


class UnitController : public Node2D {
	GDCLASS(UnitController, Node2D);

public:
	void AddUnit(BaseUnit *newUnit);

	void RemoveUnit(BaseUnit *unit);

	Vector<BaseUnit *> GetUnitsInArea(const Rect2 &area);

protected:
	static void _bind_methods();

	void _notification(int p_what);

	void _ready();

private:
	Vector<BaseUnit *> allUnits;
};
