/**
 * \file BasketDrawable.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "BasketDrawable.h"
#include "Actor.h"
#include "Drawable.h"
#include "Picture.h"
#include "Timeline.h"
#include "TreeDrawable.h"

/**
 * 
 * \param basket The basket the adapater will work with
 */
CBasketDrawable::CBasketDrawable(std::wstring name, std::shared_ptr<CBasket> basket)
	: CDrawable(name)
{
	mBasket = basket;
}


/**
 * Clears the vector of fruit
 */
void CBasketDrawable::EmptyBasket()
{
	mBasket->EmptyBasket();
}


/**
 * Draws the basket, with or without its fruit
 * \param graphics The graphics to draw on
 */
void CBasketDrawable::Draw(Gdiplus::Graphics* graphics)
{
	int currentFrame = GetActor()->GetPicture()->GetTimeline()->GetCurrentFrame();

	if (currentFrame >= mTreeDrawable->GetStartFrame())
	{
		mBasket->DrawBasket(graphics);
	}
}


/**
 * Adds a vector of fruit to the basket associated with the tree it got the fruit from
 * \param fruit The fruit to add to the basket
 */
void CBasketDrawable::AddToBasket(std::vector<std::shared_ptr<CFruit>> fruit)
{
	mBasket->AddToBasket(fruit);
}
