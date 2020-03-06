#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
using namespace std;

struct Edge{
	int source, dest, cost;
};

//Sort ascending
struct Comparator{
	bool operator()(Edge const& e1, Edge const& e2){
        return e1.cost > e2.cost;
    } 
};

int getParent(int parent[], int current){
		if(parent[current] != current){
			return parent[current] = getParent(parent, parent[current]);
		}
		
		return parent[current];
}

Edge newEdge(int source, int dest, int cost){
	Edge curr;
	curr.cost = cost;
	curr.dest = dest;
	curr.source = source;
	
	return curr;
}

int main(){
	
	while(true){
		priority_queue<Edge, vector<Edge>, Comparator> pq;
		int totalNode, totalEdge, totalUsage = 0;
		int parent[200000];
		scanf("%d %d", &totalNode, &totalEdge);
		
		if(totalEdge == 0 && totalNode == 0)break;
		
		//Init parent for each element to be the parent of itself
		for(int i = 0; i < totalNode; i++){
			parent[i] = i;
		}
		
		int src, dst, cst;
		for(int i = 0; i < totalEdge; i++){
			scanf("%d %d %d", &src, &dst, &cst);
			pq.push(newEdge(src,dst,cst));
			totalUsage+=cst;
		}
		
		int minimal = 0;
		while(!pq.empty()){
			Edge edge = pq.top();
			int src = edge.source;
			int dst = edge.dest;
			int cst = edge.cost;
			pq.pop();
			
			if(getParent(parent, src) != getParent(parent, dst)){
				parent[getParent(parent, src)] = getParent(parent, dst);
//				printf("Edge[%d][%d]: %d\n", src, dst, cst);
				minimal+=cst;
			}
			
		}
		printf("%d\n", totalUsage-minimal);
	}
	
	//Print
	while(!pq.empty()){
		Edge curr = pq.top();
		pq.pop();
		printf("Edge[%d][%d]: %d\n", curr.source, curr.dest, curr.cost);
	}
	
	return 0;
}
