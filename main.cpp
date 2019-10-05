//  main.cpp
//  INFO450FINDGOLD
//  Created by Abbie Thorne on 10/2/19.
//  Copyright © 2019 Abbie Thorne. All rights reserved.

#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;

//create a game where the user is trying to find gold on a game board, with the option to get gold or coal. The user get's five guesses on an 8x8 board.

const int ROWS = 8; //8 rows
const int COLUMNS = 8; //8 columns
int guessesLeft = 5; //user guesses five times
int gameRules;


int main()
{
    
    int initializeArray(char guessArray[ROWS][COLUMNS]);
    int displayArray(char guessArray[ROWS][COLUMNS]);
    int populateArray(char guessArray[ROWS][COLUMNS]);
    int gameLogic(char guessArray[ROWS][COLUMNS]);


    char guessArray[ROWS][COLUMNS]; //asking user to guess again
    char answer;


    do
    {
        initializeArray(guessArray);
        displayArray(guessArray);
        populateArray(guessArray);
        
        gameLogic(guessArray);

        cout << "Would you like to play Again? Enter 'Y' or 'y'" << endl;
        cin >> answer;

        if (answer == 'y' || answer == 'Y')
        {
            guessesLeft = 5; //always tell user how many guesses they have left
        }

        
    } while (answer == 'Y' || answer == 'y');

    return 0;

}


int initializeArray(char guessArray[ROWS][COLUMNS])
{
    int row, column;

    guessesLeft = 5;

    
    for (row = 0; row < ROWS; row++)
    {
        for (column = 0; column < COLUMNS; column++)
        {
            guessArray[row][column] = '!';
        }
    }
    return 0;
}


int displayArray(char guessArray[ROWS][COLUMNS])

{
    int row, column;
    cout << endl;
    cout << "   ";
    for (column = 0; column < COLUMNS; column++)
    {
        cout << setw(3) << column + 1;
    }
    cout << endl;
    cout << "  " << "--------------------------" << endl;

    for (row = 0; row < ROWS; row++)
    {
        cout << " " << row + 1 << "|";
        for (column = 0; column < COLUMNS; column++)
        {
            cout << setw(3) << guessArray[row][column];
        }
        cout << endl;
    }

    cout << "  " << "--------------------------" << endl;

    return 0;

}
//display game rules.

int coutGameRules()
{
    cout << "**" << " ********************* " << "**" << endl;
    cout << "**" << "      Find Gold!       " << "**" << endl;
    cout << "**" << "  You have 5 guesses!  " << "**" << endl;
    cout << "**" << "  Earn an extra guess  " << "**" << endl;
    cout << "**" << "  when you find gold!  " << "**" << endl;
    cout << "**" << "     There are...      " << "**" << endl;
    cout << "**" << "   5 pieces of gold,   " << "**" << endl;
    cout << "**" << "     and 1 bomb.       " << "**" << endl;
    cout << "**" << "      Good Luck!       " << "**" << endl;
    cout << "**" << "                       " << "**" << endl;
    cout << "**" << " ********************* " << "**" << endl;
    cout << endl;
    cout << endl;

    return 0;
}
//Gold Array

int populateArray(char guessArray[ROWS][COLUMNS])

{

    int bombInputCounter = 0;
    int x, y;
    int goldInputCounter = 0;
    srand(time_t(NULL));

    do {
        x = rand() % ROWS;
        y = rand() % COLUMNS;

        if (guessArray[x][y] != 'G')
        {
            // puts G for gold
            guessArray[x][y] = 'G';
            goldInputCounter++;
        }
       

    } while (goldInputCounter < 5);

  
    do
    {
        x = rand() % ROWS;
        y = rand() % COLUMNS;

        if (guessArray[x][y] != 'G') // if the get a "G", go back to the loop, and let them guess again
        {
            guessArray[x][y] = 'B'; // Put 'B' for Bomb at the random coordinate
            bombInputCounter++;
        }


    } while (bombInputCounter < 1);



    return 0;

}

int gameLogic(char guessArray[ROWS][COLUMNS])
{
    int points = 0;
    int gRow, gColumn;

    do
    {
        // ask user for input of gold location
        cout << "Enter an X coordinate between 1 and 8: ";
        cin >> gRow;

        //While the input entered is not an integer, ask for integer
        while (!cin || gRow > 8 || gRow < 1)
        {
            cout << "Please enter an integer that is between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> gRow;
        }

        gRow--;
        cout << endl;
        cout << "Enter a Y coordinate between 1 and 8: ";
        cin >> gColumn;

        
        while (!cin || gColumn > 8 || gColumn < 1)
        {
            cout << "Please enter an integer that is between 1 and 8: ";
            cin.clear();
            cin.ignore();
            cin >> gColumn;
        }

        gColumn--;
        cout << endl;

      //guesses
        
        if (guessArray[gRow][gColumn] == 'G')
        {
            cout << " Y A Y ! You Found Gold!! " << guessesLeft << " guesses left!";
            guessArray[gRow][gColumn] = 'F';
            
            points += 1;
            cout << endl;
            cout << endl;
            continue;
            
        }
        // If they find bomb, break out of loop and start over.
        else if (guessArray[gRow][gColumn] == 'B')
        {
            cout << endl;
            cout << "LOSER! YOU FOUND A BOMB." << endl << endl;
            break; // Game ends
        }
       
        else
        {
            cout << "Oh no,  no gold." << endl;
            guessesLeft--;
            cout << "You have " << guessesLeft << " guesses left!" << endl << endl;

        }


    } while (guessesLeft > 0); // Do this loop until no guesses left

    cout << "You've earned " << points << " points!" << endl;
    cout << "Better luck next time!" << endl;
    cout << "Here's your board:" << endl << endl;

    
    for (gColumn = 0; gColumn < COLUMNS; gColumn++)
    {
        for (gRow = 0; gRow < ROWS; gRow++)
        {
            if (guessArray[gRow][gColumn] == '?')
            {
                guessArray[gRow][gColumn] = ' ';
            }
        }
    }

   
    cout << "   ";
    for (gColumn = 0; gColumn < COLUMNS; gColumn++)
    {
        cout << setw(3) << gColumn + 1; // Array starts at 0, add a 1
    }
    cout << endl;
    cout << "  " << "--------------------------" << endl;

    for (gRow = 0; gRow < ROWS; gRow++)
    {
        cout << " " << gRow + 1 << "|";
        for (gColumn = 0; gColumn < COLUMNS; gColumn++)
        {
            cout << setw(3) << guessArray[gRow][gColumn];
        }
        cout << endl;
    }

    cout << "  " << "--------------------------" << endl;


    return 0;}
//game ends
