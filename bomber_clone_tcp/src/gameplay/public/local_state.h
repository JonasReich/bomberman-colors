#ifndef LOCAL_STATE_H
#define LOCAL_STATE_H

// Private client state, invisible to other clients.
// This information remains unchanged during the game.
class CLocalState
{
public:
    CLocalState();
    
    int m_PlayerNr;
};

#endif
