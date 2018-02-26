<h1>Invalid Cases:</h1>
<ul>
  
  <li>if start with symbol ( '.', '|', '*', '+', '#', ')' )</li>
  <li>if doesn't end with '#'</li>
  <li>no concatination sign before #</li>
  <li>adjacently placed '.' and '|'</li>
  <li>'*' or '+' after a symbol and not a character</li>
  <li>symbol and not a character after '('</li>
  <li>cases |* or |+ or ** or *+ or +* or ++ </li>
  <li>if 2 letters are placed adjacently withpout concatination sign ('.')</li>
  <li>if parentheses are not balanced</li>
  
</ul>


<h1>Sample inputs and outputs:</h1>

Input: (a|b.b)*.c*.#
<h3>Output:</h3>
Followpos(1) = { 1, 2, 4, 5 } <br>
Followpos(2) = { 3 }<br>
Followpos(3) = { 1, 2, 4, 5 }<br>
Followpos(4) = { 4, 5 }<br>
Followpos(5) = {  }<br>
<br><br><br>
Input: a*.b+|(a+.(b*|c))*|(a+.(b*|c+.(a+.b*|c))).#
<h3>Output:</h3>
Followpos(1) = { 1, 2 }<br>
Followpos(2) = { 2 }<br>
Followpos(3) = { 3, 4, 5, 3 }<br>
Followpos(4) = { 4, 3 }<br>
Followpos(5) = { 3 }<br>
Followpos(6) = { 6, 7, 8, 12 }<br>
Followpos(7) = { 7, 12 }<br>
Followpos(8) = { 8, 9, 11 }<br>
Followpos(9) = { 9, 10, 12 }<br>
Followpos(10) = { 10, 12 }<br>
Followpos(11) = { 12 }<br>
Followpos(12) = {  }<br>
