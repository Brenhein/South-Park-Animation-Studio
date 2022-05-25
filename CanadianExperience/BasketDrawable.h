/**
 * \file BasketDrawable.h
 *
 * \author Brenden Hein
 *
 * This class is an adapter class to connect the basket from TreeDemo to the CanadianExperience
 */

#pragma once
#include <memory>
#include <string>
#include "Drawable.h"
#include "Basket.h"

class CTreeDrawable;

/**
 * This class is an adapter class to connect the basket from TreeDemo to the CanadianExperience
 */
class CBasketDrawable : public CDrawable
{
public:
	/// Constructor
	/// \param name The name of the drawable
	/// \param basket The basket associated with the drawable
	CBasketDrawable(std::wstring name, std::shared_ptr<CBasket> basket);

	/// Default Constructor (disabled)
	CBasketDrawable() = delete;

	/// \brief Copy constructor disabled
	CBasketDrawable(const CBasketDrawable&) = delete;

	/// \brief Assignment operator disabled
	void operator=(const CBasketDrawable&) = delete;

	/// Sets the assoication between the tree and it's basket
	/// \param tree The tree the basket is related to
	void SetTree(CTreeDrawable* tree)
	{
		mTreeDrawable = tree;
	}

	/// Overrides base class hit test
	/// \param pos The point to hit
	/// \return always false
	virtual bool HitTest(Gdiplus::Point pos) override { return false; }

	/// Empties the basket filled with fruit (if any)
	virtual void EmptyBasket() override;

	/// Overrides base class draw
	/// \param graphics The graphics to draw on
	virtual void Draw(Gdiplus::Graphics* graphics);

	/// Adds to basket using adapater functionality
	/// \param fruit The fruit to add
	void AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit);

private:
	/// The basket the adapater converts data from to fit client code
	std::shared_ptr<CBasket> mBasket;

	/// The tree drawable
	CTreeDrawable* mTreeDrawable;
};

