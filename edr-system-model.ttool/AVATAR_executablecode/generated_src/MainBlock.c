#include "MainBlock.h"

#define STATE__START__STATE 0
#define STATE__MainState 1
#define STATE__STOP__STATE 2

void MainBlock__printHelloWorld() {
  __userImplemented__MainBlock__printHelloWorld();
}


void *mainFunc__MainBlock(void *arg){
  int period = 2;
  
  int __currentState = STATE__START__STATE;
  
  char * __myname = (char *)arg;
  
  pthread_cond_init(&__myCond__MainBlock, NULL);
  
  fillListOfRequests(&__list__MainBlock, __myname, &__myCond__MainBlock, &__mainMutex);
  //printf("my name = %s\n", __myname);
  
  /* Main loop on states */
  while(__currentState != STATE__STOP__STATE) {
    switch(__currentState) {
      case STATE__START__STATE: 
      __currentState = STATE__MainState;
      break;
      
      case STATE__MainState: 
      waitFor((period)*1000000, (period)*1000000);
      MainBlock__printHelloWorld();
      __currentState = STATE__MainState;
      break;
      
    }
  }
  //printf("Exiting = %s\n", __myname);
  return NULL;
}

