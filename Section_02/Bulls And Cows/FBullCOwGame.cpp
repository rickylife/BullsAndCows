#include "FBullCOwGame.h"
#include <map>
#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //Define Constructor

void FBullCowGame::Reset() {

   // FString Hidden = "";
//	MyHiddenWord = Hidden;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,7}, {4, 9}, {5, 11}, {6, 15}, {7, 18} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameWon;

}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//Loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); //Assuming same length as guess
	for (int32 i = 0; i < WordLength; i++) {
		//Compare them to the letters in the guess
		for (int32 j = 0; j < WordLength; j++) {
			if (Guess[i] == MyHiddenWord[i] && i == j) {
				BullCowCount.Bulls++; //Increase number of bulls if they're in the same place

			}
			else if (Guess[i] == MyHiddenWord[j] && i != j) {
				BullCowCount.Cows++; //Or cows if they're not
			}
		}
	}
	if ((BullCowCount.Bulls == FBullCowGame::GetHiddenWordLength())) {
		bGameWon = true;
	}
	else { bGameWon = false; }
	//Recieves a valid guess, increments turn, and return count
	return BullCowCount;
}

FBullCowCount FBullCowGame::SubmitValidHidden(FString Hidden)
{
	FBullCowCount HiddenWord;
	MyHiddenWord = Hidden;
	return HiddenWord;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) { //for all letters of the word
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	//Check for duplicates
	//Return false if duplicate
	}
	return true;
}

bool FBullCowGame::IsLower(FString Word) const
{
	if (Word.length() == 0) { return true; }

	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		} 
	}

	return true;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLower(Guess)) {
		return EGuessStatus::Uppercase;
	}
	else if (Guess.length() != GetHiddenWordLength() ) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}

}
