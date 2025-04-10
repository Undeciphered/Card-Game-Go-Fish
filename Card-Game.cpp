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
        
        void print_hand() {
            for(card selected_card : hand) {
                std::cout << "[" << selected_card.card_info() << "] ";
            }
            std::cout << '\n';
        }
        
        bool has_card(std::string card_rank) {
            for(card selected_card : hand) {
                if(selected_card.rank == card_rank) {
                    return true;   
                }
            }
            return false;
        }
        
        std::vector<card> give_all_of_rank(std::string &chosen_card) {
            std::vector<card> cards_to_give;
            for(auto it = hand.begin(); it != hand.end();) {
                if(it->rank == chosen_card) {
                    cards_to_give.push_back(*it);
                    hand.erase(it);
                } else {
                    it++;   
                }
                
            }
            return cards_to_give;
            
        }
        
        void take_all_of_rank(player &chosen_payer, std::string &chosen_card) {
            std::vector<card> taken_cards = chosen_payer.give_all_of_rank(chosen_card);
            for(card selected_card : taken_cards) {
                hand.push_back(selected_card);
            }
            
        }
};

class go_fish {
    private:
        std::vector<player> players;
        deck mydeck;
        
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
            std::string command{""}, player_name{""};
            while(true) {
                print_players();
                std::cout << "\"add #\" to add players, \"remove #\" to remove a player and \"continue #\" to confirm players: ";
                std::cin >> command >> player_name;
                if(command == "add") {
                    add_player(player_name);
                } else if(command == "remove") {
                   remove_player(stoi(player_name));
                } else if(command == "continue") {
                    if(players.size() < 2) {
                        std::cout << "must have atleast 2 players to play\n";
                    } else {
                        break;   
                    }
                }
                std::cout << '\n';
            }
            
        }
        
        bool ask_player(std::string &player_number, std::string &card_name) {
            return players[stoi(player_number)-1].has_card(card_name);
            
        }
        
        void start_game() {
            while(true) {
                for(size_t i = 0; i < players.size(); i++) {
                    std::string chosen_player{""}, chosen_card{""};
                    
                    while(true) {
                        std::cout << "\nits your turn " << players[i].get_name() << " your cards are: ";
                        players[i].print_hand();
                        print_players();
                        std::cout << "please input \"player number\" \"card to ask for\":";
                        std::cin >> chosen_player >> chosen_card;
                        if(players[stoi(chosen_player)-1].get_name() != players[i].get_name()) {
                            if(players[i].has_card(chosen_card)) {
                                if(ask_player(chosen_player, chosen_card)) {
                                    std::cout << players[stoi(chosen_player)-1].get_name() << " has that card\n";
                                    players[i].take_all_of_rank(players[stoi(chosen_player)-1], chosen_card);
                                    std::cout << players[i].get_name() << " took all of " << players[stoi(chosen_player)-1].get_name() << "'s " << chosen_card << "'s\n";
                                } else {
                                    std::cout << players[stoi(chosen_player)-1].get_name() << " does not have that card go fish\n"; 
                                    players[i].draw_card(mydeck);
                                }
                                break;
                            } else {
                                std::cout << "to ask for a card you yourself need to have a card of the same rank" << players[i].get_name() << "\n"; 
                            }
                        } else {
                            std::cout << "you cannot ask yourself for a card " << players[i].get_name() << "\n";    
                        }
                    }
                    
                    
                }
            }
            
        }
        
        void setup_game() {
            mydeck.make_deck();
            mydeck.shuffle_deck();
            player_setup();
            deal_cards(mydeck);
            start_game();
            
        }
};

int main() {
    go_fish myfish;
    myfish.setup_game();
    
    return 0;
}
