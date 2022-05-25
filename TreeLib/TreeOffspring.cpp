/**
 * \file TreeOffspring.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "Limb.h"
#include "TreeOffspring.h"

/**
 * Constructor
 * \param limb The parent of the current offspring
 */
CTreeOffspring::CTreeOffspring(CLimb* limb, CFunctionalTree *tree)
{
	mParent = limb;
	mTree = tree;
}
