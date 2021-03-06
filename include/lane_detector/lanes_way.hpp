#ifndef _lanes_HPP
#define _lanes_HPP_

#include <iostream>
#include <string.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <eigen3/Eigen/Dense>
#include "slic.cpp"
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include "geometry_msgs/PoseStamped.h"
#include <sensor_msgs/image_encodings.h>
#include "sensor_msgs/Image.h"
#include <sensor_msgs/LaserScan.h>
//#include "opencv2/cudaarithm.hpp"
#include <tf/transform_datatypes.h>
#include "../src/library/gSLIC/FastImgSeg.h"
#include <tf/transform_listener.h>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#define SHOW 0
#define W 400
#define SUBSTRACTION_CONSTANT 30
#define INTENSITY_TH 140
#define PI 3.14159265

<<<<<<< f5cb4bf155597ceab254227a1ef8c474b31c7587
#define TH_REM_GRASS 190
#define TH_DOT 170 //130
#define TH_SMALL_SUPERPIXEL 20
=======
#define TH_REM_GRASS 140
#define TH_DOT 150 //130
#define TH_SMALL_SUPERPIXEL 10
>>>>>>> Final Worked code
#define TH_MIN_WHITE_REGION 0.5
#define NUM_ITER 1000
#define PPM 150
#define DIST_CHECK 300
#define KERNEL_SIZE 200
#define JUMP 300
#define MIN_GAP_BETWEEN_OBSTACLE_AND_LANE 150 
#define NAV_GAP 120
#define LAMBDA_THRESHOLD_FOR_HORIZONTAL_LANE 1
#define MIN_INLIER_DIST_THRESH 1500
#define JUMP_OF_WAYPOINT 15
#define extrapolation_factor 5
#define frames_to_skip_when_obstacle_detected 4
<<<<<<< f5cb4bf155597ceab254227a1ef8c474b31c7587
#define degree_for_horizontal 30
=======
#define degree_for_horizontal 40
>>>>>>> Final Worked code

#define THRESHOLD_FOR_ANY_LANE 70
#define LANE_THRESHOLD 70
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))


int wide = 400;
int no_of_random_points_for_dot = 200;
int dist_for_inlier = 10;

typedef struct
{
        double a, lam1, lam2, w;
} track;


using namespace cv;
using namespace Eigen;
using namespace std;
using namespace sensor_msgs;
using namespace message_filters;

// vector<double> generateWaypoint(Mat img,double a,double lm_1,double lm_2,double w);
// vector<double> generateWayPoint_2(Mat img,double a,double lm_1,double lm_2, double w);
bool IsAllowed(float lam1,float a,float lam2,float w,int rows,int cols);
vector<double> waypoint_objectivefunc(float *param, vector<int> obs, vector<double> predicted_waypoint,Mat img);
vector<double> waypoint_objectivefunc_l(float *param, vector<double> predicted_waypoint,Mat img);
void imageCb(const sensor_msgs::ImageConstPtr& msg);
double heading (Mat img, double a, double lam);
Point centroid(Mat img, double a, double lam);
vector<int> obstacle_coords (Mat img, vector<double> old_way);
vector<double> gen_new_way(Mat top_view_rgb,double a_gl,double lam_gl,double lam2_gl,double w_gl, vector<double>);
bool waypoint_on_obstacle(Mat img, vector<double>);
bool is_lane_horizontal (Mat img, float a, float lam1);
MatrixXd homo(3,3);  
sensor_msgs::LaserScan imageConvert(cv::Mat image);

vector<track> median;
vector<track> average;
double prev_xl;
vector<double> waypoint_prev;
vector<vector<int> > obstacles; //Point.x = left x coordinate of obstacle, Point.y = right x coordinate of obstacle 
vector<double> way_avg[3];
// double prev_600/4.2;
double curr_xl;
double curr_xr;
vector<double> waypoint_prev_2;
double prev_xl_2;
double prev_xr_2;
double curr_xl_2;
double curr_xr_2;
bool is_prev_single;
bool is_prev_single_left;
bool first_frame=true;
int left_prev_x;
int right_prev_x;
bool is_lane_left;
bool is_lane_single;
bool no_lane;
int dil_ko_churaya = 0;
int obstacle_detected = 0;


struct quadratic
{
	double a,b,c;
	int inliers;
};

int j=0,frame_skip=-1;
bool first_f=true;
int counter = 0;
vector<double> old_waypoint;



class Lanes
{
	Mat img,img_gray,bisect,top_view,points,curves;
	vector<Vec2i> L,R;
	vector<Point> left_lane,right_lane;
	int frameWidth;
	int frameHeight;
	quadratic left_fy,right_gy;
	quadratic array_l[5],array_r[5];
	double gamma_,v,sigma;
	double THRESH;

public:
	Mat top_view_rgb;
	Mat linesd;
	Lanes(Mat);
  	void joiner_of_white_spaces_in_obstacles(Mat img);
	void remove_obstacles();
	void Mix_Channel();
	void Intensity_distribution();
	void display();
	void Intensity_adjust();
	void Brightest_Pixel_col();
	void Brightest_Pixel_row();
	void Edge();
	void Hough();
	void Dilation();
	void topview();
	void control_points();
	void control_vanishing();
	void curve_fitting();
	void plot_quad(quadratic,int);
	quadratic RANSAC(vector<Point>);
	void shift_parabola(quadratic ,int );
	int IsValid(Mat , int, int );
	void remove_grass();
	float* parabola_params(Point*);
	void parabola();
	void superpixels();
	void preprocess_lab();
	void preprocess_indu();
	void preprocess_old();
	vector<double> generateWaypoint(Mat img,double a,double lm_1,double lm_2,double w);
	vector<double> generateWayPoint_2(Mat img,double a,double lm_1,double lm_2, double w);
	vector<double> quadraticFit(vector<Point> *data1);
	vector<double> gen_way(Mat img, Mat mario, float a, float lam1, float lam2, float w);


};


#endif 
