#ifndef AGENTSTATE_H
#define AGENTSTATE_H
#include "configuration.h"
class AgentState
{
public:
    AgentState(Configuration config,bool isPacman);
    bool operator==(const AgentState& other);
    bool operator!=(const AgentState& other);
    AgentState(const AgentState& other);
    QPointF getPosition();
    Direction getDireciton();
    Configuration getConfiguration() const;
    void setConfiguration(Configuration conf);
    int getScarryTimer();
    void setScarryTimer(int time);
    Configuration getStartConfiguration();
private:
    Configuration start;
    Configuration current;
    bool isPacman;
    int scarryTimer = 0;
    int numCarrying = 0;
    int numReturned = 0;
};

#endif // AGENTSTATE_H
