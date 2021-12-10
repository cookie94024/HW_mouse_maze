#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include<fstream>
using namespace std;

//定義矩陣大小 
#define M 12
#define N 12


//宣告結構 
typedef struct
{
	int x;
	int y;
	int dir; //方向變數 dir=0(上),dir=1(右),dir=2(下),dir=3(左) 
}Pos;//x,y座標 

//宣告一些變數
int x, y;//起點變數，主程式內需給值
int Fx, Fy; //終點變數，主程式內需給值 
int m = M, n = N; //存入矩陣大小 

/*
想要實作的函式 
isabletoreach
printMaze
printPath
*/

//判斷是否可到達的函式，引數(起點x,起點y, 迷宮陣列) 
bool isAbleToReach(int i, int j, int Fx, int Fy, int maze[M][N], int path[M][N], int pathDraw[M][N]){
	
	stack<Pos> s;
	
	//宣告初始值 
	Pos current;
	current.x = i;
	current.y = j;
	current.dir = 0;
	path[i][j] = 2;
	//起點存入stack 
	s.push(current);
	
	while(!(s.empty())){
		
		//拿出現在位置
		current = s.top();
		i = current.x;
		j = current.y; 
		int d = current.dir; //更新方向 
		
		/* 
		* debug用，印出所有走過的座標 
		cout<<current.x<<",";
		cout<<current.y<<",";
		cout<<current.dir<<"\n";
		cout<<"d="<<d<<"\n";
		*/
		
		current.dir++;
		s.pop();
		s.push(current);
		if(i == Fx && j == Fy){
			
			//存最後路徑
			while(!(s.empty())){
				pathDraw[s.top().x][s.top().y] = 2;
				s.pop();
			} 
			return true; //若到達終點，回傳true 
		}
		
		//開始確認方向
		//往上 
		if(d == 0){
			if( i-1 >= 0 && maze[i-1][j] == 0 && path[i-1][j] == 0 ){
				//若都可以走，則為下一步，記錄下來。 
				Pos next;
				next.x = i-1;
				next.y = j;
				next.dir = 0;
				path[i-1][j] = 2; //記錄路徑
				s.push(next); //存進stack，下一個loop存進current 
			}
		}
		//往右 
		else if (d == 1){
			if( j+1 < n && maze[i][j+1] == 0 && path[i][j+1] == 0){
				Pos next;
				next.x = i;
				next.y = j+1;
				next.dir = 0;
				path[i][j+1] = 2;
				s.push(next);
			}
		}
		//往下
		else if (d == 2){
			if( i+1 < m && maze[i+1][j] == 0 && path[i+1][j] == 0){
				Pos next;
				next.x = i+1;
				next.y = j;
				next.dir = 0;
				path[i+1][j] = 2;
				s.push(next); 
			}
		} 
		//往左
		else if(d == 3){
			if( j-1 >= 0 && maze[i][j-1] == 0 && path[i][j-1] == 0 ){
				//若都可以走，則為下一步，記錄下來。 
				Pos next;
				next.x = i;
				next.y = j-1;
				next.dir = 0;
				path[i][j-1] = 2; //記錄路徑
				s.push(next); //存進stack，下一個loop存進current 
			}
		}
		//若都不符合，代表死路回頭 
		else{
			s.pop();//回到上一點 
		}
		
	}
	return false;
}

void printMaze(int array[M][N]){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(array[i][j] == 1){
				cout<<"█";
			}
			else if (array[i][j] == 0){
				cout<<"  ";
			}
		}
		cout<<"\n";
	}
}

/*
* debug用，印出陣列 
void printArray(int array[M][N]){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			cout<< array[i][j];
		}
		cout<<"\n";
	}
}
*/

void printPath(int maze[M][N], int pathDraw[M][N]){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(maze[i][j] == 1){
				cout<<"█";
			}
			else if (maze[i][j] == 0){
				if(pathDraw[i][j] == 2){
					cout<<"◇";
				}
				else{
					cout<<"  ";
				}
			}
		}
		cout<<"\n";
	}
}

int main(void)
{
	int i = 1;
	int j = 1;
	int Fx = 10;
	int Fy = 10;
	int path[M][N] = {0};
	int pathDraw[M][N] = {0};
	int maze[M][N] = {  { 1,1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,1,1,1,1,0,1,1,1,1 },
						{ 1,1,0,0,0,1,1,0,1,0,1,1 },
						{ 1,1,1,1,0,0,0,0,1,0,1,1 },
						{ 1,0,0,0,1,1,1,0,1,0,1,1 },
						{ 1,1,1,0,1,0,0,0,0,0,1,1 },
						{ 1,1,1,0,1,0,1,1,1,1,1,1 },
						{ 1,1,1,0,1,0,1,0,0,0,0,1 },
						{ 1,0,0,0,0,0,1,0,1,1,1,1 },
						{ 1,1,1,0,1,0,0,0,1,1,1,1 },
						{ 1,0,0,0,0,1,1,0,0,0,0,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1 } };
	
	bool passMaze = isAbleToReach(i, j, Fx, Fy, maze, path, pathDraw);

	cout<<"迷宮圖\n";
	printMaze(maze);
	cout<<"\n";
	cout<<"所有走過的路徑\n";
	printPath(maze, path);
	cout<<"\n";
	cout<<"到終點的路徑\n";
	printPath(maze, pathDraw);

	
	if(passMaze){
		cout<< "Success!";
	}else{
		cout<< "fail QQ";
	}
	
	
	/*
	被擋住的迷宮(走不出去) 
	int maze[M][N] = {  { 1,1,1,1,1,1,1,1,1,1,1,1 },
						{ 1,0,0,1,1,1,1,0,1,1,1,1 },
						{ 1,1,0,0,0,1,1,0,1,0,1,1 },
						{ 1,1,1,1,0,0,0,0,1,0,1,1 },
						{ 1,0,0,0,1,1,1,0,1,0,1,1 },
						{ 1,1,1,0,1,0,0,0,0,0,1,1 },
						{ 1,1,1,0,1,0,1,1,1,1,1,1 },
						{ 1,1,1,0,1,0,1,0,0,0,0,1 },
						{ 1,0,0,0,0,0,1,0,1,1,1,1 },
						{ 1,1,1,0,1,0,1,0,1,1,1,1 },
						{ 1,0,0,0,0,1,1,0,0,0,0,1 },
						{ 1,1,1,1,1,1,1,1,1,1,1,1 } };
	*/
}
