#ifndef COLOR_SETTINGS_H
#define COLOR_SETTINGS_H

#include "core/io/resource.h"

class ColorSettings : public Resource {
	GDCLASS(ColorSettings, Resource);

public:
	void setPlanetColor(const Color &p_planetColor);
	Color getPlanetColor() const;

protected:
	static void _bind_methods();

private:
	Color planetColor;
};

#endif
