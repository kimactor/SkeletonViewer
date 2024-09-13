#pragma once
#include <Eigen/Core>
#include <opencv2/core/cuda.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "SkeletonData.h"

namespace SkeletonViewerApplication
{
	struct SkeletonDetection
	{
		SkelType type;
		std::vector<Eigen::Matrix3Xf> joints;
		std::vector<Eigen::MatrixXf> pafs;

		SkeletonDetection() { type = SkelType::SKEL_TYPE_NONE; }
		SkeletonDetection(const SkelType& _type);
		SkeletonDetection Mapping(const SkelType& tarType);
		std::vector<Eigen::Matrix3Xf> Associate(const int& jcntThresh = 5);

	};

	std::vector<SkeletonDetection> ParseDetections(const std::string& filename);
	void SerializeDetections(const std::vector<SkeletonDetection>& detections, const std::string& filename);


}