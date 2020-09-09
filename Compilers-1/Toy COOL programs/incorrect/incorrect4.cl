class Main inherits IO
{
	fi : Int <- 10;-- use of keyword as a variable
	main() : SELF_TYPE
	{
		out_string("FI Value=").out_int(fi)
	};
};