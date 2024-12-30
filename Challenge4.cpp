#include "Challenge4.h"

void SolveChallenge4()
{
#ifdef TEST
	std::string input_file = test_input_files[CHALLENGE];
#else
	std::string input_file = input_files[CHALLENGE];
#endif 

	std::vector<std::vector<char>> grid = LoadInputFile(input_file);

	return;
}

std::vector<std::vector<char>> LoadInputFile(const std::string& input_file)
{
	std::fstream file;
	file.open(input_file);

	assert(file);

	std::vector<std::vector<char>> grid = std::vector<std::vector<char>>();

	std::vector<char> line = std::vector<char>(); 
	char c = 0;
	while (file)
	{
		file >> c; 
		
		if (c == '\n')
		{
			grid.push_back(line);
			line = std::vector<char>();
		}
		else
		{
			line.push_back(c);
		}
	}

	return grid;
}

// Searches in the grid for a neighbor of (x,y) which contains "letter". Returns true upon success, and stores the location of the neighbors in x_letter and y_letter, 
bool FindLetterAroundPointInGrid( const std::vector<std::vector<char>>& grid, const char letter, const int x, const int y, std::vector<int>& x_letter, std::vector<int>& y_letter)
{
	assert(grid.size() > 0);

	const int width = grid.size();
	const int height = grid[0].size();
	
	assert(x >= 0 && x < width);
	assert(y >= 0 && y < height);

	bool letter_found = false;

	x_letter = std::vector<int>();
	y_letter = std::vector<int>();

	std::vector<int> x_neighboring_points = { x + 1, x + 1, x, x - 1, x - 1, x - 1, x, x + 1 };
	std::vector<int> y_neighboring_points = { y, y + 1, y + 1, y + 1, y, y - 1, y - 1, y - 1 };

	assert(x_neighboring_points.size() == y_neighboring_points.size());

	for (int i = 0; i < x_neighboring_points.size(); i++)
	{
		int xp = x_neighboring_points[i];
		int yp = y_neighboring_points[i];

		// If xp and yp are valid coordinates for the grid
		if (xp >= 0 && xp < width && yp >= 0 && yp < height)
		{
			if (grid[xp][yp] == letter)
			{
				letter_found = true;

				x_letter.push_back(xp);
				y_letter.push_back(yp);
			}
		}
	}

	return letter_found; 
}

bool FindAllInstancesOfLetterInGrid(const std::vector<std::vector<char>>& grid, const char letter, std::vector<int>& x_locations, std::vector<int>& y_locations)
{
	x_locations = std::vector<int>();
	y_locations = std::vector<int>();

	bool letter_found = false;

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{
			if (grid[x][y] == letter)
			{
				letter_found = true;

				x_locations.push_back(x);
				y_locations.push_back(y);
			}
		}
	}

	return letter_found;
		
}