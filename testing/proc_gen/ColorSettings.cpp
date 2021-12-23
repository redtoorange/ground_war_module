#include "ColorSettings.h"

void ColorSettings::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setPlanetColor", "color"), &ColorSettings::setPlanetColor);
	ClassDB::bind_method(D_METHOD("getPlanetColor"), &ColorSettings::getPlanetColor);
	ADD_PROPERTY(PropertyInfo(Variant::COLOR, "Planet Color"), "setPlanetColor", "getPlanetColor");
}

void ColorSettings::setPlanetColor(const Color &p_planetColor) {
	planetColor = p_planetColor;
}

Color ColorSettings::getPlanetColor() const {
	return planetColor;
}
