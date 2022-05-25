/**
 * \file FunctionalTree.cpp
 *
 * \author 
 */

#include "pch.h"
#include "FunctionalTree.h"

using namespace Gdiplus;
using namespace std;

/**
 * The Default constructor
 */
CFunctionalTree::CFunctionalTree() : CTree()
{
	Reset();
}

/**
 * Draws the tree, calling draw on all its offspring
 * \param graphics The graphics to draw on
 */
void CFunctionalTree::DrawTree(Gdiplus::Graphics* graphics)
{
	if (mRoot != nullptr)
	{
		mRoot->DrawOffspring(graphics, mX, mY, -PI/2);
	}
}

/**
 * This sets the current frame of the tree.  If the start frame hasn't been set, it
 * sets it to the current frame.  If the new frame is less than the current frame, 
 * the tree shrinks.  If the new frame is greater than the current frame, the tree grows
 * \param frame The current frame of the animation
 */
void CFunctionalTree::SetTreeFrame(int frame)
{
	if (mStartFrame == -1) // The tree was just created
	{
		mStartFrame = frame;
		mFrame = frame;
	}

	else if (mFrame > frame) // Shrinks the tree
	{
		Reset(); // creates a new root
		SetSeed(mSeed); // resets the seed
		mFruit.clear();
		mFrame = mStartFrame;
	}

	while (mFrame < frame) {
		mFrame++;
		mRoot->Grow();    // Grow by one frame
	}
}

/**
 * Harvests the tree of all its fruit and puts it into its basket
 * \returns The vector of all the fruit that was on
 */
std::vector<std::shared_ptr<CFruit>> CFunctionalTree::Harvest()
{
	mRoot->HarvestFruit();
	std::vector<std::shared_ptr<CFruit>> fruitCopy = mFruit;
	mFruit.clear();
	return fruitCopy;
}

/**
 * Resets the growth of the tree back to 0 so it can grow back to a previous frame
 */
void CFunctionalTree::Reset()
{
	mRoot = make_shared<CLimb>(nullptr, this); // The root of the tree
	mRoot->SetAngle(0);
}
