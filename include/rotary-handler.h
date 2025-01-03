#ifndef _ROTARY_HANDLER_H_
#define _ROTARY_HANDLER_H_

#define PCINT2_vect _VECTOR(5)

Rotary r = Rotary(2, 3);               // Initialize Rotary opbject r (Type Rotary) a. assign pin 2 and pin 3 b. set Initial state c. set default inverter

void initRotary(){
     pinMode(2, INPUT_PULLUP);
     pinMode(3, INPUT_PULLUP);
     PCICR |= (1 << PCIE2);
     PCMSK2 |= (1 << PCINT18) | (1 << PCINT19);
     sei();
}
    
// Interrupt Service Routine
ISR(PCINT2_vect) {
        MyData::dataManager.setByRotary(r.process());
}

#endif