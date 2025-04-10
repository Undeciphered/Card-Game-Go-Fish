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
        std::vector<card> hand; // this is used as the players deck in war
    
    public:
        player(std::string player_name) : name(player_name) {}
        
        void draw_card(deck &deck_to_draw_from) {
                hand.push_back(deck_to_draw_from.draw_card());
            }
            
        card draw_first_card () { // draws the first card in hand, or from the players deck in war
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

int main() {
    
    return 0;
}
