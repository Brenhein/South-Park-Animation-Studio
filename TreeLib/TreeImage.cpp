#include "pch.h"
#include "TreeImage.h"

using namespace Gdiplus;
using namespace std;

CTreeImage::CTreeImage(const std::wstring name)
{
	wstring filePath = L"images/" + name;
	mImage = shared_ptr<Bitmap>(Bitmap::FromFile(filePath.c_str()));
	if (mImage->GetLastStatus() != Ok)
	{
		wstring msg(L"Failed to open ");
		msg += filePath;
		AfxMessageBox(msg.c_str());
	}
}

void CTreeImage::Draw(Gdiplus::Graphics* graphics, double angle, double scale, double x, double y)
{
	auto state = graphics->Save();
	graphics->TranslateTransform((float)x, (float)y);
	graphics->RotateTransform((float)(angle * RtoD));
	graphics->ScaleTransform((float)scale, (float)scale);
	graphics->DrawImage(mImage.get(), -(int)mImage->GetWidth() / 2,
		-(int)mImage->GetHeight(),
		mImage->GetWidth(), mImage->GetHeight());
	graphics->Restore(state);
}
