#pragma once

#include "NavMapCell.h"
#include <vector>

class NavMap {
public:
	typedef std::vector<std::vector<NavMapCell>> Graph;

	NavMap(int32_t p_width, int32_t p_height);

	NavMapCell *GetMapCell(int32_t p_x, int32_t p_y);

	bool SetMapCell(int32_t p_x, int32_t p_y, const NavMapCell &p_cell);

private:
	void PopulateGraph(int32_t p_width, int32_t p_height);

	int32_t width;
	int32_t height;

	Graph mapCells;
};
