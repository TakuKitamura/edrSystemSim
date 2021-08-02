#ifndef MainBlock_H
#define MainBlock_H
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#include "request.h"
#include "syncchannel.h"
#include "request_manager.h"
#include "debug.h"
#include "defs.h"
#include "mytimelib.h"
#include "random.h"
#include "tracemanager.h"
#include "main.h"

extern void *mainFunc__MainBlock(void *arg);
__attribute__((unused)) request __req0__MainBlock;
__attribute__((unused))int *__params0__MainBlock[0];
__attribute__((unused))setOfRequests __list__MainBlock;
__attribute__((unused))pthread_cond_t __myCond__MainBlock;
__attribute__((unused))request *__returnRequest__MainBlock;

#endif
