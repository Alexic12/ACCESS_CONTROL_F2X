#include "fsm.h"


CONFIG_ERROR();

//Auxiliary Operation Variables
volatile bool Serial_CMD = false;


//OBJECT DECLARATION FOR ALL PROCESSES

EthernetComms E; //Ethernet Communications Object
Serial_uart SU;

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
        Serial.println("F.INIT, Entry");

    } else if (action == ACTION_PROCESS) {

        Serial.println("F.INIT, Process");
        //Initialize Ethernet communications
        E.conn_init();
        E.connect_reader();
        delay(1000);
        State_M::fsm_changeState(&Machine_FSM, &FSM_diag);
       

    } else if (action == ACTION_EXIT) {  // 1 single time

        Serial.println("F.INIT, Exit");
        delay(1000);
    }
    NOERR();
}

err_t fsm::F_diag(fsm_action action) {
    if (action == ACTION_ENTRY) {  // 1 single time

        delay(2000);
        Serial.println("F.DIAG, Entry");

    } else if (action == ACTION_PROCESS) {

        Serial.println("F.DIAG, Process");
        delay(1000);
        State_M::fsm_changeState(&Machine_FSM, &FSM_oper);
       
    } else if (action == ACTION_EXIT) {  // 1 single time

        Serial.println("F.DIAG, Exit");
        delay(1000);
    }
    NOERR();
}


err_t fsm::F_oper(fsm_action action) {
    if (action == ACTION_ENTRY) {  // 1 single time

        delay(2000);
        Serial.println("F.OPER, Entry");

    } else if (action == ACTION_PROCESS) {

        //Serial.println("F.OPER, Process");
        //R.send_cmd_s(TAG_INV);
        byte hexArray[] = {0x04, 0x00, 0x50, 0xd7, 0x8};
        byte read_antenna_1[] = {0x0b, 0x00, 0x01, 0x04, 0x00, 0x00, 0x06, 0x00, 0x80, 0x14, 0xfd, 0xfe};
        byte read_all[] = {0x04, 0x00, 0x0f, 0xa5, 0xa2};
        if(Serial.available()>0){
            SU.ReadSerial();
           
            //Serial_CMD = False;
            
        }
        delay(100);

    } else if (action == ACTION_EXIT) {  // 1 single time

        Serial.println("F.OPER, Exit");

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