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

static const std::string keyword = "XMAS";

#endif 