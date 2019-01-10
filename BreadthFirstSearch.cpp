#include "BreadthFirstSearch.h"

BreadthFirstSearch::BreadthFirstSearch() {
	this->numberOfNodesEvaluated = 0;
}

Solution BreadthFirstSearch::search(Searchable* _searchable) {
	
	this->searchable = _searchable;

	std::vector<State> listOfNodes = searchable->getListOfStates();

	std::map<std::string, bool> visitedMap;
	std::vector<State> queue;

	std::vector<std::vector<std::string>> paths;
	std::vector<std::string> originPath;
	paths.push_back(originPath);

	for (int i = 0; i < listOfNodes.size(); i++) {
		std::string curStateStr = listOfNodes[i].getState();
		visitedMap[curStateStr] = false;
	}

	queue.push_back(this->searchable->getInitialState());
	visitedMap[this->searchable->getInitialState().getState()] = true;
	++this->numberOfNodesEvaluated;
	
	int curParrentPathIndex = 0;

	while (!queue.empty()) {
		State curFirstState = queue[0];
		queue.erase(queue.begin());

		std::vector<State> adjList = this->searchable->getAllPossibleSDtates(curFirstState);

		for (int i = 0; i < adjList.size(); i++) {

			if (!visitedMap[adjList[i].getState()]) {
				visitedMap[adjList[i].getState()] = true;
				queue.push_back(adjList[i]);

				std::vector<std::string> curPath = paths[curParrentPathIndex];
				curPath.push_back(adjList[i].getDirection());
				paths.push_back(curPath);

				++this->numberOfNodesEvaluated;

				if (adjList[i].isEqual(this->searchable->getGoalState())) {
					return Solution(curPath);
				}
			}
		}
		++curParrentPathIndex;
	}

	std::vector<std::string> optimalSolution;

	return Solution(optimalSolution);
}

int BreadthFirstSearch::getNumberOfNodesEvaluated() {
	return this->numberOfNodesEvaluated;
}