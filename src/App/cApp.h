/*
 *  cApp.h
 *  Visor
 *
 *  Created by mb on 5/29/10.
 *  Copyright 2010 Communicative Machines. All rights reserved.
 *
 */

#include <OIS/OIS.h>
#include <QApplication>
#include <r_comp/segments.h>


namespace Visor
{
    class IComponent;
    class cVisualizerReplicode;
    class cQMainWindow;
    
    class cApp
    {
    protected:
        cQMainWindow *mMainWindow;
        r_comp::Image mImage;
        r_comp::Metadata mMetadata;
        
        cVisualizerReplicode *mVisualizer;
        
        void TestAddChildren( IComponent *iRoot, int iLevel );
        int mNumComponents;
        
        
    public:
        cApp( int argc, char *argv[] );
        bool Init( void );
        void Destroy( void );
        ~cApp();
        
        int Run();
        
//        void LoadImage( const char *iFile );        
    };
}
