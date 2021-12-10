#include <iostream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include<fstream>
using namespace std;

//�w�q�x�}�j�p 
#define M 12
#define N 12


//�ŧi���c 
typedef struct
{
	int x;
	int y;
	int dir; //��V�ܼ� dir=0(�W),dir=1(�k),dir=2(�U),dir=3(��) 
}Pos;//x,y�y�� 

//�ŧi�@���ܼ�
int x, y;//�_�I�ܼơA�D�{�����ݵ���
int Fx, Fy; //���I�ܼơA�D�{�����ݵ��� 
int m = M, n = N; //�s�J�x�}�j�p 

/*
�Q�n��@���禡 
isabletoreach
printMaze
printPath
*/

//�P�_�O�_�i��F���禡�A�޼�(�_�Ix,�_�Iy, �g�c�}�C) 
bool isAbleToReach(int i, int j, int Fx, int Fy, int maze[M][N], int path[M][N], int pathDraw[M][N]){
	
	stack<Pos> s;
	
	//�ŧi��l�� 
	Pos current;
	current.x = i;
	current.y = j;
	current.dir = 0;
	path[i][j] = 2;
	//�_�I�s�Jstack 
	s.push(current);
	
	while(!(s.empty())){
		
		//���X�{�b��m
		current = s.top();
		i = current.x;
		j = current.y; 
		int d = current.dir; //��s��V 
		
		/* 
		* debug�ΡA�L�X�Ҧ����L���y�� 
		cout<<current.x<<",";
		cout<<current.y<<",";
		cout<<current.dir<<"\n";
		cout<<"d="<<d<<"\n";
		*/
		
		current.dir++;
		s.pop();
		s.push(current);
		if(i == Fx && j == Fy){
			
			//�s�̫���|
			while(!(s.empty())){
				pathDraw[s.top().x][s.top().y] = 2;
				s.pop();
			} 
			return true; //�Y��F���I�A�^��true 
		}
		
		//�}�l�T�{��V
		//���W 
		if(d == 0){
			if( i-1 >= 0 && maze[i-1][j] == 0 && path[i-1][j] == 0 ){
				//�Y���i�H���A�h���U�@�B�A�O���U�ӡC 
				Pos next;
				next.x = i-1;
				next.y = j;
				next.dir = 0;
				path[i-1][j] = 2; //�O�����|
				s.push(next); //�s�istack�A�U�@��loop�s�icurrent 
			}
		}
		//���k 
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
		//���U
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
		//����
		else if(d == 3){
			if( j-1 >= 0 && maze[i][j-1] == 0 && path[i][j-1] == 0 ){
				//�Y���i�H���A�h���U�@�B�A�O���U�ӡC 
				Pos next;
				next.x = i;
				next.y = j-1;
				next.dir = 0;
				path[i][j-1] = 2; //�O�����|
				s.push(next); //�s�istack�A�U�@��loop�s�icurrent 
			}
		}
		//�Y�����ŦX�A�N�����^�Y 
		else{
			s.pop();//�^��W�@�I 
		}
		
	}
	return false;
}

void printMaze(int array[M][N]){
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			if(array[i][j] == 1){
				cout<<"�i";
			}
			else if (array[i][j] == 0){
				cout<<"  ";
			}
		}
		cout<<"\n";
	}
}

/*
* debug�ΡA�L�X�}�C 
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
				cout<<"�i";
			}
			else if (maze[i][j] == 0){
				if(pathDraw[i][j] == 2){
					cout<<"��";
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

	cout<<"�g�c��\n";
	printMaze(maze);
	cout<<"\n";
	cout<<"�Ҧ����L�����|\n";
	printPath(maze, path);
	cout<<"\n";
	cout<<"����I�����|\n";
	printPath(maze, pathDraw);

	
	if(passMaze){
		cout<< "Success!";
	}else{
		cout<< "fail QQ";
	}
	
	
	/*
	�Q�צ��g�c(�����X�h) 
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
