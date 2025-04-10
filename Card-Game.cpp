#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

struct card {
    std::string suit{""};
    std::string rank{""};
    int value{0};
    card(std::string suit, std::string rank, int value)
        : suit(suit), rank(rank), value(value) {}
    std::string card_info() {
        return (rank + " of " + suit);
    }   
};

class deck {
    private:
        std::vector<std::string> card_suits = {"hearts", "diamonds", "clubs", "spades"};
        std::vector<std::string> card_ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        std::vector<card> cards;
        std::vector<card> discard_pile;
        std::random_device rd;
        std::mt19937 g;
        
    public:
        deck() : g(rd()) {}
        
        void make_deck() {
            for(std::string suit : card_suits) {
                int current_value{0};
                for(std::string rank : card_ranks) {
                    current_value++;
                    cards.push_back(card(suit, rank, current_value));
                }
            }   
        }
        
        void print_deck() {
            for(card selected_card : cards) {
                std::cout << selected_card.rank << " of " << selected_card.suit << '\n';
            }   
        }
        
        void shuffle_deck() {
            std::shuffle(cards.begin(), cards.end(), g);
        }
        
        card draw_card() {
            card drawn_card = cards.front();
            cards.erase(cards.begin());
            return drawn_card;  
        }
};

class player {
    private:
        std::string name{""};
        std::vector<card> hand; 
        std::vector<int> books;
    
    public:
        player(std::string player_name) : name(player_name) {}
        
        void draw_card(deck &deck_to_draw_from) {
                hand.push_back(deck_to_draw_from.draw_card());
            }
            
        card draw_first_card () {
            card first_card_in_hand = hand.front();
            hand.erase(hand.begin());
            return first_card_in_hand;
        }  
        
        void pick_up_card(card &card_picked_up) {
            hand.push_back(card_picked_up);
        }
        
        int card_count() {
            return hand.size();   
        }
        
        std::string get_name() {
            return name;   
        }
};

class go_fish {
    private:
        std::vector<player> players;
        
    public:
        void add_player(std::string name) {
            if(players.size() < 5) {
                players.push_back(player(name));
            } else {
                std::cout << "the max amount of players is 5\n";
            }
            
        }
    
        void print_players() {
            for(size_t i = 0; i < players.size(); i++) {
                std::cout << i+1 << ": " << players[i].get_name() << "\n";
            }   
        }
        
        void remove_player(int index) {
            players.erase(players.begin()+(index-1));
            
        }
        
        void deal_cards(deck& selected_deck) {
            for(player& selected_player : players) {
                for(int i = 0; i < 5; i++) {
                    selected_player.draw_card(selected_deck);
                } 
            } 
        }
        
        void player_setup() {
            bool selecting{true};
            std::string command{""}, player_name{""};
            while(selecting) {
                print_players();
                std::cout << "\"add #\" to add players, \"remove #\" to remove a player and \"continue #\" to confirm players: ";
                std::cin >> command >> player_name;
                if(command == "add") {
                    add_player(player_name);
                } else if(command == "remove") {
                   remove_player(stoi(player_name));
                } else if(command == "continue") {
                    selecting = false;   
                }
                std::cout << '\n';
            }
            
        }
        
        void start_game() {
            
            
            
        }
        
        void setup_game() {
            deck mydeck;
            mydeck.make_deck();
            mydeck.shuffle_deck();
            player_setup();
            deal_cards(mydeck);
            start_Game();
            
        }
};

int main() {
    go_fish myfish;
    myfish.setup_game();
    
    return 0;
}
