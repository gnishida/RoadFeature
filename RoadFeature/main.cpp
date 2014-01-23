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
	cv::Mat hist;
	GraphUtil::computeHistogram(r, hist);

	// １列にreduceすれば、角度のヒストグラムになる。
	cv::Mat histDir;
	cv::reduce(hist, histDir, CV_REDUCE_SUM, 0);

	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++) {
			std::cout << hist.at<float>(i, j) << ",";
		}
		std::cout << std::endl;
	}
}