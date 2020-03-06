#include<stdio.h>
#include <stack> 
#include <stdlib.h>
using namespace std;

struct Point{
	long long x, y;
};

Point newPoint(long long x, long long y){
	Point p;
	p.x = x;
	p.y = y;
	return p;
}

Point p0;
Point nextToTop(stack<Point> &S) 
{ 
    Point p = S.top(); 
    S.pop(); 
    Point res = S.top(); 
    S.push(p); 
    return res; 
} 

int swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
long long distSq(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
          (p1.y - p2.y)*(p1.y - p2.y); 
} 

int orientation(Point p, Point q, Point r) 
{ 
    long long val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // 1 for clockwise, 2 for counter clockwise 
} 
  
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 

void convexHull(Point points[], int totalPoint){
	
	//Find the bottom most or bottom left most point
//	int yMin = points[0].y
	int xMin = points[0].x, min = 0;
	for(int i = 1; i < totalPoint; i++){
//		int yCurr = points[i].y;
//		
//		if(		(yCurr < yMin) // Bottommost point
//			|| 	(yMin == yCurr && points[i].x < points[min].x) // Leftmost point
//			){
//			yMin = points[i].y;
//			min = i;
//		}
		int xCurr = points[i].x;
		
		if(		(xCurr < xMin) // Leftmost point
			|| 	(xMin == xCurr && points[i].y < points[min].y) // Bottommost point
			){
			xMin = points[i].x;
			min = i;
		}
	}
	
	//Swap the first element with the bottomleft most element
	swap(points[0],points[min]);
	
	//Sort according to p0 angle
	p0 = points[0];
	qsort(&points[1], totalPoint-1, sizeof(Point), compare);
	
	//Sort colinear
	int i = totalPoint - 2;
	Point point1 = points[0];
	Point point2 = points[totalPoint-1];
	while(i >= 0 && orientation(point1,point2,points[i]) == 0){
		i--;
	}
	for(int j = i+1, h = totalPoint - 1; j < h; j++, h--){
		Point temp = points[j];
		points[j] = points[h];
		points[h] = temp;
	}
	
	printf("%d\n", totalPoint);
	for(int i = 0; i < totalPoint; i++){
		printf("%lld %lld\n", points[i].x, points[i].y);
	}
}
Point points[100005];
int main(){
	
	int testCase;
	scanf("%d", &testCase);
	
	for(int _ = 0; _ < testCase; _++){
		int totalPoints;
		scanf("%d", &totalPoints);
//		Point points[totalPoints+5];
		
		long long x,y;
		char cHull;
		int pointCounter = 0;
		
		//Sort and find bottom left point
		for(int i = 0; i < totalPoints; i++){
			scanf("%lld %lld %c", &x, &y, &cHull);
			if(cHull == 'Y'){
				points[pointCounter] = newPoint(x,y);
				pointCounter++;
			}
		}
		
		convexHull(points, pointCounter);
	}
	
	return 0;
}
