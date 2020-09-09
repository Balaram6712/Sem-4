class Main inherits IO
{
	mod(x : Int, y : Int) : Int {
		x - (x/y)*y
	};
	prime(n : Int) : Bool {
		let k : Bool <- true in
		let i : Int <- 5 in
		let u : Int <- 5 in

		if n=1 then
		k <- false
		else if n <=3 then
		true
		else if mod(n,2)=0 then				--if divisible by 2 then not prime
		false
		else if mod(n,3)=0 then				----if divisible by 3 then not prime
		false
		else
		{
			while i*i <= n loop{
				if mod(n,i)=0 then
				k <-false
				else if mod(n,i+2)=0 then 
				k<-false
				else u <- u + 1
				fi
				fi;
				
			}
			pool;
			k;
		}
		fi 
		fi 
		fi 
		fi
	};

	main() : Object {{
		out_string("Enter a number to check if it is prime or not:\n");
		if prime(in_int()) then
			out_string("It is a prime number\n")
		else
			out_string("Not a prime number\n")
		fi;
	}};	
};