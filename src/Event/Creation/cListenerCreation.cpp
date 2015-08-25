/*
 *  cListenerCreation.cpp
 *  Visor
 *
 *  Created by mb on 5/30/10.
 *  Copyright 2010 Communicative Machines. All rights reserved.
 *
 */

#include <stdio.h>
#include "cListenerCreation.h"
using namespace Visor;

/**********************************************************************/
void cListenerCreation::OnComponentCreated( IComponent *iComponent )
/**********************************************************************/
{
    printf( "[cListenerCreation::OnComponentCreated] 0x%p\n", iComponent );
//    IEventDispatcher<cListenerCreation> vDispatcher;
//    vDispatcher.Dispatch< &cListenerCreation::OnComponentCreated >();
}
