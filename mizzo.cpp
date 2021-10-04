//James Lee (RedId:820655947)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>

#include "producers.h"
#include "consumers.h"
#include "belt.h"
#include "structs.h"


using namespace std;

void* produceFrogs(void* Ptr);
void* produceEscargot(void* Ptr);
void* consume(void* Ptr);

int main(int argc, char **argv) 
{
    //Initialize the int variables we will be using throughout this code.
    int frogSpeed = 0;
    int frogFlag = 0;
    int escargotSpeed = 0;
    int escargotFlag = 0;
    int ethelSpeed = 0;
    int ethelFlag = 0;
    int lucySpeed = 0;
    int lucyFlag = 0;

    //Initialize the pthreads we will be using.
    pthread_t frog;
    pthread_t escargot;
    pthread_t lucy;
    pthread_t ethel;

    int flag = 0;

    while((flag = getopt(argc, argv, "f:e:E:L:")) != -1){
        switch(flag){
            case 'f':
                frogSpeed = atoi(optarg);
                frogFlag = 1;
                printf("%d", frogSpeed);
                break;
            case 'e':
                escargotSpeed = atoi(optarg);
                escargotFlag = 1;
                printf("%d", escargotSpeed);
                break;
            case 'E':
                ethelSpeed = atoi(optarg);
                ethelFlag = 1;
                printf("%d", ethelSpeed);
                break;
            case 'L':
                lucySpeed = atoi(optarg);
                lucyFlag = 1;
                printf("%d", lucySpeed);
                break;
            default:
                printf("Error occurs");
                exit(1);
        }
    }

    //This creates our belt that we will be using throughout the code.
    Belt *currentBelt = new Belt();

    //We now create the consumers, and following #4 on the assignment, Lucy is made first.
    ConsumerClass* Lucy = new ConsumerClass(currentBelt, "Lucy", lucySpeed));
    ConsumerClass* Ethel = new ConsumerClass(currentBelt,"Ethel", ethelSpeed);

    //We now create the Producer
    Producers* frogProduce = new Producers(currentBelt, frogSpeed);
    Producers* escargotProduce = new Producers(currentBelt, escargotSpeed);

    //Create Pthreads for consumers
    pthread_create(&lucy, NULL, consume, Lucy);
    pthread_create(&ethel, NULL, consume, Ethel);

    //Create Pthreads for Candy 
    pthread_create(&frog, NULL, produceFrogs, (void *) frogProduce);
    pthread_create(&escargot, NULL, produceEscargot, (void *) escargotProduce);

    //Join all the threads
    pthread_join(lucy, NULL);
    pthread_join(ethel, NULL);
    pthread_join(frog, NULL);
    pthread_join(escargot, NULL);

    sem_wait(&(currentBelt->limit));

    //Production report
    int totalProduced[] = {frogProduce->totalAmountProduced, escargotProduce->totalAmountProduced};
    int* consumedFrogs = new int(2);
    int* consumedEscargots = new int(2);
    *consumedFrogs = Lucy->frogsEaten;
    *(consumedFrogs+ 1) = Ethel->frogsEaten;
    *consumedEscargots = Lucy->escargotEaten;
    *(consumedEscargots + 1) = Ethel->escargotEaten;
    int* totalConsumed[] = {consumedFrogs, consumedEscargots};
    io_production_report(totalProduced, totalConsumed);
}
 
void* produceFrogs(void* Ptr);
    Producer* producedFrogs = (Producer*) ptr;

    while(1){
        //This will allow us to enter the critical region.
        sem_wait(&(producedFrogs->currentBelt->slotsAvailable));
        sem_wait(&(producedFrogs->currentBelt->mutex));

        //Check to see if the max of 100 was reached, and will break if it has.
        if(producedFrogs->currentBelt->totalAmountProduced == MAX_CANDY){
            sem_post(&(producedFrogs->currentBelt->mutex));
            sem_post(&(producedFrogs->currentBelt->itemOnBelt));
            break;
        }

        //If we have space on the belt still, we will go through this code to add more candy.
        if(producedFrogs->currentBelt->push(FrogBite)){
            producedFrogs->currentBelt->frogAmount++;
            producedFrogs->totalAmountProduced++;
            producedFrogs->currentCounter = producedFrogs->currentBelt->frogAmount + producedEscargot->currentBelt->escargotAmount;

            //Setting up the onbelt and such in order to use the io add type.
            int onBelt[] = {producedFrogs->currentBelt->frogAmount, producedEscargot->currentBelt->escargotAmount};
            int produced[] = {producedFrogs->totalAmountProduced, producedEscargot->totalAmountProduced};
            ProductType frogCandy = FrogBite;
            io_add_type(frogCandy, onBelt, produced);

            //Checks to see if 100 candies were created second checker after adding a candy.
            if(producedFrogs->currentBelt->totalProduce == MAX_CANDY){
                sem_post(&(producedFrogs->currentBelt->mutex));
                sem_post(&(producedFrogs->currentBelt->itemOnBelt));

                break;
            }

            //Checks to see if there are currently 3 frogs on the belt after adding a candy.
            if(producedFrogs->currentBelt->frogAmount == 3){
                sem_post(&(producedFrogs->currentBelt->mutex));
                sem_post(&(producedFrogs->currentBelt->itemOnBelt));
                sem_wait(&(producedFrogs->currentBelt->frogMax));
            }

            //Otherwise do this.
            else{
                sem_post(&(producedFrogs->currentBelt->mutex));
                sem_post(&(producedFrogs->currentBelt->itemOnBelt));
            }

            usleep((producedFrogs->producerSpeed) * 1000)
        }

    }

void* produceEscargot(void* Ptr){
    Producer* producedEscargot = (Producer*) ptr;

    while(1){
        //This will allow us to enter the critical region.
        sem_wait(&(producedEscargot->currentBelt->slotsAvailable));
        sem_wait(&(producedEscargot->currentBelt->mutex));

        //Check to see if the max of 100 was reached, and will break if it has.
        if(producedEscargot->currentBelt->totalAmountProduced == MAX_CANDY){
            sem_post(&(producedEscargot->currentBelt->mutex));
            sem_post(&(producedEscargot->currentBelt->itemOnBelt));
            break;
        }

        //If we have space on the belt still, we will go through this code to add more candy.
        if(producedEscargot->currentBelt->push(FrogBite)){
            producedEscargot->currentBelt->frogAmount++;
            producedEscargot->totalAmountProduced++;
            producedEscargot->currentCounter = producedFrogs->currentBelt->frogAmount + producedEscargot->currentBelt->escargotAmount;

            //Setting up the onbelt and such in order to use the io add type.
            int onBelt[] = {producedFrogs->currentBelt->frogAmount, producedEscargot->currentBelt->escargotAmount};
            int produced[] = {producedFrogs->totalAmountProduced, producedEscargot->totalAmountProduced};
            ProductType escargotCandy = Escargot;
            io_add_type(escargotCandy, onBelt, produced);

            //Checks to see if 100 candies were created second checker after adding a candy.
            if(producedEscargot->currentBelt->totalProduce == MAX_CANDY){
                sem_post(&(producedEscargot->currentBelt->mutex));
                sem_post(&(producedEscargot->currentBelt->itemOnBelt));

                break;
            }
            //Otherwise do this.
            else{
                sem_post(&(producedEscargot->currentBelt->mutex));
                sem_post(&(producedEscargot->currentBelt->itemOnBelt));
            }

            usleep((producedEscargot->producerSpeed) * 1000)
        }

    }
}


//Consume function
void* consume(void* Ptr){
    Consumer *consumeCandy = (Consumer*) Ptr; 

    string name = consumeCandy->consumerName; 

    while(1) {
        sem_wait(&(consumeCandy->currentBelt->itemOnBelt)); 
        sem_wait(&(consumeCandy->currentBelt->mutex)); 

        // This starting if is to ensure other thread leaves.
        if(consumeCandy->currentBelt->totalConsume == MAX_CANDY) {
            break;
        }

        //If you can consume a candy, then it will start consuming.
        if(consumeCandy->currentBelt->itemOnBelt != 0) { 
            int candyConsumed = consumeCandy->currentBelt->pop(); 

            //This is for when the candy is an Escargot.
            if(candyConsumed == Escargot){
                consumeCandy->escargotEaten++;
                consumeCandy->currentBelt->escargotAmount--;
                int currentTotal = consumeCandy -> conveyor -> escargots + consume-> conveyor -> frogs;
                int onBelt[] = {consumeCandy->currentBelt->frogsEaten, consumeCandy->currentBelt->escargotEaten};
                int consumed[] = {consumeCandy->totalEaten, consumeCandy->totalEaten};
                ProductType escargotCandy = Escargot;
                io_remove_type(name, escargotCandy, onBelt, consumed);
            }

            //This is for when the candy is a frog.
            if(candyConsumed == FrogBite){ 
            consumeCandy->frogsEaten++;
            consumeCandy->currentBelt->frogAmount--;
            int currentTotal = consumeCandy->currentBelt->escargotAmount + consumeCandy->currentBelt->frogAmount;

            //If there isn't 3 anymore, it will create more candy.
            if(consumeCandy->currentBelt->frogAmount == 2) 
                sem_post(&(consumeCandy->currentBelt->frogMax)); 
            }
        }
            
            if(consumeCandy->currentBelt->totalEaten== MAX_CANDY) { 
                sem_post(&(consumeCandy->currentBelt->mutex)); 
                sem_post(&(consumeCandy->currentBelt->limit)); 
                break;
            }

            //We will let one go then tell the semaphore that there is a spot available.
            else {
                sem_post(&(consumeCandy->currentBelt->mutex));
                sem_post(&(consumeCandy->currentBelt->slotsAvailable)); 
                usleep((consumeCandy->speed) * 1000);  
            }
    }
    
}