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
        webcam.GetImage(&frame);
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