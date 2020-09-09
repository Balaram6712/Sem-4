-- calculate the rounded average of the given numbers

class Main inherits IO {
  main(): Object {{
    out_string("Enter the number of elements you want to calculate rounded average of\n");
    let average: Int <- 0 in -- stores the average of numbers
    let total : Int <- 0 in  -- stores the sum of numbers
    let n: Int <- in_int() in -- number of elements
      if n < 0 then
        out_string("ERROR: Number of elements must be greater or equal to 0\n")
      else {
      	let loopVar : Int <- 0 in  
	    	(while loopVar < n loop
	    	  {
	    	      out_string("Enter element no ").out_int(loopVar+1);
	    	      out_string("\n");
	    	      total <- total + in_int(); -- adding the current number to sum total
	    	      loopVar <- loopVar + 1;
	    	  }
	    	  pool
	    	);
	    	average <- total/n; -- dividing total by size to get rounded average
	    	out_string("The rounded average of entered elements is ").out_int(average);
	    	out_string("\n");
	   	}
	    fi;
  }};
};