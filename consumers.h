//James Lee (RedId:820655947)
#ifndef CONSUMERS_H
#define CONSUMERS_H

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "structs.h"
#include <string.h>
#include "production.h"
using namespace std;

class ConsumerClass{
    public:
        string &consumerName;
        Belt* currentBelt;

        //Int Variables
        int speed, frogsEaten, escargotEaten, totalEaten;

        ConsumerClass(Belt* currentBelt, string consumerName, int speed);
        ~ConsumerClass();
};

#endif