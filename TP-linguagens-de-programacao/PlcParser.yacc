%%

%name PlcParser

%pos int

%term FUN 
    | INT 
    | FN 
    | END 
    | VAR
    | REC 
    | MATCH 
    | WITH 
    | PRINT 
    | IF 
    | ELSE 
    | THEN 
    | NIL 
    | BOOL 
    | TRUE 
    | FALSE 
    | ISE 
    | HD 
    | TL 
    | UNDERSCORE 
    | NAME of string 
    | CINT of int 
    | NEGATION 
    | AND 
    | PLUS 
    | MINUS 
    | MULTIPLY
    | DIVISION
    | EQUAL
    | DIFFERENT 
    | LOWERTHAN
    | LOWERTHANEQUAL  
    | DESTRUCT 
    | COLON 
    | SEMICOLON
    | COMMA 
    | MATCHARROW 
    | MATCHOR 
    | FUNCTIONARROW 
    | LEFTPARENTHESES 
    | RIGHTPARENTHESES 
    | LEFTCURLYBRACE 
    | RIGHTCURLYBRACE 
    | LEFTBRACKET 
    | RIGHTBRACKET 
    | EOF

%nonterm Prog of expr 
    | Decl of expr
    | Expr of expr
    | AtomExpr of expr
    | AppExpr of expr
    | Const of expr
    | Comps of expr list
    | MatchExpr of (expr option * expr) list 
    | CondExpr of expr option
    | Args of (plcType * string) list
    | Params of (plcType * string) list
    | TypedVar of plcType * string
    | Type of plcType
    | AtomType of plcType
    | Types of plcType list

%eop EOF

%right SEMICOLON MATCHARROW
%nonassoc IF
%left ELSE 
%left AND 
%left EQUAL DIFFERENT
%left LOWERTHAN LOWERTHANEQUAL
%right DESTRUCT
%left PLUS MINUS
%left MULTIPLY DIVISION
%nonassoc NEGATION HD TL ISE PRINT NAME
%left LEFTBRACKET

%noshift EOF

%start Prog

%%

Prog: Expr (Expr) 
    | Decl (Decl)

Decl: VAR NAME EQUAL Expr SEMICOLON Prog (Let(NAME, Expr, Prog))
    | FUN NAME Args EQUAL Expr SEMICOLON Prog (Let(NAME, makeAnon(Args, Expr), Prog))
    | FUN REC NAME Args COLON Type EQUAL Expr SEMICOLON Prog (makeFun(NAME, Args, Type, Expr, Prog))

Expr: AtomExpr(AtomExpr)
    | AppExpr(AppExpr)
    | IF Expr THEN Expr ELSE Expr (If(Expr1, Expr2, Expr3))
    | MATCH Expr WITH MatchExpr (Match (Expr, MatchExpr))
    | NEGATION Expr (Prim1("!", Expr))
    | MINUS Expr (Prim1("-", Expr)) 
    | HD Expr (Prim1("hd", Expr))
    | TL Expr (Prim1("tl", Expr))
    | ISE Expr (Prim1("ise", Expr))
    | PRINT Expr (Prim1("print", Expr))
    | Expr AND Expr (Prim2("&&", Expr1, Expr2))
    | Expr PLUS Expr (Prim2("+", Expr1, Expr2))
    | Expr MINUS Expr (Prim2("-", Expr1, Expr2))
    | Expr MULTIPLY Expr (Prim2("*", Expr1, Expr2))
    | Expr DIVISION Expr (Prim2("/", Expr1, Expr2))
    | Expr EQUAL Expr (Prim2("=", Expr1, Expr2))
    | Expr DIFFERENT Expr (Prim2("!=", Expr1, Expr2))
    | Expr LOWERTHAN Expr (Prim2("<", Expr1, Expr2))
    | Expr LOWERTHANEQUAL Expr (Prim2("<=", Expr1, Expr2))
    | Expr DESTRUCT Expr (Prim2("::", Expr1, Expr2))
    | Expr SEMICOLON Expr (Prim2(";", Expr1, Expr2))
    | Expr LEFTBRACKET CINT RIGHTBRACKET (Item (CINT, Expr))

AtomExpr: Const (Const)
    | NAME (Var(NAME))
    | LEFTCURLYBRACE Prog RIGHTCURLYBRACE (Prog)
    | LEFTPARENTHESES Comps RIGHTPARENTHESES (List Comps)
    | LEFTPARENTHESES Expr RIGHTPARENTHESES (Expr)
    | FN Args FUNCTIONARROW Expr END (makeAnon(Args, Expr))

AppExpr: AtomExpr AtomExpr (Call(AtomExpr1, AtomExpr2))
    | AppExpr AtomExpr (Call(AppExpr, AtomExpr))

Const: TRUE (ConB true) | FALSE (ConB false)
    | CINT (ConI CINT)
    | LEFTPARENTHESES RIGHTPARENTHESES (List [])
    | LEFTPARENTHESES Type LEFTBRACKET RIGHTBRACKET RIGHTPARENTHESES (ESeq(Type))

Comps: Expr COMMA Expr (Expr1 :: Expr2 :: [])
    | Expr COMMA Comps (Expr :: Comps)

MatchExpr: END ([])
    | MATCHOR CondExpr MATCHARROW Expr MatchExpr ((CondExpr, Expr) :: MatchExpr)

CondExpr: Expr (SOME(Expr))
    | UNDERSCORE (NONE)

Args: LEFTPARENTHESES RIGHTPARENTHESES ([])
    | LEFTPARENTHESES Params RIGHTPARENTHESES (Params)

Params : TypedVar (TypedVar::[])
    | TypedVar COMMA Params (TypedVar::Params)

TypedVar: Type NAME ((Type, NAME))

Type: AtomType(AtomType)
    | LEFTPARENTHESES Types RIGHTPARENTHESES (ListT Types)
    | LEFTBRACKET Type RIGHTBRACKET (SeqT Type)
    | Type MATCHARROW Type (FunT (Type1, Type2))

AtomType: NIL (ListT [])
    | BOOL (BoolT)
    | INT (IntT)
    | LEFTPARENTHESES Type RIGHTPARENTHESES (Type)

Types: Type COMMA Type (Type1 :: Type2 :: [])
    | Type COMMA Types (Type :: Types)