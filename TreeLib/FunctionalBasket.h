/**
 * \file FunctionalBasket.h
 *
 * \author Brenden Hein
 *
 * This class reprents the usable basket for our tree
 */

#pragma once
#include <vector>
#include <memory>
#include <string>
#include "TreeImage.h"
#include "Basket.h"
#include "FunctionalFruit.h"

/**
 * This class reprents the usable basket for our tree
 */
class CFunctionalBasket : public CBasket
{
public:
	/// Constructor
	CFunctionalBasket();

	/// Destructor
	virtual ~CFunctionalBasket() {}

	/// Copy constructor/disabled
	CFunctionalBasket(const CFunctionalBasket&) = delete;

	/// Assignment operator/disabled
	void operator=(const CFunctionalBasket&) = delete;

	/**
	* Set the position for the basket.
	* \param x X location (pixels)
	* \param y Y location (pixels)
	*/
	virtual void SetBasketLocation(int x, int y) override
	{
		mX = double(x);
		mY = double(y);
	}

	/**
	* Draw the basket at the currently specified location
	* \param graphics GDI+ Graphics object
	*/
	virtual void DrawBasket(Gdiplus::Graphics* graphics) override;

	/**
	 * Add fruit to the basket
	 * \param fruit Vector of fruit objects
	 */
	virtual void AddToBasket(std::vector < std::shared_ptr<CFruit>> fruit) override;

	/**
	 * Empty all fruit from the basket
	 */
	virtual void EmptyBasket() override;

private:
	/// The image of the basket
	std::shared_ptr<CTreeImage> mBasketImage1;

	/// The image of the front of the basket
	std::shared_ptr<CTreeImage> mBasketImage2;

	/// The basket filled with fruit
	std::vector<std::shared_ptr<CFruit>> mFruit;

	double mX; ///< the x location of the basket
	double mY; ///< the y location of the basket
};

