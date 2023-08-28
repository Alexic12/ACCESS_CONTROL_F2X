#include "fsm.h"


CONFIG_ERROR();

// Function define so the states recognize them
err_t F_init(fsm_action action);
err_t F_diag(fsm_action action);
err_t F_oper(fsm_action action);
//err_t O_menu_pay(fsm_action action);
//err_t O_ver_pay(fsm_action action);
//err_t O_succ_trans(fsm_action action);
//err_t O_pend_trans(fsm_action action);
//err_t O_wrist_chk(fsm_action action);
//err_t O_brief(fsm_action action);

// FSM Handler init
fsm_handle_t fsm::Machine_FSM = {{"FSM"}, NULL, NULL, false};
// FSM states init
fsm_stateHandle_t fsm::FSM_init = {{"FSM_init"}, F_init};
fsm_stateHandle_t fsm::FSM_diag = {{"FSM_diag"}, F_diag};
fsm_stateHandle_t fsm::FSM_oper = {{"FSM_oper"}, F_oper};
//fsm_stateHandle_t fsm::UI_menu_pay = {{"menu_pay"}, O_menu_pay};
//fsm_stateHandle_t fsm::UI_ver_pay = {{"ver_pay"}, O_ver_pay};
//fsm_stateHandle_t fsm::UI_succ_trans = {{"succ_trans"}, O_succ_trans};
//fsm_stateHandle_t fsm::UI_pend_trans = {{"pend_trans"}, O_pend_trans};
//fsm_stateHandle_t fsm::UI_wrist_chk = {{"wrist_chk"}, O_wrist_chk};
//fsm_stateHandle_t fsm::UI_brief = {{"brief"}, O_brief};

// Counter for menu item selected
uint8_t cont_menu = -1;

// State functions
err_t fsm::F_init(fsm_action action) {
    if (action == ACTION_ENTRY) {  // 1 single time

        delay(2000);
        Serial.print("F.INIT, Entry");

    } else if (action == ACTION_PROCESS) {

        Serial.print("F.INIT, Process");
        delay(1000);

        State_M::fsm_changeState(&Machine_FSM, &FSM_diag);
       

    } else if (action == ACTION_EXIT) {  // 1 single time

     Serial.print("F.INIT, Exit");
        delay(1000);
    }
    NOERR();
}

err_t fsm::F_diag(fsm_action action) {
    if (action == ACTION_ENTRY) {  // 1 single time

        delay(2000);
        Serial.print("F.DIAG, Entry");

    } else if (action == ACTION_PROCESS) {

        Serial.print("F.DIAG, Process");
        delay(1000);
        State_M::fsm_changeState(&Machine_FSM, &FSM_oper);
       
    } else if (action == ACTION_EXIT) {  // 1 single time

        Serial.print("F.DIAG, Exit");
        delay(1000);
    }
    NOERR();
}


err_t fsm::F_oper(fsm_action action) {
    if (action == ACTION_ENTRY) {  // 1 single time

        delay(2000);
        Serial.print("F.OPER, Entry");

    } else if (action == ACTION_PROCESS) {

        Serial.print("F.OPER, Process");
        delay(1000);
       

    } else if (action == ACTION_EXIT) {  // 1 single time

        Serial.print("F.OPER, Exit");
        delay(1000);
    }
    NOERR();
}

err_t fsm::runFSM() {
    State_M::fsm_process(&Machine_FSM);
    NOERR();
}

err_t fsm::initFSM() {
    State_M::fsm_changeState(&Machine_FSM, &FSM_init);
    NOERR();
}