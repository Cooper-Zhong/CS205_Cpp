#include "game.hpp"
#include "util.hpp"
using namespace std;
namespace uno
{

    Game::Game(initializer_list<Player *> players)
    {
        if (players.size() < 2 || players.size() > 4)
        {
            throw invalid_argument("Invalid number of players");
        }
        this->players.assign(players);
    }

    void Game::setup()
    {
        this->draw = stack<const Card *>();
        this->discard = stack<const Card *>();
        // initialize draw pile
        // number cards
        this->draw.push(new NumberCard("R", 0));
        this->draw.push(new NumberCard("B", 0));
        for (size_t i = 1; i <= 9; i++)
        { // 1-9, 2 each
            this->draw.push(new NumberCard("R", i));
            this->draw.push(new NumberCard("R", i));
            this->draw.push(new NumberCard("B", i));
            this->draw.push(new NumberCard("B", i));
        }
        // skip cards, 2 each
        this->draw.push(new SkipCard("R"));
        this->draw.push(new SkipCard("R"));
        this->draw.push(new SkipCard("B"));
        this->draw.push(new SkipCard("B"));
        // reverse cards, 2 each
        this->draw.push(new ReverseCard("R"));
        this->draw.push(new ReverseCard("R"));
        this->draw.push(new ReverseCard("B"));
        this->draw.push(new ReverseCard("B"));
        // draw two cards, 2 each
        this->draw.push(new DrawTwoCard("R"));
        this->draw.push(new DrawTwoCard("R"));
        this->draw.push(new DrawTwoCard("B"));
        this->draw.push(new DrawTwoCard("B"));
        // shuffle
        shuffle_stack(this->draw);
        // randomly choose a starting player
        this->current_player_index = rand() % this->players.size();
        // deal 7 cards to each player
        for (size_t i = 0; i < 7; i++)
        {
            for (size_t j = 1; j < this->players.size(); j++)
            {
                this->players[j]->add_card(this->draw.top());
                this->draw.pop();
            }
        }
        // place the top card to the discard pile
        this->discard.push(this->draw.top());
        this->draw.pop();
    }

    bool Game::play() // play one turn
    {
        Player *currentPlayer = this->players[this->current_player_index];
        const vector<const Card *> &hand = currentPlayer->get_hand();
        if (hand.empty())
        {
            return true;
        }
        
        vector<const Card *> available_cards;
        for (const Card *card : hand)
        {
            if (card->is_available(*this))
            {
                available_cards.push_back(card);
            }
        }

        if (available_cards.empty())
        {
            // draw a card, first check if the draw pile is empty
            if (this->draw.empty())
            {
                refill_draw_pile();
            }
            const Card *card = this->draw.top();
            this->draw.pop();
            currentPlayer->add_card(card);
        }
        else
        { // choose a random card to play
            const Card *card = available_cards[rand() % available_cards.size()];
            card->effect(*this);
            currentPlayer->remove_card(card);
            if (hand.empty())
            {
                return true;
            }
        }
        this->current_player_index = (this->current_player_index + this->direction + this->players.size()) % this->players.size();
        return false;
    }

    string Game::get_winner() const
    {
        Player *winner = nullptr;
        for (size_t i = 0; i < this->players.size(); i++)
        {
            if (this->players[i]->get_hand().empty())
            {
                winner = this->players[i];
            }
        }
        if(winner == nullptr){
            return "";
        }
        // calculate the score
        int total = 0;
        for (size_t i = 0; i < this->players.size(); i++)
        {
            total += this->players[i]->get_score();
        }
        return winner->get_name() + " (" + to_string(total) + ")";

    }

    /*
    ```
             *      Draw: [9B, 9R, DR, 6R, 5B, SB, 3R, 6R, 7B, SR, 2R, 9B, 1B, 8R, 8B, 5B, 4R, 3B, 0R, 1R, 5R]
             *      Discard: [2B]
             *      Current: Player 2
             *      Direction: Right
             *      Player 1: [7R, 6B, 7B, 3R, 1R, 2B, RR]
             *      Player 2: [SR, 4R, 6B, RR, 8B, RB, 0B]
             *      Player 3: [9R, 4B, 5R, 8R, 4B, RB, 1B]
             *      Player 4: [DB, 2R, 3B, DR, 7R, SB, DB]
             *      ```
    */
    ostream &operator<<(ostream &os, const Game &game)
    {
        os << "Draw: " << stack_to_string(game.draw) << "\n";
        os << "Discard: " << stack_to_string(game.discard) << "\n";
        os << "Current: " << game.players[game.current_player_index]->get_name() << "\n";
        os << "Direction: " << (game.direction == 1 ? "Right" : "Left") << "\n";
        for (size_t i = 0; i < game.players.size(); ++i)
        {
            Player *player = game.players[i];
            os << player->get_name() << ": " << vector_to_string(player->get_hand()) << "\n";
        }
        return os;
    }

    const Card *Game::get_top_card() const
    {
        if (!discard.empty())
        {
            return discard.top();
        }
        else
        {
            return nullptr;
        }
    }

    void Game::refill_draw_pile()
    {
        // keep the top card of the discard pile
        const Card *top = discard.top();
        discard.pop();
        // shuffle the rest of the discard pile
        shuffle_stack(discard);
        while (!discard.empty())
        {
            draw.push(discard.top());
            discard.pop();
        }
        discard.push(top); // put the top card back
    }

}
