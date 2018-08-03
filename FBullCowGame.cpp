/*
	This is the console executable, that makes use of the BullCow Class
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the fBullCowGame class.

*/
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using int32 = int;



FBullCowGame::FBullCowGame()
{
	Reset();
}
// const on the end of a method means, you can't change anything from this method. 
// A safe way if you won't want anyone to change thing inside the method. 

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const{return bGameIsWon; }
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WorldLengthToMaxTries{ {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 8}, {8, 10}, {9, 10} };
	return WorldLengthToMaxTries[MyHiddenWord.length()];

}

FString FBullCowGame::AskForWordLength() {
	FString u;
	std::cout << "choose your word length between 3 and 9: ";
	std::getline(std::cin, u);
	int32 Userlength = std::stoi(u);
	TMap<int32, FString> uHIDDEN_WORD{ { 3, "pen" },{ 4, "safe" },{ 5, "plane" },{ 6, "planet" },{ 7, "special" },{ 9, "telephone" } };
	const FString HIDDEN_WORD = uHIDDEN_WORD[Userlength]; // TODO make the user enter the WORDLENGTH, which then choose a word from predefined map. 
	MyHiddenWord = HIDDEN_WORD;
	return HIDDEN_WORD;

	
} 



int32 FBullCowGame::GetHiddenWordLength() const
{	
	return MyHiddenWord.length();
}




void FBullCowGame::Reset()
{
	//const FString HIDDEN_WORD = "bounty"; // TODO make the user enter the WORDLENGTH, which then choose a word from predefined map. 
	
	MyCurrentTry = 1;
	bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	
	else if (!IsLowercase(Guess)) { // if the guess isn't all lowercase 
		return EGuessStatus::Not_Lowercase;  //TODO write function
	}

	else if (Guess.length() != GetHiddenWordLength()) // if the WordLength is wrong
	{
		return EGuessStatus::Wrong_Length; // return an error 
	}
	//otherwise
	else { return EGuessStatus::OK; } //return OK
	
		
	
		
	
		

}
// recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assume same length as guess
	// loop through  all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) // MyHiddenWordChar
	{
		// compare letters against the hidden guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) // GuessChar
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])	// Only in the right spot it will count correct. So i messed it up by comparing the same numbers. 
			{
				//  if they're in the same place
				
				if (MHWChar == GChar) 
				{
					BullCowCount.Bulls++; // increment bulls
				}
				
				// if they're not in the same place
				else 
				{
					BullCowCount.Cows++; // increment cows
				}
						
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) { bGameIsWon = true; }
	else { bGameIsWon = false; }

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{

	
	
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	// loop through all the letters of the word
	for (auto Letter : Word) 
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we do Not have an isogram
		} else { LetterSeen[Letter] = true; } // add the letter to the map as seen
	}
	return true; // in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		
		if (islower(Letter))
		{
			return true;
		}
		else { return false; }

		
	}

	return false;
}



//bool FBullCowGame::CheckGuessValidity()
//{
//    return false;
//}