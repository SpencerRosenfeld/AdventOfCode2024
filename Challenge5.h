#pragma once
#include "BuildConfig.h"
#if CHALLENGE == 5
#include <algorithm>    
#include <assert.h>
#include <fstream>
#include <iostream>
#include "input_files.h"
#include<vector>
#include <sstream>

typedef struct UPDATE_RULES
{
	std::vector<int> first = std::vector<int>();
	std::vector<int> second = std::vector<int>();
	size_t size() const { assert(first.size() == second.size());  return first.size(); }
} UPDATE_RULES;


void AddRule(UPDATE_RULES& rules, const int& first, const int& second);

UPDATE_RULES ExtractRulesRelevantToReplacements(const UPDATE_RULES& rules, const std::vector<int>& replacement);

bool ValidateReplacement(const UPDATE_RULES& rules, const std::vector<int>& replacement);

UPDATE_RULES ExtractRulesWithSecond(const UPDATE_RULES& rules, const int& second);
void SolveChallenge5();

void LoadContent(const std::string& file_name, UPDATE_RULES& rules, std::vector<std::vector<int>>& replacements);


void PrintRulesToStream(std::ostream& stream, const UPDATE_RULES& rules);

void PrintReplacementsToStream(std::ostream& stream, const std::vector<std::vector<int>>& replacements);

#endif
