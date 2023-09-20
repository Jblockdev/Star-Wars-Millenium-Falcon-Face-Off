#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

// Define the moves and their effects
struct Move {
    string name;
    int max_damage;
    int min_damage;
};

Move lando_moves[3] {
    {"X-8 Night Sniper", 30, 10},
    {"Disruptor Shot", 25, 5},
    {"Shock Grenade", 40, 15}
};

Move han_moves[3] {
    {"DL-44", 30, 10},
    {"Charging Shoulder", 25, 5},
    {"Thermal Detonator", 40, 15}
};

// Define the characters and their attributes
struct Character {
    string name;
    Move *moves;
    int health;
};

// Define some helper functions for the game flow
bool player_turn = true; // If true, it's the player's turn. If false, it's the AI's turn.

Move get_move(Character character) {
    // Get the player's or AI's move choice
    Move chosen_move;
    int move_choice;
    
    if (player_turn) {
        cout << "Select a move for " << character.name << ":" << endl;
        for (int i = 0; i < 3; i++) {
            cout << i << ". " << character.moves[i].name << endl;
        }
        
        cin >> move_choice;
        chosen_move = character.moves[move_choice];
    } else {
        move_choice = rand() % 3;
        chosen_move = character.moves[move_choice];
        
        cout << character.name << " used " << chosen_move.name << endl;
    }
    
    return chosen_move;
}

bool is_game_over(Character &han, Character &lando) {
    // Check if the game is over (i.e., either player has 0 or less health)
    if (han.health <= 0) {
        cout << "Lando Calrissian wins!" << endl;
        cout << "Han Solo has " << 0 << " health remaining." << endl;
        cout << "Lando Calrissian has " << lando.health << " health remaining." << endl;
        return true;
    } else if (lando.health <= 0) {
        cout << "Han Solo wins!" << endl;
        cout << "Lando Calrissian has " << 0 << " health remaining." << endl;
        cout << "Han Solo has " << han.health << " health remaining." << endl;
        return true;
    } else {
        return false;
    }
}

void game_loop(Character &player, Character &ai) {
    bool game_over = false;

    cout << "The game begins!" << endl << endl;

    while (!game_over) {
        if (player_turn) {
            cout << "Your turn!" << endl;
        } else {
            cout << "AI's turn..." << endl;
        }

        if (player_turn) {
            cout << "Your health: " << player.health << endl;
            cout << "AI's health: " << ai.health << endl;
        }

        // Calculate and apply damage to the defender based on the attacker's selected move
        Move move = get_move(player_turn ? player : ai);

        int damage = rand() % (move.max_damage - move.min_damage + 1) + move.min_damage;
        (player_turn ? ai : player).health -= damage;

        cout << (player_turn ? player.name : ai.name) << " used " << move.name << " and dealt " << damage << " damage to " << (player_turn ? ai.name : player.name) << "." << endl;

        game_over = is_game_over(player, ai);

        player_turn = !player_turn;

        cout << endl;
    }
}

int main() {
    // Seed the random number generator
    srand(time(0));
    
    // Initialize the characters
    Character han = {"Han Solo", han_moves, 100};
    Character lando = {"Lando Calrissian", lando_moves, 100};
    
    // Display the intro and prompt the player to choose a character
    cout << "\t\t\t\tSTAR WARS: Millenium Falcon Face-Off" << endl;
    cout << endl;
    cout << "The winner will keeps the Millenium Falcon!" << endl;
    cout << endl;
    cout << "Choose your character: " << endl;
    cout << endl;
    cout << "0: Han Solo " << endl;
    cout << "1: Lando Calrissian " << endl;
    cout << endl;
    
    int character_choice;
    cin >> character_choice;
    
    Character player;
    Character ai;
    
    if (character_choice == 0) {
        player = han;
        ai = lando;
    } else {
        player = lando;
        ai = han;
    }
    
    cout << "You have chosen " << player.name << "." << endl;

    // Start the game loop
    do {
        // Reset the health of both characters and the player turn flag
        han.health = 100;
        lando.health = 100;
        player_turn = true;
        
        game_loop(player, ai);

        // Ask the player if they want to play again
        char answer;
        cout << "Do you want to play again? (y/n): ";
        cin >> answer;
        cout << endl;
        
        if (answer == 'y' || answer == 'Y') {
            // Start a new game
            continue;
        } else {
            // Exit the program
            break;
        }
    } while (true);
    
    return 0;
}
