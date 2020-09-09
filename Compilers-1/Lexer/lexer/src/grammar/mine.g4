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

	public void reportError(String errorString)
	{
		setText(errorString);
		setType(ERROR);
	}

	public void processString()
	{
		Token t = _factory.create(_tokenFactorySourcePair, _type, 
			  _text, _channel, _tokenStartCharIndex, getCharIndex()-1,
			  _tokenStartLine, _tokenStartCharPositionInLine);
		
		String text = t.getText();

		//write your code to test strings here
		
		text = text.substring(0,text.length()-1);
		int n = text.length();
		if(n > 1024)
		{
			reportError("String constant too long");
			return ;
		}
		if(text.indexOf('\0')!=-1)
		{
			reportError("String contains null charcater");
			return ;
		}
		String escape_char = "btnf";
		String escape_res = "\b\t\n\f";
		int ind;
		ind = text.indexOf("\\");
		while(ind != -1)
		{
			int esc_ind;
			esc_ind = escape_char.indexOf(text.charAt(ind+1));
			if(esc_ind != -1)
			{
				text = text.substring(0,ind) + escape_res.charAt(	esc_ind) + text.substring(ind+2);
			}
			else
			{
				text = text.substring(0,ind) + text.substring(ind+1);
			}
			ind = text.indexOf('\\');
		}
		setText(text);
		setType(STR_CONST);
	}
	public void comments()
	{
		Token t = _factory.create(_tokenFactorySourcePair,_type,_text,_channel,_tokenStartCharIndex,getCharIndex()-1,_tokenStartLine,_tokenStartCharPositionInLine);
		String text = t.getText();
		skip();
	}
	public void reportUnmatched()
	{
		Token t = _factory.create(_tokenFactorySourcePair, _type, _text, _channel,_tokenStartCharIndex,getCharIndex()-1,_tokenStartLine,_tokenStartCharPositionInLine);
		String text = t.getText();
		reportError(text);
	}
}


/*
	WRITE ALL LEXER RULES BELOW
*/

/*special notations */

SEMICOLON   : ';';		
DARROW      : '=>';		
COMMA		: ',';		
DOT 		: '.';		
COLON		: ':';		
ASSIGN		: '<-';		
ATSYM		: '@';		
LBRACE		: '{';		
RBRACE		: '}';		
LPAREN		: '(';		
RPAREN		: ')';		
LT 			: '<';		
LE			: '<=';		
TILDE		: '~';		
MINUS 		: '-';		
PLUS 		: '+';		
STAR 		: '*';		
SLASH		: '/';		
EQUALS 		: '=';		

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
INHERITS	: ('i'|'I')('h'|'H')('e'|'E')('r'|'R')('i'|'I')('t'|'T')('s'|'S'); 
ISVOID		: ('i'|'I')('s'|'S')('v'|'V')('o'|'O')('i'|'I')('d'|'D');	

/* strings */
ERROR_COMMENT 	: '*)' {reportError("Unmatched *)");};

WHITESPACE		: [\n\v\t\b\r\f ]+ -> skip ;	

STRING_ST		: '"' -> skip, pushMode(STRING_MODE);

SINGLE_COMMENT	: '--'(.)*?('\n'|'\r') -> skip;

COMMENT_MULTI	: '(*' -> skip, pushMode(COMMENT);

UNMATCHED		: . {reportUnmatched();};

mode STRING_MODE;	

STRING_END		: '"' {processString();} -> popMode;

NEWLINE			: '\n' {reportError("Unterminated string constant");} -> mode(DEFAULT_MODE);

SINGLE_BACKSLASH: ('"')('\\')('"') {reportError("Single Backslash in string");};

EOF_STRING		: .(EOF) {reportError("EOF in comment");} -> mode(DEFAULT_MODE);			//token will be created and be passed on like an error

STRING_BODY	: (~('\u0000' | [EOF] | '"' | '\n')('\\''\n')?('\\''\"')?)+ -> more;

/*The 'more' command forces the lexer to get another token but without throwing out the current text*/

mode COMMENT;

COMMENT_OPEN	: '(*' -> skip, pushMode(COMMENT);

COMMENT_END		: '*)' -> skip, popMode;		 
EOF_COMMENT		: .(EOF) {reportError("EOF in comment");} -> mode(DEFAULT_MODE);

ANY 		: . -> skip;
	
/*  ID's */
										/*fragment is similar to an inline function, it is not counted as token only simplifies grammar */

fragment DIGIT  : '0'..'9';
fragment LOWER  : 'a'..'z';
fragment UPPER  : 'A'..'Z';
fragment LETTER : (UPPER | LOWER);
fragment TRUE	: ('t')('r'|'R')('u'|'U')('e'|'E');
fragment FALSE	: ('f')('a'|'A')('l'|'L')('s'|'S')('e'|'E');
BOOL_CONST		: TRUE | FALSE;		
INT_CONST		: DIGIT+;					
TYPEID			: (UPPER)('_'|LETTER|DIGIT)*;		
OBJECTID		: (LOWER)('_'|LETTER|DIGIT)*;		

