/**
 * \file TreeDrawable.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "TreeDrawable.h"
#include "Tree.h"
#include "Actor.h"
#include "Drawable.h"
#include "Picture.h"
#include "Timeline.h"

using namespace std;

/**
 * Constructor
 * \param tree The tree the adapter will work with
 */
CTreeDrawable::CTreeDrawable(std::wstring name, std::shared_ptr<CTree> tree)
	: CDrawable(name)
{
	mTree = tree;
}


/**
 * Draws the tree drawable to the canadian experience
 * \param graphics The graphics to draw on
 */
void CTreeDrawable::Draw(Gdiplus::Graphics* graphics)
{
	// Sets the frame
	int currentFrame = GetActor()->GetPicture()->GetTimeline()->GetCurrentFrame();
	mTree->SetTreeFrame(currentFrame);

	if (currentFrame >= mStartFrame)
	{
		mTree->DrawTree(graphics);
	}
}


/**
 * Adapater method to call harvest on the tree in the tree library
 * \param frame The frame that harvest was called on
 */
void CTreeDrawable::Harvest(int frame)
{
	// Sets the harvest frame
	mHarvestFrame = frame;

	vector<shared_ptr<CFruit>> fruit = mTree->Harvest();
	mBasketDrawable->AddToBasket(fruit);
}


/**
 * Saves the tree
 * \param node the parent of the saved node
 */
void CTreeDrawable::Save(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	node->SetAttribute(L"Seed", mTree->GetSeed());
	node->SetAttribute(L"StartFrame", mStartFrame);
	node->SetAttribute(L"HarvestFrame", mHarvestFrame);
}

