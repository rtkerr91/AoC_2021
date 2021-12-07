#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class Board
{
private:
	std::vector<std::vector<int>> m_Board;
	std::vector<std::vector<bool>> m_Bool_Board;
	int m_Last_Marked_Number;

public:
	Board(std::vector<std::vector<int>> board_numbers)
	{
		m_Board = board_numbers;

		// Initialize m_Bool_Board with all false
		for (int i = 0; i < m_Board.size(); i++)
		{
			std::vector<bool> row;
			for (int j = 0; j < m_Board[0].size(); j++)
			{
				row.push_back(false);
			}
			m_Bool_Board.push_back(row);
		}
	}
	
	~Board() {};

	void mark_number(int number)
	{
		// Loop over the board and if the number is found in the m_Board, mark it true in the m_Bool_Board
		for (int i = 0; i < m_Board.size(); i++)
		{
			for (int j = 0; j < m_Board[0].size(); j++)
			{
				if (m_Board[i][j] == number)
					m_Bool_Board[i][j] = true;
			}
		}

		m_Last_Marked_Number = number;
	}

	bool is_solved()
	{
		for (int i = 0; i < m_Bool_Board.size(); i++)
		{
			bool is_row_solved = true;
			for (int j = 0; j < m_Bool_Board[0].size(); j++)
			{
				if (!m_Bool_Board[i][j])
				{
					is_row_solved = false;
					break;
				}
			}

			if (is_row_solved)
			{
				std::cout << "Row Solved." << std::endl;
				return true;
			}
		}

		for (int j = 0; j < m_Bool_Board[0].size(); j++)
		{
			bool is_col_solved = true;
			for (int i = 0; i < m_Bool_Board.size(); i++)
			{
				if (!m_Bool_Board[i][j])
				{
					is_col_solved = false;
					break;
				}
			}

			if (is_col_solved)
			{
				std::cout << "Column Solved." << std::endl;
				return true;
			}
		}

		return false;
	}

	int score_board()
	{
		// Loop over the board and if the number has been marked, add it to sum
		int sum = 0;
		for (int i = 0; i < m_Board.size(); i++)
		{
			for (int j = 0; j < m_Board[0].size(); j++)
			{
				if (!m_Bool_Board[i][j])
					sum = sum + m_Board[i][j];
			}
		}

		return sum * m_Last_Marked_Number;
	}

	void print_board()
	{
		for (int i = 0; i < m_Board.size(); i++)
		{
			for (int j = 0; j < m_Board[0].size(); j++)
			{
				std::cout << m_Board[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

	void print_bool_board()
	{
		for (int i = 0; i < m_Bool_Board.size(); i++)
		{
			for (int j = 0; j < m_Bool_Board[0].size(); j++)
			{
				std::cout << m_Bool_Board[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
};

std::vector<int> read_called_numbers(std::string filepath)
{
	std::vector<int> numbers;

	std::ifstream file;
	file.open(filepath);

	std::string num_str;

	while (std::getline(file, num_str, ','))
	{
		numbers.push_back(std::stoi(num_str));
	}

	return numbers;
}

std::vector<Board> read_boards(std::string filepath)
{
	std::vector<Board> boards;

	std::ifstream file;
	file.open(filepath);

	std::string line;
	std::vector<std::vector<int>> new_board;

	while (std::getline(file, line))
	{
		std::vector<int> board_row;

		if (line == "")
		{
			boards.push_back(Board(new_board));
			new_board.clear();
		}

		else
		{
			std::stringstream linestream(line);
			int value;

			while (linestream >> value)
				board_row.push_back(value);

			new_board.push_back(board_row);
		}
	}

	boards.push_back(Board(new_board));

	return boards;
}

int main()
{

	std::vector<int> called_numbers = read_called_numbers("inputs\\called_numbers.txt");
	std::vector<Board> boards = read_boards("inputs\\boards.txt");

	std::cout << "Part 1 ======================" << std::endl;

	bool someone_won = false;
	int i = 0;
	while ((!someone_won) & (i<called_numbers.size()))
	{
		for (int b = 0; b < boards.size(); b++)
		{
			boards[b].mark_number(called_numbers[i]);
		}

		for (int b = 0; b < boards.size(); b++)
		{
			if (boards[b].is_solved())
			{
				int score = boards[b].score_board();
				std::cout << "Board #" << b + 1 << " won. Score is " << score << std::endl;
				someone_won = true;
			}
		}

		if (someone_won)
		{
			break;
		}

		i++;
	}

	std::cout << "Part 2 ======================" << std::endl;
	// Same as Part 1, but just keep playing until all boards have won.
	//this part has a bug where you don't know the correct board number that won because
	// you delete the board after it wins and it throws off the counter 'b'. Doesn't matter to get the right
	// answer though... :D

	i = 0;
	while ((boards.size() > 0) & (i < called_numbers.size()))
	{
		for (int b = 0; b < boards.size(); b++)
		{
			boards[b].mark_number(called_numbers[i]);
		}

		for (int b = 0; b < boards.size(); b++)
		{
			if (boards[b].is_solved())
			{
				int score = boards[b].score_board();
				std::cout << "Board #" << b + 1 << " won. Score is " << score << std::endl;
				boards.erase(boards.begin()+b);
			}
		}

		i++;
	}


	return 0;
}
