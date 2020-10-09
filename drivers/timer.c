#include "timer.h"

#include "io.h"
#include "isr.h"
#include "tty.h"
#include "string.h"
#include "stdlib.h"

#define CHANNEL_0   0x40    /* Channel 0 data port */
#define CHANNEL_1   0x41    /* Channel 1 data port */
#define CHANNEL_2   0x42    /* Channel 2 data port */
#define PIT_CMD     0x43    /* Mode/command register */


#define PIT_CLK_FREQ    1193180 /* Input frequency of clock for PIT */


uint32_t tick = 0;

static void timer_callback(registers_t *regs);



static void timer_callback(registers_t *regs)
{
    tick ++;
    char str[10] = {0};
    terminal_writestring("Tick: ");
    terminal_writestring(itoa(tick, str, 10));
    terminal_writestring("\n");
    (void)regs;
}


void init_timer(uint32_t freq)
{
    register_interrupt_handler(IRQ0, &timer_callback);

    /* The value we send to the PIT is the value to divide it's input clock
     *(1193180 Hz) by, to get our required frequency. Important to note is 
     * that the divisor must be small enough to fit into 16-bits
     */
    uint32_t divisor =  PIT_CLK_FREQ / freq;

    /*
     *    Bits         Usage
     *    6 and 7      Select channel :
     *                    0 0 = Channel 0
     *                    0 1 = Channel 1
     *                    1 0 = Channel 2
     *                    1 1 = Read-back command (8254 only)
     *    4 and 5      Access mode :
     *                    0 0 = Latch count value command
     *                    0 1 = Access mode: lobyte only
     *                    1 0 = Access mode: hibyte only
     *                    1 1 = Access mode: lobyte/hibyte
     *    1 to 3       Operating mode :
     *                    0 0 0 = Mode 0 (interrupt on terminal count)
     *                    0 0 1 = Mode 1 (hardware re-triggerable one-shot)
     *                    0 1 0 = Mode 2 (rate generator)
     *                    0 1 1 = Mode 3 (square wave generator)
     *                    1 0 0 = Mode 4 (software triggered strobe)
     *                    1 0 1 = Mode 5 (hardware triggered strobe)
     *                    1 1 0 = Mode 2 (rate generator, same as 010b)
     *                    1 1 1 = Mode 3 (square wave generator, same as 011b)
     *                    0            BCD/Binary mode: 0 = 16-bit binary, 1 = four-digit BCD
    */
    outb(PIT_CMD, 0x36);

    uint8_t lobyte = divisor & 0xFF;
    uint8_t hibyte = (divisor & 0x00FF) >> 8;

    /* Send the frequency divisor */
    outb(PIT_CMD, lobyte);
    outb(PIT_CMD, hibyte);


}