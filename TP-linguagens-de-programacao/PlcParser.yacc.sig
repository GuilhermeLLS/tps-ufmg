signature PlcParser_TOKENS =
sig
type ('a,'b) token
type svalue
val EOF:  'a * 'a -> (svalue,'a) token
val RIGHTBRACKET:  'a * 'a -> (svalue,'a) token
val LEFTBRACKET:  'a * 'a -> (svalue,'a) token
val RIGHTCURLYBRACE:  'a * 'a -> (svalue,'a) token
val LEFTCURLYBRACE:  'a * 'a -> (svalue,'a) token
val RIGHTPARENTHESES:  'a * 'a -> (svalue,'a) token
val LEFTPARENTHESES:  'a * 'a -> (svalue,'a) token
val FUNCTIONARROW:  'a * 'a -> (svalue,'a) token
val MATCHOR:  'a * 'a -> (svalue,'a) token
val MATCHARROW:  'a * 'a -> (svalue,'a) token
val COMMA:  'a * 'a -> (svalue,'a) token
val SEMICOLON:  'a * 'a -> (svalue,'a) token
val COLON:  'a * 'a -> (svalue,'a) token
val DESTRUCT:  'a * 'a -> (svalue,'a) token
val LOWERTHANEQUAL:  'a * 'a -> (svalue,'a) token
val LOWERTHAN:  'a * 'a -> (svalue,'a) token
val DIFFERENT:  'a * 'a -> (svalue,'a) token
val EQUAL:  'a * 'a -> (svalue,'a) token
val DIVISION:  'a * 'a -> (svalue,'a) token
val MULTIPLY:  'a * 'a -> (svalue,'a) token
val MINUS:  'a * 'a -> (svalue,'a) token
val PLUS:  'a * 'a -> (svalue,'a) token
val AND:  'a * 'a -> (svalue,'a) token
val NEGATION:  'a * 'a -> (svalue,'a) token
val CINT: (int) *  'a * 'a -> (svalue,'a) token
val NAME: (string) *  'a * 'a -> (svalue,'a) token
val UNDERSCORE:  'a * 'a -> (svalue,'a) token
val TL:  'a * 'a -> (svalue,'a) token
val HD:  'a * 'a -> (svalue,'a) token
val ISE:  'a * 'a -> (svalue,'a) token
val FALSE:  'a * 'a -> (svalue,'a) token
val TRUE:  'a * 'a -> (svalue,'a) token
val BOOL:  'a * 'a -> (svalue,'a) token
val NIL:  'a * 'a -> (svalue,'a) token
val THEN:  'a * 'a -> (svalue,'a) token
val ELSE:  'a * 'a -> (svalue,'a) token
val IF:  'a * 'a -> (svalue,'a) token
val PRINT:  'a * 'a -> (svalue,'a) token
val WITH:  'a * 'a -> (svalue,'a) token
val MATCH:  'a * 'a -> (svalue,'a) token
val REC:  'a * 'a -> (svalue,'a) token
val VAR:  'a * 'a -> (svalue,'a) token
val END:  'a * 'a -> (svalue,'a) token
val FN:  'a * 'a -> (svalue,'a) token
val INT:  'a * 'a -> (svalue,'a) token
val FUN:  'a * 'a -> (svalue,'a) token
end
signature PlcParser_LRVALS=
sig
structure Tokens : PlcParser_TOKENS
structure ParserData:PARSER_DATA
sharing type ParserData.Token.token = Tokens.token
sharing type ParserData.svalue = Tokens.svalue
end
