#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

#include "../core_libs/error.h"



typedef enum {
    ACTION_ENTRY,
    ACTION_PROCESS,
    ACTION_EXIT
}fsm_action;

typedef struct {
    const char* name[50];
    err_t (*f_ptr)(fsm_action); //Pointer a función
}fsm_stateHandle_t;

typedef struct {
    const char* name[50];
    fsm_stateHandle_t* currentState;
    fsm_stateHandle_t* nextState;
    bool printDebug;
}fsm_handle_t;

class State_M{
    public:

    static err_t fsm_process(fsm_handle_t* fsmHandle);
    static err_t fsm_changeState(fsm_handle_t* fsmHandle,fsm_stateHandle_t* nextState);
    static err_t fsm_reset(fsm_handle_t* fsmHandle);

    private:


};



#endif 
