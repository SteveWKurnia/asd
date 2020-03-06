#include<stdio.h>
#include<math.h>
#include<vector>
#include<queue>
using namespace std;

struct Coordinate{
	double x,y;
};
struct Edge{
	int source, destination;
	double cost;
};
struct Comparator{
	bool operator()(Edge const& e1, Edge const& e2){
        return e1.cost > e2.cost;
    } 
};

Coordinate newCoord(double x, double y){
	Coordinate coord;
	coord.x = x;
	coord.y = y;
	
	return coord;
}
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
	
	priority_queue<Edge, vector<Edge>, Comparator> pq;
	int parent[105];
	for(int i = 0; i < 100; i++){
		parent[i] = i;
	}
	
	int totalNode;
	scanf("%d", &totalNode);
	
	vector<Coordinate> v;
	for(int i = 0; i < totalNode; i++){
		double x,y;
		scanf("%lf %lf", &x, &y);
		v.push_back(newCoord(x,y));
	}
	
	for(int i = 0; i < totalNode; i++){
		for(int j = i+1; j < totalNode; j++){
			double cst;
			if(v.at(i).x == v.at(j).x){
				(v.at(i).y > v.at(j).y)?cst=v.at(i).y - v.at(j).y:cst=v.at(j).y - v.at(i).y;
			}else if(v.at(i).y == v.at(j).y){
				(v.at(i).x > v.at(j).x)?cst=v.at(i).x - v.at(j).x:cst=v.at(j).x - v.at(i).x;
			}else{
				double vert, hori;
				(v.at(i).x > v.at(j).x)?vert=v.at(i).x - v.at(j).x:vert=v.at(j).x - v.at(i).x;
				(v.at(i).y > v.at(j).y)?hori=v.at(i).y - v.at(j).y:hori=v.at(j).y - v.at(i).y;
				cst = sqrt(pow(vert,2)+pow(hori,2));
			}
			pq.push(newEdge(i,j,cst));
		}
	}
	
	//Kruskal
	double minimalCost=0;
	while(!pq.empty()){
		Edge edge = pq.top();
		int src = edge.source;
		int dst = edge.destination;
		double cost = edge.cost;
		pq.pop();
		
		if(getParent(parent, src) != getParent(parent, dst)){
			parent[getParent(parent, src)] = getParent(parent, dst);
			minimalCost+=cost;
		}
	}
	
	printf("%.2lf", minimalCost);
	
	
	//Print
//	while(!pq.empty()){
//		Edge curr = pq.top();
//		pq.pop();
//		printf("Edge[%d][%d]: %.2lf\n", curr.source, curr.destination, curr.cost);
//	}
	
	return 0;
}
