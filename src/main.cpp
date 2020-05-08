#include "core/app.hpp"
#include "thisGL/glfw_window.hpp"

#include <omp.h>
// define an app to use in our program
class myApp : public TApp<myApp>
{
public:

    void makeWindow(const TString &app_name)
    {
        MainWindow.reset( new TGLFWWindow(app_name, 640, 480));
        if(MainWindow)
        {
            MainWindow->init(); 
            return;
        }
        return;
    }

    void destroyWindow()
    {
      if(MainWindow != NULL)
        MainWindow->deinit();
    }

    myApp() 
    {
      appName = TString("this Demo");
    }


    virtual void begin() override final { makeWindow(appName); }
    virtual void end() override final { destroyWindow();  }


private :
     

};

int main (int argc, char* args[]) 
{
  // init
  myApp::appInstance().begin();
  
  // run
  myApp::appInstance().main();

  // quit
  return 0;
}
