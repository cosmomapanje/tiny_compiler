/*
 * <program>		-> begin <statement list> end
 * <statement list>	-> <statement> {<statement>}
 * <statement>		-> ID := <expression>
 * <statement> 		-> read ( <id list> ) ;
 * <statement>		-> write ( <expr list> ) ;
 * <id list>		-> ID {, ID}
 * <expr list>		-> <expression> {, <expression>}
 * <expression>		-> <primary> {<add op> <primary>}
 * <primary>		-> ( <expression> )
 * <primary>		-> ID
 * <primary>		-> INTLITERAL
 * <add op>		-> PLUSOP
 * <add op>		-> MINUSOP
 * <system goal>	-> <program> SCANEOF
 */
