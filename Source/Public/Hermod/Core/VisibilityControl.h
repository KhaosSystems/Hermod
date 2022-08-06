#pragma once

#ifdef Hermod_EXPORTS
    #define HERMOD_API __declspec(dllexport) 
#else
    #define HERMOD_API __declspec(dllimport)  
#endif