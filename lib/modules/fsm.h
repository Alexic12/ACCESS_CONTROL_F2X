#ifndef _FSM_H
#define _FSM_H

//#include "../program.h"
#include "StateMachine.h"
#include <Arduino.h>


class fsm {
   public:
    // FSM init/run functions
    static err_t runFSM();
    static err_t initFSM();
    // FSM state functions
    static err_t F_init(fsm_action action);
    static err_t F_diag(fsm_action action);
    static err_t F_oper(fsm_action action);


    // Function to get the state based on the selected menu item
    static err_t get_state(fsm_stateHandle_t& state);

   private:
    // FSM handle
    static fsm_handle_t Machine_FSM;
    // FSM States
    static fsm_stateHandle_t FSM_init;
    static fsm_stateHandle_t FSM_diag;
    static fsm_stateHandle_t FSM_oper;

    // Variable for storing the menus
};

#endif