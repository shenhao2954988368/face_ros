#include "test_face.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <regex>
#include <sstream>
#include <fstream>
#include <iterator>
#include <thread>
#include "opencv2/opencv.hpp"
#include "baidu_face_api.h"
#include "image_base64.h"
#include "cv_help.h"
#include "json/json.h"
#include "liveness.h"
#include "compare.h"
#include "setting.h"
#include <chrono>
#include "image_buf.h"
#include <sys/time.h>
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <time.h>
#include <fcntl.h>
using namespace cv;
using namespace std;

std::string match_person = "";
// ��ȡ����ʱ���
std::time_t get_timestamp()
{
    std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
    std::time_t timestamp = tmp.count(); 
    return timestamp;
}

int control = 0;
// ������������
void test_face_attr(BaiduFaceApi *api)
{
    // ��ȡ�������ԣ�ͨ������ͼƬbase64(1:base64ͼƬ��2ΪͼƬ·����
    std::string base64 = ImageBase64::file2base64("3.jpg");
    std::string res1 = api->face_attr(base64.c_str(), 1);
    std::cout<<"attr res1 is:"<<res1<<std::endl; 
   // ��ȡ�������ԣ�ͨ������ͼƬ·��(1:base64ͼƬ��2ΪͼƬ·����
    std::cout<<"before face_attr"<<std::endl;
    std::string res2 = api->face_attr("3.jpg",2);
    std::cout<<"attr res2 is:"<<res2<<std::endl;  
    std::string out_buf;
    // ��ȡ�ļ���������buffer
    int buf_len = ImageBuf::get_buf("3.jpg", out_buf);
    std::string res_buf = api->face_attr_by_buf((unsigned char*)out_buf.c_str(), buf_len);
    std::cout<<"res_buf is:"<<res_buf<<std::endl;
}

// ������������
void test_face_quality(BaiduFaceApi *api)
{
    // ��ȡ�������ԣ�ͨ������ͼƬbase64(1:base64ͼƬ��2ΪͼƬ·����
    // api->set_min_face_size(30);
    std::string base64 = ImageBase64::file2base64("1.jpg");
    std::string res1 = api->face_quality(base64.c_str(), 1);
    std::cout << "res1 is:"<< res1 << std::endl;
    // ��ȡ�������ԣ�ͨ������ͼƬ·��(1:base64ͼƬ��2ΪͼƬ·����
    std::string res2 = api->face_quality("1.jpg", 2);
    std::cout << "res2 is:"<< res2 << std::endl;
    // ��ȡ�������ԣ�ͨ������ͼƬ������buffer
    std::string out_buf;
    // ��ȡ�ļ���������buffer
    std::cout << "in test_face_quality" << std::endl;
    int buf_len = ImageBuf::get_buf("1.jpg", out_buf);
    std::cout << "in test_face_quality 1111" << std::endl;
    std::string res_buf = api->face_quality_by_buf((unsigned char*)out_buf.c_str(), buf_len); 
    std::cout << "res_buf is:" << res_buf << std::endl;
}

//���Ի�ȡ�豸ָ��device_id
void test_get_device_id(BaiduFaceApi *api)
{
    std::string res = api->get_device_id();
    std::cout << "---res is:" << res << std::endl;
}

// �Ƿ���Ȩ
void test_is_auth(BaiduFaceApi *api)
{
    bool authed = api->is_auth();
    if (authed)
    {
        std::cout << "authed is true" << std::endl;
    }
    else
    {
        std::cout << "authed is false" << std::endl;
    }
}

// ͨ���޸�setting����Ķ�Ӧ���������ﵽ�������������Ե�Ŀ��
void test_face_setting(BaiduFaceApi* api)
{
    Setting *setptr = new Setting();
    // setptr->set_blur_thr(api);
    // setptr->set_detect_in_video_interval(api);
    // setptr->set_eulur_angle_thr(api);
    // setptr->set_illum_thr(api);
    // setptr->set_is_check_quality(api);
    // ������С����
    setptr->set_min_face_size(api);
    //  setptr->set_notface_thr(api);
    //  setptr->set_occlu_thr(api);
    //  setptr->set_track_by_detection_interval(api);
    delete setptr;
}

// ���Աȶԣ�1:1�����ȶԣ�1��N�����ȶ�,����ֵ�ȶԵ�
void test_compare(BaiduFaceApi* api)
{
    Compare *comptr = new Compare();
    //1:1�Ա�
    
    //comptr->get_face_feature(api);
    
     //comptr->match(api);
   
    //ͼƬ����Ƶ�Ա�
   // comptr->match_by_img_and_frame(api, "1.jpg");
    //����Ϊ����ֵ����demo
    // comptr->get_face_feature_by_img(api);
   // comptr->get_face_feature_by_frame(api);
    // comptr->get_face_feature_by_buf(api);
     //����ֵ�Ƚ�

    comptr->compare_feature(api);

    //comptr->compare_feature_from_dataset(api);

    // ���Ի�ȡ����ֵ������ֵ�Ƚ�(�Ƚ��ۺϣ��ɸ��ݲ�����ͬ�Ƚ�)
    // comptr->get_face_feature_and_match(api);
    delete comptr;
}

// �ɼ������
void test_liveness_track(BaiduFaceApi* api)
{   
  
    Liveness* liveptr = new Liveness();
     // usb����ͷ���������ɼ�
    liveptr->initial_face_feature(api);
    
    while(1)
    {
	    liveptr->usb_track_face_info(api);
      	liveptr->match_face(api);
    }

    delete liveptr;
}

// opencv��rtsp������Ƶʾ������
void test_opencv_video()
{
    // rtsp��������ͷ��ַ
    cv::VideoCapture cap("rtsp://admin:Aa123456@192.168.1.65:554/h264/ch1/main/av_stream");
    if (!cap.isOpened())
    {
        std::cout << "open camera error" << std::endl;
        return;
    }
    cv::Mat frame;
    bool stop = false;
    int index = 0;
   
    while (!stop)
    {
        cap >> frame;
     /*   if (!frame.empty())
        {
            imshow("face", frame);
            cv::waitKey(1);
            std::cout << "mat not empty" << std::endl;
        }
        else
        {
            std::cout << "mat is empty" << std::endl;
        } */

        imshow("face", frame);
        cv::waitKey(1);
      //  frame.release();
    }
}

std::string max(std::vector<std::string> v)
{
	int n = 5;
	int i,j,count[2] = {1,1};
	string most;
	//��ʼ��Ϊ��һ����
	most = v[0];
	for (i = 0;i < n;i++)
	{
		for(j = i+1;j < n;j++)
		{
			if (v[i] == v[j])
			{
				count[0]++;
			}
		}
		if(count[0] > count[1])
		{
			count[1] = count[0];
			most = v[i];
		}
		count[0] = 1;
	}
	cout << most << endl;
	return most;
}
void write(string a, const char *m)
{
	//int a[10];
	//string a = " ��ȫojbk";
	ifstream in(m);
	ofstream out(m, ios::app);
	out << a;
    out << "\n";
	in.close();
	out.close();
	//cin.get();
}

std::string pic_save(std::string a1, std::string a2)
{
    time_t nowtime;
    nowtime = time(NULL);
    int x = nowtime;
    std::string ti = to_string(x);

    
    a2.append(ti).append("/");
    std::string command;
    command = "mkdir -p " + a2;
    int s = system(command.c_str());
    a2.append(ti).append(".jpg");
    const char* c_a1 = a1.c_str();
    const char* c_a2 = a2.c_str(); 
    //rename("/home/shen/test-face-api/dataset/data_read/1.jpg", "/home/shen/test-face-api/dataset/data_read/2.jpg");   
    rename(c_a1, c_a2);
    /* cout << a2 << endl;
    cout << x << endl;
    cout << ti << endl;
    cout << ctime(&nowtime) << endl; */
    std::cout << "99999999999999999999999999999999999999999999" << std::endl;
    return a2;
}
// ������ں���
int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_face");
    ros::NodeHandle nd;
    ros::NodeHandle nh;
    ros::Publisher pub = nd.advertise<std_msgs::String>("face_name",1);
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise("GUI/face_result", 1);
    ros::Rate loop_rate(1.0);
    std::cout << "in main" << std::endl;
    BaiduFaceApi *api = new BaiduFaceApi();
    std::vector<string> name_count, final_name_count;
    std::string x = "x";
    final_name_count.push_back(x);
    std::string name1, final_name, a1, a2;
    int count = 0;
    std::cout<<"in main init"<<std::endl;
    bool id_card = false;
    api->sdk_init(id_card);
    std::cout<<"in main after init"<<std::endl;
    std::time_t time_begin = get_timestamp();
    std::cout<<"time begin is:"<<time_begin<<std::endl;
    test_get_device_id(api);
    std::string res = "";
    //std::string pic1 = "/home/shen/1.jpg";
    //std::string pic2 = "/home/shen/fr_ws/src/test_face/dataset/face_data/";
    //test_liveness_track(api);
    Liveness* liveptr = new Liveness();
    liveptr->initial_face_feature(api);
    while(ros::ok())
    {
        std_msgs::String msg;
        liveptr->usb_track_face_info(api);
        match_person = liveptr->match_face(api);
        name_count.push_back(match_person);
        cv::Mat image = cv::imread("/home/shen/usb_track.jpg", CV_LOAD_IMAGE_COLOR);
        sensor_msgs::ImagePtr image_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        image_pub.publish(image_msg);
        //count++;
        while(name_count.size() == 5)
        {
            count = 0;
            name1 = max(name_count);
            for (int i = 0; i < 5; i++)
            {
                if (name_count[i] == name1) count++;
            }
            name_count.erase(name_count.begin());

            if (count >= 3) 
            {
                final_name = name1;
                
                final_name_count.push_back(final_name);
                while(final_name_count.size() == 2)
                {
                    //count = 0;
                    a1 = final_name_count[0];
                    a2 = final_name_count[1];
                    final_name_count.erase(final_name_count.begin());
                    if(a1 != a2)
                    {
                        std::string mo;
                        mo.append("陌生人");
                        std::cout << mo << std::endl;
                        std::cout << a2 << std::endl;

                        std::cout << "2222222222222222" << a2.compare(mo) << std::endl;
                        std::cout << a2 << std::endl;
                        msg.data = a2;
                        std::cout << "1111111111111111111111111111111111111111111111" << std::endl;
                        pub.publish(msg);
                        if(a2.compare(mo) == 0)
                        {
                            //cv::imwrite("/home/shen/fr_ws/src/test_face/dataset/face_data/1.jpg", img);
                            //path.append("/home/shen/fr_ws/src/test_face/dataset/face_data/1.jpg");
                            //std::string pic_path = pic_save(pic1, pic2);
                            //write(pic_path, "/home/shen/fr_ws/src/test_face/path.txt");
                            delete liveptr;
                            delete api;
                            return 0;
                        }
                    }
                }
            }  
        }
    }
    
    delete liveptr;
    delete api;
    return 0;
}

/* //topic callback function
void topicCallBack(const std_msgs::String::ConstPtr& msg)
{
    std::cout << "get topic text:" << msg->data.c_str();
    
    f_r();
    ros::spin();
} */


/* int main(int argc, char **argv)
{
    
    //string greet_word = "�����ϳ�ģ�������ɹ���"; //default need composed greet word
    //string face_topic = "/voice_tts/";  //default tts topic
    ros::init(argc, argv, "test_face");
    ros::NodeHandle nd;
    //topic_demo::gps msg;
    //ros::Subscriber sub = nd.subscribe("face/f_topic", 1, topicCallBack);
    ros::Publisher pub = nd.advertise<std_msgs::String>("face_name",1000);
    ros::Rate loop_rate(1.0);
    //playVoice();
     while(ros::ok())
    {
        f_r();
        std_msgs::String msg;
        msg.data = match_person;
        pub.publish(msg);
        //pub.publish(msg);
    }
    //std::cout<<"nishishui"<<std::endl;
    

    //ros::spin();

    return 0;
} */

TestFace::TestFace()
{
}

TestFace::~TestFace()
{
}
