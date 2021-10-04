//James Lee (RedId:820655947)
#include "producers.h"
#include <unistd.h>
#include <semaphore.h>
#include "structs.h"
using namespace std;

//Constructor for the producer
Producers::Producers((Conveyer*) belt, int speed){
    currentBelt = belt;
    producerSpeed = speed;
    totalAmountProduced = 0;
    currentCounter = 0;
}

//Deconstructor
Producers::~Producers(){}