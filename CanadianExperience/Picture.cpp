/**
 * \file Picture.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "Picture.h"
#include "Actor.h"
#include "TreeDrawable.h"
#include "TreeFactory.h"
#include "TreeSeedDlg.h"

using namespace Gdiplus;
using namespace xmlnode;
using namespace std;

/* Constants */
int tree1X = 870; ///< Tree1's x position
int tree1Y = 490; ///< Tree1's y position
int basket1X = 780; ///< basket1's x position
int basket1Y = 460; ///< basket1's y position

int tree2X = 550; ///< Tree2's x position
int tree2Y = 500; ///< Tree2's y position
int basket2X = 660; ///< Basket2's position
int basket2Y = 500; ///< Basket2's position

/**
 * Constructor
 */
CPicture::CPicture()
{
}


/**
 * Destructor
 */
CPicture::~CPicture()
{
}

/** Set the current animation time
*
* This forces the animation of all
* objects to the current animation location.
* \param time The new time.
*/
void CPicture::SetAnimationTime(double time)
{
	mTimeline.SetCurrentTime(time);
	UpdateObservers();

	for (auto actor : mActors)
	{
		actor->GetKeyframe();
	}
}

/** Add an observer to this picture.
* \param observer The observer to add
*/
void CPicture::AddObserver(CPictureObserver *observer)
{
    mObservers.push_back(observer);
}

/** Remove an observer from this picture
* \param observer The observer to remove
*/
void CPicture::RemoveObserver(CPictureObserver *observer)
{
    auto loc = find(std::begin(mObservers), std::end(mObservers), observer);
    if (loc != std::end(mObservers))
    {
        mObservers.erase(loc);
    }
}

/** Update all observers to indicate the picture has changed.
*/
void CPicture::UpdateObservers()
{
    for (auto observer : mObservers)
    {
        observer->UpdateObserver();
    }
}

/** Draw this picture on a device context
* \param graphics The device context to draw on
*/
void CPicture::Draw(Gdiplus::Graphics *graphics)
{
    for (auto actor : mActors)
    {
        actor->Draw(graphics);
    }
}


/** Add an actor to this picture.
* \param actor The actor to add
*/
void CPicture::AddActor(std::shared_ptr<CActor> actor)
{
    mActors.push_back(actor);
    actor->SetPicture(this);
}


/** Get the current animation time.
* \returns The current animation time
*/
double CPicture::GetAnimationTime()
{
    return mTimeline.GetCurrentTime();
}


/**
* Save the picture animation to a file
* \param filename File to save to.
*/
void CPicture::Save(const std::wstring &filename)
{
    //
    // Create an XML document
    //
    auto root = CXmlNode::CreateDocument(L"anim");

    // Save the timeline animation into the XML
    mTimeline.Save(root);

	// Saves the tree actors if they exist
	auto trees = root->AddChild(L"Trees");
	for (auto actor : mActors)
	{
		auto drawable = actor->GetRoot();
		if (actor->IsTree())
		{
			auto tree = trees->AddChild(drawable->GetName());
			actor->GetRoot()->Save(tree); // go save the tree
		}
	}

    try
    {
        root->Save(filename);
    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }
}



/**
* Load a picture animation from a file
* \param filename file to load from
*/
void CPicture::Load(const std::wstring &filename)
{
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        auto root = CXmlNode::OpenDocument(filename);

        // Load the animation from the XML
        mTimeline.Load(root);

		//
        // Loads the trees if they exist
		//

		Clear(); // Clears the trees/baskets
		
		// Finds the node that holds the trees
		for (auto node : root->GetChildren())
		{
			if (node->GetType() == NODE_ELEMENT && node->GetName() == L"Trees")
			{
				// Loops through the saved trees (if they exist)
				for (auto treeNode : node->GetChildren())
				{
					// Gets the data from the xml
					int seed = treeNode->GetAttributeIntValue(L"Seed", 0);
					int startFrame = treeNode->GetAttributeIntValue(L"StartFrame", 0);
					int harvestFrame = treeNode->GetAttributeIntValue(L"HarvestFrame", 0);

					CTreeFactory treeFactory;

					shared_ptr<CActor> actor = make_shared<CActor>(L"Tree");
					actor->SetIsTree(true);

					shared_ptr<CTree> tree = treeFactory.CreateTree(); // Creates the new tree drawable
					shared_ptr<CBasket> basket = treeFactory.CreateBasket(); // Creates the new basket drawable

					shared_ptr<CTreeDrawable> treeDrawable = nullptr;
					shared_ptr<CBasketDrawable> basketDrawable = nullptr;

					//
					// Isolates tree-specific tasks
					//

					if (treeNode->GetName() == L"Tree1")
					{
						treeDrawable = make_shared<CTreeDrawable>(L"Tree1", tree);
						basketDrawable = make_shared<CBasketDrawable>(L"Basket1", basket);

						tree->SetRootLocation(tree1X, tree1Y);
						basket->SetBasketLocation(basket1X, basket1Y);
						mIsTree1 = true;
					}
					else
					{
						treeDrawable = make_shared<CTreeDrawable>(L"Tree2", tree);
						basketDrawable = make_shared<CBasketDrawable>(L"Basket2", basket);

						tree->SetRootLocation(tree2X, tree2Y);
						basket->SetBasketLocation(basket2X, basket2Y);
						mIsTree2 = true;

					}

					// Sets the values for the tree
					tree->SetSeed(seed);
					treeDrawable->SetStartFrame(startFrame);
					treeDrawable->SetHarvestFrame(harvestFrame);
					treeDrawable->SetBasket(basketDrawable.get());

					// Adds the tree drawable to the actor
					actor->SetRoot(treeDrawable);
					actor->AddDrawable(basketDrawable); // so basket is behind tree
					actor->AddDrawable(treeDrawable);
					treeDrawable->AddChild(basketDrawable);

					AddActor(actor);
				}
			}
		}

        SetAnimationTime(0);
        UpdateObservers();
    }
	catch (CXmlNode::Exception ex)
	{
		AfxMessageBox(ex.Message().c_str());
	}
}


/**
 * Creates the actor that will hold a single tree and basket
 * \param treeNum Which tree is being created (used for hardcoding position)
 * \returns If the actor was succesfully created or not
 */
void CPicture::CreateTreeActor(int treeNum)
{
	CTreeFactory treeFactory;

	// Creates Tree Actor
	shared_ptr<CActor> actor = make_shared<CActor>(L"Tree");
	actor->SetIsTree(true);

	// Creates the new tree drawable
	shared_ptr<CTree> tree = treeFactory.CreateTree();
	shared_ptr<CTreeDrawable> treeDrawable = make_shared<CTreeDrawable>(L"Tree" + to_wstring(treeNum), tree);

	// Creates the new basket drawable
	shared_ptr<CBasket> basket = treeFactory.CreateBasket();
	shared_ptr<CBasketDrawable> basketDrawable = make_shared<CBasketDrawable>(L"Basket" + to_wstring(treeNum), basket);

	// Generates a seed for the tree
	CTreeSeedDlg dlg(tree);
	INT_PTR ret = dlg.DoModal();

	// If the user did not press ok on the dialog box
	if (ret != IDOK)
	{
		return; // Don't create the tree and basket
	}

	// Adds thre tree drawable to the actor
	actor->SetRoot(treeDrawable);
	actor->AddDrawable(basketDrawable); // so basket is behind tree
	actor->AddDrawable(treeDrawable);
	treeDrawable->AddChild(basketDrawable);

	// Sets the frame for the tree
	int currentFrame = GetTimeline()->GetCurrentFrame();
	treeDrawable->SetStartFrame(currentFrame);

	// Sets the assocaition between the 2 drawables
	treeDrawable->SetBasket(basketDrawable.get());

	// Figures out with location to draw the tree at
	switch (treeNum)
	{
	case 1:
		tree->SetRootLocation(tree1X, tree1Y);
		basket->SetBasketLocation(basket1X, basket1Y);
		mIsTree1 = true;
		break;
	case 2:
		tree->SetRootLocation(tree2X, tree2Y);
		basket->SetBasketLocation(basket2X, basket2Y);
		mIsTree2 = true;
		break;
	}

	AddActor(actor);
	UpdateObservers();
}


/**
 * Clears the trees out if there are any
 */
void CPicture::Clear()
{
	for (auto it = mActors.begin(); it != mActors.end(); it++)
	{
		if ((*it)->IsTree())
		{
			mActors.erase(it--);
		}
	}

	mIsTree1 = false;
	mIsTree2 = false;
}
