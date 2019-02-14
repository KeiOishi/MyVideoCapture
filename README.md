# MyVideoCapture

## 概要

Windowsでのみで使えるWebCamera用のツール．<br>
WebCameraの映像をOpenCVのcv::Matで扱える．<br>
また，WebCameraの使えるモード（解像度など，使うWebカメラにより異なる）
を選択することが出来る．

## 使い方

```c++:main.cpp
int main()
{
    WebCamera webcam(0);      //使うwebカメラの番号を入力
                              //プログラムを起動後モード選択をする
                         
    //WebCamera webcam(0, 0); //使うwebカメラの番号を入力
                              //二つ目の引数はモード選択                  

    while(1){
        cv::Mat frame;
        webcam.GetImage(&frame); //画像の読み込み
        if (frame.empty()){
            break;
        }
        cv::imshow("web camera", frame);
        int k = cv::waitKey(1);
        if (k == 'q') {
            break;
        }
    }
    return EXIT_SUCCESS;
}
```

## 実行例

```command
DirectShow VideoCapture  cameraID 0
------------------------
0 : 640 x 480, 30 fps RGB24
1 : 160 x 90, 15 fps RGB24
2 : 160 x 100, 15 fps RGB24
3 : 160 x 120, 15 fps RGB24
4 : 176 x 144, 15 fps RGB24
5 : 320 x 180, 15 fps RGB24
6 : 320 x 200, 15 fps RGB24
7 : 320 x 240, 15 fps RGB24
8 : 352 x 288, 15 fps RGB24
9 : 640 x 360, 15 fps RGB24
10 : 640 x 400, 15 fps RGB24
11 : 864 x 480, 15 fps RGB24
12 : 768 x 480, 15 fps RGB24
13 : 800 x 450, 15 fps RGB24
14 : 800 x 500, 15 fps RGB24
15 : 800 x 600, 15 fps RGB24
16 : 960 x 720, 15 fps RGB24
17 : 1280 x 720, 5 fps RGB24
18 : 1280 x 800, 5 fps RGB24
19 : 1280 x 1024, 5 fps RGB24
------------------------

Input format No. ->
```