# ParserTest  

## Description

  Please write a program to read a program source from stdin following the token definition 
and grammar rule at right.  
  If Yes, print each token’s type and the string of token seperated by a whitespace “ ” and 
end with a newline.   
  If No, print only “invalid input” with a newline. (don’t output any token!)
Your program has to check the source whether it follows the token and grammar rules or 
not.  

※測試檔案的換行皆為 \n

| Terminal  | Regular Expression | 
|-------|:-----:|
| ID   | '['A-Za-z_']''['A-Za-z0-9_']''*' |
