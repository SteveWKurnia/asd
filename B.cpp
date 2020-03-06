#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
using namespace std;

struct Edge{
	int source, destination, cost;
};
struct Comparator{
	bool operator()(Edge const& e1, Edge const& e2){
        return e1.cost > e2.cost;
    } 
};
Edge newEdge(int src, int dst, int cst){
	Edge edge;
	edge.cost = cst;
	edge.destination = dst;
	edge.source = src;
	
	return edge;
}
int getParent(int parent[], int curr){
	if(parent[curr] != curr){
		return parent[curr] = getParent(parent, parent[curr]);
	}
	return parent[curr];
}

int countMoves(char a[], char b[]){
	int move = 0;
//	puts("");
//	printf("%s %s\n", a, b);
	for(int j = 0; j < 4; j++){
		int res = abs(a[j] - b[j]);
//		printf("%d = abs(%d - %d)\n",res, a[j], b[j]);
		(res > 5)? move+= 10 - res:move += res;
	}
//	printf("TotalMove = %d\n", move);
//	puts("");
	return move;
}

int main(){
	int testCase;
	scanf("%d", &testCase);
	
	for(int _ = 0; _ < testCase; _++){
		priority_queue<Edge, vector<Edge>, Comparator> pq;
		int totalNode;
		int totalMove = 0;
		char lock[505][5];
		char start[5] = {"0000"};
		
		//Set parent to itself
		int parent[505];
		for(int i = 0; i < 505; i++){
			parent[i] = i;
		}
		
		//Get total node
		scanf("%d", &totalNode);
		
		//Loop for each node, get the lock
		for(int i = 0; i < totalNode; i++){
			scanf("%s", lock[i]);
		}
		
		//Calculate minimal distance between lock and start
		int min = 10000;
		for(int i = 0; i < totalNode; i++){
			int move = countMoves(lock[i], start);
//			for(int j = 0; j < 4; j++){
//				int res = abs(lock[i][j] - start[j]);
//				printf("%d = abs(%d - %d)\n",res, lock[i][j], start[j]);
//				if(res > 5) move += 10 - res;
//				else move += res;
//			}
			if(move < min) min = move;
		}
		totalMove+=min;
//		printf("%d", totalMove);
		
		//Calculate distance from and to each node
		for(int i = 0; i < totalNode; i++){
			for(int j = i+1; j < totalNode; j++){
				pq.push(newEdge(i,j,countMoves(lock[i],lock[j])));
			}
		}
		
		//Kruskal
		while(!pq.empty()){
			Edge edge = pq.top();
			int src = edge.source;
			int dst = edge.destination;
			double cost = edge.cost;
			pq.pop();
			
			if(getParent(parent, src) != getParent(parent, dst)){
				parent[getParent(parent, src)] = getParent(parent, dst);
				totalMove+=cost;
			}
		}
		printf("%d\n", totalMove);
		
//		Print
//		while(!pq.empty()){
//			Edge curr = pq.top();
//			pq.pop();
//			printf("Edge[%d][%d]: %d\n", curr.source, curr.destination, curr.cost);
//		}
	}
	
	return 0;
}
