/**
search.h
Purpose: Tells the movement package to search for an object.

@author shadySource
@version 0.0.1
*/
#ifndef SEARCH_DEF
#define SEARCH_DEF

#include "objective_definitions.h"
#include "state.h"

namespace state
{

class Search : public State
{
    private:

        //@var _target: int for the target to find
        int _target;
        int _targetSeenCounter;
        
    public:
        /**
        Set the target to search for. Check objective_definitions.h
        
        @param target: the number representing the target to search for
        */
        void SetTarget(int target);

        /**
        Search for a target.
        */
        int Execute();


    Search(ros::Publisher*, boxes::Boxes*);

};

}

#endif
