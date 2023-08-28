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
    //static err_t O_menu_pay(fsm_action action);
    //static err_t O_ver_pay(fsm_action action);
    //static err_t O_succ_trans(fsm_action action);
    //static err_t O_pend_trans(fsm_action action);
    //static err_t O_wrist_chk(fsm_action action);
    //static err_t O_brief(fsm_action action);

    // Function to get the state based on the selected menu item
    static err_t get_state(fsm_stateHandle_t& state);

   private:
    // FSM handle
    static fsm_handle_t Machine_FSM;
    // FSM States
    static fsm_stateHandle_t FSM_init;
    static fsm_stateHandle_t FSM_diag;
    static fsm_stateHandle_t FSM_oper;
    //static fsm_stateHandle_t UI_menu_pay;
    //static fsm_stateHandle_t UI_ver_pay;
    //static fsm_stateHandle_t UI_succ_trans;
    //static fsm_stateHandle_t UI_pend_trans;
    //static fsm_stateHandle_t UI_wrist_chk;
    //static fsm_stateHandle_t UI_brief;
    // Variable for storing the menus
};

#endif