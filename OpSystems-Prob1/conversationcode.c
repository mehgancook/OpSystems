TimerInitTime = 300;
num_pcbs = 6;
currenttime = TimerInitTime;

void initializeIOTrapArray() {
    // arrays are 4 int values and must be unique between both IO Trap Arrays 1 & 2
    // the values must be 1 through MAX_PC
}

void initialize() {
  for(int i; i < num_pcbs; i++){
      // creating the pcbs
      pcb_p pcb = create_pcb(i, ,);
      // assign MAX_PC with a random number between 2000 - 4000
      // assign Terminate value with a random number between 0 - 30
      // assign IO Trap Arrays 1 & 2 with initializeIOTrapArray();
  }
}

int timer() {
    currenttime--;
    if (currenttime <= 0) {
        currenttime = TimerInitTime; 
        return 1;
    } else {
        return 0;
    }
}

int iointterupt1() {
    static currentiotime = 0;
      if (currentiotime <= 0) {
        currentiotime = currentiotime; 
        return 1;
    } else {
        return 0;
    }

    // generate random number that is between 300 * 5 to 300 * 6
}

int iointterupt2() {
    // generate random number that is between 300 * 5 to 300 * 6
}

int checkForIOTrap() {
    // check running PCB's arrays
    for (each IO Trap array 1) {
        if (isRunning->PC) {
          return 1;
        }
    }
    for (each IO Trap array 2) {
      if (isRunning->PC) {
        return 2;
      }
    }
}

void run() {
    intialize();

    // main loop
    while() {
        // running PCB's PC += 1
        if (timer() == 1) {
          pseudo_isr_timer(timer);
        }

        if (iointterupt1() == 1 && !is_empty(iowaitingqueue1)) {
            dequeue(iowaitingqueue1);
            // enqueue to ready queue
        }

        if (iointterupt2() == 1 && !is_empty(iowaitingqueue2)) {
            dequeue(iowaitingqueue2);
            // enqueue to ready queue
        }
        if (checkForIOTrap() > 0) {
            // int temp = check for IO traps
            // if temp == 1
            // push IO Waiting Queue 1
            // if temp == 2
            // pushing IO Waiting Queue 2

            // dequeue from ready queue and move to is running
        }
    }
}