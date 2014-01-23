/**
 * 道路網を、画像として保存する。
 *
 * @author Gen Nishida
 * @version 1.0
 */

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "GraphUtil.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		std::cout << "Usage: RoadFeature <GSM file>" << std::endl;
		return 1;
	}

	RoadGraph r;
	GraphUtil::loadRoads(r, argv[1]);

	// エッジ長のヒストグラムを作成
	cv::MatND histEdgeLength;
	histEdgeLength = GraphUtil::computeEdgeLengthHistogram(r);

	std::cout << histEdgeLength << std::endl;
}