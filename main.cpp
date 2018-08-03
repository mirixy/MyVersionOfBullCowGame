// The Questions for Game Devs
//*Requierements: Console Games. Text-Based Game. 
// What will the outputs be ? Plain Text
// What will the inputs be ? Plain Text
// What task will the user be asked to do? User has to guess a word with no repeating letters.
// Any Performance limits worth mentioning ? No there is no need for much performance.
// What assets (art, sound, story text) do we need? A quick ASCII for the main part. No Sound. And just a few words self explaining.

// The NO List
// Give feedback on every keypress
// Have a large dictionarz of hidden words.
// User selectable word lenght, and difficulty
// Checking the user's guess is a dictionary isogram.
// Providing a time limit for the guesses.
// A hint system, spend a turn for a hint.

//using namespace std; might be a bad thing to do.
//so do it with the namespaces and colons.

#include "FBullCowGame.h"
#include <iostream>
using int32 = int;
using FText = std::string;

FBullCowGame BCGame;

int main ()
{
    // Print the Intro
    bool bPlayAgain = false;
	//SelectWorld();
    do 
    {
		BCGame.AskForWordLength();
        PrintIntro();
        PlayGame();
		PrintGameSummary();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    return 0;
}
// Ask To Play Again
bool AskToPlayAgain()
{
    std::cout << std::endl << "Do you want to play again with the same hidden word (y/n) ?  ";
    FText Response = "";
    getline (std::cin, Response);
    std::cout << std::endl;
    return (Response[0] == 'y' || Response[0] == 'Y');
    

}


void PlayGame()
{ 
		BCGame.Reset();
        int32 MaxTries = BCGame.GetMaxTries();
		// loop for guesses while the game is NOT won
		// and there are still tries remaining
        while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
        {
			FText Guess = GetValidGuess(); 
			// submit valid guess to the game
			FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			// print number of bulls and cows.
			std::cout << "Bulls = " << BullCowCount.Bulls;
			std::cout << " | Cows = " << BullCowCount.Cows << "\n";
        }
		
		
		return;
} 

// Function of Print Intro
void PrintIntro()
{
    std::cout << "\n \n" << "Welcome to Bull and Cows, a fun word game " << std::endl;
	std::cout << " |      *        *                            |" << std::endl;
	std::cout << " |     ((_______))                _+_____+_   |" << std::endl;
	std::cout << " |      ) *   * (                ) *    * (   |" << std::endl;
	std::cout << " |     (   ++    )     and      (    ++    )  |" << std::endl;
	std::cout << " |      *       *                *        *   |" << std::endl;
	std::cout << " |       *******                  ********    |" << std::endl;
	std::cout << " |________Bulls_____________________Cows______| " << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() <<  " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
	
	return;
    
}
// loop continually until the Guess is VALID
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << std::endl << "Try: " << CurrentTry << " of " << BCGame.GetMaxTries() << " Enter your guess:  ";
		getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
			case EGuessStatus::Invalid_Status:
				std::cout << "Invalid Status";
				break;
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters. \n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all in lowercase letter. \n";
				break;
			default: 
				// assume the guess is valid
				break;

		}
		
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors.
	return Guess;
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon()) {
		std::cout << std::endl <<"WELL DONE - YOU WIN \n";
	}
	else {
		std::cout << std::endl << "Better Luck next Time \n";
	}

}
/*int32 SelectWorld() {
	int32 u;
	std::cout << "choose your word length between 3 and 9: ";
	std::cin >> u;
	return u;
}

*/
