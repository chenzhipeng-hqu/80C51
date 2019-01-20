/*****************************************************************************
* Product: "Blinky" example
* Last Updated for Version: 5.8.0
* Date of the Last Update:  2016-11-06
*
*                    Q u a n t u m     L e a P s
*                    ---------------------------
*                    innovating embedded systems
*
* Copyright (C) Quantum Leaps, LLC. All rights reserved.
*
* This program is open source software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Alternatively, this program may be distributed and modified under the
* terms of Quantum Leaps commercial licenses, which expressly supersede
* the GNU General Public License and are specifically designed for
* licensees interested in retaining the proprietary status of their code.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* Contact information:
* http://www.state-machine.com
* mailto:info@state-machine.com
*****************************************************************************/
#include <stdio.h>
#include "Timer.h"

#include "qpn.h"     /* QP-nano API */
#include "bsp.h"     /* Board Support Package */
#include "usart.h"     /* Board Support Package */
#include "blinky.h"  /* Application interface */

/* Local-scope objects -----------------------------------------------------*/
static QEvt l_blinkyQSto[10]; /* Event queue storage for Blinky */
static QEvt l_AO_LCD1602QSto[10];

/* QF_active[] array defines all active object control blocks --------------*/
QActiveCB const Q_ROM QF_active[] = {
    { (QActive *)0,           (QEvt *)0,        0U                      },
    { (QActive *)&AO_Blinky,  l_blinkyQSto,     Q_DIM(l_blinkyQSto)     },
    { (QActive *)&AO_LCD1602,  l_AO_LCD1602QSto,     Q_DIM(l_AO_LCD1602QSto)     }
};

/*..........................................................................*/
int main(void) 
{
//	volatile u32 *pulSysTicks;							 //用于记录系统时钟地址

	Blinky_ctor(); /* instantiate all Blinky AO */
	LCD1602_ctor();
	
    QF_init(Q_DIM(QF_active)); /* initialize the QF-nano framework */

    BSP_init();      /* initialize the Board Support Package */


  return QF_run(); /* transfer control to QF-nano */
}
