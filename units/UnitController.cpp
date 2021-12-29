#include "UnitController.h"

void UnitController::_ready() {
	for (int c = 0; c < get_child_count(); c++) {
		BaseUnit *unit = cast_to<BaseUnit>(get_child(c));
		if (unit) {
			AddUnit(unit);
		}
	}
}

void UnitController::_bind_methods() {
}

void UnitController::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	}
}


void UnitController::AddUnit(BaseUnit *newUnit) {
	if (allUnits.find(newUnit) == -1) {
		allUnits.append(newUnit);
	} else {
		print_error("Unit already present, cannot add.");
	}
}

void UnitController::RemoveUnit(BaseUnit *unit) {
	allUnits.erase(unit);
}

Vector<BaseUnit *> UnitController::GetUnitsInArea(const Rect2 &area) {
	Vector<BaseUnit *> selectedUnits;

	for (int c = 0; c < allUnits.size(); c++) {
		BaseUnit *child = allUnits[c];
		if (area.has_point(child->get_position())) {
			selectedUnits.append(child);
			child->Select();
		}
	}

	return selectedUnits;
}
