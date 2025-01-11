#include "Challenge4.h"
#if CHALLENGE == 4

void SolveChallenge4()
{
#ifdef TEST
	std::string input_file = test_input_files[CHALLENGE];
#else
	std::string input_file = input_files[CHALLENGE];
#endif 

	std::vector<std::vector<char>> grid = LoadInputFile(input_file);

	int count = CountWordInGrid(grid, keyword);

#ifdef TEST
	assert(count == 18);
#endif 

	std::cout << "Challenge 4 part 1:\nThe number of instances of " << keyword << " in the input grid is " << count << "\n\n"; 

// Part 2 -------------------------------------------------------------
	count = CountInstancesOfPatternsInGrid(grid, patterns);
	
#ifdef TEST
	assert(count == 9);
#endif 

	std::cout << "Challenge 4 part 2:\nThe number of X-MAS's in the grid is " << count << "\n";
	return;
}

std::vector<std::vector<char>> LoadInputFile(const std::string& input_file)
{
	std::fstream file;
	file.open(input_file);

	assert(file);

	std::vector<std::vector<char>> grid = std::vector<std::vector<char>>();

//	std::vector<char> line = std::vector<char>(); 
	std::string line = "";
	int line_index = 0;
	char c = 0;
	while (file)
	{
		//file >> c; 
		//	
		//if (c == '\n')
		//{
		//	grid.push_back(line);
		//	line = std::vector<char>();
		//}
		//else
		//{
		//	line.push_back(c);
		//}

		line = "";
		std::getline(file, line);

		if (line != "")
		{
			grid.push_back(std::vector<char>());
			for (int i = 0; i < line.length(); i++)
			{
				grid[line_index].push_back(line[i]);
			}
			line_index++;
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

	const std::vector<int> x_neighboring_points = { x + 1, x + 1, x, x - 1, x - 1, x - 1, x, x + 1 };
	const std::vector<int> y_neighboring_points = { y, y + 1, y + 1, y + 1, y, y - 1, y - 1, y - 1 };

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

int CountWordInGrid(const std::vector<std::vector<char>>& grid, const std::string& word)
{
	assert(word.length() > 3);

	const int width = grid.size();
	const int height = grid[0].size();

	std::vector<int> x;
	std::vector<int> y;

	bool succuess = FindAllInstancesOfLetterInGrid(grid, word[0], x, y);

	assert(x.size() == y.size());

	if (!succuess)
	{
		return 0;
	}

	char second_letter = word[1];

	std::vector<std::vector<int>> x2 = std::vector<std::vector<int>>();
	std::vector<std::vector<int>> y2 = std::vector<std::vector<int>>();


	for (int j = 0; j < x.size(); j++)
	{
		std::vector<int> xp = std::vector<int>();
		std::vector<int> yp = std::vector<int>();

		FindLetterAroundPointInGrid(grid, second_letter, x[j], y[j], xp, yp);

		assert(yp.size() == xp.size());
		x2.push_back(xp);
		y2.push_back(yp);
	}

	int count = 0;
	for (int i = 0; i < x.size(); i++)
	{
		for (int j = 0; j < x2[i].size(); j++)
		{
			int delta_x = x2[i][j] - x[i];
			int delta_y = y2[i][j] - y[i];

			bool word_is_present = true;
			for (int k = 0; k < word.length(); k++)
			{
				int xk = x[i] + delta_x * k;
				int yk = y[i] + delta_y * k; 

				if (xk >= 0 && xk < width && yk >= 0 && yk < height)
				{
					if (grid[xk][yk] != word[k])
					{
						word_is_present = false;
						break;
					}
				}
				else
				{
					word_is_present = false;
					break;
				}
			}

			if (word_is_present == true)
			{
				count++;
			}
		}
	}
	return count;
}

int CountInstancesOfPatternsInGrid(const std::vector<std::vector<char>>& grid, const std::vector<std::vector<std::vector<char>>>& patterns)
{
	const int grid_width = grid.size();
	const int grid_height = grid[0].size();

	int count = 0;
	for (auto pattern : patterns)
	{
		const int pattern_width = pattern.size();
		const int pattern_height = pattern[0].size();
		
		for (int x = 0; x < grid_width; x++)
		{
			if (x + pattern_width-1 < grid_width)
			{
				for (int y = 0; y < grid_height; y++)
				{
					if (y + pattern_height-1 < grid_height)
					{
						bool match = true;
						for (int delta_x = 0; delta_x < pattern_width; delta_x++)
						{
							for (int delta_y = 0; delta_y < pattern_height; delta_y++)
							{
								if (pattern[delta_x][delta_y] != 0)
								{
									if (grid[x + delta_x][y + delta_y] != pattern[delta_x][delta_y])
									{
										match = false;
										break;
									}
								}
							}
							if (match == false)
							{
								break;
							}
						}
						if (match == true)
						{
							count++;
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	return count;
}
#endif 