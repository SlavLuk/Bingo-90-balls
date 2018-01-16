
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
Name :Vyacheslav Lukyanov
id : G00339839
Program Description : Bingo 90 ball game

*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>


#define ROWS 3
#define COLS 9
#define DRAWN_NUM 90

	//function declaration
int* createPlayerCards(int*bingoNumbers, int* indecesOfBingoNumbers);
void printCard(int*card,char*blanks);
void printDrawnNumbers(int * bDrawnNum);
void printGameStat(int**player, int*bingoDrawnNum, int numOfPlayers);

void main() {
			
				//variables declaration and initialization 
			FILE * savedGame, *savedGameIds;
			bool fullHouseWin = false;
			bool found = false;	
			int fullHouse = 15;
			int ** player = NULL;
			int* bingoNumbers = NULL;
			int* indecesOfBingoNumbers = NULL;
			char*bingoBlank = NULL;
			int* bingoDrawnNum = NULL;
			int lens[100];
			int fileIds[100];
			int checkDrawnNum[91];
			int counterDrawnNum = 0, i = 0, j = 0, indexOfDrawn = 0, numOfPlayers, choice, drawnNumber;
			unsigned int len;
			unsigned int fileId = 0;
			int input;

			//set all values to 0
			memset(checkDrawnNum, 0, (DRAWN_NUM + 1) * sizeof(int));
			
				//seed rand function
			srand(time(NULL));
		
				//prompt user for input
			printf("Please enter 1 to Start a new Game\n");
			printf("Please enter 2 to Reload an old Game\n");
			printf("Please enter 3 to Exit the application\n");

			input = scanf("%d", &choice);

				//check user input if not digit terminate the programme
			if (input == 0) {

				exit(0);

			}

			while (choice !=3) {

				switch (choice) {

				case 1:
				case 2:

						if (choice == 1) {

							puts("\nStarting a new game. Please enter the number of players");
							scanf(" %d", &numOfPlayers);

							fullHouseWin = false;
							found = false;
							fullHouse = 15;										
							counterDrawnNum = 0;
							indexOfDrawn = 0;


							//allocate DRAWN_NUM ints and save pointer in bingoDrawnNum
							bingoDrawnNum = (int*)malloc(DRAWN_NUM * sizeof(int));

							//set all values in bingoDrawnNum to 0
							memset(bingoDrawnNum, 0, DRAWN_NUM * sizeof(int));

							//set all values in checkDrawnNum to 0
							memset(checkDrawnNum, 0, (DRAWN_NUM + 1) * sizeof(int));

								//allocate numOfPlayers double pointer to pointer of ints and save double pointer in player
							player = (int**)malloc(numOfPlayers * sizeof(int*));

								//allocate ROWS*COLS chars and save pointer in bingoBlank
							bingoBlank = (char*)malloc(ROWS*COLS * sizeof(char));

								//create player cards
							for (int k = 0; k < numOfPlayers; k++) {

								*(player + k) = createPlayerCards(bingoNumbers, indecesOfBingoNumbers);

								printf("\nPlayer %d card\n\n", k + 1);

								printCard(*(player + k), bingoBlank);

									}

						}else{

							//choice 2 reading saved game file
							savedGame = fopen("bingo.txt", "r");
							savedGameIds = fopen("savedname.txt", "r");

							int counter = 0;

							if (savedGame == NULL || savedGameIds == NULL){

								printf("\nFile cannot be opened\nNo saved games...\n\n");

								break;

								}else {

								//reading Ids 
								while (!feof(savedGameIds)) {

									fscanf(savedGameIds, "%d %d", &fileIds[counter], &lens[counter]);

									counter++;

									}
								}

								//check if any saved games exist
							if (counter == 1) {

								printf("\nNo Games to load\n\n");

									//close file
								if (savedGame != NULL) {

									fclose(savedGame);
								}

									//close file
								if (savedGameIds != NULL) {

									fclose(savedGameIds);
								}

								break;

									}else {

								printf("\nSelect the game ID to load\n");

								//loading saved ids
								for (int i = 0; i < (counter - 1); i++) {

									printf(" id) %d\n", fileIds[i]);

								}

								input = scanf("%d", &fileId);

								//check if user input is digit
								if (input ==0) {

									exit(0);
									
								}
							
								bool found = false;

								int j = 0;

									//check user input id against saved ids
								while (!found && j < (counter - 1)) {

									if (fileId == fileIds[j]) {

										//if id == 1 move file pointer to beginning 
										if (fileId == 1) { 

											len = 0;

											}else {

											len = lens[j - 1];

											}

											found = true;

									}else {

										j++;

										}
								}//end while loop

								if (savedGame != NULL) {

								
									if (found) {

										//set file pointer to len position
										fseek(savedGame, len, SEEK_SET);

										fscanf(savedGame, "%d\n", &numOfPlayers);

										//allocate numOfPlayers double pointer to pointer of ints and save double pointer in player
										player = (int**)malloc(numOfPlayers * sizeof(int*));

										//allocate ROWS*COLS chars and save pointer in bingoBlank
										bingoBlank = (char*)malloc((ROWS*COLS) * sizeof(char));

										memset(bingoBlank, 0, (ROWS*COLS) * sizeof(char));

										//recreating bingo cards
										for (int k = 0; k < numOfPlayers; k++) {
											
											*(player + k) = (int*)malloc(ROWS*COLS * sizeof(int));

											for (int j = 0; j < ROWS*COLS; j++) {

												fscanf(savedGame, "%d ", *(player + k) + j);

											}

										}

										counterDrawnNum = 0;

										//allocate DRAWN_NUM ints and save pointer in bingoDrawnNum
										bingoDrawnNum = (int*)malloc(DRAWN_NUM * sizeof(int));

										//set all values in bingoDrawnNum to 0
										memset(bingoDrawnNum, 0, DRAWN_NUM * sizeof(int));


										//recreating bingo drawn numbers
										for (int i = 0; i < DRAWN_NUM; i++) {

											fscanf(savedGame, "%d ", &bingoDrawnNum[i]);

											if (bingoDrawnNum[i] != 0) {

												counterDrawnNum = i + 1;

											}
										}
									}
									else {

										printf("\nInvalid Id ...\n\n");

										//close file
										if (savedGame != NULL) {

											fclose(savedGame);
										}

										//close file
										if (savedGameIds != NULL) {

											fclose(savedGameIds);
										}

										break;
									}

							}

							
						}


									if (savedGame != NULL) {

										fclose(savedGame);
									}

									if (savedGameIds != NULL) {

										fclose(savedGameIds);
									}

								//print out player's cards
								for (int k = 0; k < numOfPlayers; k++) {


									printf("\nPlayer %d card\n\n", k + 1);

									printCard(*(player + k), bingoBlank);

								}


					}
				

					//prompt input
					printf("\nPlease enter 1 to Draw the next number\n");
					printf("Please enter 2 to Save the game\n");
					printf("Please enter 3 to Output the game's status\n");
					printf("Please enter 4 to Exit the game\n");
					
					input = scanf("%d", &choice);

					//terminate app if not digit
					if (input == 0) {

						exit(0);

					}

					while (choice != 4) {


						switch (choice) {

						case 1:	

							//check on bingo drawn numbers saved in file
							if (counterDrawnNum != 0)                           
																						  
							{
								for (int i = 0; i < counterDrawnNum;i++) {               

									checkDrawnNum[bingoDrawnNum[i]] = 1; 
								}
							}

							//check on fullhouse achieved
							if ( !fullHouseWin) {

								found = false;
							

								while (!found ) {           

									//generating  random drawn number
									drawnNumber = 1 + rand() % DRAWN_NUM;
						
									if (checkDrawnNum[drawnNumber] == 0) {

										bingoDrawnNum[counterDrawnNum++] = drawnNumber;

										checkDrawnNum[drawnNumber] = 1;



										printf("\nThe number %d was drawn\n", drawnNumber);
										printf("Counting numbers drawn %d\n", counterDrawnNum);

										found = true;


										}//end if
								
								}//end while loop

								for (int k = 0; k < numOfPlayers; k++) {

									fullHouse = 15;

									for (int t = 0; t < DRAWN_NUM; t++) {

										if (bingoDrawnNum[t] != 0) {

											found = false;

											i = 0;

											//check drawn numbers against player bingo numbers
											while (i < COLS*ROWS && !found) {

												if (*(*(player + k) + i) == bingoDrawnNum[t]) {

												found = true;

												//if matched decrement 1
												fullHouse--;

												}else{

													i++;

												}
											}//end while loop

										}//if end

									}//end for loop


									//check if fullhouse stop drawing numbers
									if (fullHouse == 0) {

										fullHouseWin = true;
									}

								}//end for loop
								
							} else {

								printf("\nFull house has been achieved\n");

							}
						

							break;

						case 2:

							//open saved games files
							savedGame = fopen("bingo.txt","a");
							savedGameIds = fopen("savedname.txt", "a+");
							
							int counter = 0;

							if (savedGame == NULL)
							{
								printf("File cannot be opened\n");
							}
							if (savedGameIds == NULL)
							{
								printf("File cannot be opened\n");
							}
						
							if (savedGame != NULL) {
							
								//writing to file num of players,player's card ,bingo drawn numbers
								fprintf(savedGame, "\n%d\n", numOfPlayers);

								for (int k = 0; k < numOfPlayers; k++) {

									for (int i = 0; i < COLS*ROWS; i++) {

										fprintf(savedGame, "%d ",*(*(player+k)+i));

									}
									fprintf(savedGame, "%s\n","" );
								}

								for (int i = 0; i < DRAWN_NUM; i++) {

									fprintf(savedGame, "%d ", bingoDrawnNum[i]);

								}

								//the length from beginning to end saved game
								fseek(savedGame, 0, SEEK_END);

								//byte length written to savedGame file
								len = ftell(savedGame);

							}//end if

							if (savedGameIds != NULL) {

								//reading ids to determine position in order to write new id and bytes length

								while (!feof(savedGameIds)) {

									fscanf(savedGameIds, "%d ", &fileIds[counter]);

									counter++;
								}
							

								for (int i = 0; i < (counter - 1); i++) {

									fileId = fileIds[i];

								}

								fileId++;
								

								fprintf(savedGameIds, "%d %d\n", fileId, len);

							}
					
							printf("\nThe Game saved\n");

							//close files
							if (savedGame != NULL) {

								fclose(savedGame);
							}
							if (savedGameIds != NULL) {

								fclose(savedGameIds);
							}
					

							break;

						case 3:

							//print out all drawn numbers
							printDrawnNumbers(bingoDrawnNum);
							
							puts("\n\n");

							//print out game's stat
							printGameStat(player, bingoDrawnNum,numOfPlayers);

									break;

						default:
							puts("\nInvalid selection number\n");
						}

						printf("\nPlease enter 1 to Draw the next number\n");
						printf("Please enter 2 to Save the game\n");
						printf("Please enter 3 to Output the game's status\n");
						printf("Please enter 4 to Exit the game\n");

						input = scanf("%d", &choice);

						if (input == 0) {

							exit(0);

						}

					}

					free(player);
				

					break;
				
				default:

					puts("Invalid selection number\n");


				}

				printf("Please enter 1 to Start a new Game\n");
				printf("Please enter 2 to Reload an old Game\n");
				printf("Please enter 3 to Exit the application\n");

				input = scanf("%d", &choice);

				if (input == 0) {

					exit(0);

				}

			}


	getch();

	
}//end main

//function definition

void printGameStat(int**player, int*bingoDrawnNum,int numOfPlayers) {


	for (int k = 0; k < numOfPlayers; k++) {

		int corners = 4;
		int firstLine = 0;
		int secondLine = 0;
		int thirdLine = 0;
		int fullHouse = 15;

		//finding match numbers on 4 corners
		for (int t = 0; t < DRAWN_NUM; t++) {

			if (*(*(player + k) + 0) == bingoDrawnNum[t] ||
				*(*(player + k) + 8) == bingoDrawnNum[t] ||
				*(*(player + k) + 18) == bingoDrawnNum[t] ||
				*(*(player + k) + 26) == bingoDrawnNum[t]) {

				corners--;

			}

			//comparing drawn numbers against bingo card num
			if (bingoDrawnNum[t] != 0) {

				bool found = false;
				int i = 0;

				while (i <COLS*ROWS && !found) {

					if (*(*(player + k) + i) == bingoDrawnNum[t]) {

						fullHouse--;

						found = true;
					}
					else
					{
						i++;
					}
				}//end while loop


				if (found) {

					if (i <= 8) {

						firstLine++;

					}
					else if (i <= 17 && i >= 9) {

						secondLine++;

					}
					else if (i <= 26 && i >= 18) {

						thirdLine++;
					}


				}
			}//end if




		}//end inner for

		printf("Player %d requires:\n\n", k + 1);
		printf(" %d numbers for the four corners\n", corners);

		//finding the largest one line 

		if (firstLine >= secondLine && firstLine >= thirdLine) {

			printf(" %d numbers for the one line\n", 5 - firstLine);

			//finding the largest two line 

			if (secondLine >= thirdLine) {

				printf(" %d numbers for the two lines\n", (5 - firstLine) + (5 - secondLine));

			}
			else {

				printf(" %d numbers for the two lines\n", (5 - firstLine) + (5 - thirdLine));
			}

		}
		else if (secondLine >= firstLine && secondLine >= thirdLine) {


			printf(" %d numbers for the one line\n", 5 - secondLine);

			if (firstLine >= thirdLine) {

				printf(" %d numbers for the two lines\n", (5 - secondLine) + (5 - firstLine));
			}
			else {

				printf(" %d numbers for the two lines\n", (5 - secondLine) + (5 - thirdLine));

			}

		}
		else {

			printf(" %d numbers for the one line\n", 5 - thirdLine);

			if (secondLine >= firstLine) {

				printf(" %d numbers for the two lines\n", (5 - thirdLine) + (5 - secondLine));
			}
			else {

				printf(" %d numbers for the two lines\n", (5 - thirdLine) + (5 - firstLine));

			}

		}



		printf(" %d numbers for the full house\n", fullHouse);

		if (fullHouse == 0) {


			printf("\nFull house has been achieved by Player %d WON\n", k + 1);

		}

		puts("\n");


	}//end outer for
}

void printDrawnNumbers(int * bDrawnNum) {

	printf("\nThe following numbers were drawn:\n");

	for (int j = 0; j < DRAWN_NUM; j++) {

		if (bDrawnNum[j] != 0) {

			if (j % 9 == 0) {
				puts("\n");
			}
			printf("%3d,", bDrawnNum[j]);
		}
	}




}

void printCard(int*card, char*blanks) {


	for (int i = 0; i < ROWS; i++) {

		//substitute all zeros on *
		for (int j = 0; j < COLS; j++) {

			if (card[(i*COLS) + j] == 0) {

				blanks[(i*COLS) + j] = '*';
				
				printf("%4c", blanks[(i*COLS) + j]);

			}
			else {
			
				printf("%4d", card[(i*COLS) + j]);

			}
		}
		
				puts("\n");
							
	}
}

int* createPlayerCards(int*bingoNumbers, int* indecesOfBingoNumbers) {

	bool found;
	int i,value, j = 0, counter = 0;

	int checkValue[91];
	int checkIndex[27];

	bingoNumbers = (int*)malloc(ROWS*COLS * sizeof(int));
	indecesOfBingoNumbers = (int*)malloc(ROWS * 5 * sizeof(int));

	//initialize arrays to 0
	memset(checkValue, 0, (DRAWN_NUM + 1) * sizeof(int));
	memset(checkIndex, 0, (ROWS*COLS ) * sizeof(int));

	//Generating random non-repeating numbers

	for (int i = 0; i < ROWS; i++) {

		j = 0;

		while (j< COLS) {

			value = 1 + rand() % 10;

			value = (j * 10) + value;


			if (checkValue[value] == 0) {

				bingoNumbers[(i*COLS) + j] = value;

				checkValue[value] = 1;

				j++;

			}
		}
	}

	//Generating indeces

	for (i = 0; i < ROWS; i++) {

		j = 0;

		while (j < 5) {

			if (i == 0) {

				value = rand() % 9;

			}
			else if (i == 1) {

				value = 9 + rand() % 9;

			}
			else if (i == 2) {
			
				value = (i * 10) + rand() % 6;
			
			}

			if (checkIndex[value] == 0) {

				indecesOfBingoNumbers[(i * 5) + j] = value;

				checkIndex[value] = 1;

				j++;


			}

		}//end while loop	

	}//end for  loop

	//Making 4 corners
	 //swapping 0 index

		i = 0;
		found = false;
		int temp;

	while (i < 5 * ROWS) {

		if (indecesOfBingoNumbers[i] == 0) {

			if (i > 0) {

				temp = indecesOfBingoNumbers[0];

				indecesOfBingoNumbers[0] = indecesOfBingoNumbers[i];

				indecesOfBingoNumbers[i] = temp;

				found = true;
			}

		}
	

		i++;

	}

	if (!found) {

		indecesOfBingoNumbers[0] = 0;

	}

	//swapping 8 index

	found = false;
	i = 0;

	while (i < 5 * ROWS) {

		if (indecesOfBingoNumbers[i] == 8) {

			if (i > 0) {

				temp = indecesOfBingoNumbers[8];

				indecesOfBingoNumbers[8] = indecesOfBingoNumbers[i];

				indecesOfBingoNumbers[i] = temp;

				found = true;
			}

		}

		i++;

	}

	if (!found) {

		indecesOfBingoNumbers[4] = 8;

	}

	//swapping 18 index

	found = false;
	i = 0;

	while (i < 5 * ROWS) {

		if (indecesOfBingoNumbers[i] == 18) {

			if (i > 0) {

				temp = indecesOfBingoNumbers[18];

				indecesOfBingoNumbers[18] = indecesOfBingoNumbers[i];

				indecesOfBingoNumbers[i] = temp;

				found = true;
			}

		}

		i++;

	}

	if (!found) {

		indecesOfBingoNumbers[10] = 18;

	}

	//swapping 26 index
	found = false;
	i = 0;

	while (i < 5 * ROWS) {

		if (indecesOfBingoNumbers[i] == 26) {

			if (i > 0) {

				temp = indecesOfBingoNumbers[26];

				indecesOfBingoNumbers[26] = indecesOfBingoNumbers[i];

				indecesOfBingoNumbers[i] = temp;

				found = true;
			}

		}

		i++;

	}

	if (!found) {

		indecesOfBingoNumbers[14] = 26;

	}

	//Mapping indeces to bingo numbers

	found = false; 
	counter = 0;

	for (i = 0; i < (ROWS*COLS); i++) {

		while (counter < (5 * ROWS) && found == false) {

			if (i == indecesOfBingoNumbers[counter]) {


				found = true;
			}
			else {

				counter++;
			}

		}//end while loop

		if (!found) {

			bingoNumbers[i] = 0;
		}

		counter = 0;

		found = false;


	}//end for loop



	return bingoNumbers;
}