/**
 * \file PictureFactory.cpp
 *
 * \author Charles B. Owen
 */

#include "pch.h"
#include "PictureFactory.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "ImageDrawable.h"

using namespace std;
using namespace Gdiplus;

CPictureFactory::CPictureFactory()
{
}


CPictureFactory::~CPictureFactory()
{
}


/** Factory method to create a new picture.
* \returns The created picture
*/
std::shared_ptr<CPicture> CPictureFactory::Create()
{
    shared_ptr<CPicture> picture = make_shared<CPicture>();

    // Create the background and add it
    auto background = make_shared<CActor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(Point(-100, 0));
    auto backgroundI = make_shared<CImageDrawable>(L"Background", L"images/Background.png");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

	// Create and add Sparty
	CSpartyFactory sfactory;
	auto sparty = sfactory.Create();

	sparty->SetPosition(Point(200, 500));
	picture->AddActor(sparty);

    // Create and add Harold
    CHaroldFactory factory;
    auto harold = factory.Create();
	auto flag = factory.CreateFlag();

	// This is where the flag will start out (Drawn before harold so flag appears behind hand)
	flag->SetPosition(Point(355, 380));
	picture->AddActor(flag);

    // This is where Harold will start out.
    harold->SetPosition(Point(400, 500));

    picture->AddActor(harold);

    return picture;
}
