
The game has 4 main parts (creating cards,saving to file ,reading from file,keeping status
track )

 First i tackled down by creating player's card
The number of players were given by user input from there 
i created double pointer for pointer of ints to hold bingo numbers
then filled up all cells in the arrays with random non repeating numbers
because we need only 5 numbers in a row i created random generated 3X5 array of indeces
and mapped the indeces into player's card,zeros swapped with astericks.
In order to make all corners filled with numbers i did check the indeces value on 0,8,18,26
if the value was greater than those numbers swap them.

For generating random non repeating numbers i used an array ,one to hold numbers
as indeces and set a flag 1 for not repeating.

Multisaved games were one of the most challenging task.I created two files ,one to hold num of players,player's cards and drawn numbers another file were to hold Id and length of bytes written to first file to get exact file pointer position.

Manual:
Start a new game will prompt you to pick the number of players(caution:non numbers entered, application is terminated).

Draw a number and app will display drawn number and count of drawn numbers
At that stage user can save a game ,see the game status or exit to the main menu.

 



