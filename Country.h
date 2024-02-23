//
// Created by Gal Ishai on 2/15/24.
//

#ifndef WET_1_COUNTRY_H
#define WET_1_COUNTRY_H

#include "Team.h"

#include "AVLTree.h"

//class Team;

class Country
{
public:
    int m_countryID;
    int m_medals;
    AVLTree<Team>* m_countryTeams;
    int m_playerCount;
    //AVLTree<PlayerByID>* m_countryPlayers;

    Country(int countryID, int medals)
    {
        m_countryID = countryID;
        m_medals = medals;
        m_countryTeams = new AVLTree<Team>();
        m_playerCount = 0;
        //m_countryPlayers = new AVLTree<PlayerByID>();
    }

    ~Country()
    {
        delete m_countryTeams;
        //delete m_countryPlayers;
        m_countryTeams = nullptr;
        //m_countryPlayers = nullptr;
    }

    bool operator<(Country *other) const
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_countryID < other->m_countryID)
        {
            return true;
        }
        return false;
    }

    bool operator==(Country* other) const
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_countryID == other->m_countryID)
        {
            return true;
        }
        return false;
    }




};


#endif //WET_1_COUNTRY_H
