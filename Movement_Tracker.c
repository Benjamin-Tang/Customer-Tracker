// Benjamin Tang
// ECE 209: Section 001
// Programming Assignment #2
// March 24th, 2016

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Global Variables

int timeTotal[5] = {0,0,0,0,0};
// Array used to store the total time for each individual customer

int flag = 0;
// Variable used to flag whether a customer has left the store or has just recently entered the store

double xnew[5] = {0,0,0,0,0};
// Array used to store incoming x-coordinate of customer

double ynew[5] = {0,0,0,0,0};
// Array used to store incoming y-coordinate of customer

double xold[5] = {0,0,0,0,0};
// Array used to store previous x-coordinate of customer

double yold[5] = {0,0,0,0,0};
// Array used to store previous y-coordinate of customer

double customerDistance[5] = {0,0,0,0,0};
// Array used to store each customer's total distance traveled while in the store

int jeanTime[5] = {0,0,0,0,0};
// Array used to store each customer's total time at jean (zero) display

int tshirtTime[5] = {0,0,0,0,0};
// Array used to store each customer's total time at t-shirt (one) display

int activewearTime[5] = {0,0,0,0,0};
// Array used to store each customer's total time at active wear (two) display

int thirdTime[5] = {0,0,0,0,0};
// Array used to store each customer's total time at three display

int fourthTime[5] = {0,0,0,0,0};
// Array used to store each customer's total time at four display

double jeansPercent[5] = {0,0,0,0,0};
// Array used to store each customer's percent time at jean (zero) display

double tShirtsPercent[5] = {0,0,0,0,0};
// Array used to store each customer's percent time at t-shirt (one) display

double activeWearPercent[5] = {0,0,0,0,0};
// Array used to store each customer's percent time at active wear (two) display

double thirdPercent[5] = {0,0,0,0,0};
// Array used to store each customer's percent time at three display

double fourthPercent[5] = {0,0,0,0,0};
// Array used to store each customer's percent time at four display

int priorClosestDisplay[5] = {0,0,0,0,0};
// Array used to store each customer's display they were previously closest to

int currentClosestDisplay[5] = {0,0,0,0,0};
// Array used to store each customer's display they are currently closest to

int j = 0;
// Variable used as counter in the for loop within the 'getClosestDisplay' function

int j2 = 0;
// Variable used as counter in the for loop within the 'print' function - specifically within the for loop that calculates the percentages at each display

int j3 = 0;
// Variable used as counter in the for loop within the 'print' function - specifically within the for loop that calculates the most popular display

int id = 0;
// Variable used to store customer ID's - is used for retrieving/storing appropriate array values, and as a flag

int indexCounter = 0;
// Variable used to flag whether a closest display has been met

double xDisplayDist = 0;
// Variable used to store current display's x-coordinate

double yDisplayDist = 0;
// Variable used to store current display's y-coordinate

double xTotalDistance = 0;
// Variable used to store distance between customer and display on the x-axis

double yTotalDistance = 0;
// Variable used to store distance between customer and display on the y-axis

double TotalDistance = 0;
// Variable used to store actual distance between customer and display using pythagorean calculation

int idstore = -1;
// Variable used to store previous customer id - mainly used as a flag to tell whether new customer has entered the store while another customer is still present

double jeanTimeTotal = 0;
// Variable used to store all customers' total times at the jean (zero) display

double tshirtTimeTotal = 0;
// Variable used to store all customers' total times at the t-shirt (one) display

double activeWearTimeTotal = 0;
// Variable used to store all customers' total times at the active wear (two) display

double thirdTimeTotal= 0;
// Variable used to store all customers' total times at the three display

double fourthTimeTotal = 0;
// Variable used to store all customers' total times at the four display

double realTimeTotal = 0;
// Variable used to store all customers' total times at all displays

double jeanTimeTotalAvg = 0;
// Variable used to store the average time spent at the jean (zero) display by all customers

double tshirtTimeTotalAvg = 0;
// Variable used to store the average time spent at the t-shirt (one) display by all customers

double activeWearTimeTotalAvg = 0;
// Variable used to store the average time spent at the active wear (two) display by all customers

double thirdTimeTotalAvg = 0;
//Variable used to store the average time spent at the three display by all customers

double fourthTimeTotalAvg = 0;
// Variable used to store the average time spent at the four display by all customers

int ndvidstor = -2;
// Variable used to store the previous customer's ID after a new customer enters the store

#ifndef CODELAB_TESTING

const double ProximityThreshold = 5.0;//ft
// How close does the customer need to be to the display

const int    TimeUnit = 15; //s
// Assumed time between samples

struct display {
  char name[100];
  double x;
  double y;
};
// Struct declaration containing display properties (name, x and y coordinates)

int nDisplays = 3;
// Variable containing the amount of displays in the store

struct display Displays[5] = {
  { .name="Jeans",       .x=10.0, .y=10.0},
  { .name="T-shirts",    .x=1.0, .y=1.0},
  { .name="Active wear", .x=10, .y=1.0},
  { .name="",            .x=-1, .y=-1},
  { .name="",            .x=-1, .y=-1}
};
#endif
// Struct initialization - contains the actual values declared

double distance(double x0, double y0, double x1, double y1) // Distance function that calculates the distance using the Pythagorean calculation
{
	double a = x0 - x1;
	double b = y0 - y1;
	double c = a*a + b*b; 
	
	return sqrt(c);
}


int getClosestDisplay(double x, double y) // function that calculates the closest display to a customer

{	
	j = 0;
	for(j = 0; j < nDisplays; j++)
	{
		xDisplayDist = Displays[j].x; //grabbing value of display x-coord. and storing it to 'xDisplayDist'
		yDisplayDist = Displays[j].y; //grabbing value of display y-coord. and storing it to 'yDisplayDist'
		xTotalDistance = xDisplayDist - x; //calculating distance value between display x-coord. and current customer x-coord.
		yTotalDistance = yDisplayDist - y; //calculating distance value between display y-coord. and current customer y-coord.
		TotalDistance = (xTotalDistance*xTotalDistance) + (yTotalDistance*yTotalDistance); //calculating total distance between the customer and display

		if(sqrt(TotalDistance) < ProximityThreshold) //if the total distance between the customer and display is less than the proximity value, increment index counter
		{
			indexCounter++;
			break;
		}
	}
	if(indexCounter > 0) //if the index counter is greater than 1, return the j value, which is the display that the customer is closest to
		{
		indexCounter = 0;
		return j;
		}
	else{				//if not, return a -1, this signifies that the customer is not within the set proximity value of any display
		indexCounter = 0;
		return -1;
		}

}

void track(int id, double x, double y) //function that tracks the customer in the store - does the bulk of the work in the program
{
	if((x > 0 || y > 0) && (!(x < 0) && !(y < 0))) //if at least one of the coordinates is greater than one, and the other coordinate is non-negative, then proceed
	{
		flag++;  
		if(flag == 1) //signals that the first set of coords. is a customer entering the store
		{	if(idstore != id) //signals that, upon the first flag increment, the previously stored customer ID is different, and therefore should be stored for future retrieval
			{
				ndvidstor = id; //whenever a new customer enters the store, ndvidstor is used to store the last customer's ID that is of a different value
			}
			if(idstore == id) //signals that the previously stored customer ID matches the current customer's ID
			{
				xnew[id] = x; //store the current customer x-coord. to corresponding 'xnew' array value
				ynew[id] = y; //store the current customer y-coord. to corresponding 'ynew' array value
				customerDistance[id] = customerDistance[id] + distance(xold[id], yold[id], xnew[id], ynew[id]); // customer distance is calculated
			}
			idstore = id; //store current customer ID to idstore - this prepares the appropriate checks for the incoming flags at the next track function cycle
			getClosestDisplay(x, y); //calculates the closest display index relative to the customer's location
			currentClosestDisplay[id] = j; //stores the closest display index into the appropriate value within the 'currentClosestDisplay' array
			xold[id] = x; //stores the current x-coord. of the current customer in the appropriate array value in the 'xold' array - prepares for future distance calculations for that customer ID
			yold[id] = y; //stores the current y-coord. of the current customer in the appropriate array value in the 'yold' array - prepares for future distance calculations for that customer ID
		}
		if(idstore != id) //signals that the previously stored customer ID is different, but is not the first flag increment, and therefore goes through a different line of calculations
		{	
			if(ndvidstor == id) //signals that a customer has "returned" (i.e., the same customer ID, before another customer entered, has reappeared)
			{
				timeTotal[id] = timeTotal[id] + TimeUnit; //increment the appropriate customer's net total time in the store - makes up for the time that would be skipped in this cycle
				customerDistance[id] = customerDistance[id] + distance(xold[id], yold[id], x, y); //calculate the distance the customer has moved since the last time the ID has shown
				ndvidstor = -1; //reset the 'ndvidstor' flag
			}
			idstore = id; //store current customer ID to idstore - this prepares the appropriate checks for the incoming flags at the next track function cycle
			timeTotal[id] = timeTotal[id] + TimeUnit; //increment the appropriate customer's net total time in the store
			getClosestDisplay(x, y); //calculates the closest display index relative to the customer's location
			currentClosestDisplay[id] = j; //stores the closest display index into the appropriate value within the 'currentClosestDisplay' array
			if(currentClosestDisplay[id] == 0) //this, and the next four if statements are incrementing the time value of the display the customer was closest to
			{
				jeanTime[id] = jeanTime[id] + TimeUnit;
			}
			if(currentClosestDisplay[id] == 1)
			{
				tshirtTime[id] = tshirtTime[id] + TimeUnit;
			}
			if(currentClosestDisplay[id] == 2)
			{
				activewearTime[id] = activewearTime[id] + TimeUnit;
			}
			if(currentClosestDisplay[id] == 3)
			{
				thirdTime[id] = thirdTime[id] + TimeUnit;
			}		
			if(currentClosestDisplay[id] == 4)
			{
				fourthTime[id] = fourthTime[id] + TimeUnit;
			}		
			flag = 0; // reset the flag to 0 - prepares to go through a different line of calculations on the next run through 
			xold[id] = x; //stores the current x-coord. of the current customer in the appropriate array value in the 'xold' array - prepares for future distance calculations for that customer ID
			yold[id] = y; //stores the current y-coord. of the current customer in the appropriate array value in the 'yold' array - prepares for future distance calculations for that customer ID
			
			return;
		}
		if(flag > 1) //signals that the customer ID has not changed since the first retrieval of coordinates - goes through the "normal" calculations
		{
			getClosestDisplay(x, y);
			priorClosestDisplay[id] = currentClosestDisplay[id]; //stores whatever display index that was in the currentClosestDisplay array into the priorClosestDisplay array
			currentClosestDisplay[id] = j; //stores newly retrieved index into the currentClosestDisplay array
			if(currentClosestDisplay[id] == priorClosestDisplay[id]) //signals that the customer has not moved from the previous display, and so the appropriate customer's display time is incremented
			{
				if(currentClosestDisplay[id] == 0)
				{
					jeanTime[id] = jeanTime[id] + TimeUnit;
				}
				if(currentClosestDisplay[id] == 1)
				{
					tshirtTime[id] = tshirtTime[id] + TimeUnit;
				}
				if(currentClosestDisplay[id] == 2)
				{
					activewearTime[id] = activewearTime[id] + TimeUnit;
				}			
				if(currentClosestDisplay[id] == 3)
				{
					thirdTime[id] = thirdTime[id] + TimeUnit;
				}		
				if(currentClosestDisplay[id] == 4)
				{
					fourthTime[id] = fourthTime[id] + TimeUnit;
				}		
			}
			priorClosestDisplay[id] = currentClosestDisplay[id]; //stores whatever display index that was in the currentClosestDisplay array into the priorClosestDisplay array
			timeTotal[id] = timeTotal[id] + TimeUnit; //the customer's total time spent in the store is incremented
			xnew[id] = x; //the customer's current x-coord is stored in xnew array
			ynew[id] = y; //the customer's current y-coord is stored in ynew array
			customerDistance[id] = customerDistance[id] + distance(xold[id], yold[id], xnew[id], ynew[id]); //the customer's travel distance is calculated
			xold[id] = xnew[id]; //customer's now old x-coords. are moved into the xold array
			yold[id] = ynew[id]; //customer's now old y-coords. are moved into the yold array
			
		}		
	}
	
	else //if none of the conditions are met, the flag is set to zero - signals that the customer has either left the store, or still hasn't entered
	{
		flag = 0;
	}

	return;
}

void print() //function that consolidates all of the gathered data, calculates a few more values, and prints them out 
{
	
	struct customer {
			int ID;			  			  // customer ID
	     	double distance;          	  // feet
  			int    time;                  // seconds
  			double timePerDisplay[5];     // time at each display 
			
      			};
// Struct declaration containing customer properties (ID, distance moved, time in store, time at each display)

	struct customer Customer[5] =   {
			{.ID = 0, .distance=customerDistance[0], .time=timeTotal[0], .timePerDisplay={jeanTime[0],tshirtTime[0],activewearTime[0],thirdTime[0],fourthTime[0]}},
			{.ID = 1, .distance=customerDistance[1], .time=timeTotal[1], .timePerDisplay={jeanTime[1],tshirtTime[1],activewearTime[1],thirdTime[1],fourthTime[1]}},
			{.ID = 2, .distance=customerDistance[2], .time=timeTotal[2], .timePerDisplay={jeanTime[2],tshirtTime[2],activewearTime[2],thirdTime[2],fourthTime[2]}},			
			{.ID = 3, .distance=customerDistance[3], .time=timeTotal[3], .timePerDisplay={jeanTime[3],tshirtTime[3],activewearTime[3],thirdTime[3],fourthTime[3]}},			
			{.ID = 4, .distance=customerDistance[4], .time=timeTotal[4], .timePerDisplay={jeanTime[4],tshirtTime[4],activewearTime[4],thirdTime[4],fourthTime[4]}}							
				};
// Struct initialization - contains the actual values declared

	
for(j2=0;j2<5;j2++) //for loop allows all of the 5 customers' information to be printed easily
		{
		if(Customer[j2].time != 0 && Customer[j2].ID < 6 && Customer[j2].ID >= 0) //makes sure that customers with no store time and that do not have the appropriate IDs do not have any values printed
			{
			if(jeanTime[j2] != 0) //makes sure that only the areas that the customer visited have their percentages calculated
				jeansPercent[j2] = 100*(Customer[j2].timePerDisplay[0]/Customer[j2].time);
				
			if(tshirtTime[j2] != 0)
				tShirtsPercent[j2] = 100*(Customer[j2].timePerDisplay[1]/Customer[j2].time);

			if(activewearTime[j2] != 0)
				activeWearPercent[j2] = 100*(Customer[j2].timePerDisplay[2]/Customer[j2].time);	
				
			if(thirdTime[j2] != 0)
				thirdPercent[j2] = 100*(Customer[j2].timePerDisplay[3]/Customer[j2].time);

			if(fourthTime[j2] != 0)
				fourthPercent[j2] = 100*(Customer[j2].timePerDisplay[4]/Customer[j2].time);	
			
			printf("%d: ", Customer[j2].ID); //prints customer ID
			printf("%4.1lfft ", Customer[j2].distance); //prints the distance the customer has traveled within the store
			printf("%4ds ", Customer[j2].time); //prints the amount of time the customer has been in the store
			if(jeansPercent != 0 && nDisplays >= 1) //the if statements make sure that the appropriate number of displays and their respective percentages are printed
				printf("%12s:%3.0lf%% ", Displays[0].name, jeansPercent[j2]);
			if(tShirtsPercent != 0 && nDisplays >= 2)
				printf("%12s:%3.0lf%% ", Displays[1].name, tShirtsPercent[j2]);
			if(activeWearPercent != 0 && nDisplays >= 3)
				printf("%12s:%3.0lf%% \n", Displays[2].name, activeWearPercent[j2]);
			if(thirdPercent != 0 && nDisplays >= 4)
				printf("%12s:%3.0lf%% ", Displays[3].name, thirdPercent[j2]);
			if(fourthPercent != 0 && nDisplays >= 5)
				printf("%12s:%3.0lf%% \n", Displays[4].name, fourthPercent[j2]);
			
			}
		}
		
	for(j3=0;j3<5;j3++) //the total time at each section from all customers is calculated in the for loop
	{
		jeanTimeTotal = jeanTimeTotal + Customer[j3].timePerDisplay[0];
		tshirtTimeTotal = tshirtTimeTotal + Customer[j3].timePerDisplay[1];
		activeWearTimeTotal = activeWearTimeTotal + Customer[j3].timePerDisplay[2];
		thirdTimeTotal = thirdTimeTotal + Customer[j3].timePerDisplay[3];
		fourthTimeTotal = fourthTimeTotal + Customer[j3].timePerDisplay[4];
		realTimeTotal = realTimeTotal + Customer[j3].time;
	}
		jeanTimeTotalAvg = jeanTimeTotal / realTimeTotal; //these calculate the average total time of each display - these are used in order to find which display was the most popular 
		tshirtTimeTotalAvg = tshirtTimeTotal / realTimeTotal;
		activeWearTimeTotalAvg = activeWearTimeTotal / realTimeTotal;
		thirdTimeTotalAvg = thirdTimeTotal / realTimeTotal;
		fourthTimeTotalAvg = fourthTimeTotal / realTimeTotal;
		
	//the if statements insure that the correct 'most popular' statement is printed
	if(tshirtTimeTotalAvg < jeanTimeTotalAvg && activeWearTimeTotalAvg < jeanTimeTotalAvg && thirdTimeTotalAvg < jeanTimeTotalAvg && fourthTimeTotalAvg < jeanTimeTotalAvg) 
		printf("Most popular: %s\n", Displays[0].name);
	else if(jeanTimeTotalAvg == activeWearTimeTotalAvg && activeWearTimeTotalAvg > tshirtTimeTotalAvg && activeWearTimeTotalAvg > thirdTimeTotalAvg && activeWearTimeTotalAvg > fourthTimeTotalAvg)
		printf("Most popular: %s\n", Displays[0].name);
	else if(jeanTimeTotalAvg == tshirtTimeTotalAvg && activeWearTimeTotalAvg < tshirtTimeTotalAvg && thirdTimeTotalAvg < tshirtTimeTotalAvg && fourthTimeTotalAvg < tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[0].name);
	else if(jeanTimeTotalAvg == thirdTimeTotalAvg && fourthTimeTotalAvg < thirdTimeTotalAvg && tshirtTimeTotalAvg < thirdTimeTotalAvg && activeWearTimeTotalAvg < thirdTimeTotalAvg)
		printf("Most popular: %s\n", Displays[0].name);
	else if(jeanTimeTotalAvg == fourthTimeTotalAvg && fourthTimeTotalAvg > thirdTimeTotalAvg && fourthTimeTotalAvg > activeWearTimeTotalAvg && fourthTimeTotalAvg > tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[0].name);
	else if((jeanTimeTotalAvg == tshirtTimeTotalAvg) && (tshirtTimeTotalAvg == activeWearTimeTotalAvg) && (tshirtTimeTotalAvg == thirdTimeTotalAvg) && (tshirtTimeTotalAvg == fourthTimeTotalAvg))
		printf("Most popular: %s\n", Displays[0].name);
	else if(activeWearTimeTotalAvg == tshirtTimeTotalAvg && fourthTimeTotalAvg < tshirtTimeTotalAvg && tshirtTimeTotalAvg > thirdTimeTotalAvg && jeanTimeTotalAvg < tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[1].name);
	else if(thirdTimeTotalAvg == tshirtTimeTotalAvg && fourthTimeTotalAvg < tshirtTimeTotalAvg && tshirtTimeTotalAvg > activeWearTimeTotalAvg && jeanTimeTotalAvg < tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[1].name);
	else if(fourthTimeTotalAvg == tshirtTimeTotalAvg && thirdTimeTotalAvg < tshirtTimeTotalAvg && tshirtTimeTotalAvg > activeWearTimeTotalAvg && jeanTimeTotalAvg < tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[1].name);
	else if(activeWearTimeTotalAvg < tshirtTimeTotalAvg && jeanTimeTotalAvg < tshirtTimeTotalAvg && thirdTimeTotalAvg < tshirtTimeTotalAvg && fourthTimeTotalAvg < tshirtTimeTotalAvg)
		printf("Most popular: %s\n", Displays[1].name);
	else if(thirdTimeTotalAvg == activeWearTimeTotalAvg && tshirtTimeTotalAvg < activeWearTimeTotalAvg && jeanTimeTotalAvg < activeWearTimeTotalAvg && fourthTimeTotalAvg < activeWearTimeTotalAvg)	
		printf("Most popular: %s\n", Displays[2].name);
	else if(fourthTimeTotalAvg == activeWearTimeTotalAvg && tshirtTimeTotalAvg < activeWearTimeTotalAvg && jeanTimeTotalAvg < activeWearTimeTotalAvg && thirdTimeTotalAvg < activeWearTimeTotalAvg)	
		printf("Most popular: %s\n", Displays[2].name);
	else if(jeanTimeTotalAvg < activeWearTimeTotalAvg && tshirtTimeTotalAvg < activeWearTimeTotalAvg && thirdTimeTotalAvg < activeWearTimeTotalAvg && fourthTimeTotalAvg < activeWearTimeTotalAvg)	
		printf("Most popular: %s\n", Displays[2].name);
	else if(thirdTimeTotalAvg > jeanTimeTotalAvg && thirdTimeTotalAvg > tshirtTimeTotalAvg && thirdTimeTotalAvg > activeWearTimeTotalAvg && thirdTimeTotalAvg > fourthTimeTotalAvg)
		printf("Most popular: %s\n", Displays[3].name);
	else if(thirdTimeTotalAvg == fourthTimeTotalAvg && thirdTimeTotalAvg > tshirtTimeTotalAvg && thirdTimeTotalAvg > activeWearTimeTotalAvg && thirdTimeTotalAvg > jeanTimeTotalAvg)
		printf("Most popular: %s\n", Displays[3].name);
	else if(fourthTimeTotalAvg > activeWearTimeTotalAvg && fourthTimeTotalAvg > jeanTimeTotalAvg && fourthTimeTotalAvg > tshirtTimeTotalAvg && fourthTimeTotalAvg > thirdTimeTotalAvg)
		printf("Most popular: %s\n", Displays[4].name);
	return;
}

/* Read in samples from file, and process them by calling the track function */
int main()
{
  double x, y; // coordinate
  int i;       // customer ID
  int ret=0;

  do {
    //read in the input 
    ret = scanf("%d %lf %lf",&i, &x, &y);
    if (ret==3) {
    // analyze this sample
    track(i,x,y);
    }    

    // stay in loop as long as we keep getting
    // samples
  } while(ret==3);

  // print the final output
  print();

  return 0;
}