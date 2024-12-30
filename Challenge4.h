#pragma once
#pragma once
#include "BuildConfig.h"
#if CHALLENGE == 4
#include <vector>
#include <algorithm>    
#include <assert.h>
#include <fstream>
#include <iostream>
#include "input_files.h"
#include<vector>
#include <algorithm>    
#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>


void SolveChallenge4();

std::vector<std::vector<char>> LoadInputFile(const std::string& input_file);

int CountWordInGrid(const std::vector<std::vector<char>>& grid, const std::string& word);

int CountInstancesOfPatternsInGrid(const std::vector<std::vector<char>>& grid, const std::vector<std::vector<std::vector<char>>>& patterns);

static const std::string keyword = "XMAS";

const std::vector< std::vector<std::vector<char>>> patterns =
{
	{
		{'M', 0, 'M'},
		{0, 'A', 0},
		{'S', 0, 'S'}
	},
	{
		{'S', 0, 'S'},
		{0, 'A', 0},
		{'M', 0, 'M'}
	},
	{
		{'M', 0, 'S'},
		{0, 'A', 0},
		{'M', 0, 'S'}
	},
	{
		{'S', 0, 'M'},
		{0, 'A', 0},
		{'S', 0, 'M'}
	}
};
		


#endif 