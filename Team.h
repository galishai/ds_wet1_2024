//
// Created by Gal Ishai on 2/15/24.
//

#ifndef WET_1_TEAM_H
#define WET_1_TEAM_H

#include "Player.h"
#include "PlayerByStrength.h"
#include "PlayerByID.h"

class Team
{
public:
    int m_teamID;
    PlayerByStrength* m_firstThirdMax1STR;
    PlayerByStrength* m_secondThirdMax1STR;
    PlayerByStrength* m_lastThirdMax1STR;
    PlayerByStrength* m_firstThirdMax2STR;
    PlayerByStrength* m_secondThirdMax2STR;
    PlayerByStrength* m_lastThirdMax2STR;
    PlayerByID* m_firstThirdMax1ID;
    PlayerByID* m_secondThirdMax1ID;
    PlayerByID* m_lastThirdMax1ID;
    PlayerByID* m_firstThirdMax2ID;
    PlayerByID* m_secondThirdMax2ID;
    PlayerByID* m_lastThirdMax2ID;
    PlayerByStrength* m_firstThirdMax3STR;
    PlayerByStrength* m_secondThirdMax3STR;
    PlayerByStrength* m_lastThirdMax3STR;
    PlayerByStrength* m_firstThirdMin1STR;
    PlayerByStrength* m_secondThirdMin1STR;
    PlayerByStrength* m_lastThirdMin1STR;
    PlayerByID* m_firstThird1stMinID;
    PlayerByID* m_firstThird2ndMinID;
    PlayerByID* m_firstThird3rdMinID;
    PlayerByID* m_secondThird1stMinID;
    PlayerByID* m_secondThird2ndMinID;
    PlayerByID* m_secondThird3rdMinID;
    PlayerByID* m_lastThird1stMinID;
    PlayerByID* m_lastThird2ndMinID;
    PlayerByID* m_lastThird3rdMinID;
    Sport m_sport;
    Country* m_teamCountry;
    //Team* m_teamInCountryTree;
    AVLTree<PlayerByStrength>* m_playersBySTR;
    AVLTree<PlayerByID>* m_firstThirdID;
    AVLTree<PlayerByID>* m_secondThirdID;
    AVLTree<PlayerByID>* m_lastThirdID;
    AVLTree<PlayerByStrength>* m_firstThirdSTR;
    AVLTree<PlayerByStrength>* m_secondThirdSTR;
    AVLTree<PlayerByStrength>* m_lastThirdSTR;

    //void addPlayer(PlayerByID *playerID, PlayerByStrength *playerSTR);

    //void removePlayer(PlayerByStrength *playerSTRGen); //input: player from general strength tree of team

    //void updateMinMax(Team);

    Team(int teamID, Sport sport)
    {
        m_firstThirdID = new AVLTree<PlayerByID>();
        m_secondThirdID = new AVLTree<PlayerByID>();
        m_lastThirdID = new AVLTree<PlayerByID>();
        m_firstThirdSTR = new AVLTree<PlayerByStrength>();
        m_secondThirdSTR = new AVLTree<PlayerByStrength>();
        m_lastThirdSTR = new AVLTree<PlayerByStrength>();
        m_playersBySTR = new AVLTree<PlayerByStrength>();
        m_teamID = teamID;
        m_sport = sport;
        m_teamCountry = nullptr;
        m_firstThirdMax1STR = nullptr;
        m_secondThirdMax1STR = nullptr;
        m_lastThirdMax1STR = nullptr;
        m_firstThirdMax2STR = nullptr;
        m_secondThirdMax2STR = nullptr;
        m_lastThirdMax2STR = nullptr;
        m_firstThirdMax1ID = nullptr;
        m_secondThirdMax1ID = nullptr;
        m_lastThirdMax1ID = nullptr;
        m_firstThirdMax2ID = nullptr;
        m_secondThirdMax2ID = nullptr;
        m_lastThirdMax2ID = nullptr;
        m_firstThirdMax3STR = nullptr;
        m_secondThirdMax3STR = nullptr;
        m_lastThirdMax3STR = nullptr;
        m_firstThirdMin1STR = nullptr;
        m_secondThirdMin1STR = nullptr;
        m_lastThirdMin1STR = nullptr;
        m_firstThird1stMinID = nullptr;
        m_firstThird2ndMinID = nullptr;
        m_firstThird3rdMinID = nullptr;
        m_secondThird1stMinID = nullptr;
        m_secondThird2ndMinID = nullptr;
        m_secondThird3rdMinID = nullptr;
        m_lastThird1stMinID = nullptr;
        m_lastThird2ndMinID = nullptr;
        m_lastThird3rdMinID = nullptr;

    }

    ~Team()
    {
        delete m_playersBySTR;
        delete m_firstThirdID;
        delete m_secondThirdID;
        delete m_lastThirdID;
        delete m_firstThirdSTR;
        delete m_secondThirdSTR;
        delete m_lastThirdSTR;
    }

    bool operator<(Team* other) const
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_teamID < other->m_teamID)
        {
            return true;
        }
        return false;
    }

    bool operator==(Team* other) const
    {
        if(other == nullptr)
        {
            return false;
        }
        if(m_teamID == other->m_teamID)
        {
            return true;
        }
        return false;
    }
};

static void addPlayer(Team* team, PlayerByID *playerID, PlayerByStrength *playerSTR)
{
    playerID->m_StrengthVersionThird = playerSTR;
    playerSTR->m_playerInIDThird = playerID;
    try
    {
        PlayerByStrength *playerSTRCopy = new PlayerByStrength(playerSTR->m_ID,playerSTR->m_strength,playerSTR->m_sport,playerSTR->m_playerCountry);
        playerSTRCopy->m_playerInIDThird = playerID;
        playerID->m_StrengthVersionTeamGen = playerSTRCopy;
        team->m_playersBySTR->insertNode(playerSTRCopy);
        if (team->m_firstThirdID->isEmpty())
        {
            team->m_firstThirdID->insertNode(playerID);
            team->m_firstThirdSTR->insertNode(playerSTR);
            playerID->m_currentThird = 1;
        } else if (team->m_secondThirdID->isEmpty())
        {
            if(*team->m_firstThirdMax1ID < playerID)
            {
                team->m_secondThirdID->insertNode(playerID);
                team->m_secondThirdSTR->insertNode(playerSTR);
                playerID->m_currentThird = 2;
            }
            else
            {
                team->m_firstThirdID->insertNode(playerID);
                team->m_firstThirdSTR->insertNode(playerSTR);
                Node<PlayerByID> *max = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
                PlayerByID *movePlayerID = new PlayerByID(max->m_info->m_ID, max->m_info->m_strength,
                                                          max->m_info->m_sport, max->m_info->m_playerCountry);
                max->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionTeamGen = max->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = max->m_info->m_StrengthVersionThird;
                movePlayerID->m_playerInIDGen = max->m_info->m_playerInIDGen;
                PlayerByStrength *targetSTR = max->m_info->m_StrengthVersionThird;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                team->m_firstThirdID->removeNode(max->m_info);
                team->m_firstThirdSTR->removeNode(movePlayerID->m_StrengthVersionThird);
                team->m_secondThirdID->insertNode(movePlayerID);
                team->m_secondThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                movePlayerID->m_currentThird = 2;
            }
        } else if (team->m_lastThirdID->isEmpty())
        {
            if(*team->m_secondThirdMax1ID < playerID)
            {
                team->m_lastThirdID->insertNode(playerID);
                team->m_lastThirdSTR->insertNode(playerSTR);
                playerID->m_currentThird = 3;
            }
            else if(*team->m_firstThirdMax1ID < playerID)
            {
                team->m_secondThirdID->insertNode(playerID);
                team->m_secondThirdSTR->insertNode(playerSTR);
                Node<PlayerByID> *max = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
                PlayerByStrength *targetSTR = max->m_info->m_StrengthVersionThird;
                PlayerByID *movePlayerID = new PlayerByID(max->m_info->m_ID, max->m_info->m_strength,
                                                          max->m_info->m_sport, max->m_info->m_playerCountry);
                max->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = movePlayerID;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                movePlayerID->m_StrengthVersionTeamGen = max->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerID->m_playerInIDGen = max->m_info->m_playerInIDGen;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                team->m_secondThirdID->removeNode(max->m_info);
                team->m_secondThirdSTR->removeNode(targetSTR);
                team->m_lastThirdID->insertNode(movePlayerID);
                team->m_lastThirdSTR->insertNode(movePlayerSTR);
                playerID->m_currentThird = 2;
                movePlayerID->m_currentThird = 3;
            }
            else
            {
                team->m_firstThirdID->insertNode(playerID);
                team->m_firstThirdSTR->insertNode(playerSTR);
                Node<PlayerByID> *max1 = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
                PlayerByID *movePlayerID = new PlayerByID(max1->m_info->m_ID, max1->m_info->m_strength,
                                                          max1->m_info->m_sport, max1->m_info->m_playerCountry);
                max1->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionTeamGen = max1->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = max1->m_info->m_StrengthVersionThird;
                movePlayerID->m_playerInIDGen = max1->m_info->m_playerInIDGen;
                PlayerByStrength *targetSTR = max1->m_info->m_StrengthVersionThird;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                team->m_firstThirdID->removeNode(max1->m_info);
                team->m_firstThirdSTR->removeNode(movePlayerID->m_StrengthVersionThird);
                team->m_secondThirdID->insertNode(movePlayerID);
                team->m_secondThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                movePlayerID->m_currentThird = 2;
                //team->m_secondThirdID->insertNode(playerID);
                //team->m_secondThirdSTR->insertNode(playerSTR);
                Node<PlayerByID> *max2 = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
                PlayerByStrength *targetSTR2 = max2->m_info->m_StrengthVersionThird;
                PlayerByID *movePlayerID2 = new PlayerByID(max2->m_info->m_ID, max2->m_info->m_strength,
                                                          max2->m_info->m_sport, max2->m_info->m_playerCountry);
                max2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = movePlayerID;
                PlayerByStrength *movePlayerSTR2 = new PlayerByStrength(targetSTR2->m_ID, targetSTR2->m_strength,
                                                                       targetSTR2->m_sport, targetSTR2->m_playerCountry);
                movePlayerID2->m_StrengthVersionTeamGen = max2->m_info->m_StrengthVersionTeamGen;
                movePlayerID2->m_StrengthVersionThird = movePlayerSTR2;
                movePlayerID2->m_playerInIDGen = max2->m_info->m_playerInIDGen;
                movePlayerSTR2->m_playerInIDThird = movePlayerID2;
                team->m_secondThirdID->removeNode(max2->m_info);
                team->m_secondThirdSTR->removeNode(targetSTR2);
                team->m_lastThirdID->insertNode(movePlayerID2);
                team->m_lastThirdSTR->insertNode(movePlayerSTR2);
                movePlayerID2->m_currentThird = 3;
                playerID->m_currentThird = 1;
            }
        } else if (*playerID < team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root)->m_info)
        {
            team->m_firstThirdID->insertNode(playerID);
            team->m_firstThirdSTR->insertNode(playerSTR);
            playerID->m_currentThird = 1;
            if (team->m_firstThirdID->m_treeSize - team->m_secondThirdID->m_treeSize == 2 && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
            {
                Node<PlayerByID> *max = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
                PlayerByID *movePlayerID = new PlayerByID(max->m_info->m_ID, max->m_info->m_strength,
                                                        max->m_info->m_sport, max->m_info->m_playerCountry);
                max->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionTeamGen = max->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = max->m_info->m_StrengthVersionThird;
                movePlayerID->m_playerInIDGen = max->m_info->m_playerInIDGen;
                PlayerByStrength *targetSTR = max->m_info->m_StrengthVersionThird;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                 targetSTR->m_sport, targetSTR->m_playerCountry);
                team->m_firstThirdID->removeNode(max->m_info);
                team->m_firstThirdSTR->removeNode(movePlayerID->m_StrengthVersionThird);
                team->m_secondThirdID->insertNode(movePlayerID);
                team->m_secondThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                movePlayerID->m_currentThird = 2;
            }
            else if(team->m_firstThirdID->m_treeSize > team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize > team->m_lastThirdID->m_treeSize)
            {
                Node<PlayerByID> *max = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
                PlayerByID *movePlayerID = new PlayerByID(max->m_info->m_ID, max->m_info->m_strength,
                                                          max->m_info->m_sport, max->m_info->m_playerCountry);
                max->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionTeamGen = max->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = max->m_info->m_StrengthVersionThird;
                movePlayerID->m_playerInIDGen = max->m_info->m_playerInIDGen;
                PlayerByStrength *targetSTR = max->m_info->m_StrengthVersionThird;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                team->m_firstThirdID->removeNode(max->m_info);
                team->m_firstThirdSTR->removeNode(movePlayerID->m_StrengthVersionThird);
                team->m_secondThirdID->insertNode(movePlayerID);
                team->m_secondThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                movePlayerID->m_currentThird = 2;
                Node<PlayerByID> *max1 = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
                PlayerByStrength *targetSTR1 = max1->m_info->m_StrengthVersionThird;
                PlayerByID *movePlayerID1 = new PlayerByID(max1->m_info->m_ID, max1->m_info->m_strength,
                                                          max1->m_info->m_sport, max1->m_info->m_playerCountry);
                max1->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = movePlayerID1;
                PlayerByStrength *movePlayerSTR1 = new PlayerByStrength(targetSTR1->m_ID, targetSTR1->m_strength,
                                                                       targetSTR1->m_sport, targetSTR1->m_playerCountry);
                movePlayerID1->m_StrengthVersionTeamGen = max1->m_info->m_StrengthVersionTeamGen;
                movePlayerID1->m_StrengthVersionThird = movePlayerSTR1;
                movePlayerID1->m_playerInIDGen = max1->m_info->m_playerInIDGen;
                movePlayerSTR1->m_playerInIDThird = movePlayerID1;
                team->m_secondThirdID->removeNode(max1->m_info);
                team->m_secondThirdSTR->removeNode(targetSTR1);
                team->m_lastThirdID->insertNode(movePlayerID1);
                team->m_lastThirdSTR->insertNode(movePlayerSTR1);
                movePlayerID1->m_currentThird = 3;
            }
        } else if (*playerID < team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root)->m_info)
        {
            team->m_secondThirdID->insertNode(playerID);
            team->m_secondThirdSTR->insertNode(playerSTR);
            playerID->m_currentThird = 2;
            if (team->m_firstThirdID->m_treeSize == team->m_lastThirdID->m_treeSize && team->m_secondThirdID->m_treeSize - team->m_firstThirdID->m_treeSize == 1)
            {
                Node<PlayerByID> *min = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root);
                PlayerByStrength *targetSTR = min->m_info->m_StrengthVersionThird;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                PlayerByID *movePlayerID = new PlayerByID(min->m_info->m_ID, min->m_info->m_strength,
                                                        min->m_info->m_sport, min->m_info->m_playerCountry);
                min->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerID->m_StrengthVersionTeamGen = min->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_playerInIDGen = min->m_info->m_playerInIDGen;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                team->m_secondThirdID->removeNode(min->m_info);
                team->m_secondThirdSTR->removeNode(targetSTR);
                team->m_firstThirdID->insertNode(movePlayerID);
                team->m_firstThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_currentThird = 1;
            }
            else if(team->m_firstThirdID->m_treeSize > team->m_lastThirdID->m_treeSize && team->m_secondThirdID->m_treeSize > team->m_firstThirdID->m_treeSize)
            {
                Node<PlayerByID> *max = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
                PlayerByStrength *targetSTR = max->m_info->m_StrengthVersionThird;
                PlayerByID *movePlayerID = new PlayerByID(max->m_info->m_ID, max->m_info->m_strength,
                                                        max->m_info->m_sport, max->m_info->m_playerCountry);
                max->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = movePlayerID;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                movePlayerID->m_StrengthVersionTeamGen = max->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerID->m_playerInIDGen = max->m_info->m_playerInIDGen;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                team->m_secondThirdID->removeNode(max->m_info);
                team->m_secondThirdSTR->removeNode(targetSTR);
                team->m_lastThirdID->insertNode(movePlayerID);
                team->m_lastThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_currentThird = 3;
            }
        } else
        {
            team->m_lastThirdID->insertNode((playerID));
            team->m_lastThirdSTR->insertNode(playerSTR);
            playerID->m_currentThird = 3;
            if (team->m_lastThirdID->m_treeSize - team->m_secondThirdID->m_treeSize == 1)
            {
                Node<PlayerByID> *min = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root);
                PlayerByStrength *targetSTR = min->m_info->m_StrengthVersionThird;
                PlayerByID *movePlayerID = new PlayerByID(min->m_info->m_ID, min->m_info->m_strength,
                                                        min->m_info->m_sport, min->m_info->m_playerCountry);
                min->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID;
                movePlayerID->m_StrengthVersionTeamGen = min->m_info->m_StrengthVersionTeamGen;
                movePlayerID->m_playerInIDGen = min->m_info->m_playerInIDGen;
                PlayerByStrength *movePlayerSTR = new PlayerByStrength(targetSTR->m_ID, targetSTR->m_strength,
                                                                       targetSTR->m_sport, targetSTR->m_playerCountry);
                movePlayerID->m_StrengthVersionThird = movePlayerSTR;
                movePlayerSTR->m_playerInIDThird = movePlayerID;
                team->m_lastThirdID->removeNode(min->m_info);
                team->m_lastThirdSTR->removeNode(targetSTR);
                team->m_secondThirdID->insertNode(movePlayerID);
                team->m_secondThirdSTR->insertNode(movePlayerSTR);
                movePlayerID->m_currentThird = 2;
                if (team->m_secondThirdID->m_treeSize - team->m_firstThirdID->m_treeSize == 1)
                {
                    Node<PlayerByID> *min2 = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root);
                    PlayerByStrength *targetSTR2 = min2->m_info->m_StrengthVersionThird;
                    PlayerByID *movePlayerID2 = new PlayerByID(min2->m_info->m_ID, min2->m_info->m_strength,
                                                             min2->m_info->m_sport, min2->m_info->m_playerCountry);
                    min2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird=movePlayerID2;
                    movePlayerID2->m_StrengthVersionTeamGen = min2->m_info->m_StrengthVersionTeamGen;
                    movePlayerID2->m_playerInIDGen = min2->m_info->m_playerInIDGen;
                    PlayerByStrength *movePlayerSTR2 = new PlayerByStrength(targetSTR2->m_ID, targetSTR2->m_strength,
                                                                           targetSTR2->m_sport, targetSTR2->m_playerCountry);
                    movePlayerID2->m_StrengthVersionThird = movePlayerSTR2;
                    movePlayerSTR2->m_playerInIDThird = movePlayerID2;
                    team->m_secondThirdID->removeNode(min2->m_info);
                    team->m_secondThirdSTR->removeNode(targetSTR2);
                    team->m_firstThirdID->insertNode(movePlayerID2);
                    team->m_firstThirdSTR->insertNode(movePlayerSTR2);
                    movePlayerID2->m_currentThird = 1;
                }
            }
        }
    } catch( std::bad_alloc &)
    {
        throw;
    }
}

static void removePlayer(Team *team, PlayerByStrength *playerSTRGen) //input: player from general strength tree of team
{
    PlayerByStrength playerSTRCopy(playerSTRGen->m_ID, playerSTRGen->m_strength, playerSTRGen->m_sport, playerSTRGen->m_playerCountry);
    PlayerByID playerIDCopy(playerSTRGen->m_ID, playerSTRGen->m_strength, playerSTRGen->m_sport, playerSTRGen->m_playerCountry);
    int third = playerSTRGen->m_playerInIDThird->m_currentThird;
    team->m_playersBySTR->removeNode(&playerSTRCopy);
    if(third == 1)
    {
        if(team->m_firstThirdID->m_treeSize > team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
        {
            team->m_firstThirdID->removeNode(&playerIDCopy);
            team->m_firstThirdSTR->removeNode(&playerSTRCopy);
        }
        else if(team->m_firstThirdID->m_treeSize == team->m_secondThirdID->m_treeSize) //&& m_secondThirdID->m_treeSize > m_lastThirdID->m_treeSize)
        {
            team->m_firstThirdID->removeNode(&playerIDCopy);
            team->m_firstThirdSTR->removeNode(&playerSTRCopy);
            Node<PlayerByID> *min2 = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root);
            PlayerByID *min2Copy = new PlayerByID(min2->m_info->m_ID, min2->m_info->m_strength, min2->m_info->m_sport, min2->m_info->m_playerCountry);
            PlayerByStrength* min2CopySTR = new PlayerByStrength(min2->m_info->m_ID, min2->m_info->m_StrengthVersionThird->m_strength, min2->m_info->m_sport, min2->m_info->m_playerCountry);
            min2Copy->m_StrengthVersionTeamGen = min2->m_info->m_StrengthVersionTeamGen;
            min2Copy->m_StrengthVersionThird = min2CopySTR;
            min2Copy->m_playerInIDGen = min2->m_info->m_playerInIDGen;
            min2Copy->m_currentThird = 1;
            min2CopySTR->m_playerInIDThird = min2Copy;
            min2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min2Copy;
            team->m_secondThirdID->removeNode(min2->m_info);
            team->m_firstThirdID->insertNode(min2Copy);
            team->m_secondThirdSTR->removeNode(min2CopySTR);
            team->m_firstThirdSTR->insertNode(min2CopySTR);
            //move 2->1
            if(team->m_lastThirdID->m_treeSize > team->m_secondThirdID->m_treeSize) //TODO > is after removal ######
            {
                Node<PlayerByID> *min3 = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root);
                PlayerByID *min3Copy = new PlayerByID(min3->m_info->m_ID, min3->m_info->m_strength, min3->m_info->m_sport, min3->m_info->m_playerCountry);
                PlayerByStrength* min3CopySTR = new PlayerByStrength(min3->m_info->m_ID, min3->m_info->m_StrengthVersionThird->m_strength, min3->m_info->m_sport, min3->m_info->m_playerCountry);
                min3Copy->m_StrengthVersionTeamGen = min3->m_info->m_StrengthVersionTeamGen;
                min3Copy->m_StrengthVersionThird = min3CopySTR;
                min3Copy->m_playerInIDGen = min3->m_info->m_playerInIDGen;
                min3Copy->m_currentThird = 2;
                min3CopySTR->m_playerInIDThird = min3Copy;
                min3->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min3Copy;
                team->m_lastThirdID->removeNode(min3->m_info);
                team->m_secondThirdID->insertNode(min3Copy);
                team->m_lastThirdSTR->removeNode(min3CopySTR);
                team->m_secondThirdSTR->insertNode(min3CopySTR);
            //move 3->2
            }
        }
    }
    else if(third == 2)
    {
        if(team->m_firstThirdID->m_treeSize == team->m_secondThirdID->m_treeSize && team->m_firstThirdID->m_treeSize > team->m_lastThirdID->m_treeSize)
        {
            team->m_secondThirdID->removeNode(&playerIDCopy);
            team->m_secondThirdSTR->removeNode(&playerSTRCopy);
            //remove 2
        }
        else if(team->m_firstThirdID->m_treeSize > team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
        {
            team->m_secondThirdID->removeNode(&playerIDCopy);
            team->m_secondThirdSTR->removeNode(&playerSTRCopy);
            //remove 2
            Node<PlayerByID> *max1 = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
            PlayerByID *max1Copy = new PlayerByID(max1->m_info->m_ID, max1->m_info->m_strength, max1->m_info->m_sport, max1->m_info->m_playerCountry);
            PlayerByStrength* max1CopySTR = new PlayerByStrength(max1->m_info->m_ID, max1->m_info->m_StrengthVersionThird->m_strength, max1->m_info->m_sport, max1->m_info->m_playerCountry);
            max1Copy->m_StrengthVersionTeamGen = max1->m_info->m_StrengthVersionTeamGen;
            max1Copy->m_StrengthVersionThird = max1CopySTR;
            max1Copy->m_playerInIDGen = max1->m_info->m_playerInIDGen;
            max1Copy->m_currentThird = 2;
            max1CopySTR->m_playerInIDThird = max1Copy;
            max1->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max1Copy;
            team->m_firstThirdID->removeNode(max1->m_info);
            team->m_secondThirdID->insertNode(max1Copy);
            team->m_firstThirdSTR->removeNode(max1CopySTR);
            team->m_secondThirdSTR->insertNode(max1CopySTR);
            //1->2
        }
        else if(team->m_firstThirdID->m_treeSize == team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
        {
            team->m_secondThirdID->removeNode(&playerIDCopy);
            team->m_secondThirdSTR->removeNode(&playerSTRCopy);
            //remove 2
            Node<PlayerByID> *min3 = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root);
            PlayerByID *min3Copy = new PlayerByID(min3->m_info->m_ID, min3->m_info->m_strength, min3->m_info->m_sport, min3->m_info->m_playerCountry);
            PlayerByStrength* min3CopySTR = new PlayerByStrength(min3->m_info->m_ID, min3->m_info->m_StrengthVersionThird->m_strength, min3->m_info->m_sport, min3->m_info->m_playerCountry);
            min3Copy->m_StrengthVersionTeamGen = min3->m_info->m_StrengthVersionTeamGen;
            min3Copy->m_StrengthVersionThird = min3CopySTR;
            min3Copy->m_playerInIDGen = min3->m_info->m_playerInIDGen;
            min3Copy->m_currentThird = 2;
            min3CopySTR->m_playerInIDThird = min3Copy;
            min3->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min3Copy;
            team->m_lastThirdID->removeNode(min3->m_info);
            team->m_secondThirdID->insertNode(min3Copy);
            team->m_lastThirdSTR->removeNode(min3CopySTR);
            team->m_secondThirdSTR->insertNode(min3CopySTR);
            //3->2
        }
    }
    else if(third == 3)
    {
        if(team->m_firstThirdID->m_treeSize == team->m_secondThirdID->m_treeSize && team->m_firstThirdID->m_treeSize > team->m_lastThirdID->m_treeSize)
        {
            team->m_lastThirdID->removeNode(&playerIDCopy);
            team->m_lastThirdSTR->removeNode(&playerSTRCopy);
            //remove 3
            Node<PlayerByID> *max2 = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
            PlayerByID *max2Copy = new PlayerByID(max2->m_info->m_ID, max2->m_info->m_strength, max2->m_info->m_sport, max2->m_info->m_playerCountry);
            PlayerByStrength* max2CopySTR = new PlayerByStrength(max2->m_info->m_ID, max2->m_info->m_StrengthVersionThird->m_strength, max2->m_info->m_sport, max2->m_info->m_playerCountry);
            max2Copy->m_StrengthVersionTeamGen = max2->m_info->m_StrengthVersionTeamGen;
            max2Copy->m_StrengthVersionThird = max2CopySTR;
            max2Copy->m_playerInIDGen = max2->m_info->m_playerInIDGen;
            max2Copy->m_currentThird = 3;
            max2CopySTR->m_playerInIDThird = max2Copy;
            max2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max2Copy;
            team->m_secondThirdID->removeNode(max2->m_info);
            team->m_lastThirdID->insertNode(max2Copy);
            team->m_secondThirdSTR->removeNode(max2CopySTR);
            team->m_lastThirdSTR->insertNode(max2CopySTR);
            // 2->3
        }
        else if(team->m_firstThirdID->m_treeSize > team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
        {
            team->m_lastThirdID->removeNode(&playerIDCopy);
            team->m_lastThirdSTR->removeNode(&playerSTRCopy);
            //remove 3
            Node<PlayerByID> *max2 = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
            PlayerByID *max2Copy = new PlayerByID(max2->m_info->m_ID, max2->m_info->m_strength, max2->m_info->m_sport, max2->m_info->m_playerCountry);
            PlayerByStrength* max2CopySTR = new PlayerByStrength(max2->m_info->m_ID, max2->m_info->m_StrengthVersionThird->m_strength, max2->m_info->m_sport, max2->m_info->m_playerCountry);
            max2Copy->m_StrengthVersionTeamGen = max2->m_info->m_StrengthVersionTeamGen;
            max2Copy->m_StrengthVersionThird = max2CopySTR;
            max2Copy->m_playerInIDGen = max2->m_info->m_playerInIDGen;
            max2Copy->m_currentThird = 3;
            max2CopySTR->m_playerInIDThird = max2Copy;
            max2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max2Copy;
            team->m_secondThirdID->removeNode(max2->m_info);
            team->m_lastThirdID->insertNode(max2Copy);
            team->m_secondThirdSTR->removeNode(max2CopySTR);
            team->m_lastThirdSTR->insertNode(max2CopySTR);
            // 2->3
            Node<PlayerByID> *max1 = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
            PlayerByID *max1Copy = new PlayerByID(max1->m_info->m_ID, max1->m_info->m_strength, max1->m_info->m_sport, max1->m_info->m_playerCountry);
            PlayerByStrength* max1CopySTR = new PlayerByStrength(max1->m_info->m_ID, max1->m_info->m_StrengthVersionThird->m_strength, max1->m_info->m_sport, max1->m_info->m_playerCountry);
            max1Copy->m_StrengthVersionTeamGen = max1->m_info->m_StrengthVersionTeamGen;
            max1Copy->m_StrengthVersionThird = max1CopySTR;
            max1Copy->m_playerInIDGen = max1->m_info->m_playerInIDGen;
            max1Copy->m_currentThird = 2;
            max1CopySTR->m_playerInIDThird = max1Copy;
            max1->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max1Copy;
            team->m_firstThirdID->removeNode(max1->m_info);
            team->m_secondThirdID->insertNode(max1Copy);
            team->m_firstThirdSTR->removeNode(max1CopySTR);
            team->m_secondThirdSTR->insertNode(max1CopySTR);
            //1->2
        }
        else if(team->m_firstThirdID->m_treeSize == team->m_secondThirdID->m_treeSize && team->m_secondThirdID->m_treeSize == team->m_lastThirdID->m_treeSize)
        {
            team->m_lastThirdID->removeNode(&playerIDCopy);
            team->m_lastThirdSTR->removeNode(&playerSTRCopy);
            //remove 3
        }
    }
}

static void updateMinMax(Team *team)
{
    //m_firstThirdMax = m_firstThirdSTR->maxNode(m_firstThirdSTR->m_root)->m_info;
    //m_secondThirdMax = m_secondThirdSTR->maxNode(m_secondThirdSTR->m_root)->m_info;
    //m_lastThirdMax = m_lastThirdSTR->maxNode(m_lastThirdSTR->m_root)->m_info;
    if(team->m_firstThirdSTR->m_root != nullptr)
    {
        Node<PlayerByID> *minNode = team->m_firstThirdID->minNode(team->m_firstThirdID->m_root);
        team->m_firstThirdMin1STR = team->m_firstThirdSTR->minNode(team->m_firstThirdSTR->m_root)->m_info;
        //team->m_firstThird1stMinID = team->m_firstThirdID->minNode(team->m_firstThirdID->m_root)->m_info;
        PlayerByID *min1Copy = new PlayerByID(minNode->m_info->m_ID, minNode->m_info->m_strength, minNode->m_info->m_sport, minNode->m_info->m_playerCountry);
        team->m_firstThird1stMinID = min1Copy;
        min1Copy->m_StrengthVersionTeamGen = minNode->m_info->m_StrengthVersionTeamGen;
        min1Copy->m_StrengthVersionThird = minNode->m_info->m_StrengthVersionThird;
        min1Copy->m_currentThird = minNode->m_info->m_currentThird;
        min1Copy->m_playerInIDGen = minNode->m_info->m_playerInIDGen;
        minNode->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min1Copy;
        minNode->m_info->m_StrengthVersionThird->m_playerInIDThird = min1Copy;
        if(team->m_firstThirdMax1ID == minNode->m_info)
        {
            team->m_firstThirdMax1ID = min1Copy;
        }
        if(team->m_firstThirdMax2ID == minNode->m_info)
        {
            team->m_firstThirdMax2ID = min1Copy;
        }
        if(team->m_firstThird1stMinID == minNode->m_info)
        {
            team->m_firstThird1stMinID = min1Copy;
        }
        if(team->m_firstThird2ndMinID == minNode->m_info)
        {
            team->m_firstThird2ndMinID = min1Copy;
        }
        if(team->m_firstThird3rdMinID == minNode->m_info)
        {
            team->m_firstThird3rdMinID = min1Copy;
        }
        team->m_firstThirdID->removeNode(minNode->m_info);
        if(team->m_firstThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *minNode2 = team->m_firstThirdID->minNode(team->m_firstThirdID->m_root);
            team->m_firstThird2ndMinID = minNode2->m_info;
            /*
            PlayerByID *min2Copy = new PlayerByID(minNode2->m_info->m_ID,minNode2->m_info->m_strength, minNode2->m_info->m_sport,minNode2->m_info->m_playerCountry);
            min2Copy->m_StrengthVersionTeamGen = minNode2->m_info->m_StrengthVersionTeamGen;
            min2Copy->m_StrengthVersionThird = minNode2->m_info->m_StrengthVersionThird;
            min2Copy->m_currentThird = minNode2->m_info->m_currentThird;
            minNode2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min2Copy;
            minNode2->m_info->m_StrengthVersionThird->m_playerInIDThird = min2Copy;
            m_firstThirdID->removeNode(minNode2->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdSTR->m_treeSize > 0)
            {
                m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            }
            //m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            m_firstThirdSTR->insertNode(min2Copy);*/
        }
        else
        {
            team->m_firstThird2ndMinID = nullptr;
        }
        team->m_firstThirdID->insertNode(min1Copy);
    }
    else
    {
        team->m_firstThird1stMinID = nullptr;
        team->m_firstThird2ndMinID = nullptr;
    }
    if(team->m_secondThirdID->m_root != nullptr)
    {
        Node<PlayerByID> *minNode2 = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root);
        team->m_secondThirdMin1STR = team->m_secondThirdSTR->minNode(team->m_secondThirdSTR->m_root)->m_info;
        //team->m_secondThird1stMinID = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root)->m_info;
        PlayerByID *min1aCopy = new PlayerByID(minNode2->m_info->m_ID, minNode2->m_info->m_strength, minNode2->m_info->m_sport, minNode2->m_info->m_playerCountry);
        team->m_secondThird1stMinID = min1aCopy;
        min1aCopy->m_StrengthVersionTeamGen = minNode2->m_info->m_StrengthVersionTeamGen;
        min1aCopy->m_StrengthVersionThird = minNode2->m_info->m_StrengthVersionThird;
        min1aCopy->m_currentThird = minNode2->m_info->m_currentThird;
        min1aCopy->m_playerInIDGen = minNode2->m_info->m_playerInIDGen;
        minNode2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min1aCopy;
        minNode2->m_info->m_StrengthVersionThird->m_playerInIDThird = min1aCopy;
        if(team->m_secondThirdMax1ID == minNode2->m_info)
        {
            team->m_secondThirdMax1ID = min1aCopy;
        }
        if(team->m_secondThirdMax2ID == minNode2->m_info)
        {
            team->m_secondThirdMax2ID = min1aCopy;
        }
        if(team->m_secondThird1stMinID == minNode2->m_info)
        {
            team->m_secondThird1stMinID = min1aCopy;
        }
        if(team->m_secondThird2ndMinID == minNode2->m_info)
        {
            team->m_secondThird2ndMinID = min1aCopy;
        }
        if(team->m_secondThird3rdMinID == minNode2->m_info)
        {
            team->m_secondThird3rdMinID = min1aCopy;
        }
        team->m_secondThirdID->removeNode(minNode2->m_info);
        if(team->m_secondThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *minNode2a = team->m_secondThirdID->minNode(team->m_secondThirdID->m_root);
            team->m_secondThird2ndMinID = minNode2a->m_info;
            /*
            PlayerByStrength *min2Copy = new PlayerByStrength(minNode2->m_info->m_ID,minNode2->m_info->m_strength, minNode2->m_info->m_sport,minNode2->m_info->m_playerCountry);
            min2Copy->m_playerInIDThird = minNode2->m_info->m_playerInIDThird;
            minNode2->m_info->m_playerInIDThird->m_StrengthVersionThird = min2Copy;
            m_secondThirdSTR->removeNode(minNode->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdSTR->m_treeSize > 0)
            {
                m_secondThird3rdMin = m_secondThirdSTR->minNode(m_secondThirdSTR->m_root)->m_info;
            }

            m_secondThirdSTR->insertNode(min2Copy);             */
        }
        else
        {
            team->m_secondThird2ndMinID = nullptr;
        }
        team->m_secondThirdID->insertNode(min1aCopy);
    }
    else
    {
        team->m_secondThird1stMinID = nullptr;
    }

    if(team->m_lastThirdID->m_root != nullptr)
    {
        Node<PlayerByID> *minNode3 = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root);
        team->m_lastThirdMin1STR = team->m_lastThirdSTR->minNode(team->m_lastThirdSTR->m_root)->m_info;
        //team->m_lastThird1stMinID = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root)->m_info;
        PlayerByID *min1bCopy = new PlayerByID(minNode3->m_info->m_ID, minNode3->m_info->m_strength, minNode3->m_info->m_sport, minNode3->m_info->m_playerCountry);
        team->m_lastThird1stMinID = min1bCopy;
        min1bCopy->m_StrengthVersionTeamGen = minNode3->m_info->m_StrengthVersionTeamGen;
        min1bCopy->m_StrengthVersionThird = minNode3->m_info->m_StrengthVersionThird;
        min1bCopy->m_currentThird = minNode3->m_info->m_currentThird;
        min1bCopy->m_playerInIDGen = minNode3->m_info->m_playerInIDGen;
        minNode3->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = min1bCopy;
        minNode3->m_info->m_StrengthVersionThird->m_playerInIDThird = min1bCopy;
        if(team->m_lastThirdMax1ID == minNode3->m_info)
        {
            team->m_lastThirdMax1ID = min1bCopy;
        }
        if(team->m_lastThirdMax2ID == minNode3->m_info)
        {
            team->m_lastThirdMax2ID = min1bCopy;
        }
        if(team->m_lastThird1stMinID == minNode3->m_info)
        {
            team->m_lastThird1stMinID = min1bCopy;
        }
        if(team->m_lastThird2ndMinID == minNode3->m_info)
        {
            team->m_lastThird2ndMinID = min1bCopy;
        }
        if(team->m_lastThird3rdMinID == minNode3->m_info)
        {
            team->m_lastThird3rdMinID = min1bCopy;
        }
        team->m_lastThirdID->removeNode(minNode3->m_info);
        if(team->m_lastThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *minNode4 = team->m_lastThirdID->minNode(team->m_lastThirdID->m_root);
            team->m_lastThird2ndMinID = minNode4->m_info;
            /*
            PlayerByStrength *min2Copy = new PlayerByStrength(minNode2->m_info->m_ID,minNode2->m_info->m_strength, minNode2->m_info->m_sport,minNode2->m_info->m_playerCountry);
            min2Copy->m_playerInIDThird = minNode2->m_info->m_playerInIDThird;
            minNode2->m_info->m_playerInIDThird->m_StrengthVersionThird = min2Copy;
            m_lastThirdSTR->removeNode(minNode->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdSTR->m_treeSize > 0)
            {
                m_lastThird3rdMin = m_lastThirdSTR->minNode(m_lastThirdSTR->m_root)->m_info;
            }

            m_lastThirdSTR->insertNode(min2Copy);*/
        }
        else
        {
            team->m_lastThird2ndMinID = nullptr;
        }
        team->m_lastThirdID->insertNode(min1bCopy);
    }
    else
    {
        team->m_lastThird1stMinID = nullptr;
        team->m_lastThird2ndMinID = nullptr;
    }

    if(team->m_firstThirdSTR->m_root != nullptr)
    {
        Node<PlayerByStrength> *maxNode = team->m_firstThirdSTR->maxNode(team->m_firstThirdSTR->m_root);
        //team->m_firstThirdMax1STR = team->m_firstThirdSTR->maxNode(team->m_firstThirdSTR->m_root)->m_info;
        PlayerByStrength *max1Copy = new PlayerByStrength(maxNode->m_info->m_ID, maxNode->m_info->m_strength, maxNode->m_info->m_sport, maxNode->m_info->m_playerCountry);
        team->m_firstThirdMax1STR = max1Copy;
        max1Copy->m_playerInIDThird = maxNode->m_info->m_playerInIDThird;
        maxNode->m_info->m_playerInIDThird->m_StrengthVersionThird = max1Copy;
        if(team->m_firstThirdMax1STR == maxNode->m_info)
        {
            team->m_firstThirdMax1STR = max1Copy;
        }
        if(team->m_firstThirdMax2STR == maxNode->m_info)
        {
            team->m_firstThirdMax2STR = max1Copy;
        }
        if(team->m_firstThirdMax3STR == maxNode->m_info)
        {
            team->m_firstThirdMax3STR = max1Copy;
        }
        if(team->m_firstThirdMin1STR == maxNode->m_info)
        {
            team->m_firstThirdMin1STR = max1Copy;
        }
        team->m_firstThirdSTR->removeNode(maxNode->m_info);
        if(team->m_firstThirdSTR->m_root != nullptr)
        {
            Node<PlayerByStrength> *maxNode2 = team->m_firstThirdSTR->maxNode(team->m_firstThirdSTR->m_root);
            //team->m_firstThirdMax2STR = maxNode2->m_info;
            PlayerByStrength *max2Copy = new PlayerByStrength(maxNode2->m_info->m_ID,maxNode2->m_info->m_strength, maxNode2->m_info->m_sport,maxNode2->m_info->m_playerCountry);
            team->m_firstThirdMax2STR = max2Copy;
            max2Copy->m_playerInIDThird = maxNode2->m_info->m_playerInIDThird;
            maxNode2->m_info->m_playerInIDThird->m_StrengthVersionThird = max2Copy;
            if(team->m_firstThirdMax1STR == maxNode2->m_info)
            {
                team->m_firstThirdMax1STR = max2Copy;
            }
            if(team->m_firstThirdMax2STR == maxNode2->m_info)
            {
                team->m_firstThirdMax2STR = max2Copy;
            }
            if(team->m_firstThirdMax3STR == maxNode2->m_info)
            {
                team->m_firstThirdMax3STR = max2Copy;
            }
            if(team->m_firstThirdMin1STR == maxNode2->m_info)
            {
                team->m_firstThirdMin1STR = max2Copy;
            }
            team->m_firstThirdSTR->removeNode(maxNode2->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(team->m_firstThirdSTR->m_root != nullptr)
            {
                team->m_firstThirdMax3STR = team->m_firstThirdSTR->maxNode(team->m_firstThirdSTR->m_root)->m_info;
            }
            else
            {
                team->m_firstThirdMax3STR = nullptr;
            }
            //m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            team->m_firstThirdSTR->insertNode(max2Copy);
        }
        else
        {
            team->m_firstThirdMax2STR = nullptr;
            team->m_firstThirdMax3STR = nullptr;
        }
        team->m_firstThirdSTR->insertNode(max1Copy);
    }
    else
    {
        team->m_firstThirdMax1STR = nullptr;
        team->m_firstThirdMax2STR = nullptr;
        team->m_firstThirdMax3STR = nullptr;
    }
    if(team->m_secondThirdSTR->m_root != nullptr)
    {
        Node<PlayerByStrength> *maxNode3 = team->m_secondThirdSTR->maxNode(team->m_secondThirdSTR->m_root);
        //team->m_secondThirdMax1STR = team->m_secondThirdSTR->maxNode(team->m_secondThirdSTR->m_root)->m_info;
        PlayerByStrength *max1aCopy = new PlayerByStrength(maxNode3->m_info->m_ID, maxNode3->m_info->m_strength, maxNode3->m_info->m_sport, maxNode3->m_info->m_playerCountry);
        team->m_secondThirdMax1STR = max1aCopy;
        max1aCopy->m_playerInIDThird = maxNode3->m_info->m_playerInIDThird;
        maxNode3->m_info->m_playerInIDThird->m_StrengthVersionThird = max1aCopy;
        if(team->m_secondThirdMax1STR == maxNode3->m_info)
        {
            team->m_secondThirdMax1STR = max1aCopy;
        }
        if(team->m_secondThirdMax2STR == maxNode3->m_info)
        {
            team->m_secondThirdMax2STR = max1aCopy;
        }
        if(team->m_secondThirdMax3STR == maxNode3->m_info)
        {
            team->m_secondThirdMax3STR = max1aCopy;
        }
        if(team->m_secondThirdMin1STR == maxNode3->m_info)
        {
            team->m_secondThirdMin1STR = max1aCopy;
        }
        team->m_secondThirdSTR->removeNode(maxNode3->m_info);
        if(team->m_secondThirdSTR->m_root != nullptr)
        {
            Node<PlayerByStrength> *maxNode4 = team->m_secondThirdSTR->maxNode(team->m_secondThirdSTR->m_root);
            //team->m_secondThirdMax2STR = maxNode2->m_info;
            PlayerByStrength *max2aCopy = new PlayerByStrength(maxNode4->m_info->m_ID,maxNode4->m_info->m_strength, maxNode4->m_info->m_sport,maxNode4->m_info->m_playerCountry);
            team->m_secondThirdMax2STR = max2aCopy;
            max2aCopy->m_playerInIDThird = maxNode4->m_info->m_playerInIDThird;
            maxNode4->m_info->m_playerInIDThird->m_StrengthVersionThird = max2aCopy;
            if(team->m_secondThirdMax1STR == maxNode4->m_info)
            {
                team->m_secondThirdMax1STR = max2aCopy;
            }
            if(team->m_secondThirdMax2STR == maxNode4->m_info)
            {
                team->m_secondThirdMax2STR = max2aCopy;
            }
            if(team->m_secondThirdMax3STR == maxNode4->m_info)
            {
                team->m_secondThirdMax3STR = max2aCopy;
            }
            if(team->m_secondThirdMin1STR == maxNode4->m_info)
            {
                team->m_secondThirdMin1STR = max2aCopy;
            }
            team->m_secondThirdSTR->removeNode(maxNode4->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(team->m_secondThirdSTR->m_root != nullptr)
            {
                team->m_secondThirdMax3STR = team->m_secondThirdSTR->maxNode(team->m_secondThirdSTR->m_root)->m_info;
            }
            else
            {
                team->m_secondThirdMax3STR = nullptr;
            }

            team->m_secondThirdSTR->insertNode(max2aCopy);
        }
        else
        {
            team->m_secondThirdMax2STR = nullptr;
            team->m_secondThirdMax3STR = nullptr;
        }
        team->m_secondThirdSTR->insertNode(max1aCopy);
    }
    else
    {
        team->m_secondThirdMax1STR = nullptr;
        team->m_secondThirdMax2STR = nullptr;
        team->m_secondThirdMax3STR = nullptr;
    }
    if(team->m_lastThirdSTR->m_root != nullptr)
    {
        Node<PlayerByStrength> *maxNode5 = team->m_lastThirdSTR->maxNode(team->m_lastThirdSTR->m_root);
        //team->m_lastThirdMax1STR = team->m_lastThirdSTR->maxNode(team->m_lastThirdSTR->m_root)->m_info;
        PlayerByStrength *max1bCopy = new PlayerByStrength(maxNode5->m_info->m_ID, maxNode5->m_info->m_strength, maxNode5->m_info->m_sport, maxNode5->m_info->m_playerCountry);
        team->m_lastThirdMax1STR = max1bCopy;
        max1bCopy->m_playerInIDThird = maxNode5->m_info->m_playerInIDThird;
        maxNode5->m_info->m_playerInIDThird->m_StrengthVersionThird = max1bCopy;
        if(team->m_lastThirdMax1STR == maxNode5->m_info)
        {
            team->m_lastThirdMax1STR = max1bCopy;
        }
        if(team->m_lastThirdMax2STR == maxNode5->m_info)
        {
            team->m_lastThirdMax2STR = max1bCopy;
        }
        if(team->m_lastThirdMax3STR == maxNode5->m_info)
        {
            team->m_lastThirdMax3STR = max1bCopy;
        }
        if(team->m_lastThirdMin1STR == maxNode5->m_info)
        {
            team->m_lastThirdMin1STR = max1bCopy;
        }
        team->m_lastThirdSTR->removeNode(maxNode5->m_info);
        if(team->m_lastThirdSTR->m_root != nullptr)
        {
            Node<PlayerByStrength> *maxNode6 = team->m_lastThirdSTR->maxNode(team->m_lastThirdSTR->m_root);
            //team->m_lastThirdMax2STR = maxNode2->m_info;
            PlayerByStrength *max2bCopy = new PlayerByStrength(maxNode6->m_info->m_ID,maxNode6->m_info->m_strength, maxNode6->m_info->m_sport,maxNode6->m_info->m_playerCountry);
            team->m_lastThirdMax2STR = max2bCopy;
            max2bCopy->m_playerInIDThird = maxNode6->m_info->m_playerInIDThird;
            maxNode6->m_info->m_playerInIDThird->m_StrengthVersionThird = max2bCopy;
            if(team->m_lastThirdMax1STR == maxNode6->m_info)
            {
                team->m_lastThirdMax1STR = max2bCopy;
            }
            if(team->m_lastThirdMax2STR == maxNode6->m_info)
            {
                team->m_lastThirdMax2STR = max2bCopy;
            }
            if(team->m_lastThirdMax3STR == maxNode6->m_info)
            {
                team->m_lastThirdMax3STR = max2bCopy;
            }
            if(team->m_lastThirdMin1STR == maxNode6->m_info)
            {
                team->m_lastThirdMin1STR = max2bCopy;
            }
            team->m_lastThirdSTR->removeNode(maxNode6->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(team->m_lastThirdSTR->m_root != nullptr)
            {
                team->m_lastThirdMax3STR = team->m_lastThirdSTR->maxNode(team->m_lastThirdSTR->m_root)->m_info;
            }
            else
            {
                team->m_lastThirdMax3STR = nullptr;
            }
            team->m_lastThirdSTR->insertNode(max2bCopy);
        }
        else
        {
            team->m_lastThirdMax2STR = nullptr;
            team->m_lastThirdMax3STR = nullptr;
        }
        team->m_lastThirdSTR->insertNode(max1bCopy);
    }
    else
    {
        team->m_lastThirdMax1STR = nullptr;
        team->m_lastThirdMax2STR = nullptr;
        team->m_lastThirdMax3STR = nullptr;
    }

    if(team->m_firstThirdSTR->m_root != nullptr)
    {
        Node<PlayerByID> *maxNode7 = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
        //team->m_firstThirdMax1ID = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root)->m_info;
        PlayerByID *max1cCopy = new PlayerByID(maxNode7->m_info->m_ID, maxNode7->m_info->m_strength, maxNode7->m_info->m_sport, maxNode7->m_info->m_playerCountry);
        team->m_firstThirdMax1ID = max1cCopy;
        max1cCopy->m_StrengthVersionThird = maxNode7->m_info->m_StrengthVersionThird;
        max1cCopy->m_StrengthVersionTeamGen = maxNode7->m_info->m_StrengthVersionTeamGen;
        max1cCopy->m_currentThird = maxNode7->m_info->m_currentThird;
        max1cCopy->m_playerInIDGen = maxNode7->m_info->m_playerInIDGen;
        maxNode7->m_info->m_StrengthVersionThird->m_playerInIDThird = max1cCopy;
        maxNode7->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max1cCopy;
        if(team->m_firstThirdMax1ID == maxNode7->m_info)
        {
            team->m_firstThirdMax1ID = max1cCopy;
        }
        if(team->m_firstThirdMax2ID == maxNode7->m_info)
        {
            team->m_firstThirdMax2ID = max1cCopy;
        }
        if(team->m_firstThird1stMinID == maxNode7->m_info)
        {
            team->m_firstThird1stMinID = max1cCopy;
        }
        if(team->m_firstThird2ndMinID == maxNode7->m_info)
        {
            team->m_firstThird2ndMinID = max1cCopy;
        }
        if(team->m_firstThird3rdMinID == maxNode7->m_info)
        {
            team->m_firstThird3rdMinID = max1cCopy;
        }
        team->m_firstThirdID->removeNode(maxNode7->m_info);
        if(team->m_firstThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *maxNode8 = team->m_firstThirdID->maxNode(team->m_firstThirdID->m_root);
            team->m_firstThirdMax2ID = maxNode8->m_info;
            /*PlayerByID *max2Copy = new PlayerByID(maxNode2->m_info->m_ID,maxNode2->m_info->m_strength, maxNode2->m_info->m_sport,maxNode2->m_info->m_playerCountry);
            max2Copy->m_StrengthVersionThird = maxNode2->m_info->m_StrengthVersionThird;
            max2Copy->m_StrengthVersionTeamGen = maxNode2->m_info->m_StrengthVersionTeamGen;
            maxNode2->m_info->m_StrengthVersionThird->m_playerInIDThird = max2Copy;
            maxNode2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max2Copy;
            m_firstThirdID->removeNode(maxNode->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdID->m_treeSize > 0)
            {
                m_firstThirdMax3ID = m_firstThirdSTR->maxNode(m_firstThirdSTR->m_root)->m_info;
            }
            else
            {
                m_firstThirdMax3STR = nullptr;
            }
            //m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            m_firstThirdSTR->insertNode(max2Copy);*/
        }
        else
        {
            team->m_firstThirdMax2ID = nullptr;
        }
        team->m_firstThirdID->insertNode(max1cCopy);
    }
    else
    {
        team->m_firstThirdMax1ID = nullptr;
        team->m_firstThirdMax2ID = nullptr;
    }
    if(team->m_secondThirdSTR->m_root != nullptr)
    {
        Node<PlayerByID> *maxNode9 = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
        //team->m_secondThirdMax1ID = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root)->m_info;
        PlayerByID *max1dCopy = new PlayerByID(maxNode9->m_info->m_ID, maxNode9->m_info->m_strength, maxNode9->m_info->m_sport, maxNode9->m_info->m_playerCountry);
        team->m_secondThirdMax1ID = max1dCopy;
        max1dCopy->m_StrengthVersionThird = maxNode9->m_info->m_StrengthVersionThird;
        max1dCopy->m_StrengthVersionTeamGen = maxNode9->m_info->m_StrengthVersionTeamGen;
        max1dCopy->m_currentThird = maxNode9->m_info->m_currentThird;
        max1dCopy->m_playerInIDGen = maxNode9->m_info->m_playerInIDGen;
        maxNode9->m_info->m_StrengthVersionThird->m_playerInIDThird = max1dCopy;
        maxNode9->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max1dCopy;
        if(team->m_secondThirdMax1ID == maxNode9->m_info)
        {
            team->m_secondThirdMax1ID = max1dCopy;
        }
        if(team->m_secondThirdMax2ID == maxNode9->m_info)
        {
            team->m_secondThirdMax2ID = max1dCopy;
        }
        if(team->m_secondThird1stMinID == maxNode9->m_info)
        {
            team->m_secondThird1stMinID = max1dCopy;
        }
        if(team->m_secondThird2ndMinID == maxNode9->m_info)
        {
            team->m_secondThird2ndMinID = max1dCopy;
        }
        if(team->m_secondThird3rdMinID == maxNode9->m_info)
        {
            team->m_secondThird3rdMinID = max1dCopy;
        }
        team->m_secondThirdID->removeNode(maxNode9->m_info);
        if(team->m_secondThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *maxNode2d = team->m_secondThirdID->maxNode(team->m_secondThirdID->m_root);
            team->m_secondThirdMax2ID = maxNode2d->m_info;
            /*PlayerByID *max2Copy = new PlayerByID(maxNode2->m_info->m_ID,maxNode2->m_info->m_strength, maxNode2->m_info->m_sport,maxNode2->m_info->m_playerCountry);
            max2Copy->m_StrengthVersionThird = maxNode2->m_info->m_StrengthVersionThird;
            max2Copy->m_StrengthVersionTeamGen = maxNode2->m_info->m_StrengthVersionTeamGen;
            maxNode2->m_info->m_StrengthVersionThird->m_playerInIDThird = max2Copy;
            maxNode2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max2Copy;
            m_firstThirdID->removeNode(maxNode->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdID->m_treeSize > 0)
            {
                m_firstThirdMax3ID = m_firstThirdSTR->maxNode(m_firstThirdSTR->m_root)->m_info;
            }
            else
            {
                m_firstThirdMax3STR = nullptr;
            }
            //m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            m_firstThirdSTR->insertNode(max2Copy);*/
        }
        else
        {
            team->m_secondThirdMax2ID = nullptr;
        }
        team->m_secondThirdID->insertNode(max1dCopy);
    }
    else
    {
        team->m_secondThirdMax1ID = nullptr;
        team->m_secondThirdMax2ID = nullptr;
    }
    if(team->m_lastThirdSTR->m_root != nullptr)
    {
        Node<PlayerByID> *maxNode11 = team->m_lastThirdID->maxNode(team->m_lastThirdID->m_root);
        //team->m_lastThirdMax1ID = team->m_lastThirdID->maxNode(team->m_lastThirdID->m_root)->m_info;
        PlayerByID *max1fCopy = new PlayerByID(maxNode11->m_info->m_ID, maxNode11->m_info->m_strength, maxNode11->m_info->m_sport, maxNode11->m_info->m_playerCountry);
        team->m_lastThirdMax1ID = max1fCopy;
        max1fCopy->m_StrengthVersionThird = maxNode11->m_info->m_StrengthVersionThird;
        max1fCopy->m_StrengthVersionTeamGen = maxNode11->m_info->m_StrengthVersionTeamGen;
        max1fCopy->m_currentThird = maxNode11->m_info->m_currentThird;
        max1fCopy->m_playerInIDGen = maxNode11->m_info->m_playerInIDGen;
        maxNode11->m_info->m_StrengthVersionThird->m_playerInIDThird = max1fCopy;
        maxNode11->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max1fCopy;
        if(team->m_lastThirdMax1ID == maxNode11->m_info)
        {
            team->m_lastThirdMax1ID = max1fCopy;
        }
        if(team->m_lastThirdMax2ID == maxNode11->m_info)
        {
            team->m_lastThirdMax2ID = max1fCopy;
        }
        if(team->m_lastThird1stMinID == maxNode11->m_info)
        {
            team->m_lastThird1stMinID = max1fCopy;
        }
        if(team->m_lastThird2ndMinID == maxNode11->m_info)
        {
            team->m_lastThird2ndMinID = max1fCopy;
        }
        if(team->m_lastThird3rdMinID == maxNode11->m_info)
        {
            team->m_lastThird3rdMinID = max1fCopy;
        }
        team->m_lastThirdID->removeNode(maxNode11->m_info);
        if(team->m_lastThirdID->m_root != nullptr)
        {
            Node<PlayerByID> *maxNode2f = team->m_lastThirdID->maxNode(team->m_lastThirdID->m_root);
            team->m_lastThirdMax2ID = maxNode2f->m_info;
            /*PlayerByID *max2Copy = new PlayerByID(maxNode2->m_info->m_ID,maxNode2->m_info->m_strength, maxNode2->m_info->m_sport,maxNode2->m_info->m_playerCountry);
            max2Copy->m_StrengthVersionThird = maxNode2->m_info->m_StrengthVersionThird;
            max2Copy->m_StrengthVersionTeamGen = maxNode2->m_info->m_StrengthVersionTeamGen;
            maxNode2->m_info->m_StrengthVersionThird->m_playerInIDThird = max2Copy;
            maxNode2->m_info->m_StrengthVersionTeamGen->m_playerInIDThird = max2Copy;
            m_firstThirdID->removeNode(maxNode->m_info);
            //Node<PlayerByStrength> *minNode3 = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root);
            if(m_firstThirdID->m_treeSize > 0)
            {
                m_firstThirdMax3ID = m_firstThirdSTR->maxNode(m_firstThirdSTR->m_root)->m_info;
            }
            else
            {
                m_firstThirdMax3STR = nullptr;
            }
            //m_firstThird3rdMin = m_firstThirdSTR->minNode(m_firstThirdSTR->m_root)->m_info;
            m_firstThirdSTR->insertNode(max2Copy);*/
        }
        else
        {
            team->m_lastThirdMax2ID = nullptr;
        }
        team->m_lastThirdID->insertNode(max1fCopy);
    }
    else
    {
        team->m_lastThirdMax1ID = nullptr;
        team->m_lastThirdMax2ID = nullptr;
    }
}

static void uniteTeamPointers(PlayerByID* playerInIDThird, Team* team1, Team* team2)
{
    if(playerInIDThird->m_playerInIDGen->m_team1 == team2 && playerInIDThird->m_playerInIDGen->m_team2 != team1 && playerInIDThird->m_playerInIDGen->m_team3 != team1)
    {
        playerInIDThird->m_playerInIDGen->m_team1 = team1;
    }
    else if(playerInIDThird->m_playerInIDGen->m_team2 == team2 && playerInIDThird->m_playerInIDGen->m_team1 != team1 && playerInIDThird->m_playerInIDGen->m_team3 != team1)
    {
        playerInIDThird->m_playerInIDGen->m_team2 = team1;
    }
    else if(playerInIDThird->m_playerInIDGen->m_team3 == team2 && playerInIDThird->m_playerInIDGen->m_team1 != team1 && playerInIDThird->m_playerInIDGen->m_team2 != team1)
    {
        playerInIDThird->m_playerInIDGen->m_team3 = team1;
    }
    else if(playerInIDThird->m_playerInIDGen->m_team1 == team2)
    {
        playerInIDThird->m_playerInIDGen->m_team1 = nullptr;
    }
    else if(playerInIDThird->m_playerInIDGen->m_team2 == team2)
    {
        playerInIDThird->m_playerInIDGen->m_team2 = nullptr;
    }
    else if(playerInIDThird->m_playerInIDGen->m_team3 == team2)
    {
        playerInIDThird->m_playerInIDGen->m_team3 = nullptr;
    }
}




#endif //WET_1_TEAM_H
