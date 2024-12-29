#pragma once
#include "BuildConfig.h"
#if CHALLENGE  == 1
#include <vector>
#include <algorithm>    
#include <assert.h>
#include <fstream>
#include <iostream>
#include "input_files.h"

void SolveChallenge1();
void LoadInputForChallenge1(std::string input_file, std::vector<int>& list1, std::vector<int>& list2);
int ComputeDistanceBetweenLists(std::vector<int>& list1, std::vector<int>& list2);
int ComputeSimilarityScore(const std::vector<int>& list1, const std::vector<int>& list2);

#endif 