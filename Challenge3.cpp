#include "Challenge3.h"

#if CHALLENGE == 3
void SolveChallenge3()
{
#ifdef TEST
	const std::string input_file = test_input_files[CHALLENGE];
#else
	const std::string input_file = input_files[CHALLENGE];
#endif 

	std::string input = "";
	LoadChallenge3Input(input, input_file);

	assert(input != "");

	std::vector<std::string> muls = ExtractMuls(input);

#ifdef TEST
	assert(muls.size() == 4);
	assert(TestEvaluateMul());
#endif 

	std::vector<int> evaluated_muls = std::vector<int>();
	evaluated_muls.resize(muls.size());

	std::transform(muls.begin(), muls.end(), evaluated_muls.begin(), EvaluateMul);
	
	// Sum the evaluted muls to get the answerb
	unsigned long long sum = 0;
	for (int i = 0; i < evaluated_muls.size(); i++)
	{
		assert(sum < ULLONG_MAX / 10);
		assert(ULLONG_MAX - evaluated_muls[i] > sum);

		sum += evaluated_muls[i];
	}

#ifdef TEST
	assert(sum == 161);
#endif 

	std::cout << "Challenge " << CHALLENGE << " part1: The sum of the evaluted muls is " << sum << "\n\n";

	// Part 2:	
	muls = std::vector<std::string>();
	muls = ExtractMulsRespectDoAndDontCommands(input);

#ifdef TEST
	assert(TestExtractMulsRespectDoAndDontCommands());
#endif 

	evaluated_muls = std::vector<int>();
	evaluated_muls.resize(muls.size());
	std::transform(muls.begin(), muls.end(), evaluated_muls.begin(), EvaluateMul);

	// Sum the evaluted muls to get the answerb
	sum = 0;
	for (int i = 0; i < evaluated_muls.size(); i++)
	{
		assert(sum < ULLONG_MAX / 10);
		assert(ULLONG_MAX - evaluated_muls[i] > sum);

		sum += evaluated_muls[i];
	}

	std::cout << "Challenge " << CHALLENGE << " part2: The sum of the evaluate muls, which respect the do command, is " << sum << "\n";

	return;
}


void LoadChallenge3Input(std::string& input, const std::string input_file)
{
	std::fstream file;
	file.open(input_file);

	assert(file);

	std::string line = "";
	while (file)
	{
		line = "";
		file >> line;
		input += line;
	}

	file.close();

	return;
}

std::vector<std::string> ExtractMuls(const std::string& input)
{
	std::vector<std::string> muls;

	const std::string keyword = "mul";
	const std::string minimal_sized_valid_expression = "mul(1,1)";
	const std::string maximal_sized_valid_expression = "mul(111,111)";


	int offset = 0;

	do
	{
		int mul_index = 0;
		int rparen_index = 0;

		mul_index = input.find(keyword, offset);
		rparen_index = input.find(")", mul_index);

		offset = mul_index + keyword.size();

		if (mul_index < input.size() && rparen_index < input.size())
		{
			std::string candidate = input.substr(mul_index, rparen_index - mul_index + 1);

			if(IsValidMul(candidate))
			{
				muls.push_back(candidate);
			}
		}
		else
		{
			break;
		}

	} while (offset < input.size() - minimal_sized_valid_expression.size()+1);
	

	return muls;
}

bool IsValidMul(const std::string& candidate)
{
	if (candidate == "")
	{
		return false;
	}
	const std::string keyword = "mul";
	const std::string minimal_sized_valid_expression = "mul(1,1)";
	const std::string maximal_sized_valid_expression = "mul(111,111)";

	auto IsDigit = [](char c) -> bool { return c >= '0' && c <= '9'; };


	assert(candidate.substr(0, keyword.size()) == keyword);
	assert(candidate[candidate.size() - 1] == ')');

	const int lparen_index = candidate.find("(");
	const int rparen_index = candidate.find(")");

	// Must be at least the size of the minimal size valid expression
	if (candidate.size() < minimal_sized_valid_expression.size())
	{
			return false;
	}

	// Must be no greater than the size of the maximal sized valid expression 
	if (candidate.size() > maximal_sized_valid_expression.size())
	{
		return false;
	}

	// Must have a comma
	if (candidate.find(",") >= candidate.size())
	{
		return false;
	}

	// Must have only one comma
	if (candidate.find_first_of(",") != candidate.find_last_of(","))
	{
		return false;
	}

	// Must have an lparen immediately after the keyword
	if (candidate.find("(") != keyword.size())
	{
		return false;
	}

	// Must have an rparen as the last character
	if (candidate.find(")") != candidate.size() - 1)
	{
		return false;

	}

	assert(candidate[lparen_index] == '(');
	assert(candidate[rparen_index] == ')');

	int first_arg_digit_count = 0;
	int second_arg_digit_count = 0;
	bool invalid_character_found = false;
	int* digit_count = &first_arg_digit_count;
	for (int i = lparen_index + 1; i < rparen_index; i++)
	{
		if (IsDigit(candidate[i]))
		{
			(*digit_count)++;
		}
		else if (',' == candidate[i])
		{
			digit_count = &second_arg_digit_count;
		}
		else
		{
			invalid_character_found = true;
			break;
		}
	}

	digit_count = nullptr;

	// First argument must be 1-3 digits
	if (first_arg_digit_count > 3 || first_arg_digit_count < 1)
	{
		return false;
	}

	// Second argument must be 1-3 digits
	if (second_arg_digit_count > 3 || second_arg_digit_count < 1)
	{
		return false;
	}

	// Expression must consist of only 
	//	the keyword, 
	//	an lparen immediately after the keyword, 
	//	a 1-3 digit number, a single ',', 
	//	a 1-3 digit number, 
	//	and terminate with an rparen immediately after the second 1-3 digit number. 

	if (invalid_character_found)
	{
		return false;
	}

	return true;
}

int EvaluateMul(const std::string& mul)
{
#if _DEBUG
	const std::string minimum_expression = "mul(1,1)";
	const std::string maximum_expression = "mul(111,111)";

	assert(mul.size() >= minimum_expression.size() && mul.size() <= maximum_expression.size());
#endif

	int lparen_index = mul.find('(');
	int rparen_index = mul.find(')');

	assert(lparen_index < mul.size());
	assert(rparen_index < mul.size());
	assert(rparen_index > lparen_index);

	int x1 = 0;
	int x2 = 0;

	int* px = &x2;

	int powerOfTen = 1;

	for (int i = rparen_index-1; i > lparen_index; i--)
	{
		if (mul[i] == ',')
		{
			px = &x1;
			powerOfTen = 1;
		}
		else
		{
			assert(mul[i] >= '0' && mul[i] <= '9');

			(*px) += (mul[i] - '0') * powerOfTen;
			powerOfTen *= 10;
		}
	}

	px = nullptr;

	return x1 * x2;
}

bool TestEvaluateMul()
{
	std::vector<std::string> inputs =
	{
		"mul(999,999)",
		"mul(1,1)",
		"mul(10,20)",
		"mul(250,2)",
		"mul(2,250)"
	};

	std::vector<int> expected =
	{
		999 * 999,
		1 * 1,
		10 * 20,
		250 * 2,
		2 * 250
	};

	std::vector<int> actual;
	actual.resize(inputs.size());

	std::transform(inputs.begin(), inputs.end(), actual.begin(), EvaluateMul);

	assert(actual.size() == expected.size());

	for (int i = 0; i < actual.size(); i++)
	{
		if (actual[i] != expected[i])
		{
			return false;
		}
	}

	return true;
}

std::vector<std::string> ExtractMulsRespectDoAndDontCommands(const std::string& input)
{
	const std::string minimal_mul = "mul(1,1)";
	const std::string do_command = "do()";
	const std::string dont_command = "don't()";

	std::vector<std::string> muls_to_do = std::vector<std::string>();

	int offset = 0;

	while (offset < input.size())
	{
		int dont_index = input.find(dont_command, offset);

		
		std::string relevant_section = input.substr(offset, dont_index - offset);
		muls_to_do.push_back(relevant_section);

		offset = input.find(do_command, dont_index);
	}

	std::vector<std::string> muls;
	for (std::string to_do : muls_to_do)
	{
		std::vector<std::string> new_muls = ExtractMuls(to_do);
		muls.insert(muls.end(), new_muls.begin(), new_muls.end());
	}

	return muls;
}

bool TestExtractMulsRespectDoAndDontCommands()
{
	const std::string input = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

	std::vector<std::string> expected =
	{
		"mul(2,4)",
		"mul(8,5)"
	};

	std::vector<std::string> muls = ExtractMulsRespectDoAndDontCommands(input);


	if (muls.size() != expected.size())
	{
		return false;
	}

	for (int i = 0; i < muls.size(); i++)
	{
		if (muls[i] != expected[i])
		{
			return false;
		}
	}

	return true;
}
#endif 