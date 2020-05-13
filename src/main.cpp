#include "core/app.hpp"
#include "thisGL/gl_window.hpp"
#include "core/asset_manager.hpp"

// define an app to use in our program
class myApp : public TApp<myApp,TGLWindow, TAssetManager>
{
public:
    myApp() : TApp<myApp,TGLWindow, TAssetManager>("this-demo") {}
};

int main (int argc, char* args[]) 
{
    // init
    myApp::appInstance().begin();
  
    // run
    myApp::appInstance().main();

    // clean
    myApp::appInstance().end();

    // quit
    return 0;
}
