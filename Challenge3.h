#pragma once
#pragma once
#include "BuildConfig.h"
#if CHALLENGE == 3
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


void SolveChallenge3();

void LoadChallenge3Input(std::string& input, const std::string input_file);

std::vector<std::string> ExtractMuls(const std::string& input);

bool IsValidMul(const std::string& candidate);

int EvaluateMul(const std::string& mul);
bool TestEvaluateMul();

std::vector<std::string> ExtractMulsRespectDoAndDontCommands(const std::string& input);
bool TestExtractMulsRespectDoAndDontCommands();
#endif 
