//James Lee (RedId:820655947)
#ifndef PRODUCERS_H
#define PRODUCERS_H

#include "structs.h"
#include "belt.h"
#include "pthread.h"
#include "io.h"
#include "consumers.h"
#include "production.h"
#include <stdio.h>
#include <semaphore.h>
using namespace std;

class Producers{
    public:
        Producers(Belt* currentBelt, int speed);
        ~Producers();
        int totalAmountProduced;
        int producerSpeed;
        int currentCounter;
        Belt* currentBelt;
};

#endif