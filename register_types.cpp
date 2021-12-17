#include "register_types.h"

#include "core/object/class_db.h"
#include "editor/editor_plugin.h"
#include "proc_gen/Planet.h"
#include "proc_gen/ColorSettings.h"
#include "proc_gen/ShapeSettings.h"
#include "proc_gen/TerrainFace.h"

void register_ground_war_types() {
	GDREGISTER_CLASS(Planet);
	GDREGISTER_CLASS(TerrainFace);
	GDREGISTER_CLASS(ShapeSettings);
	GDREGISTER_CLASS(ColorSettings);
}

void unregister_ground_war_types() {
}
