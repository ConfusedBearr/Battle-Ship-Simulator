/* ******************************************************************
*                                                                   *
*       Exam 2.0                                                    *
*       Coded By: Rodrigo Peixoto, William Cade, Lilly              *
*       Final Edits on: 04/03/2023                                  *
*                                                                   *
******************************************************************* */
#include <stdio.h>


#include <stdlib.h>


#include <time.h>


//define data type


struct boats {


    // (S) Seminole State Ship (3 Holes)


    // (A) Air Force Academy (5 Holes)


    // (V) Valencia Destroyer (4 Holes)


    // (E) Eskimo University (3 Holes)


    // (D) Deland High School (2 Holes)


    char boatname[30];





    int boatnum;


    //number of holes


    int boatsize;





    char boatchar;





    int boatHealth;


};



struct board {


    //y value


    int column;


    //x value


    int row;


    char seenChar;


    char hiddenChar;


    char hiddenBoard;


};



struct board boardMaker(struct board board[10][10], struct boats  ships[5]); //makes board and places ships


int scoreSaver(int topScores[10], int games);



void boardSaver(struct board board[10][10], struct boats  ships[5]);


void boardLoader(board board[10][10], struct boats ships[5]);


void progressSaver(int score);



void hitsSaver(int hits);



int hitsLoader(void);




int attemptsLoader(void);



void boardLoader(board board, struct boats ships[5]);



void printMenu(void);



//*************main function**************



int main() {



    printf("Welcome to Battleship!\nThe enemy has five boats. \nFind and sink them all to win!\n");



    int xCoordAtt=0;;



    int yCoordAtt=0;


    //board size


    struct board board[10][10];





    //top 10 scores


    int topScores[10];


    //name the boats








    struct boats  ships[5] = {





            {"Seminole State Ship",1, 3, 'S', 3}, {"Air Force Academy", 2, 5, 'A', 5},





            {"Valencia Destroyer", 3, 4, 'V', 4}, {"Eskimo University", 4, 3, 'E', 3},





            {"Deland High School", 5, 2, 'D', 2}};





    int hits=17;


    //how many attempts the user has


    int attempts=100;


    //game count


    int games=0;








    char menuChoice;


    //while the user hasnt decide to quit or run out of attempts


    while (1)





    {


        printMenu();


        scanf(" %c", &menuChoice);





        switch(menuChoice)


        {


            case 'F':
            case 'f': //fire a missile


            {
                xCoordAtt = 1; // resets the y and x coords so you can repeat the code again
                yCoordAtt = 1;
                while (xCoordAtt >= 0 || yCoordAtt >= 0) {


                //print the board


                printf("\n");


                printf(" 1  2  3  4  5  6  7  8  9  10\n ------------------------------");





                for (int j=0; j<10; j++)


                { //print the columns of current board


                    printf("\n");


                    for (int i=0; i<10; i++){


                        //prints the rows of the current board





                        printf(" %c ", board[j][i].seenChar);


                    }





                } //end of for


                    printf("\nEnter your x coordinate to attack (negative to quit):");

                    scanf("%d", &xCoordAtt);

                    if (xCoordAtt < 0) {
                        printf("\nReturning to main menu..."); // quits the game if they enter a negative number
                        break;
                    }

                    printf("\nEnter your y coordinate to attack (negative to quit):");

                    scanf("%d", &yCoordAtt);

                    if (yCoordAtt < 0) {
                        printf("\nReturning to main menu..."); // quits the game if they enter a negative number
                    }
                    //array starts at 0


                    xCoordAtt--;


                    yCoordAtt--;





                    //****************checks if coordinates work**************





                    if (xCoordAtt < 0 || xCoordAtt >= 10 || yCoordAtt < 0 || yCoordAtt >= 10) {


                        printf("Invalid coordinates. Please enter numbers between 1 and 10.\n");


                        break; // This will skip the rest of the loop and start over again


                    }





                    //************checks if the missile hit a boat**********





                    //******************missed missile***************


                    if (board[xCoordAtt][yCoordAtt].hiddenChar == 'O') {


                        attempts--;


                        //checks to see if user still has missiles to shoot


                        if (attempts == 0) {


                            printf("You have run out of missiles. Please start a new game");


                            break; //returns to main menu


                        } else {


                            printf("Miss! You have %d missile shots left with %d hits still on the board\n", attempts,
                                   hits);


                            board[xCoordAtt][yCoordAtt].seenChar = 'M';




                        }


                    }





                        //*****************hit missile*******************


                    else if (board[xCoordAtt][yCoordAtt].hiddenChar != 'O') {


                        //1 less missile


                        attempts--;





                        //checks to see if user still has missiles to shoot


                        if (attempts == 0) {


                            printf("You have run out of missiles. Please start a new game");


                            break; //returns to main menu


                        } else {


                            //subtract from number of targets that have been hit


                            hits--;


                            printf("Direct hit!! You have %d missile shots left with %d hits still on the board\n",
                                   attempts, hits);





                            //************when user wins**************


                            if (hits == 0) {


                                printf("You win! Your score is %d\n", attempts);


                                topScores[games] = attempts;


                                games++;


                            }


                            //******************changing board after each missile**************************





                            //make the seen board change the character to H


                            board[xCoordAtt][yCoordAtt].seenChar = 'H';





                            //loop to test each boat


                            for (int i = 0; i < 5; i++) {


                                //checking to see if the coordinate on hidden board contains character from boat


                                if (board[xCoordAtt][yCoordAtt].hiddenChar == ships[i].boatchar) {


                                    //if so subtract 1 from health


                                    ships[i].boatHealth--;


                                    //if all the targets on the boat are hit


                                    if (ships[i].boatHealth == 0) {


                                        //**********change the all the H's to the boat characters***************


                                        for (int k = 0; k < 10; k++) //x coordinate


                                        {


                                            for (int p = 0; p < 10; p++) //y coordinate


                                            {


                                                if (board[k][p].seenChar ==
                                                    'H') //change H characters to the boat characters


                                                {


                                                    board[k][p].seenChar = ships[i].boatchar;


                                                } //end of if char = H


                                            } // end of p loop


                                        } // end of k loop


                                    } //end of if boat health = 0


                                } // end of if checking  boat health


                            } // end of loop testing 5 boats


                        } //end of else

                    }
                }  //end of if they enter a negative number
                break;
            } //end of f case











            case 'N':
            case 'n': //new game


            {


                char newchoice;


                printf("\nAre you sure you want to start a new game? Enter Y or N: ");





                scanf(" %c",&newchoice);


                if(newchoice == 'Y' || newchoice == 'y')





                {


                    board[9][9] = boardMaker(board, ships);


                    attempts = 100;


                    hits = 17;


                    printf("A new game has been created. Continue to play.\n");





                    break; //skips the rest of the loop





                }


                else if(newchoice == 'N' || newchoice == 'n')


                {


                    printf("Returning to main menu...\n");


                    break;


                }


                else


                {


                    printf("That is not an option. Returning to main menu...\n");


                    break;


                }


            } //end of n case





            case 'V':
            case 'v':    // save game


            {


                printf("Game has been saved");


                boardSaver(board,ships);


                progressSaver(attempts);


                hitsSaver(hits);



                break;


            } //end of v case











            case 'L':
            case 'l':    //load game


            {
                boardLoader(board, ships);
                hitsLoader();
                attemptsLoader();
                printf("\nSaved board has been loaded\n");
                break;
            }














            case 'S':
            case 's':    //see top 10





            {


                scoreSaver(topScores, games);
                break;

            } //end of s case








            case 'Q':
            case 'q':


                exit(0);








            default:


                printf("That is not an option. Please try again");





        } //end of switch case


    }// end of while loop





    return 0;





}




//********************end of main function***********************



struct board boardMaker(struct board board[10][10], struct boats  ships[5])


{


    int row=0;


    int col=0;


    int dir=0;


    int valid;





    for (int j=0; j<10; j++){//initialize the board to show all O


        for (int i=0; i<10; i++){


            board[j][i].seenChar = 'O';





        }


    }


    for (int j=0; j<10; j++){//initialize the board to have O where boats will be


        for (int i=0; i<10; i++){


            board[j][i].hiddenChar = 'O';


        }


    }


    for (int i=0; i < 5; i++)


    { // For each boat


        valid = 0; // Assume the placement is invalid





        while (!valid) { // Repeat until a valid placement is found


            // Generate a random row, column, and direction


            row = rand() % 10;





            col = rand() % 10;





            dir = rand() % 2; // 0 for horizontal, 1 for vertical


            // Check if the boat fits on the board in the given direction





            //if horizontal and the randomized columns + boatsize are <= 10 it is true/valid





            if (dir == 0 && col + ships[i].boatsize <= 10) {


                valid = 1;


                //if vertical and the randomized row + boatsize are <= 10 it is true/valid


            } else if (dir == 1 && row + ships[i].boatsize <= 10) {


                valid = 1; //true


            }


            // Check if the boat overlaps with any existing boats


            if (valid) {


                for (int j = 0; j < ships[i].boatsize; j++) {





                    if (dir == 0) //if horizontal





                    {





                        //at the randomized coordinate if these spots are not 0 then return as false and start over





                        if (board[row][col + j].hiddenChar != 'O') {





                            valid = 0;


                            break;


                        }


                    }


                    else { //if dir is vertical





                        //at the randomized coordinate if these spots are not 0 then return as false and start over





                        if (board[row + j][col].hiddenChar != 'O')





                        {


                            valid = 0;


                            break;


                        } // end of if


                    } //end of else


                } //end of for boat size loop


            } //end of if checking valid


        } //end of while loop


        // Place the boat on the hidden board





        for (int j = 0; j < ships[i].boatsize; j++) {


            //go through the columns and change the character to the boat's character


            if (dir == 0)


            {


                board[row][col + j].hiddenChar = ships[i].boatchar;


            } // end of if


            else


            {


                //go through the rows and change the character to the boat's character


                board[row + j][col].hiddenChar = ships[i].boatchar;


            } //end of else


        } //end of for


    } // end of loop checking per boat





    return board[9][9];


}



//**************saving*****************



int scoreSaver(int topScores[10], int games)


{


    int i, j, temp;





    for (i = 0; i < games - 1; i++) {


        for (j = 0; j < games - i - 1; j++) {


            if (topScores[j] > topScores[j+1]) {





                temp = topScores[j];





                topScores[j] = topScores[j+1];





                topScores[j+1] = temp;


            }


        }


    }


    printf("Top scores: ");


    for (i = 0; i < games; i++) {


        printf("%d ", topScores[i]);


    }





    return 0;


}



//*************SAVING PROCESS*****************





void boardSaver(struct board board[10][10], struct boats  ships[5])

{


    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\save_Game.txt", "w");


    if (fp == NULL)


    {


        printf("Error opening saved_game file for writing\n");


        return;


    }


    for (int i=0; i<5; i++)


    {


        fprintf(fp, "%s %d %d %c %d\n", ships[i].boatname, ships[i].boatnum, ships[i].boatsize, ships[i].boatchar, ships[i].boatHealth);


    }


    for (int i=0; i<10; i++)


    {


        for (int j=0; j<10; j++)


        {


            fprintf(fp, "%c %c\n", board[i][j].seenChar, board[i][j].hiddenChar);


        }


    }



    FILE* fp1 = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\chars.txt", "w");


    if (fp1 == NULL)


    {


        printf("Error opening chars.txt file for writing\n");


        return;


    }



    for (int i=0; i<10; i++)


    {



        for (int j=0; j<10; j++)



        {

            fprintf(fp1, "%c\n", board[i][j].seenChar);

        }

    }


    fclose(fp);


}



void hitsSaver(int hits) //saves the number of hits until game over


{





    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\saved_hits.txt", "w");





    if (fp == NULL)


    {


        printf("Error opening saved_hits file for writing\n");





        return;


    }


    fprintf(fp, "%d\n", hits);


    fclose(fp);





}


void progressSaver(int score) //saves the score specifically


{





    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\save_score.txt", "w");





    if (fp == NULL)





    {





        printf("Error opening saved_score file for writing\n");


        return;


    }





    fprintf(fp, "%d\n", score);





    fclose(fp);





}




void boardLoader(struct board (*board)[10], struct boats* ships) {
    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\saved_game.txt", "r");

    if (fp == NULL) {
        printf("Could not find save_game.txt\n");
        return;
    }

    // Load ships from file
    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%s %d %d %c %d\n", ships[i].boatname, &ships[i].boatnum, &ships[i].boatsize, &ships[i].boatchar, &ships[i].boatHealth);
    }

    // Load board from file
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            fscanf(fp, "%c %c\n", &board[i][j].seenChar, &board[i][j].hiddenChar);
        }
    }

    fclose(fp);
}



int attemptsLoader(void) //loads previous score


{


    int score = 0;





    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ship\\save_score.txt", "r");





    if (fp == NULL)


    {


        printf("Error opening file saved_score for reading\n");


        return 0;


    }


    fscanf(fp, "%d\n", &score);





    return score;





}


int hitsLoader(void)


{


    int hits = 0;





    FILE* fp = fopen("C:\\Users\\User\\Desktop\\C++ Code\\C++ CODE\\NEW NEW Battle Ships\\saved_hits.txt", "r");





    if (fp == NULL)


    {


        printf("Error opening file saved_hits for reading\n");


        return 0;


    }


    fscanf(fp, "%d\n", &hits);



    return hits;


}

void printMenu(void)


{


    printf("\n\n  ****MAIN MENU****\n");


    printf("[N] Start a new game\n");


    printf("[F] Fire a missile:\n");


    printf("[V] Save game:\n");


    printf("[L] Load saved game:\n");


    printf("[S] See top ten scores\n");


    printf("[Q] Quit the game:\n");


    printf("Select an option from above:");
}