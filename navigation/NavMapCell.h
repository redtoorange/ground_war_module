#pragma once

#include <cstdint>

struct NavMapCell {
	NavMapCell(int32_t p_graphX, int32_t p_graphY) :
		graph_x(p_graphX),
		graph_y(p_graphY) {
	}

	int32_t graph_x;
	int32_t graph_y;
};

