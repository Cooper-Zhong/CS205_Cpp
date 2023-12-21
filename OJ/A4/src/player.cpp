
#include "player.hpp"

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
