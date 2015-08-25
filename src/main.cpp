/*
 *  main.cpp
 *  Visor
 *
 *  Created by mb on 5/29/10.
 *  Copyright 2010 Communicative Machines. All rights reserved.
 *
 */

#include <stdio.h>

#include <App/cApp.h>
using namespace Visor;

int main( int argc, char *argv[] )
{
    QApplication app(argc, argv);
    cApp vApp( argc, argv );
    vApp.Init();

    return app.exec();
}
