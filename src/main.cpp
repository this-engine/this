#include "core/app.hpp"
#include "thisGL/gl_window.hpp"
#include "thisGL/gl_renderer.hpp"

#include <omp.h>
// define an app to use in our program
class myApp : public TApp<myApp>
{
public:

    void makeWindow(const TString &app_name)
    {
        auto window = new TGLWindow(app_name, 640, 480);
        MainWindow.reset(window);
    }

    void destroyWindow()
    {
        MainWindow.reset(nullptr);
    }

    myApp() 
    {
      appName = TString("this Demo");
    }


    virtual void begin() override final { makeWindow(appName); TApp<myApp>::begin();}
    virtual void end() override final { destroyWindow();  }


private :
     

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
