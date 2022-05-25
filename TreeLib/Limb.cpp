/**
 * \file Limb.cpp
 *
 * \author Brenden Hein
 */

#include "pch.h"
#include "Limb.h"
#include "FunctionalTree.h"
#include "Leaf.h"
#include "FunctionalFruit.h"

using namespace std;
using namespace Gdiplus;

/**
 * Constructor for the limb object
 * \param limb The parent of the limb
 */
CLimb::CLimb(CLimb *limb, CFunctionalTree* tree) : CTreeOffspring(limb, tree)
{
}

/**
 * Draws the tree
 * \param graphics The grpahics to draw with
 * \param x the x location of the parent
 * \param y the y location of the parent
 * \param angle The angle of the parent
 */
void CLimb::DrawOffspring(Gdiplus::Graphics* graphics, double x, double y, double angle)
{
	double limbAngle = angle + GetAngle();

	/* WIND */

	double directionalAngle = sin(limbAngle);
	double windSpeed = GetTree()->GetWindSpeed();
	
	// Will the angle bend up or down with the wind
	if (directionalAngle < 0) // Up
	{
		limbAngle += windSpeed * .003;
	}
	else if (directionalAngle > 0) // Down
	{
		limbAngle -= windSpeed * .003;
	}

	// Draws the limb
	double dx = cos(limbAngle) * mHeight;
	double dy = sin(limbAngle) * mHeight;

	Pen pen(Color(139, 69, 19), (REAL)mWidth);
	pen.SetEndCap(LineCapRound);
	graphics->DrawLine(&pen, (REAL)x, (REAL)y,
		(REAL)(x + dx), (REAL)(y + dy));

	// Draws the children
	for (auto child : mChildren)
	{
		child->DrawOffspring(graphics, x + dx, y + dy, limbAngle);
	}
}

/**
 * This function grows a limb until it reaches a certain height, and then either splits
 * it off into 2 children or grows a piece of fruit/leaf
 */
void CLimb::Grow()
{
	// Grows the children
	for (auto child : mChildren)
	{
		child->Grow();
	}

	// Grows the tree's height
	double delta = 1.0 / ((double)GetTree()->GetTreeFrame() - (double)GetTree()->GetTreeStartFrame() + 1.0);
	double growRate = pow(1.7, delta);
	mHeight *= growRate;

	// Find how hi the limb should grow to
	double spawnLength = GetTree()->GetRNG()->Random(10.0, 13.0);

	// Is it time to spawn the 2 children??
	if (mChildren.size() == 0 && mHeight > spawnLength)
	{
		// Calaculates the probability of a leaf spawning
		double prob = 0.65 + (double(GetDepth()) - 5) * .05;
		prob = (prob <= 0.95) ? prob : 0.95;

		// First Child
		if (GetDepth() > 5 && GetTree()->GetRNG()->Random(0, 1) < prob )
		{
			auto leaf = make_shared<CLeaf>(this, GetTree());
			leaf->SetPosition(GetX(), GetY());
			leaf->SetAngle(GetTree()->GetRNG()->Random(-0.2, 0.2));
			leaf->SetDepth(this->GetDepth() + 1);
			mChildren.push_back(leaf);
		}
		else
		{
			auto limb = make_shared<CLimb>(this, GetTree());
			limb->SetAngle(GetTree()->GetRNG()->Random(-0.2, 0.2));
			limb->SetPosition(GetX(), GetY());
			limb->SetDepth(this->GetDepth() + 1);
			limb->SetDim();
			mChildren.push_back(limb);
		}

		// Second Child
		if (GetDepth() > 7 && GetTree()->GetRNG()->Random(0, 1) < 0.2)
		{
			auto fruit = make_shared<CFunctionalFruit>(this, GetTree());
			fruit->SetPosition(GetX(), GetY());
			fruit->SetAngle(GetTree()->GetRNG()->Random(-0.4, 0.4) + PI);
			fruit->SetDepth(this->GetDepth() + 1);
			mChildren.push_back(fruit);
			
			// Adds to the tree's list of fruit
			GetTree()->AddFruit(fruit);
		}
		else
		{
			auto limb = make_shared<CLimb>(this, GetTree());
			limb->SetAngle(GetTree()->GetRNG()->Random(-1.5, 1.5));
			limb->SetPosition(GetX(), GetY());
			limb->SetDepth(this->GetDepth() + 1);
			limb->SetDim();
			mChildren.push_back(limb);
		}
	}
}

/**
 * Sets the dimiensions of the limb using the pseudo-RNG
 */
void CLimb::SetDim()
{
	CPseudoRandom* rng = GetTree()->GetRNG();
	mWidth = rng->Random(40.0, 50.0) / (double(GetDepth()) * .8 + 1); // Width gets smaller at each depth
	mHeight = rng->Random(5.0, 10.0); // Height of the beginning nub
}

/**
 * This function calls harvest on its children, and if a child's harvest returns true (it's a fruit), it
 * will be harvested and removed from the tree
 * \returns false because a limb is not a fruit
 */
bool CLimb::HarvestFruit()
{
	// Loops through fruit children
	for (auto i = mChildren.begin(); i != mChildren.end(); i++)
	{
		auto child = *i;
		if (child->HarvestFruit()) // Is it a fruit
		{
			mChildren.erase(i);
			break; // Break becasue only one piece of fruit per limb
		}
	}

	return false;
}
