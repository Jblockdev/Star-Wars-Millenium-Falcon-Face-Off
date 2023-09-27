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
    bool has_super_blaster = false;
    float super_blaster_damage; 
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

bool is_game_over(Character &user, Character &AI) {
    // Check if the game is over (i.e., either user has 0 or less health)
    if (user.health <= 0) {
        cout << AI.name << " has defeated " << user.name << " and will keep the Millennium Falcon!" << endl;
        return true;

    } else if (AI.health <= 0) {
        cout << user.name << " has defeated " << AI.name << " and is returning to Bespin in a new ride!" << endl;
        return true;

    } else {
        return false;
    }
}

void game_loop(Character &user, Character &AI) {
    bool game_over = false;

    cout << "The game begins!" << endl << endl;

    while (!game_over) {
        if (player_turn) {
            cout << "Your turn!" << endl;
            cout << endl;
            cout << user.name << " has " << user.health << "%" << " remaining." << endl;
        }
        else {
            cout << "AI's turn..." << endl;
            cout << endl;
            cout << AI.name << " has " << AI.health << "%" << " remaining." << endl;
        }


        if (rand() % 10 == 0) {

            if (!user.has_super_blaster && AI.has_super_blaster) {

                bool super_blaster_to_user = (rand() / double(RAND_MAX)) > 0.5;
                Character &character = super_blaster_to_user ? user : AI;
                character.has_super_blaster = true;
                cout << "A Super Blaster has been dropped! " << character.name << " has picked it up." << endl;

            }

        }

        // Calculate and apply damage to the defender based on the attacker's selected move
        Move move = get_move(player_turn ? user : AI);

         int damage = rand() % (move.max_damage - move.min_damage + 1) + move.min_damage;
        if (player_turn) {
            if (user.has_super_blaster) {
                damage *= 2;
                user.has_super_blaster = false;
                cout << user.name << " used the Super Blaster! The next attack will be regular." << endl;
            }
            AI.health -= damage;
        } else {
            if (AI.has_super_blaster) {
                damage *= 2;
                AI.has_super_blaster = false;
                cout << AI.name << " used the Super Blaster! The next attack will be regular." << endl;
            }
            user.health -= damage;
        }
    }
}

int main() {
    // Seed the random number generator
    srand(time(0));

    // Initialize the characters
    Character han = {"Han Solo", han_moves, 100};
    Character lando = {"Lando Calrissian", lando_moves, 100};

    // Display the intro and prompt the player to choose a character
    cout << "\t\t\t\tSTAR WARS: Millennium Falcon Face-Off" << endl;
    cout << endl;
    cout << "The last one standing keeps the Millennium Falcon!" << endl;
    cout << endl;
    cout << "Choose your character: " << endl;
    cout << endl;
    cout << "0: Han Solo " << endl;
    cout << endl;
    cout << "1: Lando Calrissian " << endl;
    cout << endl;

    int character_choice;
    cin >> character_choice;

    Character user;
    Character AI;

    if (character_choice == 0) {
        user = han;
        AI = lando;
    } else {
        user = lando;
        AI = han;
    }

    cout << "You have chosen " << user.name << "." << endl;

    // Start the game loop
    bool game_over = false;
    do {
        // Reset the health of both characters and the player turn flag
        han.health = 100;
        lando.health = 100;
        player_turn = true;

        game_loop(user, AI);

        // Ask the user if they want to play again
        char answer;
        cout << "Do you want to play again? (y/n): ";
        cin >> answer;
        cout << endl;

        if (answer == 'y' || answer == 'Y') {
            // Prompt the user to choose a new character
            cout << "Choose your character: " << endl;
            cout << endl;
            cout << "0: Han Solo " << endl;
            cout << endl;
            cout << "1: Lando Calrissian " << endl;
            cout << endl;

            int character_choice;
            cin >> character_choice;

            if (character_choice == 0) {
                user = {"Han Solo", han_moves, 100};
                AI = {"Lando Calrissian", lando_moves, 100};
            } else {
                user = {"Lando Calrissian", lando_moves, 100};
                AI = {"Han Solo", han_moves, 100};
            }

            game_over = false;
            player_turn = true;
        } else {
            cout << "Thanks for playing! May the force be with you - Always." << endl;
        }
    } while (!game_over);

    return 0;
}