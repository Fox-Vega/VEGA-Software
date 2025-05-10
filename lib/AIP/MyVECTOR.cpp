#include <MyVECTOR.h>
#include <Input.h>

void MyVECTOR::get_cord(int azimuth, int magnitude) {
    theta = 90 - azimuth; //方位角をy軸基準の角度に変換(+-180度)

    //値を調整
    if (theta < -180) {
        theta += 360;
    } else if (theta > 180) {
        theta -= 360;
    }

    //座標を計算
    x = int(cos(radians(theta)) * magnitude);
    y = int(sin(radians(theta)) * magnitude);
}

void MyVECTOR::get_ppcord(int po_x, int po_y) {
    gyro.get_cord();
    int plpo_x = gyro.get_x();
    int plpo_y = gyro.get_y();

    //絶対値を取得
    plpo_x = int(abs(po_x - plpo_x));
    plpo_y = int(abs(po_y - plpo_y));

    //距離の正・負を適用
    if (po_x < plpo_x) {
        plpo_x = plpo_x - (plpo_x * 2);
    } else if (po_y < plpo_y) {
        plpo_y = plpo_y - (plpo_y * 2);
    }
}

void MyVECTOR::get_tarcord(int tar_azimuth, int tar_magnitude) {
    gyro.get_cord();
    int plpo_x = gyro.get_x();
    int plpo_y = gyro.get_y();

    myvector.get_cord(tar_azimuth, tar_magnitude);
    tarcord_x = myvector.get_x() + plpo_x;
    tarcord_y = myvector.get_y() + plpo_y;
}

void MyVECTOR::get_svec(int tar_azimuth, int tar_magnitude) {
    gyro.get_cord();
    myvector.get_tarcord(tar_azimuth, tar_magnitude);
    cord_x = gyro.get_x();
    cord_y = gyro.get_y();
    tarcord_x = myvector.get_tar_x();
    tarcord_y = myvector.get_tar_y();
    dt = millis() - lastupdatetime;

    //ズレを計算して秒間速度ベクトルに変換
    svec_x = ((cord_x - lastcord_x) / dt) * 1000;
    svec_y = ((cord_y - lastcord_y) / dt) * 1000;
    tarsvec_x = (((tarcord_x - lasttar_x) / dt) * 1000) - svec_x;
    tarsvec_y = (((tarcord_y - lasttar_y) / dt) * 1000) - svec_y;

    //ターゲットのベクトルから進行角(°)とマグニチュードを計算
    tarsvec_magnitude = myvector.get_magnitude(tarsvec_x, tarsvec_y);
    tarsvec_azimuth = myvector.get_azimuth(tarsvec_x, tarsvec_y);

    //最終値の更新
    lasttar_x = tarcord_x;
    lasttar_y = tarcord_y;
    lastcord_x = cord_x;
    lastcord_y = cord_y;
}

int MyVECTOR::get_azimuth(int x, int y) {
    theta = atan2(y, x); //座標をy軸基準の角度に変換(+-180度)
    azimuth = int(90 - degrees(theta)); //y軸基準の角度を方位角に変換

    //値を調整
    if (azimuth < 0) { 
        azimuth += 360;
    } else if (azimuth > 360) {
        azimuth -= 360;
    }

    return azimuth;
}

int MyVECTOR::get_magnitude(int x, int y) {
    return int(sqrt(x * x + y * y)); //マグニチュードを計算、送信
}

//値取得ゾーン

int MyVECTOR::get_x() {
    return x;
}

int MyVECTOR::get_y() {
    return y;
}

int MyVECTOR::get_plpo_x() {
    return plpo_x;
}

int MyVECTOR::get_plpo_y() {
    return plpo_y;
}

int MyVECTOR::get_tar_x() {
    return tarcord_x;
}

int MyVECTOR::get_tar_y() {
    return tarcord_y;
}

int MyVECTOR::get_tarsvec_x() {
    return tarsvec_x;
}

int MyVECTOR::get_tarsvec_y() {
    return tarsvec_x;
}

int MyVECTOR::get_tarsvecazimuth() {
    return tarsvec_azimuth;
}

int MyVECTOR::get_tarsvecmagnitude() {
    return tarsvec_magnitude;
}