class Main inherits IO
{
	k : Bool;
	s : String;
	temp : String;
	spc : String;
	w_c : Int; 
	char_c : Int;
	main() : Object {{
		out_string("Enter the sentence: ");
		temp <- " ";
		spc <- " ";
		s <-in_string();
		w_c <- 0;
		char_c <- 0 ;
		temp <- temp.concat(s);
		let n : Int <- s.length() in	
		let i : Int <- 0 in
		(while not i = n + 1 loop{
			if temp.substr(i,1) = spc then
			k <- false
			else
			{
				char_c <- char_c + 1;
				if k = false then
				{
					w_c <- w_c + 1;
				}
				else 0 
				fi;
				k <- true;
			}fi;
			i < i + 1;
		}
		pool
		) ;
		out_string("The number of words: ").out_int(w_c);
		out_string("\n");
		out_string("The number of words: ").out_int(char_c);
		out_string("\n");
	}};	
};