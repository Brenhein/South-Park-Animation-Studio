/**
 * \file Limb.h
 *
 * \author Brenden Hein
 *
 * This class reprents the limb of the tree
 */

#pragma once
#include <memory>
#include <vector>
#include "TreeOffspring.h"

/**
 * This class reprents the limb of the tree
 *
 * The entire tree's base is made up of limbs.  Every limb will have 2 children or will
 * be terminated by a leaf.  The root of the tree will start with one limb and the tree will 
 * build up from there
 */
class CLimb : public CTreeOffspring
{
public:
	/// Constructor
	/// \param limb The parent limb
	/// \param tree The tree the limb is associated with
	CLimb(CLimb* limb, CFunctionalTree* tree);

	/// Default constructor/disabled
	CLimb() = delete;

	/// Copy constructor/disabled
	CLimb(const CLimb&) = delete;

	/// Assignment operator/disabled
	void operator=(const CLimb&) = delete;

	/// Destructor
	virtual ~CLimb() {}

	/// The base class for draw, which will be overridden
	/// \param graphics The graphics to draw on
	/// \param x The x position of the parent's top center
	/// \param y The y position of the parent's top center
	virtual void DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle) override;

	/// Grows the limb
	virtual void Grow() override;

	/// Sets the dimensions of the limb using a pseudo random number generator
	virtual void SetDim();

	/// Checks if an offspring is fruit and harvests it if so
	/// \returns If the offspring was fruit or not
	virtual bool HarvestFruit() override;

private:
	std::vector<std::shared_ptr<CTreeOffspring>> mChildren; ///< The children of the tree offspring (Can be any offspring unlike parent)

	double mWidth = 0.0; ///< The width of the limb
	double mHeight = 0.0; ///< The height of the limb
};

