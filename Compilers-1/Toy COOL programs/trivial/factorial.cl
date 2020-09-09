class Main inherits IO
{
	fact(num : Int) : Int{
		if num = 1 then					--method return type int
		 1 
		else
		num*fact(num-1)					--recursive calling of the function
		fi
	};
	main() : Object {{
		out_string("Enter the number for which you want to find the factorial:\n");
		let n : Int <- in_int()	in --taking number input
		out_string("The factorial of the given number is: ").out_int(fact(n));			--calling function and printing output
		out_string("\n");
	
	}};	
};