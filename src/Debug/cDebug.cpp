/*
 *  cDebug.cpp
 *  Visor
 *
 *  Created by mb on 5/30/10.
 *  Copyright 2010 Communicative Machines. All rights reserved.
 *
 */
#include "cDebug.h"
#include <QMessageBox>

#ifdef _WIN32
	#include "cDebug_Win32.cpp"
#elif defined( __APPLE_CC__ )
	#include "cDebug_OSX.cpp"
#else
using namespace Visor;

/**********************************************************************/
bool cDebug::Alert( const char *iMessage, const char *iHeader )
/**********************************************************************/
{
    //CFOptionFlags vFlags;
    //CFUserNotificationDisplayAlert( 0, 0, NULL, NULL, NULL, CFStringCreateWithCStringNoCopy( NULL, iHeader, kCFStringEncodingASCII, kCFAllocatorNull ), CFStringCreateWithCStringNoCopy( NULL, iMessage, kCFStringEncodingASCII, kCFAllocatorNull ), NULL, CFSTR( "Ignore" ), NULL, &vFlags );

    //return ( vFlags == 0 );
    return (QMessageBox::warning(nullptr, iHeader, iMessage) == QMessageBox::Ok);
}

/**********************************************************************/
bool cDebug::Alert( const char *iMessage, const char *iFunction, const char *iLine )
/**********************************************************************/
{
    char *vTemp = new char[ strlen( iFunction ) + strlen( iLine ) + 7 ];
    sprintf( vTemp, "%s line %s", iFunction, iLine );

    bool vResult = Alert( iMessage, vTemp );

    delete [] vTemp;

    return vResult;
}

/**********************************************************************/
void cDebug::Notify( const char *iMessage, const char *iHeader )
/**********************************************************************/
{
//    CFUserNotificationDisplayNotice( 0, 0, NULL, NULL, NULL, CFStringCreateWithCStringNoCopy( NULL, iHeader, kCFStringEncodingASCII, kCFAllocatorNull ), CFStringCreateWithCStringNoCopy( NULL, iMessage, kCFStringEncodingASCII, kCFAllocatorNull ), NULL );
    //CFOptionFlags vFlags;
    //CFUserNotificationDisplayAlert( 0, 0, NULL, NULL, NULL, CFStringCreateWithCStringNoCopy( NULL, iHeader, kCFStringEncodingASCII, kCFAllocatorNull ), CFStringCreateWithCStringNoCopy( NULL, iMessage, kCFStringEncodingASCII, kCFAllocatorNull ), NULL, NULL, NULL, &vFlags );
    QMessageBox::information(nullptr, iHeader, iMessage);
}





#endif
