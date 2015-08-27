/*
 *  cQOgre.cpp
 *  QTTest
 *
 *  Created by mb on 6/6/10.
 *  Copyright 2010 Communicative Machines. All rights reserved.
 *
 */

#include "cQOgre.h"
#include <QtGui/qevent.h>
#include <QDebug>
#include "Debug/cDebug.h"
#include <QX11Info>

#ifdef Q_WS_MAC
	#include <OpenGL/OpenGL.h>
#elsif defined(Q_WS_WIN)
	#include <wingdi.h>
#endif
using namespace Visor;

/**********************************************************************/
cQOgre::cQOgre( QWidget *iParent )
: QGLWidget( iParent ), mWindow( NULL )
/**********************************************************************/
{
    resize( 128, 128 );
    setAttribute( Qt::WA_PaintOnScreen );
    setAttribute( Qt::WA_NoBackground );
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    InitRoot();
}

/**********************************************************************/
cQOgre::~cQOgre()
/**********************************************************************/
{
    mRoot->shutdown();
    delete mRoot;
    destroy();
}

/**********************************************************************/
bool cQOgre::InitRoot( void )
/**********************************************************************/
{
    // Basic config
#ifdef Q_WS_MAC
    Ogre::String vPath = Ogre::macBundlePath() + "/Contents/Resources/";    
#else
    Ogre::String vPath = "resources/";
#endif
    Ogre::String vA = vPath + "Config/Plugins.cfg";    
    Ogre::String vB = vPath + "Config/Visor.cfg";    
    //Ogre::String vC = vPath + "../Logs/Visor.log";
    mRoot = OGRE_NEW Ogre::Root();// vA, vB, "visor.log" );
    mRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL.so");
    mRoot->loadPlugin("/usr/lib/OGRE/Plugin_CgProgramManager.so");
  
    // Select rendersystem ( TODO: Select OpenGL )
    Ogre::RenderSystemList vRenderers = mRoot->getAvailableRenderers();
    ASSERTTXT(vRenderers.size(), "No renderers available!");
    Ogre::RenderSystem *vRender = *vRenderers.begin();
    mRoot->setRenderSystem( vRender );
    
    // Set size to widget size
    QString dimensions = QString( "%1x%2" )
                       .arg(this->width())
                       .arg(this->height());

     vRender->setConfigOption( "Video Mode", dimensions.toStdString() );

    vRender->setConfigOption( "Full Screen", "No" );
    mRoot->saveConfig();
    
//    mRoot->showConfigDialog();
//    mRoot->saveConfig();
    
    // Init
    mRoot->initialise( false );
    
    return true;
}

/**********************************************************************/
bool cQOgre::InitWindow( void )
/**********************************************************************/
{
    Ogre::String winHandle;
#ifdef WIN32
    // Windows code
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
#elif MACOS
    // Mac code, tested on Mac OSX 10.6 using Qt 4.7.4 and Ogre 1.7.3
    Ogre::String winHandle  = Ogre::StringConverter::toString(winId());
#else
    // Unix code
    QX11Info info = x11Info();
    winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));
#endif


    Ogre::NameValuePairList params;
#ifndef MACOS
    // code for Windows and Linux
    params["parentWindowHandle"] = winHandle;
    mWindow = mRoot->createRenderWindow( "QOgreWidget_RenderWindow",
                                         this->width(),
                                         this->height(),
                                         false,
                                         &params );

    mWindow->setActive(true);
    WId ogreWinId = 0x0;
    mWindow->getCustomAttribute( "WINDOW", &ogreWinId );

    assert( ogreWinId );

    // bug fix, extract geometry
    QRect geo = this->frameGeometry ( );

    // create new window
    this->create( ogreWinId );

    // set geometrie infos to new window
    this->setGeometry (geo);

    mWindow->setActive(true);
    mWindow->setVisible(true);
    //mWindow->setAutoUpdated(true);
#else
    // code for Mac
    params["externalWindowHandle"] = winHandle;
    params["macAPI"] = "cocoa";
    params["macAPICocoaUseNSView"] = "true";
    mWindow = mOgre->createRenderWindow("QOgreWidget_RenderWindow",
                                        width(), height(), false, &params);
    mWindow->setActive(true);
    makeCurrent();
#endif

    return true;
}

/**********************************************************************/
bool cQOgre::InitScene( void )
/**********************************************************************/
{
    mScene    = mRoot->createSceneManager( Ogre::ST_GENERIC );
    mCamera   = mScene->createCamera( "MainCamera" );
    mViewport = mWindow->addViewport( mCamera );
    mViewport->setBackgroundColour( Ogre::ColourValue( 0.8,0.8,1 ) );

    return true;
}

/**********************************************************************/
void cQOgre::initializeGL()
/**********************************************************************/
{
    InitWindow();
    InitResources();
    InitScene();
    InitPost();
}

/**********************************************************************/
void cQOgre::paintGL()
/**********************************************************************/
{
    RenderFrame();
    mRoot->renderOneFrame();
}

/**********************************************************************/
void cQOgre::resizeGL( int iWidth, int iHeight )
/**********************************************************************/
{
    mCamera->setAspectRatio( (float)width() / (float)height() );
    mWindow->resize( width(), height() );
    mWindow->windowMovedOrResized();
}

/**********************************************************************/
void cQOgre::resizeEvent( QResizeEvent *e )
/**********************************************************************/
{
    QGLWidget::resizeEvent( e );
}

/**********************************************************************/
void cQOgre::paintEvent(QPaintEvent *)
/**********************************************************************/
{
    updateGL();
}
