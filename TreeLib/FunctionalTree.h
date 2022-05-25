/**
 * \file FunctionalTree.h
 *
 * \author Brenden Hein
 *
 * This class represents the usable form of our tree in both the demo and canadian experience
 */


#pragma once
#include <vector>
#include "PseudoRandom.h"
#include "Tree.h"
#include "TreeOffspring.h"
#include "Limb.h"

/* CONSTANTS */
const double PI = 3.141592654; ///< value of pi

/**
 * This class represents the usable form of our tree in both the demo and canadian experience
 */
class CFunctionalTree : public CTree
{
public:
	/// Constructor
	CFunctionalTree();

	/// Destructor
	virtual ~CFunctionalTree() {}

	/// Copy constructor/disabled
	CFunctionalTree(const CFunctionalTree&) = delete;

	/// Assignment operator/disabled
	void operator=(const CFunctionalTree&) = delete;

	/**
	* Set the position for the root of the tree
	* \param x X location (pixels)
	* \param y Y location (pixels)
	*/
	virtual void SetRootLocation(int x, int y) override 
	{
		mX = double(x);
		mY = double(y);
		mRoot->SetPosition(mX, mY);
	}

	/**
	* Draw the tree at the currently specified location
	* \param graphics GDI+ Graphics object
	*/
	virtual void DrawTree(Gdiplus::Graphics* graphics) override;

	/// Gets the tree frame
	/// \returns the current tree frame
	int GetTreeFrame() { return mFrame; }

	/// Gets the tre start frame
	/// \returns the tree start frame
	int GetTreeStartFrame() {return mStartFrame; }

	/// Gets the wind speed
	/// \returns The velcoity of wind in mph
	double GetWindSpeed() { return mWindSpeed; }

	/**
	* Set the current tree frame
	* \param frame Frame number
	*/
	virtual void SetTreeFrame(int frame) override;

	/**
	* Set  the wind speed
	* \param speed Wind speed in miles per hour
	*/
	virtual void SetWindSpeed(double speed) override { mWindSpeed = speed; }

	/**
	* Gets the rangom number geenrator so offspring can access it
	* \returns The random number generator
	*/
	CPseudoRandom *GetRNG() { return &RNG; }

	/**
	* Set the tree seed
	* \param seed An integer number. Each number makes a different tree
	*/
	virtual void SetSeed(int seed) override 
	{ 
		mSeed = seed;
		RNG.Seed(seed);
		mRoot->SetDim();
	}

	/**
	 * Get the current tree seed
	 * \return Tree seed integer
	 */
	virtual int GetSeed() override { return mSeed; }

	/**
	 * Harvest all of the fruit
	 * \return Vector of objects of type CFruit
	 */
	virtual std::vector<std::shared_ptr<CFruit>> Harvest() override;

	/// Resets the tree back to 0 then starts growing it again
	void Reset();

	/// Adds a fruit to the vector of current fruit on three
	/// \param fruit The fruit to add to the list of fruit associated with the tree
	void AddFruit(std::shared_ptr<CFruit> fruit) { mFruit.push_back(fruit); }

private:
	/// The speed of wind that causes the tree to bend
	double mWindSpeed = 0;

	/// The seed generated for the tree
	int mSeed = 0;

	double mX = 0; ///< the x location OF THE ROOT
	double mY = 0; ///< the y location OF THE ROOT

	int mFrame = 0; ///< Current frame
	int mStartFrame = -1; ///< The frame the tree was generated at

	/// The root of the tree
	std::shared_ptr<CLimb> mRoot;

	/// The vecotr of fruit currently on the tree
	std::vector<std::shared_ptr<CFruit>> mFruit;

	/// The random number generator that will be used for the tree
	CPseudoRandom RNG;
};

