/**
 * \file FunctionalFruit.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "FunctionalTree.h"
#include "FunctionalFruit.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 * \param limb The parent of the fruit
 */
CFunctionalFruit::CFunctionalFruit(CLimb* limb, CFunctionalTree* tree) : CTreeOffspring(limb, tree)
{
	mFruitImage = make_shared<CTreeImage>(L"apple.png");

	CPseudoRandom* rng = GetTree()->GetRNG();
	mBasketOffsetX = rng->Random(15, mFruitImage->GetImage()->GetWidth() - 5);
	mBasketOffsetY = rng->Random(10, mFruitImage->GetImage()->GetHeight() / 3) + 20.0;
}

/**
 * Sets the location of where the fruit is in the basket using RNG
 * \param x The x position
 * \param y The y position
 */
void CFunctionalFruit::SetBasketPosition(int x, int y)
{
	SetPosition(double(x), double(y));
}

/**
 * Draws the fruit in its tree's basket
 * \param graphics The graphics to draw on
 * \param left The left side of the basket
 * \param top The top of the basket
 */
void CFunctionalFruit::DrawInBasket(Gdiplus::Graphics* graphics, int left, int top)
{
	mFruitImage->Draw(graphics, GetAngle(), mSize, 
		left + mBasketOffsetX, top + mBasketOffsetY);
}

/**
 * This method grows the fruit as the tree grows
 */
void CFunctionalFruit::Grow()
{
	if (mSize < .2) // Max size of leaf
	{
		mSize += .02;
	}
}

/**
 * Draws the fruit imagee
 * \param graphics The graphics to draw on
 * \param x The x position
 * \param y The y position
 * \param angle The angle to rotate by
 */
void CFunctionalFruit::DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle)
{
	mFruitImage->Draw(graphics, GetAngle(), mSize, x, y);
}
