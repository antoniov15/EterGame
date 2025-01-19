﻿#include "Game.h"
#include "GameState.h"
#include <iostream>
#include <stdlib.h> 
#include <Windows.h>
#include <regex>
#include <map>
#include <functional>
//#include <nlohmann/json.hpp>

void clearConsole();

// Mod antrenament
void trainingMode();
// Duel vrajitori
void wizardsDuel();
//Duel elemente

void elementsDuel();
// Modul turneu

bool checkPass(const std::string& parola) {
    std::regex pattern(R"([E|e]ter123)");
    return std::regex_match(parola, pattern);
}

int main() {
    std::string password;

    do {
        std::cout << "Write password: ";
        std::cin >> password;
        std::cout << "Wrong password!\n";
    } while (!checkPass(password));

    srand(static_cast<unsigned>(time(0)));

    // Încărcare progres joc (dacă există)
    std::string choice;
    GameState gameState;

    std::cout << "🔹 Vrei să încarci progresul anterior? (da/nu): ";
    std::cin >> choice;

    if (choice == "da") {
        gameState = loadGame(); // Încarcă progresul din `savegame.json`
    }
    else {
        std::cout << "🆕 Începem un joc nou!\n";
        gameState = {}; // Inițializează un nou joc
    }

    unsigned short int choiceMenu = 0;

    std::map<int, std::function<void()>> actions = {
        {1, trainingMode},
        {2, wizardsDuel},
        {3, elementsDuel},
        {4, []() { std::cout << "Modul Turneu (Momentan nu este disponibil).\n"; }},
        {5, []() { std::cout << "Modul Viteză (Momentan nu este disponibil).\n"; }},
        {6, []() { std::cout << "Leaving Game.\n\n"; }}
    };

    do {
        clearConsole();
        std::cout << "/------------------------------------\\\n";
        std::cout << "| What gamemode do you want to play? |\n";
        std::cout << "| 1. Training Mode                   |\n";
        std::cout << "| 2. Wizard's Duel                   |\n";
        std::cout << "| 3. Element's Duel                  |\n";
        std::cout << "| 4. Tournament                      |\n";
        std::cout << "| 5. Speed Mode                      |\n";
        std::cout << "| 6. Exit Game                       |\n";
        std::cout << "\\------------------------------------/\n\n";

        std::cout << "Choice: ";
        if (!(std::cin >> choiceMenu)) {
            // Dacă intrarea nu este numerică
            std::cin.clear();                // Curățăm starea de eroare
            std::cin.ignore(1000, '\n');     // Golim bufferul până la finalul liniei
            std::cout << "\nInvalid input. Please enter a number between 1 and 6.\n\n";
            continue;                        // Reia bucla
        }

        std::cout << '\n';

        // Verificăm dacă `choice` este o cheie validă în mapă
        if (actions.find(choiceMenu) != actions.end()) {
            actions[choiceMenu](); // Execută funcția mapată la `choice`
        }
        else {
            std::cout << "Invalid choice. Please try again.\n\n";
        }

        /*switch (choice) {
        case 1:
            trainingMode();
            break;
        case 2:
            wizardsDuel();
            break;
        case 3:
            //elementsDuel();
            break;
        case 4:
            //tournamentMode();
            break;
        case 5:
            //speedMode();
            break;
        case 6:
            std::cout << "Leaving Game.\n\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n\n";
            break;
        }*/
    } while (choiceMenu != 6);

    return 0;
}

void clearConsole() {
    system("CLS");
    /*
    // Adaugare debug

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Invalid handle\n";
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        std::cerr << "Error: Unable to get console screen buffer info\n";
        return;
    }

    DWORD consoleSize;
    DWORD charsWritten;

    if (!FillConsoleOutputCharacter(hConsole, ' ', consoleSize, { 0, 0 }, &charsWritten)) {
        std::cerr << "Error: Unable to fill console output character\n";
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, { 0, 0 }, &charsWritten)) {
        std::cerr << "Error: Unable to fill console output attribute\n";
        return;
    }

    if (!SetConsoleCursorPosition(hConsole, { 0, 0 })) {
        std::cerr << "Error: Unable to set console cursor position\n";
        return;
    }

    // Obține dimensiunea bufferului consolei
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Umple bufferul cu spații
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, { 0, 0 }, &charsWritten);

    // Resetează atributele consolei
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, { 0, 0 }, &charsWritten);

    // Mutați cursorul la început
    SetConsoleCursorPosition(hConsole, { 0, 0 });*/
}

// Mod antrenament
void trainingMode() {
    //clearConsole();
    std::cout << "Starting Training Mode...\n";

    /// Crearea vrăjitorilor "default" pentru acest mod
    /// Wizard wizard1("Training Wizard 1", MagicPower::GAIN_EXTRA_CARD);
    /// Wizard wizard2("Training Wizard 2", MagicPower::MOVE_ROW_TO_EDGE);

    // Crearea jocului cu tabla 3x3
    Game game(3,
        "Player 1",
        "Player 2",
        Wizard("", MagicPower::GAIN_EXTRA_CARD),
        Wizard("", MagicPower::MOVE_ROW_TO_EDGE),
        GameMode::Training);

    // Configurarea cărților pentru fiecare jucător conform regulilor
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(1));
        game.getPlayer2().addCard(Card(1));
    }
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(2));
        game.getPlayer2().addCard(Card(2));
    }
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));

    // Formatul 2/3
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < 2 && player2Wins < 2) {
        /// Se afiseaza scorul curent
        std::cout << "\nCurrent score: "
            << game.getPlayer1().getName() << " " << player1Wins
            << " - " << player2Wins << " " << game.getPlayer2().getName() << '\n';

        //clearConsole();
        std::cout << "\nPLAYER 1's turn\n";
        game.getBoard().printBoard();
        std::string choice;

        // Alegerea între iluzie și carte normală
        std::cout << "Do you want to place an illusion? (yes/no): ";
        std::cin >> choice;

        while (choice != "yes" && choice != "no") {
            std::cout << "Invalid input! Please answer 'yes' or 'no': ";
            std::cin >> choice;
        }

        bool moveSuccessful = false;
        if (choice == "yes" && !game.getPlayer1().hasPlacedIllusion) {
            moveSuccessful = game.placeIllusion(game.getPlayer1(), game.getBoard());
            if (moveSuccessful) {
                game.getPlayer1().hasPlacedIllusion = true;
            }
        }
        else {
            moveSuccessful = game.placeNormalCard(game.getPlayer1(), game.getBoard(), game.getPlayer2());
        }

        if (!moveSuccessful) {
            std::cout << "Invalid move. Player 1 loses their turn.\n";
        }

        // Verificare condiții câștig pentru Player 1
        std::string winConditionP1 = game.getBoard().checkWinCondition(game.getPlayer1());
        if (!winConditionP1.empty()) {
            player1Wins++;
            std::cout << game.getPlayer1().getName() << " wins this round with " << winConditionP1 << "!\n";
            game.resetGame();
            continue;
        }

        //clearConsole();
        std::cout << "\nPLAYER 2's turn\n";
        game.getBoard().printBoard();

        std::cout << "Do you want to place an illusion? (yes/no): ";
        std::cin >> choice;


        while (choice != "yes" && choice != "no") {
            std::cout << "Invalid input! Please answer 'yes' or 'no': ";
            std::cin >> choice;
        }

        moveSuccessful = false;
        if (choice == "yes" && !game.getPlayer2().hasPlacedIllusion) {
            moveSuccessful = game.placeIllusion(game.getPlayer2(), game.getBoard());
            if (moveSuccessful) {
                game.getPlayer2().hasPlacedIllusion = true;
            }
        }
        else {
            moveSuccessful = game.placeNormalCard(game.getPlayer2(), game.getBoard(), game.getPlayer1());
        }

        if (!moveSuccessful) {
            std::cout << "Invalid move. Player 2 loses their turn.\n";
        }

        // Verificare condiții câștig pentru Player 2
        std::string winConditionP2 = game.getBoard().checkWinCondition(game.getPlayer2());
        if (!winConditionP2.empty()) {
            player2Wins++;
            std::cout << game.getPlayer2().getName() << " wins this round with " << winConditionP2 << "!\n";
            game.resetGame();
            continue;
        }
    }

    // Determinarea câștigătorului general
    std::cout << "\nFinal score: "
        << game.getPlayer1().getName() << " " << player1Wins
        << " - " << player2Wins << " " << game.getPlayer2().getName() << "\n";

    if (player1Wins == 2) {
        std::cout << game.getPlayer1().getName() << " wins the training mode!\n";
    }
    else {
        std::cout << game.getPlayer2().getName() << " wins the training mode!\n";
    }

    /// Așteaptă confirmarea utilizatorului înainte de revenirea la meniu
    std::cout << "Press Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
}

const std::vector<Wizard> availableWizards = {
    Wizard("Fire Mage", MagicPower::REMOVE_ROW_WITH_OWN_CARD),
    Wizard("Ice Mage", MagicPower::REMOVE_OPPONENT_CARD_OVER_OWN),
    Wizard("Earth Mage", MagicPower::CREATE_HOLE),
    Wizard("Air Mage", MagicPower::MOVE_STACK_WITH_OWN_CARD),
    Wizard("Light Mage", MagicPower::GAIN_EXTRA_CARD),
    Wizard("Dark Mage", MagicPower::COVER_OPPONENT_CARD),
    Wizard("Water Mage", MagicPower::MOVE_STACK_WITH_OPPONENT_CARD),
    Wizard("Storm Mage", MagicPower::MOVE_ROW_TO_EDGE)
};


void wizardsDuel() {
    std::cout << "Starting Wizard's Duel...\n";

    // Randomizare vrăjitori
    srand(static_cast<unsigned>(time(0))); // Inițializare pentru rand()
    int index1 = rand() % availableWizards.size();
    int index2;
    do {
        index2 = rand() % availableWizards.size();
    } while (index1 == index2); // Asigură-te că vrăjitorii sunt diferiți

    Wizard wizard1 = availableWizards[index1];
    Wizard wizard2 = availableWizards[index2];

    // Configurare joc
    Game game(4, 
              "Player 1", 
              "Player 2",
              wizard1,
              wizard2,
              GameMode::WizardsDuel);

    // Configurare cărți pentru fiecare jucător
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(1));
        game.getPlayer2().addCard(Card(1));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(2));
        game.getPlayer2().addCard(Card(2));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));
    game.getPlayer1().addCard(Card(0, false, true)); // Eter
    game.getPlayer2().addCard(Card(0, false, true)); // Eter

    // Format meci: 3/5
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < 3 && player2Wins < 3) {
        game.resetGame();
        game.start();

        // Determină câștigătorul și actualizează scorul
        int score1 = game.getBoard().calculateScore(game.getPlayer1());
        int score2 = game.getBoard().calculateScore(game.getPlayer2());

        if (score1 > score2) {
            std::cout << game.getPlayer1().getName() << " wins this game!\n";
            ++player1Wins;
        }
        else if (score2 > score1) {
            std::cout << game.getPlayer2().getName() << " wins this game!\n";
            ++player2Wins;
        }
        else {
            std::cout << "This game is a tie!\n";
        }

        std::cout << "Current score: " << game.getPlayer1().getName() << " " << player1Wins
            << " - " << player2Wins << " " << game.getPlayer2().getName() << "\n";
    }

    // Determină câștigătorul meciului
    if (player1Wins == 3) {
        std::cout << game.getPlayer1().getName() << " wins the match!\n";
    }
    else {
        std::cout << game.getPlayer2().getName() << " wins the match!\n";
    }
}

const std::vector<MagicPower> availableElementalPowers = {
    MagicPower::CONTROLLED_EXPLOSION,
    MagicPower::DESTRUCTION,
    MagicPower::FLAMES,
    MagicPower::LAVA,
    MagicPower::FROM_ASHES,
    MagicPower::SPARKS,
    MagicPower::BLIZZARD,
    MagicPower::WHIRLWIND,
    MagicPower::HURRICANE,
    MagicPower::BLAST,
    MagicPower::MIRAGE,
    MagicPower::STORM,
    MagicPower::TIDE,
    MagicPower::FOG,
    MagicPower::WAVE,
    MagicPower::WHIRLPOOL,
    MagicPower::TSUNAMI,
    MagicPower::CASCADE,
    MagicPower::SUPPORT,
    MagicPower::EARTHQUAKE,
    MagicPower::SHATTER,
    MagicPower::BORDERS,
    MagicPower::AVALANCHE,
    MagicPower::BOULDER
};

void elementsDuel() {
    std::cout << "Starting Elements Duel...\n";

    // Randomizare puteri elementale
    srand(static_cast<unsigned>(time(0)));
    MagicPower player1Power1 = availableElementalPowers[rand() % availableElementalPowers.size()];
    MagicPower player1Power2 = availableElementalPowers[rand() % availableElementalPowers.size()];
    while (player1Power2 == player1Power1) {
        player1Power2 = availableElementalPowers[rand() % availableElementalPowers.size()];
    }

    MagicPower player2Power1 = availableElementalPowers[rand() % availableElementalPowers.size()];
    MagicPower player2Power2 = availableElementalPowers[rand() % availableElementalPowers.size()];
    while (player2Power2 == player2Power1) {
        player2Power2 = availableElementalPowers[rand() % availableElementalPowers.size()];
    }

    // Configurare joc
    Game game(4, "Player 1", "Player 2", GameMode::ElementsDuel);

    // Atribuire puteri
    game.getPlayer1().addElementalPower(player1Power1);
    game.getPlayer1().addElementalPower(player1Power2);
    game.getPlayer2().addElementalPower(player2Power1);
    game.getPlayer2().addElementalPower(player2Power2);

    // Configurare mâini
    game.getPlayer1().hand.clear();
    game.getPlayer2().hand.clear();
    for (int i = 0; i < 2; ++i) {
        game.getPlayer1().addCard(Card(1));
        game.getPlayer2().addCard(Card(1));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(2));
        game.getPlayer2().addCard(Card(2));
    }
    for (int i = 0; i < 3; ++i) {
        game.getPlayer1().addCard(Card(3));
        game.getPlayer2().addCard(Card(3));
    }
    game.getPlayer1().addCard(Card(4));
    game.getPlayer2().addCard(Card(4));
    game.getPlayer1().addCard(Card(0, false, true)); // Eter
    game.getPlayer2().addCard(Card(0, false, true)); // Eter

    // Format meci: 3/5
    int player1Wins = 0;
    int player2Wins = 0;

    while (player1Wins < 3 && player2Wins < 3) {
        std::cout << "\nStarting a new round...\n";
        game.resetGame(); // Resetează tabla și mâinile jucătorilor

        int currentPlayer = 1; // Player 1 începe fiecare rundă
        while (true) {
            game.getBoard().printBoard();
            Player& activePlayer = (currentPlayer == 1) ? game.getPlayer1() : game.getPlayer2();
            Player& opponent = (currentPlayer == 1) ? game.getPlayer2() : game.getPlayer1();

            std::cout << activePlayer.getName() << "'s turn.\n";

            std::string choice;
            if (activePlayer.canUseElementalPower()) {
                std::cout << "Do you want to use an elemental power? (yes/no): ";
                std::cin >> choice;

                if (choice == "yes") {
                    if (game.useElementalPower(activePlayer, opponent)) {
                        activePlayer.usePower();
                        currentPlayer = (currentPlayer == 1) ? 2 : 1;
                        continue;
                    }
                    else {
                        std::cout << "Failed to use elemental power.\n";
                    }
                }
            }

            std::cout << "Do you want to place an illusion? (yes/no): ";
            std::cin >> choice;

            bool moveSuccessful = (choice == "yes")
                ? game.placeIllusion(activePlayer, game.getBoard())
                : game.placeNormalCard(activePlayer, game.getBoard(), opponent);

            if (!moveSuccessful) {
                std::cout << activePlayer.getName() << " made an invalid move. Turn lost.\n";
            }

            std::string winCondition = game.getBoard().checkWinCondition(activePlayer);
            if (!winCondition.empty()) {
                std::cout << activePlayer.getName() << " wins this round with " << winCondition << "!\n";
                if (currentPlayer == 1) {
                    ++player1Wins;
                }
                else {
                    ++player2Wins;
                }
                break;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        std::cout << "Current score: "
            << game.getPlayer1().getName() << " " << player1Wins
            << " - " << player2Wins << " " << game.getPlayer2().getName() << "\n";
    }

    if (player1Wins == 3) {
        std::cout << game.getPlayer1().getName() << " wins the match!\n";
    }
    else {
        std::cout << game.getPlayer2().getName() << " wins the match!\n";
    }
}