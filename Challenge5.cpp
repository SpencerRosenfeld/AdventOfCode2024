#include "Challenge5.h"
#if CHALLENGE == 5
void SolveChallenge5()
{
#ifdef TEST
	std::string file_name = test_input_files[CHALLENGE];
#else 
	std::string file_name = input_files[CHALLENGE];
#endif 

	UPDATE_RULES rules;
	std::vector<std::vector<int>> replacements = std::vector<std::vector<int>>();

	LoadContent(file_name, rules, replacements);

#ifdef TEST
	// Test rules
	{
		std::string test_string = "47|53\n97|13\n97|61\n97|47\n75|29\n61|13\n75|53\n29|13\n97|29\n53|29\n61|53\n97|53\n61|29\n47|13\n75|47\n97|75\n47|61\n75|61\n47|29\n75|13\n53|13\n";

		std::stringstream sstream;

		PrintRulesToStream(sstream, rules);

		std::string actual = sstream.str();

		assert(test_string == actual);
	}
	

	// Test replacements
	{
		std::string test_string = "75,47,61,53,29\n97,61,53,29,13\n75,29,13\n75,97,47,61,53\n61,13,29\n97,13,75,29,47\n";

		std::stringstream sstream;

		PrintReplacementsToStream(sstream, replacements);

		std::string actual = sstream.str();

		assert(test_string == actual);
	}
#endif 

	std::vector<bool> replacement_is_valid = std::vector<bool>();
	replacement_is_valid.resize(replacements.size());

	for (int i = 0; i < replacements.size(); i++)
	{
		replacement_is_valid[i] = ValidateReplacement(rules, replacements[i]);
	}

	for (int i = 0; i < replacements.size(); i++)
	{
		std::string valid = replacement_is_valid[i] ? "VALID: " : "INVALID";

		std::cout << valid << " ";
		for (int j = 0; j < replacements[i].size(); j++)
		{
			std::cout << replacements[i][j] << ",";
		}

		std::cout << "\n";
	}

}

void LoadContent(const std::string& file_name, UPDATE_RULES& rules, std::vector<std::vector<int>>& replacements)
{
	std::fstream file;
	file.open(file_name);

	assert(file);

	std::string line = "";
	while (file)
	{
		std::getline(file, line);

		int divider_index = line.find("|");
		if (divider_index < line.size() && divider_index + 1 < line.size() )
		{
			std::string first_str = line.substr(0, divider_index);
			std::string second_str = line.substr(divider_index + 1, line.size());

			int first = atoi(first_str.c_str());
			int second = atoi(second_str.c_str());

			AddRule(rules, first, second);
		}
		else
		{
			// End of rules list. Not proceed to read page repalcements. 
			break;
		}
	}

	// Load the replacemnts 
	while (file)
	{
		getline(file, line);

		if (line != "");
		{
			std::vector<int> replacement;
			std::stringstream ss;

			int offset = 0;
			int x = 0;
			std::string x_str = "";
			 
			while (offset  < line.size())
			{
				int index = line.find(',', offset);

				if (index != std::string::npos)
				{
					// 3-1 == 2 => Num characters in indices [1,3)
					// [0, 1, 2, 3, 4, 5]
					x_str = line.substr(offset, index-offset);
					offset = index + 1;
				}
				else
				{
					x_str = line.substr(offset, line.size() - offset);
					offset = line.size();
				}

				x = atoi(x_str.c_str());

				replacement.push_back(x);
			}

			if (replacement.size() > 0)
			{
				replacements.push_back(replacement);
			}
		}
	}

	file.close();
}

void PrintRulesToStream(std::ostream& stream,  const UPDATE_RULES& rules)
{
	assert(rules.first.size() == rules.second.size());
	for (int i = 0; i < rules.first.size(); i++)
	{
		stream << rules.first[i] << "|" << rules.second[i] << "\n";
	}

	return;
}

void PrintReplacementsToStream(std::ostream& stream, const std::vector<std::vector<int>>& replacements)
{
	for (int i = 0; i < replacements.size(); i++)
	{
		for (int j = 0; j < replacements[i].size()-1; j++)
		{
			stream << replacements[i][j] << ",";
		}

		stream << replacements[i][replacements[i].size() - 1] << "\n";
	}
	
	return;
}

void AddRule(UPDATE_RULES& rules, const int& first, const int& second)
{
	rules.first.push_back(first);
	rules.second.push_back(second);
}

UPDATE_RULES ExtractRulesRelevantToReplacements(const UPDATE_RULES& rules, const std::vector<int>& replacement)
{
	UPDATE_RULES relevant_rules = UPDATE_RULES();

	for (int i = 0; i < rules.size(); i++)
	{
		for (int k = 0; k < replacement.size(); k++)
		{
			if (rules.first[i] == replacement[k])
			{
				AddRule(relevant_rules, rules.first[i], rules.second[i]);
				continue;
			}
			else if (rules.second[i] == replacement[k])
			{
				AddRule(relevant_rules, rules.first[i], rules.second[i]);
				continue;
			}
		}
	}

	return relevant_rules;
}

bool ValidateReplacement(const UPDATE_RULES& rules, const std::vector<int>& replacement)
{
	for (int i = 0; i < replacement.size(); i++)
	{
		auto relevant_rules = ExtractRulesWithSecond(rules, replacement[i]);

		for (int j = 0; j < relevant_rules.size(); j++)
		{
			bool first_found = false;
			for (int k = 0; k < i; k++)
			{
				if (relevant_rules.first[j] == replacement[k])
				{
					first_found = true;
					break;
				}
			}

			if (!first_found)
			{
				return false;
			}
		}
	}

	return true;

}
UPDATE_RULES ExtractRulesWithSecond(const UPDATE_RULES& rules, const int& second)
{
	UPDATE_RULES relevant_rules = UPDATE_RULES();

	assert(rules.first.size() == rules.second.size());
	for (int i = 0; i < rules.first.size(); i++)
	{
		if (rules.second[i] == second)
		{
			AddRule(relevant_rules, rules.first[i], rules.second[i]);
		}
	}

	return relevant_rules;
}

#endif 
