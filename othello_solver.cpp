#include "othello_solver.hpp"
#include "OthelloGameState.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, jisook5::MyOthelloAI, "Jenny's AI (required)");


std::vector<std::pair<int, int>> jisook5::MyOthelloAI::getMoves(const OthelloGameState & state)
{
	std::vector<std::pair<int, int>> valid_moves;
	for (int i = 0; i < state.board().height(); ++i)
	{
		for (int j = 0; j < state.board().width(); ++j)
		{
			if (state.isValidMove(i, j))
			{
				valid_moves.push_back(std::make_pair(i, j));
			}
		}
		
	}
	return valid_moves;
}


int jisook5::MyOthelloAI::search(const OthelloGameState& state, int depth, std::string turn_color) 
{
	if (state.isGameOver())
		return 0;

	if (depth == 0)
		return evaluate(state, turn_color);
	else
	{
		if ((state.isBlackTurn() && turn_color == "B") || (state.isWhiteTurn() && turn_color == "W"))
		{
			int max = -100;
			for (auto x : getMoves(state))
			{
				std::unique_ptr<OthelloGameState> cloned = state.clone();
				cloned->makeMove(x.first, x.second);
				int game_score = search(*cloned, depth - 1, turn_color);
				if (game_score > max)
					max = game_score;

			}
			return max;
		}

		else
		{
			int min = 100;
			for (auto x : getMoves(state))
			{
				std::unique_ptr<OthelloGameState> cloned = state.clone();
				cloned->makeMove(x.first, x.second);
				int game_score = search(*cloned, depth - 1, turn_color);
				if (game_score < min)
					min = game_score;
			}
			
			return min;
		}
	}
	
}

int jisook5::MyOthelloAI::evaluate(const OthelloGameState& state, std::string turn_color)
{
	if (turn_color == "W")
	{
		
		return state.whiteScore() - state.blackScore();
	}

	if (turn_color == "B")
	{
		return state.blackScore() - state.whiteScore();
	}
}

std::pair<int, int> jisook5::MyOthelloAI::chooseMove(const OthelloGameState & state)
{
	std::string turn_color;

	if (state.isBlackTurn())
		turn_color = "B";
	if (state.isWhiteTurn())
		turn_color = "W";


	int best_possible_move = -64;
	std::pair<int, int> pair1;


	for (int i = 0; i < state.board().height(); ++i) 
	{
		for (int j=0; j < state.board().width(); ++j)
		{
			if (state.isValidMove(i, j))
			{
				std::unique_ptr<OthelloGameState> cloned_state = state.clone();
				cloned_state->makeMove(i, j);

				int best_move_score = search(*cloned_state, 3, turn_color);
				if (best_move_score > best_possible_move)
					pair1 = std::make_pair(i, j);
			}
		}
	}

	return pair1;

}