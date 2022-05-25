/**
 * \file TreeImage.h
 *
 * \author Brenden Hein
 *
 * Class that represents an image used by our system.
 */


#pragma once
#include <memory>
#include <string>

 /// Constant ratio to convert radians to degrees
const double RtoD = 57.295779513;

/**
 * Class that represents an image used by our system.
 */
class CTreeImage
{
public:
	/// The construcotr
	/// \param name The filename
	CTreeImage(const std::wstring name);

	/// Default constructor/disabled
	CTreeImage() = delete;

	/// Copy constructor/disabled
	CTreeImage(const CTreeImage&) = delete;

	/// Virtual Destructor
	virtual ~CTreeImage() {}

	/// Gets the image
	/// \returns The image associated witht he class
	std::shared_ptr<Gdiplus::Bitmap> GetImage() { return mImage; }

	/// Draws the image
	/// \param graphics The graphics object
	/// \param angle The angle to draw at
	/// \param scale How big the image should be
	/// \param x The x position
	/// \param y The y position
	void CTreeImage::Draw(Gdiplus::Graphics* graphics, double angle, double scale, double x, double y);

private:
	std::shared_ptr<Gdiplus::Bitmap> mImage; ///< The part image
};
