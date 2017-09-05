#pragma once
#include <string>

using int32 = int;
using FString = std::string;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum  class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Uppercase
};

class FBullCowGame {
public:
	FBullCowGame(); //Constructor

	void Reset(); //TODO
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon()const;
	EGuessStatus IsGuessValid(FString) const;

	// Checking how many bulls and cows exist, and increasing try number - if the guess is valid
	FBullCowCount SubmitValidGuess(FString Guess);
	FBullCowCount SubmitValidHidden(FString Hidden);

private:

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;
	bool IsIsogram(FString) const;
	bool IsLower(FString) const;
};