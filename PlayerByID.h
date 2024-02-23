//
// Created by Gal Ishai on 2/15/24.
//

#ifndef WET_1_PLAYERBYID_H
#define WET_1_PLAYERBYID_H

#include "Player.h"

class PlayerByStrength;

class PlayerByID : public Player
{
public:
    PlayerByStrength* m_StrengthVersionThird;
    PlayerByStrength* m_StrengthVersionTeamGen;
    int m_currentThird; //1-first, 2-second, 3-last

    PlayerByID(int ID, int strength, Sport sport, Country *country) : Player(ID,strength,sport,country)
    {
        m_StrengthVersionThird = nullptr;
        m_StrengthVersionTeamGen = nullptr;
        m_currentThird = -1;
    }

    explicit PlayerByID(PlayerByID* other): Player(other)
    {
        m_StrengthVersionThird = other->m_StrengthVersionThird;
        m_StrengthVersionTeamGen = other->m_StrengthVersionTeamGen;
        m_currentThird = other->m_currentThird;
    }

    bool operator<(Player *other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if (m_ID < other->m_ID) {
            return true;
        }
        return false;
    }

};


#endif //WET_1_PLAYERBYID_H
