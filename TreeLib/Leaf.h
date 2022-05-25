/**
 * \file Leaf.h
 *
 * \author Brenden Hein
 *
 * This class represents a leaf on the tree, one of the tree offspring
 */

#pragma once
#include "TreeOffspring.h"
#include "TreeImage.h"


/**
 * This class represents a leaf on the tree, one of the tree offspring
 */
class CLeaf : public CTreeOffspring
{
public:
	/// Constructor
	/// \param limb The parent of the leaf
	/// \param tree The tree the leaf is associated with
	CLeaf(CLimb* limb, CFunctionalTree* tree);

	/// Virtual destructor
	~CLeaf() {}

	/// Grows the leaf
	virtual void Grow() override;

	// The base class for draw, which will be overridden
	/// \param graphics The graphics to draw on
	/// \param x The x position of the parent's top center
	/// \param y The y position of the parent's top center
	virtual void DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle) override;

private:
	/// The image of a leaf
	std::shared_ptr<CTreeImage> mLeafImage;

	/// The size of the image
	double mSize = .005;
};

