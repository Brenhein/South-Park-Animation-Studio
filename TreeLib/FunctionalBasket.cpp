/**
 * \file FunctionalBasket.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include <random>
#include "FunctionalBasket.h"
#include "FunctionalFruit.h"

using namespace std;

/**
 * Constructor for the basket
 */
CFunctionalBasket::CFunctionalBasket() : CBasket()
{
	mBasketImage1 = make_shared<CTreeImage>(L"basket.png");
	mBasketImage2 = make_shared<CTreeImage>(L"basket-front.png");
}

/**
 * Draws the basket with its fruit inside of it
 * \param graphics The graphics object to draw on
 */
void CFunctionalBasket::DrawBasket(Gdiplus::Graphics* graphics)
{
	mBasketImage1->Draw(graphics, 0.0, 1.0, mX, mY);

	// Draws the fruit in the basket
	for (auto fruit : mFruit)
	{
		// Gets the top left corner of the basket (includes transparent pixels)
		double top = mX - double(mBasketImage1->GetImage()->GetWidth() / 2);
		double left = mY - double(mBasketImage1->GetImage()->GetHeight());

		fruit->DrawInBasket(graphics, (int)top, (int)left);
	}

	mBasketImage2->Draw(graphics, 0.0, 1.0, mX, mY);
}

/**
 * Adds the fruit to the basket it is assocaited with
 * \param fruit The container of fruit to add
 */
void CFunctionalBasket::AddToBasket(std::vector<std::shared_ptr<CFruit>> fruit)
{
	for (auto piece : fruit) // Sets the fruit in the basket
	{
		piece->SetBasketPosition((int)mX, (int)mY);
		mFruit.push_back(piece);
	}
}

/**
 * Clears the basket of fruit
 */
void CFunctionalBasket::EmptyBasket()
{
	mFruit.clear();
}
