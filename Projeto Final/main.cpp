
/*
 * Copyright (c) 2011. Philipp Wagner <bytefish[at]gmx[dot]de>.
 * Released to public domain under terms of the BSD Simplified license.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the organization nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 *   See <http:www.opensource.org/licenses/bsd-license>
 */

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/cv.h>
#include <vector>
#include <iostream>

using namespace cv;

using std::cout;
using std::endl;

bool R1(int R, int G, int B) {
    bool e1 = (R>95) && (G>40) && (B>20) && ((max(R,max(G,B)) - min(R, min(G,B)))>15) && (abs(R-G)>15) && (R>G) && (R>B);
    bool e2 = (R>220) && (G>210) && (B>170) && (abs(R-G)<=15) && (R>B) && (G>B);
    return (e1||e2);
}

bool R2(float Y, float Cr, float Cb) {
    bool e3 = Cr <= 1.5862*Cb+20;
    bool e4 = Cr >= 0.3448*Cb+76.2069;
    bool e5 = Cr >= -4.5652*Cb+234.5652;
    bool e6 = Cr <= -1.15*Cb+301.75;
    bool e7 = Cr <= -2.2857*Cb+432.85;
    return e3 && e4 && e5 && e6 && e7;
}

bool R3(float H, float S, float V) {
    return (H<25) || (H > 230);
}

Mat GetSkin(Mat const &src) {
    // allocate the result matrix
    Mat dst = src.clone();

    Vec3b cwhite = Vec3b::all(255);
    Vec3b cblack = Vec3b::all(0);

    Mat src_ycrcb, src_hsv;
    // OpenCV scales the YCrCb components, so that they
    // cover the whole value range of [0,255], so there's
    // no need to scale the values:
    cvtColor(src, src_ycrcb, CV_BGR2YCrCb);
    // OpenCV scales the Hue Channel to [0,180] for
    // 8bit images, so make sure we are operating on
    // the full spectrum from [0,360] by using floating
    // point precision:
    src.convertTo(src_hsv, CV_32FC3);
    cvtColor(src_hsv, src_hsv, CV_BGR2HSV);
    // Now scale the values between [0,255]:
    normalize(src_hsv, src_hsv, 0.0, 255.0, NORM_MINMAX, CV_32FC3);

    for(int i = 0; i < src.rows; i++) {
        for(int j = 0; j < src.cols; j++) {

            Vec3b pix_bgr = src.ptr<Vec3b>(i)[j];
            int B = pix_bgr.val[0];
            int G = pix_bgr.val[1];
            int R = pix_bgr.val[2];
            // apply rgb rule
            bool a = R1(R,G,B);

            Vec3b pix_ycrcb = src_ycrcb.ptr<Vec3b>(i)[j];
            int Y = pix_ycrcb.val[0];
            int Cr = pix_ycrcb.val[1];
            int Cb = pix_ycrcb.val[2];
            // apply ycrcb rule
            bool b = R2(Y,Cr,Cb);

            Vec3f pix_hsv = src_hsv.ptr<Vec3f>(i)[j];
            float H = pix_hsv.val[0];
            float S = pix_hsv.val[1];
            float V = pix_hsv.val[2];
            // apply hsv rule
            bool c = R3(H,S,V);

            if(!(a&&b&&c))
                dst.ptr<Vec3b>(i)[j] = cblack;
        }
    }
    return dst;
}


int main(int argc, const char *argv[]) {
    // Get filename to the source image:
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <image.ext>" << endl;
        exit(1);
    }
    // Load image & get skin proportions:
    Mat image = imread(argv[1]);
	Mat sav = image;
	Mat image2 = image;
	Mat hsv[3];
	std::vector<Mat> hsv2;
	cvtColor(image, image2, CV_BGR2HSV);
	split(image2,hsv);
	equalizeHist( hsv[2], hsv[2] );//Luminancia
	hsv2.push_back(hsv[0]);
	hsv2.push_back(hsv[1]);
	hsv2.push_back(hsv[2]);
	merge(hsv2,image2);
	cvtColor(image2, image, CV_HSV2BGR);
	//int VMax=51;//gaussian convolution
	//for(int i=1;i<VMax;i++)
	//GaussianBlur(image,image,Size(i,i),0);
	Mat gray;
	 /// Do the operation new_image(i,j) = alpha*image(i,j) + beta
 /*for( int y = 0; y < skin.rows; y++ )
    { for( int x = 0; x < skin.cols; x++ )
         { for( int c = 0; c < 3; c++ )
              {
      skin.at<Vec3b>(y,x)[c] =
         saturate_cast<uchar>( ( skin.at<Vec3b>(y,x)[c] ) + 60 );
             }
    }
    }*/

	int val=60;

  for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
	Point3_<uchar>* p = image.ptr<Point3_<uchar> >(i,j);
	
		p->z=(p->z)+val;
		p->y=(p->y)+val;
		p->x=(p->x)+val;	
        }
    }
    Mat skin = GetSkin(image);
    // Show the results:
    //namedWindow("original");
    //namedWindow("skin");
	cvtColor( skin, skin, CV_BGR2GRAY );
///começa aqui *************************************************

CascadeClassifier face_cascade;

	std::vector<Rect> faces;
	face_cascade.detectMultiScale( skin, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

 for( size_t i = 0; i < faces.size(); i++ )
  {
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    ellipse( sav, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );

    Mat faceROI = skin( faces[i] );

  }
///termina aqui *************************************************
	
	imshow("resultado" , sav );
	threshold(skin, skin, 0, 255, CV_THRESH_BINARY);
    //imshow("original", image);
    //imshow("skin", skin);

    waitKey(0);
    return 0;
}
