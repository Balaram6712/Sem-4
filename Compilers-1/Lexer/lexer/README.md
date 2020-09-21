# COOL Compiler #
CooLexer.g4 has grammar rules for the lexer written for COOL programming language using ANTLR compiler.

The lexer for handling COOL programs needed to be taken care of in specific main things:
1) Integers,identifires and Special notations
2) Strings 
3) Comments
4) Keywords
5) White space


Some of the major error areas are:
1) Null character in a string.
2) Unterminated string constant when a string is not ended
3) EOF in string constant.
4) Back slash at the end of the file.
5) EOF in Comment.
Order of matching:
1)Keywords are needed to be matched before as some of them might become object id or type id which is incorrrect.

Rules declaration:
* Defining the file CoolLexer.g4 from Top to bottom, First it has tokens which are a list of tokens which will be generated accordingly when found in the given file.

* It has members functions which has functions like **reportError(String errorstring)** function which is called and a string is passed which is the error string and token of error type is generated in this function and setting the token type to ERROR.

* **reportUnmatched()** to report all the characters which are unmatched by the lexer will be called and executed accordingly and set the token type to ERROR.

* **processString()** is called when we need to generate a token for the valid matched string given and process it accordingly and it also handle the 'String constant too long' case as well along with 'String contains null character'.A empty string is taken every time this function is called and we process it accordingly and \n,\b,\t,\f are matched and added to the string as one charcater by iterating in a while loop for the text that has been passed and then the string length is checked for error if its length is greater than 1024 and the string is passed after that and function returns.

* After this the rules are defined accordingly special notations and keywords are declared according to the tokens given in the list.Then the special characters need to be defined based on the token corresponding to them.

* Next the rules definitons for handling the comments,strings,whitespace,TYPEID etc are handled.
Rules for keywords,identifiers and integers for example:
-OBJECTID : [a-z[\_a-zA-Z0-9]\*;
-TYPEID 	 : [A-Z]\_a-zA-Z0-9]\*;
-DIGIT	 : '0'..'9';
-INT_CONST:DIGIT+;
-Typeid has first letter small, Object id has first letter as capital letter.'[]' is used to match the multiple characters for the positon.

* WHITESPACE : [ \n\f\t\r\u000b]; to recognise the whitespace so that it can be ignored and can be used in rules for skipping those.
* UNMATCHED : . { reportUnmatched();}; to report any special symbols which do not satisfy the grammar rule and lying outside the string or the comments.


**Comments**
* Single line comments:
-When a '--' is observed ignore all the characters using 'skip' until a '\n' or EOF is found.

* Block Comments:
* The rules are written and ensured in such a way that closing and openings are correctly matched.Two modes are used for handling the situation of block comments.
* The two modes are MULTI_COMMENT and MULTI_MULTI_COMMENT.
* When a '(\*' is seen then pushMode(MULTI_COMMENT) and change the mode in which we further handle the incoming strings and '(\*' is ignored before changing the mode.
* If another '(\*' is seen then wee again pushMode(MULTI_MULTI_COMMENT) is entered.OTHER takes care of the characters to be ignored.If a EOF is seen in MULTI_COMMENT mode then it is an error 'EOF in comment'.When a '\*)' is seen we popMode and return to the previous mode which this mode has been called from.In MULTI_COMMENT mode when '(\*' is again observed we enter into another mode 'MULTI_MULTI_COMMENT' mode is pushed to handle the nested comments.
* In MULTI_MULTI_COMMENT in this mode REST is used to ignore the characters in th comments.In this mode nested comments recursively when a '(\*' is seen we get into the same mode 'MULTI_MULTI_COMMENT' using push mode and neglect this '(\*' using 'skip' to ignore.If EOF is found in this mode then it is an error EOF in comment. If '\*)' is seen then we popMode and return to the previous mode which it has been pushed from it may be nested comment also.Sometimes there is a possibility that after this '\*)' EOF may be found and this tells that it may be all the comments have not been balanced and EOF is found.

**Errors in comments**:
* Possible errors which can occur during comments is EOF, it is handled in single line case if by cheking EOF along with '\n' and that case has been handled.
* In case of multi or block comments if in the modes we enter due to comments we find (EOF) according to the errors this tells that 'EOF in comment' error and a error token has been generated and further continue to take in the tokens if any left.Also ERR_EOF_NEW is used to detect '(\*'(EOF) this and report error EOF in comment.
* EOF inside nested comments leads to an error EOF in comment. 

**Strings**:
When " is encountered STRING_MODE is pushed and the rules executed according the rules in STRING_MODE.After the string gets processed if it is valid then string constant is used to set the string as that type.ESC is used to recognise the ('\\'.) which is defined as fragment and used in STR_CONST.fragment is like defining a inline expression which can be used in other grammar rules.

* STRING_MODE:
- When '"' is observed the method processstring is called and the string is processed and we pop from the current mode and return to the Default mode.
- ERROR_BACK is used for the case to handle '\"' is used in the string and more indicates to take and check the next parts of the input.
- NULL_STR is used to detect the null character '\u0000' is used to detect is which is NULL in unicode and an error String contains null is detected and the mode is changed to default as the string containing Null is an error we need to evaluate the next tokens rather than this which is already an error. 
- BACK_SLASH is used to detect the error at the end of the file in a string which has not seen '"' closing quotes gives the backslash error and when it occurs in a string this rule takes care of that error and generates a token error for 'back slash erro at EOF'.
- ERROR_STRING is used to check if the string is terminated or not, it is terminated only when '"' is seen or '\' is seen before it gets '\n', so it will be turn out to be and error 'Unterminated string constant' is reported and token is generated correspondingly.
- STRING_MAIN is the main part which process the strings and neglects the null character,whitespace,'"' and process the string until a '"' closing is observed for the string, and also it recongnises if it contains '\' and '\"' when processed to it and ensure that it contains in the string constant and no error is given out for the correct string where '\"' and '\\' are usedfor literals to be used in string.
- EOF_STRING is an error if the string is not ended, for this '"','\n' and '\' are not seen so that the string has no closing and EOF seens in the same line and it generates an error EOF found in string constant.

* Any other characters which are not matched are reported using UNMATCHED by calling the method reportUnmatched(); method.  
* The handling of string literals '"' and '\' are taken care of and '\n','\b','\t','\f' are added to the string if found and added as one character only not as 2 seperate characters.The escaped characters are searched by using '\\' searching for litearal '\' and proceed accordingly.  

**Test Cases**
A good amount of testing has been done almost covering all the cases, testing on strings and escaped chaarcters has been done to ensure the correctness, also some of the file have been attached.These files covere following cases:

1)'test1.cl' contains testing of strings and various cases in strings with '\\' and other cases with unterminated string, if no backslash in a STR_CONST then we get a unterminated string constant error and next line the words are recognised outside the string as object id and type id when then see a '\"' we get another error as it is seen as opening for a new string.In another case '\"' to use the lietral quotes in the string constant are handled.
2)'test2.cl' cotains multiple sequence of strings and which have characters of literals like '\\','\"','\"--' etc are some of the chaarcters and are handled in the string and which corresponds to the actual quotes which is an error etc have been identified by the lexer.  
3)'test3.cl' contains 2 STR_CONST and EOF in comment error which is handled when a EOF is reached and the comments are not closed and also a unmatched '\*)' is given as error as it is not matched is detected by the lexer. 
4)'test4.cl' it can be opened in vim editor or u can open the file with utf-8 encoding in sublime this contains a null character and a back slash when the string goes to the next line, the null character is detected and error is reported and another string is detected as string constant and a commetns which has been ignored.
5)'test5.cl' containf a string constant which has greater than 1024 charcaters when run on the lexer it gives the errors it String constant too long and also a single line comment which is neglected.
6)'atoi.cl' is a program which has been submitted in the first assignments is also used for testing the lexer which has functions and detecting INT_CONST and checks out some other symbols and special notations by matching them.

The test cases cover the cases with strings and comments and recognising the string constants and typeid and object id other required errors by using the lexer.