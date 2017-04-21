#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H

// Public server state.
// This information changes during the game.
class CGlobalState
{
public:
    CGlobalState();
    
    unsigned int m_Round;
    unsigned int m_Cycle;

    unsigned int m_Score[4];
};

#endif
