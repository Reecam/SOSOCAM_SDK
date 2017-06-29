//
//  SoundWaveWifiSetting & WiFiMatching SoundWaveWifiSetting & WiFiMatching SoundWaveWifiSetting+WiFiMatching.h
//  SoDemon
//
//  Created by feng on 16/3/15.
//  Copyright © 2016年 feng. All rights reserved.
//
---------------------------------------------------------

SoundWaveWifiSetting & WiFiMatching

说明：
无线网络设置，是指把摄像机设置成连接莫一个无线路由器。
无线网络设置有四种方式：声音设置无线网络，smartlink设置无线网络和单纯的无线设置，web_app。
其中无线设置添加有两种方式：声音设置无线网络，smartlink设置无线。这两种方式可以单独使用，也可以同
时使用。但同时使用时，一定要注意。当一种方式成功时，一定要记得把另外一种设置方式停止。即smartlinK
设置先成功时，要记得把sound停止。当smartlink设置先成功时，要记得把smartlink停止。


#pragma mark  1.声音设置无线 <无线设置／停止／无线设置结果／结果信息>
1.声音设置无线

1）开始声音设置无线
说明：使用以下函数可以通过声音设置无线网络也可以监控设置的过程。
函数：
/*
 * 参数如下：
 * ssid:wifi的ssid
 * psk:wifi的密码
 * test:测试无线，默认设置为NO
 * delegate:代理SoundWaveWifiSettingDelegate
 * 返回：
 * 返回一个BOOL值，当返回YES时，表示函数执行成功，否则执行失败。
 */
-(BOOL)start:(NSString *)ssid
psk:(NSString *)psk
test:(BOOL)test
delegate:(id<SoundWaveWifiSettingDelegate>)delegate;//开始声音无线设置

/*
 *这是代理SoundWaveWifiSettingDelegate的回调函数
 *开始声音设时，添加了此代理
 *只要声音设置无线状态有改变时候就会调用此函数
 */
回调函数：-(void)on_sound_wave_wifi_setting_state_changed;

2）停止声音设置无线
说明：使用此函数，可以强制停止声音无线设置
函数：-(void)stop;

3）声音设置无线信息获取：

/*
 *声音设置无线结果，共有五种结果，详细如下：
 */
-(SOUND_WAVE_WIFI_SETTING_RESULT)result; //声音设置无线结果
typedef enum {
    SOUND_WAVE_WIFI_SETTING_RESULT_SUCCEED, //设置成功
    SOUND_WAVE_WIFI_SETTING_RESULT_TIMEOUT,//设置超时
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_JOIN,//JSON解析错误
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_BUSY,//网络繁忙
    SOUND_WAVE_WIFI_SETTING_RESULT_FAILED_INTERNAL,//内部出错
} SOUND_WAVE_WIFI_SETTING_RESULT;

/*
 *声音设置无线状态，共有五种结果，详细如下：
 */
-(SOUND_WAVE_WIFI_SETTING_STATE)state;//声音设置无线状态
typedef enum {
    SOUND_WAVE_WIFI_SETTING_STATE_IDLE, //设置失败
    SOUND_WAVE_WIFI_SETTING_STATE_SEND_SETTING, //发送声音设置
    SOUND_WAVE_WIFI_SETTING_STATE_WAIT_CONFIRM,//等待信息确认
    SOUND_WAVE_WIFI_SETTING_STATE_WAIT_RESULT,//等待设置结果
    SOUND_WAVE_WIFI_SETTING_STATE_SEND_CONFIRM,//发送确认信息
} SOUND_WAVE_WIFI_SETTING_STATE;

/*设置成功后，查询id是否在局域网内
 *因为id太长，摄像机传不过来，所以把id编码分成name_of_camera_id和serial_of_camera_id来传
 *比较的时候，先把局域网的id通过get_name_of_camera_id和get_serial_of_camera_id编码再来来比较
 */
-(int)name_of_camera_id;

-(int)serial_of_camera_id;


4）示列：
/*
 第一步：创建一个SoundWaveWifiSetting对象
 */
SoundWaveWifiSetting * m_sound_wifi_setting = [[SoundWaveWifiSetting alloc] init];

/*
 *第二步：发送声音 添加代理SoundWaveWifiSettingDelegate
 */
-(void)startSound{
    BOOL  m_sound_wifi = [m_sound_wifi_setting start:m_ssid psk:m_text_input.text test:NO delegate:self];
    if (! m_sound_wifi){
        [self show_error:LOCAL_STR(@"SEND_WIFI_INFO_FAIL")];
    }
}

/*
 *监测 声音设置无线的过程
 */
-(void)on_sound_wave_wifi_setting_state_changed {
    SOUND_WAVE_WIFI_SETTING_STATE state = [m_sound_wifi_setting state];
    SOUND_WAVE_WIFI_SETTING_RESULT result = [m_sound_wifi_setting result];
    NSLog(@"SOUND_WAVE_WIFI_SETTING_STATE = %u SOUND_WAVE_WIFI_SETTING_RESULT = %u",state,result);
    if (result == SOUND_WAVE_WIFI_SETTING_RESULT_SUCCEED){
        [self discover];//设置成功开始在局域网查询
    }
}

/*
 *第三步：设置成功后，查询id是否在局域网内,来获取id
 */
-(void)discover{
    NSArray * cameras_list = [[IPCamMgr get_share] get_discovered_cameras_list];
    int i;
    NSString * camera_id;
    int camera_id_name;
    int camera_id_serial;
    NSDictionary * camera;
    for (i = 0;i < cameras_list.count;i ++) {
        camera =  [cameras_list objectAtIndex:i];
        camera_id = [camera objectForKey:@"camera_id"];
        /*对局域网的摄像机id进行编码*/
        camera_id_name = [Util get_name_of_camera_id:camera_id];
        camera_id_serial = [Util get_serial_of_camera_id:camera_id];
        /*查id 是否在局域网内*/
        if (camera_id_name == [m_sound_wifi_setting name_of_camera_id] &&
            camera_id_serial == [m_sound_wifi_setting serial_of_camera_id]) {
            NSLog(@"camera id is :%@",camera_id);
        }
    }
/*
 *不需要了，强制取消SoundWaveWifisetting设置。设置成功了，不需要做停止的的操作
 */
    [m_sound_wifi_setting stop];
    
    
#pragma mark  2.smartlink设置无线网络 <设置／停止／成功回调>
2.smartlink设置无线网络

1）smartlink设置
说明：使用以下函数可以通过smartlink设置无线网络
/*
 *参数如下：
 *ssid:wifi的ssid
 *psk:wifi的密码
 *delegate:WiFiMatchingDelegate代理
 * 返回：
 * 返回一个BOOL值，当返回YES时，表示函数执行成功，否则执行失败。
 */
函数：
-(BOOL)start:(NSString *)ssid
psk:(NSString *)psk
delegate:(id<WiFiMatchingDelegate>)delegate;

/*
 *这是代理WiFiMatchingDelegate的回调函数
 *开始smartlink设置时时，添加了此代理
 *当smartlink设置无线成功后就会调用此函数且返回成功摄像机的id,其他时候不会掉用此函数
 */
回调函数：
-(void)on_wifi_matching_succeed:(NSString *)camera_id;
    
2）停止smartlink设置无线
说明：此函数可以强制停止smartlink设置无线
函数：
-(void)stop;

3）示列：
/*
 *第一步：创建一个WiFiMatching对象
 */
    WiFiMatching * m_wifi_match = [[WiFiMatching alloc]init];
    
/*
 *第二步：发送smartlink 添加代理WiFiMatchingDelegate
 */
-(void)startSmartlink{
    BOOL  m_smart_link = [m_wifi_match start:m_ssid psk:m_text_input.text delegate:self];
    if (! m_smart_link){
        [self show_error:LOCAL_STR(@"SEND_WIFI_INFO_FAIL")];
    }
}
    
/*
 *WiFiMatchingDelegate代理回调
 */
-(void)on_wifi_matching_succeed:(NSString *)camera_id{
    if (camera_id) {
        NSLog(@"smartlink设置成功, camera_id= %@”，camera_id);
              }
}

/*
 *不需要了，强制取消smartlink设置，设置成功了，不需要做停止的的操作
 */
    [m_wifi_match stop];
              
              
#pragma mark - 更新版本接口/功能
        
/**
 更新摄像机清晰度

 @param camera_id 摄像机ID
 @param stream    清晰度
 */
-(void)update_camera_stream:(NSString *)camera_id
                     stream:(int)stream;
              
/**
 获取摄像机存储于本地的清晰度

 @param camera_id 摄像机ID

 @return 返回清晰度
 */
-(int)get_camera_stream:(NSString *)camera_id;


/**
 更新收藏的图片的清晰度

 @param share_id 指定摄像机ID
 @param stream   清晰度
 */
-(void)update_collection_stream:(NSString *)share_id
                         stream:(int)stream;
