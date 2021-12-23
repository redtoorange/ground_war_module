#include "register_types.h"

#include "testing/compute/ComputeTest.h"
#include "testing/proc_gen/Planet.h"
#include "testing/proc_gen/ColorSettings.h"
#include "testing/proc_gen/ShapeSettings.h"

#include "units/BaseUnit.h"

#include "core/object/class_db.h"
#include "editor/editor_plugin.h"

void register_ground_war_types() {
	GDREGISTER_CLASS(Planet);
	GDREGISTER_CLASS(ShapeSettings);
	GDREGISTER_CLASS(ColorSettings);
	GDREGISTER_CLASS(ComputeTest);
	GDREGISTER_CLASS(BaseUnit);
}

void unregister_ground_war_types() {
}
