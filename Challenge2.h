#pragma once
#include "BuildConfig.h"
#if CHALLENGE == 2
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
void SolveChallenge2();
void LoadInputForChallenge2(std::string input_file, std::vector<std::vector<int>>& level_reports);
int CountSafeLevelReports(const std::vector<std::vector<int>>& level_reports, bool IsLevelReportSafe(const std::vector<int>&));
bool IsLevelReportSafe(const std::vector<int>& level_report);
bool IsTrueIfWeRemoveOneInt(const std::vector<int>& level_report, bool IsTrue(const std::vector<int>&));
//bool IsLevelSafeIfWeRemoveOneEntry(const std::vector<int>& i);
bool IsPositive(int x);

#endif 

