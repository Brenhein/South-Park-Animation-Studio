/**
 * \file TreeOffspring.h
 *
 * \author 
 *
 * This class is the base class for the offspring of a tree
 */

#pragma once
#include <memory>
#include <vector>
#include "PseudoRandom.h"

class CLimb;
class CFunctionalTree;
class CFruit;

/**
 * This class is the base class for the offspring of a tree
 *
 * This class wil lreperesent one of the three children a tree can have, a limb, 
 * a piece of fruit, or a leaf
 */
class CTreeOffspring
{
public:
	/// Constructor
	/// \param limb The parent limb of thew offspring
	/// \param tree the tree the limb is associated with
	CTreeOffspring(CLimb* limb, CFunctionalTree* tree);

	/// Default construcotr/disabled
	CTreeOffspring() = delete;

	/// Copy constructor/disabled
	CTreeOffspring(const CTreeOffspring&) = delete;

	/// Assignment operator/disabled
	void operator=(const CTreeOffspring&) = delete;

	/// Destructor
	virtual ~CTreeOffspring() {}

	/// Gets the x postion
	/// \returns The x position
	double GetX() { return mX; }

	/// Gets the y postion
	/// \returns The x position
	double GetY() { return mY; }

	/// Sets the position of the limb
	/// \param x The x position to set to
	/// \param y The y position to set to
	void SetPosition(double x, double y) { mX = x; mY = y; }

	/// Gets the angle
	/// \returns angle The angle of the offspring
	double GetAngle() { return mAngle; }

	/// Sets the angle
	/// \param angle The angle to set to
	void SetAngle(double angle) { mAngle = angle; }

	/// Gets the depth
	/// \returns the depth of the offspring
	int GetDepth() { return mDepth; }

	/// Sets the depth
	/// \param depth The depth to set to
	void SetDepth(int depth) { mDepth = depth; }

	/// Gets the tree the offspring is part of
	/// \returns angle The tree the ofsspring is part of
	CFunctionalTree* GetTree() { return mTree; }

	/// The base class for draw, which will be overridden
	/// \param graphics The graphics to draw on
	/// \param x The x position of the parent's top center
	/// \param y The y position of the parent's top center
	/// \param angle The angle of the parent
	virtual void DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle) = 0;

	/// pure virtual function for growing the offspring of the tree
	virtual void Grow() = 0;

	/// Pure virtual that checks if an offspring is fruit and harvests it if so
	/// \returns If the offspring was fruit or not
	virtual bool HarvestFruit() { return false; }

private:
	CLimb *mParent; ///< The parent of the limb (which will always be a limb)

	CFunctionalTree* mTree = nullptr; ///< The tree the offspring is part of

	double mX = 0; ///< the x location
	double mY = 0; ///< the y location
	double mAngle = -1; ///< The angle of the offspring

	int mDepth = 1; ///< The depth of the current offspring
};

