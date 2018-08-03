#pragma once
#include <string>
#include <iostream>


using int32 = int;
using FString = std::string;

// initialize values to zero
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

void PrintIntro();
FString GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();
//int32 SelectWorld();



class FBullCowGame
{
public:
	FBullCowGame(); // constructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString AskForWordLength();

    bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); 
    
	// provide a method for counting bulls & cows, and increasing try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);
	





//Please Try and ignoere this and focus on the interface above ;)
private:
	// see constructor
    int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
    

};