class Main inherits IO
{
	gcd(x : Int, y: Int) : Int {{
		(while not x=y loop					-- if x is not equal y we run a while loop to find gcd
		if x < y then
			y <- y - x
		else 
			x <- x-y
		fi
		pool
		);
		x;					--if x and y equal then one of them is the gcd 
	}};						--method of return int type
	a : Int <- 0;
	b : Int <- 0;
	main() : Object {{
		out_string("Enter the 1st number for which you want to find the gcd:\n");
		a <- in_int();
		out_string("Enter the 2nd number for which you want to find the gcd:\n");
		b <- in_int();
		out_string("The gcd of the 2 numbers is:").out_int(gcd(a,b));			--gcd method being called by passing integers as arguments
		out_string("\n");	
	}};	
};