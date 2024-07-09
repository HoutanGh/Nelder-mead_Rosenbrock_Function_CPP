#include <stdio.h>	
#include <math.h>

//Exercise 2

float F(float x0, float n) //Declares a function F with x0 and n as the arguments.
{
	FILE* fp; //Declares variable *fp as a file handle.
	
	float increment = (n - x0) / 101; //Equation to help calculate the increment where n is the highest point of the range of -2 to 2, so in this case 2.
	float x1 = 1; // x1 is set to be a constant 1.
	float y; //Declaration of y for result of the rosenbrock function.
	
    fp = fopen("exercise2.txt", "w"); //Opens a data.txt where the "w" indicates the file for writing.
	for (x0; x0 < n; x0 += increment) //For loop that starts at the inputted x0 value and increments until n has been reached.

		fprintf(fp, "%.2f %.2f\n", x0, y = 100 * pow(x1 - pow(x0, 2), 2) + pow(1 - x0, 2)); //fprint function to print into the text file the increments of x0 and their corresponding y values.
	                                                                                       
	fclose(fp);	//For closing the file.																																				
}





//Exercise 3

float y(float x0, float x1)	//Declaration of the function y that contains the code for calculting the value of the rosenbrock function.
{
	float y;
	y = 100 * pow(x1 - pow(x0, 2), 2) + pow(1 - x0, 2); //This is the actual equation for the rosenbrock function.
	return y; //Return function returns y so that the calculated variable can be used in the code.
}



float main()
{
	//Exercise 2
	
	F(-2, 2); //Function F from exercise 2 is in the main body so that it can be carried out, and contains the require argument values for x0 and n.


	//Exercise 3 continued
	
	float criterion = 1;         //Criterion has to be initialised so that the requirements for starting the while loop are met.
	float p0[2] = { 0.0, 0.0 };  //The vertices of the simplex are initialised.
	float p1[2] = { 2.0, 0.0 };
	float p2[2] = { 0.0, 2.0 };
	
	float y0, y1, y2, yL, yH, yI, ystar, y2star, ymid; //Declarations of floats for all the different results of the rosenbrock function.
	
	float pstar[2]; //Trial vertices. 
	float p2star[2]; //Another iteration of the trial vertices if needed while doing the flowchart.
	float pmid[2]; //Contains the coordinates of the mid-point between the two lowest vertices.
	float pH[2], pL[2], pI[2]; //Declaration for the vertices that will produce the highest, lowest and middle y values respectively.
	
	int iterations = 0, n = 2; //Iterations represents the number of times the while loop is undergone; and n represents the number of dimensions we are working in.
	
	y0 = y(p0[0], p0[1]);      //Setting the y values using the y function that inputs the values in the p vertices into the rosenbrock function AKA "y".
	y1 = y(p1[0], p1[1]);
	y2 = y(p2[0], p2[1]);
	
	float (*y_ptr)(float, float);
	y_ptr = &y;
	
	while (iterations < 1000 && criterion > pow(10, -8)) { //The loop with the conditions of continuing so long as the iterations are below 2 and the criterion has not been met.
														   //The conditions in this case are whether or not the criterion is less than 10^-8 or 1000 iterations of the loop have been complete.
		if (y1 < y0 && y0 > y2) {						   //If else statements to organise the y values from smallest to largest, as well as the vertices values.
			yH = y0;                                       //This is code for if y0 has been found to be the highest y value that it is set to yH, this is also done for the p arrays.
			pH[0] = p0[0];
			pH[1] = p0[1];
		}
		else if (y0 < y1 && y1 > y2) {		//Similar code to above but checks if y1 is the highest value, and sets all the "high" values to y1 and the p1s.
			yH = y1;
			pH[0] = p1[0];
			pH[1] = p1[1];
		}
		else if (y0 < y2 && y2 > y1) {	    //Checks if y2 is the highest, and carries out same procedure as stated above.
			yH = y2;
			pH[0] = p2[0];
			pH[1] = p2[1];
		}
		if (y1 > y0 && y0 < y2) {			//Similar idea but checks for the lowest value and sets the y0 value to the yL and the corresponding p vertices.
			yL = y0;
			pL[0] = p0[0];
			pL[1] = p0[1];
		}
		else if (y0 > y1 && y1 < y2) {
			yL = y1;
			pL[0] = p1[0];
			pL[1] = p1[1];
		}
		else if (y0 > y2 && y2 < y1) {
			yL = y2;
			pL[0] = p2[0];
			pL[1] = p2[1];
		}
		if (y0 != yH && y0 != yL) {	 //Rather than using inequalities, these if else statements check which one of the y values (y0, y1, y2) have not been set to yL or yH sets yI to said value.
			yI = y0;
			pI[0] = p0[0];
			pI[1] = p0[1];
		}
		else if (y1 != yH && y1 != yL) {
			yI = y1;
			pI[0] = p1[0];
			pI[1] = p1[1];
		}
		else if (y2 != yH && y2 != yL) {
			yI = y2;
			pI[0] = p2[0];
			pI[1] = p2[1];
		}
		//The code was used to order the y values produced by p0, p1 and p2 so that they can be compared with other variables more easily.

		pmid[0] = (pL[0] + pI[0]) / 2;		//this is the centroid calculation for the mid point between the two smallest vertices
		pmid[1] = (pL[1] + pI[1]) / 2;		
		pstar[0] = 2 * pmid[0] - pH[0];		//calculation for the trial vertices, p*		
		pstar[1] = 2 * pmid[1] - pH[1];
		ystar = (*y_ptr)(pstar[0], pstar[1]);	//The pointer that points towards the y function is used to calculate the value for the corresponding vertex, in this case ystar (y*).

		if (ystar < yL) {						//First box of the flowchart, where it checks whether or not y* (that was been calculated from p* vertices) is smaller than the lowest y value. 
			
			p2star[0] = 2 * pstar[0] - pmid[0];	//If the bracket of the if statement is true, a new vertex is calculated and defined.
			p2star[1] = 2 * pstar[1] - pmid[1]; 
			y2star = (*y_ptr)(p2star[0], p2star[1]); //Corresponding y calculated and recorded.
			
			if (y2star < yL) {						 //Check if y** is less than yL and if so carry out the task within the brackets.
				
				pH[0] = p2star[0];					 //New pH is set to the calculated p** value.
				pH[1] = p2star[1];
				
				yH = (*y_ptr)(pH[0], pH[1]);		 //Updated yH value calculated from the new pH.		
				ymid = (*y_ptr)(pmid[0], pmid[1]);	 //ymid also calculated to be inputted in the criterion equation.
				criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n))); //Equation to see whether or not the criterion has been met.

				p0[0] = pL[0];	//Update all the terms of the vertices to be put back into the loop.
				p0[1] = pL[1];
				p1[0] = pI[0];
				p1[1] = pI[1];
				p2[0] = pH[0];
				p2[1] = pH[1];
				
				y0 = (*y_ptr)(p0[0], p0[1]);	//Using the updated vertices also update all the y values to be used in the loop again.
				y1 = (*y_ptr)(p1[0], p1[1]);
				y2 = (*y_ptr)(p2[0], p2[1]);
			}
			else {								//If the statement in the brackets is false carry out the code in the bracket.
				
				pH[0] = pstar[0]; 
				pH[1] = pstar[1];
				
				ymid = (*y_ptr)(pmid[0], pmid[1]); 
				yH = (*y_ptr)(pH[0], pH[1]);
				criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n)));


				p0[0] = pL[0];   //Updated variables for the loop.
				p0[1] = pL[1];	 
				p1[0] = pI[0];
				p1[1] = pI[1];
				p2[0] = pH[0];
				p2[1] = pH[1];
				
				y0 = (*y_ptr)(p0[0], p0[1]);  
				y1 = (*y_ptr)(p1[0], p1[1]);
				y2 = (*y_ptr)(p2[0], p2[1]);
			}
		}
		else {
			
			if (ystar > yI && ystar > yL) {  //Checks whether y* is greater than the middle and lowest y value
				
				if (ystar > yH) {			 //If the statement above check if y* is also greater than the highest y value and carry out code in brackets.
					
					p2star[0] = (pH[0] + pmid[0]) / 2;			//Calculate values for p** as well as the corresponding y value.
					p2star[1] = (pH[1] + pmid[1]) / 2;
					y2star = (*y_ptr)(p2star[0], p2star[1]);
					
					if (y2star > yH) {				 //Checking whether or not y** is larger than yH and carry out code in bracket, otherwise go to else bracket.
						
						pL[0] = (pL[0] + pL[0]) / 2; //Replaces all the elements, cutting down the simplex triangle drastically.												
						pL[1] = (pL[1] + pL[1]) / 2; //The first two lines of this is unnecessary but is wrote anyway to show that all the vertices are involved.
						pI[0] = (pI[0] + pL[0]) / 2;
						pI[1] = (pI[1] + pL[1]) / 2;
						pH[0] = (pH[0] + pL[0]) / 2;
						pH[1] = (pH[1] + pL[1]) / 2;
						
						ymid = (*y_ptr)(pmid[0], pmid[1]);
						yL = (*y_ptr)(pL[0], pL[1]);
						yI = (*y_ptr)(pI[0], pI[1]);
						yH = (*y_ptr)(pH[0], pH[1]);
						criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n)));

						p0[0] = pL[0];
						p0[1] = pL[1];
						p1[0] = pI[0];
						p1[1] = pI[1];
						p2[0] = pH[0];
						p2[1] = pH[1];
						
						y0 = (*y_ptr)(p0[0], p0[1]);
						y1 = (*y_ptr)(p1[0], p1[1]);
						y2 = (*y_ptr)(p2[0], p2[1]);
					}
					
					else {
						
						pH[0] = p2star[0]; //pH values updated
						pH[1] = p2star[1];
						
						ymid = (*y_ptr)(pmid[0], pmid[1]);
						yH = (*y_ptr)(pH[0], pH[1]);
						criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n)));
						
						p0[0] = pL[0];
						p0[1] = pL[1];
						p1[0] = pI[0];
						p1[1] = pI[1];
						p2[0] = pH[0];
						p2[1] = pH[1];
						
						y0 = (*y_ptr)(p0[0], p0[1]);
						y1 = (*y_ptr)(p1[0], p1[1]);
						y2 = (*y_ptr)(p2[0], p2[1]);
					}
				}
				
				else {
					
					pH[0] = pstar[0];
					pH[1] = pstar[1];
					p2star[0] = (pH[0] + pmid[0]) / 2;
					p2star[1] = (pH[1] + pmid[1]) / 2;
					y2star = (*y_ptr)(p2star[0], p2star[1]);
					
					if (y2star > yH) {
						
						pL[0] = (pL[0] + pL[0]) / 2; 
						pL[1] = (pL[1] + pL[1]) / 2;
						pI[0] = (pI[0] + pL[0]) / 2;
						pI[1] = (pI[1] + pL[1]) / 2;
						pH[0] = (pH[0] + pL[0]) / 2;
						pH[1] = (pH[1] + pL[1]) / 2;
						
						ymid = (*y_ptr)(pmid[0], pmid[1]);
						yL = (*y_ptr)(pL[0], pL[1]);
						yI = (*y_ptr)(pI[0], pI[1]);
						yH = (*y_ptr)(pH[0], pH[1]);
						criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n)));

						p0[0] = pL[0];
						p0[1] = pL[1];
						p1[0] = pI[0];
						p1[1] = pI[1];
						p2[0] = pH[0];
						p2[1] = pH[1];
						
						y0 = (*y_ptr)(p0[0], p0[1]);
						y1 = (*y_ptr)(p1[0], p1[1]);
						y2 = (*y_ptr)(p2[0], p2[1]);
					}
					else {
						
						pH[0] = p2star[0];
						pH[1] = p2star[1];
						
						yH = (*y_ptr)(pH[0], pH[1]);
						ymid = (*y_ptr)(pmid[0], pmid[1]);
						criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n))); 

						p0[0] = pL[0];
						p0[1] = pL[1];
						p1[0] = pI[0];
						p1[1] = pI[1];
						p2[0] = pH[0];
						p2[1] = pH[1];
						
						y0 = (*y_ptr)(p0[0], p0[1]);
						y1 = (*y_ptr)(p1[0], p1[1]);
						y2 = (*y_ptr)(p2[0], p2[1]);


					}
				}
			}
			else {  //This bracket is connected to the if statement of the flowchart checking whether or not y* > yL and if that statement is false the code in this else bracket is carried out.
				
			    pH[0] = pstar[0];
				pH[1] = pstar[1];
				
				ymid = (*y_ptr)(pmid[0], pmid[1]);
				yH = (*y_ptr)(pH[0], pH[1]);
				criterion = sqrt((((pow(yL - ymid, 2)) / n) + ((pow(yI - ymid, 2)) / n) + ((pow(yH - ymid, 2)) / n)));
				
				p0[0] = pL[0];
				p0[1] = pL[1];
				p1[0] = pI[0];
				p1[1] = pI[1];
				p2[0] = pH[0];
				p2[1] = pH[1];
				
				y0 = (*y_ptr)(p0[0], p0[1]);
				y1 = (*y_ptr)(p1[0], p1[1]);
				y2 = (*y_ptr)(p2[0], p2[1]);
			}
		}

		iterations++; //Makes sure that at the end of the while loop 1 is added to iterations so that the program can keep count of how many loops have occurred.
	}
	printf("y0 = %.10f, y1 = %.10f, y2 = %.10f\n", y0, y1, y2); //Prints the values to 2 decimal points.
	printf("The number of iterations: %d\n", iterations);    //Prints the number of times to loop had to be done until criterion was met.
	printf("Criterion: %.1f\n", criterion);                             //Prints the value calculated from the criterion equation.
	
	printf("The points of the triangle were as follows:\n");  //Text signifying the points of the simplex triangle are stated below.
	
	printf("p0: ");
	for (int i = 0; i < 2; i++) {    //For printing the arrays, a loop at goes through the individual elements of the array and prints them.
		printf("%.2f ", pL[i]);
	}
	printf("\n");					 //Prints a line so that the next text in the print function gets printed on a separate line.
	printf("p1: ");
	for (int j = 0; j < 2; j++) {  
		printf("%.2f ", pI[j]);
	}
	printf("\n");
	printf("p2: ");
	for (int k = 0; k < 2; k++) {
		printf("%.2f ", pH[k]);
	}
	printf("\n");
	
	return 0; //Indicates that the program has been successfully ran and the main function can be terminated.
}










