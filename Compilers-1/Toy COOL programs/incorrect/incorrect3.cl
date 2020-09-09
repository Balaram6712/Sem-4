class Main inherits IO
{
	x : Int <- 10;
	y : Int <- 15;
	main() : SELF_TYPE
	{{
	   x <- x + y;  --adding two numbers
		out_int(x);	- printing incorrect commenting
	}};
};