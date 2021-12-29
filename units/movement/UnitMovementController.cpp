#include "UnitMovementController.h"

void UnitMovementController::_bind_methods() {
	ADD_GROUP("Paths", "path_");
	ClassDB::bind_method(D_METHOD("SetUnitSelectionManagerPath", "unit_selection_manager_path"), &UnitMovementController::SetUnitSelectionManagerPath);
	ClassDB::bind_method(D_METHOD("GetUnitSelectionManagerPath"), &UnitMovementController::GetUnitSelectionManagerPath);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "path_unit_selection_manager", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "UnitSelectionManager"), "SetUnitSelectionManagerPath", "GetUnitSelectionManagerPath");
}

void UnitMovementController::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
		return;

	if (p_what == NOTIFICATION_READY) {
		_ready();
	}
}

void UnitMovementController::_ready() {
	unitSelectionManager = cast_to<UnitSelectionManager>(get_node(unitSelectionManagerPath));
}
