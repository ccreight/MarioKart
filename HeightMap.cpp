#include "HeightMap.h"
#include <fstream>
#include "CSVHelper.h"
#include <iostream>

void HeightMap::LoadCSV(const std::string& fileName) {

	std::string line = "";
	std::ifstream myfile(fileName);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			if (line == "") {
				continue;
			}

			std::vector<std::string> nums = CSVHelper::Split(line);
			std::vector<float> insertions;

			for (unsigned int i = 0; i < nums.size(); i++) {

				insertions.push_back(stof(nums[i]));

			}

			mValues.push_back(insertions);

		}
		myfile.close();
	}

}

bool HeightMap::isCellOnTrack(int row, int col) {

	if ((size_t)row < 0 || (size_t)row >= mValues.size() || (size_t)col < 0 || (size_t)col >= mValues[0].size()) {
		return false;
	}

	if (mValues[row][col] != -1) {
		return true;
	}

	return false;

}

float HeightMap::GetHeightFromCell(int row, int col) {

	return mValues[row][col] * 5.0f - 40.0f;

}

Vector3 HeightMap::CellToWorld(int row, int col) {

	if (mValues[row][col] == -1) {
		return Vector3::Zero;
	}

	Vector3 pos = Vector3(0, 0, 0);
	pos.x = GRID_TOP - CELL_SIZE * row;
	pos.y = GRID_LEFT + CELL_SIZE * col;
	pos.z = GetHeightFromCell(row, col);

	return pos;

}

std::pair<int, int> HeightMap::WorldToCell(float row, float col) {

	std::pair<int, int> coords = std::pair<int, int>(0, 0);

	float val = row - GRID_TOP;
	coords.first = (int)((abs(val) + CELL_SIZE / 2.0f) / CELL_SIZE);

	val = col - GRID_LEFT;
	coords.second = (int)((abs(val) + CELL_SIZE / 2.0f) / CELL_SIZE);

	return coords;

}

bool HeightMap::isOnTrack(float row, float col) {

	std::pair<int, int> coords = WorldToCell(row, col);
	return isCellOnTrack(coords.first, coords.second);

}

float HeightMap::GetHeight(float row, float col) {

	if (!isOnTrack(row, col)) {
		return -1000.0f;
	}

	std::pair<int, int> coords = WorldToCell(row, col);
	return GetHeightFromCell(coords.first, coords.second);

}
