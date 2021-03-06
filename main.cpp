//
// author: ???ɵ?????
//

#include <opencv2/opencv.hpp>
#include "meanshift.h"

void test_meanshift()
{
	auto BGRimg = cv::imread("D:\\2.png"); // read image.
	cv::imshow("display", BGRimg);
	cv::waitKey(0);
	//cv::imshow("dsdfisplay", BGRimg);
	//cv::waitKey(0);

	Segmentation::Image imgRGB;
	for (int i = 0; i < BGRimg.rows; i++)
	{
		Segmentation::Row row;
		for (int j = 0; j < BGRimg.cols; j++)
		{
			auto temp = BGRimg.at<cv::Vec3b>(i, j);
			row.emplace_back(Segmentation::Color(temp[2], temp[1], temp[0]));
		}
		imgRGB.push_back(row);
	}  // convert cv::Mat to Segmentation::Image
	printf("OK1!\n");
	Segmentation::Image imgLUV;
	Segmentation::RGBimage2LUVimage(imgRGB, imgLUV);   // convert from RGB color space to LUV color space.
	printf("OK2!\n");
	Segmentation::Image meanshift_imgLUV;
	printf("OK3!\n");
	//Segmentation::meanshift_filter(imgLUV,meanshift_imgLUV); // meanshift
	Segmentation::meanshift_segmentation(imgLUV, meanshift_imgLUV, 1000);
	printf("OK4!\n");
	Segmentation::LUVimage2RGBimage(meanshift_imgLUV, imgRGB);   // convert from LUV color space to RGB color space.
	printf("OK5!\n");
	cv::Mat output_image(imgRGB.size(), imgRGB[0].size(), CV_8UC3);
	for (unsigned long i = 0; i < imgRGB.size(); i++)
	{
		for (unsigned long j = 0; j < imgRGB[0].size(); j++)
		{
			output_image.at<cv::Vec3b>(i, j)[0] = imgRGB[i][j][2];
			output_image.at<cv::Vec3b>(i, j)[1] = imgRGB[i][j][1];
			output_image.at<cv::Vec3b>(i, j)[2] = imgRGB[i][j][0];
		}
	}  // convert Segmentation::Image to cv::Mat

	//cv::imshow("display", BGRimg);
	cv::imshow("outdisplay", output_image);
	cv::waitKey(0);
}

int main() {
	test_meanshift();
	return 0;
}