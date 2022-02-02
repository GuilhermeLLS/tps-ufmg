(* Plc Lexer *)

(* User declarations *)

open Tokens
type pos = int
type slvalue = Tokens.svalue
type ('a,'b) token = ('a,'b) Tokens.token
type lexresult = (slvalue, pos)token

(* A function to print a message error on the screen. *)
val error = fn x => TextIO.output(TextIO.stdOut, x ^ "\n")
val lineNumber = ref 0

fun parseInt word =
    case Int.fromString word of
    SOME integer => integer
    |  NONE => raise Fail ("Not possible to convert the string '" ^ word ^ "' to integer")

(* Get the current line being read. *)
fun getLineAsString() =
    let
        val lineNum = !lineNumber
    in
        Int.toString lineNum
    end


fun keyWord (s, lpos, rpos) = 
    case s of
    "fun" => FUN (lpos, rpos)
    | "Int" => INT (lpos, rpos)
    | "fn" => FN (lpos, rpos)
    | "end" => END (lpos, rpos)
    | "var" => VAR (lpos, rpos)
    | "rec" => REC (lpos, rpos)
    | "match" => MATCH (lpos, rpos)
    | "with" => WITH (lpos, rpos)
    | "print" => PRINT (lpos, rpos)
    | "if" => IF (lpos, rpos)
    | "else" => ELSE (lpos, rpos)
    | "then" => THEN (lpos, rpos)
    | "Nil" => NIL (lpos, rpos)
    | "Bool" => BOOL (lpos, rpos)
    | "true" => TRUE (lpos, rpos)
    | "false" => FALSE (lpos, rpos)
    | "ise" => ISE (lpos, rpos)
    | "hd" => HD (lpos, rpos)
    | "tl" => TL (lpos, rpos)
    | "_" => UNDERSCORE (lpos, rpos)
    | _ => NAME (s, lpos, rpos)


(* Define what to do when the end of the file is reached. *)
fun eof () = Tokens.EOF(0,0)

(* Initialize the lexer. *)
fun init() = ()
%%
%header (functor PlcLexerFun(structure Tokens: PlcParser_TOKENS));
alpha=[A-Za-z];
number=[0-9];
whitespace=[\ \t];
identifier=[a-zA-Z_][a-zA-Z_0-9]*;
%s COMMENT;
%%

\n => (lineNumber := !lineNumber + 1; lex());
<INITIAL>{whitespace}+ => (lex());
<INITIAL>{number}+ => (CINT(parseInt(yytext), yypos, yypos));
<INITIAL>{identifier} => (keyWord(yytext, yypos, yypos));
<INITIAL>"!" => (NEGATION(yypos, yypos));
<INITIAL>"&&" => (AND(yypos, yypos));
<INITIAL>"+" => (PLUS(yypos, yypos));
<INITIAL>"-" => (MINUS(yypos, yypos));
<INITIAL>"*" => (MULTIPLY(yypos, yypos));
<INITIAL>"/" => (DIVISION(yypos, yypos));
<INITIAL>"=" => (EQUAL(yypos, yypos));
<INITIAL>"!=" => (DIFFERENT(yypos, yypos));
<INITIAL>"<" => (LOWERTHAN(yypos, yypos));
<INITIAL>"<=" => (LOWERTHANEQUAL(yypos, yypos));
<INITIAL>"::" => (DESTRUCT(yypos, yypos));
<INITIAL>":" => (COLON(yypos, yypos));
<INITIAL>";" => (SEMICOLON(yypos, yypos));
<INITIAL>"," => (COMMA(yypos, yypos));
<INITIAL>"->" => (MATCHARROW(yypos, yypos));
<INITIAL>"|" => (MATCHOR(yypos, yypos));
<INITIAL>"=>" => (FUNCTIONARROW(yypos, yypos));
<INITIAL>"(" => (LEFTPARENTHESES(yypos, yypos));
<INITIAL>")" => (RIGHTPARENTHESES(yypos, yypos));
<INITIAL>"{" => (LEFTCURLYBRACE(yypos, yypos));
<INITIAL>"}" => (RIGHTCURLYBRACE(yypos, yypos));
<INITIAL>"[" => (LEFTBRACKET(yypos, yypos));
<INITIAL>"]" => (RIGHTBRACKET(yypos, yypos));
<INITIAL>"(*" => (YYBEGIN COMMENT; lex());
<COMMENT>"*)" => (YYBEGIN INITIAL; lex());
<COMMENT>. => (lex());
<INITIAL>. => (error("\n*** Lexer could not parse character. Please insert a valid character. ***\n");
    raise Fail("Lexer error: invalid character. " ^yytext));