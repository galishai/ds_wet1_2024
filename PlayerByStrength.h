//
// Created by Gal Ishai on 2/15/24.
//

#ifndef WET_1_PLAYERBYSTRENGTH_H
#define WET_1_PLAYERBYSTRENGTH_H

#include "Player.h"

class PlayerByID;

class PlayerByStrength: public Player
{
public:
    PlayerByID* m_playerInIDThird;
//int node_count;

    PlayerByStrength(int ID, int strength, Sport sport, Country *country) : Player(ID,strength,sport,country)
    {
        //node_count = 1; //###############
        m_playerInIDThird = nullptr;
    }

    explicit PlayerByStrength(PlayerByStrength* other): Player(other)
    {
        m_playerInIDThird = other->m_playerInIDThird;
    }
    bool operator<(Player *other) const override
    {
        if(other == nullptr)
        {
            return false;
        }
        if (m_strength < other->m_strength || (m_strength == other->m_strength && m_ID < other->m_ID))
        {
            return true;
        }
        return false;
    }
};

/*static PlayerByStrength* updateNearestMin(Node<PlayerByStrength> *playerToUpdate, AVLTree<PlayerByStrength> *playerByStrengthThird)
{
    if (playerToUpdate == nullptr)
    {
        return nullptr;
    }

    if (playerToUpdate->m_left != nullptr && playerToUpdate->m_right != nullptr) //if has two sons
    {
        playerToUpdate->m_info->m_greaterOptionForClosest = minNode(playerToUpdate->m_right);
        playerToUpdate->m_info->m_smallerOptionForClosest = maxNode(playerToUpdate->m_left);

    }

    else if ((playerToUpdate->m_left == nullptr && playerToUpdate->m_right != nullptr)) //if only has right son todo check
    {
        playerToUpdate->m_info->m_greaterOptionForClosest = minNode(playerToUpdate->m_right);
        if (*(minNode(playerByStatsTree->m_root)->m_info) == playerToUpdate->m_info)
        {
            playerToUpdate->m_info->m_smallerOptionForClosest = nullptr;
            return;
        }
        if(playerToUpdate->m_parent == nullptr)
        {
            playerToUpdate->m_info->m_smallerOptionForClosest = nullptr;
            return;
        }
        if(playerToUpdate->m_parent->m_left == playerToUpdate)
        {
            Node<PlayerByStats> *ptr = playerToUpdate;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_left == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                playerToUpdate->m_info->m_smallerOptionForClosest = ptr->m_parent;
            } else
            {
                playerToUpdate->m_info->m_smallerOptionForClosest = nullptr;
            }
        }else if (playerToUpdate->m_parent->m_right == playerToUpdate)
        {
            playerToUpdate->m_info->m_smallerOptionForClosest = playerToUpdate->m_parent;
        }

    } else if (playerToUpdate->m_left != nullptr && playerToUpdate->m_right == nullptr) //if only has left son
    {
        playerToUpdate->m_info->m_smallerOptionForClosest = maxNode(playerToUpdate->m_left);

        if (*(maxNode(playerByStatsTree->m_root)->m_info) == playerToUpdate->m_info)
        {
            playerToUpdate->m_info->m_greaterOptionForClosest = nullptr;
            return;
        }
        if(playerToUpdate->m_parent == nullptr)
        {
            playerToUpdate->m_info->m_greaterOptionForClosest = nullptr;
            return;
        }
        if(playerToUpdate->m_parent->m_right == playerToUpdate)
        {
            Node<PlayerByStats> *ptr = playerToUpdate;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_right == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                playerToUpdate->m_info->m_greaterOptionForClosest = ptr->m_parent;
            } else
            {
                playerToUpdate->m_info->m_greaterOptionForClosest = nullptr;
            }
        }else if (playerToUpdate->m_parent->m_left == playerToUpdate)
        {
            playerToUpdate->m_info->m_greaterOptionForClosest = playerToUpdate->m_parent;
        }

    } else //if player is a leaf (no sons)
    {
        if (playerToUpdate->m_parent == nullptr)
        {
            playerToUpdate->m_info->m_smallerOptionForClosest = nullptr;
            playerToUpdate->m_info->m_greaterOptionForClosest = nullptr;
            return;
        }

        if (playerToUpdate->m_parent->m_left == playerToUpdate)
        {
            playerToUpdate->m_info->m_greaterOptionForClosest = playerToUpdate->m_parent;

            Node<PlayerByStats> *ptr = playerToUpdate;


            while (ptr->m_parent != nullptr && ptr->m_parent->m_left == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                playerToUpdate->m_info->m_smallerOptionForClosest = ptr->m_parent;
            } else
            {
                playerToUpdate->m_info->m_smallerOptionForClosest = nullptr;
            }
        }
        if (playerToUpdate->m_parent->m_right == playerToUpdate)
        {
            playerToUpdate->m_info->m_smallerOptionForClosest = playerToUpdate->m_parent;

            Node<PlayerByStats> *ptr = playerToUpdate;

            while (ptr->m_parent != nullptr && ptr->m_parent->m_right == ptr)
            {
                ptr = ptr->m_parent;
            }
            if (ptr->m_parent != nullptr)
            {
                playerToUpdate->m_info->m_greaterOptionForClosest = ptr->m_parent;
            } else
            {
                playerToUpdate->m_info->m_greaterOptionForClosest = nullptr;
            }
        }
    }
}*/


#endif //WET_1_PLAYERBYSTRENGTH_H
