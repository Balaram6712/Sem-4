lexer grammar CoolLexer;


tokens{
	ERROR,
	TYPEID,
	OBJECTID,
	BOOL_CONST,
	INT_CONST,
	STR_CONST,
	LPAREN,
	RPAREN,
	COLON,
	ATSYM,
	SEMICOLON,
	COMMA,
	PLUS,
	MINUS,
	STAR,
	SLASH,
	TILDE,
	LT,
	EQUALS,
	LBRACE,
	RBRACE,
	DOT,
	DARROW,
	LE,
	ASSIGN,
	CLASS,
	ELSE,
	FI,
	IF,
	IN,
	INHERITS,
	LET,
	LOOP,
	POOL,
	THEN,
	WHILE,
	CASE,
	ESAC,
	OF,
	NEW,
	ISVOID,
	NOT
}
/*
  DO NOT EDIT CODE ABOVE THIS LINE
*/
	
@members{

	/*YOU CAN ADD YOUR MEMBER VARIABLES AND METHODS HERE*/
	/**
	* Function to report errors.
	* Use this function whenever your lexer encounters any erroneous input
	* DO NOT EDIT THIS FUNCTION
	*/

	public void reportError(String errorstring)
	{
		setText(errorstring);
		setType(ERROR);
	}					//report error function and setting the token type to ERROR

	public void reportUnmatched()
	{
		Token t = _factory.create(_tokenFactorySourcePair, _type, _text, _channel,_tokenStartCharIndex,getCharIndex()-1,_tokenStartLine,_tokenStartCharPositionInLine);
		String text = t.getText();
		reportError(text);
	}										//reporting the unmatched characters

	public void processString()
	{
		Token t = _factory.create(_tokenFactorySourcePair, _type, 
			  _text, _channel, _tokenStartCharIndex, getCharIndex()-1,
			  _tokenStartLine, _tokenStartCharPositionInLine);
		String text = t.getText();
		text = text.substring(1,text.length()-1);
		String s = "";
		int it=0,len=0;
		while(it < text.length())
		{
			len++;
			if(text.charAt(it)=='\u0000')
			{
				reportError("String contains null character.");
				return;
			}												//if null in the string reporting the error
			if(text.charAt(it)=='\\')
			{
				if(text.charAt(it+1)=='\u0000')
				{
					reportError("String contains escaped null character.");	
					return;							//reporting it as escaped null charcater as \\u0000 is found in the string
				}
				if(text.charAt(it+1)=='t')
				{
					s = s + "\t";
				}
				else if(text.charAt(it+1)=='f')
				{
					s = s + "\f";
				}
				else if(text.charAt(it+1)=='n')
				{
					s = s + "\n";
				}
				else if(text.charAt(it+1)=='b')
				{
					s = s + "\b";
				}
				else if(text.charAt(it+1)=='"')
				{
					s = s + '"';
				}
				else if(text.charAt(it+1)=='\\')
				{
					s = s + '\\';
				}
				else
				{
					s = s + text.charAt(it+1);
				}
				it = it + 2;
			}
			else
			{
				s = s + text.charAt(it);
				it++;
			}
			
		}
		if(len > 1024)
		{
			reportError("String constant too long");
			return;
		}
		setText(s);
		return ;
	}

	public void comments()
	{
		Token t = _factory.create(_tokenFactorySourcePair,_type,_text,_channel,_tokenStartCharIndex,getCharIndex()-1,_tokenStartLine,_tokenStartCharPositionInLine);
		String text = t.getText();
		skip();
	}
}


/*
	WRITE ALL LEXER RULES BELOW
*/
/* key words */

CASE 		: ('c'|'C')('a'|'A')('s'|'S')('e'|'E');	 
ESAC		: ('e'|'E')('s'|'S')('a'|'A')('c'|'C');		
IF			: ('i'|'I')('f'|'F');					
FI			: ('f'|'F')('i'|'I');					
ELSE		: ('e'|'E')('l'|'L')('s'|'S')('e'|'E');	
WHILE		: ('w'|'W')('h'|'H')('i'|'I')('l'|'L')('e'|'E'); 
THEN		: ('t'|'T')('h'|'H')('e'|'E')('n'|'N');		
LOOP		: ('l'|'L')('o'|'O')('o'|'O')('p'|'P');		
POOL		: ('p'|'P')('o'|'O')('o'|'O')('l'|'L');		
OF			: ('o'|'O')('f'|'F');				
LET			: ('l'|'L')('e'|'E')('t'|'T'); 		
NEW			: ('n'|'N')('e'|'E')('w'|'W');		
NOT			: ('n'|'N')('o'|'O')('t'|'T');		
IN			: ('i'|'I')('n'|'N');				
CLASS		: ('c'|'C')('l'|'L')('a'|'A')('s'|'S')('s'|'S');		
INHERITS	: ('i'|'I')('n'|'N')('h'|'H')('e'|'E')('r'|'R')('i'|'I')('t'|'T')('s'|'S'); 
ISVOID		: ('i'|'I')('s'|'S')('v'|'V')('o'|'O')('i'|'I')('d'|'D');

/*special notations */

SEMICOLON   : ';';
DARROW      : '=>';
LPAREN		: '(' ;
RPAREN		: ')' ;
COLON		: ':' ;
ATSYM		: '@' ;
COMMA		: ',' ;
PLUS		: '+' ;
MINUS		: '-' ;
STAR		: '*' ;
SLASH		: '/' ;
TILDE		: '~' ;
LT			: '<' ;
EQUALS		: '=' ;
LBRACE		: '{' ;
RBRACE		: '}' ;
DOT			: '.' ;
LE  		: '<=' ;
ASSIGN		: '<-' ;


fragment UPPER	: 'A'..'Z';
fragment LOWER	: 'a'..'z';
fragment DIGIT	: '0'..'9';
fragment ESC 	: ('\\').;
fragment TRUE	: ('t')('r'|'R')('u'|'U')('e'|'E');
fragment FALSE	: ('f')('a'|'A')('l'|'L')('s'|'S')('e'|'E');		//true and false should have their first letter as small letters
INT_CONST		: DIGIT+;									
BOOL_CONST		: (TRUE | FALSE);
TYPEID			: [A-Z][_a-zA-Z0-9]*;
OBJECTID		: [a-z][_a-zA-Z0-9]*;


WHITESPACE		: [ \u000b\n\f\r\t]+ -> skip;						// whitespace which can be ignored using skip
SINGLE_LINE		: '--'(.)*?('\n'|(EOF)) -> skip;					//single line comment 
STRING_ST		: '"' -> skip, pushMode(STRING_MODE);				// when '"' is seen then string mode is entered
STR_CONST		: '"'(ESC| ~('\\'|'"'|'\n'))*'"' {processString();}; //stating the string type to string constant
COMMENTS		: '(*' -> skip, pushMode(MULTI_COMMENT);			//'(*' has been seen and it enters comment mode
ERROR_COMMENT	: '*)' {reportError("Unmatched *)");};			//when an comment is even not started and '*)' is seen it is error
ERR_EOF_NEW		: '(*'EOF {reportError("EOF in comment");} -> mode(DEFAULT_MODE);
UNMATCHED		: . {reportUnmatched();};			//unmatched characters a method is called and that character is reported as error

mode MULTI_COMMENT;
EOF_NEW_ERROR_CASE1		: '(*'EOF {reportError("EOF in comment");};			//eof found in comment mode it is an error
NESTED_ST1				: '(*' -> skip, pushMode(MULTI_MULTI_COMMENT);   // (* is seen and it enters into a nested comment mode
NESTED_END1				: '*)' -> skip, popMode;					//closing the comment popMode and it returns to the normal mode
EOF_ERROR_FILE1			: .(EOF) {reportError("EOF in comment");} -> mode(DEFAULT_MODE);
OTHER 					: . -> skip;										//other characters are neglected by using skip

mode MULTI_MULTI_COMMENT;
EOF_NEW_ERROR_CASE2		: '(*'EOF {reportError("EOF in comment");};			//eof found in comment mode it is an error
NESTED_ST3				: '(*' -> skip, pushMode(MULTI_MULTI_COMMENT);	//nested comment and (* is seen entering again into the same mode similar to recursion
NESTED_END2 			: '*)' -> skip, popMode;							
EOF_ERROR_FILE2			: .(EOF) {reportError("EOF in comment");};				
EOF_ERROR_FILE3			: '*)'(EOF) {reportError("EOF in comment");};	//eof found in comment mode it is an error
REST					: . -> skip;								//other characters are neglected by using skip
			
mode STRING_MODE;
STRING_END				: 	'"' {processString();} -> popMode;		//string end reached for string constant and pop from presnt mode
ERROR_BACK				: 	('\\"'). -> more;					
NULL_ERROR_STR			:	~('\n'|'"'|'\u0000')*('\u0000')+ ~('\n'|'"')* ('"'|'\n'|'EOF') { reportError("String contains null character."); } -> mode(DEFAULT_MODE);					//error for null character in string a grammar rule
BACK_SLASH_ERROR		: 	~[\n"]*('\\')+(EOF) {reportError("backslash at end of file");} -> mode(DEFAULT_MODE);		//rule for deetcting the backslash at eof error
ERROR_STRING			: 	~[\n"]*('\n') {reportError("Unterminated string constant");} -> mode(DEFAULT_MODE) ;		//when a strig is not terminated this error is generated
STRING_MAIN				: 	(~( '"' |'\u0000'|'\u000b'|'\u000B'| '\n')('\\''\n')?('\\''\"')?)+ -> more;
EOF_ERROR_STRING		: 	~[\n"]*(EOF) {reportError("EOF in string constant");} -> mode(DEFAULT_MODE);		//when EOF is reached in a string constant			