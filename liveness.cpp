
#include "liveness.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <iterator>
#include "compare.h"
#include <thread>
#include <stdlib.h>
#include <memory.h>
#include <dirent.h>
#include "baidu_face_api.h"
#include "image_base64.h"
#include "cv_help.h"
#include "image_buf.h"
#include "json/json.h"
Liveness::Liveness()
{
}

Liveness::~Liveness()
{
}

/* void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
         
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
} */

std::vector<std::string> read_data(const char *m){
    
    /* DIR *dir;
    std::string txt_path = "/home/shen/fr_ws/src/test_face/";
    dir = opendir((char *) txt_path.c_str()); */
    std::ifstream in(m); 
    //cout << in << endl; 
    //string filename;  
    std::string line;
    std::vector<std::string>  v;
    //std::string s;
    if(in) // 有该文件  
    {  
        while(getline(in, line))
        {
            v.push_back(line);
        } 
        
    }
    else // 没有该文件  
    {  
        std::cout <<"no such file" << std::endl;  
    }  
    //string s = "a,b,c,d,e,f";
    //vector<string> v;
    //cout << line.size() << endl;
    //cout << line << endl;
    //SplitString(line, v,","); //可按多个字符来分隔; 
    std::cout << v.size() << std::endl;
    std::cout << "11111111111111111111111111111111111111111111111111111111" << std::endl;
    return v;
} 

int name_index(std::vector<std::string> v, std::string name){
    int index;
    std::vector<std::string>::iterator iter = std::find(v.begin(), v.end(), name);
    if (iter==v.end())
    {
        std::cout << "error!" << std::endl;
    }
    else
    {
        std::cout << "the index of value" << (*iter) << " is " << std::distance(v.begin(), iter) << std::endl;
    }
    index = std::distance(v.begin(),iter);
    std::cout << index << std::endl;
    return std::distance(v.begin(),iter);  
}

/* std::string user_name[18]={"chaileigang","chensijia","duanxintong","kangyuchangxia","lianlaoshi","lihongbin",
"liujianshan","lizhuoyang","luoyucui","shenhao","shijianhao","sunyuzhe","wangmeng",
"zhaiwenpeng","zhangchi","zhaozhuang","zhengwenjian","zhouyanhong"}; */
//std::string user_name[18] = {"柴雷刚","陈思佳","段欣彤","康玉嫦霞","连老师","李鸿彬","刘建珊","李卓阳","洛玉翠","申毫","史佳豪","孙玉哲","王老师","翟文鹏","张驰","黄壮","郑文键","周艳红"};
 
//std::string user_path[18]={"/home/shen/fr_ws/src/test_face/dataset/face_data/chaileigang/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/chensijia/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/duanxintong/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/kangyuchangxia/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/lianlaoshi/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/lihongbin/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/liujianshan/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/lizhuoyang/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/luoyucui/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/shenhao/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/shijiahao/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/sunyuzhe/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/wangmeng/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/zhaiwenpeng/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/zhangchi/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/zhaozhuang/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/zhengwenjian/1.jpg","/home/shen/fr_ws/src/test_face/dataset/face_data/zhouyanhong/1.jpg"};
std::vector<std::string> user_name = read_data("/home/shen/fr_ws/src/test_face/name.txt");
std::vector<std::string> user_path = read_data("/home/shen/fr_ws/src/test_face/path.txt");
std::vector<std::string> hello_name = read_data("/home/shen/fr_ws/src/test_face/hello_name.txt");
int per_num = user_name.size();




//define feature label
    using Feature = std::vector<float>;
    float score_all[50];
    int max_score_location;
    float max_score;
    std::string max_name;
    


const float *feature_base = nullptr;Feature v_feature_base;
/*
const float *feature2 = nullptr;const float *feature3 = nullptr;
Feature v_feature2;Feature v_feature3;Feature v_feature4;Feature v_feature5;
Feature v_feature6;Feature v_feature7;Feature v_feature8;Feature v_feature9;Feature v_feature10;
Feature v_feature11;Feature v_feature12;Feature v_feature13;Feature v_feature14;Feature v_feature15;
Feature v_feature16;Feature v_feature17;Feature v_feature18;Feature v_feature19;Feature v_feature20;
const float *feature4 = nullptr;const float *feature5 = nullptr;
const float *feature6 = nullptr;const float *feature7 = nullptr;const float *feature8 = nullptr;
const float *feature9 = nullptr;const float *feature10 = nullptr;const float *feature11 = nullptr;
const float *feature12 = nullptr;const float *feature13 = nullptr;const float *feature14 = nullptr;
const float *feature15 = nullptr;const float *feature16 = nullptr;
*/
Feature Feature_dataset[50];


void Liveness::initial_face_feature(BaiduFaceApi *api)
{      
	for(int p=0;p<per_num;p++)
        {
		    cv::Mat m = cv::imread(user_path[p]);
            int count_base = api->get_face_feature(m, feature_base);
            v_feature_base.assign(feature_base, feature_base + count_base);
		    Feature_dataset[p]=v_feature_base;
        }


}

std::string Liveness::match_face(BaiduFaceApi *api)
{
	    
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
    cv::Mat frame_image = cv::imread("usb_track.jpg");
    //cv::Mat frame_image = cv::imread("3.jpg");
    //cv::imwrite("/home/shen/fr_ws/src/test_face/dataset/1.jpg", frame_image);
    int size = api->track(track_info, frame_image, 3);
    Feature v_feature1;
    Feature v_feature2;
    std::string hello_message;
    for(int z=0;z<size;z++)
    {
        // 获取特征
        int index = 0;
        const float *feature_database = nullptr;
        const float *feature =nullptr;
        TrackFaceInfo info = track_info->at(z);
        int dim_count = api->get_face_feature_by_face(frame_image, info, feature);
        v_feature1.assign(feature, feature + dim_count);
        //std::cout<<"dim count is:"<<dim_count<<std::endl;
        for(int q=0;q<per_num;q++)
        {   
            /*
            cv::Mat m = cv::imread(user_path[q]);
            int count = api->get_face_feature(m, feature_database);
            v_feature2.assign(feature_database, feature_database + count);
            */
            v_feature2 = Feature_dataset[q];
            float score = api->compare_feature(v_feature1, v_feature2);
            score_all[q] = score;
        }
        max_score = score_all[0];
        max_score_location = 0;
        for(int k=0;k<per_num;k++)
        {
            if(max_score<score_all[k])
            {
                max_score = score_all[k];
                max_score_location = k;
                max_name = user_name[max_score_location];
            }
            else
            {
                max_score = max_score;
                max_score_location = max_score_location;
                max_name = user_name[max_score_location];
            }
        }
        //strcpy(name[z],max_name.c_str());
        


	    std::cout<<"max score is:"<<max_score<<std::endl;
        std::cout<<"max location is:"<<max_score_location<<std::endl;
        if(max_score>45)
	    {
		
            std::cout<<"the nearest face is: "<<max_name<<std::endl;
            std::cout<<"person   "<<z+1<<"  is: "<<max_name<<std::endl;
            std::cout << max_name << std::endl;
            index = name_index(user_name, max_name);
            hello_message.append(hello_name[index]);
	    }
	    else
	    {
		    std::cout<<"no such person in the face dataset."<<std::endl;
            hello_message.append("陌生人");
	    }
    }
    
    return hello_message;       
}





// usb摄像头人脸检测
void Liveness::usb_track_face_info(BaiduFaceApi *api)
{
   
    int device = 1; // 默认检测摄像头为0,若不对，可依次修改为1-10,实际上为您设备接上摄像头后认定的图像设备id
    cv::VideoCapture cap(device);
    cap.set(CV_CAP_PROP_AUTOFOCUS, true);//设置自动对焦
    if (!cap.isOpened())
    {
        std::cout << "open camera error" << std::endl;
        return;
    }
    cv::Mat frame;
    bool stop = false;
    int index = 0;
    bool save_file = true; //可选择是否保存检测到的图片
    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
    while (!stop)
    {
        cap >> frame;
        cv::imwrite("1.jpg", frame);
        track_info->clear();
        
        int size = api->track(track_info, frame, 3);
        for (int i = 0; i < size; i++)
        {
            TrackFaceInfo info = track_info->at(i);
            std::cout << "in Liveness::usb_track score is:" << info.score << std::endl;
            // 人脸框信息
            FaceInfo ibox = info.box;
            // 角度
            std::cout << "in Liveness::usb_track mAngle is:" << ibox.mAngle << std::endl;
            // 人脸宽度
            std::cout << "in Liveness::usb_track mWidth is:" << ibox.mWidth << std::endl;
            // 中心点x，y坐标
            std::cout << "in Liveness::usb_track mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::usb_track mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> headPose = info.headPose;
            // 返回x，y，z三个角度的人脸角度
            for (int k = 0; k < headPose.size(); k++)
            {
                float angle = headPose.at(k);
                std::cout << "in Liveness::usb_track angle is:" << angle << std::endl;
            }
            //画人脸框
            box = CvHelp::bounding_box(info.landmarks);
            CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
            // 画关键点轮廓
            CvHelp::draw_shape(info.landmarks, frame, cv::Scalar(0, 255, 0));

            // frame为视频帧，可根据采集到的人脸信息筛选需要的帧
            // 以下为保存图片到本地的示例，可根据采集信息有选择的保存
            if (save_file)
            {
                save_file = true;
                cv::imwrite("usb_track.jpg", frame);

                
            }
                stop = true;
		break;
           
          //  std::string res_attr = api->face_attr_by_face(frame, info);
          //  std::cout<<"res attr is:"<< i << "---" << res_attr << std::endl;

           
        } 
        if (!frame.empty())
        {
           
            imshow("face", frame);
            cv::waitKey(1);
            std::cout << "mat not empty" << std::endl;
         
        }
        else
        {
            std::cout << "mat is empty" << std::endl;
        }
        frame.release();
       
    }
    delete track_info;
}


void Liveness::image_track_face_info(BaiduFaceApi *api)
{
   
    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
    std::string img_path = "duizhao.jpg";
    int size = api->track(track_info, img_path.c_str(), 2,1);

    if (size > 0)
    {
       for (int i = 0; i < size; i++)
	{
	    TrackFaceInfo info = track_info->at(i);
	    std::cout << "in Liveness::image_track_face_info score is:" << info.score << std::endl;
	    // 人脸框信息
	    FaceInfo ibox = info.box;
	    // 角度draw_face_info:image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
	    // 人脸宽度
	    std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
	    // 中心点X，Y坐标
	    std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
	    std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
	    std::vector<float> headPose = info.headPose;
	    // 返回x y z三个角度的人脸角度
	    for (int k = 0; k < headPose.size(); k++)
	    {
                float angle = headPose.at(k);
		std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
	    }
	    // 画人脸框
	   // box = CvHelp::bounding_box(info.landmarks);
	   // CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
	    // 画关键点轮廓
	    //CvHelp::draw_shape(info.landmarks, frame, cv::Scalar(0, 255, 0));
	}
    }
    else
    {
	std::cout << "image has no face!" << std::endl;
    }

	/*if (!frame.empty())
	{
	    std::cout << "11111!" << std::endl;
	    cv::namedWindow("face",CV_WINDOW_AUTOSIZE);
	    std::cout << "22222!" << std::endl;
	   // imshow("face", frame);
	    cv::Mat mat = cv::imread("1.jpg");
	    imshow("face",mat);
	    std::cout << "3333!" << std::endl;
	    cv::waitKey(3);
	    std::cout << "mat not empty" << std::endl;
	}
	else
	{
	    std::cout << "mat is empty" << std::endl;
	} */
   // frame.release();
    
    delete track_info;
}
// 通过图片检测，输出人脸信息(传入二进制图片buffer）
void Liveness::image_track_face_info_by_buf(BaiduFaceApi *api)
{
    std::string out_buf;
    int buf_len = ImageBuf::get_buf("2.jpg", out_buf);

    cv::RotatedRect box;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();

   // track_info->clear();
    int size = api->track_by_buf(track_info, (unsigned char*)out_buf.c_str(), buf_len, 1);
    if (size > 0)
    {
        for (int i = 0; i < size; i++)
        {
            TrackFaceInfo info = track_info->at(i);
            std::cout << "in Liveness::image_track_face_info score is:" << info.score << std::endl;
            // 人脸信息
            FaceInfo ibox = info.box;
            // 角度
            std::cout << "in Liveness::image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
            // 人脸宽度
            std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
            // 中心点X,Y坐标
            std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
            std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
            std::vector<float> head_pose = info.headPose;
            // 返回 x，y，z三个角度的人脸角度
            for (int k = 0; k < head_pose.size(); k++)
            {
                float angle = head_pose.at(k);
                std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
            }
           
        }
    }
    else
    {
        std::cout << "image has no face!" << std::endl;
    }
    cv::waitKey(1);
    delete track_info;
}

// 双目摄像头进行ir,rgb活体检测
bool Liveness::ir_rgb_track(BaiduFaceApi *api, float default_score)
{
 
    bool pass = true;
    // 序号0为电脑识别的usb摄像头编号，本demo中
    // 不同摄像头和电脑识别可能有区别
    // 编号一般从0-10
    int device =0;
    cv::VideoCapture camera1(device);
    if (!camera1.isOpened())
    {
        std::cout << "camera1 open error" << std::endl;
        return false;
    }
    // 序号1为电脑识别的usb摄像头编号，本demo中1为rgb可见光摄像头
    cv::VideoCapture camera2(device + 1);
    
    if (!camera2.isOpened())
    {
        std::cout << "camera2 open error" << std::endl;
        return false;
    }
    bool save_file = false;
    int is_frame1_rgb = 0;
    std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
    while (true) 
    {
        //grab and retrieve each frames of the video sequentially 
        cv::Mat frame1;
        cv::Mat frame2;
        camera1 >> frame1;
        camera2 >> frame2;

        // cv::Size size1 = frame1.size();
        if (!frame1.empty() && !frame2.empty())
        {
            if (!save_file)
            {
                save_file = true;
                is_frame1_rgb = is_rgb(frame1,frame2);
            }
            std::cout<<"is_frame1_rgb "<<is_frame1_rgb <<std::endl;
            cv::Mat rgb;
            cv::Mat ir;
            
            if (is_frame1_rgb)
            {
                rgb = frame1;
                ir = frame2;
                std::cout<<"frame1 = rgb"<<std::endl;
            }
            else
            {
                ir = frame1;
                rgb = frame2;
                std::cout<<"frame2 = rgb"<<std::endl;
            }
        
            float rgb_score = 0;
            float ir_score = 0;
            track_info->clear();
            std::string res = api->rgb_ir_liveness_check(track_info, rgb, ir, rgb_score, ir_score);
            
            std::cout << "res is:" << res << std::endl;

            std::string msg1 = "ir score is:" + std::to_string(ir_score);
            cv::putText(ir, msg1, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
                1, cv::Scalar(255, 100, 0), 2, 2);
            cv::imshow("ir", ir);


            // 画轮廓
            if (track_info->size()>0)
            {
		    TrackFaceInfo info = track_info->at(0);
		   // std::cout << "in Liveness::usb_track score is:" << info.score << std::endl;
		    // 人脸框信息
		    FaceInfo ibox = info.box;
		    // 角度
		  //  std::cout << "in Liveness::usb_track mAngle is:" << ibox.mAngle << std::endl;
		    // 人脸宽度
		  //  std::cout << "in Liveness::usb_track mWidth is:" << ibox.mWidth << std::endl;
		    // 中心点x，y坐标
		   // std::cout << "in Liveness::usb_track mCenter_x is:" << ibox.mCenter_x << std::endl;
		   // std::cout << "in Liveness::usb_track mCenter_y is:" << ibox.mCenter_y << std::endl;
		    std::vector<float> headPose = info.headPose;
		    // 返回x，y，z三个角度的人脸角度
		    for (int k = 0; k < headPose.size(); k++)
		    {
		        float angle = headPose.at(k);
		     //   std::cout << "in Liveness::usb_track angle is:" << angle << std::endl;
		    }
		    //画人脸框
		    cv::RotatedRect box = CvHelp::bounding_box(info.landmarks);
		    CvHelp::draw_rotated_box(rgb, box, cv::Scalar(0, 255, 0));
		    // 画关键点轮廓
		    CvHelp::draw_shape(info.landmarks, rgb, cv::Scalar(0, 255, 0));
            }
           
            std::string msg2 = "rgb score is:" + std::to_string(rgb_score);
            cv::putText(rgb, msg2, cv::Point(20, 50), CV_FONT_HERSHEY_COMPLEX,
                1, cv::Scalar(255, 100, 0), 2, 2);
            cv::imshow("rgb", rgb);
        }
            frame1.release();
            frame2.release();
            cvWaitKey(1);
    }
    delete track_info;
    return pass;
}

bool Liveness::ir_rgb_track_by_buf(BaiduFaceApi *api)
{
     std::string ir_buf;
     int ir_len = ImageBuf::get_buf("ir.jpg", ir_buf);
 
     std::string rgb_buf;
     int rgb_len = ImageBuf::get_buf("rgb.jpg", rgb_buf);

     std::vector<TrackFaceInfo> *track_info = new std::vector<TrackFaceInfo>();
     std::string res = api->rgb_ir_liveness_check_by_buf(track_info, (unsigned char*)rgb_buf.c_str(),
         rgb_len, (unsigned char*)ir_buf.c_str(), ir_len);
     std::cout<<"ir_rgb_check_by_buf res is:"<<res<<std::endl;
     delete track_info; 
     return true;
}

// 根据图片大小判断rgb视频帧和ir视频帧，有的摄像头该判断可能不准确，请自行写代码筛查
int Liveness::is_rgb(const cv::Mat& rgb, const cv::Mat& ir)
{
    std::string rgb_name = "rgb.jpg";
    std::string ir_name = "ir.jpg";
    cv::imwrite(rgb_name, rgb);
    cv::imwrite(ir_name, ir);
    int rgb_size = get_file_size(rgb_name);
    int ir_size = get_file_size(ir_name);
    
    return rgb_size > ir_size ? 1 : 0;
}

bool Liveness::get_file_size(const std::string& file_name)
{
    FILE * fp = fopen(file_name.c_str(), "r");
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
} 


void Liveness::draw_face_info(std::vector<TrackFaceInfo> *track_info)
{

    if (track_info==nullptr)
    {
       return;
    }
    int size = track_info->size();
    for (int i = 0; i < size; i++)
	{
	    TrackFaceInfo info = track_info->at(i);
	    std::cout << "in Liveness::image_track_face_info score is:" << info.score << std::endl;
	    // 人脸框信息
	    FaceInfo ibox = info.box;
	    // 角度draw_face_info:image_track_face_info mAngle is:" << ibox.mAngle << std::endl;
	    // 人脸宽度
	    std::cout << "in Liveness::image_track_face_info mWidth is:" << ibox.mWidth << std::endl;
	    // 中心点X，Y坐标
	    std::cout << "in Liveness::image_track_face_info mCenter_x is:" << ibox.mCenter_x << std::endl;
	    std::cout << "in Liveness::image_track_face_info mCenter_y is:" << ibox.mCenter_y << std::endl;
	    std::vector<float> headPose = info.headPose;
	    // 返回x y z三个角度的人脸角度
	    for (int k = 0; k < headPose.size(); k++)
	    {
                float angle = headPose.at(k);
		std::cout << "in Liveness::image_track_face_info angle is:" << angle << std::endl;
	    }
	    // 画人脸框
	   // box = CvHelp::bounding_box(info.landmarks);
	   // CvHelp::draw_rotated_box(frame, box, cv::Scalar(0, 255, 0));
	    // 画关键点轮廓
	    //CvHelp::draw_shape(info.landmarks, frame, cv::Scalar(0, 255, 0));
	}
}

