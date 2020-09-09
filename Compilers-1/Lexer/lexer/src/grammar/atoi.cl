class Main inherits IO{
	chtoin(cha : String) : Int{
		if cha = "0" then 0
		else if cha = "1" then 1
		else if cha = "2" then 2
		else if cha = "3" then 3
		else if cha = "4" then 4
		else if cha = "5" then 5
		else if cha = "6" then 6
		else if cha = "7" then 7
		else if cha = "8" then 8
		else if cha = "9" then 9
		else { abort(); 0;}
		fi fi fi fi fi fi fi fi fi fi 
	};				--converting a charcater to integer
	
	num : Int <- 0;
	j : Int <- 0;
	i : Int <- 0;
	ataa(st : String) : Int{{
		j <- st.length();
		while i < j loop{
			num <- num*10 + chtoin(st.substr(i,1));
			i <- i + 1; 
		}
		pool;							--a method for converting the string into a integer a returning the integer
		num;
	}};


	atoi(str : String) : Int{
		if str.length() = 0 then 0					--if the string is not given -1 returned 
		else if str.substr(0,1) = "-" then ~ataa(str.substr(1,str.length()-1))			--if negative number given as input then it is tqaken care of
		else
		ataa(str) 		--method is called to convert the string to intger
		fi fi 
	};
	s : String;
	n : Int <- 0;
	main () : Object{{
		out_string("Enter a string which consists of numbers to convert it to integer type, even negative numbers string can be given as input:\n");
		s <- in_string();
		n <- atoi(s);
		out_string("The integer given as input: ").out_int(n);
		out_string("\n");
	}};
};				--implementation of atoi function which takes string as input and converts into input when integer given as input 