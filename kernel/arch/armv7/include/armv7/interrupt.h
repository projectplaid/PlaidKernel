#ifndef __INTERRUPT_H
#define __INTERRUPT_H

void interrupt_init();
void interrupt_register(unsigned int intrNum, void (*interrupt_handler)(void));
void interrupt_unregister(unsigned int intrNum);

#endif // __INTERRUPT_H
