class Main inherits IO {
	s: String <- "This is
	COOL Language\n";		--To avoid this we need to add a back slash at start
	main() : SELF_TYPE
	{
		out_string(s)
	};
};