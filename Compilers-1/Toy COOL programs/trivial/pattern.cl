class Main inherits IO
{
	pattern(a : Int) :Object
	{
		let i : Int <- 0 in
		let j : Int <- 0 in
		while j < a loop {
			i <- 0;
			while i < j+1 loop {
				out_string("*");				--printing the pattern and itearting aaccordingly
				i <- i +1;
			}
			pool;
			j <- j + 1;
			out_string("\n");
		}
		pool
	};
	main() : Object {{
		out_string(" Pattern \n");
		out_string("Enter a number:\n");
		let n : Int <- in_int()	in          --taking the n input to print the pattern 
		pattern(n);							--calling the method passing the argument
	}};	
};