class Main inherits IO
{
	main() : Object {{
		out_string("Enter string to print its reverse:\n");
		let s : String <-in_string() in     --taking string input
		let n : Int <- s.length()-1 in      --string the last chacrter number into a variable
		while 0 < n +1 loop
		{
			out_string(s.substr(n,1));	--printing from last character
			n <- n -1;	
		}
		pool;
		out_string("\n");

	}};	
};