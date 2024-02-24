#include "Olympicsa1.h"



Olympics::Olympics(){
    m_Countries = new AVLTree<Country>();
    m_Teams = new AVLTree<Team>();
    m_Players = new AVLTree<PlayerByID>();
}

Olympics::~Olympics(){
    delete m_Countries;
    delete m_Teams;
    delete m_Players;
    m_Countries = nullptr;
    m_Teams = nullptr;
    m_Players = nullptr;
}
	
StatusType Olympics::add_country(int countryId, int medals){
    if(medals < 0 || countryId <=0)
    {
        return StatusType::INVALID_INPUT;
    }
    Country *newCountry;
    try
    {
        newCountry = new Country(countryId, medals);
        if(m_Countries->findNode(newCountry) != nullptr)
        {
            delete newCountry;
            return StatusType::FAILURE;
        }
        m_Countries->insertNode(newCountry);
    } catch(std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_country(int countryId){
	if(countryId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Country *countryFinder;
        countryFinder = new Country(countryId, 0);
        Node<Country> *toBeRemoved = m_Countries->findNode(countryFinder);
        if(toBeRemoved == nullptr)
        {
            delete countryFinder;
            return StatusType::FAILURE;
        }
        delete countryFinder;
        if(toBeRemoved->m_info->m_playerCount != 0 || !toBeRemoved->m_info->m_countryTeams->isEmpty())
        {
            return StatusType::FAILURE;
        }
        m_Countries->removeNode(toBeRemoved->m_info);
    } catch (std::bad_alloc &)
{
    return StatusType::ALLOCATION_ERROR;
}
    return StatusType::SUCCESS;
}

StatusType Olympics::add_team(int teamId,int countryId,Sport sport){
	if(teamId <= 0 || countryId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Country *countryFinder;
    Team *newTeam;
    Team *newTeamInCountry;
    try {
        countryFinder = new Country(countryId, 0);
        Node<Country> *country = m_Countries->findNode(countryFinder);
        if(country == nullptr) //if country doesn't exist
        {
            delete countryFinder;
            return StatusType::FAILURE;
        }
        newTeam = new Team(teamId, sport);
        Node<Team> *alreadyExists = m_Teams->findNode(newTeam);
        if(alreadyExists)
        {
            delete countryFinder;
            delete newTeam;
            return StatusType::FAILURE;
        }
        newTeamInCountry = new Team(teamId, sport);
        m_Teams->insertNode(newTeam);
        country->m_info->m_countryTeams->insertNode(newTeamInCountry);
        //newTeam-> m_teamInCountryTree = newTeamInCountry;
        newTeam->m_teamCountry = country->m_info;
        newTeamInCountry->m_teamCountry = country->m_info;
        delete countryFinder;
    } catch(std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_team(int teamId){
	if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Team *checkIfExists;
        checkIfExists = new Team(/*0*/teamId, Sport::SWIMMING);////////////
        Node<Team> *toBeRemoved = m_Teams->findNode(checkIfExists);
        delete checkIfExists;
        if (toBeRemoved == nullptr)
        {
            return StatusType::FAILURE;
        }
        if(!toBeRemoved->m_info->m_firstThirdID->isEmpty())
        {
            return StatusType::FAILURE;
        }
        toBeRemoved->m_info->m_teamCountry->m_countryTeams->removeNode(toBeRemoved->m_info);
        m_Teams->removeNode(toBeRemoved->m_info);
    } catch (std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
	
StatusType Olympics::add_contestant(int contestantId ,int countryId,Sport sport,int strength){
    try{
        if (strength < 0 || countryId <= 0 || contestantId <= 0)
        {
            return StatusType::INVALID_INPUT;
        }
        Country checkIfCountryExists(countryId, 0);
        Node<Country> *playerCountry = m_Countries->findNode(&checkIfCountryExists);
        PlayerByID checkIfPlayerExists(contestantId, 0, Sport::SWIMMING, nullptr);
        Node<PlayerByID> *playerNode = m_Players->findNode(&checkIfPlayerExists);
        if (playerCountry == nullptr || playerNode != nullptr)
        {
            return StatusType::FAILURE;
        }
        PlayerByID *playerInGenTree;
        playerInGenTree = new PlayerByID(contestantId, strength, sport, playerCountry->m_info);
        try
        {
            m_Players->insertNode(playerInGenTree);
        } catch(std::bad_alloc &)
        {
            delete playerInGenTree;
            throw;
        }
        playerCountry->m_info->m_playerCount++;
    } catch(std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}
	
StatusType Olympics::remove_contestant(int contestantId){
	if(contestantId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    PlayerByID playerFinder(contestantId, 0 , Sport::SWIMMING, nullptr);
    Node<PlayerByID> *playerNode = m_Players->findNode(&playerFinder);
    if(playerNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(playerNode->m_info->m_teamCount > 0)
    {
        return StatusType::FAILURE;
    }
    Country *playerCountry = playerNode->m_info->m_playerCountry;
    try
    {
        m_Players->removeNode(&playerFinder);
    } catch(std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    playerCountry->m_playerCount--;
    return StatusType::SUCCESS;
}
	
StatusType Olympics::add_contestant_to_team(int teamId,int contestantId){ //TODO TODO TODO TODO #######################
	if(teamId <= 0 || contestantId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    PlayerByID playerFinder(contestantId, 0, Sport::SWIMMING, nullptr);
    Team teamFinder(teamId, Sport::SPINNING);
    Node<PlayerByID> *playerNode = m_Players->findNode(&playerFinder);
    Node<Team> *teamtemp = m_Teams->findNode(&teamFinder);
    Country* teamCountry = teamtemp->m_info->m_teamCountry;
    Node<Team> *teamNode = teamCountry->m_countryTeams->findNode(&teamFinder);

    if(playerNode == nullptr || teamNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(playerNode->m_info->m_playerCountry != teamNode->m_info->m_teamCountry
    || playerNode->m_info->m_sport != teamNode->m_info->m_sport || playerNode->m_info->m_teamCount >= 3)
    {
        return StatusType::FAILURE;
    }
    if(teamNode->m_info->m_firstThirdID->findNode(&playerFinder) != nullptr || teamNode->m_info->m_secondThirdID->findNode(&playerFinder) != nullptr
    || teamNode->m_info->m_lastThirdID->findNode(&playerFinder) != nullptr)
    {
        return StatusType::FAILURE;
    }
    PlayerByID *playerIDInThird = new PlayerByID(playerNode->m_info->m_ID, playerNode->m_info->m_strength, playerNode->m_info->m_sport, playerNode->m_info->m_playerCountry);
    PlayerByStrength *playerSTRInThird = new PlayerByStrength(playerNode->m_info->m_ID, playerNode->m_info->m_strength, playerNode->m_info->m_sport, playerNode->m_info->m_playerCountry);
    //PlayerByStrength *playerSTRGen = new PlayerByStrength(playerNode->m_info->m_ID, playerNode->m_info->m_strength, playerNode->m_info->m_sport, playerNode->m_info->m_playerCountry);
    try
    {
        addPlayer(teamNode->m_info,playerIDInThird, playerSTRInThird);
        updateMinMax(teamNode->m_info);////////////
    } catch (std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    playerNode->m_info->m_teamCount++;
    if(playerNode->m_info->m_team1 == nullptr)
    {
        playerNode->m_info->m_team1 = teamNode->m_info;
    }
    else if(playerNode->m_info->m_team2 == nullptr)
    {
        playerNode->m_info->m_team2 = teamNode->m_info;
    }
    else if(playerNode->m_info->m_team3 == nullptr)
    {
        playerNode->m_info->m_team3 = teamNode->m_info;
    }
    return StatusType::SUCCESS;
}

StatusType Olympics::remove_contestant_from_team(int teamId,int contestantId){
    if(teamId <= 0 || contestantId <= 0)
    {
        return StatusType::FAILURE;
    }

    PlayerByID playerFinder(contestantId, 0, Sport::SWIMMING, nullptr);
    Node<PlayerByID> *playerIDNode = m_Players->findNode(&playerFinder);
    if(playerIDNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    int teamNum = -1;
    if(playerIDNode->m_info->m_team1 != nullptr && playerIDNode->m_info->m_team1->m_teamID == teamId)
    {
        teamNum = 1;
    }
    else if(playerIDNode->m_info->m_team2 != nullptr && playerIDNode->m_info->m_team2->m_teamID == teamId)
    {
        teamNum = 2;
    }
    else if(playerIDNode->m_info->m_team3 != nullptr && playerIDNode->m_info->m_team3->m_teamID == teamId)
    {
        teamNum = 3;
    }
    if(teamNum == -1)
    {
        return StatusType::FAILURE;
    }
    PlayerByStrength playerSTRFinder(playerIDNode->m_info->m_ID, playerIDNode->m_info->m_strength, playerIDNode->m_info->m_sport, playerIDNode->m_info->m_playerCountry);
    Node<PlayerByStrength>* playerBySTRGen;
    if(teamNum == 1)
    {
        playerBySTRGen = playerIDNode->m_info->m_team1->m_playersBySTR->findNode(&playerSTRFinder);
        removePlayer(playerIDNode->m_info->m_team1, playerBySTRGen->m_info);
        updateMinMax(playerIDNode->m_info->m_team1);////////////
        playerIDNode->m_info->m_team1 = nullptr;
    }
    else if(teamNum == 2)
    {
        playerBySTRGen = playerIDNode->m_info->m_team2->m_playersBySTR->findNode(&playerSTRFinder);
        removePlayer(playerIDNode->m_info->m_team2, playerBySTRGen->m_info);
        updateMinMax(playerIDNode->m_info->m_team2);////////////
        playerIDNode->m_info->m_team2 = nullptr;
    }
    else
    {
        playerBySTRGen = playerIDNode->m_info->m_team3->m_playersBySTR->findNode(&playerSTRFinder);
        removePlayer(playerIDNode->m_info->m_team3, playerBySTRGen->m_info);
        updateMinMax(playerIDNode->m_info->m_team3); ////////////
        playerIDNode->m_info->m_team3 = nullptr;
    }
    playerIDNode->m_info->m_teamCount--;
	return StatusType::SUCCESS;
}

StatusType Olympics::update_contestant_strength(int contestantId ,int change){ //TODO TODO #############
    try
    {
        if (contestantId <= 0)
        {
            return StatusType::INVALID_INPUT;
        }
        PlayerByID playerFinder(contestantId, 0, Sport::SWIMMING, nullptr);
        Node<PlayerByID> *playerNode = m_Players->findNode(&playerFinder);
        if (playerNode == nullptr)
        {
            return StatusType::FAILURE;
        }
        if (playerNode->m_info->m_strength + change < 0)
        {
            return StatusType::FAILURE;
        }
        int new_strength = playerNode->m_info->m_strength + change;
        if(new_strength < 0)
        {
            return StatusType::FAILURE;
        }
        PlayerByID *player = playerNode->m_info;
        if (player->m_team1 != nullptr)
        {
            PlayerByStrength *updatedSTRThird1 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                     player->m_playerCountry);
            PlayerByStrength *updatedSTRGen1 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                   player->m_playerCountry);
            PlayerByStrength p1(player->m_ID, player->m_strength, player->m_sport, player->m_playerCountry);
            Node<PlayerByID> *p = player->m_team1->m_firstThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team1->m_firstThirdSTR->removeNode(&p1);
                player->m_team1->m_firstThirdSTR->insertNode(updatedSTRThird1);
                player->m_team1->m_playersBySTR->removeNode(&p1);
                player->m_team1->m_playersBySTR->insertNode(updatedSTRGen1);
                updatedSTRThird1->m_playerInIDThird = p->m_info;
                p->m_info->m_StrengthVersionThird = updatedSTRThird1;
                p->m_info->m_StrengthVersionTeamGen = updatedSTRGen1;
                updatedSTRGen1->m_playerInIDThird = p->m_info;
            }
            p = player->m_team1->m_secondThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team1->m_secondThirdSTR->removeNode(&p1);
                player->m_team1->m_secondThirdSTR->insertNode(updatedSTRThird1);
                player->m_team1->m_playersBySTR->removeNode(&p1);
                player->m_team1->m_playersBySTR->insertNode(updatedSTRGen1);
                updatedSTRThird1->m_playerInIDThird = p->m_info;
                p->m_info->m_StrengthVersionThird = updatedSTRThird1;
                p->m_info->m_StrengthVersionTeamGen = updatedSTRGen1;
                updatedSTRGen1->m_playerInIDThird = p->m_info;
            }
            p = player->m_team1->m_lastThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team1->m_lastThirdSTR->removeNode(&p1);
                player->m_team1->m_lastThirdSTR->insertNode(updatedSTRThird1);
                player->m_team1->m_playersBySTR->removeNode(&p1);
                player->m_team1->m_playersBySTR->insertNode(updatedSTRGen1);
                updatedSTRThird1->m_playerInIDThird = p->m_info;
                p->m_info->m_StrengthVersionThird = updatedSTRThird1;
                p->m_info->m_StrengthVersionTeamGen = updatedSTRGen1;
                updatedSTRGen1->m_playerInIDThird = p->m_info;
            }
            updateMinMax(player->m_team1);////////////
        }
        if (player->m_team2 != nullptr)
        {
            PlayerByStrength *updatedSTRThird2 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                     player->m_playerCountry);
            PlayerByStrength *updatedSTRGen2 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                   player->m_playerCountry);
            PlayerByStrength p2(player->m_ID, player->m_strength, player->m_sport, player->m_playerCountry);
            Node<PlayerByID> *p = player->m_team2->m_firstThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team2->m_firstThirdSTR->removeNode(&p2);
                player->m_team2->m_firstThirdSTR->insertNode(updatedSTRThird2);
            }
            p = player->m_team1->m_secondThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team2->m_secondThirdSTR->removeNode(&p2);
                player->m_team2->m_secondThirdSTR->insertNode(updatedSTRThird2);
            }
            p = player->m_team2->m_lastThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team2->m_lastThirdSTR->removeNode(&p2);
                player->m_team2->m_lastThirdSTR->insertNode(updatedSTRThird2);
            }
            player->m_team2->m_playersBySTR->removeNode(&p2);
            player->m_team2->m_playersBySTR->insertNode(updatedSTRGen2);
            updatedSTRThird2->m_playerInIDThird = p->m_info;
            p->m_info->m_StrengthVersionThird = updatedSTRThird2;
            p->m_info->m_StrengthVersionTeamGen = updatedSTRGen2;
            updatedSTRGen2->m_playerInIDThird = p->m_info;
            updateMinMax(player->m_team2);////////////
        }
        if (player->m_team3 != nullptr)
        {
            PlayerByStrength *updatedSTRThird3 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                     player->m_playerCountry);
            PlayerByStrength *updatedSTRGen3 = new PlayerByStrength(player->m_ID, new_strength, player->m_sport,
                                                                   player->m_playerCountry);
            PlayerByStrength p3(player->m_ID, player->m_strength, player->m_sport, player->m_playerCountry);
            Node<PlayerByID> *p = player->m_team3->m_firstThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team3->m_firstThirdSTR->removeNode(&p3);
                player->m_team3->m_firstThirdSTR->insertNode(updatedSTRThird3);
            }
            p = player->m_team3->m_secondThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team3->m_secondThirdSTR->removeNode(&p3);
                player->m_team3->m_secondThirdSTR->insertNode(updatedSTRThird3);
            }
            p = player->m_team1->m_lastThirdID->findNode(player);
            if (p != nullptr)
            {
                player->m_team3->m_lastThirdSTR->removeNode(&p3);
                player->m_team3->m_lastThirdSTR->insertNode(updatedSTRThird3);
            }
            player->m_team3->m_playersBySTR->removeNode(&p3);
            player->m_team3->m_playersBySTR->insertNode(updatedSTRGen3);
            updatedSTRThird3->m_playerInIDThird = p->m_info;
            p->m_info->m_StrengthVersionThird = updatedSTRThird3;
            p->m_info->m_StrengthVersionTeamGen = updatedSTRGen3;
            updatedSTRGen3->m_playerInIDThird = p->m_info;
            updateMinMax(player->m_team3);////////////
        }
        player->m_strength = new_strength;
    } catch (std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> Olympics::get_strength(int contestantId){
	if( contestantId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    PlayerByID playerFinder(contestantId, 0, Sport::SWIMMING, nullptr);
    Node<PlayerByID> *playerIDNode = m_Players->findNode(&playerFinder);
    if(playerIDNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    return playerIDNode->m_info->m_strength;
}

output_t<int> Olympics::get_medals(int countryId){
	if(countryId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Country countryFinder(countryId, 0);
    Node<Country> *countryNode = m_Countries->findNode(&countryFinder);
    if(countryNode == nullptr)
    {
        return StatusType::FAILURE;
    }
    return countryNode->m_info->m_medals;
}

output_t<int> Olympics::get_team_strength(int teamId){
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team checkIfExists(/*0*/teamId, Sport::SWIMMING);/////////
    Node<Team> *team = m_Teams->findNode(&checkIfExists);
    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }
    Country* teamCountry = team->m_info->m_teamCountry;
    Node<Team> *teamInCountry = teamCountry->m_countryTeams->findNode(&checkIfExists);
    int n1 = 0;
    int n2 = 0;
    int n3 = 0;
    if(teamInCountry->m_info->m_firstThirdID != nullptr)
    {
        n1 = teamInCountry->m_info->m_firstThirdID->m_treeSize;
    }
    if(teamInCountry->m_info->m_secondThirdID != nullptr)
    {
        n2 = teamInCountry->m_info->m_secondThirdID->m_treeSize;
    }
    if(teamInCountry->m_info->m_lastThirdID != nullptr)
    {
        n3 = teamInCountry->m_info->m_lastThirdID->m_treeSize;
    }
    int num = n1 + n2 + n3;
    if ((num % 3) != 0 || num == 0)
    {
        return 0;
    }
    int strength = teamInCountry->m_info->m_firstThirdMax1STR->m_strength + teamInCountry->m_info->m_secondThirdMax1STR->m_strength + teamInCountry->m_info->m_lastThirdMax1STR->m_strength;
	return strength;
}

StatusType Olympics::unite_teams(int teamId1,int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    Team checkIfExists1(teamId1, Sport::SWIMMING);
    Team checkIfExists2(teamId2, Sport::SWIMMING);
    Node<Team> *team1 = m_Teams->findNode(&checkIfExists1);
    Node<Team> *team2 = m_Teams->findNode(&checkIfExists1);
    if (team1 == nullptr || team2 == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(team1->m_info->m_teamCountry->m_countryID != team2->m_info->m_teamCountry->m_countryID)
    {
        return StatusType::FAILURE;
    }
    if(team1->m_info->m_sport != team2->m_info->m_sport)
    {
        return StatusType::FAILURE;
    }
    Node<Team> *team1InCountry = team1->m_info->m_teamCountry->m_countryTeams->findNode(&checkIfExists1);
    Node<Team> *team2InCountry = team2->m_info->m_teamCountry->m_countryTeams->findNode(&checkIfExists2);

    int sizeOfArray11 = team1InCountry->m_info->m_firstThirdID->m_treeSize;

    int sizeOfArray12 = team1InCountry->m_info->m_secondThirdID->m_treeSize;

    int sizeOfArray13 = team1InCountry->m_info->m_lastThirdID->m_treeSize;

    int sizeOfArray21 = team2InCountry->m_info->m_firstThirdID->m_treeSize;

    int sizeOfArray22 = team2InCountry->m_info->m_secondThirdID->m_treeSize;

    int sizeOfArray23 = team2InCountry->m_info->m_lastThirdID->m_treeSize;

    PlayerByID **arrayID11;
    try
    {
        arrayID11 = new PlayerByID *[sizeOfArray11];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayID12;
    try
    {
        arrayID12 = new PlayerByID *[sizeOfArray12];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayID13;
    try
    {
        arrayID13 = new PlayerByID *[sizeOfArray13];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayMerged112;
    try
    {
        arrayMerged112 = new PlayerByID *[sizeOfArray11 + sizeOfArray12];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayMerged1123;
    try
    {
        arrayMerged1123 = new PlayerByID *[sizeOfArray11 + sizeOfArray12 + sizeOfArray13];
    } catch (std::bad_alloc &)
    {
        throw;
    }


    PlayerByID **arrayID21;
    try
    {
        arrayID21 = new PlayerByID *[sizeOfArray21];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayID22;
    try
    {
        arrayID22 = new PlayerByID *[sizeOfArray22];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayID23;
    try
    {
        arrayID23 = new PlayerByID *[sizeOfArray23];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayMerged212;
    try
    {
        arrayMerged212 = new PlayerByID *[sizeOfArray21 + sizeOfArray22];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByID **arrayMerged2123;
    try
    {
        arrayMerged2123 = new PlayerByID *[sizeOfArray21 + sizeOfArray22 + sizeOfArray23];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(team1InCountry->m_info->m_firstThirdID->m_root, arrayID11, sizeOfArray11, 0);
    InorderTransversalIntoArray(team1InCountry->m_info->m_secondThirdID->m_root, arrayID12, sizeOfArray12, 0);
    InorderTransversalIntoArray(team1InCountry->m_info->m_lastThirdID->m_root, arrayID13, sizeOfArray13, 0);
    mergeTwoArraysIntoOne(arrayID11, arrayID12, arrayMerged112, sizeOfArray11, sizeOfArray12);
    mergeTwoArraysIntoOne(arrayMerged112, arrayID13, arrayMerged1123, sizeOfArray11 + sizeOfArray12, sizeOfArray13);

    InorderTransversalIntoArray(team2InCountry->m_info->m_firstThirdID->m_root, arrayID21, sizeOfArray21, 0);
    InorderTransversalIntoArray(team2InCountry->m_info->m_secondThirdID->m_root, arrayID22, sizeOfArray22, 0);
    InorderTransversalIntoArray(team2InCountry->m_info->m_lastThirdID->m_root, arrayID23, sizeOfArray23, 0);
    mergeTwoArraysIntoOne(arrayID21, arrayID22, arrayMerged212, sizeOfArray21, sizeOfArray22);
    mergeTwoArraysIntoOne(arrayMerged212, arrayID23, arrayMerged2123, sizeOfArray21 + sizeOfArray22, sizeOfArray23);

    PlayerByID **arrayMergedTeam12;
    try
    {
        arrayMergedTeam12 = new PlayerByID *[sizeOfArray11 + sizeOfArray12 + sizeOfArray13 + sizeOfArray21 + sizeOfArray22 + sizeOfArray23];
        //arrayMergedTeam12 = {nullptr};
        for (int i = 0; i < sizeOfArray11 + sizeOfArray12 + sizeOfArray13 + sizeOfArray21 + sizeOfArray22 + sizeOfArray23; i++)
        {
            arrayMergedTeam12[i] = nullptr;
        }
    } catch (std::bad_alloc &)
    {
        throw;
    }
    mergeTwoArraysIntoOne(arrayMerged1123, arrayMerged2123, arrayMergedTeam12, sizeOfArray11 + sizeOfArray12 + sizeOfArray13, sizeOfArray21 + sizeOfArray22 + sizeOfArray23);
    int true_length = 0;
    while(arrayMergedTeam12[true_length] != nullptr)
    {
        true_length++;
    }

    PlayerByID **trueMergedTeam12;
    try
    {
        trueMergedTeam12 = new PlayerByID *[true_length];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    for(int i = 0; i < true_length; i++)
    {
        trueMergedTeam12[i] = arrayMergedTeam12[i];
    }
    int sizeOfFirstThird = true_length / 3;
    int sizeOfSecondThird = true_length / 3;
    int sizeOfLastThird = true_length / 3;
    if(true_length % 3 == 1)
    {
        sizeOfFirstThird = true_length / 3 + 1;
    }
    else if(true_length % 3 == 2)
    {
        sizeOfFirstThird = true_length / 3 + 1;
        sizeOfSecondThird = true_length / 3 + 1;
    }

    for(int i = 0; i < sizeOfFirstThird; i++)
    {
        trueMergedTeam12[i]->m_currentThird = 1;
    }
    for(int i = sizeOfFirstThird; i < sizeOfFirstThird + sizeOfSecondThird; i++)
    {
        trueMergedTeam12[i]->m_currentThird = 2;
    }
    for(int i = sizeOfFirstThird + sizeOfSecondThird; i < sizeOfFirstThird + sizeOfSecondThird + sizeOfLastThird; i++)
    {
        trueMergedTeam12[i]->m_currentThird = 3;
    }
    Node<PlayerByID> *new_rootID1 = mergedArrayIntoBalTree(trueMergedTeam12, 0, sizeOfFirstThird - 1);
    Node<PlayerByID> *new_rootID2 = mergedArrayIntoBalTree(trueMergedTeam12, sizeOfFirstThird,
                                                           sizeOfFirstThird + sizeOfSecondThird - 1);
    Node<PlayerByID> *new_rootID3 = mergedArrayIntoBalTree(trueMergedTeam12, sizeOfFirstThird + sizeOfSecondThird,
                                                           sizeOfFirstThird + sizeOfSecondThird + sizeOfLastThird - 1);

    PlayerByID **arrayPtrUpdate11;
    try
    {
        arrayPtrUpdate11 = new PlayerByID *[sizeOfFirstThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    InorderTransversalIntoArray(new_rootID1, arrayPtrUpdate11, sizeOfFirstThird, 0);
    for(int i = 0; i < sizeOfFirstThird; i++)
    {
        arrayPtrUpdate11[i]->m_StrengthVersionThird->m_playerInIDThird = arrayPtrUpdate11[i];
        arrayPtrUpdate11[i]->m_StrengthVersionTeamGen->m_playerInIDThird = arrayPtrUpdate11[i];
    }
    PlayerByID **arrayPtrUpdate12;
    try
    {
        arrayPtrUpdate12 = new PlayerByID *[sizeOfSecondThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    InorderTransversalIntoArray(new_rootID2, arrayPtrUpdate12, sizeOfSecondThird, 0);
    for(int i = 0; i < sizeOfFirstThird; i++)
    {
        arrayPtrUpdate12[i]->m_StrengthVersionThird->m_playerInIDThird = arrayPtrUpdate12[i];
        arrayPtrUpdate12[i]->m_StrengthVersionTeamGen->m_playerInIDThird = arrayPtrUpdate12[i];
    }
    PlayerByID **arrayPtrUpdate13;
    try
    {
        arrayPtrUpdate13 = new PlayerByID *[sizeOfLastThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    InorderTransversalIntoArray(new_rootID3, arrayPtrUpdate13, sizeOfFirstThird, 0);
    for(int i = 0; i < sizeOfFirstThird; i++)
    {
        arrayPtrUpdate13[i]->m_StrengthVersionThird->m_playerInIDThird = arrayPtrUpdate13[i];
        arrayPtrUpdate13[i]->m_StrengthVersionTeamGen->m_playerInIDThird = arrayPtrUpdate13[i];
    }
    //delete team1InCountry->m_info->m_firstThirdID;
    //delete team1InCountry->m_info->m_secondThirdID;
    //delete team1InCountry->m_info->m_lastThirdID;
    team1InCountry->m_info->m_firstThirdID->m_root = new_rootID1;
    team1InCountry->m_info->m_firstThirdID->m_treeSize = sizeOfFirstThird;
    team1InCountry->m_info->m_secondThirdID->m_root = new_rootID2;
    team1InCountry->m_info->m_secondThirdID->m_treeSize = sizeOfSecondThird;
    team1InCountry->m_info->m_lastThirdID->m_root = new_rootID3;
    team1InCountry->m_info->m_lastThirdID->m_treeSize = sizeOfLastThird;

    PlayerByStrength **arraySTRGen1;
    try
    {
        arraySTRGen1 = new PlayerByStrength *[team1InCountry->m_info->m_playersBySTR->m_treeSize];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    PlayerByStrength **arraySTRGen2;
    try
    {
        arraySTRGen2 = new PlayerByStrength *[team2InCountry->m_info->m_playersBySTR->m_treeSize];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(team1InCountry->m_info->m_playersBySTR->m_root, arraySTRGen1, team1InCountry->m_info->m_playersBySTR->m_treeSize, 0);
    InorderTransversalIntoArray(team2InCountry->m_info->m_playersBySTR->m_root, arraySTRGen2, team2InCountry->m_info->m_playersBySTR->m_treeSize, 0);

    PlayerByStrength **arrayMergedSTRGen;
    try
    {
        arrayMergedSTRGen = new PlayerByStrength *[team1InCountry->m_info->m_playersBySTR->m_treeSize + team2InCountry->m_info->m_playersBySTR->m_treeSize];
        //arrayMergedSTRGen = {nullptr};
        for(int i = 0; i < team1InCountry->m_info->m_playersBySTR->m_treeSize + team2InCountry->m_info->m_playersBySTR->m_treeSize; i++)
        {
            arrayMergedSTRGen[i] = nullptr;
        }
    } catch (std::bad_alloc &)
    {
        throw;
    }

    mergeTwoArraysIntoOne(arraySTRGen1, arraySTRGen2, arrayMergedSTRGen, team1InCountry->m_info->m_playersBySTR->m_treeSize, team2InCountry->m_info->m_playersBySTR->m_treeSize);

    /*int true_lengthstr = 0;
    while(arrayMergedSTRGen[true_lengthstr] != nullptr)
    {
        true_lengthstr++;
    }*/

    PlayerByStrength **trueMergedTeamSTR;
    try
    {
        trueMergedTeamSTR = new PlayerByStrength *[true_length];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    for(int i = 0; i < true_length; i++)
    {
        trueMergedTeamSTR[i] = arrayMergedSTRGen[i];
    }

    PlayerByStrength **arraySTR1New;
    try
    {
        arraySTR1New = new PlayerByStrength *[sizeOfFirstThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    PlayerByStrength **arraySTR2New;
    try
    {
        arraySTR2New = new PlayerByStrength *[sizeOfSecondThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    PlayerByStrength **arraySTR3New;
    try
    {
        arraySTR3New = new PlayerByStrength *[sizeOfLastThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }
    int i = 0;
    int j = 0;
    int k = 0;
    for(int l = 0; l < true_length; l++)
    {
        if(trueMergedTeamSTR[l]->m_playerInIDThird->m_currentThird == 1)
        {
            arraySTR1New[i] = trueMergedTeamSTR[l];
            i++;
        }
        else if(trueMergedTeamSTR[l]->m_playerInIDThird->m_currentThird == 2)
        {
            arraySTR2New[j] = trueMergedTeamSTR[l];
            j++;
        }
        else
        {
            arraySTR3New[k] = trueMergedTeamSTR[l];
            k++;
        }
    }



    Node<PlayerByStrength> *new_rootSTR1 = mergedArrayIntoBalTree(arraySTR1New, 0, sizeOfFirstThird - 1);
    Node<PlayerByStrength> *new_rootSTR2 = mergedArrayIntoBalTree(arraySTR2New, 0,
                                                                  sizeOfSecondThird - 1);
    Node<PlayerByStrength> *new_rootSTR3 = mergedArrayIntoBalTree(arraySTR3New, 0,
                                                           sizeOfLastThird - 1);

    PlayerByStrength **arrayToUpdate21;
    try
    {
        arrayToUpdate21 = new PlayerByStrength *[sizeOfFirstThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(new_rootSTR1, arrayToUpdate21, sizeOfFirstThird, 0);

    for(i = 0; i < sizeOfFirstThird; i++)
    {
        arrayToUpdate21[i]->m_playerInIDThird->m_StrengthVersionThird = arrayToUpdate21[i];
    }

    PlayerByStrength **arrayToUpdate22;
    try
    {
        arrayToUpdate22 = new PlayerByStrength *[sizeOfSecondThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(new_rootSTR2, arrayToUpdate22, sizeOfSecondThird, 0);

    for(i = 0; i < sizeOfSecondThird; i++)
    {
        arrayToUpdate22[i]->m_playerInIDThird->m_StrengthVersionThird = arrayToUpdate22[i];
    }

    PlayerByStrength **arrayToUpdate23;
    try
    {
        arrayToUpdate23 = new PlayerByStrength *[sizeOfLastThird];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(new_rootSTR3, arrayToUpdate23, sizeOfLastThird, 0);

    for(i = 0; i < sizeOfLastThird; i++)
    {
        arrayToUpdate23[i]->m_playerInIDThird->m_StrengthVersionThird = arrayToUpdate23[i];
    }

    //delete team1InCountry->m_info->m_firstThirdSTR;
    //delete team1InCountry->m_info->m_secondThirdSTR;
    //delete team1InCountry->m_info->m_lastThirdSTR;
    team1InCountry->m_info->m_firstThirdSTR->m_root = new_rootSTR1;
    team1InCountry->m_info->m_firstThirdSTR->m_treeSize = sizeOfFirstThird;
    team1InCountry->m_info->m_secondThirdSTR->m_root = new_rootSTR2;
    team1InCountry->m_info->m_secondThirdSTR->m_treeSize = sizeOfSecondThird;
    team1InCountry->m_info->m_lastThirdSTR->m_root = new_rootSTR3;
    team1InCountry->m_info->m_lastThirdSTR->m_treeSize = sizeOfLastThird;

    Node<PlayerByStrength> *new_rootSTRGen = mergedArrayIntoBalTree(trueMergedTeamSTR, 0, true_length);

    PlayerByStrength **arrayToUpdateGen;
    try
    {
        arrayToUpdateGen = new PlayerByStrength *[true_length];
    } catch (std::bad_alloc &)
    {
        throw;
    }

    InorderTransversalIntoArray(new_rootSTRGen, arrayToUpdateGen, true_length, 0);

    for(i = 0; i < true_length; i++)
    {
        arrayToUpdateGen[i]->m_playerInIDThird->m_StrengthVersionTeamGen = arrayToUpdateGen[i];
    }

    delete team1InCountry->m_info->m_playersBySTR;
    team1InCountry->m_info->m_playersBySTR->m_root = new_rootSTRGen;
    team1InCountry->m_info->m_playersBySTR->m_treeSize = sizeOfFirstThird + sizeOfSecondThird + sizeOfLastThird;


    //in the end
    m_Teams->removeNode(&checkIfExists2);
    team2->m_info->m_teamCountry->m_countryTeams->removeNode(&checkIfExists2);

    updateMinMax(team1InCountry->m_info);
    //1. unite teams in Gen ID Tree
    //2. unite ID thirds into array
    //3. inorder transversal to create new Thirds
    //TODO update minMax *#*#*#*#*#*#



    ///////updateMinMax
    ////////////return StatusType::ALLOCATION_ERROR;
	return StatusType::SUCCESS;
}

StatusType Olympics::play_match(int teamId1,int teamId2){
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
    {
        return StatusType::INVALID_INPUT;
    }
    Team checkIfExists1(teamId1, Sport::SWIMMING);
    Team checkIfExists2(teamId2, Sport::SWIMMING);
    Node<Team> *team1 = m_Teams->findNode(&checkIfExists1);
    Node<Team> *team2 = m_Teams->findNode(&checkIfExists2);
    if (team1 == nullptr || team2 == nullptr)
    {
        return StatusType::FAILURE;
    }
    if(team1->m_info->m_sport != team2->m_info->m_sport)
    {
        return StatusType::FAILURE;
    }
    int s1 = 0, s2 = 0;
    s1 = team1->m_info->m_teamCountry->m_medals + get_team_strength(teamId1).ans();
    s2 = team2->m_info->m_teamCountry->m_medals + get_team_strength(teamId2).ans();
    if (s1 > s2)
    {
        team1->m_info->m_teamCountry->m_medals++;
    }
    if (s1 < s2)
    {
        team2->m_info->m_teamCountry->m_medals++;
    }
    ////////////return StatusType::ALLOCATION_ERROR;
	return StatusType::SUCCESS;
}

int maxg(int s1 = 0, int s2 = 0, int s3 = 0, int s4 = 0, int s5 = 0, int s6 = 0, int s7 = 0, int s8 = 0, int s9 = 0, int s10 = 0)
{
    if(s1 >= s2 && s1 >=s3 && s1 >=s4 && s1>=s5 && s1>=s6 && s1>=s7 && s1 >= s8 && s1 >= s9 && s1 >= s10)
    {
        return s1;
    }
    if(s2 >= s1 && s2 >=s3 && s2 >=s4 && s2>=s5 && s2>=s6 && s2>=s7 && s2 >= s8 && s2 >= s9 && s2 >= s10)
    {
        return s2;
    }
    if(s3 >= s1 && s3 >= s2 && s3 >=s4 && s3>=s5 && s3>=s6 && s3>=s7 && s3 >= s8 && s3 >= s9 && s3 >= s10)
    {
        return s3;
    }
    if(s4 >= s1 && s4 >= s2 && s4 >=s3 && s4>=s5 && s4>=s6 && s4>=s7 && s4 >= s8 && s4 >= s9 && s4 >= s10)
    {
        return s4;
    }
    if(s5 >= s1 && s5 >= s2 && s5 >=s3 && s5 >=s4 && s5>=s6 && s5>=s7 && s5 >= s8 && s5 >= s9 && s5 >= s10)
    {
        return s5;
    }
    if(s6 >= s1 && s6 >= s2 && s6 >=s3 && s6 >=s4 && s6>=s5 && s6>=s7 && s6 >= s8 && s6 >= s9 && s6 >= s10)
    {
        return s6;
    }
    if(s7 >= s1 && s7 >= s2 && s7 >=s3 && s7 >=s4 && s7>=s5 && s7>=s6 && s7 >= s8 && s7 >= s9 && s7 >= s10)
    {
        return s7;
    }
    if(s8 >= s1 && s8 >= s2 && s8 >=s3 && s8 >=s4 && s8>=s5 && s8 >= s7 && s8>=s6 && s8 >= s9 && s8 >= s10)
    {
        return s8;
    }
    if(s9 >= s1 && s9 >= s2 && s9 >=s3 && s9 >=s4 && s9>=s5 && s9>=s6 && s9 >= s7 && s9 >= s8 && s9 >= s10)
    {
        return s9;
    }
    if(s10 >= s1 && s10 >= s2 && s10 >=s3 && s10 >=s4 && s10>=s5 && s10>=s6 && s10 >= s7 && s10 >= s8 && s10 >= s9)
    {
        return s10;
    }
}

output_t<int> Olympics::austerity_measures(int teamId){
    if(teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Team checkIfExists(/*0*/teamId, Sport::SWIMMING);/////////
    Node<Team> *team = m_Teams->findNode(&checkIfExists);
    if (team == nullptr)
    {
        return StatusType::FAILURE;
    }
    Node<Team> *teamInCountryNode = team->m_info->m_teamCountry->m_countryTeams->findNode(&checkIfExists);
    int size = teamInCountryNode->m_info->m_firstThirdID->m_treeSize + teamInCountryNode->m_info->m_secondThirdID->m_treeSize + teamInCountryNode->m_info->m_lastThirdID->m_treeSize;
    if (size < 3)
    {
        return StatusType::FAILURE;
    }
    int strength = 0;
    if (size == 3 || size % 3 != 0) // t1=1, t2=1, t3=1 -> 0,0,0
    {
        return 0;
    }


    //int s1 = 0, s2 = 0, s3 = 0;


    //(num % 3) = 0 -> next num = 6
     // t1=2, t2=2, t3=2
     Team *teamInCountry = teamInCountryNode->m_info;
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    int s1 = 0;
    int s2 = 0;
    int s3 = 0;
    int s4 = 0;
    int s5 = 0;
    int s6 = 0;
    int s7 = 0;
    int s8 = 0;
    int s9 = 0;
    int s10 = 0;

     if(size == 6)
     {
         //2,1,0
         max1 = teamInCountry->m_secondThirdMax1STR->m_strength;
         max2 = teamInCountry->m_lastThird1stMinID->m_strength;
         if(teamInCountry->m_lastThirdMax1STR->m_ID == teamInCountry->m_lastThird1stMinID->m_ID)
         {
             max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         }
         else
         {
             max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         s1 = max1 + max2 + max3;

         //2,0,1
         max1 = teamInCountry->m_secondThirdMax1STR->m_strength;
         max2 = teamInCountry->m_secondThirdMax2STR->m_strength;
         max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         s2 = max1 + max2 + max3;

         //1,2,0
         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         max2 = teamInCountry->m_lastThirdMax1STR->m_strength;
         max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         s3 = max1 + max2 + max3;

         //0,2,1
         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         max2 = teamInCountry->m_firstThirdMax2STR->m_strength;
         max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         s4 = max1 + max2 + max3;

         //0,1,2
         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         max2 = teamInCountry->m_firstThirdMax2STR->m_strength;
         max3 = teamInCountry->m_secondThirdMax1STR->m_strength;
         s5 = max1 + max2 + max3;

         //1,0,2
         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         max2 = teamInCountry->m_secondThirdMax1STR->m_strength;
         max3 = teamInCountry->m_secondThirdMax2STR->m_strength;

         //1,1,1
         s7 = get_team_strength(teamId).ans();
         return maxg(s1,s2,s3,s4,s5,s6,s7);
     }
     else
     {
         //3,0,0
         int m22;
         int m11;
         if(teamInCountry->m_firstThirdID->m_treeSize == 3)
         {
             m11 = 0;
         }
         else
         {
             m11 = teamInCountry->m_firstThirdMax1STR->m_strength;
         }
         max1 = maxg(m11, teamInCountry->m_secondThird1stMinID->m_strength, teamInCountry->m_secondThird2ndMinID->m_strength);
         if(teamInCountry->m_secondThirdMax1STR->m_ID != teamInCountry->m_secondThird1stMinID->m_ID && teamInCountry->m_secondThirdMax1STR->m_ID != teamInCountry->m_secondThird2ndMinID->m_ID)
         {
             m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
         }
         else if(teamInCountry->m_secondThirdMax2STR->m_ID != teamInCountry->m_secondThird2ndMinID->m_ID && teamInCountry->m_secondThirdMax2STR->m_ID != teamInCountry->m_secondThird1stMinID->m_ID)
         {
             m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
         }
         else
         {
             m22 = teamInCountry->m_secondThirdMax3STR->m_strength;
         }
         max2 = maxg(m22, teamInCountry->m_lastThird1stMinID->m_strength);
         if(teamInCountry->m_lastThirdMax1STR->m_ID == teamInCountry->m_lastThird1stMinID->m_ID)
         {
             max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         }
         else
         {
             max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         s1 = max1 + max2 + max3;

         //0,3,0
         if(teamInCountry->m_firstThirdMax1ID->m_ID == teamInCountry->m_firstThirdMax1STR->m_ID) //Todo add maxID to team
         {
             max1 = teamInCountry->m_firstThirdMax2STR->m_strength;
         }
         else
         {
             max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         }
         if(teamInCountry->m_secondThirdID->m_treeSize == 3)
         {
             m22 = 0;
         }
         else
         {
             m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
         }
         max2 = maxg(teamInCountry->m_firstThirdMax1ID->m_strength, m22, teamInCountry->m_lastThird1stMinID->m_strength);
         if(teamInCountry->m_lastThird1stMinID->m_strength == teamInCountry->m_lastThirdMax1STR->m_strength)
         {
             max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         }
         else
         {
             max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         s2 = max1 + max2 + max3;

         //0,0,3
         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         int m33;
         if(teamInCountry->m_lastThirdID->m_treeSize == 3)
         {
             m33 = 0;
         }
         else
         {
             m33 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         max3 = maxg(m33, teamInCountry->m_secondThirdMax1ID->m_strength, teamInCountry->m_secondThirdMax2ID->m_strength);
         if(teamInCountry->m_secondThirdMax1STR->m_strength != teamInCountry->m_secondThirdMax1ID->m_strength && teamInCountry->m_secondThirdMax1STR->m_strength != teamInCountry->m_secondThirdMax2ID->m_strength)
         {
             m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
         }
         else if(teamInCountry->m_secondThirdMax2STR->m_strength != teamInCountry->m_secondThirdMax1ID->m_strength && teamInCountry->m_secondThirdMax2STR->m_strength != teamInCountry->m_secondThirdMax2ID->m_strength)
         {
             m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
         }
         else
         {
             m22 = teamInCountry->m_secondThirdMax3STR->m_strength;
         }
         max2 = maxg(m22, teamInCountry->m_firstThirdMax1ID->m_strength);
         s3 = max1 + max2 + max3;

         //2,1,0

         if(teamInCountry->m_lastThirdMax1STR->m_ID == teamInCountry->m_lastThird1stMinID->m_ID)
         {
             max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         }
         else
         {
             max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         m11 = teamInCountry->m_firstThirdMax1STR->m_strength;
         int m12;
         if(teamInCountry->m_secondThirdMin1STR->m_ID == teamInCountry->m_secondThird1stMinID->m_ID)
         {
             m12 = teamInCountry->m_secondThird2ndMinID->m_strength;
         }
         else
         {
             m12 = teamInCountry->m_secondThird1stMinID->m_strength;
         }
         max1 = maxg(m11, m12);
         int m23 = teamInCountry->m_lastThird1stMinID->m_strength;
         if(teamInCountry->m_secondThirdMin1STR->m_ID == teamInCountry->m_secondThird1stMinID->m_ID)
         {
             if(teamInCountry->m_secondThirdMax1STR-> m_strength == teamInCountry->m_secondThird2ndMinID->m_strength)
             {
                 m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
             }
             else
             {
                 m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
             }
         }
         else
         {
             if(teamInCountry->m_secondThirdMax1STR->m_strength == teamInCountry->m_secondThird1stMinID->m_strength)
             {
                 m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
             }
             else
             {
                 m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
             }
         }
         max2 = maxg(m22,m23);
         s4 = max1 + max2 + max3;

         //2,0,1

         max1 = maxg(teamInCountry->m_firstThirdMax1STR->m_strength, teamInCountry->m_secondThird1stMinID->m_strength);
         if(teamInCountry->m_secondThirdMax1STR->m_ID == teamInCountry->m_secondThird1stMinID->m_ID)
         {
             max2 = teamInCountry->m_secondThirdMax2STR->m_strength;
         }
         else
         {
             max2 = teamInCountry->m_secondThirdMax1STR->m_strength;
         }
         max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         s5 = max1 + max2 + max3;

         //1,2,0

         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         max2 = maxg(teamInCountry->m_secondThirdMax1STR->m_strength, teamInCountry->m_lastThird1stMinID->m_strength);
         if(teamInCountry->m_lastThirdMax1STR->m_ID == teamInCountry->m_lastThird1stMinID->m_ID)
         {
             max3 = teamInCountry->m_lastThirdMax2STR->m_strength;
         }
         else
         {
             max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         }
         s6 = max1 + max2 + max3;

         //0,2,1

         if(teamInCountry->m_firstThirdMax1ID->m_ID == teamInCountry->m_firstThirdMax1STR->m_ID)
         {
             max1 = teamInCountry->m_firstThirdMax2STR->m_strength;
         }
         else
         {
             max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         }
         max2 = maxg(teamInCountry->m_firstThirdMax1ID->m_strength, teamInCountry->m_secondThirdMax1STR->m_strength);
         max3 = teamInCountry->m_lastThirdMax1STR->m_strength;
         s7 = max1 + max2 + max3;

         //1,0,2

         max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         if(teamInCountry->m_secondThirdMax1ID->m_ID == teamInCountry->m_secondThirdMax1STR->m_ID)
         {
             max2 = teamInCountry->m_secondThirdMax2STR->m_strength;
         }
         else
         {
             max2 = teamInCountry->m_secondThirdMax1STR->m_strength;
         }
         max3 = maxg(teamInCountry->m_secondThirdMax1ID->m_strength, teamInCountry->m_lastThirdMax1STR->m_strength);
         s8 = max1 + max2 + max3;

         //0,1,2

         if(teamInCountry->m_firstThirdMax1ID->m_ID == teamInCountry->m_firstThirdMax1STR->m_ID)
         {
             max1 = teamInCountry->m_firstThirdMax2STR->m_strength;
         }
         else
         {
             max1 = teamInCountry->m_firstThirdMax1STR->m_strength;
         }
         if(teamInCountry->m_secondThirdMin1STR->m_ID == teamInCountry->m_secondThirdMax1ID->m_ID)
         {
             max3 = maxg(teamInCountry->m_secondThirdMax2ID->m_strength, teamInCountry->m_lastThirdMax1STR->m_strength);
         }
         else
         {
             max3 = maxg(teamInCountry->m_secondThirdMax1ID->m_strength, teamInCountry->m_lastThirdMax1STR->m_strength);
         }
         if(teamInCountry->m_secondThirdMin1STR->m_ID == teamInCountry->m_secondThirdMax1ID->m_ID)
         {
             if(teamInCountry->m_secondThirdMax1STR->m_strength == teamInCountry->m_secondThirdMax2ID->m_strength)
             {
                 m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
             }
             else
             {
                 m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
             }
             max2 = maxg(teamInCountry->m_firstThirdMax1ID->m_strength, m22);
         }
         else
         {
             if(teamInCountry->m_secondThirdMax1STR->m_strength == teamInCountry->m_secondThirdMax1ID->m_strength)
             {
                 m22 = teamInCountry->m_secondThirdMax2STR->m_strength;
             }
             else
             {
                 m22 = teamInCountry->m_secondThirdMax1STR->m_strength;
             }
             max2 = maxg(teamInCountry->m_firstThirdMax1ID->m_strength, m22);
         }
         s9 = max1 + max2 + max3;

         //1,1,1
         s10 = get_team_strength(teamId).ans();
         return maxg(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10);
     }


    /*    // -1,-1,-1
    int s1 = get_team_strength(teamId).ans();

    // 2 from t1 -> --,-1,11 OR --,11,-1
    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    if(teamInCountry->m_info->m_firstThirdID->m_treeSize == 2)
    {
        max1 = teamInCountry->m_info->m_secondThird1stMin->m_strength;
        if(teamInCountry->m_info->m_secondThird1stMin->m_ID == teamInCountry->m_info->m_secondThirdMax1->m_ID)
        {
            if(teamInCountry->m_info->m_secondThirdID->m_treeSize == 2)
            {

            }
        }
    }
    if(teamInCountry->m_info->m_firstThirdMax1->m_strength >= teamInCountry->m_info->m_secondThird1stMin->m_strength)
    {
        max1 = teamInCountry->m_info->m_firstThirdMax1->m_strength;
    }
    else
    {
        max1 = teamInCountry->m_info->m_secondThird1stMin->m_strength;
    }
    // 2 from t2 -> 11,--,-1 OR -1,--,11
    // 2 from t3 -> 11,-1,-- OR -1,11,--


        if(team->m_info->m_firstThirdID->m_treeSize > 2)
        {
            // 3 from t1
            if(team->m_info->m_secondThirdID->m_treeSize > 2)
            {
                // 3 from t2
                if(team->m_info->m_lastThirdID->m_treeSize > 2)
                {
                    // 3 from t3

                }
            }
        }
        	return strength;
*/





}



