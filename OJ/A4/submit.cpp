
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <random>
#include <initializer_list>

using namespace std;
// util.hpp ------------------------------------------------------------
template <typename T>
void shuffle_stack(std::stack<T> &stack)
{
    std::vector<T> tmp;
    while (!stack.empty())
    {
        tmp.push_back(stack.top());
        stack.pop();
    }

    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(tmp.begin(), tmp.end(), rng);

    for (const auto &cardPtr : tmp)
    {
        stack.push(cardPtr);
    }
}

template <typename T>
std::string stack_to_string(const std::stack<T> &stack)
{
    std::string result = "[";
    auto cpy = stack;
    while (!cpy.empty())
    {
        result += cpy.top()->to_string();
        cpy.pop();
        if (!cpy.empty())
        {
            result += ", ";
        }
    }
    return result + "]";
}

template <typename T>
std::string vector_to_string(const std::vector<T> &vector)
{
    std::string result = "[";
    for (size_t i = 0; i < vector.size(); i++)
    {
        result += vector[i]->to_string();
        if (i != vector.size() - 1)
        {
            result += ", ";
        }
    }
    return result + "]";
}

// card.hpp ------------------------------------------------------------
namespace uno
{
    class Game;

    class Card // parent class
    {
    protected:
        /**
         * @brief The color of the card
         */
        std::string color;

    public:
        /**
         * @brief Gets the string representation of the card
         * @return The formatted string
         */
        virtual std::string to_string() const = 0;

        /**
         * @brief Gets the point of the card
         * @return The point
         */
        virtual const int get_point() const = 0;

        /**
         * @brief Gets the color of the card
         * @return The color
         */
        const std::string &get_color() const
        {
            return color;
        }

        /**
         * @brief Checks if the card can be played
         * @param game The game instance
         * @return true if the card can be played, false otherwise
         */
        virtual bool is_available(const Game &game) const = 0;

        /**
         * @brief Performs the effect of the card
         * @param game The game instance
         */
        virtual void effect(Game &game) const = 0;
    };

    /**
     * @brief A number card, holds a number and a color
     * @note Its string representation is the number followed by the color, e.g. "1B", "2R"
     */
    class NumberCard : public Card
    {
    private:
        int number;

    public:
        NumberCard(std::string color, int number);
        std::string to_string() const override;
        const int get_point() const override;
        bool is_available(const Game &game) const override;
        void effect(Game &game) const override;
    };

    /**
     * @brief A skip card, holds a color
     * @note Its string representation is "S" followed by the color, e.g. "SB", "SR"
     */
    class SkipCard : public Card
    {
    public:
        SkipCard(std::string color);
        std::string to_string() const override;
        const int get_point() const override;
        bool is_available(const Game &game) const override;
        void effect(Game &game) const override;
    };
    /**
     * @brief A reverse card, holds a color
     * @note Its string representation is "R" followed by the color, e.g. "RB", "RR"
     */
    class ReverseCard : public Card
    {
    public:
        ReverseCard(std::string color);
        std::string to_string() const override;
        const int get_point() const override;
        bool is_available(const Game &game) const override;
        void effect(Game &game) const override;
    };

    /**
     * @brief A draw two card, holds a color
     * @note Its string representation is "D" followed by the color, e.g. "DB", "DR"
     */
    class DrawTwoCard : public Card
    {
    public:
        DrawTwoCard(std::string color);
        std::string to_string() const override;
        const int get_point() const override;
        bool is_available(const Game &game) const override;
        void effect(Game &game) const override;
    };
}

// player.hpp ------------------------------------------------------------
namespace uno
{

    class Player
    {
    private:
        /**
         * @brief The name of the player
         */
        std::string name;

        /**
         * @brief The cards in the player's hand
         */
        std::vector<const Card *> hand;

    public:
        /**
         * @brief Creates a new player with the given name
         * @param name The name of the player
         */
        explicit Player(std::string name) : name(std::move(name)) {}
        void add_card(const Card *card);
        void remove_card(const Card *card);
        const std::vector<const Card *> &get_hand() const;
        const std::string &get_name() const;
        int get_score() const;
    };
}

// player.cpp
namespace uno
{

    void Player::add_card(const Card *card)
    {
        hand.push_back(card);
    }

    void Player::remove_card(const Card *card)
    {
        for (auto it = hand.begin(); it != hand.end(); it++)
        {
            if (*it == card)
            {
                hand.erase(it);
                break;
            }
        }
    }

    const std::vector<const Card *> &Player::get_hand() const
    {
        return hand;
    }

    const std::string &Player::get_name() const
    {
        return name;
    }

    int Player::get_score() const
    {
        int score = 0;
        for (const Card *card : hand)
        {
            score += card->get_point();
        }
        return score;
    }

}

// game.hpp ------------------------------------------------------------
namespace uno
{

    class Game
    {
    private:
        /**
         * The players in the game
         */
        std::vector<Player *> players;

        /**
         * The index of the current player
         */
        int current_player_index;

        /**
         * The direction of the game, 1 for right, -1 for left
         */
        int direction = 1;

        /**
         * The draw pile. Initially holds all 50 cards
         */
        std::stack<const Card *> draw;

        /**
         * The discard pile. Initially empty
         */
        std::stack<const Card *> discard;

    public:
        /**
         * @brief Creates a new game with the given players joining
         * @param players The players in the game, length must be between 2 and 4 (inclusive)
         * @throws std::invalid_argument if the number of players is invalid
         * @note For the {@param players} as {@code {"P1", "P2", "P3", "P4"}}, they should sit in the order of:
         *       ```
         *        P1  --→  P2
         *         ↖︎       ↘︎
         *          P4  ←--  P3
         *       ```
         */
        Game(std::initializer_list<Player *> players);

        /**
         * @brief Sets up the game (check the game rules)
         */
        void setup();

        /**
         * @brief Plays the turn
         * @return true if the game ends, false otherwise
         */
        bool play();

        /**
         * @brief Gets the winner of the game
         * @return The name of the winner followed by its score, e.g. "Player 1 (500)"
         * @note If the game is not over, return an empty string ("")
         */
        std::string get_winner() const;

        /**
         * @brief Prints the current state of the game
         * @param os The output stream
         * @param game The game instance
         * @return The output stream
         * @note A sample output is:
         *      ```
         *      Draw: [9B, 9R, DR, 6R, 5B, SB, 3R, 6R, 7B, SR, 2R, 9B, 1B, 8R, 8B, 5B, 4R, 3B, 0R, 1R, 5R]
         *      Discard: [2B]
         *      Current: Player 2
         *      Direction: Right
         *      Player 1: [7R, 6B, 7B, 3R, 1R, 2B, RR]
         *      Player 2: [SR, 4R, 6B, RR, 8B, RB, 0B]
         *      Player 3: [9R, 4B, 5R, 8R, 4B, RB, 1B]
         *      Player 4: [DB, 2R, 3B, DR, 7R, SB, DB]
         *      ```
         *      For the draw and discard piles, the card on top should be shown at the start
         *      The players are represented by their name (not Player+index or so)
         */
        friend std::ostream &operator<<(std::ostream &os, const Game &game);

        friend class NumberCard;

        friend class SkipCard;

        friend class ReverseCard;

        friend class DrawTwoCard;

        const Card *get_top_card() const;

        void refill_draw_pile();
    };
};

// card.cpp
namespace uno
{

    // 实现 Card 类的成员函数

    // NumberCard
    NumberCard::NumberCard(std::string color, int number)
    {
        this->color = color;
        this->number = number;
    }

    std::string NumberCard::to_string() const
    {
        return std::to_string(number) + color;
    }

    const int NumberCard::get_point() const
    {
        return number;
    }

    bool NumberCard::is_available(const Game &game) const
    {
        const Card *top = game.get_top_card();
        // if top card is a number card
        if (dynamic_cast<const NumberCard *>(top))
        {
            const NumberCard *topNumberCard = dynamic_cast<const NumberCard *>(top);
            // if the color is the same
            if (topNumberCard->get_color() == color)
            {
                return true;
            }
            // if the number is the same
            if (topNumberCard->get_point() == number)
            {
                return true;
            }
        }
        // if top card is a function card
        else
        {
            // if the color is the same
            if (top->get_color() == color)
            {
                return true;
            }
        }
        return false;
    }

    void NumberCard::effect(Game &game) const
    {
        game.discard.push(this);
    }

    // SkipCard
    SkipCard::SkipCard(std::string color)
    {
        this->color = color;
    }

    std::string SkipCard::to_string() const
    {
        return "S" + color;
    }

    const int SkipCard::get_point() const
    {
        return 20;
    }

    bool SkipCard::is_available(const Game &game) const
    {
        const Card *top = game.get_top_card();
        if (dynamic_cast<const SkipCard *>(top))
        {
            return true;
        }
        else
        {
            if (top->get_color() == color)
            {
                return true;
            }
        }
        return false;
    }

    void SkipCard::effect(Game &game) const
    {
        game.discard.push(this);
        game.current_player_index = (game.current_player_index + game.direction + game.players.size()) % game.players.size();
    }

    // ReverseCard
    ReverseCard::ReverseCard(std::string color)
    {
        this->color = color;
    }

    std::string ReverseCard::to_string() const
    {
        return "R" + color;
    }

    const int ReverseCard::get_point() const
    {
        return 30;
    }

    bool ReverseCard::is_available(const Game &game) const
    {
        const Card *top = game.get_top_card();
        if (dynamic_cast<const ReverseCard *>(top))
        {
            return true;
        }
        else
        {
            if (top->get_color() == color)
            {
                return true;
            }
        }
        return false;
    }

    void ReverseCard::effect(Game &game) const
    {
        game.discard.push(this);
        game.direction *= -1;
    }

    // DrawTwoCard
    DrawTwoCard::DrawTwoCard(std::string color)
    {
        this->color = color;
    }

    std::string DrawTwoCard::to_string() const
    {
        return "D" + color;
    }

    const int DrawTwoCard::get_point() const
    {
        return 40;
    }

    bool DrawTwoCard::is_available(const Game &game) const
    {
        const Card *top = game.get_top_card();
        if (dynamic_cast<const DrawTwoCard *>(top))
        {
            return true;
        }
        else
        {
            if (top->get_color() == color)
            {
                return true;
            }
        }
        return false;
    }

    void DrawTwoCard::effect(Game &game) const
    {
        game.discard.push(this);
        size_t nextPlayerIndex = (game.current_player_index + game.direction + game.players.size()) % game.players.size();
        Player *nextPlayer = game.players[nextPlayerIndex];
        for (int i = 0; i < 2; i++)
        {
            if (game.draw.empty())
            {
                game.refill_draw_pile();
            }
            const Card *card = game.draw.top();
            game.draw.pop();
            nextPlayer->add_card(card);
        }
        // skip the next player
        game.current_player_index = (game.current_player_index + game.direction + game.players.size()) % game.players.size();
    }
}

// game.cpp ------------------------------------------------------------
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
            for (size_t j = 0; j < this->players.size(); j++)
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
        if (winner == nullptr)
        {
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
