#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<pthread.h>
#include<unistd.h>
#include<sched.h>
#define NUM_THREADS 10

//mutex is declared globally
pthread_mutex_t count_mtx;

/*
--> Drone is defined as a struct which contains its separate id, state, symbol(for this project we assume that all drones are represented by '+'), home coordinates and destination coordinates
*/
typedef struct{
	int did;
	bool state;
	char sym;
	int hx;
	int hy;
	int dx;
	int dy;

} Drone;
//mat as a matrix of characters represents the map on which the drones are moving
char mat[50][50];
//10 Drones are individually declared globally
Drone drone;
Drone drone1;
Drone drone2;
Drone drone3;
Drone drone4;
Drone drone5;
Drone drone6;
Drone drone7;
Drone drone8;
Drone drone9;
/*
--> printMap is a void functions that upon every drone movements prints the whole matrix to visually show the drone movement. It individually symbolizes the home and destination position as H and D so that these positions symbol remain constant. This process is placed under mutex lock and unlock so that only one thread is able to access this at one time. 
*/
void printMap(){
	
	int i,j;
	mat[drone.hx][drone.hy]='H';
	mat[drone1.hx][drone1.hy]='H';
	mat[drone2.hx][drone2.hy]='H';
	mat[drone3.hx][drone3.hy]='H';
	mat[drone4.hx][drone4.hy]='H';
	mat[drone5.hx][drone5.hy]='H';
	mat[drone6.hx][drone6.hy]='H';
	mat[drone7.hx][drone7.hy]='H';
	mat[drone8.hx][drone8.hy]='H';
	mat[drone9.hx][drone9.hy]='H';
	mat[drone.dx][drone.dy]='D';
	mat[drone1.dx][drone1.dy]='D';
	mat[drone2.dx][drone2.dy]='D';
	mat[drone3.dx][drone3.dy]='D';
	mat[drone4.dx][drone4.dy]='D';
	mat[drone5.dx][drone5.dy]='D';
	mat[drone6.dx][drone6.dy]='D';
	mat[drone7.dx][drone7.dy]='D';
	mat[drone8.dx][drone8.dy]='D';
	mat[drone9.dx][drone9.dy]='D';

	pthread_mutex_lock(&count_mtx);
	for(i=1;i<=50;i++){
		for(j=1;j<=50;j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
	pthread_mutex_unlock(&count_mtx);

}
/*
--> isOpen is a fuction to check obstacles, drones or boundary that may come in the drones path and it will return true and false depending on the case where the drone next position is available or not
*/
bool isOpen(int x, int y){

	if((x<50 || x>1)&&(y<50 || y>1)&&(mat[x][y]!='+')&&(mat[x][y]!='!')&&(mat[x][y]!='&')){
		return true;
	}
//	if(mat[x][y]=='+'){
//		sleep(1);
//		isOpen(x,y);
//	}
	return false;
}

/*
--> signalD is a void function to signal collision happening at a point. It takes as parameters the position at which the collision happens. It is used instead of avoidCollision function to see the collision signal 
*/
void signalD(int i, int j){
	pthread_mutex_lock(&count_mtx);
	mat[i][j]='&';
	pthread_mutex_unlock(&count_mtx);
	sleep(1);
	system("clear");
	printMap();
//	pthread_mutex_lock(&count_mtx);
//	mat[i][j]='&';
//	pthread_mutex_unlock(&count_mtx);
}

/*
--> avoidCollision is a void function whose primary task is to avoid collision if an obstacle comes in front of it. The way it do this is that it checks whether the next block of space in matrix is open or not by isOpen function. If the space is not open it moves accordingly in horizontal or vertical direction just to avoid collision. For example: if the drone is at position (x,y) and it has to move to (x,y+1) but that space is occupied, so it checks whether (x-1,y) is open or not. If its open then it moves to (x-1,y)->(x-1,y+1)->(x-1,y+2)->(x,y+1) which succesfully avoids the collision. If not, it checks for (x+1,y) and then accordingly move to avoid collision.  
*/
void avoidCollision(int i, int j, int x, int y){
	char s;
	s='+';
	//for the case where the home position vertical coordinate is less than destination position vertical coordinate
	if(j<y){
			//check if the block of space upwards is open or not
			if(isOpen(i-1,j)==true){
					//move vertical upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	
					
					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move vertical downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	
					
			}else{
					//if block of space upwards is not open, move vertically downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	
					
					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move vertical upwards one time 
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	
				
			}	
		//successfully avoided collision!
		return;				
	}
	//for the case where the home position vertical coordinate is more than destination position vertical coordinate
	if(j>y){
			//check if the block of space upwards is open or not
			if(isOpen(i-1,j)==true){
					//move vertically upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;	
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	

					//move horizonal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move vertically downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	
	
			}else{
					//if block of space upwards is not open move vertically downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;	
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	

					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move vertically upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	
						
			}
		//collision succesfully avoided!
		return;
	}
	//for the case where the home position horizontal coordinate is less than destination position horizontal coordinate 
	if(i<x){
			//check if the block of space on the left is open or not
			if(isOpen(i,j-1)==true){
					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move vertical downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	

					//move vertical downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;

					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;

			}else{
					//if the block of space on left is not open move right
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move vertical downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;	

					//move vertical downwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i+1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i++;

					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;
				
			}
		//succesfully avoided collision!
		return;
	
	}
	//for the case where the home position horizontal coordinate is more than destination position horizontal coordinate 
	if(i>x){
				//check if the block of space on the right is open or not
				if(isOpen(i,j+1)==true){
					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

					//move vertical upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	

					//move vertical upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	

					//move horizontal left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

				}else{
					//if the block of space on right is not open move left one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j-1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j--;	

					//move vertical upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	

					//move vertically upwards one time
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i-1][j]=' ';
					pthread_mutex_unlock(&count_mtx);
					i--;	

					//move horizontal right one time
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=s;
					pthread_mutex_unlock(&count_mtx);
					system("clear");
					printMap();
					sleep(1);
					pthread_mutex_lock(&count_mtx);
					mat[i][j+1]=' ';
					pthread_mutex_unlock(&count_mtx);
					j++;	

			}
		//successfully avoided collision!
		return;
	}

}
/*
--> moveDrone is a function representing the navigation of the drone. It takes as parameters the home coordinates and the destination coordintes. Following the manhattan distance, the drone can only move horizontally or vertically. Also the drone is first made to cover the horizontal distance, i.e., it moves until the vertical coordinates of drone and destination are equal and then it tends to move vertically upwards or downwards until it reaches the destination.
*/
void moveDrone(int i, int j, int x, int y){
	char s;
	s='+';
	//while the vertical coordinates of drone and destination are not equal
	while(j!=y){
		//for the case where the drone position vertical coordinate is less than destination postion vertical coordinate 
		if((j<y)){
			//check if the block of space on the right is open or not
			if(isOpen(i,j+1)==true){	
				//move right one time
				pthread_mutex_lock(&count_mtx);
				mat[i][j+1]=s; 
				pthread_mutex_unlock(&count_mtx);
				//sleep(1);
				system("clear");
				printMap();
				sleep(1);
				pthread_mutex_lock(&count_mtx);
				mat[i][j+1]=' ';
				pthread_mutex_unlock(&count_mtx);
				j++;

			}else{
				//if space on the right is occupied avoid collision or signal collision taking place 
				avoidCollision(i,j,x,y);
			//	signalD(i,j+1);
				j=j+2;
			}
					
		}
		//for the case where the drone position vertical coordinate is more than destination position vertical coordinate
		if((j>y)){
			//check if the block of space on the left is open or not
			if(isOpen(i,j-1)==true){
				//move left one time
				pthread_mutex_lock(&count_mtx);
				mat[i][j-1]=s;
				pthread_mutex_unlock(&count_mtx);
				//sleep(1);
				system("clear");
				printMap();
				sleep(1);
				pthread_mutex_lock(&count_mtx);
				mat[i][j-1]=' ';
				pthread_mutex_unlock(&count_mtx);
				j--;

			}else{
				//if the space on the left is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	signalD(i,j-1);
				j=j-2;
			}
		}
	}
	//while the horizontal coordinates of the drone and destination are not equal
	while(i!=x){
		//for the case where the drone position horizontal coordinate is less than destination position horizontal coordinate
		if((i<x)){
			//check if the block of space downwards is open or not
			if(isOpen(i+1,j)==true){
				//move downwards one time
				pthread_mutex_lock(&count_mtx);
				mat[i+1][j]=s;	
				pthread_mutex_unlock(&count_mtx);
				//sleep(1);
				system("clear");
				printMap();
				sleep(1);
				pthread_mutex_lock(&count_mtx);
				mat[i+1][j]=' ';
				pthread_mutex_unlock(&count_mtx);
				i++;

			}else{
				//if the space downwards is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	signalD(i+1,j);
				i=i+2;
			}
		}	
		//for the case where the drone position horizontal coordinate is more than destination position horizontal coordinate
		if((i>x)){
			//check if the block of space upwards is open or not
			if(isOpen(i-1,j)==true){
				//move upwards one time
				pthread_mutex_lock(&count_mtx);
				mat[i-1][j]=s;
				pthread_mutex_unlock(&count_mtx);
				//sleep(1);
				system("clear");
				printMap();
				sleep(1);
				pthread_mutex_lock(&count_mtx);
				mat[i-1][j]=' ';
				pthread_mutex_unlock(&count_mtx);
				i--;

			}else{
				//if the space upwards is occupied avoid collision or signal collision taking place
				avoidCollision(i,j,x,y);
			//	signalD(i-1,j);
				i=i-2;
			}
		}
	}

}
/*
--> fillMap is a function that task is to fill the construct the matrix representing map and fill it with spaces for open space and x to represent boundaries. The number of obstacles to be placed in the map can be defined here. This method is called by each drone upon their takeoff. 
*/
void fillMap(int a, int b, int x, int y){
	
	pthread_mutex_lock(&count_mtx);
	int i,j;
	for(i=1;i<=50;i++){
		for(j=1;j<=50;j++){
		
			if(i!=50 && i!=1 && j !=50 && j!=1){
				mat[i][j]=' ';
			}else{
				mat[i][j]='x';
			}
		
		}
	
	}
	
	mat[14][9]='!';
	mat[28][39]='!';
	pthread_mutex_unlock(&count_mtx);
	//the moveDrone or navigation method is called here 2 times for the drone to first move from home to destination and then back to home
	moveDrone(a,b,x,y);
	moveDrone(x,y,a,b);
}
/*
--> printDrone fnction is called by each thread, i.e., drone. These function is similar to takeoff function generally defined for a drone. The home and destination points of the drones are specified over here. The function for the map construction(fillMap) is called by each drone individually 
*/
void *printDroneX(void *threadid){
	drone.hx=25;
	drone.hy=25;
	drone.dx=9;
	drone.dy=9;
	drone1.hx=25;
	drone1.hy=25;
	drone1.dx=9;
	drone1.dy=9;
	drone2.hx=25;
	drone2.hy=25;
	drone2.dx=39;
	drone2.dy=39;
	drone3.hx=25;
	drone3.hy=25;
	drone3.dx=39;
	drone3.dy=39;
	drone4.hx=25;
	drone4.hy=25;
	drone4.dx=9;
	drone4.dy=39;
	drone5.hx=25;
	drone5.hy=25;
	drone5.dx=9;
	drone5.dy=39;
	drone6.hx=25;
	drone6.hy=25;
	drone6.dx=39;
	drone6.dy=39;
	drone7.hx=25;
	drone7.hy=25;
	drone7.dx=39;
	drone7.dy=9;
	drone8.hx=25;
	drone8.hy=25;
	drone8.dx=39;
	drone8.dy=9;
	drone9.hx=25;
	drone9.hy=25;
	drone9.dx=39;
	drone9.dy=9;


	long tid;
	tid = (long)threadid;
	if(tid==0){
		fillMap(drone.hx, drone.hy, drone.dx, drone.dy);
	}
	if(tid==1){
		fillMap(drone1.hx, drone1.hy, drone1.dx, drone1.dy);
	}
	if(tid==2){
		fillMap(drone2.hx, drone2.hy, drone2.dx, drone2.dy);
	}
	if(tid==3){
		fillMap(drone3.hx, drone3.hy, drone3.dx, drone3.dy);
	}
	if(tid==4){
		fillMap(drone4.hx, drone4.hy, drone4.dx, drone4.dy);
	}
	if(tid==5){
		fillMap(drone5.hx, drone5.hy, drone5.dx, drone5.dy);
	}
	if(tid==6){
		fillMap(drone6.hx, drone6.hy, drone6.dx, drone6.dy);
	}
	if(tid==7){
		fillMap(drone7.hx, drone7.hy, drone7.dx, drone7.dy);
	}
	if(tid==8){
		fillMap(drone8.hx, drone8.hy, drone8.dx, drone8.dy);
	}
	if(tid==9){
		fillMap(drone9.hx, drone9.hy, drone9.dx, drone9.dy);
	}
	pthread_exit(NULL);
}
/*
--> main function is used to launch the program. All the threads are defined over here. 
*/
int main(){

	pthread_t threads[NUM_THREADS];
	int rc;
	long t=0;
	long t1=1;
	long t2=2;
	long t3=3;
	long t4=4;
	long t5=5;
	long t6=6;
	long t7=7;
	long t8=8;
	long t9=9;

	void *status;
	pthread_attr_t attr;

	pthread_mutex_init(&count_mtx,NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	int i;
	for(t=0; t<NUM_THREADS;t++){
		pthread_create(&threads[t],NULL,printDroneX,(void *)t);
		sleep(2);
	}
		pthread_attr_destroy(&attr);
//		int i;
		for(i=0;i<NUM_THREADS;i++){
			pthread_join(threads[i],&status);
		}
	pthread_mutex_destroy(&count_mtx);
	pthread_exit(NULL);

}
