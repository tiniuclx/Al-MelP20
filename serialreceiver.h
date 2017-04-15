#ifndef SERIALRECEIVER_H
#define SERIALRECEIVER_H

#include <vector>

class serialReceiver
{
public:
    serialReceiver();
    void decoder(std::vector<bool> message);

private:

};

#endif // SERIALRECEIVER_H
