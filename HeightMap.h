#pragma once
#include <string>
#include <vector>
#include "Math.h"

class HeightMap {

	public:
		void LoadCSV(const std::string& fileName);
		Vector3 CellToWorld(int row, int col);
		std::pair<int, int> WorldToCell(float row, float col);
		bool isOnTrack(float row, float col);
		float GetHeight(float row, float col);

	private:
		std::vector<std::vector<float>> mValues;
		const float CELL_SIZE = 40.55f;
		const float GRID_TOP = 1280.0f;
		const float GRID_LEFT = -1641.0f;

		bool isCellOnTrack(int row, int col);
		float GetHeightFromCell(int row, int col);
		

};