#include "EDRSystemBlock.h"

#define STATE__START__STATE 0
#define STATE__EDRSystemStartState 1
#define STATE__PacketCaptureState 2
#define STATE__PacketParseState 3
#define STATE__ParseSpeedState 4
#define STATE__CheckValidationResultState 5
#define STATE__RecordInEDRState 6
#define STATE__CheckRecordInEDRResultState 7
#define STATE__WroteEventToRecordState 8
#define STATE__EDRSystemEndState 9
#define STATE__EDRErrorState 10
#define STATE__NormalLoopState 11
#define STATE__ValidationErrorState 12
#define STATE__ParseDoorState 13
#define STATE__ParseIndicatorState 14
#define STATE__STOP__STATE 15

void *mainFunc__EDRSystemBlock(void *arg){
  can_frame canFrame;
  uint32_t canID = 0;
  uint8_t canDLC = 0;
  uint8_t* data;
  fstar_int32_array speed;
  fstar_uint8 indicator;
  fstar_uint8 door;
  uint32_t code = 0;
  uint8_t* message;
  int32_t recordInEDRResult = 0;
  
  int __currentState = STATE__START__STATE;
  
  char * __myname = (char *)arg;
  
  pthread_cond_init(&__myCond__EDRSystemBlock, NULL);
  
  fillListOfRequests(&__list__EDRSystemBlock, __myname, &__myCond__EDRSystemBlock, &__mainMutex);
  //printf("my name = %s\n", __myname);
  
  /* Main loop on states */
  while(__currentState != STATE__STOP__STATE) {
    switch(__currentState) {
      case STATE__START__STATE: 
      __currentState = STATE__EDRSystemStartState;
      break;
      
      case STATE__EDRSystemStartState: 
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__PacketCaptureState: 
      canFrame = packetCapture();
      canID = canFrame.can_id;
      canDLC = canFrame.can_dlc;
      data = canFrame.data;
      __currentState = STATE__PacketParseState;
      break;
      
      case STATE__PacketParseState: 
      if (canID == 0x19b) {
        makeNewRequest(&__req0__EDRSystemBlock, 931, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (canID == 0x188) {
        makeNewRequest(&__req1__EDRSystemBlock, 935, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (canID == 0x1b4) {
        makeNewRequest(&__req2__EDRSystemBlock, 939, IMMEDIATE, 0, 0, 0, 0, __params2__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req2__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
       if (__returnRequest__EDRSystemBlock == &__req0__EDRSystemBlock) {
        __currentState = STATE__ParseDoorState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        __currentState = STATE__ParseIndicatorState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req2__EDRSystemBlock) {
        __currentState = STATE__ParseSpeedState;
        
      }
      break;
      
      case STATE__ParseSpeedState: 
      speed = parseSpeed(canIDcanDLCdata);
      code = speed.struct_error.code;
      message = speed.struct_error.message;
      __currentState = STATE__CheckValidationResultState;
      break;
      
      case STATE__CheckValidationResultState: 
      if (code > 0) {
        makeNewRequest(&__req0__EDRSystemBlock, 877, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (code == 0) {
        makeNewRequest(&__req1__EDRSystemBlock, 881, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
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
        __currentState = STATE__ValidationErrorState;
        
      }
      else  if (__returnRequest__EDRSystemBlock == &__req1__EDRSystemBlock) {
        __currentState = STATE__RecordInEDRState;
        
      }
      break;
      
      case STATE__RecordInEDRState: 
      recordInEDRResult = recordInEDR(canIDspeed, indicator, door);
      __currentState = STATE__CheckRecordInEDRResultState;
      break;
      
      case STATE__CheckRecordInEDRResultState: 
      if (recordInEDRResult == 2) {
        makeNewRequest(&__req0__EDRSystemBlock, 952, IMMEDIATE, 0, 0, 0, 0, __params0__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req0__EDRSystemBlock);
      }
      if (recordInEDRResult == 1) {
        makeNewRequest(&__req1__EDRSystemBlock, 956, IMMEDIATE, 0, 0, 0, 0, __params1__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req1__EDRSystemBlock);
      }
      if (recordInEDRResult == 0) {
        makeNewRequest(&__req2__EDRSystemBlock, 961, IMMEDIATE, 0, 0, 0, 0, __params2__EDRSystemBlock);
        addRequestToList(&__list__EDRSystemBlock, &__req2__EDRSystemBlock);
      }
      if (nbOfRequests(&__list__EDRSystemBlock) == 0) {
        debug2Msg(__myname, "No possible request");
        __currentState = STATE__STOP__STATE;
        break;
      }
      __returnRequest__EDRSystemBlock = executeListOfRequests(&__list__EDRSystemBlock);
      clearListOfRequests(&__list__EDRSystemBlock);
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
      __currentState = STATE__EDRSystemEndState;
      break;
      
      case STATE__EDRSystemEndState: 
      __currentState = STATE__STOP__STATE;
      break;
      
      case STATE__EDRErrorState: 
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__NormalLoopState: 
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__ValidationErrorState: 
      __currentState = STATE__PacketCaptureState;
      break;
      
      case STATE__ParseDoorState: 
      door = parseDoor(canIDcanDLCdata);
      code = door.struct_error.code;
      message = door.struct_error.message;
      __currentState = STATE__CheckValidationResultState;
      break;
      
      case STATE__ParseIndicatorState: 
      indicator = parseIndicator(canIDcanDLCdata);
      code = indicator.struct_error.code;
      message = indicator.struct_error.message;
      __currentState = STATE__CheckValidationResultState;
      break;
      
    }
  }
  //printf("Exiting = %s\n", __myname);
  return NULL;
}

