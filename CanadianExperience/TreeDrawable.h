/**
 * \file TreeDrawable.h
 *
 * \author Brenden Hein
 *
 * This class is an adapter class to connect the tree from TreeDemo to the CanadianExperience
 */

#pragma once
#include <memory>
#include <vector>
#include <string>
#include "Drawable.h"
#include "BasketDrawable.h"
#include "Tree.h"
#include "Fruit.h"

/**
 * This class is an adapter class to connect the tree from TreeDemo to the CanadianExperience
 */
class CTreeDrawable : public CDrawable
{
public:
	/// Constructor
	/// \param name The name of the drawable
	/// \param tree The tree the drawable is assoicated with
	CTreeDrawable(std::wstring name, std::shared_ptr<CTree> tree);

	/// Default constructor (disabled)
	CTreeDrawable() = delete;

	/// \brief Copy constructor disabled
	CTreeDrawable(const CTreeDrawable&) = delete;

	/// \brief Assignment operator disabled
	void operator=(const CTreeDrawable&) = delete;

	/// Sets the assoication between the tree and it's basket
	/// \param basket The basket the tree is related to
	void SetBasket(CBasketDrawable* basket)
	{
		mBasketDrawable = basket;
		basket->SetTree(this);
	}

	/// Gets the tre start frame
	/// \returns the tree start frame
	int GetStartFrame() { return mStartFrame; }

	/// Sets the tree's start frame
	/// \param frame The start frame of the tree
	void SetStartFrame(int frame)
	{
		mStartFrame = frame;
		mTree->SetTreeFrame(frame);
	}

	/// Sets the harvest frame
	/// \param frame The harvest frmae
	void SetHarvestFrame(int frame) { mHarvestFrame = frame; }

	/// Overrides base class hit test
	/// \param pos The point to hit
	/// \returns always false
	virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	/// Overrides base class draw
	/// \param graphics The graphics to draw on
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Harvests the fruit
	/// \param frame The frame that harvest was called on
	virtual void Harvest(int frame) override;

	/// Saves the drawable components
	/// \param node The parent node
	virtual void Save(const std::shared_ptr<xmlnode::CXmlNode>& node);

private:
	/// The tree the adapater converts data from to fit client code
	std::shared_ptr<CTree> mTree;

	/// The basket drawable
	CBasketDrawable* mBasketDrawable;
	
	/// The start frame for the tree drawable
	int mStartFrame = -1;

	/// The harvest frame for the drawable
	int mHarvestFrame = -1;
};

