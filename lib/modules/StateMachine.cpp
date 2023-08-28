
#include "StateMachine.h"
CONFIG_ERROR();

err_t State_M::fsm_process(fsm_handle_t* fsmHandle) {
    //Verificar cambio de estado
    if ((fsmHandle->currentState != fsmHandle->nextState) && (fsmHandle->nextState != NULL)) {
        if(fsmHandle->printDebug) {
            //printf("%s: %s -> %s\n", fsmHandle->name, fsmHandle->currentState == NULL ? "NULL" : fsmHandle->currentState->name,
                  // fsmHandle->nextState->name);
        }
        //Ejecutar cambio de estado
        if ((fsmHandle->currentState != NULL) && (fsmHandle->currentState->f_ptr != NULL)) {
            fsmHandle->currentState->f_ptr(ACTION_EXIT);
        }
        fsmHandle->currentState = fsmHandle->nextState;
        if (fsmHandle->currentState->f_ptr != NULL) {
            fsmHandle->currentState->f_ptr(ACTION_ENTRY);
        }
    } else {
        if (fsmHandle->currentState != NULL && fsmHandle->currentState->f_ptr != NULL) {
            fsmHandle->currentState->f_ptr(ACTION_PROCESS);
        }
    }
    NOERR();
}

err_t State_M::fsm_changeState(fsm_handle_t* fsmHandle, fsm_stateHandle_t* nextState) {
    fsmHandle->nextState = nextState;
    NOERR();
}

err_t State_M::fsm_reset(fsm_handle_t* fsmHandle) {
    fsmHandle->currentState = NULL;
    fsmHandle->nextState = NULL;
    NOERR();
}
