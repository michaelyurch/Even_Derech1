#include "BestFirstSearch.h"

BestFirstSearch::BestFirstSearch() {
	this->numberOfNodesEvaluated = 0;
}

Solution BestFirstSearch::search(Searchable* _searchable) {
	
	this->searchable = _searchable;

	std::vector<State> listOfNodes = searchable->getListOfStates();

	std::map<std::string, bool> visitedMap;
//	std::vector<State> stack;
    std::priority_queue<State> queue;

	std::vector<std::vector<std::string>> paths;

	std::string prevDirection = searchable->getInitialState().getState();

	std::vector<std::string> path;

	for (int i = 0; i < listOfNodes.size(); i++) {
		std::string curStateStr = listOfNodes[i].getState();
		visitedMap[curStateStr] = false;
	}

	queue.push(this->searchable->getInitialState());

	while (!queue.empty()) {
		State curFirstState = queue.top();
		queue.pop();

		if (curFirstState.getDirection() != prevDirection) {
			prevDirection = curFirstState.getDirection();

			paths.push_back(path);
		}

		if (!visitedMap[curFirstState.getState()]) {

            ++this->numberOfNodesEvaluated;

			if (!curFirstState.isEqual(this->searchable->getInitialState())) {
				std::cout<<curFirstState.getCost()<<" "
				<<curFirstState.getState()<<" "<<curFirstState.getDirection()<<"\n";
				path.push_back(curFirstState.getDirection());
			}
			
			if (curFirstState.isEqual(this->searchable->getGoalState())) {
				return Solution(path);
			}

			visitedMap[curFirstState.getState()] = true;
			std::vector<State> adjList = this->searchable->getAllPossibleSDtates(curFirstState);

			int unvisitedAdjSize = 0;

			for (int i = 0; i < adjList.size(); i++) {
				queue.push(adjList[i]);
				if (!visitedMap[adjList[i].getState()]) {
					++unvisitedAdjSize;
				}
			}

			if (unvisitedAdjSize == 0) {
				paths.pop_back();
				std::cout<<"NO ADJ\n";
				path = paths[paths.size() - 1];
			//	paths.pop_back();
			}
		}
	}

	std::vector<std::string> optimalSolution;
	return Solution(optimalSolution);
}
	
int BestFirstSearch::getNumberOfNodesEvaluated() {
	return this->numberOfNodesEvaluated;
}