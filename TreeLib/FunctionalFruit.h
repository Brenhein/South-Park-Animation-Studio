/**
 * \file FunctionalFruit.h
 *
 * \author Brenden Hein
 *
 * This class represent the usable version of fruit in our program
 */

#pragma once
#include "Fruit.h"
#include "TreeOffspring.h"
#include "TreeImage.h"

/**
 * This class represent the usable version of fruit in ou program
 */
class CFunctionalFruit : public CFruit, public CTreeOffspring
{
public:
	/// Constructor
	/// \param limb The parent of the fruit
	/// \param tree The tree the fruit is a part of
	CFunctionalFruit(CLimb* limb, CFunctionalTree* tree);

	/// Destructor
	virtual ~CFunctionalFruit() {}

	/**
	 * Set the position of the fruit in the basket
	 *
	 * This position is relative to the basket, so
	 * it will be added to the basket location passed
	 * to DrawInBasket when we draw it
	 * \param x X position in pixels
	 * \param y Y position in pixels
	 */
	virtual void SetBasketPosition(int x, int y) override;

	/**
	 * Draw the fruit in the basket
	 * \param graphics The graphics object to draw on
	 * \param left X location of the basket
	 * \param top Y location of the basket
	 */
	virtual void DrawInBasket(Gdiplus::Graphics* graphics, int left, int top) override;

	/// Grows the leaf
	virtual void Grow() override;

	// The base class for draw, which will be overridden
	/// \param graphics The graphics to draw on
	/// \param x The x position of the parent's top center
	/// \param y The y position of the parent's top center
	/// \param angle the angle of the fruit
	virtual void DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle) override;

	/// Checks if an offspring is fruit and harvests it if so
	/// \returns If the offspring was fruit or not
	virtual bool HarvestFruit() override { return true; }

private:
	/// The image of a fruit
	std::shared_ptr<CTreeImage> mFruitImage;

	/// The size of the image
	double mSize = .005;

	/// The x offset within the basket
	double mBasketOffsetX;

	/// The y offset within the basket
	double mBasketOffsetY;
};

