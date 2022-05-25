/**
 * \file Leaf.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "Leaf.h"

using namespace std;
using namespace Gdiplus;

/**
 * This is the constructor for a leaf
 * \param limb the parent of the leaf
 */
CLeaf::CLeaf(CLimb* limb, CFunctionalTree* tree) : CTreeOffspring(limb, tree)
{
	mLeafImage = make_shared<CTreeImage>(L"leaf3.png");
}

/**
 * This method grows the leaf as the tree grows
 */
void CLeaf::Grow()
{
	if (mSize < .2) // Max size of leaf
	{
		mSize += .02;
	}
}


/**
 * 
 * \param graphics The graphics to draw on
 * \param x The x position of the parent's top center
 * \param y The y position of the parent's top center 
 * \param angle The angle to draw the image at
 */
void CLeaf::DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle)
{
	mLeafImage->Draw(graphics, angle, mSize, x, y);
}
