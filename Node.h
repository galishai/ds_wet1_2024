
#ifndef HW_WET_NODE_H
#define HW_WET_NODE_H

template<class T>
class Node
{
public:
    Node *m_parent;
    Node *m_left;
    Node *m_right;
    T *m_info;
    int m_height;

    ~Node()
    {
        /*if(m_left != nullptr)
        {
            m_left->m_parent = nullptr;
        }
        if(m_right != nullptr)
        {
            m_right->m_parent = nullptr;
        }
        if(m_parent != nullptr)
        {
            if(m_parent->m_left == this)
            {
                m_parent->m_left = nullptr;
            }
            else if(m_parent->m_right == this)
            {
                m_parent->m_right = nullptr;
            }
        }*/
        //delete m_info;
        m_left = nullptr;
        m_right = nullptr;
        m_parent = nullptr;
        m_info = nullptr;
    }

    explicit Node(T *info) : m_parent(nullptr), m_left(nullptr), m_right(nullptr), m_info(info), m_height(0)
    {};

};

static int max(int a, int b)
{
    return a >= b ? a : b;
}

static int absval(int a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

template<class T>
int getHeight(Node<T> *node)
{
    if (node == nullptr)
    {
        return -1;
    }
    return node->m_height;
}

static int total_games(int gamesPlayed, int newTeamGames, int prevGames)
{
    return gamesPlayed - newTeamGames + prevGames;
}


#endif //HW_WET_NODE_H