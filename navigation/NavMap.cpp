#include "NavMap.h"

void NavMap::PopulateGraph(int32_t p_width, int32_t p_height) {
	for (int32_t x = 0; x < p_width; x++) {
		std::vector<NavMapCell> cells;
		for (int32_t y = 0; y < p_height; y++) {
			cells.emplace_back(x, y);
		}
		mapCells.push_back(cells);
	}
}

NavMap::NavMap(int32_t p_width, int32_t p_height) :
	width(p_width),
	height(p_height) {

	PopulateGraph(p_width, p_height);
}

NavMapCell *NavMap::GetMapCell(int32_t p_x, int32_t p_y) {
	if (p_x >= 0 && p_x < width && p_y >= 0 && p_y < height) {
		return &mapCells[p_x][p_y];
	}

	return nullptr;
}

bool NavMap::SetMapCell(int32_t p_x, int32_t p_y, const NavMapCell &p_cell) {
	bool success = false;

	if (p_x >= 0 && p_x < width && p_y >= 0 && p_y < height) {
		mapCells[p_x][p_y] = p_cell;
		success = true;
	}

	return success;
}
