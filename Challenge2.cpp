#include "Challenge2.h"

#if CHALLENGE == 2
void SolveChallenge2()
{
#ifdef TEST
    std::string input_file = test_input_files[CHALLENGE];
#else 
    std::string input_file = input_files[CHALLENGE];
#endif 

    std::vector<std::vector<int>> level_reports;

    LoadInputForChallenge2(input_file, level_reports);

#ifdef TEST
    assert(level_reports.size() == 6);
    for (int i = 0; i < level_reports.size(); i++)
    {
        assert(level_reports[i].size() == 5);
    }
#endif

    int number_of_safe_level_reports = CountSafeLevelReports(level_reports, IsLevelReportSafe);
 
#ifdef TEST
    assert(number_of_safe_level_reports == 2);
#endif 

    std::cout << "Part1:\nThe number of safe level reports is " << number_of_safe_level_reports << "\n\n";


    auto IsLevelSafeIfWeRemoveOneEntry = [](const std::vector<int>&i)->bool 
    {
        return IsTrueIfWeRemoveOneInt(i, IsLevelReportSafe);
    };

    int number_of_safe_level_reports_if_we_remove_one_entry = CountSafeLevelReports(level_reports, IsLevelSafeIfWeRemoveOneEntry);

    std::cout << "Part2:\nThe number of safe level reports if we allow one entry to be removed is " << number_of_safe_level_reports_if_we_remove_one_entry << "\n";
 
    return;
}


void LoadInputForChallenge2(std::string input_file, std::vector<std::vector<int>>& level_reports)
{
    std::fstream file;

    file.open(input_file);

    assert(file);

    std::vector<int> report;
    while (file)
    {
        std::string line;
        std::getline(file, line);

        if (line != "")
        {
            std::stringstream ss(line);
            std::vector<int> report;
            while (ss)
            {
                int level;
                ss >> level;
                if (ss)
                {
                    report.push_back(level);
                }
            }

            level_reports.push_back(report);
        }
    }
}

int CountSafeLevelReports(const std::vector<std::vector<int>>& level_reports, bool IsLevelReportSafe( const std::vector<int>&) ) 
{
    int sum = 0;
    for (int i = 0; i < level_reports.size(); i++)
    {
        if (IsLevelReportSafe(level_reports[i]))
        {
            sum += 1;
        }
    }

    return sum;
}


bool IsLevelReportSafe(const std::vector<int>& level_report)
{
    // Conditions for a safe level report
    //  * The levels are either all increasing or all decreasing.
    //  * Any two adjacent levels differ by at least oneand at most three.

    assert(level_report.size() > 2);

    for (int i = 1; i < level_report.size(); i++)
    {
        if (IsPositive(level_report[1] - level_report[0]) == IsPositive(level_report[i] - level_report[i - 1]))
        {
            if (abs(level_report[i] - level_report[i - 1]) >= 1 && abs(level_report[i] - level_report[i - 1]) <= 3)
            {
                continue;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool IsTrueIfWeRemoveOneInt(const std::vector<int>& input, bool IsTrue(const std::vector<int>&) )
{
    if (IsTrue(input))
    {
#ifdef TEST
        std::cout << "Safe already ";
        for (int j = 0; j < input.size(); j++)
        {
            std::cout << input[j] << ",";
        }
        std::cout << "\n";
#endif 

        return true;
    }

    std::vector<int> input_without_element_i = std::vector<int>();
    input_without_element_i.resize(input.size() - 1);
    for (int i = 0; i < input.size(); i++)
    {
        int pointer = 0;
        for (int j = 0; j < input.size(); j++)
        {
            if (j == i)
            {
                continue;
            }

            input_without_element_i[pointer++] = input[j];
        }

        assert(pointer == input_without_element_i.size());

        if (IsTrue(input_without_element_i))
        {
#ifdef TEST
            std::cout << "Safe with one entry removed ";
            for (int j = 0; j < input.size(); j++)
            {
                std::cout << input[j] << ",";
            }
            std::cout << "\n";
#endif 
            return true;
        }
    }

#ifdef TEST
    std::cout << "Unsafe even with one entry removed ";
    for (int j = 0; j < input.size(); j++)
    {
        std::cout << input[j] << ",";
    }
    std::cout << "\n";
#endif 

    return false;
}

//bool IsLevelSafeIfWeRemoveOneEntry(const std::vector<int>& i)
//{
//    return IsTrueIfWeRemoveOneInt(i, IsLevelReportSafe);
//};

bool IsPositive(int x)
{
    return x > 0 ? true : false;
}

#endif 