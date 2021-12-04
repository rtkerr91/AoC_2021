#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::vector<int>> read_inputs(std::string filepath)
{

	std::vector<std::vector<int>> data;

	std::ifstream file;
	file.open(filepath);

	std::string line;

	while (std::getline(file, line))
	{
		std::vector<int> row;
		for (int i = 0; i < line.length(); i++)
		{
			row.push_back(line[i] - 48);    // This is a dumb way to convert string '1' or '0' to integer 1 or 0...
		}

		data.push_back(row);
	}

	file.close();

	return data;
}

int get_gamma_rate(std::vector<std::vector<int>> data)
{
	std::stringstream gamma_rate_str;

	int n_rows = data.size();
	
	for (int j = 0; j < data[0].size(); j++)
	{
		int sum = 0;
		for (int i = 0; i < n_rows; i++)
		{
			sum = sum + data[i][j];
		}

		if (sum > ((n_rows / 2) + n_rows % 2))
			gamma_rate_str << 1;
		else
			gamma_rate_str << 0;
	}

	return std::stoi(gamma_rate_str.str(), nullptr, 2);
}

int get_epsilon_rate(std::vector<std::vector<int>> data)
{
	std::stringstream epsilon_rate_str;

	int n_rows = data.size();

	for (int j = 0; j < data[0].size(); j++)
	{
		int sum = 0;
		for (int i = 0; i < n_rows; i++)
		{
			sum = sum + data[i][j];
		}

		if (sum > ((n_rows / 2) + n_rows % 2))
			epsilon_rate_str << 0;
		else
			epsilon_rate_str << 1;
	}

	return std::stoi(epsilon_rate_str.str(), nullptr, 2);
}

std::vector<std::vector<int>> _get_o2_rate_recursive(std::vector<std::vector<int>> &data, int j_col)
{
	if (data.size() == 1)
		return data;

	int sort_value;

	std::vector<std::vector<int>> data_0;
	std::vector<std::vector<int>> data_1;

	int n_rows = data.size();
	int sum = 0;

	for (int i = 0; i < n_rows; i++)
	{
		sum = sum + data[i][j_col];

		if (data[i][j_col] == 0)
			data_0.push_back(data[i]);
		else
			data_1.push_back(data[i]);
	}

	if (sum >= ((n_rows / 2) + n_rows % 2))
		sort_value = 1;
	else
		sort_value = 0;
	
	j_col++;

	std::vector<std::vector<int>> filtered_data;

	if (sort_value == 0)
		filtered_data = _get_o2_rate_recursive(data_0, j_col);
	else
		filtered_data = _get_o2_rate_recursive(data_1, j_col);

	return filtered_data;
}

int get_o2_rate(std::vector<std::vector<int>> data)
{
	std::vector<std::vector<int>> rate_bit_array = _get_o2_rate_recursive(data, 0);

	std::stringstream rate_ss;

	for (int i = 0; i < rate_bit_array[0].size(); i++)
		rate_ss << rate_bit_array[0][i];

	return std::stoi(rate_ss.str(), nullptr, 2);
}

std::vector<std::vector<int>> _get_co2_rate_recursive(std::vector<std::vector<int>>& data, int j_col)
{
	if (data.size() == 1)
		return data;

	int sort_value;

	std::vector<std::vector<int>> data_0;
	std::vector<std::vector<int>> data_1;

	int n_rows = data.size();
	int sum = 0;

	for (int i = 0; i < n_rows; i++)
	{
		sum = sum + data[i][j_col];

		if (data[i][j_col] == 0)
			data_0.push_back(data[i]);
		else
			data_1.push_back(data[i]);
	}

	if (sum >= ((n_rows / 2) + n_rows % 2))
		sort_value = 0;
	else
		sort_value = 1;

	j_col++;

	std::vector<std::vector<int>> filtered_data;

	if (sort_value == 0)
		filtered_data = _get_co2_rate_recursive(data_0, j_col);
	else
		filtered_data = _get_co2_rate_recursive(data_1, j_col);

	return filtered_data;
}

int get_co2_rate(std::vector<std::vector<int>> data)
{
	std::vector<std::vector<int>> rate_bit_array = _get_co2_rate_recursive(data, 0);

	std::stringstream rate_ss;

	for (int i = 0; i < rate_bit_array[0].size(); i++)
		rate_ss << rate_bit_array[0][i];

	return std::stoi(rate_ss.str(), nullptr, 2);
}

int main()
{
	std::vector<std::vector<int>> input_data = read_inputs("inputs\\inputs.txt");
	
	std::cout << "Part 1 =================" << std::endl;
	
	int gamma_rate = get_gamma_rate(input_data);
	int epsilon_rate = get_epsilon_rate(input_data);

	std::cout << "Gamma Rate: " << gamma_rate << std::endl;
	std::cout << "Epsilon Rate: " << epsilon_rate << std::endl;
	std::cout << "Gamma * Epsilon: " << gamma_rate * epsilon_rate << std::endl;

	std::cout << "Part 2 =================" << std::endl;

	int o2_rate = get_o2_rate(input_data);
	int co2_rate = get_co2_rate(input_data);

	std::cout << "O2 Rate: "<< o2_rate << std::endl;
	std::cout << "CO2 Rate: "<< co2_rate << std::endl;
	std::cout << "O2 * CO2: "<< o2_rate * co2_rate << std::endl;

	return 0;
}
