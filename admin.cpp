#include "admin.h"

int main () {


	std::cout<<"MATRIX IS:\n";

	std::vector<std::vector<std::string>> matrix;

	int k = 10;

	for (int i = 0; i < 5; ++i) {
		std::vector<std::string> curLine;
		for (int i2 = 0; i2 < 5; ++i2) {
			curLine.push_back(std::to_string(++k));
			std::cout<<k<<" ";
		}
		matrix.push_back(curLine);

		std::cout<<"\n";
	}

/*
std::vector<std::string> curLine;
curLine.push_back("8");
curLine.push_back("9");
curLine.push_back("11");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("5");
curLine.push_back("6");
curLine.push_back("7");
matrix.push_back(curLine);
curLine.clear();

curLine.push_back("8");
curLine.push_back("9");
curLine.push_back("10");
matrix.push_back(curLine);
curLine.clear();
*/	
	Searchable* searchable = new Problem(matrix, "3,4", "0,0");

//	Searcher* searcher = new BreadthFirstSearch();
//	Searcher* searcher = new DepthFirstSearch();
	Searcher* searcher = new BestFirstSearch();
	SearcherAdapter searchAdapter = SearcherAdapter(searcher);

	std::vector<std::string> optimalSolution = searchAdapter.solve(searchable).getOptimalPath();

	std::cout<<"The optimal path is:\n";
	for (int i = 0; i < optimalSolution.size(); ++i) {
		std::cout<<optimalSolution[i]<<"\n";
	}

	return 0;
}
