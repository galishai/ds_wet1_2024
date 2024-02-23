//
// Created by Gal Ishai on 2/15/24.
//

#ifndef WET_1_PLAYER_H
#define WET_1_PLAYER_H

#include "wet1util.h"

#include "Node.h"
#include "AVLTree.h"

class Country;

class Team;

class Player
{
public:
    int m_ID;
    int m_teamCount;
    int m_strength;
    Sport m_sport;
    Country *m_playerCountry;
    Team *m_team1;
    Team *m_team2;
    Team *m_team3;

    Player(int ID, int strength, Sport sport, Country *country)
    {
        m_ID = ID;
        m_teamCount = 0;
        m_strength = strength;
        m_sport = sport;
        m_playerCountry = country;
        m_team1 = nullptr;
        m_team2 = nullptr;
        m_team3 = nullptr;
    }

    explicit Player(Player *other)
    {
        m_ID = other->m_ID;
        m_strength = other->m_strength;
        m_sport = other->m_sport;
        m_playerCountry = other->m_playerCountry;
        m_team1 = other->m_team1;
        m_team2 = other->m_team2;
        m_team3 = other->m_team3;
    }

    virtual ~Player() = default;

    virtual bool operator<(Player *other) const
    {
        return false;
    }

    virtual bool operator==(Player *other) const
    {
        if (other == nullptr)
        {
            return false;
        }
        if (m_ID == other->m_ID) {
            return true;
        }
        return false;
    }
};




#endif //WET_1_PLAYER_H
