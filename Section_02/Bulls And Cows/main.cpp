#include <iostream>
#include <string>
#include "FBullCOwGame.h"

using Ftext = std::string;
using int32 = int;
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
Ftext GetValidHidden();
void GameSummary();
bool AskToPlayAgain();

FBullCowGame BCGame; //Create instance of new game


//Entry point for application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro(); // Display information on the game
		PlayGame();  // Game logic and functionality
		GameSummary(); // Win/Lose
		bPlayAgain = AskToPlayAgain(); // Self-Explanatory
	} while (bPlayAgain);

	
	return 0;
}

// Introduce the game
void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows\n"; // TODO Display ASCII Figures
	std::cout << std::endl;
	return;
}

void PlayGame()
{

	BCGame.Reset();	
	Ftext Hidden = GetValidHidden();
	FBullCowCount HiddenWord = BCGame.SubmitValidHidden(Hidden);
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << "\nCan you guess the " << BCGame.GetHiddenWordLength() << " word isogram I'm thinking of ? \n";
	// Loop for 5 turns
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {

		Ftext Guess = GetValidGuess();
		//submit valid guess
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// display bulls and cows
		std::cout << "Your guess was: " << Guess << std::endl;
		std::cout << "Bulls: " << BullCowCount.Bulls << " -";
		std::cout << " Cows: " << BullCowCount.Cows << std::endl;
		//TODO Check if game is won
		
		std::cout << std::endl;
	}
}

Ftext GetValidHidden() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Hidden = "";
	do {
		Hidden = "";
		std::cout <<  "Please choose a Hidden word for the second player to guess: " << Hidden;
		std::getline(std::cin, Hidden);
		std::cout << "\x1B[2J\x1B[H";
		//Check status and give feedback
		Status = BCGame.IsGuessValid(Hidden);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please input a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Uppercase:
			std::cout << "Please input in lowercase." << std::endl;
			break;
		default:
			return Hidden;
		}
	} while (Status != EGuessStatus::OK); //Keep looping until valid
	return Hidden;

}

// Get a guess from the player
Ftext GetValidGuess() {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	Ftext Guess = "";
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		Guess = "";
		std::cout << "Try " << CurrentTry << "/" << BCGame.GetMaxTries() << " Guess word: " << Guess;

		std::getline(std::cin, Guess);
        //Check status and give feedback
		Status = BCGame.IsGuessValid(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please input a word without repeating letters." << std::endl;

			break;
		case EGuessStatus::Uppercase:
			std::cout << "Please input in lowercase." << std::endl;

			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please input a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;

			break;
		default:
			return Guess;
		}
	} while (Status != EGuessStatus::OK); //Keep looping until valid
	return Guess;
}

void GameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations, you won!\n";
	}
	else { std::cout << "Better luck next time!\n"; }
	return;
}
bool AskToPlayAgain() {
	std::cout << "Do you wish to play again?\n";
	std::string Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
