#include "register_types.h"

#include "camera/CameraController.h"
#include "testing/compute/ComputeTest.h"
#include "testing/proc_gen/Planet.h"
#include "testing/proc_gen/ColorSettings.h"
#include "testing/proc_gen/ShapeSettings.h"

#include "units/BaseUnit.h"

#include "core/object/class_db.h"
#include "editor/editor_plugin.h"
#include "orders/UnitOrderManager.h"
#include "units/SelectionSquareManager.h"
#include "units/UnitSelectionManager.h"

void register_ground_war_types() {
	GDREGISTER_CLASS(Planet);
	GDREGISTER_CLASS(ShapeSettings);
	GDREGISTER_CLASS(ColorSettings);
	GDREGISTER_CLASS(ComputeTest);
	GDREGISTER_CLASS(BaseUnit);
	GDREGISTER_CLASS(UnitSelectionManager);
	GDREGISTER_CLASS(SelectionSquareManager);
	GDREGISTER_CLASS(CameraController);
	GDREGISTER_CLASS(UnitOrderManager);

}

void unregister_ground_war_types() {
}
