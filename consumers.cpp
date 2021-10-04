#include "consumers.h"
//James Lee (RedId:820655947)
#include <unistd.h>
#include <semaphore.h>
#include "structs.h"
#include <string.h>
using namespace std;

ConsumerClass::ConsumerClass(Belt* currentBelt, std::string consumerName, int speed){
    this->onBelt = currentBelt;
    this->name = name;
    this->speed = speed;
    
    frogsEaten = 0;
    escargotEaten = 0;
    totalEaten = 0;
}

ConsumerClass::~ConsumerClass(){}