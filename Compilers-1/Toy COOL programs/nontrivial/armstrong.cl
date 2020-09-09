class Main inherits IO{
	pow(a : Int, b : Int) : Int{
		if b=0 then 1
		else a*pow(a,b-1)
		fi
	};				--a method to calculate a to the power b

	a : Int <- 0;
	order(x : Int) : Int{{
		a <- 0;
		while 0 < x loop{
			a <- a + 1;
			x <- x/10;
		}
		pool;
		a;
	}};					--a mtethod to find the order of the the digit entered

	mod(x : Int, y : Int) : Int {
		x - (x/y)*y
	};					--method to find modulus, a%b 


	n : Int <- 0;
	temp : Int <-0;
	sum : Int <- 0;
	t : Int <- 0;
	isarms(x : Int) : Bool{{
		n <- order(x);
		temp <- x;
		sum <- 0;
		while 0 < temp loop{
			t <- mod(temp,10);
			sum <- sum + pow(t,n);
			temp <- temp/10;
		}
		pool;
		if sum = x then true
		else
		false
		fi;
	}};						--this method tells if the entered number is armstrong number or not

	main() : Object{{
	out_string("Enter a number to check if the given number is Armstrong number or not:\n");
	if isarms(in_int()) then								--calling the method and taking the input and passing the input as argument to the method
		out_string("It is an Armstrong number\n")
	else
		out_string("Not an Armstrong number\n")
	fi;
	}};
};				--sum of its own digits each raised to the power of the number of digits is equal to the given digit then it is a armstrong number 