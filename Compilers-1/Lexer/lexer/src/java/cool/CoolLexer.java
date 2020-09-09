// Generated from CoolLexer.g4 by ANTLR 4.5
package cool;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class CoolLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		ERROR=1, TYPEID=2, OBJECTID=3, BOOL_CONST=4, INT_CONST=5, STR_CONST=6, 
		LPAREN=7, RPAREN=8, COLON=9, ATSYM=10, SEMICOLON=11, COMMA=12, PLUS=13, 
		MINUS=14, STAR=15, SLASH=16, TILDE=17, LT=18, EQUALS=19, LBRACE=20, RBRACE=21, 
		DOT=22, DARROW=23, LE=24, ASSIGN=25, CLASS=26, ELSE=27, FI=28, IF=29, 
		IN=30, INHERITS=31, LET=32, LOOP=33, POOL=34, THEN=35, WHILE=36, CASE=37, 
		ESAC=38, OF=39, NEW=40, ISVOID=41, NOT=42, WHITESPACE=43, SINGLE_LINE=44, 
		STRING_ST=45, COMMENTS=46, ERROR_COMMENT=47, ERR_EOF_NEW=48, UNMATCHED=49, 
		EOF_NEW_ERROR_CASE1=50, NESTED_ST1=51, NESTED_END1=52, EOF_ERROR_FILE1=53, 
		OTHER=54, EOF_NEW_ERROR_CASE2=55, NESTED_ST3=56, NESTED_END2=57, EOF_ERROR_FILE2=58, 
		EOF_ERROR_FILE3=59, REST=60, STRING_END=61, NULL_ERROR_STR=62, BACK_SLASH_ERROR=63, 
		ERROR_STRING=64, EOF_ERROR_STRING=65;
	public static final int MULTI_COMMENT = 1;
	public static final int MULTI_MULTI_COMMENT = 2;
	public static final int STRING_MODE = 3;
	public static String[] modeNames = {
		"DEFAULT_MODE", "MULTI_COMMENT", "MULTI_MULTI_COMMENT", "STRING_MODE"
	};

	public static final String[] ruleNames = {
		"CASE", "ESAC", "IF", "FI", "ELSE", "WHILE", "THEN", "LOOP", "POOL", "OF", 
		"LET", "NEW", "NOT", "IN", "CLASS", "INHERITS", "ISVOID", "SEMICOLON", 
		"DARROW", "LPAREN", "RPAREN", "COLON", "ATSYM", "COMMA", "PLUS", "MINUS", 
		"STAR", "SLASH", "TILDE", "LT", "EQUALS", "LBRACE", "RBRACE", "DOT", "LE", 
		"ASSIGN", "UPPER", "LOWER", "DIGIT", "ESC", "TRUE", "FALSE", "INT_CONST", 
		"BOOL_CONST", "TYPEID", "OBJECTID", "WHITESPACE", "SINGLE_LINE", "STRING_ST", 
		"STR_CONST", "COMMENTS", "ERROR_COMMENT", "ERR_EOF_NEW", "UNMATCHED", 
		"EOF_NEW_ERROR_CASE1", "NESTED_ST1", "NESTED_END1", "EOF_ERROR_FILE1", 
		"OTHER", "EOF_NEW_ERROR_CASE2", "NESTED_ST3", "NESTED_END2", "EOF_ERROR_FILE2", 
		"EOF_ERROR_FILE3", "REST", "STRING_END", "ERROR_BACK", "NULL_ERROR_STR", 
		"BACK_SLASH_ERROR", "ERROR_STRING", "STRING_MAIN", "EOF_ERROR_STRING"
	};

	private static final String[] _LITERAL_NAMES = {
		null, null, null, null, null, null, null, "'('", "')'", "':'", "'@'", 
		"';'", "','", "'+'", "'-'", "'*'", "'/'", "'~'", "'<'", "'='", "'{'", 
		"'}'", "'.'", "'=>'", "'<='", "'<-'", null, null, null, null, null, null, 
		null, null, null, null, null, null, null, null, null, null, null, null, 
		null, "'\"'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "ERROR", "TYPEID", "OBJECTID", "BOOL_CONST", "INT_CONST", "STR_CONST", 
		"LPAREN", "RPAREN", "COLON", "ATSYM", "SEMICOLON", "COMMA", "PLUS", "MINUS", 
		"STAR", "SLASH", "TILDE", "LT", "EQUALS", "LBRACE", "RBRACE", "DOT", "DARROW", 
		"LE", "ASSIGN", "CLASS", "ELSE", "FI", "IF", "IN", "INHERITS", "LET", 
		"LOOP", "POOL", "THEN", "WHILE", "CASE", "ESAC", "OF", "NEW", "ISVOID", 
		"NOT", "WHITESPACE", "SINGLE_LINE", "STRING_ST", "COMMENTS", "ERROR_COMMENT", 
		"ERR_EOF_NEW", "UNMATCHED", "EOF_NEW_ERROR_CASE1", "NESTED_ST1", "NESTED_END1", 
		"EOF_ERROR_FILE1", "OTHER", "EOF_NEW_ERROR_CASE2", "NESTED_ST3", "NESTED_END2", 
		"EOF_ERROR_FILE2", "EOF_ERROR_FILE3", "REST", "STRING_END", "NULL_ERROR_STR", 
		"BACK_SLASH_ERROR", "ERROR_STRING", "EOF_ERROR_STRING"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}



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


	public CoolLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "CoolLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	@Override
	public void action(RuleContext _localctx, int ruleIndex, int actionIndex) {
		switch (ruleIndex) {
		case 49:
			STR_CONST_action((RuleContext)_localctx, actionIndex);
			break;
		case 51:
			ERROR_COMMENT_action((RuleContext)_localctx, actionIndex);
			break;
		case 52:
			ERR_EOF_NEW_action((RuleContext)_localctx, actionIndex);
			break;
		case 53:
			UNMATCHED_action((RuleContext)_localctx, actionIndex);
			break;
		case 54:
			EOF_NEW_ERROR_CASE1_action((RuleContext)_localctx, actionIndex);
			break;
		case 57:
			EOF_ERROR_FILE1_action((RuleContext)_localctx, actionIndex);
			break;
		case 59:
			EOF_NEW_ERROR_CASE2_action((RuleContext)_localctx, actionIndex);
			break;
		case 62:
			EOF_ERROR_FILE2_action((RuleContext)_localctx, actionIndex);
			break;
		case 63:
			EOF_ERROR_FILE3_action((RuleContext)_localctx, actionIndex);
			break;
		case 65:
			STRING_END_action((RuleContext)_localctx, actionIndex);
			break;
		case 67:
			NULL_ERROR_STR_action((RuleContext)_localctx, actionIndex);
			break;
		case 68:
			BACK_SLASH_ERROR_action((RuleContext)_localctx, actionIndex);
			break;
		case 69:
			ERROR_STRING_action((RuleContext)_localctx, actionIndex);
			break;
		case 71:
			EOF_ERROR_STRING_action((RuleContext)_localctx, actionIndex);
			break;
		}
	}
	private void STR_CONST_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 0:
			processString();
			break;
		}
	}
	private void ERROR_COMMENT_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 1:
			reportError("Unmatched *)");
			break;
		}
	}
	private void ERR_EOF_NEW_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 2:
			reportError("EOF in comment");
			break;
		}
	}
	private void UNMATCHED_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 3:
			reportUnmatched();
			break;
		}
	}
	private void EOF_NEW_ERROR_CASE1_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 4:
			reportError("EOF in comment");
			break;
		}
	}
	private void EOF_ERROR_FILE1_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 5:
			reportError("EOF in comment");
			break;
		}
	}
	private void EOF_NEW_ERROR_CASE2_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 6:
			reportError("EOF in comment");
			break;
		}
	}
	private void EOF_ERROR_FILE2_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 7:
			reportError("EOF in comment");
			break;
		}
	}
	private void EOF_ERROR_FILE3_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 8:
			reportError("EOF in comment");
			break;
		}
	}
	private void STRING_END_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 9:
			processString();
			break;
		}
	}
	private void NULL_ERROR_STR_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 10:
			 reportError("String contains null character."); 
			break;
		}
	}
	private void BACK_SLASH_ERROR_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 11:
			reportError("backslash at end of file");
			break;
		}
	}
	private void ERROR_STRING_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 12:
			reportError("Unterminated string constant");
			break;
		}
	}
	private void EOF_ERROR_STRING_action(RuleContext _localctx, int actionIndex) {
		switch (actionIndex) {
		case 13:
			reportError("EOF in string constant");
			break;
		}
	}

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\2C\u020f\b\1\b\1\b"+
		"\1\b\1\4\2\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t"+
		"\4\n\t\n\4\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21"+
		"\t\21\4\22\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30"+
		"\t\30\4\31\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37"+
		"\t\37\4 \t \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)"+
		"\4*\t*\4+\t+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63"+
		"\t\63\4\64\t\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;"+
		"\4<\t<\4=\t=\4>\t>\4?\t?\4@\t@\4A\tA\4B\tB\4C\tC\4D\tD\4E\tE\4F\tF\4G"+
		"\tG\4H\tH\4I\tI\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\4\3\4\3\4\3"+
		"\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\b\3\b\3\b\3\b"+
		"\3\b\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\f\3\f\3"+
		"\f\3\f\3\r\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\20\3\20\3"+
		"\20\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\22\3"+
		"\22\3\22\3\22\3\22\3\22\3\22\3\23\3\23\3\24\3\24\3\24\3\25\3\25\3\26\3"+
		"\26\3\27\3\27\3\30\3\30\3\31\3\31\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3"+
		"\35\3\36\3\36\3\37\3\37\3 \3 \3!\3!\3\"\3\"\3#\3#\3$\3$\3$\3%\3%\3%\3"+
		"&\3&\3\'\3\'\3(\3(\3)\3)\3)\3*\3*\3*\3*\3*\3+\3+\3+\3+\3+\3+\3,\6,\u0127"+
		"\n,\r,\16,\u0128\3-\3-\5-\u012d\n-\3.\3.\7.\u0131\n.\f.\16.\u0134\13."+
		"\3/\3/\7/\u0138\n/\f/\16/\u013b\13/\3\60\6\60\u013e\n\60\r\60\16\60\u013f"+
		"\3\60\3\60\3\61\3\61\3\61\3\61\7\61\u0148\n\61\f\61\16\61\u014b\13\61"+
		"\3\61\5\61\u014e\n\61\3\61\3\61\3\62\3\62\3\62\3\62\3\62\3\63\3\63\3\63"+
		"\7\63\u015a\n\63\f\63\16\63\u015d\13\63\3\63\3\63\3\63\3\64\3\64\3\64"+
		"\3\64\3\64\3\64\3\65\3\65\3\65\3\65\3\65\3\66\3\66\3\66\3\66\3\66\3\66"+
		"\3\66\3\66\3\67\3\67\3\67\38\38\38\38\38\38\39\39\39\39\39\39\3:\3:\3"+
		":\3:\3:\3:\3;\3;\3;\3;\3;\3;\3<\3<\3<\3<\3=\3=\3=\3=\3=\3=\3>\3>\3>\3"+
		">\3>\3>\3?\3?\3?\3?\3?\3?\3@\3@\3@\3@\3A\3A\3A\3A\3A\3A\3B\3B\3B\3B\3"+
		"C\3C\3C\3C\3C\3D\3D\3D\3D\3D\3D\3D\3E\7E\u01c1\nE\fE\16E\u01c4\13E\3E"+
		"\6E\u01c7\nE\rE\16E\u01c8\3E\7E\u01cc\nE\fE\16E\u01cf\13E\3E\3E\3E\3E"+
		"\5E\u01d5\nE\3E\3E\3E\3E\3F\7F\u01dc\nF\fF\16F\u01df\13F\3F\6F\u01e2\n"+
		"F\rF\16F\u01e3\3F\3F\3F\3F\3F\3G\7G\u01ec\nG\fG\16G\u01ef\13G\3G\3G\3"+
		"G\3G\3G\3H\3H\3H\5H\u01f9\nH\3H\3H\5H\u01fd\nH\6H\u01ff\nH\rH\16H\u0200"+
		"\3H\3H\3I\7I\u0206\nI\fI\16I\u0209\13I\3I\3I\3I\3I\3I\3\u0149\2J\6\'\b"+
		"(\n\37\f\36\16\35\20&\22%\24#\26$\30)\32\"\34*\36,  \"\34$!&+(\r*\31,"+
		"\t.\n\60\13\62\f\64\16\66\178\20:\21<\22>\23@\24B\25D\26F\27H\30J\32L"+
		"\33N\2P\2R\2T\2V\2X\2Z\7\\\6^\4`\5b-d.f/h\bj\60l\61n\62p\63r\64t\65v\66"+
		"x\67z8|9~:\u0080;\u0082<\u0084=\u0086>\u0088?\u008a\2\u008c@\u008eA\u0090"+
		"B\u0092\2\u0094C\6\2\3\4\5\34\4\2EEee\4\2CCcc\4\2UUuu\4\2GGgg\4\2KKkk"+
		"\4\2HHhh\4\2NNnn\4\2YYyy\4\2JJjj\4\2VVvv\4\2PPpp\4\2QQqq\4\2RRrr\4\2T"+
		"Ttt\4\2XXxx\4\2FFff\4\2WWww\3\2C\\\6\2\62;C\\aac|\3\2c|\4\2\13\17\"\""+
		"\3\3\f\f\5\2\f\f$$^^\5\2\2\2\f\f$$\4\2\f\f$$\5\2\2\2\f\r$$\u0218\2\6\3"+
		"\2\2\2\2\b\3\2\2\2\2\n\3\2\2\2\2\f\3\2\2\2\2\16\3\2\2\2\2\20\3\2\2\2\2"+
		"\22\3\2\2\2\2\24\3\2\2\2\2\26\3\2\2\2\2\30\3\2\2\2\2\32\3\2\2\2\2\34\3"+
		"\2\2\2\2\36\3\2\2\2\2 \3\2\2\2\2\"\3\2\2\2\2$\3\2\2\2\2&\3\2\2\2\2(\3"+
		"\2\2\2\2*\3\2\2\2\2,\3\2\2\2\2.\3\2\2\2\2\60\3\2\2\2\2\62\3\2\2\2\2\64"+
		"\3\2\2\2\2\66\3\2\2\2\28\3\2\2\2\2:\3\2\2\2\2<\3\2\2\2\2>\3\2\2\2\2@\3"+
		"\2\2\2\2B\3\2\2\2\2D\3\2\2\2\2F\3\2\2\2\2H\3\2\2\2\2J\3\2\2\2\2L\3\2\2"+
		"\2\2Z\3\2\2\2\2\\\3\2\2\2\2^\3\2\2\2\2`\3\2\2\2\2b\3\2\2\2\2d\3\2\2\2"+
		"\2f\3\2\2\2\2h\3\2\2\2\2j\3\2\2\2\2l\3\2\2\2\2n\3\2\2\2\2p\3\2\2\2\3r"+
		"\3\2\2\2\3t\3\2\2\2\3v\3\2\2\2\3x\3\2\2\2\3z\3\2\2\2\4|\3\2\2\2\4~\3\2"+
		"\2\2\4\u0080\3\2\2\2\4\u0082\3\2\2\2\4\u0084\3\2\2\2\4\u0086\3\2\2\2\5"+
		"\u0088\3\2\2\2\5\u008a\3\2\2\2\5\u008c\3\2\2\2\5\u008e\3\2\2\2\5\u0090"+
		"\3\2\2\2\5\u0092\3\2\2\2\5\u0094\3\2\2\2\6\u0096\3\2\2\2\b\u009b\3\2\2"+
		"\2\n\u00a0\3\2\2\2\f\u00a3\3\2\2\2\16\u00a6\3\2\2\2\20\u00ab\3\2\2\2\22"+
		"\u00b1\3\2\2\2\24\u00b6\3\2\2\2\26\u00bb\3\2\2\2\30\u00c0\3\2\2\2\32\u00c3"+
		"\3\2\2\2\34\u00c7\3\2\2\2\36\u00cb\3\2\2\2 \u00cf\3\2\2\2\"\u00d2\3\2"+
		"\2\2$\u00d8\3\2\2\2&\u00e1\3\2\2\2(\u00e8\3\2\2\2*\u00ea\3\2\2\2,\u00ed"+
		"\3\2\2\2.\u00ef\3\2\2\2\60\u00f1\3\2\2\2\62\u00f3\3\2\2\2\64\u00f5\3\2"+
		"\2\2\66\u00f7\3\2\2\28\u00f9\3\2\2\2:\u00fb\3\2\2\2<\u00fd\3\2\2\2>\u00ff"+
		"\3\2\2\2@\u0101\3\2\2\2B\u0103\3\2\2\2D\u0105\3\2\2\2F\u0107\3\2\2\2H"+
		"\u0109\3\2\2\2J\u010b\3\2\2\2L\u010e\3\2\2\2N\u0111\3\2\2\2P\u0113\3\2"+
		"\2\2R\u0115\3\2\2\2T\u0117\3\2\2\2V\u011a\3\2\2\2X\u011f\3\2\2\2Z\u0126"+
		"\3\2\2\2\\\u012c\3\2\2\2^\u012e\3\2\2\2`\u0135\3\2\2\2b\u013d\3\2\2\2"+
		"d\u0143\3\2\2\2f\u0151\3\2\2\2h\u0156\3\2\2\2j\u0161\3\2\2\2l\u0167\3"+
		"\2\2\2n\u016c\3\2\2\2p\u0174\3\2\2\2r\u0177\3\2\2\2t\u017d\3\2\2\2v\u0183"+
		"\3\2\2\2x\u0189\3\2\2\2z\u018f\3\2\2\2|\u0193\3\2\2\2~\u0199\3\2\2\2\u0080"+
		"\u019f\3\2\2\2\u0082\u01a5\3\2\2\2\u0084\u01a9\3\2\2\2\u0086\u01af\3\2"+
		"\2\2\u0088\u01b3\3\2\2\2\u008a\u01b8\3\2\2\2\u008c\u01c2\3\2\2\2\u008e"+
		"\u01dd\3\2\2\2\u0090\u01ed\3\2\2\2\u0092\u01fe\3\2\2\2\u0094\u0207\3\2"+
		"\2\2\u0096\u0097\t\2\2\2\u0097\u0098\t\3\2\2\u0098\u0099\t\4\2\2\u0099"+
		"\u009a\t\5\2\2\u009a\7\3\2\2\2\u009b\u009c\t\5\2\2\u009c\u009d\t\4\2\2"+
		"\u009d\u009e\t\3\2\2\u009e\u009f\t\2\2\2\u009f\t\3\2\2\2\u00a0\u00a1\t"+
		"\6\2\2\u00a1\u00a2\t\7\2\2\u00a2\13\3\2\2\2\u00a3\u00a4\t\7\2\2\u00a4"+
		"\u00a5\t\6\2\2\u00a5\r\3\2\2\2\u00a6\u00a7\t\5\2\2\u00a7\u00a8\t\b\2\2"+
		"\u00a8\u00a9\t\4\2\2\u00a9\u00aa\t\5\2\2\u00aa\17\3\2\2\2\u00ab\u00ac"+
		"\t\t\2\2\u00ac\u00ad\t\n\2\2\u00ad\u00ae\t\6\2\2\u00ae\u00af\t\b\2\2\u00af"+
		"\u00b0\t\5\2\2\u00b0\21\3\2\2\2\u00b1\u00b2\t\13\2\2\u00b2\u00b3\t\n\2"+
		"\2\u00b3\u00b4\t\5\2\2\u00b4\u00b5\t\f\2\2\u00b5\23\3\2\2\2\u00b6\u00b7"+
		"\t\b\2\2\u00b7\u00b8\t\r\2\2\u00b8\u00b9\t\r\2\2\u00b9\u00ba\t\16\2\2"+
		"\u00ba\25\3\2\2\2\u00bb\u00bc\t\16\2\2\u00bc\u00bd\t\r\2\2\u00bd\u00be"+
		"\t\r\2\2\u00be\u00bf\t\b\2\2\u00bf\27\3\2\2\2\u00c0\u00c1\t\r\2\2\u00c1"+
		"\u00c2\t\7\2\2\u00c2\31\3\2\2\2\u00c3\u00c4\t\b\2\2\u00c4\u00c5\t\5\2"+
		"\2\u00c5\u00c6\t\13\2\2\u00c6\33\3\2\2\2\u00c7\u00c8\t\f\2\2\u00c8\u00c9"+
		"\t\5\2\2\u00c9\u00ca\t\t\2\2\u00ca\35\3\2\2\2\u00cb\u00cc\t\f\2\2\u00cc"+
		"\u00cd\t\r\2\2\u00cd\u00ce\t\13\2\2\u00ce\37\3\2\2\2\u00cf\u00d0\t\6\2"+
		"\2\u00d0\u00d1\t\f\2\2\u00d1!\3\2\2\2\u00d2\u00d3\t\2\2\2\u00d3\u00d4"+
		"\t\b\2\2\u00d4\u00d5\t\3\2\2\u00d5\u00d6\t\4\2\2\u00d6\u00d7\t\4\2\2\u00d7"+
		"#\3\2\2\2\u00d8\u00d9\t\6\2\2\u00d9\u00da\t\f\2\2\u00da\u00db\t\n\2\2"+
		"\u00db\u00dc\t\5\2\2\u00dc\u00dd\t\17\2\2\u00dd\u00de\t\6\2\2\u00de\u00df"+
		"\t\13\2\2\u00df\u00e0\t\4\2\2\u00e0%\3\2\2\2\u00e1\u00e2\t\6\2\2\u00e2"+
		"\u00e3\t\4\2\2\u00e3\u00e4\t\20\2\2\u00e4\u00e5\t\r\2\2\u00e5\u00e6\t"+
		"\6\2\2\u00e6\u00e7\t\21\2\2\u00e7\'\3\2\2\2\u00e8\u00e9\7=\2\2\u00e9)"+
		"\3\2\2\2\u00ea\u00eb\7?\2\2\u00eb\u00ec\7@\2\2\u00ec+\3\2\2\2\u00ed\u00ee"+
		"\7*\2\2\u00ee-\3\2\2\2\u00ef\u00f0\7+\2\2\u00f0/\3\2\2\2\u00f1\u00f2\7"+
		"<\2\2\u00f2\61\3\2\2\2\u00f3\u00f4\7B\2\2\u00f4\63\3\2\2\2\u00f5\u00f6"+
		"\7.\2\2\u00f6\65\3\2\2\2\u00f7\u00f8\7-\2\2\u00f8\67\3\2\2\2\u00f9\u00fa"+
		"\7/\2\2\u00fa9\3\2\2\2\u00fb\u00fc\7,\2\2\u00fc;\3\2\2\2\u00fd\u00fe\7"+
		"\61\2\2\u00fe=\3\2\2\2\u00ff\u0100\7\u0080\2\2\u0100?\3\2\2\2\u0101\u0102"+
		"\7>\2\2\u0102A\3\2\2\2\u0103\u0104\7?\2\2\u0104C\3\2\2\2\u0105\u0106\7"+
		"}\2\2\u0106E\3\2\2\2\u0107\u0108\7\177\2\2\u0108G\3\2\2\2\u0109\u010a"+
		"\7\60\2\2\u010aI\3\2\2\2\u010b\u010c\7>\2\2\u010c\u010d\7?\2\2\u010dK"+
		"\3\2\2\2\u010e\u010f\7>\2\2\u010f\u0110\7/\2\2\u0110M\3\2\2\2\u0111\u0112"+
		"\4C\\\2\u0112O\3\2\2\2\u0113\u0114\4c|\2\u0114Q\3\2\2\2\u0115\u0116\4"+
		"\62;\2\u0116S\3\2\2\2\u0117\u0118\7^\2\2\u0118\u0119\13\2\2\2\u0119U\3"+
		"\2\2\2\u011a\u011b\7v\2\2\u011b\u011c\t\17\2\2\u011c\u011d\t\22\2\2\u011d"+
		"\u011e\t\5\2\2\u011eW\3\2\2\2\u011f\u0120\7h\2\2\u0120\u0121\t\3\2\2\u0121"+
		"\u0122\t\b\2\2\u0122\u0123\t\4\2\2\u0123\u0124\t\5\2\2\u0124Y\3\2\2\2"+
		"\u0125\u0127\5R(\2\u0126\u0125\3\2\2\2\u0127\u0128\3\2\2\2\u0128\u0126"+
		"\3\2\2\2\u0128\u0129\3\2\2\2\u0129[\3\2\2\2\u012a\u012d\5V*\2\u012b\u012d"+
		"\5X+\2\u012c\u012a\3\2\2\2\u012c\u012b\3\2\2\2\u012d]\3\2\2\2\u012e\u0132"+
		"\t\23\2\2\u012f\u0131\t\24\2\2\u0130\u012f\3\2\2\2\u0131\u0134\3\2\2\2"+
		"\u0132\u0130\3\2\2\2\u0132\u0133\3\2\2\2\u0133_\3\2\2\2\u0134\u0132\3"+
		"\2\2\2\u0135\u0139\t\25\2\2\u0136\u0138\t\24\2\2\u0137\u0136\3\2\2\2\u0138"+
		"\u013b\3\2\2\2\u0139\u0137\3\2\2\2\u0139\u013a\3\2\2\2\u013aa\3\2\2\2"+
		"\u013b\u0139\3\2\2\2\u013c\u013e\t\26\2\2\u013d\u013c\3\2\2\2\u013e\u013f"+
		"\3\2\2\2\u013f\u013d\3\2\2\2\u013f\u0140\3\2\2\2\u0140\u0141\3\2\2\2\u0141"+
		"\u0142\b\60\2\2\u0142c\3\2\2\2\u0143\u0144\7/\2\2\u0144\u0145\7/\2\2\u0145"+
		"\u0149\3\2\2\2\u0146\u0148\13\2\2\2\u0147\u0146\3\2\2\2\u0148\u014b\3"+
		"\2\2\2\u0149\u014a\3\2\2\2\u0149\u0147\3\2\2\2\u014a\u014d\3\2\2\2\u014b"+
		"\u0149\3\2\2\2\u014c\u014e\t\27\2\2\u014d\u014c\3\2\2\2\u014e\u014f\3"+
		"\2\2\2\u014f\u0150\b\61\2\2\u0150e\3\2\2\2\u0151\u0152\7$\2\2\u0152\u0153"+
		"\3\2\2\2\u0153\u0154\b\62\2\2\u0154\u0155\b\62\3\2\u0155g\3\2\2\2\u0156"+
		"\u015b\7$\2\2\u0157\u015a\5T)\2\u0158\u015a\n\30\2\2\u0159\u0157\3\2\2"+
		"\2\u0159\u0158\3\2\2\2\u015a\u015d\3\2\2\2\u015b\u0159\3\2\2\2\u015b\u015c"+
		"\3\2\2\2\u015c\u015e\3\2\2\2\u015d\u015b\3\2\2\2\u015e\u015f\7$\2\2\u015f"+
		"\u0160\b\63\4\2\u0160i\3\2\2\2\u0161\u0162\7*\2\2\u0162\u0163\7,\2\2\u0163"+
		"\u0164\3\2\2\2\u0164\u0165\b\64\2\2\u0165\u0166\b\64\5\2\u0166k\3\2\2"+
		"\2\u0167\u0168\7,\2\2\u0168\u0169\7+\2\2\u0169\u016a\3\2\2\2\u016a\u016b"+
		"\b\65\6\2\u016bm\3\2\2\2\u016c\u016d\7*\2\2\u016d\u016e\7,\2\2\u016e\u016f"+
		"\3\2\2\2\u016f\u0170\7\2\2\3\u0170\u0171\b\66\7\2\u0171\u0172\3\2\2\2"+
		"\u0172\u0173\b\66\b\2\u0173o\3\2\2\2\u0174\u0175\13\2\2\2\u0175\u0176"+
		"\b\67\t\2\u0176q\3\2\2\2\u0177\u0178\7*\2\2\u0178\u0179\7,\2\2\u0179\u017a"+
		"\3\2\2\2\u017a\u017b\7\2\2\3\u017b\u017c\b8\n\2\u017cs\3\2\2\2\u017d\u017e"+
		"\7*\2\2\u017e\u017f\7,\2\2\u017f\u0180\3\2\2\2\u0180\u0181\b9\2\2\u0181"+
		"\u0182\b9\13\2\u0182u\3\2\2\2\u0183\u0184\7,\2\2\u0184\u0185\7+\2\2\u0185"+
		"\u0186\3\2\2\2\u0186\u0187\b:\2\2\u0187\u0188\b:\f\2\u0188w\3\2\2\2\u0189"+
		"\u018a\13\2\2\2\u018a\u018b\7\2\2\3\u018b\u018c\b;\r\2\u018c\u018d\3\2"+
		"\2\2\u018d\u018e\b;\b\2\u018ey\3\2\2\2\u018f\u0190\13\2\2\2\u0190\u0191"+
		"\3\2\2\2\u0191\u0192\b<\2\2\u0192{\3\2\2\2\u0193\u0194\7*\2\2\u0194\u0195"+
		"\7,\2\2\u0195\u0196\3\2\2\2\u0196\u0197\7\2\2\3\u0197\u0198\b=\16\2\u0198"+
		"}\3\2\2\2\u0199\u019a\7*\2\2\u019a\u019b\7,\2\2\u019b\u019c\3\2\2\2\u019c"+
		"\u019d\b>\2\2\u019d\u019e\b>\13\2\u019e\177\3\2\2\2\u019f\u01a0\7,\2\2"+
		"\u01a0\u01a1\7+\2\2\u01a1\u01a2\3\2\2\2\u01a2\u01a3\b?\2\2\u01a3\u01a4"+
		"\b?\f\2\u01a4\u0081\3\2\2\2\u01a5\u01a6\13\2\2\2\u01a6\u01a7\7\2\2\3\u01a7"+
		"\u01a8\b@\17\2\u01a8\u0083\3\2\2\2\u01a9\u01aa\7,\2\2\u01aa\u01ab\7+\2"+
		"\2\u01ab\u01ac\3\2\2\2\u01ac\u01ad\7\2\2\3\u01ad\u01ae\bA\20\2\u01ae\u0085"+
		"\3\2\2\2\u01af\u01b0\13\2\2\2\u01b0\u01b1\3\2\2\2\u01b1\u01b2\bB\2\2\u01b2"+
		"\u0087\3\2\2\2\u01b3\u01b4\7$\2\2\u01b4\u01b5\bC\21\2\u01b5\u01b6\3\2"+
		"\2\2\u01b6\u01b7\bC\f\2\u01b7\u0089\3\2\2\2\u01b8\u01b9\7^\2\2\u01b9\u01ba"+
		"\7$\2\2\u01ba\u01bb\3\2\2\2\u01bb\u01bc\13\2\2\2\u01bc\u01bd\3\2\2\2\u01bd"+
		"\u01be\bD\22\2\u01be\u008b\3\2\2\2\u01bf\u01c1\n\31\2\2\u01c0\u01bf\3"+
		"\2\2\2\u01c1\u01c4\3\2\2\2\u01c2\u01c0\3\2\2\2\u01c2\u01c3\3\2\2\2\u01c3"+
		"\u01c6\3\2\2\2\u01c4\u01c2\3\2\2\2\u01c5\u01c7\7\2\2\2\u01c6\u01c5\3\2"+
		"\2\2\u01c7\u01c8\3\2\2\2\u01c8\u01c6\3\2\2\2\u01c8\u01c9\3\2\2\2\u01c9"+
		"\u01cd\3\2\2\2\u01ca\u01cc\n\32\2\2\u01cb\u01ca\3\2\2\2\u01cc\u01cf\3"+
		"\2\2\2\u01cd\u01cb\3\2\2\2\u01cd\u01ce\3\2\2\2\u01ce\u01d4\3\2\2\2\u01cf"+
		"\u01cd\3\2\2\2\u01d0\u01d5\t\32\2\2\u01d1\u01d2\7G\2\2\u01d2\u01d3\7Q"+
		"\2\2\u01d3\u01d5\7H\2\2\u01d4\u01d0\3\2\2\2\u01d4\u01d1\3\2\2\2\u01d5"+
		"\u01d6\3\2\2\2\u01d6\u01d7\bE\23\2\u01d7\u01d8\3\2\2\2\u01d8\u01d9\bE"+
		"\b\2\u01d9\u008d\3\2\2\2\u01da\u01dc\n\32\2\2\u01db\u01da\3\2\2\2\u01dc"+
		"\u01df\3\2\2\2\u01dd\u01db\3\2\2\2\u01dd\u01de\3\2\2\2\u01de\u01e1\3\2"+
		"\2\2\u01df\u01dd\3\2\2\2\u01e0\u01e2\7^\2\2\u01e1\u01e0\3\2\2\2\u01e2"+
		"\u01e3\3\2\2\2\u01e3\u01e1\3\2\2\2\u01e3\u01e4\3\2\2\2\u01e4\u01e5\3\2"+
		"\2\2\u01e5\u01e6\7\2\2\3\u01e6\u01e7\bF\24\2\u01e7\u01e8\3\2\2\2\u01e8"+
		"\u01e9\bF\b\2\u01e9\u008f\3\2\2\2\u01ea\u01ec\n\32\2\2\u01eb\u01ea\3\2"+
		"\2\2\u01ec\u01ef\3\2\2\2\u01ed\u01eb\3\2\2\2\u01ed\u01ee\3\2\2\2\u01ee"+
		"\u01f0\3\2\2\2\u01ef\u01ed\3\2\2\2\u01f0\u01f1\7\f\2\2\u01f1\u01f2\bG"+
		"\25\2\u01f2\u01f3\3\2\2\2\u01f3\u01f4\bG\b\2\u01f4\u0091\3\2\2\2\u01f5"+
		"\u01f8\n\33\2\2\u01f6\u01f7\7^\2\2\u01f7\u01f9\7\f\2\2\u01f8\u01f6\3\2"+
		"\2\2\u01f8\u01f9\3\2\2\2\u01f9\u01fc\3\2\2\2\u01fa\u01fb\7^\2\2\u01fb"+
		"\u01fd\7$\2\2\u01fc\u01fa\3\2\2\2\u01fc\u01fd\3\2\2\2\u01fd\u01ff\3\2"+
		"\2\2\u01fe\u01f5\3\2\2\2\u01ff\u0200\3\2\2\2\u0200\u01fe\3\2\2\2\u0200"+
		"\u0201\3\2\2\2\u0201\u0202\3\2\2\2\u0202\u0203\bH\22\2\u0203\u0093\3\2"+
		"\2\2\u0204\u0206\n\32\2\2\u0205\u0204\3\2\2\2\u0206\u0209\3\2\2\2\u0207"+
		"\u0205\3\2\2\2\u0207\u0208\3\2\2\2\u0208\u020a\3\2\2\2\u0209\u0207\3\2"+
		"\2\2\u020a\u020b\7\2\2\3\u020b\u020c\bI\26\2\u020c\u020d\3\2\2\2\u020d"+
		"\u020e\bI\b\2\u020e\u0095\3\2\2\2\32\2\3\4\5\u0128\u012c\u0132\u0139\u013f"+
		"\u0149\u014d\u0159\u015b\u01c2\u01c8\u01cd\u01d4\u01dd\u01e3\u01ed\u01f8"+
		"\u01fc\u0200\u0207\27\b\2\2\7\5\2\3\63\2\7\3\2\3\65\3\3\66\4\4\2\2\3\67"+
		"\5\38\6\7\4\2\6\2\2\3;\7\3=\b\3@\t\3A\n\3C\13\5\2\2\3E\f\3F\r\3G\16\3"+
		"I\17";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}