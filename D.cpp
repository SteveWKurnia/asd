#include<stdio.h>
#include<vector>
#include<queue>
using namespace std;

struct Edge{
	int cost, source, destination;
};
struct Comparator{
	bool operator()(Edge const& e1, Edge const& e2){
        return e1.cost < e2.cost;
    } 
};

Edge newEdge(int src, int dst, double cst){
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

int main(){
	int testCase;
	scanf("%d", &testCase);
	
	for(int _ = 0; _ < testCase; _++){
		priority_queue<Edge, vector<Edge>, Comparator> pq;
		int parent[10005];
		
		for(int i = 0; i < 10000; i++){
			parent[i] = i;
		}
		
		int totalNode, totalEdge;
		scanf("%d %d", &totalNode, &totalEdge);
		
		int cameraCost = 0;
		int src, dst, cst;
		for(int i = 0; i < totalEdge; i++){
			scanf("%d %d %d", &src, &dst, &cst);
			pq.push(newEdge(src,dst,cst));
			cameraCost += cst;
		}
		
		while(!pq.empty()){
			Edge edge = pq.top();
			int src = edge.source;
			int dst = edge.destination;
			double cost = edge.cost;
			pq.pop();
			
			if(getParent(parent, src) != getParent(parent, dst)){
				parent[getParent(parent, src)] = getParent(parent, dst);
				cameraCost-=cost;
			}
		}
		
		printf("%d\n", cameraCost);
	}
	
	return 0;
}
