#include"stdafx.h"
#include"head.h"
int main(void)
{
	int flag;//  0--成功 1--失败
	int choice;//开始界面几个选项
	FILE *fp = NULL;
	setinitmode(INIT_RENDERMANUAL, 400, 150);
	initgraph(820, 550);
	muswel.OpenFile("welcome.mp3");
	muswel.Play(0);
	muswel.SetVolume(0.5f);
	setcaption("魔塔");
	admin_initial();
	ID_identify(fp);
	closegraph();
	setinitmode(INIT_RENDERMANUAL, 400, 150);
	//初始化种子
	randomize();
	setfont(15, 0, "黑体");
	initgraph(820, 550);
	setcaption("魔塔");
	mus.OpenFile("bgm.mp3"); // 打开文件
	mus.SetVolume(0.3f);
	musdoor.OpenFile("door.mp3"); // 打开文件
	musget.OpenFile("get.mp3");
	mushit.OpenFile("hit.mp3");
	musdoor.SetVolume(0.6f);
	musget.SetVolume(0.6f);
	mushit.SetVolume(0.6f);
allbegin: //begin
	choice = startgamepage(0);
	if (choice == 3)return 0;
	if (choice == 2) {
		setbkcolor(EGERGB(0, 0, 0));
		cleardevice();
		setfontbkcolor(EGERGB(0, 0, 0));
		PIMAGE img1 = newimage();
		xyprintf(20, 10, "你是王国的一名勇士，排行第9527位");
		xyprintf(20, 60, "一天，公主被魔王抓进了魔塔");
		xyprintf(20, 100, ".....");
		xyprintf(20, 140, "目标：探遍0到6层，收集装备法宝,击败魔王，救出公主");
		xyprintf(20, 190, "进入游戏后点击左侧帮助，查看玩法");
		xyprintf(200, 500, "按任意键返回开始界面");
		getch();
		goto allbegin;
	}
	if (choice == 1) {
	begin2:
		ifload = 0;
		choice = startgamepage(1);
		if (choice == 1);
		else if (choice == 2) {
			cleardevice(); delay_fps(500);
			ifload = 1;
		}
		else if (choice == 3)goto allbegin;
	}
	setfont(15, 0, "黑体");
	monbegin();
	begingame();
	if (ifload) {
		int i;
		readgame();
		print_equip(pe.equip[0]);
		print_equip(pe.equip[1]);
		for (i = 0; i <= 9; i++) {
			if (pe.tr[i])print_tr(i, 1);
		}
	}
	readmap(site);
	printnum();
	PIMAGE imgwall = newimage();
	PIMAGE imgroad = newimage();
	getimage(imgwall, "wall.jpg", 40, 40);
	getimage(imgroad, "road.jpg", 40, 40);
	printmap(imgroad, imgwall);
	delay_fps(1000);
	flag = play(imgwall, imgroad); //0-bad结局 1-好结局 2-返回
	if (flag == 2)goto begin2;
	delay_fps(3);
	endgame(flag);
	// 关闭文件
	musdoor.Close();
	musget.Close();
	mushit.Close();
	delimage(imgroad);
	delimage(imgwall);
	//关闭图形界面
	closegraph();
	return 0;
}
int startgamepage(int kind) {
	int x, y;
	PIMAGE imgbegin = newimage();
	setfont(30, 0, "黑体");
	getimage(imgbegin, "begin.png");
	putimage(0, 0, 820, 550, imgbegin, 0, 0, getwidth(imgbegin), getheight(imgbegin));
	setfillcolor(EGERGB(100, 100, 100));
	setfontbkcolor(EGERGB(100, 100, 100));
	setcolor(EGERGB(255, 255, 255));
	printhelp(1 + 3 * kind);
	printhelp(2 + 3 * kind);
	printhelp(3 + 3 * kind);
	delay_fps(100);
	while (1) {
		setfillcolor(EGERGB(100, 100, 100));
		setfontbkcolor(EGERGB(100, 100, 100));
		delay_fps(1000);
		mousepos(&x, &y);
		if (x<500 && x>300 && y<320 && y>280) {
			setfillcolor(EGERGB(190, 230, 0));
			setfontbkcolor(EGERGB(190, 230, 0));
			printhelp(1 + 3 * kind); delay_fps(1000);
			if (mousemsg()) {
				while (mousemsg())msg = getmouse();
				if ((int)msg.is_down() == 1) {
					return 1;
				}
			}
			continue;
		}
		else printhelp(1 + 3 * kind);
		if (x<500 && x>300 && y<395 && y>355) {
			setfillcolor(EGERGB(190, 230, 0));
			setfontbkcolor(EGERGB(190, 230, 0));
			printhelp(2 + 3 * kind); delay_fps(1000);
			if (mousemsg()) {
				while (mousemsg())msg = getmouse();
				if ((int)msg.is_down() == 1) {
					return 2;
				}
			}
			continue;
		}
		else printhelp(2 + 3 * kind);
		if (x<500 && x>300 && y<480 && y>440) {
			setfillcolor(EGERGB(190, 230, 0));
			setfontbkcolor(EGERGB(190, 230, 0));
			printhelp(3 + 3 * kind); delay_fps(1000);
			if (mousemsg()) {
				while (mousemsg())msg = getmouse();
				if ((int)msg.is_down() == 1) {
					return 3;
				}
			}
			continue;
		}
		else printhelp(3 + 3 * kind);
	}
	delimage(imgbegin);
	return 0;
}
void printhelp(int choice) {
	if (choice == 1) {
		bar(300, 280, 500, 320);
		xyprintf(320, 284, "开始游戏");
	}
	if (choice == 2) {
		bar(300, 355, 500, 395);
		xyprintf(320, 360, "游戏简介");
	}
	if (choice == 3) {
		bar(300, 440, 500, 480);
		xyprintf(320, 444, "退出游戏");
	}
	if (choice == 4) {
		bar(300, 280, 500, 320);
		xyprintf(320, 284, "新的开始");
	}
	if (choice == 5) {
		bar(300, 355, 500, 395);
		xyprintf(320, 360, "载入存档");
	}
	if (choice == 6) {
		bar(300, 440, 500, 480);
		xyprintf(320, 444, "返回");
	}
}
void begingame() {
	int i;
	PIMAGE imgleft = newimage();
	getimage(imgleft, "left.png");
	PIMAGE imgright = newimage();
	getimage(imgright, "right.png");
	putimage(0, 0, 150, 520, imgleft, 0, 0, getwidth(imgleft), getheight(imgleft));
	putimage(670, 0, 150, 520, imgright, 0, 0, getwidth(imgright), getheight(imgright));
	delimage(imgright);
	delimage(imgleft);
	setfillcolor(EGERGB(102, 102, 102));
	bar(680, 460, 800, 512);
	bar(13, 460, 133, 512);
	setfillcolor(EGERGB(0, 255, 0));
	setcolor(EGERGB(0, 0, 0));
	bar(730, 461, 750, 481);
	bar(730, 486, 750, 506);
	bar(63, 461, 83, 481);
	bar(63, 486, 83, 506);
	setcolor(EGERGB(233, 233, 233));
	line(680, 460, 800, 460);
	line(13, 460, 133, 460);
	setcolor(EGERGB(0, 0, 0));
	setfontbkcolor(EGERGB(1, 255, 0));
	xyprintf(732, 463, "开");
	xyprintf(732, 488, "关");
	xyprintf(67, 463, "?");
	xyprintf(65, 488, "←");
	setfontbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(255, 255, 255));
	xyprintf(680, 462, "声音：");
	xyprintf(680, 489, "秒杀：");
	xyprintf(13, 462, "帮助：");
	xyprintf(13, 489, "返回：");
	//数值初始化
	pe.atk = 11;
	pe.blood = 800;
	pe.def = 11;
	pe.x = 10;
	pe.y = 5;
	pe.dir = 1;
	pe.money = 0;
	pe.ykeynum = pe.bkeynum = pe.rkeynum = 0;
	pe.double_atk = 10;
	pe.miss = 8;
	pe.equip[0] = pe.equip[1] = 0;
	for (i = 0; i<10; i++)pe.tr[i] = 0;
	for (i = 0; i <= 50; i++) {
		ifpass[i] = 0;
	}
	win = 0;
	sec_kill = 1;
	site = 1;
}
void monbegin(void) {
	mon[1].blood = 35;
	mon[2].blood = 45;
	mon[3].blood = 35;
	mon[4].blood = 60;
	mon[5].blood = 52;
	mon[6].blood = 55;
	mon[7].blood = 50;
	mon[8].blood = 110;
	mon[9].blood = 400;
	mon[10].blood = 200;
	mon[30].blood = 2500;
	mon[1].atk = 18;
	mon[2].atk = 21;
	mon[3].atk = 38;
	mon[4].atk = 32;
	mon[5].atk = 47;
	mon[6].atk = 55;
	mon[7].atk = 46;
	mon[8].atk = 66;
	mon[9].atk = 199;
	mon[10].atk = 300;
	mon[30].atk = 212;
	mon[1].def = 1;
	mon[2].def = 2;
	mon[3].def = 3;
	mon[4].def = 9;
	mon[5].def = 6;
	mon[6].def = 12;
	mon[7].def = 22;
	mon[8].def = 15;
	mon[9].def = 65;
	mon[10].def = 80;
	mon[30].def = 102;
	mon[1].money = 1;
	mon[2].money = 2;
	mon[3].money = 3;
	mon[4].money = 5;
	mon[5].money = 6;
	mon[6].money = 8;
	mon[7].money = 12;
	mon[8].money = 32;
	mon[9].money = 145;
	mon[10].money = 90;
	mon[30].money = 300;
	mon[1].double_atk = 4;
	mon[2].double_atk = 5;
	mon[3].double_atk = 6;
	mon[4].double_atk = 7;
	mon[5].double_atk = 5;
	mon[6].double_atk = 5;
	mon[7].double_atk = 11;
	mon[8].double_atk = 23;
	mon[9].double_atk = 10;
	mon[10].double_atk = 40;
	mon[30].double_atk = 50;
	mon[1].miss = 4;
	mon[2].miss = 5;
	mon[3].miss = 6;
	mon[4].miss = 7;
	mon[5].miss = 5;
	mon[6].miss = 5;
	mon[7].miss = 11;
	mon[8].miss = 13;
	mon[9].miss = 30;
	mon[10].miss = 16;
	mon[30].miss = 20;
	strcpy(mon[1].name, "绿色史莱姆");
	strcpy(mon[2].name, "红色史莱姆");
	strcpy(mon[3].name, "小蝙蝠");
	strcpy(mon[4].name, "初级法师");
	strcpy(mon[5].name, "骷髅人");
	strcpy(mon[6].name, "骷髅士兵");
	strcpy(mon[7].name, "初级卫兵");
	strcpy(mon[8].name, "骷髅队长");
	strcpy(mon[9].name, "吸血鬼");
	strcpy(mon[10].name, "黑巫师");
	strcpy(mon[30].name, "魔王");
}
void endgame(int choice) {
	int i = 1;
	int flag = 1;
	cleardevice();
	mus.Close();
	MUSIC musend;
	PIMAGE imgend = newimage();
	PIMAGE imgwoman = newimage();
	PIMAGE img0 = newimage();
	setfillcolor(EGERGB(255, 255, 255));
	PIMAGE imgblank = newimage();
	bar(0, 0, 820, 550);
	getimage(imgblank, 0, 0, 820, 550);
	if (choice == 0) {
		if (music_flag)musend.OpenFile("endbad.mp3");
		getimage(imgend, "end1.png");
		musend.Play(0);
		putimage(0, 0, 820, 550, imgend, 0, 0, getwidth(imgend), getheight(imgend));
		delay_fps(1000);
		delay(15000);
	}
	if (choice == 1) {
		PIMAGE imgman1 = newimage();
		PIMAGE imgman2 = newimage();
		PIMAGE imgman3 = newimage();
		PIMAGE imgman4 = newimage();
		if (music_flag)musend.OpenFile("endgood.mp3");
		getimage(imgend, "end2.png");
		getimage(img0, "manmove.png");
		getimage(imgman1, img0, 0, 66, 32, 33);
		getimage(imgman2, img0, 33, 66, 32, 33);
		getimage(imgman3, img0, 66, 66, 32, 33);
		getimage(imgman4, img0, 99, 66, 32, 33);
		getimage(imgwoman, "woman.png");
		musend.Play(0);
		while (1) {
			putimage(0, 0, 820, 550, imgend, 0, 0, getwidth(imgend), getheight(imgend));
			if ((i % 4) == 0)putimage_withalpha(NULL, imgman1, 100 + i * 3, 290);
			if ((i % 4) == 1)putimage_withalpha(NULL, imgman2, 100 + i * 3, 290);
			if ((i % 4) == 2)putimage_withalpha(NULL, imgman3, 100 + i * 3, 290);
			if ((i % 4) == 3)putimage_withalpha(NULL, imgman4, 100 + i * 3, 290);
			putimage_withalpha(NULL, imgwoman, 700, 290);
			i += flag;
			if (i == 186) {
				break;
			}
			delay_fps(4);
		}
	}
	getimage(imgend, 0, 0, 820, 550);
	while (flag < 67) {
		flag += 2;
		putimage_alphablend(imgend, imgblank, 0, 0, flag);
		putimage(0, 0, imgend);
		delay_fps(19);
	}
	musend.Close();
}
void readmap(int mapnum) {
	FILE *fp;
	int i, j;
	if (ifpass[mapnum] == 0 || (ifpass[mapnum] == 2 && mapnum == 0)) {
		if (mapnum == 1)fp = fopen("map1.txt", "r");
		else if (mapnum == 2)fp = fopen("map2.txt", "r");
		else if (mapnum == 3)fp = fopen("map3.txt", "r");
		else if (mapnum == 4)fp = fopen("map4.txt", "r");
		else if (mapnum == 5)fp = fopen("map5.txt", "r");
		else if (mapnum == 6)fp = fopen("map6.txt", "r");
		else fp = fopen("map0.txt", "r");
	}
	else {
		if (mapnum == 1)fp = fopen("newmap1.txt", "r");
		else if (mapnum == 2)fp = fopen("newmap2.txt", "r");
		else if (mapnum == 3)fp = fopen("newmap3.txt", "r");
		else if (mapnum == 4)fp = fopen("newmap4.txt", "r");
		else if (mapnum == 5)fp = fopen("newmap5.txt", "r");
		else if (mapnum == 6)fp = fopen("newmap6.txt", "r");
		else fp = fopen("newmap0.txt", "r");
	}
	for (i = 0; i<11; i++) {
		for (j = 0; j<11; j++) {
			fscanf(fp, "%d", &mapt[i][j]);
		}
	}
	fclose(fp);
	if (win&&site == 0)mapt[9][5] = 0;
}
void savemap(void) {
	FILE *fp;
	int i, j;
	ifpass[site] = 1;
	if (site == 1)fp = fopen("newmap1.txt", "w");
	else if (site == 2)fp = fopen("newmap2.txt", "w");
	else if (site == 3)fp = fopen("newmap3.txt", "w");
	else if (site == 4)fp = fopen("newmap4.txt", "w");
	else if (site == 5)fp = fopen("newmap5.txt", "w");
	else if (site == 6)fp = fopen("newmap6.txt", "w");
	else fp = fopen("newmap0.txt", "w");
	for (i = 0; i<11; i++) {
		for (j = 0; j<11; j++) {
			fprintf(fp, "%d ", mapt[i][j]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
void swapmap(FILE *fp1, FILE *fp2) {
	int i, j;
	for (i = 0; i<11; i++) {
		for (j = 0; j<11; j++) {
			fscanf(fp1, "%d", &mapt[i][j]);
		}
	}
	for (i = 0; i<11; i++) {
		for (j = 0; j<11; j++) {
			fprintf(fp2, "%d ", mapt[i][j]);
		}
		fprintf(fp2, "\n");
	}
}
void printone(int choice, int x, int y, PIMAGE imgroad, PIMAGE imgwall, int flag) {
	PIMAGE imgone = newimage();
	PIMAGE img0 = newimage();
	switch (choice) {
	case 51://神圣剑
		getimage(imgone, "sword1.png", 40, 40); break;
	case 52://神圣盾
		getimage(imgone, "shield1.png", 40, 40); break;
	case fire:
		getimage(img0, "fire.png", 160, 160);
		getimage(imgone, img0, 0, 0, 33, 33); break;
	case yellowdoor:
		getimage(imgone, "yellowdoor.jpg", 40, 40); break;
	case bluedoor:
		getimage(imgone, "bluedoor.jpg", 40, 40); break;
	case reddoor:
		getimage(imgone, "reddoor.jpg", 40, 40); break;
	case medoor:
		getimage(imgone, "medoor.jpg", 40, 40); break;
	case bossdoor:
		getimage(img0, "bossdoor.png", 160, 160);
		getimage(imgone, img0, 33, 0, 35, 35); break;
	case uproad:
		getimage(imgone, "up.png", 40, 40); break;
	case downroad:
		getimage(imgone, "down.png", 40, 40); break;
	case yellowkey:
		getimage(imgone, "ykey.png", 40, 40); break;
	case bluekey:
		getimage(imgone, "bkey.png", 40, 40); break;
	case redkey:
		getimage(imgone, "rkey.png", 40, 40); break;
	case redstone:
		getimage(img0, "stone.png", 160, 160);
		getimage(imgone, img0, 0, 0, 35, 35); break;
	case bluestone:
		getimage(img0, "stone.png", 160, 160);
		getimage(imgone, img0, 33, 0, 35, 35); break;
	case bloodbottle:
		getimage(imgone, "blood.png", 40, 40); break;
	case 20:
		getimage(imgone, "ud.png", 40, 40); break;
	case -1:
		getimage(imgone, "-1.png", 40, 40); break;
	case -2:
		getimage(imgone, "-2.png", 40, 40); break;
	case -3:
		getimage(imgone, "-3.png", 40, 40); break;
	case -4:
		getimage(imgone, "-4.png", 40, 40); break;
	case -5:
		getimage(imgone, "-5.png", 40, 40); break;
	case -6:
		getimage(imgone, "-6.png", 40, 40); break;
	case -7:
		getimage(imgone, "-7.png", 40, 40); break;
	case -8:
		getimage(imgone, "-8.png", 40, 40); break;
	case -9:
		getimage(imgone, "-9.png", 40, 40); break;
	case -10:
		getimage(imgone, "-10.png", 40, 40); break;
	case -30:
		getimage(imgone, "-30.png", 40, 40); break;
	case man:
		getimage(imgone, "man.png", 40, 40); break;
	case woman:
		getimage(imgone, "woman.png", 40, 40); break;
	case npc:
		getimage(imgone, "npc.png", 40, 40); break;
	case oldman:case oldman_end:
		getimage(imgone, "old.png", 40, 40); break;
	case shopman:case shopman1:case shopman1_end:
	case shopman2:case shopman2_end:case shopman_end:
		getimage(imgone, "shop.png", 40, 40); break;
	case myfriend:case myfriend_end:
		getimage(imgone, "friend.png", 40, 40); break;
	}
	getimage(img0, "road.jpg");
	if (choice == wall)putimage(x, y, 40, 40, imgwall, 0, 0, getwidth(imgwall), getheight(imgwall));
	else if (choice == uproad || choice == downroad || choice == fire) {
		putimage(x, y, 40, 41, imgone, 0, 0, getwidth(imgone), getheight(imgone));
	}
	else {
		if (flag)getimage(img0, "blank.png", 40, 40);
		putimage_transparent(img0, imgone, 0, 0, 0x000000, 0, 0, 40, 40);//图像重合
		putimage(x, y, 40, 40, img0, 0, 0, getwidth(img0), getheight(img0));
	}
	delimage(imgone);
	delimage(img0);
}
void printmap(PIMAGE imgroad, PIMAGE imgwall) {
	int i, j;
	int x, y;
	for (i = 0; i <= 12; i++) {
		putimage(i * 40 + 150, 0, 40, 40, imgwall, 0, 0, getwidth(imgwall), getheight(imgwall));
		putimage(150, i * 40, 40, 40, imgwall, 0, 0, getwidth(imgwall), getheight(imgwall));
		putimage(i * 40 + 150, 480, 40, 40, imgwall, 0, 0, getwidth(imgwall), getheight(imgwall));
		putimage(630, i * 40, 40, 40, imgwall, 0, 0, getwidth(imgwall), getheight(imgwall));
	}
	for (i = 0; i<11; i++) {
		for (j = 0; j<11; j++) {
			x = 190 + j * 40; y = i * 40 + 40;
			putimage(x, y, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
			if (mapt[i][j])printone(mapt[i][j], x, y, imgroad, imgwall, 0);
		}
	}
	setcolor(EGERGB(255, 255, 255));
	setfontbkcolor(EGERGB(102, 102, 102));
	xyprintf(42, 62, "魔塔第%d层  ", site);
	xyprintf(30, 252, "暴击率：%d%% ", pe.double_atk);
	xyprintf(30, 272, "闪避率：%d%% ", pe.miss);
	msg = { 0 };
	delay_fps(1000);
}
void print_equip(int choice) {
	PIMAGE img0 = newimage();
	PIMAGE img1 = newimage();
	int flag = 0;//  看是武器还是防具
	setfontbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(255, 255, 255));
	getimage(img0, "blank.png", 40, 40);
	if (choice == 53) {
		cleanmon(1);
		pe.equip[0] = 53;
		getimage(img1, "knife.png", 40, 40);
		xyprintf(685, 87, "屠龙宝刀"); flag = 1;
	}
	if (choice == 54) {
		cleanmon(2);
		pe.equip[1] = 54;
		getimage(img1, "shoe.png", 40, 40);
		xyprintf(685, 150, "轻羽靴  "); flag = 2;
	}
	if (choice == 51) {
		cleanmon(1);
		pe.equip[0] = 51;
		getimage(img1, "sword1.png", 40, 40);
		xyprintf(685, 87, "神圣剑  "); flag = 1;
	}
	if (choice == 52) {
		cleanmon(2);
		pe.equip[1] = 52;
		getimage(img1, "shield1.png", 40, 40);
		xyprintf(685, 150, "神圣盾  "); flag = 2;
	}
	if (choice == 55) {
		cleanmon(2);
		pe.equip[1] = 55;
		getimage(img1, "shield2.png", 40, 40);
		xyprintf(685, 150, "铁盾    "); flag = 2;
	}
	putimage_transparent(img0, img1, 0, 0, 0x000000, 0, 0, 40, 40);
	if (flag == 1)putimage(770, 65, img0);
	if (flag == 2)putimage(770, 130, img0);
	delimage(img0);
	delimage(img1);
}
void printnum(void) {
	setbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(240, 240, 240));
	xyprintf(50, 106, "%d", pe.blood);
	xyprintf(50, 136, "%d   ", pe.atk);
	xyprintf(50, 167, "%d", pe.def);
	xyprintf(50, 198, "%d", pe.money);
	setcolor(EGERGB(240, 240, 20));
	xyprintf(686, 186, "黄钥匙：%d", pe.ykeynum);
	setcolor(EGERGB(20, 20, 240));
	xyprintf(686, 216, "蓝钥匙：%d", pe.bkeynum);
	setcolor(EGERGB(240, 20, 20));
	xyprintf(686, 246, "红钥匙：%d", pe.rkeynum);
}
//1-宝典，2-钻地符，3-升降机，4-镐子 5-神圣盾
void print_tr(int choice, int flag) {
	PIMAGE imgone = newimage();
	PIMAGE imgclean = newimage();
	if (flag == 0)getimage(imgclean, "blank.png", 35, 35);
	switch (choice) {
	case 1:
		if (flag) {
			getimage(imgone, "book.png");
			putimage_withalpha(NULL, imgone, 20, 300);
		}
		else {
			putimage(20, 300, imgclean);
		}
		break;
	case 2:
		if (flag) {
			getimage(imgone, "trdown.png");
			putimage_withalpha(NULL, imgone, 60, 300);
		}
		else {
			putimage(60, 300, imgclean);
		}
		break;
	case 3:
		if (flag) {
			getimage(imgone, "ud.png");
			putimage_withalpha(NULL, imgone, 100, 300);
		}
		else {
			putimage(100, 300, imgclean);
		}
		break;
	case 4:
		if (flag) {
			getimage(imgone, "gao.png");
			putimage_withalpha(NULL, imgone, 20, 340);
		}
		else putimage(20, 340, imgclean);
	}
	delimage(imgone);
	delimage(imgclean);
}
void print_mon(int kind, int order, PIMAGE imgroad, PIMAGE imgwall) {
	int i; i = kind;
	printone(-kind, 200, order * 60 + 40, imgroad, imgwall, 1);
	setcolor(EGERGB(255, 255, 8));
	xyprintf(250, order * 60 + 40, "%s  血量:%d ", mon[i].name, mon[i].blood);
	setcolor(EGERGB(255, 255, 233));
	xyprintf(250, order * 60 + 60, "攻击:%d  防御:%d 金钱:%d  暴击率:%d%% 闪避率:%d%%", mon[i].atk, mon[i].def, mon[i].money, mon[i].double_atk, mon[i].miss);
	setcolor(EGERGB(0, 0, 0));
}
int play(PIMAGE imgwall, PIMAGE imgroad) { //根据鼠标键盘操作，作出不同反应
	char c;
	int i, j;
	int x, y;
	PIMAGE img0 = newimage(); 
	PIMAGE imgnman = newimage(); 
	PIMAGE img1 = newimage();
	int newx, newy;
	int choice;
	getimage(img0, "manmove.png", 40, 40);
	getimage(imgnman, "road.jpg", 40, 40);
	clean();
	while (1) {
		newx = pe.x; newy = pe.y;
		muswel.SetVolume(0.0f);
		if (music_flag)mus.SetVolume(0.35f);
		else mus.SetVolume(0.0f);
		if (mus.GetPlayStatus() == MUSIC_MODE_STOP && music_flag) { // 发现停止了就重新播放
																	// Play函数：参数1表示开始播放的地方，参数2是结束的地方
																	// 如果两个参数都不写，就当前位置开始播，只填第一个表示播放到结束为止
			mus.Play(0);
		}
	 get_c: 
	 if (kbhit()) {
		while (kbhit())c = getch();
		if (c>47 && c<55 && pe.tr[3] == 0)continue;
		if (c == 106 && pe.tr[4] == 0)continue;
		if (c == 104 && pe.tr[1] == 0)continue;
		if (c == 102 && pe.tr[2] == 0)continue;
	  difc:           //就是根据不同c不同选择
		switch (c) {
		case  27: exit(0);
		case 'o':   return 1;
		case 'p':   return 0;
		case 'c': {
			clean();
			setfontbkcolor(EGERGB(255, 255, 255));
			setcolor(EGERGB(0, 0, 0));
			savegame();
			readmap(site);
			xyprintf(0, 520, "保存成功");
			goto get_c;
		}
				  //pgup上
		case 33: {
			if (pe.tr[3] == 0)goto get_c;
			c = site + 1 + 48;
			goto difc;
		}
				 //pgdown下
		case 34: {
			if (pe.tr[3] == 0)goto get_c;
			c = site - 1 + 48;
			goto difc;
		}
		case 37:case 'a': {
			pe.dir = 2;
			newy = pe.y - 1; break;
		}
		case 38:case 'w': {
			pe.dir = 4;
			newx = pe.x - 1; break;
		}
		case 39:case 'd': {
			pe.dir = 3;
			newy = pe.y + 1; break;
		}
		case 40:case 's': {
			pe.dir = 1;
			newx = pe.x + 1; break;
		}
		case 48: {
			if (ifpass[0] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 0;
			readmap(0);
			mapt[0][1] = 100;
			pe.x = newx = 0; pe.y = newy = 1;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 49: {
			if (ifpass[1] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 1;
			readmap(1);
			mapt[0][1] = 100;
			pe.x = newx = 0; pe.y = newy = 1;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 50: {
			if (ifpass[2] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 2;
			readmap(2);
			mapt[1][0] = 100;
			pe.x = newx = 1; pe.y = newy = 0;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 51: {
			if (ifpass[3] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 3;
			readmap(3);
			mapt[10][1] = 100;
			pe.x = newx = 10; pe.y = newy = 1;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 32: {
			x = 73; y = 471;
			goto helppage;
		}
		case 52: {
			if (ifpass[4] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 4;
			readmap(4);
			mapt[10][1] = 100;
			pe.x = newx = 10; pe.y = newy = 1;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 53: {
			if (ifpass[5] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 5;
			readmap(5);
			mapt[1][0] = 100;
			pe.x = newx = 1; pe.y = newy = 0;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 54: {
			if (ifpass[6] == 0)goto get_c;
			mapt[pe.x][pe.y] = 0;
			savemap();
			site = 6;
			readmap(6);
			mapt[5][1] = 100;
			pe.x = newx = 5; pe.y = newy = 1;
			printmap(imgroad, imgwall); goto get_c;
		}break;
		case 106: {
			pe.tr[4] = 0;
			print_tr(4, 0);
			mapt[pe.x][pe.y] = man;
			if (pe.x - 1>0)mapt[pe.x - 1][pe.y] = 0;
			if (pe.y - 1>0)mapt[pe.x][pe.y - 1] = 0;
			if (pe.x + 1<11)mapt[pe.x + 1][pe.y] = 0;
			if (pe.y + 1<11)mapt[pe.x][pe.y + 1] = 0;
			printmap(imgroad, imgwall); goto get_c;
		}
		case 104: {                 //打印怪物信息
			int k[100];//存放打印过的怪物
			int p, q;
			setfillcolor(EGERGB(102, 102, 102));
			setfontbkcolor(EGERGB(102, 102, 102));
			bar(150, 0, 670, 520);
			for (i = 1; i <= 99; i++) {
				k[i] = 0;
			}
			i = 0;
			for (p = 0; p<11; p++) {
				for (q = 0; q<11; q++) {
					if (mapt[p][q]<0 && k[-mapt[p][q]] == 0) {
						k[-mapt[p][q]] = 1;
						print_mon(-mapt[p][q], i, imgroad, imgwall);
						i++;
					}
				}
			}
			getch();
			printmap(imgroad, imgwall); goto get_c;
		}
		case 102: {
			ifpass[site - 1] = 2;
			pe.tr[2] = 0;
			print_tr(2, 0);
			c = site - 1 + 48;
			goto difc;
		}
		default:goto get_c;
		}
		delay_fps(20);
		if (pe.dir == 1)getimage(img1, img0, 0, 0, 32, 32);
		if (pe.dir == 2)getimage(img1, img0, 0, 33, 32, 32);
		if (pe.dir == 3)getimage(img1, img0, 0, 66, 32, 32);
		if (pe.dir == 4)getimage(img1, img0, 0, 99, 32, 32);
		getimage(imgnman, "road.jpg", 40, 40);
		putimage_transparent(imgnman, img1, 0, 0, 0x000000, 0, 0, 40, 40);//图像重合
																		  //printf(" %d %d",newx,newy);
		choice = nextwalk(newx, newy, imgroad, imgwall, imgnman);  //根据下一步的值作出不同的选择
		if (choice == 0)return 0;
		if (choice == 1)return 1;
		newx = pe.x; newy = pe.y;
	}
		   //鼠标操作
		   if (mousemsg()) {
			   while (mousemsg())msg = getmouse();
			   mousepos(&x, &y);
			   if ((int)msg.is_down() == 1) {
			   helppage:
				   int flag = 0;
				   if (x>20 && x<55 && y>300 && y<335 && pe.tr[1] == 1) {  //怪物宝典
					   c = 'h';
					   flag = 1;
				   }
				   else if (x>60 && x<95 && y>300 && y<335 && pe.tr[2] == 1) { //钻地符
					   c = 'f';
					   print_tr(2, 0);
					   flag = 1;
				   }
				   else if (x>20 && x<55 && y>340 && y<375 && pe.tr[4] == 1) {  //镐
					   c = 'j';
					   print_tr(4, 0);
					   flag = 1;
				   }
				   else if (x>100 && x<135 && y>300 && y<318 && pe.tr[3] == 1) {  //上楼
					   c = site + 1 + 48;
					   print_tr(3);
					   flag = 1;
				   }
				   else if (x>100 && x<135 && y>317 && y<335 && pe.tr[3] == 1) { //下楼
					   c = site - 1 + 48;
					   print_tr(3);
					   flag = 1;
				   }
				   else if (x>730 && x<750 && y>461 && y<481) {       //设置音乐开关
					   music_flag = 1 - music_flag;
				   }
				   else if (x>730 && x<750 && y>486 && y<506) {          //设置秒杀开关
					   pe.atk += sec_kill * 10000;
					   printnum();
					   delay_fps(1000);
					   sec_kill = -sec_kill;
				   }
				   else if (x<83 && x>63 && y<481 && y>461) {   //打开帮助页面
					   char c;
					   mapt[pe.x][pe.y] = man;
					   setfillcolor(EGERGB(0, 0, 0));
					   setfontbkcolor(EGERGB(0, 0, 0));
					   while (1) {
						   bar(150, 0, 670, 520);
						   setcolor(EGERGB(255, 255, 255));
						   setfont(15, 0, "黑体");
						   xyprintf(160, 20, "上下左右(或WSAD)键移动,O-一键胜利,P-一键死亡,C-存档，空格-帮助");
						   xyprintf(160, 40, "所有法宝都有鼠标、键盘两种使用方式");
						   getimage(img1, "ud.png");
						   putimage(160, 60, img1);
						   xyprintf(200, 60, "升降器：可快速到达已到达过的上下层");
						   xyprintf(200, 80, "按数字键或PgUp、PgDn使用");
						   getimage(img1, "book.png");
						   putimage(160, 105, img1);
						   xyprintf(200, 105, "怪物宝典：可以查看怪物信息");
						   xyprintf(200, 125, "按H使用");
						   getimage(img1, "gao.png");
						   putimage(160, 150, img1);
						   xyprintf(200, 150, "镐：可以拆上下左右四方墙（一次性）");
						   xyprintf(200, 170, "按J使用");
						   getimage(img1, "trdown.png");
						   putimage(160, 195, img1);
						   xyprintf(200, 195, "钻地符：此法宝可以直接飞到前一层（一次性，想想再用）");
						   xyprintf(200, 215, "按F使用");
						   xyprintf(160, 240, "红宝石加攻击,蓝宝石加防御,瓶子加血,有些门打败怪物就会解锁");
						   xyprintf(160, 260, "开启秒杀模式时，攻击瞬间会上涨1w,但不建议打开");
						   setcolor(EGERGB(244, 223, 23));
						   setfont(13, 0, "黑体");
						   xyprintf(400, 442, "按空格返回游戏");
						   c = getch();
						   if (c == 32)break;  //空格从帮助界面退出
					   }
					   setfont(15, 0, "黑体");
					   printmap(imgroad, imgwall);
				   }
				   else if (x<83 && x>63 && y<506 && y>486) {                 //返回
					   return 2;
				   }
				   if (flag)goto difc;
			   }
		   }
		   //下面是鼠标移到相应按钮上，按钮样子变化
		   mousepos(&x, &y);
		   if (pe.tr[1] == 1) {
			   if (x<55 && x>20 && y<335 && y>300) {
				   setfillcolor(EGERGB(0, 255, 0));
				   setfontbkcolor(EGERGB(0, 255, 0));
				   setcolor(EGERGB(0, 0, 0));
				   bar(20, 300, 55, 335);
				   xyprintf(32, 312, "H");
			   }
			   else {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(20, 300, 55, 335);
				   print_tr(1);
			   }
		   }
		   if (pe.tr[2] == 1) {
			   if (x<95 && x>60 && y<335 && y>300) {
				   setfillcolor(EGERGB(0, 255, 0));
				   setfontbkcolor(EGERGB(0, 255, 0));
				   setcolor(EGERGB(0, 0, 0));
				   bar(60, 300, 95, 335);
				   xyprintf(72, 312, "F");
			   }
			   else {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(60, 300, 95, 335);
				   print_tr(2);
			   }
		   }
		   if (pe.tr[3] == 1) {
			   if (x<135 && x>100 && y<318 && y>300) {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(100, 300, 135, 335);
				   print_tr(3);
				   setfillcolor(EGERGB(0, 255, 0));
				   setfontbkcolor(EGERGB(0, 255, 0));
				   setcolor(EGERGB(0, 0, 0));
				   bar(100, 300, 135, 318);
				   xyprintf(102, 300, "PgUp");
			   }
			   else if (x<135 && x>100 && y<335 && y>317) {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(100, 300, 135, 335);
				   print_tr(3);
				   setfillcolor(EGERGB(0, 255, 0));
				   setfontbkcolor(EGERGB(0, 255, 0));
				   setcolor(EGERGB(0, 0, 0));
				   bar(100, 317, 135, 335);
				   xyprintf(102, 316, "PgDn");
			   }
			   else {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(100, 300, 135, 335);
				   print_tr(3);
			   }
		   }
		   if (pe.tr[4] == 1) {
			   if (x<60 && x>20 && y<375 && y>340) {
				   setfillcolor(EGERGB(0, 255, 0));
				   setfontbkcolor(EGERGB(0, 255, 0));
				   setcolor(EGERGB(0, 0, 0));
				   bar(20, 340, 55, 375);
				   xyprintf(32, 352, "J");
			   }
			   else {
				   setfillcolor(EGERGB(102, 102, 102));
				   bar(20, 340, 55, 375);
				   print_tr(4);
			   }
		   }
		   if (x>730 && x<750 && y>461 && y<481) {
			   setfillcolor(EGERGB(255, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(730, 461, 750, 481);
			   setfontbkcolor(EGERGB(255, 255, 0));
			   if (music_flag)xyprintf(732, 463, "开");
			   else xyprintf(732, 463, "关");
		   }
		   else {
			   setfillcolor(EGERGB(0, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(730, 461, 750, 481);
			   setfontbkcolor(EGERGB(0, 255, 0));
			   if (music_flag)xyprintf(732, 463, "开");
			   else xyprintf(732, 463, "关");
		   }
		   if (x>730 && x<750 && y>486 && y<506) {
			   setfillcolor(EGERGB(255, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(730, 486, 750, 506);
			   setfontbkcolor(EGERGB(255, 255, 0));
			   if (sec_kill == 1)xyprintf(732, 488, "关");
			   else xyprintf(732, 488, "开");
		   }
		   else {
			   setfillcolor(EGERGB(0, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(730, 486, 750, 506);
			   setfontbkcolor(EGERGB(0, 255, 0));
			   if (sec_kill == 1)xyprintf(732, 488, "关");
			   else xyprintf(732, 488, "开");
		   }
		   if (x<83 && x>63 && y<481 && y>461) {
			   setfillcolor(EGERGB(255, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(63, 461, 83, 481);
			   setfontbkcolor(EGERGB(255, 255, 0));
			   xyprintf(67, 463, "?");
		   }
		   else {
			   setfillcolor(EGERGB(0, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(63, 461, 83, 481);
			   setfontbkcolor(EGERGB(0, 255, 0));
			   xyprintf(67, 463, "?");
		   }
		   if (x<83 && x>63 && y<506 && y>486) {
			   setfillcolor(EGERGB(255, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(63, 486, 83, 506);
			   setfontbkcolor(EGERGB(255, 255, 0));
			   xyprintf(65, 488, "←");
		   }
		   else {
			   setfillcolor(EGERGB(0, 255, 0));
			   setcolor(EGERGB(0, 0, 0));
			   bar(63, 486, 83, 506);
			   setfontbkcolor(EGERGB(0, 255, 0));
			   xyprintf(65, 488, "←");
		   }
		   setfontbkcolor(EGERGB(102, 102, 102));
		   delay_fps(300);
	}
	delimage(img0);
	delimage(imgnman);
}
int fight(int mkind, PIMAGE imgwall, PIMAGE imgroad, int newx, int newy) {      //战斗函数
	int monblood, flag = 0;
	int patk, matk;
	PIMAGE imgnman = newimage();
	PIMAGE img1 = newimage();
	monblood = mon[mkind].blood;
	putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	setbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(240, 240, 240));
	cleanmon(0);
	printone(-mkind, 710, 301, imgroad, imgwall, 1);
	xyprintf(729, 380, "%d    ", monblood);
	xyprintf(729, 405, "%d   ", mon[mkind].atk);
	xyprintf(729, 430, "%d   ", mon[mkind].def);
	xyprintf(710, 350, "%s", mon[mkind].name);
	delay_fps(1000);
	if (pe.atk <= mon[mkind].def) {
		clean();
		setfontbkcolor(EGERGB(255, 255, 255));
		outtextrect(0, 520, 820, 550, "你攻击不够 ");
		setfontbkcolor(EGERGB(102, 102, 102));
		return 0;
	}
	patk = pe.atk - mon[mkind].def;
	matk = mon[mkind].atk - pe.def;
	if (matk<0)matk = 0;
	while (monblood>0 && pe.blood>0) {
		if (music_flag)mushit.Play(0);
		getimage(img1, "man.png");
		getimage(imgnman, "road.jpg");
		putimage_transparent(imgnman, img1, 0, 0, 0x000000, 0, 0, getwidth(img1), getheight(img1));//图像重合
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
		delay_fps(1000);
		delay_fps(11);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		getimage(imgnman, "bang.png");
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
		delay_fps(1000);
		delay_fps(11);
		printone(-mkind, newy * 40 + 190, newx * 40 + 40, imgroad, imgwall, 0);
		delay_fps(1000);
		setbkcolor(EGERGB(102, 102, 102));
		setcolor(EGERGB(240, 240, 240));
		xyprintf(50, 106, "%d    ", pe.blood);
		xyprintf(729, 380, "%d    ", monblood);
		xyprintf(729, 405, "%d", mon[mkind].atk);
		xyprintf(729, 430, "%d", mon[mkind].def);
		delay_fps(11);
		setfontbkcolor(EGERGB(255, 255, 255));
		setcolor(EGERGB(0, 0, 0));
		flag = 1 - flag;
		if (flag) {
			if (random(99)<mon[mkind].miss) {
				clean();
				outtextrect(0, 520, 820, 550, "你的攻击未击中 "); continue;
			}
			if (random(99)<pe.double_atk) {
				clean(); xyprintf(0, 520, "你打出致命一击，造成%d点伤害", 2 * patk);
				monblood -= 2 * patk;
			}
			else {
				clean(); xyprintf(0, 520, "你对%s造成%d点伤害", mon[mkind].name, patk);
				monblood -= patk;
			}
		}
		else {
			if (random(99)<pe.miss) {
				clean();
				outtextrect(0, 520, 820, 550, "你闪避了攻击 "); continue;
			}
			if (random(99)<mon[mkind].double_atk) {
				clean(); xyprintf(0, 520, "%s打出致命一击，造成%d点伤害", mon[mkind].name, 2 * matk);
				pe.blood -= 2 * matk;
			}
			else {
				clean(); xyprintf(0, 520, "%s对你造成%d点伤害", mon[mkind].name, matk);
				pe.blood -= matk;
			}
		}
	}
	setbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(240, 240, 240));
	monblood = 0;
	xyprintf(729, 380, "%d    ", monblood);
	setfontbkcolor(EGERGB(255, 255, 255));
	if (pe.blood <= 0) {
		clean();
		outtextrect(0, 520, 820, 550, "game over ");
		setfontbkcolor(EGERGB(102, 102, 102));
		return 2;
	}
	else if (monblood <= 0) {
		clean();
		xyprintf(0, 520, "%s 被击败了,你得到了%d个金币", mon[mkind].name, mon[mkind].money);
		pe.money += mon[mkind].money;
		if (mkind == 30)win = 1;
	}
	setfontbkcolor(EGERGB(102, 102, 102));
	setcolor(EGERGB(255, 255, 255));
	xyprintf(50, 198, "%d  ", pe.money);
	delay_fps(1000);
	delimage(imgnman);
	delimage(img1);
	return 1;
}
void clean(void) {   //清理底端文字
	setfillcolor(EGERGB(255, 255, 255));
	bar(0, 520, 820, 550);
	setfontbkcolor(EGERGB(255, 255, 255));
	setcolor(EGERGB(0, 100, 56));
	xyprintf(540, 520, "遇到困难看帮助或左下信息");
	setcolor(EGERGB(0, 0, 0));
}
void cleanmon(int choice) {   //清理 2-怪物信息 1-武器信息
	setfillcolor(EGERGB(102, 102, 102));
	if (choice == 0)bar(680, 288, 804, 372);
	if (choice == 1) {
		bar(760, 55, 808, 106);
		bar(680, 82, 800, 106);
	}
	if (choice == 2) {
		bar(760, 120, 808, 169);
		bar(680, 145, 800, 169);
	}
}
int talk(int mankind) {    //对话
	int flag0;
	mapt[pe.x][pe.y] = man;
	switch (mankind) {
	case oldman: {
		if (site == 2) {
			char ch[] = "好孩子，老朽捡到了有469金币，是你的么？";
			flag0 = talkbox(4, ch);
			if (flag0) {
				setfontbkcolor(EGERGB(102, 102, 102));
				setcolor(EGERGB(255, 255, 255));
				pe.money += 469;
				xyprintf(50, 198, "%d  ", pe.money);
				delay_fps(1000);
				return 1;
			}
			else {
				char ch[] = "不为金钱所动，真是好男儿！\n这有把我祖传的屠龙宝刀，可增加致命一击概率\n点击就送你了！";
				flag0 = talkbox(1, ch);
				pe.double_atk += 65;
				print_equip(53);
				delay_fps(1000);
				xyprintf(30, 252, "暴击率：%d%% ", pe.double_atk);
				return 1;
			}
		}
		if (site == 5) {
			char ch[] = "我听说，某扇门坏了..";
			talkbox(3, ch);
		}
		if (site == 3) {
			char ch[] = "我这有一本怪物宝典，按H可以查看怪物状态;\n少年，维护世界和平的重任就交到你手里了";
			flag0 = talkbox(1, ch);
			pe.tr[1] = 1;
			print_tr(1);
			delay_fps(1000);
			return 1;
		}
		if (site == 1) {
			char ch[] = "诸位在塔，有两个问题应该自己问问\n第一，你数数从几开始数？\n第二，你以为我们npc说来说去，就只有一套\n话吗？";
			flag0 = talkbox(3, ch);
			delay_fps(1000);
			return 1;
		}
	}break;
	case shopman: {
		if (site == 0) {
			char ch[] = "我有一双轻羽靴，增加回避概率，\n只要201金币，就是你的了,要吗？";
			flag0 = talkbox(2, ch);
			if (flag0) {
				if (pe.money<201) {
					char ch[] = "没钱还想买东西，滚一边去";
					talkbox(3, ch); return 0;
				}
				setfontbkcolor(EGERGB(102, 102, 102));
				setcolor(EGERGB(255, 255, 255));
				pe.money -= 201;
				pe.miss += 34;
				print_equip(54);
				delay_fps(1000);
				xyprintf(50, 198, "%d  ", pe.money);
				xyprintf(30, 272, "闪避率：%d%% ", pe.miss);
				delay_fps(1000);
			}
			return flag0;
		}
		if (site == 2) {
			char ch[] = "感谢你救了我\n只需一个金币，我就帮你提升10%攻击防御，\n怎么样，心动了吗？";
			flag0 = talkbox(2, ch);
			if (flag0) {
				if (pe.money<1) {
					char ch[] = "没钱还想买东西，滚一边去";
					talkbox(3, ch); return 0;
				}
				setfontbkcolor(EGERGB(102, 102, 102));
				setcolor(EGERGB(255, 255, 255));
				pe.money -= 1;
				pe.atk += pe.atk / 10 + 1;
				pe.def += pe.def / 10 + 1;
				xyprintf(50, 198, "%d ", pe.money);
				xyprintf(50, 136, "%d ", pe.atk);
				xyprintf(50, 166, "%d ", pe.def);
				delay_fps(1000);
			}
			return flag0;
		}
	}break;
	case shopman1: {
		char ch[] = "我卖的盾天下无镐可破，提升防御30点\n一口价99个金币，要吗？";
		flag0 = talkbox(2, ch);
		if (flag0) {
			if (pe.money<99) {
				char ch[] = "没钱还想买东西，滚一边去";
				talkbox(3, ch); return 0;
			}
			setfontbkcolor(EGERGB(102, 102, 102));
			setcolor(EGERGB(255, 255, 255));
			pe.money -= 99;
			pe.def += 30;
			print_equip(55);
			delay_fps(1000);
			xyprintf(50, 198, "%d    ", pe.money);
			xyprintf(50, 166, "%d  ", pe.def);
			delay_fps(1000);
		}
		return flag0;
	}
	case shopman2: {
		char ch[] = "我卖的镐天下无盾可挡，可拆四方墙\n一口价99个金币，要吗？";
		flag0 = talkbox(2, ch);
		if (flag0) {
			if (pe.money<99) {
				char ch[] = "没钱还想买东西，滚一边去";
				talkbox(3, ch); return 0;
			}
			setfontbkcolor(EGERGB(102, 102, 102));
			setcolor(EGERGB(255, 255, 255));
			pe.money -= 99;
			pe.tr[4] = 1;
			print_tr(4);
			xyprintf(50, 198, "%d    ", pe.money);
			delay_fps(1000);
		}
		return flag0;
	}
	case myfriend: {
		if (site == 2) {
			char ch[] = "这看守所我已经呆了十年了。。\n这有个到（当前楼层-1）层的宝物\n我用它来报答你吧";
			talkbox(1, ch);
			pe.tr[2] = 1;
			print_tr(2); delay_fps(1000);
			return 1;
		}
	}break;
	case myfriend_end: {
		char ch[] = "打工这方面，打工是不可能打工的..";
		talkbox(3, ch);
		return 1;
	}break;
	case oldman_end: {
		if (site == 2) {
			char ch[] = "想救公主，必须打败魔王";
			talkbox(3, ch);
		}
		if (site == 3) {
			char ch[] = "想当年，我雄姿英发...\n叹如今，廉颇老矣，不能饭了..";
			talkbox(3, ch);
		}
		if (site == 5) {
			char ch[] = "不弄坏门，镐子又怎么卖得出去呢？→_→";
			talkbox(3, ch);
		}
		if (site == 1) {
			char ch[] = "我交给你的两个问题想的怎么样了。";
			talkbox(3, ch);
		}
		return 1;
	}break;
	case shopman1_end: {
		char ch[] = "跟你说个秘密，对面的镐贼钝..";
		talkbox(3, ch);
		return 1;
	}break;
	case shopman2_end: {
		char ch[] = "跟你说个秘密，对面的盾贼脆..";
		talkbox(3, ch);
		return 1;
	}break;
	case shopman_end: {
		if (site == 0) {
			char ch[] = "江南皮革厂倒闭啦!\n原价200多的钱包，现在统统20块..";
			talkbox(3, ch);
		}
		if (site == 2) {
			char ch[] = "我从来没碰过钱，我对钱没有兴趣";
			talkbox(3, ch);
		}
		return 1;
	}
	}
	return 0;
}
//1-谢谢  2-是的我再想想  3-...  4-是的不是
int talkbox(int kind, char words[]) {
	char c;
	int x, y;
	setfillcolor(EGERGB(150, 158, 148));
	bar(190, 100, 630, 370);
	setfillcolor(EGERGB(255, 255, 255));
	bar(240, 136, 580, 315);
	setfontbkcolor(EGERGB(255, 255, 255));
	setcolor(EGERGB(2, 2, 2));
	outtextrect(252, 146, 570, 330, words);
	if (kind == 1 || kind == 3) {
		setfillcolor(EGERGB(0, 255, 0));
		bar(500, 326, 573, 355);
		setfontbkcolor(EGERGB(0, 255, 0));
		if (kind == 1)xyprintf(510, 336, "<y>谢谢");
		else xyprintf(510, 336, "<y>...");
	}
	else if (kind == 2 || kind == 4) {
		setfillcolor(EGERGB(0, 255, 0));
		bar(500, 326, 610, 355);
		bar(410, 326, 483, 355);
		setfontbkcolor(EGERGB(0, 255, 0));
		xyprintf(420, 336, "<y>是的");
		if (kind == 2)xyprintf(510, 336, "<n>我再想想");
		else xyprintf(510, 336, "<n>不是");
	}
	delay_fps(1000);
	if (kind == 1 || kind == 3) {
		while (1) {
			if (kbhit()) {
				c = getch();
				if (c == 121)return 1;
			}
			if (mousemsg()) {
				while (mousemsg())msg = getmouse();
				mousepos(&x, &y);
				if ((int)msg.is_down() == 1) {
					if (x>500 && x<573 && y>326 && y<355) {
						return 1;
					}
				}
			}
			mousepos(&x, &y);
			if (x>500 && x<573 && y>326 && y<355) {
				setfillcolor(EGERGB(255, 255, 0));
				bar(500, 326, 573, 355);
				setfontbkcolor(EGERGB(255, 255, 0));
				if (kind == 1)xyprintf(510, 336, "<y>谢谢");
				else xyprintf(510, 336, "<y>...");
			}
			else {
				setfillcolor(EGERGB(1, 255, 0));
				bar(500, 326, 573, 355);
				setfontbkcolor(EGERGB(1, 255, 0));
				if (kind == 1)xyprintf(510, 336, "<y>谢谢");
				else xyprintf(510, 336, "<y>...");
			}
		}
	}
	else {
		while (1) {
			if (kbhit()) {
				c = getch();
				if (c == 121)return 1;
				if (c == 110)return 0;
			}
			if (mousemsg()) {
				while (mousemsg())msg = getmouse();
				mousepos(&x, &y);
				if ((int)msg.is_down() == 1) {
					if (x>500 && x<610 && y>326 && y<355) {
						return 0;
					}
					if (x>410 && x<483 && y>326 && y<355) {
						return 1;
					}
				}
			}
			mousepos(&x, &y);
			if (x>500 && x<610 && y>326 && y<355) {
				setfillcolor(EGERGB(255, 255, 0));
				bar(500, 326, 610, 355);
				setfontbkcolor(EGERGB(255, 255, 0));
				if (kind == 2)xyprintf(510, 336, "<n>我再想想");
				if (kind == 4) xyprintf(510, 336, "<n>不是");
			}
			else {
				setfillcolor(EGERGB(0, 255, 0));
				bar(500, 326, 610, 355);
				setfontbkcolor(EGERGB(0, 255, 0));
				if (kind == 2)xyprintf(510, 336, "<n>我再想想");
				if (kind == 4) xyprintf(510, 336, "<n>不是");
			}
			if (x>410 && x<483 && y>326 && y<355) {
				setfillcolor(EGERGB(255, 255, 0));
				bar(410, 326, 483, 355);
				setfontbkcolor(EGERGB(255, 255, 0));
				xyprintf(420, 336, "<y>是的");
			}
			else {
				setfillcolor(EGERGB(0, 255, 0));
				bar(410, 326, 483, 355);
				setfontbkcolor(EGERGB(0, 255, 0));
				xyprintf(420, 336, "<y>是的");
			}
		}
	}
}
void savegame(void) {
	//记录顺序为 当前楼层，是否经过楼层,人物坐标，血量
	//攻击,防御,金钱，暴击，闪避，钥匙，宝物
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	int i;
	fp = fopen("person.txt", "w");
	mapt[pe.x][pe.y] = man;
	savemap();
	ifpass[site] = 1;
	fprintf(fp, "%d ", site);
	for (i = 0; i <= 50; i++) {
		fprintf(fp, "%d ", ifpass[i]);
	}
	fprintf(fp, "%d ", pe.x);
	fprintf(fp, "%d ", pe.y);
	fprintf(fp, "%d ", pe.blood);
	if (pe.atk>10000)fprintf(fp, "%d ", pe.atk - 10000);
	else fprintf(fp, "%d ", pe.atk);
	fprintf(fp, "%d ", pe.def);
	fprintf(fp, "%d ", pe.money);
	fprintf(fp, "%d ", pe.double_atk);
	fprintf(fp, "%d ", pe.miss);
	fprintf(fp, "%d ", pe.ykeynum);
	fprintf(fp, "%d ", pe.bkeynum);
	fprintf(fp, "%d ", pe.rkeynum);
	fprintf(fp, "%d ", pe.equip[0]);
	fprintf(fp, "%d ", pe.equip[1]);
	fprintf(fp, "%d ", win);
	for (i = 0; i <= 9; i++) {
		fprintf(fp, "%d ", pe.tr[i]);
	}
	fclose(fp);
	for (i = 0; i <= 50; i++) {
		if (ifpass[i] && i == 1) {
			fp1 = fopen("newmap1.txt", "r");
			fp2 = fopen("new2map1.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 2) {
			fp1 = fopen("newmap2.txt", "r");
			fp2 = fopen("new2map2.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 3) {
			fp1 = fopen("newmap3.txt", "r");
			fp2 = fopen("new2map3.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 4) {
			fp1 = fopen("newmap4.txt", "r");
			fp2 = fopen("new2map4.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 5) {
			fp1 = fopen("newmap5.txt", "r");
			fp2 = fopen("new2map5.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 6) {
			fp1 = fopen("newmap6.txt", "r");
			fp2 = fopen("new2map6.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 0) {
			fp1 = fopen("newmap0.txt", "r");
			fp2 = fopen("new2map0.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
	}
}
void readgame(void) {
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	int i;
	fp = fopen("person.txt", "r");
	fscanf(fp, "%d", &site);
	for (i = 0; i <= 50; i++) {
		fscanf(fp, "%d", &ifpass[i]);
	}
	fscanf(fp, "%d", &pe.x);
	fscanf(fp, "%d", &pe.y);
	fscanf(fp, "%d", &pe.blood);
	fscanf(fp, "%d", &pe.atk);
	fscanf(fp, "%d", &pe.def);
	fscanf(fp, "%d", &pe.money);
	fscanf(fp, "%d", &pe.double_atk);
	fscanf(fp, "%d", &pe.miss);
	fscanf(fp, "%d", &pe.ykeynum);
	fscanf(fp, "%d", &pe.bkeynum);
	fscanf(fp, "%d", &pe.rkeynum);
	fscanf(fp, "%d", &pe.equip[0]);
	fscanf(fp, "%d", &pe.equip[1]);
	fscanf(fp, "%d", &win);
	for (i = 0; i <= 9; i++) {
		fscanf(fp, "%d", &pe.tr[i]);
	}
	fclose(fp);
	for (i = 0; i <= 50; i++) {
		if (ifpass[i] && i == 1) {
			fp1 = fopen("new2map1.txt", "r");
			fp2 = fopen("newmap1.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 2) {
			fp1 = fopen("new2map2.txt", "r");
			fp2 = fopen("newmap2.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 3) {
			fp1 = fopen("new2map3.txt", "r");
			fp2 = fopen("newmap3.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 4) {
			fp1 = fopen("new2map4.txt", "r");
			fp2 = fopen("newmap4.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 5) {
			fp1 = fopen("new2map5.txt", "r");
			fp2 = fopen("newmap5.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 6) {
			fp1 = fopen("new2map6.txt", "r");
			fp2 = fopen("newmap6.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
		if (ifpass[i] && i == 0) {
			fp1 = fopen("new2map0.txt", "r");
			fp2 = fopen("newmap0.txt", "w");
			swapmap(fp1, fp2);
			fclose(fp1); fclose(fp2);
		}
	}
	readmap(site);
	mapt[pe.x][pe.y] = man;
}
void manwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman) {
	PIMAGE img0 = newimage();
	getimage(img0, "manmove1.png");
	putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	//人的行走中间态
	PIMAGE moveman1 = newimage();
	PIMAGE moveman2 = newimage();
	PIMAGE moveman3 = newimage();
	PIMAGE imgt = newimage();      //辅助用
	if (pe.dir == 1) {  //前
		getimage(moveman1, img0, 40, 0, 40, 40);
		getimage(moveman2, img0, 120, 0, 40, 40);
		getimage(moveman3, img0, 80, 0, 40, 40);
		putimage_withalpha(NULL, moveman1, newy * 40 + 190, newx * 40 + 10);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman3, newy * 40 + 190, newx * 40 + 20);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman2, newy * 40 + 190, newx * 40 + 30);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	}
	if (pe.dir == 2) {  //左
		getimage(moveman1, img0, 40, 42, 40, 40);
		getimage(moveman2, img0, 120, 42, 40, 40);
		getimage(moveman3, img0, 80, 42, 40, 40);
		putimage_withalpha(NULL, moveman1, newy * 40 + 220, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman3, newy * 40 + 210, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman2, newy * 40 + 200, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	}
	if (pe.dir == 3) {  //右
		getimage(moveman1, img0, 40, 82, 40, 40);
		getimage(moveman2, img0, 120, 82, 40, 40);
		getimage(moveman3, img0, 80, 82, 40, 40);
		putimage_withalpha(NULL, moveman1, newy * 40 + 160, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman3, newy * 40 + 170, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman2, newy * 40 + 180, newx * 40 + 40);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	}
	if (pe.dir == 4) {  //后
		getimage(moveman1, img0, 40, 122, 40, 39);
		getimage(moveman2, img0, 120, 122, 40, 39);
		getimage(moveman3, img0, 80, 122, 40, 39);
		putimage_withalpha(NULL, moveman1, newy * 40 + 190, newx * 40 + 70);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman3, newy * 40 + 190, newx * 40 + 60);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage_withalpha(NULL, moveman2, newy * 40 + 190, newx * 40 + 50);
		delay_fps(20);
		putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
	}
	putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
	delay_fps(18);
	mapt[newx][newy] = man; mapt[pe.x][pe.y] = road;
	pe.y = newy; pe.x = newx;
	delimage(moveman1);
	delimage(moveman2);
	delimage(moveman3);
	delimage(img0);
	delimage(imgt);
}
int nextwalk(int newx, int newy, PIMAGE imgroad, PIMAGE imgwall, PIMAGE imgnman) {
	int i, j, choice;
	if (newx == -1 || newy == 11 || newy == -1 || newx == 11 || mapt[newx][newy] == wall || mapt[newx][newy] == medoor || mapt[newx][newy] == bossdoor) {
		putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
		delay_fps(1000);
	}
	//升降器
	else if (mapt[newx][newy] == 20) {
		pe.tr[3] = 1;
		print_tr(3); delay_fps(1000);
		mapt[newx][newy] = 0;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	//战斗
	else if (mapt[newx][newy]<0) {
		//choice代表战斗结果 0-打不了 1-赢了 2-挂了
		choice = fight(-mapt[newx][newy], imgwall, imgroad, newx, newy);
		if (choice == 0) putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
		else if (choice == 1) {
			putimage(newy * 40 + 190, newx * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
			mapt[newx][newy] = man; mapt[pe.x][pe.y] = road;
			if (site == 5) {
				if (mapt[4][8] >= 0 && mapt[4][10] >= 0) {
					mapt[3][9] = 0;
					putimage(550, 160, 40, 40, imgroad, 0, 0, getwidth(imgroad), getheight(imgroad));
					delay_fps(1000);
				}
			}
			if (site == 2) {
				if (mapt[1][5] >= 0 && mapt[1][7] >= 0) {
					for (i = 0; i <= 10; i++) {
						for (j = 0; j<11; j++) {
							if (mapt[i][j] == 6)mapt[i][j] = 0;
						}
					}
				}
				printmap(imgroad, imgwall);
			}
			if (site == 6) {
				if (mapt[2][4] >= 0 && mapt[3][4] >= 0 && mapt[4][4] >= 0 &&
					mapt[6][4] >= 0 && mapt[7][4] >= 0 && mapt[8][4] >= 0)
				{
					mapt[5][5] = 0;
				}
				printmap(imgroad, imgwall);
			}
			pe.y = newy; pe.x = newx;
		}
		else if (choice == 2) {
			return 0;
		}
	}
	else if (mapt[newx][newy] == fire) {       //岩浆
		if (pe.tr[5] == 1) {
			mapt[newx][newy] = road;
			manwalk(newx, newy, imgroad, imgwall, imgnman);
		}
		else {
			clean();
			setfontbkcolor(EGERGB(255, 255, 255));
			xyprintf(0, 520, "你没有拿到神圣盾，无法抵御岩浆的侵蚀");
		}
	}
	else if (mapt[newx][newy] == road) {
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == yellowdoor) {
		if (pe.ykeynum == 0) {
			clean();
			setfontbkcolor(EGERGB(255, 255, 255));
			xyprintf(0, 520, "黄钥匙不足");
			putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
			delay_fps(1000);
		}
		else {
			if (music_flag)musdoor.Play(0);
			pe.ykeynum -= 1;
			setcolor(EGERGB(240, 240, 20));
			xyprintf(686, 186, "黄钥匙：%d ", pe.ykeynum);
			mapt[newx][newy] = road;
			manwalk(newx, newy, imgroad, imgwall, imgnman);
			delay_fps(2);
		}
	}
	else if (mapt[newx][newy] == bluedoor) {
		if (pe.bkeynum == 0) {
			if (pe.ykeynum == 0) {
				clean();
				setfontbkcolor(EGERGB(255, 255, 255));
				xyprintf(0, 520, "蓝钥匙不足");
				putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
				delay_fps(1000);
			}
		}
		else {
			if (music_flag)musdoor.Play(0);
			pe.bkeynum -= 1;
			setcolor(EGERGB(20, 20, 240));
			xyprintf(686, 216, "蓝钥匙：%d ", pe.bkeynum);
			mapt[newx][newy] = road;
			manwalk(newx, newy, imgroad, imgwall, imgnman);
			delay_fps(2);
		}
	}
	else if (mapt[newx][newy] == reddoor) {
		if (pe.rkeynum == 0) {
			clean();
			setfontbkcolor(EGERGB(255, 255, 255));
			xyprintf(0, 520, "红钥匙不足");
			putimage(pe.y * 40 + 190, pe.x * 40 + 40, 40, 40, imgnman, 0, 0, getwidth(imgnman), getheight(imgnman));
			delay_fps(1000);
		}
		else {
			if (music_flag)musdoor.Play(0);
			pe.rkeynum -= 1;
			setcolor(EGERGB(240, 20, 20));
			xyprintf(686, 246, "红钥匙：%d ", pe.rkeynum);
			mapt[newx][newy] = road;
			manwalk(newx, newy, imgroad, imgwall, imgnman);
			delay_fps(2);
		}
	}
	else if (mapt[newx][newy] == yellowkey) {
		if (music_flag)musget.Play(0);
		pe.ykeynum += 1;
		setcolor(EGERGB(240, 240, 20));
		xyprintf(686, 186, "黄钥匙：%d ", pe.ykeynum);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == woman) {          //公主
		return 1;
	}
	else if (mapt[newx][newy] == bluekey) {
		if (music_flag)musget.Play(0);
		pe.bkeynum++;
		setcolor(EGERGB(20, 20, 240));
		xyprintf(686, 216, "蓝钥匙：%d ", pe.bkeynum);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == redkey) {
		if (music_flag)musget.Play(0);
		pe.rkeynum++;
		setcolor(EGERGB(240, 20, 20));
		xyprintf(686, 246, "红钥匙：%d ", pe.rkeynum);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == bloodbottle) {
		if (music_flag)musget.Play(0);
		pe.blood += 500;
		setcolor(EGERGB(240, 240, 240));
		xyprintf(50, 106, "%d", pe.blood);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == redstone || mapt[newx][newy] == 51) { //红宝石或神圣剑
		if (music_flag)musget.Play(0);
		if (mapt[newx][newy] == 51)print_equip(51);
		delay_fps(1000);
		pe.atk += 3; if (mapt[newx][newy] == 51)pe.atk += 76;
		setcolor(EGERGB(240, 240, 240));
		xyprintf(50, 136, "%d ", pe.atk);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == bluestone || mapt[newx][newy] == 52) {  //蓝宝石或神圣盾
		if (music_flag)musget.Play(0);
		if (mapt[newx][newy] == 52)print_equip(52);
		delay_fps(1000);
		pe.def += 2;
		if (mapt[newx][newy] == 52) {
			pe.def += 42; pe.tr[5] = 1;
		}
		setcolor(EGERGB(240, 240, 240));
		xyprintf(50, 166, "%d", pe.def);
		mapt[newx][newy] = road;
		manwalk(newx, newy, imgroad, imgwall, imgnman);
	}
	else if (mapt[newx][newy] == uproad) {         //上楼
		mapt[pe.x][pe.y] = 0;
		savemap();
		ifpass[site] = 1;
		site += 1;
		readmap(site);
		if (site == 1) {
			pe.x = 10; pe.y = 5;
			mapt[10][5] = 100;
		}
		else {
			for (i = 0; i<11; i++) {
				for (j = 0; j<11; j++) {
					if (mapt[i][j] == 12)goto out1;
				}
			}
		out1:if (i - 1>-1 && mapt[i - 1][j] == 0) {
			pe.x = i - 1; pe.y = j;
			mapt[i - 1][j] = 100;
		}
			 else if (i + 1<11 && mapt[i + 1][j] == 0) {
				 pe.x = i + 1; pe.y = j;
				 mapt[i + 1][j] = 100;
			 }
			 else if (j - 1>-1 && mapt[i][j - 1] == 0) {
				 pe.x = i; pe.y = j - 1;
				 mapt[i][j - 1] = 100;
			 }
			 else if (j + 1<11 && mapt[i][j + 1] == 0) {
				 pe.x = i; pe.y = j + 1;
				 mapt[i][j + 1] = 100;
			 }
		}
		printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == downroad) {         //下楼
		mapt[pe.x][pe.y] = 0;
		savemap();
		ifpass[site] = 1;
		site -= 1;
		readmap(site);
		for (i = 0; i<11; i++) {
			for (j = 0; j<11; j++) {
				if (mapt[i][j] == 11)goto out2;
			}
		}
	out2: if (i - 1>-1 && mapt[i - 1][j] == 0) {
		pe.x = i - 1; pe.y = j;
		mapt[i - 1][j] = man;
	}
		  else if (i + 1<11 && mapt[i + 1][j] == 0) {
			  pe.x = i + 1; pe.y = j;
			  mapt[i + 1][j] = man;
		  }
		  else if (j - 1>-1 && mapt[i][j - 1] == 0) {
			  pe.x = i; pe.y = j - 1;
			  mapt[i][j - 1] = man;
		  }
		  else if (j + 1<11 && mapt[i][j + 1] == 0) {
			  pe.x = i; pe.y = j + 1;
			  mapt[i][j + 1] = man;
		  }
		  printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == oldman) {      //oldman
		talk(oldman);
		mapt[newx][newy] = oldman_end;
		printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == shopman) {      //shopman
		int flag1;
		flag1 = talk(shopman);
		if (flag1)mapt[newx][newy] = shopman_end;
		printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == shopman1) {
		int flag1;
		flag1 = talk(shopman1);
		if (flag1)mapt[newx][newy] = shopman1_end;
		printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == shopman2) {
		int flag1;
		flag1 = talk(shopman2);
		if (flag1)mapt[newx][newy] = shopman2_end;
		printmap(imgroad, imgwall);
	}
	else if (mapt[newx][newy] == myfriend) {     //friend
		talk(myfriend);
		mapt[newx][newy] = myfriend_end;
		printmap(imgroad, imgwall);
	}
	//后缀end表示是已经进行完第一段对话，变成第二段
	else if (mapt[newx][newy] == myfriend_end || mapt[newx][newy] == shopman1_end ||
		mapt[newx][newy] == shopman2_end || mapt[newx][newy] == shopman_end ||
		mapt[newx][newy] == oldman_end) {
		talk(mapt[newx][newy]);
		printmap(imgroad, imgwall);
	}
	else;
	return 2;
}

//下面是帐户注册块
void clear(char *temp)
{
	int ordinal;

	for (ordinal = 0; ordinal < 20; ordinal++)
		*(temp + ordinal) = 0;
	ID_ordinal = 0;
	keyword_ordinal = 0;
	rekeyword_ordinal = 0;
	invisible_key_ordinal = 0;
	invisible_rekey_ordinal = 0;
}

bool security_check(char *temp)
{
	int ordinal;
	bool flag = 0;

	for (ordinal = 0; ordinal < 20; ordinal++)
		if (*(temp + ordinal) != 0) {
			flag = 1;
			break;
		}

	return flag;
}

void encrypt(char *temp, char *backup)
{
	int ordinal = 0;

	while (*(temp + ordinal) != 0) {
		*(backup + ordinal) = *(temp + ordinal) - 17;
		ordinal++;
	}
	while (ordinal < 20) {
		*(backup + ordinal) = 0;
		ordinal++;
	}
}

void decrypt(char *temp)
{
	int ordinal = 0;

	while (*(temp + ordinal) != 0) {
		*(temp + ordinal) += 17;
		ordinal++;
	}
}

int ID_check(FILE *fp)
{
	char temp[20];
	int flag = -1;

	fp = fopen("ID_admin.dat", "rb");
	while (!feof(fp)) {
		fread(temp, sizeof(char), 20, fp);
		decrypt(temp);
		if (strcmp(temp, ID) == 0) {
			fread(temp, sizeof(char), 20, fp);
			decrypt(temp);
			if (strcmp(temp, keyword) == 0)
				flag = 1;
		}
	}
	fclose(fp);

	return flag;
}

int ID_search(FILE *fp)
{
	int flag = 1;
	char temp[20];

	if (security_check(ID) && security_check(keyword)) {
		fp = fopen("ID_admin.dat", "rb");
		while (!feof(fp)) {
			fread(temp, sizeof(char), 20, fp);
			decrypt(temp);
			if (strcmp(temp, ID) == 0) {
				flag = 2;
				break;
			}
		}
		fclose(fp);
		if (strcmp(keyword, rekeyword) != 0)
			flag = 3;
	}
	else
		flag = 4;

	return flag;
}

void ID_store(FILE *fp)
{
	char backup[20];

	fp = fopen("ID_admin.dat", "ab+");
	fseek(fp, 0, SEEK_END);
	encrypt(ID, backup);
	fwrite(backup, sizeof(char), 20, fp);
	encrypt(keyword, backup);
	fwrite(backup, sizeof(char), 20, fp);
	fclose(fp);
}

void admin_initial(void)
{
	PIMAGE bk_admin = newimage();
	getimage(bk_admin, "begin.png");
	putimage(0, 0, 820, 550, bk_admin, 0, 0, getwidth(bk_admin), getheight(bk_admin));
	setlinewidth(1);
	setfont(-20, 0, "黑体");
	setfontbkcolor(EGERGB(0, 0, 0));
	setcolor(EGERGB(128, 128, 255));
	xyprintf(300, 270, "请输入您的账户:");
	xyprintf(300, 340, "请输入您的密码:");
	setfillcolor(EGERGB(255, 255, 255));
	bar(290, 300, 530, 330);
	bar(290, 370, 530, 400);
	setfont(-15, 0, "黑体");
	setfontbkcolor(EGERGB(0, 0, 0));
	xyprintf(300, 410, "没有账户？戳这里创建一个");
	line(300, 425, 490, 425);
	setfillcolor(EGERGB(255, 128, 128));
	bar(380, 455, 440, 485);
	setcolor(EGERGB(128, 128, 255));
	setfontbkcolor(EGERGB(255, 128, 128));
	setfont(-20, 0, "黑体");
	xyprintf(390, 460, "登录");
	setlinewidth(3);
	setcolor(EGERGB(255, 128, 128));
	setfillcolor(EGERGB(255, 128, 128));
	pieslice(510, 390, 0, 360, 4);
	arc(510, 390, 0, 180, 10);
	delimage(bk_admin);
}

void create_initial(void)
{
	PIMAGE bk_create = newimage();
	getimage(bk_create, "begin.png");
	putimage(0, 0, 820, 550, bk_create, 0, 0, getwidth(bk_create), getheight(bk_create));
	setlinewidth(1);
	setfont(-20, 0, "黑体");
	setfontbkcolor(EGERGB(0, 0, 0));
	setcolor(EGERGB(128, 128, 255));
	xyprintf(300, 270, "请输入您的账户:");
	xyprintf(300, 340, "请输入您的密码:");
	xyprintf(300, 410, "请再次确认您的密码:");
	setfillcolor(EGERGB(255, 255, 255));
	bar(290, 300, 530, 330);
	bar(290, 370, 530, 400);
	bar(290, 440, 530, 470);
	setfont(-15, 0, "黑体");
	setfontbkcolor(EGERGB(0, 0, 0));
	xyprintf(300, 480, "点此创建");
	line(300, 495, 360, 495);
	xyprintf(490, 480, "退出");
	line(490, 495, 520, 495);
	setlinewidth(3);
	setcolor(EGERGB(255, 128, 128));
	setfillcolor(EGERGB(255, 128, 128));
	pieslice(510, 390, 0, 360, 4);
	arc(510, 390, 0, 180, 10);
	pieslice(510, 460, 0, 360, 4);
	arc(510, 460, 0, 180, 10);
	delimage(bk_create);
}

void keyboard_input(int flag, int signal)
{
	char temp;

	setfont(-20, 0, "Arial");
	setfontbkcolor(EGERGB(255, 255, 255));
	setcolor(EGERGB(0, 0, 0));
	temp = getch();
	if (temp >= 48 && temp <= 57 || temp >= 65 && temp <= 90 || temp >= 97 && temp <= 122) {
		switch (flag) {
		case 1:
			ID[ID_ordinal++] = temp;
			outtextxy(300, 305, ID);
			break;
		case 2:
			keyword[keyword_ordinal++] = temp;
			invisible_key[invisible_key_ordinal++] = '*';
			outtextxy(300, 375, invisible_key);
			break;
		case 3:
			rekeyword[rekeyword_ordinal++] = temp;
			invisible_rekey[invisible_rekey_ordinal++] = '*';
			outtextxy(300, 445, invisible_rekey);
			break;
		}
	}
	else if (temp == 8) {
		switch (flag) {
		case 1:
			if (ID_ordinal > 0) {
				ID_ordinal--;
				ID[ID_ordinal] = 0;
				clearviewport();
				if (signal == 1)
					admin_initial();
				else
					create_initial();
				setfontbkcolor(EGERGB(255, 255, 255));
				setcolor(EGERGB(0, 0, 0));
				setfont(-20, 0, "Arial");
				outtextxy(300, 305, ID);
				outtextxy(300, 375, invisible_key);
				outtextxy(300, 445, invisible_rekey);
				switch (flag) {
				case 1:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					break;
				case 2:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					break;
				case 3:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 440, 530, 470);
					break;
				}
			}
			break;
		case 2:
			if (keyword_ordinal > 0 && invisible_key_ordinal > 0) {
				keyword_ordinal--;
				keyword[keyword_ordinal] = 0;
				invisible_key_ordinal--;
				invisible_key[invisible_key_ordinal] = 0;
				clearviewport();
				if (signal == 1)
					admin_initial();
				else
					create_initial();
				setfontbkcolor(EGERGB(255, 255, 255));
				setcolor(EGERGB(0, 0, 0));
				setfont(-20, 0, "Arial");
				outtextxy(300, 305, ID);
				outtextxy(300, 375, invisible_key);
				outtextxy(300, 445, invisible_rekey);
				switch (flag) {
				case 1:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					break;
				case 2:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					break;
				case 3:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 440, 530, 470);
					break;
				}
			}
			break;
		case 3:
			if (rekeyword_ordinal > 0 && invisible_rekey_ordinal > 0) {
				rekeyword_ordinal--;
				rekeyword[rekeyword_ordinal] = 0;
				invisible_rekey_ordinal--;
				invisible_rekey[invisible_rekey_ordinal] = 0;
				clearviewport();
				if (signal == 1)
					admin_initial();
				else
					create_initial();
				setfontbkcolor(EGERGB(255, 255, 255));
				setcolor(EGERGB(0, 0, 0));
				setfont(-20, 0, "Arial");
				outtextxy(300, 305, ID);
				outtextxy(300, 375, invisible_key);
				outtextxy(300, 445, invisible_rekey);
				switch (flag) {
				case 1:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					break;
				case 2:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					break;
				case 3:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 440, 530, 470);
					break;
				}
			}
			break;
		}
	}
}

void ID_create(FILE *fp)
{
	mouse_msg mevent;
	int judgement = -1, flag = 0;
	int mouse_x, mouse_y;
	int check;

	create_initial();
	clear(ID);
	clear(keyword);
	clear(rekeyword);
	clear(invisible_key);
	clear(invisible_rekey);
	while (1) {
		if (kbhit())
			keyboard_input(flag, 2);
		if (mousemsg()) {
			mevent = getmouse();
			mousepos(&mouse_x, &mouse_y);
			if (mouse_x > 300 && mouse_x < 360 && mouse_y > 480 && mouse_y < 495) {
				setlinewidth(2);
				setcolor(EGERGB(128, 255, 128));
				setfont(-15, 0, "黑体");
				setfontbkcolor(EGERGB(0, 0, 0));
				xyprintf(300, 480, "点此创建");
				line(300, 495, 360, 495);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					check = ID_search(fp);
					flag = 0;
					if (check == 1) {
						setfillcolor(EGERGB(128, 128, 255));
						bar(0, 245, 820, 305);
						setfont(-40, 0, "黑体");
						setfontbkcolor(EGERGB(128, 128, 255));
						setcolor(EGERGB(255, 128, 128));
						outtextxy(310, 255, "创建成功！");
						ID_store(fp);
						delay_ms(1000);
						clearviewport();
						admin_initial();
						break;
					}
					else if (check == 2) {
						setfillcolor(EGERGB(128, 128, 255));
						bar(0, 245, 820, 305);
						setfont(-40, 0, "黑体");
						setfontbkcolor(EGERGB(128, 128, 255));
						setcolor(EGERGB(255, 128, 128));
						outtextxy(230, 255, "该用户名已被占用！");
						delay_ms(1000);
						clearviewport();
						create_initial();
						clear(ID);
						clear(keyword);
						clear(rekeyword);
						clear(invisible_key);
						clear(invisible_rekey);
					}
					else if (check == 3) {
						setfillcolor(EGERGB(128, 128, 255));
						bar(0, 245, 820, 305);
						setfont(-40, 0, "黑体");
						setfontbkcolor(EGERGB(128, 128, 255));
						setcolor(EGERGB(255, 128, 128));
						outtextxy(230, 255, "两次密码输入不符！");
						delay_ms(1000);
						clearviewport();
						create_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
						outtextxy(300, 445, invisible_rekey);
					}
					else if (check == 4) {
						setfillcolor(EGERGB(128, 128, 255));
						bar(0, 245, 820, 305);
						setfont(-40, 0, "黑体");
						setfontbkcolor(EGERGB(128, 128, 255));
						setcolor(EGERGB(255, 128, 128));
						outtextxy(190, 255, "用户名和密码不能为空！");
						delay_ms(1000);
						clearviewport();
						create_initial();
					}
				}
			}
			else if (mouse_x > 490 && mouse_x < 520 && mouse_y > 480 && mouse_y < 495) {
				setlinewidth(2);
				setcolor(EGERGB(128, 255, 128));
				setfont(-15, 0, "黑体");
				setfontbkcolor(EGERGB(0, 0, 0));
				xyprintf(490, 480, "退出");
				line(490, 495, 520, 495);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					admin_initial();
					break;
				}
			}
			else if (mouse_x > 290 && mouse_x < 530 && mouse_y > 300 && mouse_y < 330) {
				setcolor(EGERGB(128, 255, 128));
				setlinewidth(3);
				rectangle(290, 300, 530, 330);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					create_initial();
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					setfontbkcolor(EGERGB(255, 255, 255));
					setcolor(EGERGB(0, 0, 0));
					setfont(-20, 0, "Arial");
					outtextxy(300, 305, ID);
					outtextxy(300, 375, invisible_key);
					outtextxy(300, 445, invisible_rekey);
					flag = 1;
				}
			}
			else if (mouse_x > 290 && mouse_x < 530 && mouse_y > 370 && mouse_y < 400) {
				setcolor(EGERGB(128, 255, 128));
				setlinewidth(3);
				rectangle(290, 370, 530, 400);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					create_initial();
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					setfontbkcolor(EGERGB(255, 255, 255));
					setcolor(EGERGB(0, 0, 0));
					setfont(-20, 0, "Arial");
					outtextxy(300, 305, ID);
					outtextxy(300, 375, invisible_key);
					outtextxy(300, 445, invisible_rekey);
					if (mouse_x > 500 && mouse_x < 520 && mouse_y > 380 && mouse_y < 390) {
						clearviewport();
						create_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, keyword);
						outtextxy(300, 445, invisible_rekey);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 370, 530, 400);
						setcolor(EGERGB(128, 255, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 390, 0, 360, 4);
						arc(510, 390, 0, 180, 10);
						mevent = getmouse();
						while (!mevent.is_up())
							mevent = getmouse();
						clearviewport();
						create_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
						outtextxy(300, 445, invisible_rekey);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 370, 530, 400);
						setcolor(EGERGB(255, 128, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 390, 0, 360, 4);
						arc(510, 390, 0, 180, 10);
					}
					flag = 2;
				}
			}
			else if (mouse_x > 290 && mouse_x < 530 && mouse_y > 440 && mouse_y < 470) {
				setcolor(EGERGB(128, 255, 128));
				setlinewidth(3);
				rectangle(290, 440, 530, 470);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					create_initial();
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 440, 530, 470);
					setfontbkcolor(EGERGB(255, 255, 255));
					setcolor(EGERGB(0, 0, 0));
					setfont(-20, 0, "Arial");
					outtextxy(300, 305, ID);
					outtextxy(300, 375, invisible_key);
					outtextxy(300, 445, invisible_rekey);
					if (mouse_x > 500 && mouse_x < 520 && mouse_y > 450 && mouse_y < 460) {
						clearviewport();
						create_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
						outtextxy(300, 445, rekeyword);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 440, 530, 470);
						setcolor(EGERGB(128, 255, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 460, 0, 360, 4);
						arc(510, 460, 0, 180, 10);
						mevent = getmouse();
						while (!mevent.is_up())
							mevent = getmouse();
						clearviewport();
						create_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
						outtextxy(300, 445, invisible_rekey);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 440, 530, 470);
						setcolor(EGERGB(255, 128, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 460, 0, 360, 4);
						arc(510, 460, 0, 180, 10);
					}
					flag = 3;
				}
			}
			else if (judgement != 0) {
				clearviewport();
				create_initial();
				setfontbkcolor(EGERGB(255, 255, 255));
				setcolor(EGERGB(0, 0, 0));
				setfont(-20, 0, "Arial");
				outtextxy(300, 305, ID);
				outtextxy(300, 375, invisible_key);
				outtextxy(300, 445, invisible_rekey);
				judgement = 0;
				switch (flag) {
				case 1:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					break;
				case 2:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					break;
				case 3:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 440, 530, 470);
					break;
				}
			}
		}
		delay_ms(10);
	}
}

void ID_identify(FILE *fp)
{
	int mouse_x, mouse_y;
	int flag = 0, judgement = 0;
	mouse_msg mevent;
	int check = 0;

	while (1) {
		if (kbhit())
			keyboard_input(flag, 1);
		if (mousemsg()) {
			mevent = getmouse();
			mousepos(&mouse_x, &mouse_y);
			if (mouse_x > 380 && mouse_x < 440 && mouse_y > 455 && mouse_y < 485) {
				setfillcolor(EGERGB(128, 255, 128));
				bar(380, 455, 440, 485);
				setcolor(EGERGB(128, 128, 255));
				setfontbkcolor(EGERGB(128, 255, 128));
				setfont(-20, 0, "黑体");
				xyprintf(390, 460, "登录");
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					check = ID_check(fp);
					if (check == 1)
						break;
					else if (check == -1) {
						setfillcolor(EGERGB(128, 128, 255));
						bar(0, 245, 820, 305);
						setfont(-40, 0, "黑体");
						setfontbkcolor(EGERGB(128, 128, 255));
						setcolor(EGERGB(255, 128, 128));
						outtextxy(210, 255, "用户名或密码不正确！");
						delay_ms(1000);
						flag = 0;
						clearviewport();
						admin_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
					}
				}
			}
			else if (mouse_x > 290 && mouse_x < 530 && mouse_y > 300 && mouse_y < 330) {
				setcolor(EGERGB(128, 255, 128));
				setlinewidth(3);
				rectangle(290, 300, 530, 330);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					admin_initial();
					setfontbkcolor(EGERGB(255, 255, 255));
					setcolor(EGERGB(0, 0, 0));
					setfont(-20, 0, "Arial");
					outtextxy(300, 305, ID);
					outtextxy(300, 375, invisible_key);
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					flag = 1;
				}
			}
			else if (mouse_x > 290 && mouse_x < 530 && mouse_y > 370 && mouse_y < 400) {
				setcolor(EGERGB(128, 255, 128));
				setlinewidth(3);
				rectangle(290, 370, 530, 400);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					clearviewport();
					admin_initial();
					setfontbkcolor(EGERGB(255, 255, 255));
					setcolor(EGERGB(0, 0, 0));
					setfont(-20, 0, "Arial");
					outtextxy(300, 305, ID);
					outtextxy(300, 375, invisible_key);
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					if (mouse_x > 500 && mouse_x < 520 && mouse_y > 380 && mouse_y < 390) {
						clearviewport();
						admin_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, keyword);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 370, 530, 400);
						setcolor(EGERGB(128, 255, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 390, 0, 360, 4);
						arc(510, 390, 0, 180, 10);
						mevent = getmouse();
						while (!mevent.is_up())
							mevent = getmouse();
						clearviewport();
						admin_initial();
						setfontbkcolor(EGERGB(255, 255, 255));
						setcolor(EGERGB(0, 0, 0));
						setfont(-20, 0, "Arial");
						outtextxy(300, 305, ID);
						outtextxy(300, 375, invisible_key);
						setlinewidth(3);
						setcolor(EGERGB(128, 255, 128));
						rectangle(290, 370, 530, 400);
						setcolor(EGERGB(255, 128, 128));
						setfillcolor(EGERGB(255, 128, 128));
						pieslice(510, 390, 0, 360, 4);
						arc(510, 390, 0, 180, 10);
					}
					flag = 2;
				}
			}
			else if (mouse_x > 300 && mouse_x < 490 && mouse_y > 410 && mouse_y < 425) {
				setlinewidth(2);
				setcolor(EGERGB(128, 255, 128));
				setfont(-15, 0, "黑体");
				setfontbkcolor(EGERGB(0, 0, 0));
				xyprintf(300, 410, "没有账户？戳这里创建一个");
				line(300, 425, 490, 425);
				if (judgement == 0)
					judgement = -1;
				if (mevent.is_down()) {
					ID_create(fp);
					flag = 0;
					clear(ID);
					clear(keyword);
					clear(rekeyword);
					clear(invisible_key);
					clear(invisible_rekey);
				}
			}
			else if (judgement != 0) {
				clearviewport();
				admin_initial();
				setfontbkcolor(EGERGB(255, 255, 255));
				setcolor(EGERGB(0, 0, 0));
				setfont(-20, 0, "Arial");
				outtextxy(300, 305, ID);
				outtextxy(300, 375, invisible_key);
				judgement = 0;
				switch (flag) {
				case 1:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 300, 530, 330);
					break;
				case 2:
					setlinewidth(3);
					setcolor(EGERGB(128, 255, 128));
					rectangle(290, 370, 530, 400);
					break;
				}
			}
		}
		delay_ms(10);
	}
}