#include "Application.h"
#include <iostream>


using namespace std;

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
#endif

#ifdef _DEBUG
	#define _CRTDBG_MAPALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif    // DEBUG

void execution( ) {
    try {
            llm::Application* app = llm::Application::getInstance();
            app->start( );
            app->kill( );
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    MessageBoxA( NULL, e.getFullDescription( ).c_str( ), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
    std::cerr << "An exception has occured: " << e.getFullDescription( ).c_str( ) << std::endl;
#endif
        
        }
}
 
#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char *argv[]) {
        // Create application object
		#ifdef _DEBUG
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
			//_crtBreakAlloc = 106158;
		#endif

        execution( );
		
		return 0;
    }
 
#ifdef __cplusplus
}
#endif