/**
 * \file HaroldFactory.h
 *
 * \author Charles B. Owen
 *
 * Factory class that builds the Harold character
 */

#pragma once
#include "ActorFactory.h"

/** 
 * Factory class that builds the Harold character 
 */
class CHaroldFactory :
    public CActorFactory
{
public:
    CHaroldFactory();
    virtual ~CHaroldFactory();

    std::shared_ptr<CActor> Create(); 

	/// Creates a prop for harold (a canadian flag)
	std::shared_ptr<CActor> CreateFlag();
};

