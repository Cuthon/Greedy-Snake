#include "drawer.h"
#include "wall.h"

using std::string;

drawer* drawer::_instance = 0;

drawer* drawer::GetInstance(){
    if (_instance == 0){
        _instance = new drawer;
    }
    return _instance;
}

drawer::drawer(){
    // loadImgs();
}

void drawer::loadImgs(){
    // string imgPath = "../images/";
    IMAGE ptemp;

    loadimage(&ptemp, _T("../images/Item_apple.png"), SCALE, SCALE);
    imgMap["Item_apple"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/Item_chiken.png"), SCALE, SCALE);
    imgMap["Item_chiken"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/Item_gapp.png"), SCALE, SCALE);
    imgMap["Item_gapp"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/Item_purple.png"), SCALE, SCALE);
    imgMap["Item_purple"] = IMAGE(ptemp);

    loadimage(&ptemp, _T("../images/head_down.png"), SCALE, SCALE);
    imgMap["head_down"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/head_left.png"), SCALE, SCALE);
    imgMap["head_left"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/head_up.png"), SCALE, SCALE);
    imgMap["head_up"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/head_right.png"), SCALE, SCALE);
    imgMap["head_right"] = IMAGE(ptemp);

    loadimage(&ptemp, _T("../images/tail_d.png"), SCALE, SCALE);
    imgMap["tail_d"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/tail_l.png"), SCALE, SCALE);
    imgMap["tail_l"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/tail_r.png"), SCALE, SCALE);
    imgMap["tail_r"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/tail_u.png"), SCALE, SCALE);
    imgMap["tail_u"] = IMAGE(ptemp);

    loadimage(&ptemp, _T("../images/turn_ld.png"), SCALE, SCALE);
    imgMap["turn_ld"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/turn_lu.png"), SCALE, SCALE);
    imgMap["turn_lu"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/turn_rd.png"), SCALE, SCALE);
    imgMap["turn_rd"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/turn_ru.png"), SCALE, SCALE);
    imgMap["turn_ru"] = IMAGE(ptemp);

    loadimage(&ptemp, _T("../images/body_horizen.png"), SCALE, SCALE);
    imgMap["body_horizen"] = IMAGE(ptemp);
    loadimage(&ptemp, _T("../images/body_vert.png"), SCALE, SCALE);
    imgMap["body_vert"] = IMAGE(ptemp);
}

void transparentimage(int x, int y, IMAGE& img)
{
    IMAGE img1;
    DWORD *d1;
    img1 = img;
    d1 = GetImageBuffer(&img1);
    float h, s, l;
    for (int i = 0; i < img1.getheight() * img1.getwidth(); i++)
    {
        RGBtoHSL(BGR(d1[i]), &h, &s, &l);
        if (l < 0.03)
        {
            d1[i] = BGR(WHITE);
        }
        if (d1[i] != BGR(WHITE))
        {
            d1[i] = 0;
        }
    }
    putimage(x, y, &img1, SRCAND);
    putimage(x, y, &img, SRCPAINT);
}