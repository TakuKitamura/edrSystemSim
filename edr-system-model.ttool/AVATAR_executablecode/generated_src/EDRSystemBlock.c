#include "EDRSystemBlock.h"


// Header code defined in the model

// End of header code defined in the model

#define STATE__START__STATE 0
#define STATE__EDRSystemStartState 1
#define STATE__PacketCaptureState 2
#define STATE__CheckRecordInEDRFlagState 3
#define STATE__EDRSystemEndState 4
#define STATE__PacketParseState 5
#define STATE__CheckValidationResultState 6
#define STATE__RecordInEDRState 7
#define STATE__CheckRecordInEDRResultState 8
#define STATE__WroteEventToRecordState 9
#define STATE__EDRErrorState 10
#define STATE__NormalLoopState 11
#define STATE__ValidationErrorState 12
#define STATE__STOP__STATE 13

void *mainFunc__EDRSystemBlock(void *arg){
  int recordInEDRFlag = 0;
  can_frame packet = INIT_PACKET;
  fstar_int32 validationResult = INIT_VALIDATION_RESLUT;
  int recordInEDRResult = 0;
  
  int __currentState = STATE__START__STATE;
  
  char * __myname = (char *)arg;
  
  pthread_cond_init(&__myCond__EDRSystemBlock, NULL);
  
  fillListOfRequests(&__list__EDRSystemBlock, __myname, &__myCond__EDRSystemBlock, &__mainMutex);
  //printf("my name = %s\n", __myname);
  
  /* Main loop on states */
  while(__currentState != STATE__STOP__STATE) {
    switch(__currentState) {
      case STATE__START__STATE: 
      traceStateEntering(__myname, "__StartState");
      __currentState = STATE__EDRSystemStartState;
      break;
      
      case STATE__EDRSystemStartState: 
      traceStateEntering(__myname, "EDRSystemStartState");
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__PacketCaptureState: 
      traceStateEntering(__myname, "PacketCaptureState");
      __currentState = STATE__CheckRecordInEDRFlagState;
      break;
      
      case STATE__CheckRecordInEDRFlagState: 
      traceStateEntering(__myname, "CheckRecordInEDRFlagState");
      if (recordInEDRFlag == 1) {
        makeNewRequest(&__req0__EDRSystemBlock, 48, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (recordInEDRFlag == 0) {
        makeNewRequest(&__req1__EDRSystemBlock, 77, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
      traceRequest(__myname, __returnRequest__EDRSystemBlock);
       if (__returnRequest__EDRSystemBlock == &__req0__EDRSystemBlock) {
        __currentState = STATE__EDRSystemEndState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        packet = EDRSystemBlock__packetCapture();
        traceVariableModification("EDRSystemBlock", "packet", packet,1);
        __currentState = STATE__PacketParseState;
        
      }
      break;
      
      case STATE__EDRSystemEndState: 
      traceStateEntering(__myname, "EDRSystemEndState");
      __currentState = STATE__STOP__STATE;
      break;
      
      case STATE__PacketParseState: 
      traceStateEntering(__myname, "PacketParseState");
      validationResult = EDRSystemBlock__validatePacketData(packet.can_id, packet.can_dlc, packet.data);
      traceVariableModification("EDRSystemBlock", "validationResult", validationResult,1);
      __currentState = STATE__CheckValidationResultState;
      break;
      
      case STATE__CheckValidationResultState: 
      traceStateEntering(__myname, "CheckValidationResultState");
      if (validationResult.struct_error.codde > 0) {
        makeNewRequest(&__req0__EDRSystemBlock, 53, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (validationResult.struct_error.code == 0) {
        makeNewRequest(&__req1__EDRSystemBlock, 65, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
      traceRequest(__myname, __returnRequest__EDRSystemBlock);
       if (__returnRequest__EDRSystemBlock == &__req0__EDRSystemBlock) {
        __currentState = STATE__ValidationErrorState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        __currentState = STATE__RecordInEDRState;
        
      }
      break;
      
      case STATE__RecordInEDRState: 
      traceStateEntering(__myname, "RecordInEDRState");
      recordInEDRResult = EDRSystemBlock__recordInEDR(packet.can_id, packet.can_dlc, packet.data);
      traceVariableModification("EDRSystemBlock", "recordInEDRResult", recordInEDRResult,0);
      __currentState = STATE__CheckRecordInEDRResultState;
      break;
      
      case STATE__CheckRecordInEDRResultState: 
      traceStateEntering(__myname, "CheckRecordInEDRResultState");
      if (recordInEDRResult == 2) {
        makeNewRequest(&__req0__EDRSystemBlock, 58, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (recordInEDRResult == 1) {
        makeNewRequest(&__req1__EDRSystemBlock, 62, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (recordInEDRResult == 0) {
        makeNewRequest(&__req2__EDRSystemBlock, 87, IMMEDIATE, 0, 0, 0, 0, __params2__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req2__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
      traceRequest(__myname, __returnRequest__EDRSystemBlock);
       if (__returnRequest__EDRSystemBlock == &__req0__EDRSystemBlock) {
        __currentState = STATE__EDRErrorState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        __currentState = STATE__WroteEventToRecordState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req2__EDRSystemBlock) {
        __currentState = STATE__NormalLoopState;
        
      }
      break;
      
      case STATE__WroteEventToRecordState: 
      traceStateEntering(__myname, "WroteEventToRecordState");
      recordInEDRFlag = 1;
      traceVariableModification("EDRSystemBlock", "recordInEDRFlag", recordInEDRFlag,0);
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__EDRErrorState: 
      traceStateEntering(__myname, "EDRErrorState");
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__NormalLoopState: 
      traceStateEntering(__myname, "NormalLoopState");
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__ValidationErrorState: 
      traceStateEntering(__myname, "ValidationErrorState");
      __currentState = STATE__PacketCaptureState;
      break;
      
    }
  }
  //printf("Exiting = %s\n", __myname);
  return NULL;
}

