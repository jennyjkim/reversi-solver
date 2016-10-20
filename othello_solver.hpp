#include "OthelloAI.hpp"
#include <iostream>
#include <vector>
#ifndef OTHELLO_SOLVER_HPP
#define OTHELLO_SOLVER_HPP




namespace jisook5
{
	class MyOthelloAI : public OthelloAI
	{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		int evaluate(const OthelloGameState& state, std::string turn_color);
		int search(const OthelloGameState& state, int depth, std::string turn_color);
		std::vector<std::pair<int, int>> getMoves(const OthelloGameState & state);
	};
}



#endif //OTHELLO_SOLVER_HPP//