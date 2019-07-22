#ifndef __XHLS_REG_COMMON_H
#define __XHLS_REG_COMMON_H



#define XHLS_REG_CTRL_START                     BIT(0)
#define XHLS_REG_CTRL_DONE                      BIT(1)
#define XHLS_REG_CTRL_IDLE                      BIT(2)
#define XHLS_REG_CTRL_READY                     BIT(3)
#define XHLS_REG_CTRL_AUTO_RESTART              BIT(7)
#define XHLS_REG_GIE                            0x04
#define XHLS_REG_GIE_GIE                        BIT(0)
#define XHLS_REG_IER                            0x08
#define XHLS_REG_IER_DONE                       BIT(0)
#define XHLS_REG_IER_READY                      BIT(1)
#define XHLS_REG_ISR                            0x0c
#define XHLS_REG_ISR_DONE                       BIT(0)
#define XHLS_REG_ISR_READY                      BIT(1)
#define XHLS_REG_ROWS                           0x10
#define XHLS_REG_COLS                           0x18





#endif

