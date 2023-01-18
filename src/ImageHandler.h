//
// Created by abdoulayedia on 18.01.2023
//
#pragma once

#include "constants.h"

#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace sse {
	// ImageManager
	class ImageHandler {
	  public:
		static cv::Mat                  TextureToOpenCVMat(const sf::Texture& texture);
		static sf::Texture              OpenCVMatToTexture(const cv::Mat& mat);
		static std::vector<sf::IntRect> SliceFrames(const sf::Texture& texture, const sf::IntRect& roiRect);
		static sf::Image                ReplaceBackgroundColor(const sf::Image& img,
		                                                       const sf::Color& colorToReplace = sf::Color::White,
		                                                       const sf::Color& newColor       = sf::Color::Transparent,
		                                                       double           threshold      = 1.0);
		static sf::Image                ReplaceBackgroundColor(const sf::Image& img,
		                                                       int              x,
		                                                       int              y,
		                                                       const sf::Color& newColor  = sf::Color::Transparent,
		                                                       double           threshold = 1.0);
		static sf::Image                ReplaceBackgroundColor(sf::Texture&     texture,
		                                                       const sf::Color& colorToReplace = sf::Color::White,
		                                                       const sf::Color& newColor       = sf::Color::Transparent,
		                                                       double           threshold      = 1.0);
		static sf::Image                ReplaceBackgroundColor(sf::Texture&     texture,
		                                                       int              x,
		                                                       int              y,
		                                                       const sf::Color& newColor  = sf::Color::Transparent,
		                                                       double           threshold = 1.0);

	  private:
	};
} // namespace sse
