#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
// 遊戲功能相關擺最上面，中間擺畫面繪製，系統相關擺最底下
int se_play=1,bgm_play=1,bad_end1=0,bad_end2=0,bad_end3=0,true_end=0,return_title=0,service_use=1;
int land[10]={0},land_price[10],estate[5],map_kind=0,map_kind_order=0,stop[5]={0};
int dead[5]={0};
char *temp[],temp_bgm[100]={'0'};
void main()
{   Initalize(); // 呼叫初始化程式
    Title();
    exit:
    return 0;
}
void Title(){
    int i,select=1,key_pressed=888;
    char *start="〈開始遊戲〉",*option="　系統設定",*exit="  結束遊戲";
    // 播放背景音樂
    PlayBgm("audio\\bgm\\title.wav");
    while(1){
        // 清空畫面
        Clr();
        // 繪製標題畫面
        Title_Draw();
        printf("　　　　　　　　　　　　　　　　　　　　");
        if(select==1)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s\n",start);
        printf("\n　　　　　　　　　　　　　　　　　　　　");
        if(select==2)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s\n",option);
        printf("\n　　　　　　　　　　　　　　　　　　　　");
        if(select==3)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s\n",exit);
        Set_TextColor(7);
        // 清空緩存
        int k;
        while (1) {
            if (kbhit()){
                k=getch();
                if (0==k || 0xE0==k)k=k<<8|getch();
            }
            else
                break;
        }
        // 等待輸入
        key_pressed=Keyboard_Pressed();
        while(key_pressed!=72&&key_pressed!=80&&key_pressed!=13){
            key_pressed=Keyboard_Pressed();
        }
        if(key_pressed==72)
            select--;
        if(key_pressed==80)
            select++;
        if(key_pressed==72||key_pressed==80){
        PlaySe("audio/se/select.wav");
        Sleep(50);
        // 變更選中選項
            if(select>3)
                select=1;
            if(select<1)
                select=3;
            if(select==3){
                start="  開始遊戲";
                option="　系統設定";
                exit="〈結束遊戲〉";
            }
            if(select==1){
                start="〈開始遊戲〉";
                exit="  結束遊戲";
                option="　系統設定";
            }
            if(select==2){
                start="  開始遊戲";
                option="〈系統設定〉";
                exit="　結束遊戲";
            }
        }
        // 按下確認時
        if(select==3&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            Sleep(500);
            return;
        }
        if(select==1&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            Game();
            Sleep(175);
        }
        if(select==2&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            Option();
        }
    }
}
void Option(){
    int i,select=1,key_pressed=888;
    char *bgm_volume="〈開〉",*se_volume="  開",*exit="  儲存並返回";
    while(1){
        Clr();
        // 變更選中選項
            if(select>3)
                select=1;
            if(select<1)
                select=3;
            if(select==2){
                if(bgm_play==0)
                    bgm_volume="　關";
                else
                    bgm_volume="  開";
                if(se_play==0)
                    se_volume="〈關〉";
                else
                    se_volume="〈開〉";
                exit="  儲存並返回";
            }
            if(select==1){
                if(bgm_play==0)
                    bgm_volume="〈關〉";
                else
                    bgm_volume="〈開〉";
                if(se_play==0)
                    se_volume="　關";
                else
                    se_volume="　開";
                exit="  儲存並返回";
            }
            if(select==3){
                if(bgm_play==0)
                    bgm_volume="　關";
                else
                    bgm_volume="　開";
                if(se_play==0)
                    se_volume="　關";
                else
                    se_volume="　開";
                exit="〈儲存並返回〉";
            }
        for(i=0;i<12;i++)
            printf("\n");
        if(select==1)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("　　　　　　　　　　　　　　　　　　　　Bgm播放：%s\n\n",bgm_volume);
        if(select==2)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("　　　　　　　　　　　　　　　　　　　　Se 播放：%s\n\n",se_volume);
        if(select==3)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("　　　　　　　　　　　　　　　　　　　　%s",exit);
        // 等待輸入
        key_pressed=Keyboard_Pressed();
        while(key_pressed!=72&&key_pressed!=80&&key_pressed!=13){
            key_pressed=Keyboard_Pressed();
        }
        if(key_pressed==72)
            select--;
        if(key_pressed==80)
            select++;
        if(key_pressed==72||key_pressed==80){
            PlaySe("audio/se/select.wav");
        Sleep(50);
        }
        // 按下確認時
        if(select==2&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            se_play++;
            if(se_play>1)
                se_play=0;
        }
        if(select==1&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            bgm_play++;
            if(bgm_play>1){
                bgm_play=0;
                PlaySound(NULL,NULL,SND_FILENAME);
            }
            else if(bgm_play==1){
                PlayBgm(temp_bgm);
            }
        }
        if(select==3&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            SaveSet();
            break;
        }
    }
}
void Game(){
    //播放背景音樂
    PlayBgm("audio\\bgm\\game.wav");
    // 初始化
    int money[5],*x[5],moral[5],round=1,i=0,skill[2],bankrupt=0;
    return_title=0;
    skill[0]=rand()%4+1;
    skill[1]=1;
    for(i=0;i<5;i++){
        x[i]=0;
        moral[i]=0;
        money[i]=100000;
        dead[i]=0;
    }
    for(i=0;i<=9;i++){
        land_price[i]=10000;
        land[i]=0;
        estate[i]=0;
        stop[i]=0;
    }
    while(1){
        if(return_title==1){
            PlayBgm("audio\\bgm\\title.wav");
            return;
        }
        if(round==1){
            if(dead[1]==1){
                printf("\n玩家角色已死亡，遊戲結束");
                Sleep(2000);
                PlayBgm("audio\\bgm\\title.wav");
                return;
            }
            // 破產判斷
            for(i=1;i<5;i++){
                if(money[i]<0)
                    bankrupt++;
            }
            if(bankrupt==3&&money[round]>=0){
                printf("\n其他角色皆已破產或死亡，玩家獲得勝利，遊戲結束");
                Sleep(2000);
                PlayBgm("audio\\bgm\\title.wav");
                return;
            }
            service_use=1;
            *x=DrawGameScreen_Player(x,skill,money,moral,round);

        }
        else{
            bankrupt=0;
            //電腦AI
            if(x[round]>27)
                x[round]-=28;
            // 破產判斷
            for(i=1;i<5;i++){
                if(money[i]<0)
                    bankrupt++;
            }
            if(bankrupt==3&&money[round]>=0){
                printf("\n其他角色皆已破產或死亡");
                if(round==2){
                    Set_TextColor(12);
                    printf("凱撒");
                    Set_TextColor(15);
                    printf("獲得勝利，遊戲結束");
                }
                if(round==3){
                    Set_TextColor(6);
                    printf("克雷格");
                    Set_TextColor(15);
                    printf("獲得勝利，遊戲結束");
                }
                if(round==4){
                    Set_TextColor(13);
                    printf("莫伊拉");
                    Set_TextColor(15);
                    printf("獲得勝利，遊戲結束");
                }
                Sleep(2000);
                PlayBgm("audio\\bgm\\title.wav");
                return;
            }
            *x=DrawGameScreen_Ai(x,money,moral,round);
        }
        if(dead[round]==1)
                money[round]=-500;
        round++;
        if(round>=5){
            LandPriceChange();
            round=1;
        }
    }
}
int Dice(){
    int i=0;
    i=rand()%6+1;
    Sleep(100);
    printf("擲出了%d點",i);
    return i;
}
void Landservice(int money[5],int x[5],int round){
    char agree[2];
    MapJudge(x[round]);
    if(land[map_kind_order]==round){
        printf("此塊為您的土地，價值為：%d",land_price[map_kind_order]);
        Sleep(1000);
        printf("\n請問是否要賣出？(Y/N)：");
        agree[0]=' ';
        while(agree[0]!='y'&&agree[0]!='Y'&agree[0]!='n'&agree[0]!='N')
            scanf("%s",agree);
        if(agree[0]=='y'||agree[0]=='Y'){
            printf("賣出成功");
            Sleep(1000);
            land[map_kind_order]=0;
            money[round]+=land_price[map_kind_order];
            }
    }
    else if(land[map_kind_order]!=round&&land[map_kind_order]!=0){
        if(land[map_kind_order]==2){
            printf("此塊為");
            Set_TextColor(12);
            printf("凱撒");
            Set_TextColor(15);
            printf("的土地，價值為：%d",land_price[map_kind_order]);
        }
        if(land[map_kind_order]==3){
            printf("此塊為");
            Set_TextColor(6);
            printf("克雷格");
            Set_TextColor(15);
            printf("的土地，價值為：%d",land_price[map_kind_order]);
        }
        if(land[map_kind_order]==4){
            printf("此塊為");
            Set_TextColor(13);
            printf("莫伊拉");
            Set_TextColor(15);
            printf("的土地，價值為：%d",land_price[map_kind_order]);
        }
        Sleep(1000);
    }
    else if(land[map_kind_order]==0){
        printf("此塊為空地，價格為：%d\n",land_price[map_kind_order]);
        printf("請問是否要購買？(Y/N)：");
        agree[0]=' ';
        while(agree[0]!='y'&&agree[0]!='Y'&agree[0]!='n'&agree[0]!='N')
            scanf("%s",&agree);
        if(agree[0]=='y'||agree[0]=='Y'){
            if(money[round]>land_price[map_kind_order]){
                printf("購買成功");
                Sleep(1000);
                land[map_kind_order]=round;
                money[round]-=land_price[map_kind_order];
            }
            else
                printf("財產不足");
                Sleep(1000);
        }
    }
    return money;
}
void LandPriceChange(){
    int i,change[2];
    for(i=0;i<10;i++){
        change[0]=rand()%2;
        change[1]=rand()%11;
        if(change[0]==1)
            land_price[i]+=land_price[i]*change[1]/100;
        else
            land_price[i]-=land_price[i]*change[1]/100;
    }
}
void InvestmentGame(int money[5]){
    int stake=0,player[2]={0,0},makers[2]={0,0},win=0;
    char agree[2];
    if(service_use==0){
        PlaySe("audio/se/miss.wav");
        printf("目前不可使用服務");
        Sleep(1000);
        return money;
    }
    Dialouge("歡迎來到博奕場，這裡進行以自由決定賭金的小遊戲，規則如下：\n",30,1,15);
    Dialouge("首先輸入賭金，之後會各發一張1~13的牌給莊家與參與者，參與者看過兩邊的牌後，可自行決定要否放棄\n",30,1,15);
    Dialouge("之後會再各發一張牌，依據兩張牌加起來的數字比大小，較大者為贏家，可以獲取2倍賭金，否則失去賭金\n",30,1,15);
    Sleep(500);
    Dialouge("賭局開始，請輸入賭金：",40,1,15);
    scanf("%d",&stake);
    while(stake>money[1]||stake<=0){
        if(stake<=0)
            Dialouge("請勿亂輸入\n",40,1,15);
        else
            Dialouge("不可輸入大於財產之金額\n",40,1,15);
        Sleep(1000);
        scanf("%d",&stake);
    }
    player[0]=rand()%13+1;
    makers[0]=rand()%13+1;
    Set_TextColor(15);
    printf("你的牌為：%d莊家的牌為：%d，請問是否賭博？（Y/N）",player[0],makers[0]);
    scanf("%c",&agree);
    while(agree[0]!='y'&&agree[0]!='Y'&&agree[0]!='n'&&agree[0]!='N')
        scanf("%s",agree);
    if(agree[0]=='y'|agree[0]=='Y'){
        Sleep(1000);
        player[1]=rand()%13+1;
        makers[1]=rand()%6+4;
        if(player[0]-makers[0]>3)
            makers[1]=rand()%10+4;
        if(player[0]-makers[0]>8)
            makers[1]=rand()%8+6;
        if(player[0]-makers[0]>9)
            makers[1]=rand()%6+8;
        printf("你的牌為：%d、%d莊家的牌為：%d、%d\n",player[0],player[1],makers[0],makers[1]);
        if(player[0]+player[1]>makers[0]+makers[1]){
            PlaySe("audio/se/money.wav");
            printf("你贏了，獲取兩倍賭金");
            money[1]+=(2*stake);
            Sleep(3500);
        }
        else if(makers[0]+makers[1]>player[0]+player[1]){
            printf("你輸了，失去兩倍賭金");
            money[1]-=(2*stake);
            Sleep(2000);
        }
        else{
            printf("平局");
            Sleep(2000);
        }
    }
    service_use=0;
    return money;
}
void Bankrupt(int money[5],int round){
    // 破產判斷及抵押房產
    int i,j=0;
    while(money[round]<0&&j!=1){
        for(i=0;i<10;i++){
            if(land[i]==round&&money[round]<0){
                land[i]=0;
                Sleep(1000);
                printf("因負債強制抵押土地(%d)。\n",i+1);
                Sleep(1000);
                money[round]+=land_price[i];
                estate[round]-=land_price[i];
            }
        }
        if(money[round]<0){
            j=1;
            break;
        }
    }
    return money;
}
void DeepMarket(int money[5],int round,int moral[5],int x[5]){
    char agree[2];
    int jail_chance=0,profit=0,i,j,item[4]={0,0,0,0},event=0,event_chance=0,rank[4],temp,ai_use_chance=0;
    for(i=0;i<4;i++){
        item[i]=rand()%3;
        rank[i]=money[i+1];
    }
    // 財產排序
    for(i=1;i<4;i++){
        for(j=0;j<4-i;j++){
            if(rank[j]>rank[j+1]){
                temp=rank[j];
                rank[j]=rank[j+1];
                rank[j+1]=temp;
            }
        }
    }
    // 玩家操作
    if(round==1){
        if(service_use==0){
        PlaySe("audio/se/miss.wav");
        printf("目前不可使用服務");
        Sleep(1000);
        return money;
        }
        Dialouge("歡迎來到暗市，這裡這裡提供以下服務：\n",35,1,15);
        Dialouge("1.毒品買賣 2.物品買賣 3.人口販賣 4.殺手服務，請輸入欲使用服務之編號或(N)取消\n",35,1,15);
        Set_TextColor(15);
        scanf("%s",agree);
        while(agree[0]!='n'&&agree[0]!='N'&&(agree[0]<49||agree[0]>52))
            scanf("%s",agree);
        if(agree[0]=='n'||agree[0]=='N')
            return money;
        else if(agree[0]=='1'){
            agree[0]=' ';
            Dialouge("請選擇種類：1.搖頭丸xtc(84%) 2.Xanax 500Bars 3.Speed 20g 4.安非他命(Uncut MDMA Crystals)3.5g\n",20,1,15);
            Set_TextColor(15);
            while(agree[0]!='n'&&agree[0]!='N'&&(agree[0]<49||agree[0]>52))
                scanf("%s",agree);
            if(agree=='n'||agree=='N')
                return money;
            Set_TextColor(15);
            if(agree[0]=='1'){
                profit=rand()%4000+5000;
                money[round]+=profit;
                moral[round]+=rand()%6+3;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
                service_use=0;
            }
            if(agree[0]=='2'){
                profit=rand()%4000+9000;
                money[round]+=profit;
                moral[round]+=rand()%9+5;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
                service_use=0;
            }
            if(agree[0]=='3'){
                profit=rand()%2500+3000;
                money[round]+=profit;
                moral[round]+=rand()%6+1;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
                service_use=0;
            }
            if(agree[0]=='4'){
                profit=rand()%2500+1000;
                money[round]+=profit;
                moral[round]+=rand()%4+1;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
                service_use=0;
            }
            jail_chance=rand()%6;
        }
        else if(agree[0]=='2'){
            Set_TextColor(15);
            Sleep(1000);
            printf("目前市場庫存：I.複製品項鍊：%d  II.複製品戒指：%d  III.金條：%d  IV.金幣：%d\n",item[0],item[1],item[2],item[3]);
            agree[0]=' ';
            while((agree[0]!='n'&&agree[0]!='N')&&(agree[0]<49||agree[0]>52))
                scanf("%s",agree);
            if(agree[0]=='n'||agree[0]=='N')
                return money;
            if(agree[0]=='1'&&item[agree[0]-'0'-1]!=0){
                profit=(agree[0]-'0')*(rand()%400+1600);
                money[round]+=profit;
                Sleep(1000);
                printf("假賣複製品項鍊，獲取利潤：%d\n",profit);
                jail_chance=item[0]*(rand()%20+10);
                service_use=0;
            }
            if(agree[0]=='2'&&item[agree[0]-'0'-1]!=0){
                profit=(agree[0]-'0')*(rand()%200+1200);
                money[round]+=profit;
                Sleep(1000);
                printf("假賣複製品戒指，獲取利潤%d\n",profit);
                jail_chance=item[1]*(rand()%16+10);
                service_use=0;
            }
            if(agree[0]=='3'&&item[agree[0]-'0'-1]!=0){
                profit=(agree[0]-'0')*rand()%2500+2000;
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣金條，獲取利潤：%d\n",profit);
                jail_chance=item[2]*(rand()%50+10);
                service_use=0;
            }
            if(agree[0]=='4'&&item[agree[0]-'0'-1]!=0){
                profit=(agree[0]-'0')*(rand()%500+3000);
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣金幣，獲取利潤：%d\n",profit);
                jail_chance=item[3]*(rand()%50+10);
                service_use=0;
            }
            moral[round]+=(item[agree[0]-'0'-1])*(rand()%5+1);
        }
        else if(agree[0]=='3'){
            Dialouge("請選擇種類：1.偷取幼兒轉賣認養者 2.暴力搶奪獲得贊助費 3.販運勞工 4.器官買賣 \n",30,1,15);
            agree[0]=' ';
            Set_TextColor(15);
            while(agree[0]!='n'&&agree[0]!='N'&&(agree[0]<49||agree[0]>52))
                scanf("%s",agree);
            Set_TextColor(15);
            if(agree[0]=='n'||agree[0]=='N')
                return money;
            if(agree[0]=='1'){
                Sleep(1000);
                profit=rand()%6000+4000;
                money[round]+=profit;
                printf("透過轉賣幼兒，獲取利潤：%d\n",profit);
                moral[round]+=rand()%85+15;
                jail_chance=rand()%70+30;
                service_use=0;
            }
            if(agree[0]=='2'){
                event_chance=rand()%100+1;
                if(event_chance>5){
                    event=rand()%3;
                    if(event==0){
                        Sleep(1000);
                        Dialouge("因暴力搶奪，與其母親發生衝突，是否殺死她？(Y/N)",45,1,15);
                        agree[0]=' ';
                        Set_TextColor(15);
                        while(agree[0]!='n'&&agree[0]!='N'&&agree[0]!='y'&&agree[0]!='Y')
                            scanf("%s",agree);
                        if(agree[0]=='Y'||agree[0]=='y'){
                            Sleep(1000);
                            Dialouge("殺死了那位女性，她嘴裡呢喃著”還給我”，聲帶已經枯竭，撐大的眼還流著淚，頸部已被劃開\n",45,1,12);
                            jail_chance=rand()%60+40;
                            moral[round]+=20;
                            service_use=0;
                        }
                        else{
                            Sleep(1000);
                            Dialouge("她報警了，你被判下死刑。",45,1,15);
                            dead[1]=1;
                        }
                    }
                    if(event==1){
                        Dialouge("因暴力搶奪，與其父母發生衝突，是否殺死男人？(Y/N)",45,1,15);
                        agree[0]=' ';
                        Set_TextColor(15);
                        while(agree[0]!='n'&&agree[0]!='N'&&agree[0]!='y'&&agree[0]!='Y')
                            scanf("%s",agree);
                        if(agree[0]=='y'||agree[0]=='Y'){
                            Dialouge("殺死了男人，那女人憎恨的看著你，卻死守著小孩不放，是否殺死她？(Y/N)",45,1,12);
                            moral[round]+=20;
                            agree[0]=' ';
                            Set_TextColor(15);
                            while(agree[0]!='n'&&agree[0]!='N'&&agree[0]!='y'&&agree[0]!='Y')
                            scanf("%s",agree);
                            if(agree[0]=='Y'||agree[0]=='y'){
                                Dialouge("殺死了那位女性，她嘴裡呢喃著",45,1,12);
                                Dialouge("”殺了你”",300,1,12);
                                Dialouge("，聲帶已經枯竭，撐大的眼還流著淚，頸部已被劃開\n",45,1,12);
                                jail_chance=rand()%50+50;
                                moral[round]+=20;
                                service_use=0;
                            }
                            else{
                                Sleep(1000);
                                Dialouge("她抓狂的用利器把你的腦袋打爛，你被她挖開腦子，死掉了。",45,1,15);
                                dead[1]=1;
                            }
                        }
                        else{
                            Sleep(1000);
                            Set_TextColor(15);
                            printf("那個男人憤怒地向你攻擊，殺死了你");
                            dead[1]=1;
                        }

                    }
                    if(event==2){
                        Dialouge("因暴力搶奪，與其兄弟姊妹發生了衝突，是否殺死他們？(Y/N)",45,1,15);
                        agree[0]=' ';
                        Set_TextColor(15);
                        while(agree[0]!='n'&&agree[0]!='N'&&agree[0]!='y'&&agree[0]!='Y')
                            scanf("%s",agree);
                        if(agree[0]=='Y'||agree[0]=='y'){
                            Dialouge("殺死了其他所有小孩，遍地的血跡與斷肢、腸子、腦漿、肉塊。\n",45,1,12);
                            jail_chance=rand()%60+40;
                            moral[round]+=30;
                            Set_TextColor(15);
                            service_use=0;
                        }
                        else{
                            Sleep(1000);
                            printf("他們報警了，你被判下死刑。");
                            dead[1]=1;
                        }
                    }
                }
                profit=rand()%30000+30000;
                money[round]+=profit;
                Sleep(1000);
                Set_TextColor(15);
                printf("獲得利潤：%d\n",profit);
                moral[round]+=rand()%50;
                service_use=0;
            }
            if(agree[0]=='3'){
                profit=rand()%10000+10000;
                money[round]+=profit;
                Sleep(1000);
                printf("販運勞工，獲取利潤：%d\n",profit);
                jail_chance=rand()%80+20;
                moral[round]+=rand()%25+10;
                service_use=0;
            }
            if(agree[0]=='4'){
                profit=rand()%20000+10000;
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣人體器官，獲取利潤：%d\n",profit);
                jail_chance=rand()%70+30;
                moral[round]+=rand()%35+10;
                service_use=0;
            }
        }
        else if(agree[0]=='4'){
            Dialouge("請輸入想殺掉的對象，（編號2.3.4，財富最高位者不可殺、需要支付100000元）（或N取消）：\n",30,1,15);
            agree[0]=' ';
            Set_TextColor(15);
            while((agree[0]<50||agree[0]>52)&&(agree[0]!='n'&agree[0]!='N'))
                scanf("%s",agree);
            if(money[agree[0]-'0']!=rank[3]){
                if(money[round]<100000){
                    Set_TextColor(15);
                    Sleep(1000);
                    printf("財產不足\n");
                    Sleep(1000);
                }
                else if (money[round]>=100000&&dead[agree[0]-'0']==1){
                    Set_TextColor(15);
                    Sleep(1000);
                    printf("指定對象已經死亡\n");
                    Sleep(1000);
                }
                else{
                    money[round]-=100000;
                    moral[round]+=10;
                    Sleep(1000);
                    printf("已殺死指定之對象，收取金額：100000\n");
                    stop[agree[0]-'0']=100;
                    service_use=0;
                }
            }
        }
    }
    if(round==2||round==3||round==4){
        ai_use_chance=rand()%100+1;
        if(money[round]>120000){
            if(ai_use_chance>=50){
                event=rand()%4+1;
                while(event==round||event==rank[3]||dead[event]==1)
                    event=rand()%4+1;
                if(event!=round&&rank[event-1]!=rank[3]&&dead[event]!=1){
                    Sleep(1000);
                    printf("雇傭殺手殺死了...\n");
                    money[round]-=100000;
                    moral[round]+=10;
                    stop[event]=100;
                    Sleep(1000);
                    return money;
                }
            }
        }
    else if(ai_use_chance>50){
            event=rand()%4+1;
            if(event==1){
                Sleep(1000);
                profit=rand()%6000+4000;
                money[round]+=profit;
                printf("透過轉賣幼兒，獲取利潤：%d\n",profit);
                moral[round]+=rand()%85+15;
                jail_chance=rand()%70+30;
            }
            if(event==2){
                profit=rand()%10000+10000;
                money[round]+=profit;
                Sleep(1000);
                printf("販運勞工，獲取利潤：%d\n",profit);
                jail_chance=rand()%80+20;
                moral[round]+=rand()%25+10;
            }
            if(event==3){
                profit=rand()%20000+10000;
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣人體器官，獲取利潤：%d\n",profit);
                jail_chance=rand()%70+30;
                moral[round]+=rand()%35+10;
            }
            if(event==4){
                event_chance=rand()%4;
                event=rand()%3;
                if(event_chance==0){
                    Sleep(1000);
                    printf("因暴力搶奪，殺害一位女性\n");
                    Sleep(1000);
                    jail_chance=rand()%60+40;
                    moral[round]+=20;
                }
                if(event_chance==1){
                    Dialouge("因暴力搶奪，殺害一對夫婦\n");
                    jail_chance=rand()%50+50;
                    moral[round]+=20;
                }
                if(event_chance==2){
                    Sleep(1000);
                    Dialouge("因暴力搶奪，殺害一群小孩\n");
                    jail_chance=rand()%60+40;
                    moral[round]+=30;
                    }
                profit=rand()%30000+30000;
                money[round]+=profit;
                Sleep(1000);
                Set_TextColor(15);
                printf("暴力搶奪，獲得利潤：%d\n",profit);
                moral[round]+=rand()%50;
            }
        }
        else if(ai_use_chance>25){
            event=rand()%4+1;
            if(event==1&&item[event-1]!=0){
                profit=item[event-1]*(rand()%400+1600);
                money[round]+=profit;
                Sleep(1000);
                printf("假賣複製品項鍊，獲取利潤：%d\n",profit);
                jail_chance=item[0]*(rand()%20+10);
            }
            if(event==2&&item[event-1]!=0){
                profit=item[event-1]*(rand()%200+1200);
                money[round]+=profit;
                Sleep(1000);
                printf("假賣複製品戒指，獲取利潤%d\n",profit);
                jail_chance=item[1]*(rand()%16+10);
            }
            if(event==3&&item[event-1]!=0){
                profit=item[event-1]*rand()%2500+2000;
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣金條，獲取利潤：%d\n",profit);
                jail_chance=item[2]*(rand()%50+10);
            }
            if(event==4&&item[event-1]!=0){
                profit=item[event-1]*(rand()%500+3000);
                money[round]+=profit;
                Sleep(1000);
                printf("盜賣金幣，獲取利潤：%d\n",profit);
                jail_chance=item[3]*(rand()%50+10);
            }
            moral[round]+=(item[event-1])*(rand()%5+1);
        }
        else if(ai_use_chance>=0){
            Sleep(1000);
            event=rand()%4+1;
            printf("進行毒品買賣，");
            if(event==1){
                profit=rand()%4000+5000;
                money[round]+=profit;
                moral[round]+=rand()%6+3;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
            }
            if(event==2){
                profit=rand()%3000+6000;
                money[round]+=profit;
                moral[round]+=rand()%9+5;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
            }
            if(event==3){
                profit=rand()%2500+3000;
                money[round]+=profit;
                moral[round]+=rand()%6+1;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
            }
            if(event==4){
                profit=rand()%2500+1000;
                money[round]+=profit;
                moral[round]+=rand()%4+1;
                Sleep(1000);
                printf("獲取利潤：%d\n",profit);
            }
            jail_chance=rand()%6;
        }
    }
    temp=rand()%101;
    if(temp<jail_chance){
        Sleep(1000);
        printf("犯罪被偵查，遭到逮捕，停留監獄5個回合。\n");
        stop[round]=5;
        x[round]=10;
    }
    Sleep(1000);
    return money;
}
void Opportunity(int money[5],int x[5],int round){
    int event=0,input=0,event_chance=0,i,go;
    event=rand()%8+1;
    if(event==1){
        event_chance=rand()%4000+1;
        Sleep(1000);
        printf("\n在路上搶劫別人，獲得%d。",event_chance);
        money[round]+=event_chance;
        Sleep(1000);
        return money;
    }
    if(event==2){
        Sleep(1000);
        printf("\n沒事發生");
        Sleep(1000);
        return money;
    }
    if(event==3){
        Sleep(1000);
        if(round==1){
            printf("\n獲得可直達想去的地方的機會，請輸入（格數）：");
            scanf("%d",&input);
            while(input<1||input>28)
                scanf("%d",&input);
            x[1]=input-1;
            Sleep(1000);
            return money;
        }
        if(round!=1){
            printf("\n獲得可直達想去的地方的機會");
            event_chance=rand()%6+1;
            if(event_chance==1)
                x[round]=3;
            if(event_chance==2)
                x[round]=14;
            if(event_chance==3)
                x[round]=16;
            if(event_chance>=4)
                x[round]=27;
            if(event_chance>5){
                event_chance=rand()%28;
                x[round]=event_chance;
            }
            Sleep(1000);
        }
        return money;
    }
    if(event==4){
        int n=0;
        for(i=0;i<10;i++){
            event_chance=rand()%2000+1;
            if(land[i]==round){
                n++;
                Sleep(1000);
                printf("\n所擁有土地(%d)價值上升%d",i+1,event_chance);
                Sleep(1000);
                land_price[i]+=event_chance;
            }
        }
        if(n==0){
            Sleep(1000);
            printf("\n沒事發生");
            Sleep(1000);
        }
        return money;
    }
    if(event==5){
        event_chance=rand()%2000+1;
        Sleep(1000);
        printf("\n在路上撿到錢，獲得：%d",event_chance);
        Sleep(1000);
        money[round]+=event_chance;
        return money;
    }
    if(event==6){
        event_chance=rand()%3000;
        Sleep(1000);
        printf("\n偷別人的錢，獲得：%d",event_chance);
        Sleep(1000);
        money[round]+=event_chance;
        return money;
    }
    if(event==7){
        event_chance=rand()%3000;
        Sleep(1000);
        printf("\n在路上被流氓打，獲得賠償：%d，得住院2回合",event_chance);
        Sleep(1000);
        stop[round]=2;
        x[round]=2Opportunity4;
        money[round]+=event_chance;
        return money;
    }
    if(event==8){
        Sleep(1000);
        printf("\n不甚得得到感冒，花錢看醫生，失去:500");
        Sleep(1000);
        money[round]-=500;
    }
}
void Fate(int money[5],int x[5],int round){
    int event=0,input=0,event_chance=0,i;
    event=rand()%8+1;
    if(event==1){
        event_chance=rand()%8000+1;
        Sleep(1000);
        printf("\n在路上被別人搶劫，失去%d。",event_chance);
        money[round]-=event_chance;
        Sleep(1000);
        return money;
    }
    if(event==2){
        Sleep(1000);
        printf("\n沒事發生");
        Sleep(1000);
        return money;
    }
    if(event==3){
        event_chance=rand()%6+1;
        Sleep(1000);
        printf("\n倒退%d格",event_chance);
        x[round]-=event_chance;
        Sleep(1000);
        return money;
    }
    if(event==4){
        int n=0;
        for(i=0;i<10;i++){
            event_chance=rand()%3000+1;
            if(land[i]==round){
                n++;
                Sleep(1000);
                printf("\n所擁有土地(%d)貶值%d",i+1,event_chance);
                Sleep(1000);
                land_price[i]-=event_chance;
            }
        }
        if(n==0){
            Sleep(1000);
            printf("\n沒事發生");
            Sleep(1000);
        }
        return money;
    }
    if(event==5){
        event_chance=rand()%4000+1;
        Sleep(1000);
        printf("\n不小心掉了錢包，失去：%d",event_chance);
        Sleep(1000);
        money[round]-=event_chance;
        return money;
    }
    if(event==6){
        event_chance=rand()%6000;
        Sleep(1000);
        printf("\n錢包被扒手偷走，失去：%d",event_chance);
        Sleep(1000);
        money[round]-=event_chance;
        return money;
    }
    if(event==7){
        event_chance=rand()%3000;
        Sleep(1000);
        printf("\n在路上跟人發生衝突，得賠錢：%d，得進監獄3回合",event_chance);
        Sleep(1000);
        stop[round]=3;
        x[round]=10;
        money[round]-=event_chance;
        return money;
    }
    if(event==8){
        event_chance=rand()%4000+2000;
        Sleep(1000);
        printf("\n被盜刷信用卡，失去:%d",event_chance);
        money[round]-=event_chance;
        Sleep(1000);
        return money;
    }
}
void PlayBgm(char file[100]){
    // 使用方法：PlayBgm("檔案"); 變數bgm_play為是否播放bgm之判斷
    if(bgm_play==1)
        PlaySound(file,NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
    strcpy(temp_bgm,file);
}
void PlaySe(char *file[]){
    // 使用方法：PlaySe("檔案"); 變數se_play為是否播放se之判斷
    if(se_play==1){
        int i;
        char play[100]="play ",stop[100]="stop ";
        for(i=0;i<strlen(file);i++)
            temp[i]=file[i];
        strcat(stop,temp);
        mciSendString(stop,0, 0, 0);
        strcat(play,file);
        mciSendString(play,0, 0, 0);
    }
}
int Dialouge(char text[],int speed,int skip,int color){
    // 使用方式：Dialouge("文字內容",每個字等待秒數);
    //顯示文字
    Set_TextColor(color);
    int i;
    for(i=0;i<strlen(text);i++){
        printf("%c",text[i]);
        Sleep(speed);
    }
    // 自動恢復預設顏色
    Set_TextColor(7);
    while(skip==0){
        // 清空緩存
        int k;
        while (1) {
        if (kbhit()){
        k=getch();
        if (0==k || 0xE0==k)k=k<<8|getch();
        }
        else
            break;
        }
        // 判斷是否按下確認鍵
        if(i==13||i==32)
            break;
        else{
            i=Keyboard_Pressed();
        }
    }
}
void MapJudge(int x){
    x++;
    if(x==1)
        map_kind=1;
    else if(x==3|x==5|x==7|x==10|x==13|x==18|x==20|x==22|x==24|x==27){
        x--;
        map_kind=2;
        if(x==2)
            map_kind_order=1;
        if(x==4)
            map_kind_order=2;
        if(x==6)
            map_kind_order=3;
        if(x==9)
            map_kind_order=4;
        if(x==12)
            map_kind_order=5;
        if(x==17)
            map_kind_order=6;
        if(x==19)
            map_kind_order=7;
        if(x==21)
            map_kind_order=8;
        if(x==23)
            map_kind_order=9;
        if(x==26)
            map_kind_order=10;
            map_kind_order--;
    }
    else if(x==2|x==8|x==14|x==21)
        map_kind=3;
    else if(x==9|x==12|x==16|x==26)
        map_kind=4;
    else if(x==19|x==6|x==23)
        map_kind=5;
    else if(x==4|x==17)
        map_kind=6;
    else if(x==15|x==28)
        map_kind=7;
    else if(x==11)
        map_kind=8;
    else if(x==25)
        map_kind=9;
    return 0;
}
void Title_Draw(){
    int i;
    printf("\n");
    Set_TextColor(12);
    printf("　　　　　　　　　　　■　　　　　　　　　　　■　　　　　　　　　　　■　■\n");
    printf("　　　　　　　　　　　■　　　　　　　■■■■■■■■■　　　　　　■　　　■\n");
    printf("　　　　　　　　　　　■　　　　　　　■　　　　　　　■　　　　　■　■　　　■\n");
    printf("　　　　　　■■■■■■■■■■■　　■　■■■■■　■　　　　■　■　　■　　■\n");
    printf("　　　　　　　　　　 ■■　　　 　　　■　　　　　　　■　　　    ■■■■■■　　■\n");
    Set_TextColor(14);
    printf("　　　　　　　　　  ■  ■　　　　　　　　■■■■■　　　　　　　　\n");
    printf("　　　　　　　　　 ■　  ■　　　　       ■　　　■　　　　　　■■■■　■■■■\n");
    printf("　　　　　　　　  ■　　　■　　  　      ■　　　■　　　　 　   ■　■　　■　■\n");
    printf("　　　　　　　　 ■　　　　■　    　     ■■■■■　　　　　      ■■　　　■■\n");
    Set_TextColor(10);
    printf("　　　　　　　  ■　　　　　■　　 　   　　　　　　　    　　　  ■　■　　■　■\n");
    printf("　　　　　　　 ■　　　　　　■  　     ■■■■■■■　　　　　■　　■　■　　■\n");
    printf("　　　　　　　■　　　　　　　■　　　  ■　　■　　■　　　　    　■■　　　■■\n");
    printf("　　　　　   ■                ■   　  ■■■■■■■　　　　　　　　\n");
    printf("　　　　　                          　　■　　■　　■　　　　　　　　\n");
    printf("　　　　　                         　   ■■■■■■■　　　　　　　　\n");
    Set_TextColor(12);
    printf("\n\n　　　　　　　　　　　　　　　　　 ");
    for(i=0;i<4;i++)
        printf("\n");;
}
void DrawMap(int position[5]){
    Clr();
    int i,j,character_color,map_grid[28];
        // 房產計算
    for(i=0;i<5;i++){
        estate[i]=0;
        for(j=0;j<10;j++){
            if(land[j]==i)
                estate[i]+=land_price[j];
        }
    }
    //繪製地圖
    for(i=0;i<28;i++)
        map_grid[i]=0;
    for(i=0;i<5;i++){
        map_grid[position[i]]=i;
    }
    printf("\n");
    // 繪製第一層
    Set_TextColor(7);
    printf("　　　　　　 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("　　　　　　 ");
    for(i=0;i<11;i++){
        printf("■");
        if(map_grid[i]!=0){
        if(map_grid[i]==1)
            Set_TextColor(11);
        else if(map_grid[i]==2)
            Set_TextColor(12);
        else if(map_grid[i]==3)
            Set_TextColor(6);
        else if(map_grid[i]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        }
        else
            printf("　");
        if(i<9)
            printf(" %d",i+1);
        else
            printf("%d",i+1);
    }
    // 1~11格
    printf("■\n");
    printf("　　　　　　 ■");
    Set_TextColor(15);
    printf("起點");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(14);
    printf("機會");
    Set_TextColor(7);
    printf("■");
    if(land[0]==1)
        Set_TextColor(11);
    else if(land[0]==2)
        Set_TextColor(12);
    else if(land[0]==3)
        Set_TextColor(6);
    else if(land[0]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(12);
    printf("博奕");
    Set_TextColor(7);
    printf("■");
    if(land[1]==1)
        Set_TextColor(11);
    else if(land[1]==2)
        Set_TextColor(12);
    else if(land[1]==3)
        Set_TextColor(6);
    else if(land[1]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    printf("休憩");
    Set_TextColor(7);
    printf("■");
    if(land[2]==1)
        Set_TextColor(11);
    else if(land[2]==2)
        Set_TextColor(12);
    else if(land[2]==3)
        Set_TextColor(6);
    else if(land[2]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(14);
    printf("機會");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(10);
    printf("命運");
    Set_TextColor(7);
    printf("■");
    if(land[3]==1)
        Set_TextColor(11);
    else if(land[3]==2)
        Set_TextColor(12);
    else if(land[3]==3)
        Set_TextColor(6);
    else if(land[3]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(8);
    printf("監獄");
    Set_TextColor(7);
    printf("■\n");
    printf("　　　　　　 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■　　\n");
    // 繪製第二層
    printf("　　　　　　 ");
    printf("■");
    if(map_grid[27]!=0){
        if(map_grid[27]==1)
            Set_TextColor(11);
        else if(map_grid[27]==2)
            Set_TextColor(12);
        else if(map_grid[27]==3)
            Set_TextColor(6);
        else if(map_grid[27]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("28");
    }
    else
        printf("　28");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　");
    printf("■");
    if(map_grid[11]!=0){
        if(map_grid[11]==1)
            Set_TextColor(11);
        else if(map_grid[11]==2)
            Set_TextColor(12);
        else if(map_grid[11]==3)
            Set_TextColor(6);
        else if(map_grid[11]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("12");
    }
    else
        printf("　12");
    printf("■\n");
    // 28 12
    printf("　　　　　　 ■");
    Set_TextColor(4);
    printf("暗市");
    Set_TextColor(7);
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　■");
    Set_TextColor(10);
    printf("命運");
    Set_TextColor(7);
    printf("■\n");
    printf("　　　　　　 ■■■■　　　　　　　　　　　　　　　　　　　　　　　　　　■■■■\n");
    // 繪製第三層
    printf("　　　　　　 ");
    printf("■");
    if(map_grid[26]!=0){
        if(map_grid[26]==1)
            Set_TextColor(11);
        else if(map_grid[26]==2)
            Set_TextColor(12);
        else if(map_grid[26]==3)
            Set_TextColor(6);
        else if(map_grid[26]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("27");
    }
    else
        printf("　27");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　");
    printf("■");
    if(map_grid[12]!=0){
        if(map_grid[12]==1)
            Set_TextColor(11);
        else if(map_grid[12]==2)
            Set_TextColor(12);
        else if(map_grid[12]==3)
            Set_TextColor(6);
        else if(map_grid[12]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("13");
    }
    else
        printf("　13");
    printf("■\n");
    // 27 13
    printf("　　　　　　 ■");
    if(land[9]==1)
        Set_TextColor(11);
    else if(land[9]==2)
        Set_TextColor(12);
    else if(land[9]==3)
        Set_TextColor(6);
    else if(land[9]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　■");
    if(land[4]==1)
        Set_TextColor(11);
    else if(land[4]==2)
        Set_TextColor(12);
    else if(land[4]==3)
        Set_TextColor(6);
    else if(land[4]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■\n");
    printf("　　　　　　 ■■■■　　　　　　　　　　　　　　　　　　　　　　　　　　■■■■\n");
    // 繪製第四層
    printf("　　　　　　 ");
    printf("■");
    if(map_grid[25]!=0){
        if(map_grid[25]==1)
            Set_TextColor(11);
        else if(map_grid[25]==2)
            Set_TextColor(12);
        else if(map_grid[25]==3)
            Set_TextColor(6);
        else if(map_grid[25]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("26");
    }
    else
        printf("　26");
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　");
    printf("■");
    if(map_grid[13]!=0){
        if(map_grid[13]==1)
            Set_TextColor(11);
        else if(map_grid[13]==2)
            Set_TextColor(12);
        else if(map_grid[13]==3)
            Set_TextColor(6);
        else if(map_grid[13]==4)
            Set_TextColor(13);
        printf("◆");
        Set_TextColor(7);
        printf("14");
    }
    else
        printf("　14");
    // 26 14
    printf("■\n　　　　　　 ■");
    Set_TextColor(10);
    printf("命運");
    Set_TextColor(7);
    printf("■　　　　　　　　　　　　　　　　　　　　　　　　　　■");
    Set_TextColor(14);
    printf("機會");
    Set_TextColor(7);
    printf("■\n");
    printf("　　　　　　 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    // 繪製最底層
    printf("　　　　　　 ");
    for(i=24;i>13;i--){
        printf("■");
        if(map_grid[i]!=0){
            if(map_grid[i]==1)
                Set_TextColor(11);
            else if(map_grid[i]==2)
                Set_TextColor(12);
            else if(map_grid[i]==3)
                Set_TextColor(6);
            else if(map_grid[i]==4)
                Set_TextColor(13);
            printf("◆");
            Set_TextColor(7);
            printf("%d",i+1);
        }
        else
            printf("　%d",i+1);
    }
    printf("■\n");
    printf("　　　　　　 ■");
    Set_TextColor(7);
    printf("醫院");
    Set_TextColor(7);
    printf("■");
    if(land[8]==1)
        Set_TextColor(11);
    else if(land[8]==2)
        Set_TextColor(12);
    else if(land[8]==3)
        Set_TextColor(6);
    else if(land[8]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(7);
    printf("休憩");
    Set_TextColor(7);
    printf("■");
    if(land[7]==1)
        Set_TextColor(11);
    else if(land[7]==2)
        Set_TextColor(12);
    else if(land[7]==3)
        Set_TextColor(6);
    else if(land[7]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(14);
    printf("機會");
    Set_TextColor(7);
    printf("■");
    if(land[6]==1)
        Set_TextColor(11);
    else if(land[6]==2)
        Set_TextColor(12);
    else if(land[6]==3)
        Set_TextColor(6);
    else if(land[6]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(7);
    printf("休憩");
    Set_TextColor(7);
    printf("■");
    if(land[5]==1)
        Set_TextColor(11);
    else if(land[5]==2)
        Set_TextColor(12);
    else if(land[5]==3)
        Set_TextColor(6);
    else if(land[5]==4)
        Set_TextColor(13);
    else
        Set_TextColor(15);
    printf("土地");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(12);
    printf("博奕");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(10);
    printf("命運");
    Set_TextColor(7);
    printf("■");
    Set_TextColor(4);
    printf("暗市");
    Set_TextColor(7);
    printf("■\n");
    printf("　　　　　　 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■　　\n");
    Set_TextColor(7);
    printf("﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍﹍\n");
}
void DrawGameScreen_Player(int x[5],int Skill[2],int money[5],int moral[5],int round){
    int key_pressed=0,select=1,i;
    char *dice="〈投擲骰子〉",*skill="　使用技能　",*service="　使用服務　",*option="　系統設定　",*title="　返回標題　",agree[2];
    // 判斷當前所在地圖類型 1=起點 2=空地 3=機會 4=命運 5=休憩 6=博奕 7=暗市 8=監獄 9=醫院
    if(money>=0&&stop[1]==0)
        PlaySe("audio/se/bell.wav");
    while(1&&dead[round]!=1){
        MapJudge(x[round]);
        if(return_title==1)
            return;
        Sleep(50);
        DrawMap(x);
        // 操作畫面繪製
        if(select==1)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("　　　%s　|　",dice);
        if(select==2)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s　|　",skill);
        if(select==3)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s　|　",service);
        if(select==4)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s　|　",option);
        if(select==5)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("%s|　　 \n",title);
        Set_TextColor(7);
        printf("﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉");
        // 人物訊息繪製
        Set_TextColor(11);
        printf("◆格倫　");
        Set_TextColor(15);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[1]+1,money[1],estate[1],moral[1]);
        if(dead[1]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(12);
        printf("◆凱撒　");
        Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[2]+1,money[2],estate[2],moral[2]);
        if(dead[2]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(6);
        printf("◆克雷格");
        Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[3]+1,money[3],estate[3],moral[3]);
        if(dead[3]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(13);
        printf("◆莫伊拉");
        Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[4]+1,money[4],estate[4],moral[4]);
        if(dead[4]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(15);
        printf("當前輪到你的回合，請進行動作：\n");
        // 死亡判斷
        if(stop[round]==100){
            Sleep(1000);
            Dialouge("...已經死亡，無法進行任何動作，土地歸還",100,1,12);
            for(i=0;i<10;i++){
                    if(land[i]==round){
                        land[i]=0;
                        estate[round]-=land_price[i];
                    }
            }
            dead[round]=1;
            Set_TextColor(15);
            money[round]=-500;
            break;
        }
        // 判斷能否動作
        if(stop[round]>0){
            Sleep(1000);
            printf("目前無法移動，還有%d回合",stop[round]);
            stop[round]--;
            Sleep(1000);
            break;
        }
        Bankrupt(money,round);
        if(money[round]<0){
            Sleep(1000);
            printf("已經破產，無法進行動作");
            Sleep(1000);
            break;
        }
        // 清空緩存
        int k;
        while (1) {
            if (kbhit()){
                k=getch();
                if (0==k || 0xE0==k)k=k<<8|getch();
            }
            else
                break;
        }
        key_pressed=Keyboard_Pressed();
        while(key_pressed!=75&&key_pressed!=77&&key_pressed!=13){
            key_pressed=Keyboard_Pressed();
        }
        if(key_pressed==75){
            PlaySe("audio/se/select.wav");
            select--;
        }
        if(key_pressed==77){
            PlaySe("audio/se/select.wav");
            select++;
        }
        if(select>5)
            select=1;
        if(select<1)
            select=5;
        if(select==1){
            dice="〈投擲骰子〉";
            skill="　使用技能　";
            service="　使用服務　";
            option="　系統設定　";
            title="　返回標題　";
        }
        if(select==2){
            dice="　投擲骰子　";
            skill="〈使用技能〉";
            service="　使用服務　";
            option="　系統設定　";
            title="　返回標題　";
        }
        if(select==3){
            dice="　投擲骰子　";
            skill="　使用技能　";
            service="〈使用服務〉";
            option="　系統設定　";
            title="　返回標題　";
        }
        if(select==4){
            dice="　投擲骰子　";
            skill="　使用技能　";
            service="　使用服務　";
            option="〈系統設定〉";
            title="　返回標題　";
        }
        if(select==5){
            dice="　投擲骰子　";
            skill="　使用技能　";
            service="　使用服務　";
            option="　系統設定　";
            title="〈返回標題〉";
        }
        // 擲骰子前進 及遭遇事件
        if(select==1&&key_pressed==13){
            PlaySe("audio/se/decide.wav");
            x[1]+=Dice();
            if(x[1]>27)
                x[1]-=28;
            Sleep(1000);
            MapJudge(x[round]);
            if(map_kind==2&&land[map_kind_order]!=0&&land[map_kind_order]!=1){
                printf("\n經過土地，被收取租金：%d元",land_price[map_kind_order]/5);
                money[1]-=land_price[map_kind_order]/5;
                money[land[map_kind_order]]+=land_price[map_kind_order]/5;
            }
            if(map_kind==3)
                Opportunity(money,x,round);
            if(map_kind==4)
                Fate(money,x,round);
            printf("\n回合結束");
            Sleep(2000);
            return x;
        }
        // 使用技能
        if(select==2&&key_pressed==13){
            if(Skill[1]==1){
                printf("技能為：");
                if(Skill[0]==1){
                    printf("交換位置，請輸入欲與其交換位置的角色編號（2,3,4）或輸入N取消動作\n");
                    agree[0]=' ';
                    while((agree[0]<50||agree[0]>52)&&agree[0]!='n'&agree[0]!='N')
                        scanf("%s",agree);
                    if(agree[0]<=52&&agree[0]>=50){
                        int temp;
                        temp=x[round];
                        x[round]=x[agree[0]-'0'];
                        x[agree[0]-'0']=temp;
                        printf("已交換位置");
                        Sleep(1000);
                        Skill[1]=0;
                    }
                }
                if(Skill[0]==2){
                    printf("指定停止3回合，請輸入欲停止其行動的角色編號（2,3,4）或輸入N取消動作\n");
                    agree[0]=' ';
                    while((agree[0]<50||agree[0]>52)&&agree[0]!='n'&agree[0]!='N')
                        scanf("%s",agree);
                    if(agree[0]<=52&&agree[0]>=50){
                        stop[agree[0]-'0']+=3;
                        printf("已停止其行動3回合");
                        Sleep(1000);
                        Skill[1]=0;
                    }
                }
                if(Skill[0]==4||Skill[0]==3){
                    printf("前進指定步數(1~6)，請輸入欲前進之步數或輸入N取消動作\n");
                    agree[0]=' ';
                    while((agree[0]<49||agree[0]>54)&&agree[0]!='n'&agree[0]!='N')
                        scanf("%s",agree);
                    if(agree[0]<=54&&agree[0]>=49){
                        x[round]+=agree[0]-'0';
                        printf("已前進%d步",agree[0]-'0');
                        Skill[1]=0;
                        Sleep(1000);
                    }
                }
            }
            else{
                PlaySe("audio/se/miss.wav");
                printf("已使用過技能");
                Sleep(1000);
            }
        }
        // 使用該地之服務
        if(select==3&&key_pressed==13){
            if(map_kind==1|map_kind==3|map_kind==4|map_kind==5|map_kind==8|map_kind==9){
                PlaySe("audio/se/miss.wav");
                printf("此處無可用之服務");
                Sleep(1000);
            }
            if(map_kind==2){
                PlaySe("audio/se/decide.wav");
                Landservice(money,x,round);
            }
            if(map_kind==6){
                if(service_use==1)
                    PlaySe("audio/se/decide.wav");
                InvestmentGame(money);
            }
            if(map_kind==7){
                if(service_use==1)
                    PlaySe("audio/se/decide.wav");
                DeepMarket(money,round,moral,x);
            }
        }
        // 系統設定
        if(select==4&&key_pressed==13){
                PlaySe("audio/se/decide.wav");
                Option();
        }
        // 返回標題
        if(select==5&&key_pressed==13){
                PlaySe("audio/se/decide.wav");
                printf("確定是否返回標題(Y/N)");
                scanf("%s",agree);
                while(agree[0]!='y'&&agree[0]!='Y'&&agree[0]!='n'&&agree[0]!='N')
                    scanf("%s",agree);
                if(agree[0]=='y'||agree[0]=='Y'){
                    Sleep(1000);
                    return_title=1;
                }
            }
        Set_TextColor(7);
    }
}
void DrawGameScreen_Ai(int x[5],int money[5],int moral[5],int round){
    int event_chance=0,makers[2],ai[2],i;
    MapJudge(x[round]);
    while(1&&dead[round]==0){
        Sleep(50);
        int Skill[5]={0,0,0,0,0,0};
        DrawMap(x);
        printf("\n");
        printf("﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉﹉");
        // 人物訊息繪製
        Set_TextColor(11);
        printf("◆格倫　");
        Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[1]+1,money[1],estate[1],moral[1]);
        if(dead[1]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(12);
        printf("◆凱撒　");
        if(round==2)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[2]+1,money[2],estate[2],moral[2]);
        if(dead[2]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(6);
        printf("◆克雷格");
        if(round==3)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[3]+1,money[3],estate[3],moral[3]);
        if(dead[3]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(13);
        printf("◆莫伊拉");
        if(round==4)
            Set_TextColor(15);
        else
            Set_TextColor(7);
        printf("→位置：%2d　→財產：%6d　→房產：%6d　→善惡值：%3d\n",x[4]+1,money[4],estate[4],moral[4]);
        if(dead[4]==1){
            Set_TextColor(12);
            printf("　已死亡\n");
        }
        Set_TextColor(15);
        if(round==2){
            printf("當前輪到");
            Set_TextColor(12);
            printf("凱撒");
            Set_TextColor(15);
            printf("的回合，請等候其進行動作：\n");
            // 死亡判斷
            if(stop[round]==100){
                Sleep(1000);
                Dialouge("...已經死亡，無法進行任何動作，土地歸還",100,1,12);
                dead[round]=1;
                Set_TextColor(15);
                for(i=0;i<10;i++){
                    if(land[i]==round){
                        land[i]=0;
                        estate[round]-=land_price[i];
                    }
                }
                break;
            }
            //  可否動作判斷
            if(stop[round]>0&&stop[round]!=100){
                Sleep(1000);
                printf("目前無法移動，還有%d回合",stop[round]-1);
                stop[round]--;
                Sleep(1000);
                break;
            }
            Bankrupt(money,round);
            if(money[round]<0){
                Sleep(1000);
                printf("已經破產，無法進行動作");
                Sleep(1000);
                break;
            }
            //  擲骰子前的事件判斷
            //  購買土地事件
            if(map_kind==2&&land[map_kind_order]==0){
                event_chance=rand()%3;
                if(event_chance==1){
                    if(money[round]>land_price[map_kind_order]){
                    Sleep(1000);
                    printf("購買了土地\n");
                    Sleep(1000);
                    land[map_kind_order]=round;
                    money[round]-=land_price[map_kind_order];
            }
                }
            }
            //  博奕事件
            if(map_kind==6){
                event_chance=rand()%5;
                if(event_chance>=1){
                    if(event_chance==1){
                        makers[0]=rand()%13+1;
                        ai[0]=rand()%13+1;
                        Sleep(1000);
                        printf("進行賭局，輸入賭金：%d\n",money[round]/4);
                        Sleep(1000);
                        if(ai[0]>makers[0]){
                            event_chance=rand()%100+1;
                            if(event_chance>=35){
                                makers[1]=rand()%13+1;
                                ai[1]=rand()%13+1;
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                        else{
                            event_chance=rand()%100+1;
                            if(event_chance>=60){
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                    }
                }
                Sleep(1000);
            }
            // 暗市事件
            if(map_kind==7)
                DeepMarket(money,round,moral,x);
            if(stop[round]!=0)
                break;
            x[2]+=Dice();
            if(x[2]>27)
                x[2]-=28;
            Sleep(1000);
            MapJudge(x[round]);
            // 擲骰子後的事件判斷
            if(map_kind==2&&land[map_kind_order]!=0&&land[map_kind_order]!=2){
                printf("\n經過土地，被收取租金：%d元",land_price[map_kind_order]/5);
                money[2]-=land_price[map_kind_order]/5;
                money[land[map_kind_order]]+=land_price[map_kind_order]/5;
            }
            if(map_kind==3)
                Opportunity(money,x,round);
            if(map_kind==4)
                Fate(money,x,round);
        }
        else if(round==3){
            printf("當前輪到");
            Set_TextColor(6);
            printf("克雷格");
            Set_TextColor(15);
            printf("的回合，請等候其進行動作：\n");
            // 死亡判斷
            if(stop[round]==100){
                Sleep(1000);
                Dialouge("...已經死亡，無法進行任何動作，土地歸還",100,1,12);
                dead[round]=1;
                Set_TextColor(15);
                for(i=0;i<10;i++){
                    if(land[i]==round){
                        land[i]=0;
                        estate[round]-=land_price[i];
                    }
                }
                break;
            }
            //  可否動作判斷
            if(stop[round]>0&&stop[round]!=100){
                Sleep(1000);
                printf("目前無法移動，還有%d回合",stop[round]-1);
                stop[round]--;
                Sleep(1000);
                break;
            }
            Bankrupt(money,round);
            if(money[round]<0){
                Sleep(1000);
                printf("已經破產，無法進行動作");
                Sleep(1000);
                break;
            }
           //  擲骰子前的事件判斷
            if(map_kind==2&&land[map_kind_order]==0){
                event_chance=rand()%2;
                if(event_chance==3){
                    if(money[round]>land_price[map_kind_order]){
                    Sleep(1000);
                    printf("購買了土地\n");
                    Sleep(1000);
                    land[map_kind_order]=round;
                    money[round]-=land_price[map_kind_order];
            }
                }
            }
            //  博奕事件
            if(map_kind==6){
                event_chance=rand()%5;
                if(event_chance>=1){
                    if(event_chance==1){
                        makers[0]=rand()%13+1;
                        ai[0]=rand()%13+1;
                        Sleep(1000);
                        printf("進行賭局，輸入賭金：%d\n",money[round]/4);
                        Sleep(1000);
                        if(ai[0]>makers[0]){
                            event_chance=rand()%100+1;
                            if(event_chance>=35){
                                makers[1]=rand()%13+1;
                                ai[1]=rand()%13+1;
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                        else{
                            event_chance=rand()%100+1;
                            if(event_chance>=60){
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                    }
                }
                Sleep(1000);
            }
            // 暗市事件
            if(map_kind==7)
                DeepMarket(money,round,moral,x);
            if(stop[round]!=0)
                break;
            x[3]+=Dice();
            if(x[3]>27)
                x[3]-=28;
            Sleep(1000);
            MapJudge(x[round]);
            if(map_kind==2&&land[map_kind_order]!=0&&land[map_kind_order]!=3){
                printf("\n經過土地，被收取租金：%d元",land_price[map_kind_order]/5);
                money[3]-=land_price[map_kind_order]/5;
                money[land[map_kind_order]]+=land_price[map_kind_order]/5;
            }
            if(map_kind==3)
                Opportunity(money,x,round);
            if(map_kind==4)
                Fate(money,x,round);
        }
        else if(round==4){
            printf("當前輪到");
            Set_TextColor(13);
            printf("莫伊拉");
            Set_TextColor(15);
            printf("的回合，請等候其進行動作：\n");
            // 死亡判斷
            if(stop[round]==100){
                Sleep(1000);
                Dialouge("...已經死亡，無法進行任何動作，土地歸還",100,1,12);
                dead[round]=1;
                Set_TextColor(15);
                for(i=0;i<10;i++){
                    if(land[i]==round){
                        land[i]=0;
                        estate[round]-=land_price[i];
                    }
                }
                break;
            }
            //  可否動作判斷
            if(stop[round]>0&&stop[round]!=100){
                Sleep(1000);
                printf("目前無法移動，還有%d回合",stop[round]-1);
                stop[round]--;
                Sleep(1000);
                break;
            }
           //  擲骰子前的事件判斷
            if(map_kind==2&&land[map_kind_order]==0){
                event_chance=rand()%3;
                if(event_chance==1){
                    if(money[round]>land_price[map_kind_order]){
                    Sleep(1000);
                    printf("購買了土地\n");
                    Sleep(1000);
                    land[map_kind_order]=round;
                    money[round]-=land_price[map_kind_order];
            }
                }
            }
            Bankrupt(money,round);
            if(money[round]<0){
                Sleep(1000);
                printf("已經破產，無法進行動作");
                Sleep(1000);
                break;
            }
            //  博奕事件
            if(map_kind==6){
                event_chance=rand()%5;
                if(event_chance>=1){
                    if(event_chance==1){
                        makers[0]=rand()%13+1;
                        ai[0]=rand()%13+1;
                        Sleep(1000);
                        printf("進行賭局，輸入賭金：%d\n",money[round]/4);
                        Sleep(1000);
                        if(ai[0]>makers[0]){
                            event_chance=rand()%100+1;
                            if(event_chance>=35){
                                makers[1]=rand()%13+1;
                                ai[1]=rand()%13+1;
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                        else{
                            event_chance=rand()%100+1;
                            if(event_chance>=60){
                                if(makers[0]+makers[1]>ai[0]+ai[1]){
                                    printf("輸了，失去兩倍賭金\n");
                                    money[round]-=2*(money[round]/4);
                                }
                                else if(makers[0]+makers[1]<ai[0]+ai[1]){
                                    printf("贏了，獲得兩倍賭金\n");
                                    money[round]+=2*(money[round]/4);
                                }
                                else
                                    printf("平局\n");
                            }
                            else
                                printf("放棄賭局。\n");
                        }
                    }
                }
                Sleep(1000);
            }
            // 暗市事件
            if(map_kind==7)
                DeepMarket(money,round,moral,x);
            if(stop[round]!=0)
                break;
            x[4]+=Dice();
            if(x[4]>27)
                x[4]-=28;
            Sleep(1000);
            MapJudge(x[round]);
            if(map_kind==2&&land[map_kind_order]!=0&&land[map_kind_order]!=4){
                printf("\n經過土地，被收取租金：%d元",land_price[map_kind_order]/5);
                money[4]-=land_price[map_kind_order]/5;
                money[land[map_kind_order]]+=land_price[map_kind_order]/5;
            }
            if(map_kind==3)
                Opportunity(money,x,round);
            if(map_kind==4)
                Fate(money,x,round);
        }
        printf("\n回合結束");
        Sleep(2500);
        return x;
    }
}
void Initalize(){
    SetConsoleTitle("大富翁");
    system("mode con cols=95 lines=35"); //解析度約800*600
    srand(time(NULL));
    FILE *fin;
    int x[100],i=0;
    char t[100];
    // 讀取系統設定檔案
    fin=fopen("system.dat","r");
    if (fin){
        while(fscanf(fin,"%d",&x[i]) != EOF){
            i++;
        }
        bgm_play=x[0];
        se_play=x[1];
        i=0;
    }
    fclose(fin);
    // 讀取遊戲系統存檔及解密
    fin=fopen("global.dat","r");
    if (fin){
        while(fscanf(fin,"%c",&t[i]) != EOF)i++;
        bad_end1=t[0]-'0'-25;
        bad_end2=t[4]-'0'+12;
        bad_end3=t[8]-'0'+36;
        true_end=t[12]-'0'-48;
    }
    fclose(fin);
    // 測試時使用 printf("%d %d %d %d",bad_end1,bad_end2,bad_end3,true_end);
}
void SaveSet(){
    FILE *fout;
    fout=fopen("system.dat","w");
    fprintf(fout,"%d\n%d\n",bgm_play,se_play);
    fclose(fout);
}
void SaveGlobal(){
    // 儲存遊戲系統存檔及加密
    srand(time(NULL));
    int i,x[4];
    for(i=0;i<4;i++)
        x[i]=rand()%127;
    FILE *fout;
    fout=fopen("global.dat","w");
    fprintf(fout,"%c\n%c\n%c\n%c\n%c\n%c\n%c\n%c\n",bad_end1+'0'+25,x[0],bad_end2+'0'-12,x[1],bad_end3+'0'-36,x[2],true_end+'0'+48,x[3]);
    fclose(fout);
}
int Keyboard_Pressed(){
    /* 注意，呼叫方法為變數=Keyboard_Pressed() 會回傳輸入按鍵的ascii code
       且只有等待按下一個按鍵，要重複判斷需自行加上迴圈
    */
    int keyboard;
    keyboard=getch();
    // 測試時使用 printf("%d",Keyboard);
    return keyboard;
}
void Clr(){
    /*
    函式： Clr, 清除螢幕
    說明： 解決使用 system("cls") 會有閃爍問題
        事實上這只是把每個點都填上空白而已
    轉載： CodeGurn
    */
    COORD coordScreen = { 0,0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD dwConSize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hConsole, &csbi);
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(hConsole, TEXT(' '),dwConSize,coordScreen,&cCharsWritten);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
    SetConsoleCursorPosition(hConsole, coordScreen);
}
void Set_TextColor(int c){
    /*
    使用方式：_Settextcolor(顏色代碼)
    設定printf 文字顏色，印出完後需補一行_Settextcolor(7) 調回預設顏色
    輸入顏色參考網站：https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
    */
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, c);
}
