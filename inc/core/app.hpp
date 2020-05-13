// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#ifndef _this_app_
#define _this_app_

#include <stdio.h>
#include <cstdlib>  // for atexit
#include <memory>
#include <omp.h>
#include "core.hpp"
#include "window.hpp"
#include "asset_manager.hpp"




/**
 *  TApp
 *  @brief      singleton class of any app build with the __This__ engine
 *  @note       this represent the running app, there is only one
 *  @note       we use the CRTP paradigm to allow users of the engine to extend the behaviour of the app
 *  @see        <https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern>
 */
template<typename DERIVEDAPP,typename WindowType, typename AssetManagerType>
class TApp
{
private :


    DERIVEDAPP operator=(const DERIVEDAPP& rv);

    /**
     *  delete_singleton
     *  @brief       Function that manages the destruction of the instance at the end of the execution.
     */
    static void delete_singleton() { delete App; }

    /**
     *  app
     *  @brief      this app
     *  @note       only living instance
     */
	static DERIVEDAPP* App;

protected:

    /**
     *  app_name
     *  @brief      human readable name for this app
     *  @todo       repalce by a more compact and unique type(hash table ?)
     */
    TString AppName = TString("default-This-App");

    /**
     *  TApp
     *  @brief      ctor
     *  @note       protected to allow inheritance
     */
    TApp(TString app_name) : AppName(app_name) 
    {
        static_assert(std::is_base_of<TWindow, WindowType>::value,             "WindowType must be derived from TWindow");
        static_assert(std::is_base_of<TAssetManager, AssetManagerType>::value, "AssetManagerType must be derived from TAssetManager");
        auto window = new WindowType(AppName, 640, 480);
        MainWindow.reset(window);
        auto asset_manager = new AssetManagerType();
        AssetManager.reset(asset_manager);
    }

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
    std::unique_ptr<WindowType> MainWindow;


    /**
     *  MainWindow
     *  @brief      window to draw to
     */
    std::unique_ptr<AssetManagerType> AssetManager;

public :


    /**
     *  appInstance
     *  @brief      get the one and only app instance
     */
    static DERIVEDAPP&  appInstance()
    {
        if(!App)
        {
            App = new DERIVEDAPP;
            std::atexit( delete_singleton ); //Destruction of instance registered at runtime exit (No leak).
        }
        return static_cast<DERIVEDAPP&>( *App );
    }


};

template<typename DERIVEDAPP,typename WindowType, typename AssetManagerType>
DERIVEDAPP* TApp<DERIVEDAPP,WindowType,AssetManagerType >::App = nullptr;


template<typename DERIVEDAPP,typename WindowType, typename AssetManagerType>
void TApp<DERIVEDAPP,WindowType,AssetManagerType >::begin()
{
    if(MainWindow)
        MainWindow->init();
}

template<typename DERIVEDAPP,typename WindowType, typename AssetManagerType>
void TApp<DERIVEDAPP,WindowType,AssetManagerType >::end()
{

}

template<typename DERIVEDAPP,typename WindowType, typename AssetManagerType>
void TApp<DERIVEDAPP,WindowType,AssetManagerType >::main()
{
#pragma omp parallel shared(MainWindow)
    {
        #pragma omp master
        {
            while(!MainWindow->shouldClose())
            {
                // must be run on "main thread";
                MainWindow->windowEvents();

                #pragma omp taskgroup
                {
                    #pragma omp task shared(MainWindow)
                    { MainWindow->render(); }
                }

                //stderr << glGetError() << std::endl;
            }
        
        }
    
    }
}

#endif // _this_app_

