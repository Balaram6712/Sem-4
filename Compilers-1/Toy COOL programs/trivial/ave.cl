class Main inherits IO {
	main() : Object {{
		out_string("Enter the number of elements you want to find the average of:\n");
		let total : Int <- 0 in	
		let average : Int <- 0 in 	--initialising variables
		let n : Int <- in_int()	in 			--taking number of elements as input
		if n < 0 then	
		out_string("N should be greater than 0")
		else {
		out_string("Enter the elements for which you want to find average:\n");
		let iterator : Int <- 0 in
		(while iterator < n loop
			{
				total <- total + in_int();
				iterator <- iterator + 1;			--running a loop to find the total sum of the elemnts
			}
			pool
		); 
		average <- total/n;				--rounded average to less than equal to value of average is being printed
		out_string("The rounded average is equal to: ").out_int(average);		--printing the output of average of numbers rounded to fllor intger value
		out_string("\n");
		}
		fi;				
	}};
};