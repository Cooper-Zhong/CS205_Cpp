#include "card.hpp"
#include "game.hpp"
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
