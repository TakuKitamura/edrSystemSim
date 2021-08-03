#include "EDRSystemBlock.h"

#define STATE__START__STATE 0
#define STATE__PacketCaptureState 1
#define STATE__PacketParseState 2
#define STATE__state0 3
#define STATE__STOP__STATE 4

void *mainFunc__EDRSystemBlock(void *arg){
  int64_t crashTime = 0;
  int crashFlag = 0;
  int writeToEdrFlag = 2;
  can_frame packet = INIT_PACKET;
  VerificationType verificationResult = INIT_VERIFICATION_RESLUT;
  
  int __currentState = STATE__START__STATE;
  
  char * __myname = (char *)arg;
  
  pthread_cond_init(&__myCond__EDRSystemBlock, NULL);
  
  fillListOfRequests(&__list__EDRSystemBlock, __myname, &__myCond__EDRSystemBlock, &__mainMutex);
  //printf("my name = %s\n", __myname);
  
  /* Main loop on states */
  while(__currentState != STATE__STOP__STATE) {
    switch(__currentState) {
      case STATE__START__STATE: 
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__PacketCaptureState: 
      makeNewRequest(&__req0__EDRSystemBlock, 23, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
      addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      if (writeToEdrFlag == 1) {
        makeNewRequest(&__req1__EDRSystemBlock, 27, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
       if (__returnRequest__EDRSystemBlock == &__req0__EDRSystemBlock) {
        packet = EDRSystemBlock__packetCapture();
        __currentState = STATE__PacketParseState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        __currentState = STATE__STOP__STATE;
        
      }
      break;
      
      case STATE__PacketParseState: 
      verificationResult = EDRSystemBlock__validatePacketData(packet.can_id, packet.can_dlc, packet.can_data);
      __currentState = STATE__state0;
      break;
      
      case STATE__state0: 
      if (!writeToEdrFlag == 0) {
        __currentState = STATE__STOP__STATE;
        break;
      }
      __currentState = STATE__PacketCaptureState;
      break;
      
    }
  }
  //printf("Exiting = %s\n", __myname);
  return NULL;
}

