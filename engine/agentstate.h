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
    QPointF getPosition() const;
    Direction getDireciton() const;
    void setPosition(QPointF);
    Configuration getConfiguration() const;
    void setConfiguration(Configuration conf);
    int getScarryTimer() const;
    void setScarryTimer(int time);
    Configuration getStartConfiguration() const;
private:
    Configuration start;
    Configuration current;
    bool isPacman;
    int scarryTimer = 0;
};

#endif // AGENTSTATE_H
