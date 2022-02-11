#include "register_types.h"

#include "buildings/BaseBuilding.h"
#include "camera/RtsCameraController.h"

#include "units/BaseUnit.h"

#include "core/object/class_db.h"
#include "editor/editor_plugin.h"
#include "orders/MoveOrder.h"
#include "orders/UnitOrderManager.h"
#include "units/managers/SelectionSquareManager.h"
#include "units/managers/UnitSelectionManager.h"

void register_ground_war_types() {
	GDREGISTER_CLASS(BaseUnit);
	GDREGISTER_CLASS(BaseBuilding);


	GDREGISTER_CLASS(UnitSelectionManager);
	GDREGISTER_CLASS(SelectionSquareManager);
	GDREGISTER_CLASS(UnitController);

	GDREGISTER_CLASS(RtsCameraController);
	GDREGISTER_CLASS(UnitOrderManager);

	GDREGISTER_VIRTUAL_CLASS(Order);
	GDREGISTER_CLASS(MoveOrder);
}

void unregister_ground_war_types() {
}
