#include "UnitSelectionManager.h"
#include "SelectionSquareManager.h"

void UnitSelectionManager::_ready() {
	unitController = cast_to<UnitController>(get_node(unitControllerPath));
	selectionSquareManager = cast_to<SelectionSquareManager>(get_node(selectionSquareManagerPath));

	selectionSquareManager->connect("selection_completed", callable_mp(this, &UnitSelectionManager::SelectUnits));
}

void UnitSelectionManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("SetSelectionSquareManagerPath", "selection_square_path"), &UnitSelectionManager::SetSelectionSquareManagerPath);
	ClassDB::bind_method(D_METHOD("GetSelectionSquareManagerPath"), &UnitSelectionManager::GetSelectionSquareManagerPath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_selection_square"), "SetSelectionSquareManagerPath", "GetSelectionSquareManagerPath");

	ClassDB::bind_method(D_METHOD("SetUnitControllerPath", "unit_controller_path"), &UnitSelectionManager::SetUnitControllerPath);
	ClassDB::bind_method(D_METHOD("GetUnitControllerPath"), &UnitSelectionManager::GetUnitControllerPath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_unit_controller"), "SetUnitControllerPath", "GetUnitControllerPath");
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

	selectedUnits = unitController->GetUnitsInArea(selectionArea);
}
