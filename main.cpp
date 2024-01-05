#include <iostream>
#include <conio.h>
using namespace std;

// Declaring global Variables
bool Editing = true;                           // declaring boolean variable to exit from the loop

// Defining a LevelEditor Class learned in Gap 120 by graham pezzuti
// I got an clicked in my mind that we can use class to avoid global variables and use variables in different functions by declaring them out of the function
class LevelEditor
{
    // declaring variables
    char** grid = nullptr;                     // declaring Pointer to a 2D array representing the grid. Initialized to nullptr.
    int width = 0;                             // width  of the grid
    int height = 0;                            // height of the grid
    char Char = 0;                             // for character
    int CharX = 16;                             // for character's X position
    int CharY = 16;                             // for character's Y position
    char wall = 0;                             // for wall
    int wallX = 16;                            // for wall's x position
    int wallY = 16;                            // for wall's Y position
    int WallCount = 0;                         // int variable for wall count
    char rewards = 0;                          // char variable for rewards
    int rewardsX = 16;                         // for rewards's X position
    int rewardsY = 16;                         // for rewards's Y position
    int RewardsCount = 0;                      // int variable for Rewards count
    char exit = 0;                             // char variable for exit with value
    int exitX = 16;                            // for exit's X position
    int exitY = 16;                            // for exit's Y position
    int ExitCount = 0;                         // int variable for exit count
    int score = 0;
    bool IsExited = false;
    bool IsRewards = false;
// making functions public so everyone can use it out of the class
public:

    void DeallocatingMemory()
    {
        // Deallocating memory for the array before exiting
        for (int i = 0; i < height; i++)
        {
            delete[] grid[i];                    // deleting/deallocating the data/memory in grid/array
        }
        delete[] grid;
    }
    // defining function to print the grid
    void printGrid()
    {
        // using nested loops to print the grid (2d array form)
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (i == CharX && j == CharY)
                {
                    cout << Char << " ";            // printing character and to leave some space between each grid character
                }
                else  if (i == exitX && j == exitY)
                {
                    cout << exit << " ";
                    if (IsExited)
                    {
                        cout << Char << " ";         // printing character and to leave some space between each grid character
                    }
                }
                else
                {
                    if (CharX == rewardsX && CharY == rewardsY)  // Condition to check if player is on rewards
                    {
                        if (IsRewards)
                        {
                            grid[CharX][CharY] = '.';       // If yes then print '.' there
                            IsRewards = true;
                        }
                    }
                    bool IsWall = false;
                    for (int k = 0; k < WallCount; k++)
                    {
                        if (i == wallX && j == wallY)
                        {
                            cout << wall << " ";
                            IsWall = true;
                            break;
                        }
                    }
                   
                    for (int g = 0; g < RewardsCount; g++)
                    {
                        if (i == rewardsX && j == rewardsY && IsRewards)
                        {
                            cout << rewards << " ";
                            IsRewards = true;
                            break;
                        }
                    }
                   if (!IsWall && !IsRewards)
                   {
                       cout << grid[i][j] << " ";      // to print the grid
                   }
                   
                }
            }
            cout << "\n";                           // to break the line after every row
        }
    }
    // There are two stages in the program :
    // Setup mode
    // Editing mode
    // To include cursor-based interface instead of cin based for character reposition I mergen things of editing mode to setup mode.
    void SetupMode()
    {
        // Ask the user for the desired width and height of their grid
        cout << "Enter the width of the grid (must be between 5-15): ";
        cin >> width;

        cout << "Enter the height of the grid (must be between 5-15): ";
        cin >> height;

        // Allocatting memory for the grid
        grid = new char* [height];

        // Updating the grid as per height and width
        for (int i = 0; i < height; i++)
        {
            grid[i] = new char[width];
            for (int j = 0; j < width; j++)
            {
                grid[i][j] = '.';
            }
        }

        // Display the current state of the grid to the user.
        printGrid();
        // Allow the user to enter the desired X coordinate.
        cout << "Enter X coordinate: ";
        cin >> CharX;

        // Allow the user to enter the desired Y coordinate.
        cout << "Enter Y coordinate: ";
        cin >> CharY;
        // Calling Character function to get a character input from user.
        Character();
        system("cls");                     // to clear the screen
    }

    void Character()
    {
        // Once a location is chosen, allow the user to enter any character of their choice.
        cout << "Enter character of your choice: ";
        cin >> Char;
    }

    void Wall()
    {
        if (WallCount <= ((width * height) - width))
        {
           cout << "Enter X coordinate: ";  // Allow the user to enter the desired X coordinate.
           cin >> wallX;                    // taking user's input
           cout << "Enter Y coordinate: ";  // Allow the user to enter the desired Y coordinate.
           cin >> wallY;                    // taking user's input
           
           grid[wallX][wallY] = wall;       // updating grid with walls
           WallCount++;                     // increasing wall count by +1
        }
    }

    void Rewards()
    {
        cout << "Enter X coordinate: ";     // Allow the user to enter the desired X coordinate.
        cin >> rewardsX;                    // taking user's input
        cout << "Enter Y coordinate: ";     // Allow the user to enter the desired Y coordinate.
        cin >> rewardsY;                    // taking user's input
        grid[rewardsX][rewardsY] = rewards; // updating grid with walls
        RewardsCount++;                     // increasing rewards count by +1
        IsRewards = true;
    }

    void MazeExit()
    {
        cout << "Enter X coordinate: ";     // Allow the user to enter the desired X coordinate.
        cin >> exitX;                       // taking user's input
        cout << "Enter Y coordinate: ";     // Allow the user to enter the desired Y coordinate.
        cin >> exitY;                       // taking user's input
        ExitCount++;                        // increasing exit count by +1
    }

    void PlayTheGame()
    {
      do
        { 
            system("cls");
            cout << "Use W, A, S, D on your keyboard to Play\n";
            cout << "Press 'p' to go back to Editing Mode\n";
            cout << "Current position: (" << CharX << ", " << CharY << ")\n";
            if (grid[CharX][CharY] == rewards)                                             // Condition if player is on rewards
            {                                                                              
                score += 5;                                                                // then update the score add 5 to it
            }
           cout << "your Score is " << score << "\n";                                      // Printing the score
            printGrid();
            char choice1 = _getch();
          switch (choice1)
          {
           case 'w':                                // case 'w' if w key is pressed move character up
               W();
               break;                               // to break the switch statement after the case is true/ if the case is true
           case 'a':                                // case 'a' if a key is pressed move character left
               A();
               break;                               // to break the switch statement after the case is true/ if the case is true
           
           case 's':                                // case 's' if s key is pressed move character down
               S();
               break;                               // to break the switch statement after the case is true/ if the case is true
           
           case 'd':                                // case 'd' if d key is pressed move character right
               D();
               break;                               // to break the switch statement after the case is true/ if the case is true
           case 'p':
               return;                              // to go back to Editing mode

           default:
               cout << "Use W, A, S, D on your keyboard to move\n";
               break;
          }
          if (CharX == exitX && CharY == exitY)
          {
              IsExited = true;
              break;
          }
        } while (true);
        system("cls");
        printGrid();
        IsExited = false;
        cout << "your Score is " << score << "\n";                                      // Printing the score
        cout << "You Win The Game Congratulations!\n";
        system("pause");
    }
    // At any time during the editing loop, you must also present the user with the option to return to setup mode and start over.
    void Exit()
    {
        system("cls");                   // to clear the screen

        DeallocatingMemory();            // calling function DeallocatingMemory() to deallocate memory

        grid = nullptr;                  // Setting the pointer to nullptr after deallocation
        SetupMode();                     // calling SetupMode() function
    }

    void W()
    {
        if (CharX > 0 &&
            grid[CharY][CharX - 1] != wall)   // using if statement to check above x cordinate is greater than zero
        {
            CharX--;                          // then decrease X coordinate
        }
    }
    
    void A()
    {
        if (CharY > 0 &&
            grid[CharY - 1][CharX] != wall)  // using if statement to check left y cordinate is greater than zero
        {
            CharY--;                         // then decrease Y coordinate
        }
    }

    void S()
    {
        if (CharX < height - 1 &&
            grid[CharY][CharX + 1] != wall)  // using if statement to check below x cordinate is less than height - 1
        {
            CharX++;                         // then increase X coordinate
        }
    }

    void D()
    {
        if (CharY < width - 1 &&
            grid[CharY + 1][CharX] != wall)  // using if statement to check right y cordinate is less than width - 1
        {
            CharY++;                         // then increase Y coordinate
        }
    }

    void EditingMode()
    {
        // printing some stuff for operating editing mode
        cout << "1) You are now in Editing Mode, press '1' on keyboard to exit anytime\n";
        cout << "\n";
        cout << "2) You can move the character using 'W' 'A' 'S' and 'D' on the keyboard\n";
        cout << "\n";
        cout << "3) To change the Character press '3' on the keyboard\n";
        cout << "\n";
        cout << "4) Press 'q' to exit the program completely\n";
        cout << "\n";
        cout << "5) Press '5' to make a exit for the maze/grid\n";
       
        cout << "\n";
        cout << "6) Press '6' to include rewards in your game\n";
        cout << "\n";
        cout << "7) If you done with your character placing press '7' to place walls in the map/grid\n";
        cout << "\n";
        cout << "8) If Editing is over press 'p' to play the game\n";
        cout << "\n";
        // declaring an integer variable for switch statement to get user's input directly form keyboard without pressing enter key
        char choice = _getch();
      

        // using switch statement for locating character 
        switch (choice)
        {
         case 'w':                                // case 'w' if w key is pressed move character up
             W();
             break;                               // to break the switch statement after the case is true/ if the case is true
         case 'a':                                // case 'a' if a key is pressed move character left
             A();
             break;                               // to break the switch statement after the case is true/ if the case is true

         case 's':                                // case 's' if s key is pressed move character down
             S();
             break;                               // to break the switch statement after the case is true/ if the case is true

         case 'd':                                // case 'd' if d key is pressed move character right
             D();
             break;                               // to break the switch statement after the case is true/ if the case is true

         case '1':                                // case '1' if 1 key is pressed 
             Exit();                              // call's Exit() function to exit the editing mode and get back to setup mode
             break;                               // to break the switch statement after the case is true/ if the case is true

         case '3':                                // case '2' if 2 key is pressed 
             Character();                         // call's Character() function to choose a new character
             break;                               // to break the switch statement after the case is true/ if the case is true

         case 'q':
             Editing = false;                     // if q is pressed then value of bool Editing will change to flase and this will exit the loop
             break;                               // to break the switch statement after the case is true/ if the case is true  (its an optional to use break here as its last case and if its true the program will exit but its good practice to write it)
         case '7':
             if (WallCount >= ((width * height) - width))
             {
                 cout << "You reached to limit of creating walls\n";
                 system("pause");
                 break;
             }
             char input;
             cout << "Enter the character which will be your wall in the map/grid\n";
             cin >> wall;
             
             while (true)
             {
                 Wall();
                 system("cls");
                 printGrid();
                 
                 if (WallCount < ((width * height) - width))
                 {
                     cout << "Do you want to include more walls?(y/n)\n";
                     cin >> input;
                     if (input == 'y')
                     {
                         continue;
                     }
                     if (input == 'n')
                     {
                         break;
                     }
                 }
                 if (WallCount >= ((width * height) - width))
                 {
                     break;
                 }
             }
             break;
         case'6':
             if (RewardsCount >= 3)
             {
                 cout << "You reached to limit of including Rewards\n";
                 system("pause");
                 break;
             }
             cout << "Enter the character which will be your Rewards in the map/grid\n";
             cin >> rewards;
             char input2;
             while (true)
             {
                 Rewards();
                 system("cls");
                 printGrid();
                 
                 if (RewardsCount < 3)
                 {
                     cout << "Do you want to include more Rewards?(y/n)\n";
                     cin >> input2;
                     if (input2 == 'y')
                     {
                         continue;
                     }
                     if (input2 == 'n')
                     {
                         break;
                     }
                 }
                 if (RewardsCount > 2)
                 {
                     break;
                 }
             }
             break;
         case'5':
             if (ExitCount == 1)
             {
                 char input3;
                 cout << "You cant include more than 1 Exit\n";
                 cout << "Do you Want to change position of Exit?(y/n)\n";
                 cin >> input3;
                 if (input3 == 'y')
                 {
                     MazeExit();
                 }
                 if (input3 == 'n')
                 {
                     break;
                 }
                 break;
             }
             cout << "Enter the character which will be your Exit for the map/grid\n";
             cin >> exit;
             MazeExit();
             break;
         case'p':
            
             PlayTheGame();
             
             break;
        }
        system("cls");                            // to clear the screen
    }

};
    int main()
    {
        LevelEditor Level;                        // Creating a LevelEditor object named 'Level'
        Level.SetupMode();                        // To enter the setup mode of the LevelEditor 

        // creating an infinite loop
        while (Editing)
        {
          Level.printGrid();                      // Display the current state of the grid.
          Level.EditingMode();                    // To enter editing mode to allow the user to edit the grid in the editing mode.
        }
        Level.DeallocatingMemory();               // calling function to deallocate memory

        return 0;                                 // exits the code with zero errors
    }
