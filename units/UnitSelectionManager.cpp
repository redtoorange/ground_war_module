#include "UnitSelectionManager.h"

void UnitSelectionManager::_ready() {
	for (int c = 0; c < get_child_count(); c++) {
		BaseUnit *unit = cast_to<BaseUnit>(get_child(c));
		if (unit) {
			allUnits.append(unit);
		}
	}
}

void UnitSelectionManager::_bind_methods() {
}

void UnitSelectionManager::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	}
}

void UnitSelectionManager::DeselectAll() {
	for (BaseUnit *selected : selectedUnits) {
		selected->Deselect();
	}

	selectedUnits.clear();
}

void UnitSelectionManager::SelectUnits(const Rect2 &selectionArea) {
	DeselectAll();

	for (int c = 0; c < allUnits.size(); c++) {
		BaseUnit *child = allUnits[c];
		if (selectionArea.has_point(child->get_position())) {
			selectedUnits.append(child);
			child->Select();
		}
	}
}


void UnitSelectionManager::AddUnit(BaseUnit *newUnit) {
	// Ensure the unit is not already present
	if (allUnits.find(newUnit) == -1) {
		allUnits.append(newUnit);
	}
	else {
		print_error("Unit already present, cannot add.");
	}
}

void UnitSelectionManager::RemoveUnit(BaseUnit *unit) {
	allUnits.erase(unit);

	// Remove from selected units also
	if(selectedUnits.size() > 0) {
		selectedUnits.erase(unit);
	}
}

// --------------------------- Getters / Setters -------------------------------------------------
