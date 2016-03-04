# Drone-Collision-Avoidance-System
Drone Collision Avoidance System (DCAS)
Objective:
• Design, implement and test real-time software “DCAS”.
• Use a GPS-based algorithm to check for obstacles and avoid collision.
• Implement the code for multiple drones using pthreads.
• Implement state diagrams and transition tables for better understanding
of the project.
Design:
As stated in the grading rubric this project needs to be divided into 3 levels for proper step by step implementation.
For my design part following are the steps that I took initially before designing any level:
• The Drone is defined as a struct which has its own symbol, id, state, home and destination coordinates. For this project, I did not take in account the id and symbol was set as ‘+’ for all drones.
• The path on which the drone will move, i.e., map is represented by matrix of characters (50 by 50). The open space where drone can move freely is represented by ‘ ‘ and the boundaries are represented by ‘x’. The obstacles that will be placed later on are symbolized by ‘!’.
• Each drone is created by a separate thread which executes a separate function. Separate mutex locks and unlocks are used so that only one drone can access the map at one time.
Functions defined in code:
• int main(): as the name suggests, it is the main function that is first
executed when the program runs. This function creates 10 pthreads for 10 drones that executes their separate functions. This function can also be said as home base where all the drones are stored and waiting.
• void printDroneX(void *threadid): This function represents the takeoff for each drone(10 drones). In this function, the id of each thread is taken as an input which can be used to set particular symbols to each drone. Although I set each drone symbol separately, while playing the code I used the character ‘+’ to represent each drone. In this function drone’s home and destination coordinates can be hard coded.
• void fillMap(int a, int b, int x, int y): This function fills the matrix (map) on which the drone will move with ‘ ’ and ‘x’. All the drones executes this function. In this function, obstacle position can be hard coded to check the collision avoidance.
• void moveDrone(int i, int j, int x, int y): This function can also be called navigation function. The points i and j represents home coordinates and x and y destination coordinates. Keeping in mind that the drone can only move horizontal and vertical(manhattan distance), the drone is made to move until the drone and the destination are in same column, i.e., it only moves horizontally. After this the drone can either move vertically up or down to reach destination. While executing, it checks every time whether the space drone is going to move is occupied or not. According to grader wish, collision check or collision signal check can be done here. This
function is executed 2 times for drone to first reach destination and then
back to home.
• void avoidCollision(int i, int j, int x, int y): Upon call, this function is used
to avoid collision if the space the drone is going to move to is occupied. The drone can avoid collision by moving in vertical or horizontal path and after execution of this function the drone returns to its original path after avoiding collision.
• bool isOpen(int x, int y): This function’s task is to check whether the position on matrix at (x,y) is occupied or not. If it is occupied, then function returns false or true otherwise.
• void signalD(int i, int j): This function’s task is to signal if the collision happens at any point. It takes as parameters the position where the drone is going to collide with the obstacle, i.e., the obstacle position or drone collision among one another. If collision takes place, that point is symbolized by ‘&’.
State Diagram:
DL: Drone Launched
NSC: Navigate and signal collision NAC: Navigate and avoid collision ND: Navigate to destination
NH: Navigate to home
How to run code:
The project is divided into 3 levels. My code consists of all the levels in the same code.
For changing drone’s home and destination coordinates:
￼
The printDroneX() function is defined from lines 675 to 751. Change the drone.hx and drone.hy values to change home coordinates and drone.dx and drone.dy to change destination coordinates.
For putting more obstacles in the map at different positions:
Go to the fillMap() function that is common for all drone defined from lines 648 to 671. In this function at lines 665 and 666, change the (x,y) values in mat[x][y]=’!’. You can also write more of these to increase obstacles.
If you run the submitted executable without changing anything other than home or destination coordinates, then that is the final stage comprising of all levels.
Level 0: To run this level, go to line 7 in the drone.c file and change the NUM_THREADS from 10 to 1 which will show movement of one drone. Run make and then executable to play level 0.
Level 1a and 1b: To run these levels, go to line 7 in drone.c file and change NUM_THREADS value to 10. We now have 10 threads representing 10 drones individually. Comment out the obstacles at line 665 and 666 to play level 1a and uncomment them to play level 1b.
Level 2: (a) To show the collision signal, comment the avoidCollision function in moveDrone() function at line 561, 586, 613 and 637. Uncomment the signalD() function call at line 562, 587, 614 and 638. The collision happening on map are represented by ‘&’.
(b) To show the collision avoidance, uncomment the avoidCollision function in moveDrone() function at line 561, 586, 613 and 637. Comment the signalD() function call at line 562, 587, 614 and 638.The file that was initially submitted represents this level. For this don’t do any change to the code (except if you want to change home and destination address or obstacles). The code that was submitted when played will represent this level.
