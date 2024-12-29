#include "Challenge1.h"

#if CHALLENGE == 1
void SolveChallenge1()
{

#ifdef TEST
    std::string input_file = test_input_files[CHALLENGE];
#else 
    std::string input_file = input_files[CHALLENGE];
#endif 

    std::vector<int> list1 = std::vector<int>();
    std::vector<int> list2 = std::vector<int>();

    LoadInputForChallenge1(input_file, list1, list2);

#ifdef TEST
    assert(list1.size() == 6);
    assert(list2.size() == 6);
#endif 

    int distance = ComputeDistanceBetweenLists(list1, list2);

#ifdef TEST
    assert(distance == 11);
#endif 

    std::cout << "The distance between the lists is " << distance << "\n";

    int score = ComputeSimilarityScore(list1, list2);

#ifdef TEST
    assert(score == 31);
#endif 
    std::cout << "The similarity score between the lists is " << score << "\n";

}
void LoadInputForChallenge1(std::string input_file, std::vector<int>& list1, std::vector<int>& list2)
{
    std::fstream file;
    file.open(input_file);

    assert(file);

    int x1, x2;

    while (file)
    {
        file >> x1;
        file >> x2;

        if (file)
        {
            list1.push_back(x1);
            list2.push_back(x2);
        }
    }

    file.close();
}

int ComputeDistanceBetweenLists(std::vector<int>& list1, std::vector<int>& list2)
{
    assert(list1.size() == list2.size());

    std::sort(list1.begin(), list1.end());
    std::sort(list2.begin(), list2.end());

    int sum = 0;

    for (int i = 0; i < list1.size(); i++)
    {
        sum += abs(list1[i] - list2[i]);
    }

    return sum;
}

int ComputeSimilarityScore(const std::vector<int>& list1, const std::vector<int>& list2)
{
    assert(list1.size() == list2.size());

    int score = 0;
    for (int i = 0; i < list1.size(); i++)
    {
        int item1 = list1[i];

        score += item1 * std::count(list2.begin(), list2.end(), item1);
    }

    assert(score >= 0);

    return score;
}
#endif 