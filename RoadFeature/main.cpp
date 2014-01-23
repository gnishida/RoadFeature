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
#include "BBox.h"

int main(int argc, char *argv[]) {
	if (argc < 4) {
		std::cout << "Usage: RoadFeature <GSM file> <size> <cell size>" << std::endl;
		return 1;
	}

	RoadGraph r;
	GraphUtil::loadRoads(r, argv[1]);

	int size = atoi(argv[2]);
	int cellSize = atoi(argv[3]);

	for (int v = 0; v < size; v += cellSize) {
		for (int u = 0; u < size; u += cellSize) {
			BBox box(QVector2D(u, v));
			box.addPoint(QVector2D(u + cellSize, v + cellSize));

			// セルの道路網を抽出
			RoadGraph patch;
			GraphUtil::copyRoads(r, patch);
			GraphUtil::extractRoads(patch, box, true);

			// セルの道路網のヒストグラムを作成
			cv::Mat hist;
			GraphUtil::computeHistogram(patch, hist);

			// 出力
			for (int i = 0; i < hist.rows; i++) {
				for (int j = 0; j < hist.cols; j++) {
					std::cout << hist.at<float>(i, j) << ",";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
}