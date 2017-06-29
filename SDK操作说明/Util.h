//
//  Util.h
//  SoDemon
//
//  Created by feng on 16/3/15.
//  Copyright © 2016年 feng. All rights reserved.
//

#pragma mark  1.获取iphone系统属性参数<版本／语言／时间／Wi-Fi／方向>

1.获取iphone系统属性参数

1）iphone系统版本号检测
说明：以下函数，用于判断iphone版本，详细版本需求，如下：
函数：
+(BOOL)isOS7; //版本［7.0，8.0］

+(BOOL)isOS8;  //版本［8.0，9.0］

+(BOOL)isAfterOS7; //版本>=7.0

+(BOOL)isAfterOS8;  //版本>=8.0

+(BOOL)isBelowOS8;   //版本<=8.0
返回：五个函数都是返回BOOL,返回YES时，表示满足条件。否则不满足条件。
示例：
BOOL isBleowOs8 = [Util isBelowOS8];

2）iphone系统语言检测
说明：使用以下函数，可以检测出iphone当前的语言。
函数：+(NSString *)check_language
返回：返回一个NSString类型，当返回@"";
，代表当前是中文（包含简体中文和繁体中文），当返回@"en"，代表当前是非中文
示例：
[Util check_language];

3)iphone手机当前wifi ssid
说明：使用此函数，可以获取党当前手机正在连接的wifi ssid
函数：
+(NSString *)get_ssid

示例：
m_ssid = [Util get_ssid];

4）iphone当前时间
说明：使用此函数可以获取iphone手机当前的时间
函数：
+(NSString*)get_sys_current_datatime
返回：返回NSString字符,返回"YYYY-MM-dd hh:mm:ss"格式
示例：
[Util get_sys_current_datatime];

5）获取当前手机方向

说明：获取当前手机屏幕方向，这个函数用到了sdk内部的OMGToast。
函数：+(UIInterfaceOrientation)getScreenOrientation
返回：返回UIInterfaceOrientation
示例：
[Util getScreenOrientation];


#pragma mark  2.app信息检测<版本／名称>
2.app信息检测
1）app版本号检测
说明：使用此函数可以获取到app的版本号
函数:
+(NSString *)get_app_version
返回：返回一个NSString，就是app的"CFBundleShortVersionString"
示例：
[Util get_app_version];


2）app名字检测
说明：使用此函数可以获取到app的名字
函数：
+(NSString* )get_app_name
返回：返回一个NSString，就是app的"CFBundleDisplayName"
示例：
[Util get_app_name];

#pragma mark  3.控件定制<alterview/toast/cornerRadius&color>
3.控件定制
1）定制UIAlertView
说明：以下两个函数是定制的UIAlertView，适配ios8和ios7。
函数：
+(UIAlertView *)show_alert_view:(NSString *)title
message:(NSString *)message
ok_title:(NSString *)ok_title
ok_handler:(void (^)(UIAlertAction * action))ok_handler
parent_vc:(UIViewController *)parent_vc
delegate:(id<UIAlertViewDelegate>)delegate;
参数：
title:弹窗标题
message:弹窗信息
ok_title:确定按钮的标题
ok_handler:确定按钮的动作,仅用于ios8,IOS7的通过代理实现
parent_vc:一个UIViewController的父类，仅用于ios8
delegate：UIAlertViewDelegate代理,仅用于ios7
返回：返回一个UIAlertView，仅用于ios7

+(UIAlertView *)show_alert_view:(NSString *)title
message:(NSString *)message
ok_title:(NSString *)ok_title
ok_handler:(void (^)(UIAlertAction * action))ok_handler
cancel_title:(NSString *)cancel_title
cancel_handler:(void (^)(UIAlertAction * action))cancel_handler
parent_vc:(UIViewController *)parent_vc
delegate:(id<UIAlertViewDelegate>)delegate;

参数：
title:弹窗标题
message:弹窗信息
ok_title:确定按钮的标题
ok_handler:确定按钮的动作,仅用于ios8,IOS7的通过代理实现
cancel_title:取消按钮的标题
cancel_handler:取消按钮的动作,仅用于ios8,IOS7的通过代理实现
parent_vc:一个UIViewController的父类，仅用于ios8
delegate：UIAlertViewDelegate代理,仅用于ios7
返回：返回一个UIAlertView，仅用于ios7
示例：

/*创建UIAlertView */
UIAlertView * m_alertview_delete ＝ [Util show_alert_view:LOCAL_STR(@"TIPS")
                                                 message:LOCAL_STR(@"SURE_SAVE_ALBUM")
                                                ok_title:LOCAL_STR(@"SURE")
                                              ok_handler:^(UIAlertAction * action) {
                                                  [self do_export];
                                              }
                                            cancel_title:LOCAL_STR(@"CANCEL")
                                          cancel_handler:nil
                                               parent_vc:self
                                                delegate:self];
/* ios7 UIAlertView的代理*/

-(void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if ([alertView isEqual:m_alertview_delete]) {
        if (buttonIndex == 1) {
            [self do_delete];
            [m_tableview_files_list reloadData];
        }
    }
}

2）定制消息提示框
说明：以下三个函数，是用来提示信息用的，且自动消息。
函数：
/*
 *显示提示框，3.5s后自动消失
 *参数tip:要显示的内容
 */
+(void)show_long_toast:(NSString *)tip

/*
 *显示提示框，2.0s后自动消失
 *参数tip:要显示的内容
 */
+(void)show_short_toast:(NSString *)tip

/*
 *强制取消提示框
 */
+(void)cancel_toast
示例：
[Util show_long_toast:LOCAL_STR(@"UNABLE_ENTER_TF")];
[Util cancel_toast];

3）圆弧定制和颜色
说明：以下三个函数都是用来定制控件属性的
函数：
/*
 *颜色定制
 *参数color是一个16进制的三个字节的数目，如果0xffFF9966，
 *表示r:255(0xFF) g:153(0x99)  b:102(0x66)
 */
+(UIColor *)colorWithRGB:(int)color
/*
 *button圆角角度定制＋borderColor定制
 *参数color是一个16进制的三个字节的数目，如果0xffFF9966，
 *表示r:255(0xFF) g:153(0x99)  b:102(0x66)
 */

+(UIButton*)cornerRadius:(UIButton*)m_button colorwithRGB:(int)color;
/*
 *UIView圆角角度定制＋borderColor定制
 *参数color是一个16进制的三个字节的数目，如果0xffFF9966，
 *表示r:255(0xFF) g:153(0x99)  b:102(0x66)
 */

+(UIView*)cornerRadius:(UIView*) m_view colorRGB:(int)color

示例：
m_label_pwd_power.textColor = [Util colorWithRGB:0xffFF9966];
m_button_research = [Util cornerRadius:m_button_research colorwithRGB:0xffFF9966];
m_view_research_back = [Util cornerRadius:m_view_research_back colorwithRGB:0xffFF9966];

#pragma mark 4.字符串操作<正规则表达式比较／密码强度／id编码／特殊字符转码>
4.字符串操作
1）正规则表达式判断两个字符串相等
说明：判断content字符是否满足regular_expression的正规则表达式
函数：+(BOOL)is_content_matching_regular_expression:(NSString *)content
regular_expression:(NSString *)regular_expression
参数：
content：被判断的字符
regular_expression：正规则表达式的字符。
返回：返回一个BOOL类型.
示例：
/*
 *判断camera_id是否满足@"^RCAM-\\d{6}-[A-Z]{5}$" */
[Util is_content_matching_regular_expression:camera_id regular_expression:@"^RCAM-\\d{6}-[A-Z]{5}$"]

2）正规则表达式判断字符中是否包含某些字符。
说明：搜索content是否包含regular_expression这个字符。包含返回YES,否则返回NO.
+(BOOL)is_content_contain_regular_expression:(NSString *)content
regular_expression:(NSString *)regular_expression;
返回：返回一个BOOL类型.
示例：
/*
 *判断str是否满足正规则表达式@".*?[\\d]+.*?"
 */
[Util is_content_contain_regular_expression:str regular_expression: @".*?[\\d]+.*?"];

3).UTF8字符串编码
说明：以下函数会对特殊字符@"!*'();:@&=+$,/?%#[]"进行编码输出。
函数：
+(NSString *)url_query_value_encode:(NSString *)value;
参数：value：对value字符进行编码
示例：
[Util url_query_value_encode:m_camera_name];


5）.正规则表达式判断密码强弱
说明：计算密码的
函数：+(int)passwordStrength:(NSString *)str;
返回：返回一个int型，一共有四个等级，详细如下：
0:表示密码长度小于8:
1:表示密码由数字，大写字母，小写字母，特殊字符其中一种类型组成。
2:表示密码由数字，大写字母，小写字母，特殊字符其中两种类型组成。
3:表示密码由数字，大写字母，小写字母，特殊字符其中三种类型组成。
4:表示密码由数字，大写字母，小写字母，特殊字符其中四种类型组成。

示例：
int i = [Util passwordStrength:@"sandy666666"];

#pragma mark 5.GET URL操作打开网址获取图片或图片数据 <GET URL JSON/UIImage/NSData>

5.GET URL操作
1)JSON返回
说明：以下两个函数，都是用于打开url的。函数1没有设置超时时间，函数2设置了超时时间。值得注意的时，传入的URL如果有特殊字符需要编码的，先要用url_query_value_encode编码，才传给以下两个函数之一。
函数1:
+(NSDictionary *)http_get_json:(NSString *)url;
url:编码后的url
返回：返回一个json数据的NSDictionary
示例：
NSString *url = [NSString stringWithFormat:@"%@%@:%d/get_params.cgi?user=%@&pwd=%@&json=1&%@",
                 m_https?@"https://":@"http://",
                 m_ip,
                 m_port,
                 m_user,
                 [Util url_query_value_encode:m_pwd],
                 [Util url_query_value_encode:params]];
NSDictionary * json = [Util http_get_json:url];

函数2:
+(NSDictionary *)http_get_json:(NSString *)url
timeout:(int)timeout;
参数：
url:UTF8编码后的url
timeout:超时时间，单位ms
返回：返回一个json数据的NSDictionary
示例：
NSString *url = [NSString stringWithFormat:@"%@%@:%d/get_params.cgi?user=%@&pwd=%@&json=1&%@",
                 m_https?@"https://":@"http://",
                 m_ip,
                 m_port,
                 m_user,
                 [Util url_query_value_encode:m_pwd],
                 [Util url_query_value_encode:params]];
NSDictionary * json = [Util http_get_json:url timeout:10.0];
2）UIImage返回
说明：打开一个url,返回一个UIImage类。值得注意的时，传入的URL如果有特殊字符需要编码的，先要用url_query_value_encode编码，才传给以下两个函数之一。
+( *)http_get_image:(NSString *)url;
示例：
UIImage *image = [Util http_get_image:url];

3）NSData返回
说明：打开一个url,返回一个NSData类。值得注意的时，传入的URL如果有特殊字符需要编码的，先要用url_query_value_encode编码，才传给以下两个函数之一。
+(NSData *)http_get_binary:(NSString *)url;
示例：
NSData *data = [Util http_get_image:url];


#pragma mark 6.文件导出 <从document或把服务器获取到的文件导出到本地相册>
6.导出图片或录像到本地存储
1）把document的文件导出到本地相册
说明:把图片或录像从document导出到系统相册。［reecam主要用于导出拍照和本地录像文件］
函数：
+(void)save_picture_to_system_album:(NSString *)picture_path//导出图片
+(void)save_clip_to_system_album:(NSString *)clip_path //导出录像
参数：picture_path：图片的路径  clip_path：录像的路径
示例：
-(void)on_button_export_clicked:(int)index
{
    NSDictionary * item = [m_album objectAtIndex:index];
    if (item) {
        if ([[item objectForKey:@"type"] intValue] == MEDIA_CLIP) {
            [Util save_clip_to_system_album:[item objectForKey:@"path"]]; //导出录像
            [Util show_long_toast:LOCAL_STR(@"SAVE_CLIP_SUCCESS")];
        } else {
            [Util save_picture_to_system_album:[item objectForKey:@"path"]];//导出图片
            [Util show_long_toast:LOCAL_STR(@"SAVE_PICTURE_SUCCESS")];
        }
    }
}

2)把服务器的文件导出到系统相册
说明：把图片导出到系统相册［reecam主要用于把从服务器下载下来的图片导出到系统相册］
函数：+(void)save_picture_data_to_system_album:(NSData *)picture_data
参数：picture_data：文件数据
示例：
{
    NSDictionary * image = [m_images_list objectAtIndex:index];
    if (image) {
        NSData * data = [image objectForKey:@"data"];
        if (data) {
            [Util save_picture_data_to_system_album:data];
            [Util show_long_toast:LOCAL_STR(@"SAVE_PICTURE_SUCCESS")];
        }
    }
}

#pragma mark 7.获取本地录像信息 <获取本地文件的大小和预览图>

7.获取本地录像信息
说明：获取本地录像文件信息(预览图 时长等)
函数：
/*
 *duration / NSNumber * / float 时长，没有格式，单位秒
 *duration_string / NSString * 时长 %02lld:%02d:%02d或%02d:%02d格式
 *thumb / UIImage *  预览图
 */
+(NSDictionary *)get_clip_info:(NSString *)file_path time:(CGFloat )timeBySecond
参数：
file_path：录像文件路径
timeBySecond：单位秒，取第几秒的数据预览图像。[reecam设置为0]
示例：

-(void)show_content:(NSDictionary *)item
index:(int)index
{
    if ([[item objectForKey:@"type"] intValue] == MEDIA_CLIP) {
        NSDictionary * info = [Util get_clip_info:[item objectForKey:@"path"] time:0];
        m_imageview_thumb.image = [info objectForKey:@"thumb"]; //预览图
        m_label_size.text = [info objectForKey:@"duration_string"];//时长
    }
}

#pragma mark 8.摄像机id处理<id编码用于jpush tag/soundwave>

8.摄像机id处理
1）推送摄像机id转义[reecam自己定义]
说明：遇到非字母数字的都转义成与下划线开始后面带他的16进制。消息推送，以id为tag注册时用,瑞彩自定义
函数：+(NSString *)encodeTag:(NSString*)camID
返回：返回一个转码后的NSString
示例：
[Util encodeTag:@"-66&88"];  //返回：_2d66_2688

2）声音添加摄像机id转义
说明：把摄像机id拆分，转换成两个int.使用声音添加时,需要用到。
函数：
+(int)get_name_of_camera_id:(NSString *)camera_id //是否和sound里面name_of_camera_id转义出来是一致的
+(int)get_serial_of_camera_id:(NSString *)camera_id //是否和sound里面serial_of_camera_id转义出来是一致的

返回：都是返回一个int类型的数
示例：
-(void)checkId{
    camera_id = [camera objectForKey:@"camera_id"];
    camera_id_name = [Util get_name_of_camera_id:camera_id];
    camera_id_serial = [Util get_serial_of_camera_id:camera_id];
    if (camera_id_name == [m_sound_wifi_setting name_of_camera_id] &&
        camera_id_serial == [m_sound_wifi_setting serial_of_camera_id]){
        ;
    }
}

#pragma mark 9.手机录音 <手机录音和播放>

9.手机录音
说明：以下函数是手机录音和回放的视线
1）手机录音
函数：
/*
 *开始手机录音＋添加代理UtilRecordAudioDelegate
 *参数max_seconds：设置录音时长，时间到了会自动停止。
 */
+(BOOL)start_record_audio:(unsigned int)max_seconds delegate:(id<UtilRecordAudioDelegate>)delegate;
/*
 *停止手机录音
 */
+(void)stop_record_audio;
/*
 *录音结束后的回调，返回录音数据data
 */

-(void)on_record_audio_finished:(NSData *)data;


2）手机回放
/*
 *开始手机录音回放＋添加代理UtilPlayAudioDelegate
 */
+(BOOL)start_play_audio:(NSData *)data delegate:(id<UtilPlayAudioDelegate>)delegate;

/*
 *停止手机录音回放
 */
+(void)stop_play_audio;

/*
 *UtilPlayAudioDelegate回调
 */
-(void)on_play_audio_finished;


示例：

#pragma mark 10.SDK版本号获取

10.SDK版本号获取
说明：获取sdk版本号
函数：
+(NSString *)get_sosocamlib_version
示例：
[Util get_sosocamlib_version];

#pragma mark - 新增加接口/方法

/**
 给指定的View修改属性

 @param m_view 指定的view
 @param color  颜色
 @param i      圆角
 @param j      边界宽度

 @return 制定修改的View
 */
+(UIView*)cornerRadius:(UIView*) m_view colorRGB:(int)color radius:(int)i borderwidth:(int)j;
