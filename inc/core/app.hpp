// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef _this_app_
#define _this_app_


#include <cstdlib>  // for atexit
#include <memory>
#include "core.hpp"
#include "window.hpp"
#include <omp.h>



/**
 *  TApp
 *  @brief      singleton class of any app build with the __This__ engine
 *  @note       this represent the running app, there is only one
 *  @note       we use the CRTP paradigm to allow users of the engine to extend the behaviour of the app
 *  @see        <https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern>
 */
template<typename DERIVEDAPP>
class TApp
{
private :


    DERIVEDAPP operator=(const DERIVEDAPP& rv);

    /**
     *  delete_singleton
     *  @brief       Function that manages the destruction of the instance at the end of the execution.
     */
    static void delete_singleton() { delete app; }

    /**
     *  app
     *  @brief      this app
     *  @note       only living instance
     */
	static DERIVEDAPP* app;

protected:

    /**
     *  app_name
     *  @brief      human readable name for this app
     *  @todo       repalce by a more compact and unique type(hash table ?)
     */
    TString appName = TString("default-This-App");

    /**
     *  TApp
     *  @brief      ctor
     *  @note       protected to allow inheritance
     */
    TApp() {}

    /**
     *  ~TApp
     *  @brief      dtor
     *  @note       IMPORTANT: virtual destructor
     */
    virtual ~TApp() {}

public:
   
    /**
     *  begin
     *  @brief      initialisation of the app
     */
    virtual void begin();


    /**
     *  main
     *  @brief      actual main loop function
     */
    virtual void main();



    /**
     *  end
     *  @brief      cleaning up of the app
     */
    virtual void end();


    /**
     *  MainWindow
     *  @brief      window to draw to
     */
    std::shared_ptr<TWindow> MainWindow;


public :


    /**
     *  appInstance
     *  @brief      get the one and only app instance
     */
    static DERIVEDAPP&  appInstance()
    {
        if(!app)
        {
            app = new DERIVEDAPP;
            std::atexit( delete_singleton ); //Destruction of instance registered at runtime exit (No leak).
        }
        return static_cast<DERIVEDAPP&>( *app );
    }


};

template<typename DERIVEDAPP>
DERIVEDAPP* TApp<DERIVEDAPP>::app = nullptr;


template<typename DERIVEDAPP>
void TApp<DERIVEDAPP>::begin()
{

}

template<typename DERIVEDAPP>
void TApp<DERIVEDAPP>::end()
{

}

template<typename DERIVEDAPP>
void TApp<DERIVEDAPP>::main()
{
    #pragma omp critical (refresh)
    {
        while(!MainWindow->shouldClose())
            {
                MainWindow->refreshEvent();
            }
    }
    
}

#endif // _this_app_

