//
// Created by abdoulayedia on 18.01.2023
//
#include "ImageHandler.h"

namespace sse {
	cv::Mat ImageHandler::TextureToOpenCVMat(const sf::Texture &texture) {
		sf::Image img = texture.copyToImage();

		uint16_t width  = img.getSize().x;
		uint16_t height = img.getSize().y;

		const sf::Uint8 *pixels = img.getPixelsPtr();

		return cv::Mat(height, width, CV_8UC4, (void *)pixels);
	}

	sf::Texture ImageHandler::OpenCVMatToTexture(const cv::Mat &mat) {
		sf::Texture texture;
		texture.create(mat.cols, mat.rows);

		sf::Image img;
		img.create(mat.cols, mat.rows, mat.ptr());

		texture.update(img);

		return texture;
	}

	std::vector<sf::IntRect> ImageHandler::SliceFrames(const sf::Texture &texture, const sf::IntRect &roiRect) {
		// Declare OpenCV matrices and a vector of rectangles
		cv::Mat                  original, img, gray, bw;
		cv::Mat                  close, dil, blurred;
		std::vector<sf::IntRect> slices;

		// Convert the texture to an OpenCV matrix
		original = TextureToOpenCVMat(texture);

		// Get a region of interest matrix from the original matrix using the
		// roiRect
		img = original(cv::Rect(roiRect.left, roiRect.top, roiRect.width, roiRect.height));

		// Convert the region of interest matrix to grayscale
		cvtColor(img, gray, cv::COLOR_BGR2GRAY);

		cv::GaussianBlur(gray, blurred, {3, 3}, 0);

		// Apply Otsu's threshold to the grayscale matrix to create a black and white image
		double thresh = cv::threshold(blurred, bw, 0.0, 255.0, cv::THRESH_BINARY);

		// Create a 3x3 rectangular kernel for morphological transformations
		cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, {3, 3});

		// Apply a closing morphological transformation to the black and white image
		morphologyEx(bw, close, cv::MORPH_CLOSE, kernel, {-1, -1}, 1);

		// Dilate the closing image
		dilate(close, dil, kernel, {-1, -1}, 1);
		cv::GaussianBlur(dil, blurred, {3, 3}, 0);

		cv::morphologyEx(blurred, blurred, cv::MORPH_CLOSE, kernel, {-1, -1}, 1);

		// Find the contours in the dilated image
		std::vector<std::vector<cv::Point>> contours;
		findContours(blurred, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

		// Iterate through the contours
		int spriteCount = 0;
		for (auto c : contours) {
			// Get the bounding rectangle of the contour
			cv::Rect bRect = boundingRect(c);

			// Calculate the area of the contour
			double area = contourArea(c);

			// Skip contours with small areas
			if (area < 50) {
				continue;
			}

			// Add the bounding rectangle to the vector of rectangles
			slices.push_back({bRect.x, bRect.y, bRect.width, bRect.height});
		}

		return slices;
	}

	sf::Color ImageHandler::ImColorToSFColor(const ImColor &color) {
		return sf::Color(color.Value.x * 255, color.Value.y * 255, color.Value.z * 255, color.Value.w * 255);
	}

	ImColor ImageHandler::SFColorToImColor(const sf::Color &color) {
		return ImColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
	}

	sf::Image ImageHandler::ReplaceBackgroundColor(const sf::Image &img,
	                                               const sf::Color &colorToReplace,
	                                               const sf::Color &newColor,
	                                               double           threshold) {
		sf::Image newImg = img;
		uint16_t  width  = newImg.getSize().x;
		uint16_t  height = newImg.getSize().y;

		const sf::Uint8 *pixels = newImg.getPixelsPtr();

		for (uint16_t i = 0; i < height; ++i) {
			for (uint16_t j = 0; j < width; ++j) {
				int r = colorToReplace.r - newImg.getPixel(j, i).r;
				int g = colorToReplace.g - newImg.getPixel(j, i).g;
				int b = colorToReplace.b - newImg.getPixel(j, i).b;

				double distance = sqrt(r * r + g * g + b * b);

				// If the distance is below the threshold, set the pixel color to the new color
				if (distance < threshold) {
					newImg.setPixel(j, i, newColor);
				}
			}
		}

		return newImg;
	}

	sf::Image ImageHandler::ReplaceBackgroundColor(const sf::Image &img,
	                                               int              x,
	                                               int              y,
	                                               const sf::Color &newColor,
	                                               double           threshold) {
		if (x < 0 || x >= img.getSize().x || y < 0 || y >= img.getSize().y)
			throw std::out_of_range("The coordinates of the pixel are out of range");

		return ReplaceBackgroundColor(img, img.getPixel(x, y), newColor, threshold);
	}

	sf::Image ImageHandler::ReplaceBackgroundColor(sf::Texture     &texture,
	                                               const sf::Color &colorToReplace,
	                                               const sf::Color &newColor,
	                                               double           threshold) {
		return ReplaceBackgroundColor(texture.copyToImage(), colorToReplace, newColor, threshold);
	}

	sf::Image ImageHandler::ReplaceBackgroundColor(sf::Texture     &texture,
	                                               int              x,
	                                               int              y,
	                                               const sf::Color &newColor,
	                                               double           threshold) {
		if (x < 0 || x >= texture.getSize().x || y < 0 || y >= texture.getSize().y)
			throw std::out_of_range("The coordinates of the pixel are out of range");

		return ReplaceBackgroundColor(texture.copyToImage(), x, y, newColor, threshold);
	}
} // namespace sse
