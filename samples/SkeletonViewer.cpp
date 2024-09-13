// SkeletonViewer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "../src/ApplicationCanvas.h"
#include <opencv2/opencv.hpp>
#include "../src/SkeletonDetection.h"

using namespace SkeletonViewerApplication;

int main()
{
    std::cout << "Hello World!\n";
    const int img_width = 1280;
    const int img_height = 720;
    const int pc_width = 960;
    const int camera_num = 5;
    const std::string dataset = "seq_3";
    SkeletonViewerApplication::ApplicationCanvas app(img_width + pc_width, img_height, "SkeletonViewer");
    std::vector<std::vector<SkeletonDetection>> SkelDete(camera_num);
#pragma omp parallel for 
    for (int i = 0; i < camera_num; ++i)
    {
        //SkelDete[i] = ParseDetections("./data/" + dataset + "/detection/" + );
    }

    while (app)
    {
        //app.show();
        //app.show();
        std::cout << " show " << std::endl;

        if (cv::waitKey(1) == 'q')
            break;
    }

    return 1;

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
