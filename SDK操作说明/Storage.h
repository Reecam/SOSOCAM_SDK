//
//  Storage.h
//  SoDemon
//
//  Created by feng on 16/3/15.
//  Copyright © 2016年 feng. All rights reserved.
//
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
//
//  read.m
//  SoSoCamSDKBundle
//
//  Created by feng on 16/3/9.
//  Copyright © 2016年 reecam. All rights reserved.
//


－－－－－－－－－－－－－－－－－－－－－
#pragma mark 1.本地存储用户管理<获取用户列表/更新用户/删除用户/设置当前用户>

1.本地存储用户管理
说明：以下函数是在需要用户管理才用到的函数，包括用户列表的获取／删除用户／更新用户／设置当前用户
1）本地用户信息获取
说明：通过此函数可以获取到本地的所有用户以及用户信息。
函数：-(NSArray *)get_users_list;
返回：返回一个数组，数组的每一个元素是一个字典，字典的key/value如下：
user_id/NSString *   //账号的user_id，注册的时候用user_id为tag
alias/NSString *     //账号昵称
/*
 *登录类型，共有四种
 *OFFLINE_USER      离线登录，即不用账号直接使用，不使用平台功能
 *ACCOUNT_USER      账号登录
 *QQ_USER           第三方 QQ登录
 *FACEBOOK_USER     第三方 facebook登录
 *WEB_QQ_USER       第三方 QQ网页登录
 */
login_type/NSNumber * //登录类型
/*
 *account_name和account_pwd，当login_type = ACCOUNT_USER时才用到
 */
account_name/NSString *//账号名
account_pwd/NSString * //账号密码
/*
 *open_id和access_token
 *当login_type = FACEBOOK_USER | WEB_QQ_USER 时才用到
 */
open_id/NSString *     //openId
access_token/NSString * //accessToken
/*
 *是否是最新登录，如果是最新登录的，可以保存起来，如果是YES,下次可以直接登录
 *但是WEB_QQ_USER为了安全，不能直接保存openId和accessToken，所以一直设置为No
 */
latest/NSNumber *       //是否是最新登录


2)更新用户
说明：通过此函数可以更新本地用户信息。当切换用户或登录等，只要登录状态有改变，都需要用到此函数。
参数：
user_id   //user_ID 是服务器返回来的用户标记码
login_type //登录类型
/*
 *如果是ACCOUNT_USER类型，auth_name就是账号名account_name
 *如果是QQ_USER或FACEBOOK_USER类型，auth_name就是open_id
 *如果是WEB_QQ_USER，auth_name = @""
 */
auth_name
/*
 *如果是ACCOUNT_USER类型，auth_pwd就是账号名account_pwd
 *如果是QQ_USER或FACEBOOK_USER类型，auth_pwd就是access_token
 *如果是WEB_QQ_USER，auth_pwd = @""
 */
auth_pwd：
alias：//别名
函数：
-(void)update_user:(NSString *)user_id
login_type:(int)login_type
auth_name:(NSString *)auth_name
auth_pwd:(NSString *)auth_pwd
alias:(NSString *)alias;


3）删除账号

说明：以下两个分别删除本地所有账号和删除本地指定账号
函数：
-(void)clear_user_latest; //删除所有账号

-(void)remove_user:(NSString *)user_id; //删除指定账号
参数：
user_id：指定删除的账号user_id

4）当前账号
说明：以下函数可以实现，设置当前用户，获取当前用户的user_id和名称
函数：
-(void)set_current_user:(NSString *)user_id; //设置user_id为当前账号

-(NSString *)get_current_user_id;//获取当前账号的user_id

-(NSString *)get_current_user_alias;//获取当前账号的昵称
参数：
user_id：指定设定为当前账号的账号user_id

5）示例：


#pragma mark 2.本地存储摄像机管理 <获取摄像机／和服务器比较／添加／删除／更新>

2.本地存储摄像机管理

1）摄像机list获取
说明:以下函数用来获取本地存储的摄像机，以及摄像机的信息
函数：
-(NSArray *)get_cameras_list;

返回：返回一个数组，数组的每一个元素是一个字典，字典的key/value如下：
camera_id/NSString * //摄像机id
alias/NSString *    //摄像机昵称
user/NSString *    //摄像机登录用户名
pwd/NSString *   //摄像机登录密码
https/NSNumber * //加密安全传输，两个值 0:非加密    1:加密
sosocam_id/NSString * //摄像机sosocam_id
cover/NSData *   //摄像机预览图data数据
model/NSNumber * //摄像机模型，两个值，0 云台机  1 卡片机
recent/NSNumber */Long
master/NSNumber */BOOL //主摄像机，BOOL值，YES:主摄像机，NO:非主摄像机。
示例：
m_ipcams_list = [[storage get_share] get_cameras_list];


2）比较
说明：把从服务器上获取到的摄像机和当前账号本地的cams做比较,如果一样返回Yes,如果不一样，此函数把服务器上的和本地的做同步，且返回No
函数：
-(BOOL)merge_cameras_list:(NSArray *)server_cameras_list;
参数：server_cameras_list:服务器上获取到的摄像机机
返回：返回BOOL值，YES:服务器上的cams和本地的cams一样。NO:服务器上的cams和本地的cams不一样。
示例：
[storage merge_cameras_list:[webservice get_cameras_list]]

3）添加
说明：添加摄像机到本地存储。一般添加了摄像机或从服务器上获取到了新摄像机都要存储到本地。这时候就要适用此函数。
函数：
-(void)add_camera:(NSString *)camera_id
alias:(NSString *)alias
user:(NSString *)user
pwd:(NSString *)pwd
https:(BOOL)https
sosocam_id:(NSString *)sosocam_id
model:(int32_t)model
master:(BOOL)master;
参数：
camera_id/NSString * //摄像机id
alias/NSString *    //摄像机昵称
user/NSString *    //摄像机登录用户名
pwd/NSString *   //摄像机登录密码
https/NSNumber * //加密安全传输，两个值 0:非加密    1:加密
sosocam_id/NSString * //摄像机sosocam_id
model/NSNumber * //摄像机模型，两个值，0 云台机  1 卡片机
master/NSNumber */BOOL //主摄像机，BOOL值，YES:主摄像机，NO:非主摄像机。

示例：
[[Storage get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                          alias:m_camera_name
                           user:@"admin"
                            pwd:[m_ipcam pwd]
                          https:[m_ipcam https]
                     sosocam_id:sosocam_camera_id
                          model:[m_ipcam model]
                         master:NO];


4）删除
说明：此函数用来从本地删除指定的摄像机。
函数：
-(void)remove_camera:(NSString *)camera_id;
参数：
camera_id：即将被删除的摄像机id
示例：
[[Storage get_share] remove_camera:m_camera_id];


5）更新
说明：以下函数都是用来更新摄像机本地信息的。（名称／登录名／登录密码／https／ID／sosocam_id/cover/master）
函数：
/*
 *更新摄像机的名称
 *参数
 *camera_id:要被更新的摄像机id
 *alias:摄像机昵称更新为alias
 */
-(void)update_camera_alias:(NSString *)camera_id
alias:(NSString *)alias;

/*
 *更新摄像机的登录名
 *参数
 *camera_id:要被更新的摄像机id
 *user:摄像机登录名更新为user
 */
-(void)update_camera_user:(NSString *)camera_id
user:(NSString *)user;

/*
 *更新摄像机的登录密码
 *参数
 *camera_id:要被更新的摄像机id
 *pwd:摄像机登录密码更新为pwd
 */
-(void)update_camera_pwd:(NSString *)camera_id
pwd:(NSString *)pwd;

/*
 *更新摄像机的安全传输值
 *参数
 *camera_id:要被更新的摄像机id
 *https:摄像机安全传输值更新为https
 */
-(void)update_camera_https:(NSString *)camera_id
https:(BOOL)https;

/*
 *更新摄像机的sosocam_id
 *参数
 *camera_id:要被更新的摄像机id
 *sosocam_id:摄像机的sosocam_id更新为sosocam_id
 */
-(void)update_camera_sosocam_id:(NSString *)camera_id
sosocam_id:(NSString *)sosocam_id;


/*
 *更新摄像机的预览图
 *参数
 *camera_id:要被更新的摄像机id
 *cover:摄像机的预览图数据更新为cover
 */
-(void)update_camera_cover:(NSString *)camera_id
cover:(NSData *)cover;

/*
 *更新摄像机的主摄像机值
 *参数
 *camera_id:要被更新的摄像机id
 *master:摄像机的主摄像机值更新为master
 */
-(void)update_camera_master:(NSString *)camera_id
master:(BOOL)master;
示例：
[[Storage get_share] update_camera_pwd:[ipcam camera_id] pwd:[ipcam pwd]]

#pragma mark 3.本地存储收藏摄像机管理 <获取收藏摄像机／和服务器比较／添加／删除／更新>

3.本地存储收藏摄像机管理

1）获取本地收藏摄像机
说明：以下两个函数
函数：
/*
 *返回一个数组，数组的每一个元素是一个字典，字典的key/value如下:
 *
 *share_id/NSString *  分享id
 *valid/NSNumber *
 *alias/NSString *    昵称
 *user/NSString *     登录名
 *pwd/NSString *      登录密码
 *cover_url/NSString * 预览图url
 *recent/NSNumber *(Long)
 */
-(NSArray *)get_collections_list;//获取收藏的所有cams
/*
 *返回一个字典，字典的key/value如下:
 *
 *share_id/NSString *  分享id
 *valid/NSNumber *
 *alias/NSString *    昵称
 *user/NSString *     登录名
 *pwd/NSString *      登录密码
 *cover_url/NSString * 预览图url
 *recent/NSNumber *(Long)
 */
-(NSDictionary *)get_collection:(NSString *)share_id;//获取单个收藏的cam
示例：
NSArray * collections_list = [[Storage get_share] get_collections_list];


2）比较
说明：把从服务器上获取到的收藏摄像机和当前账号本地收藏的cams做比较,如果一样返回Yes,如果不一样，此函数把服务器上的和本地的做同步，且返回No
函数：
-(BOOL)merge_collections_list:(NSArray *)server_collections_list;
返回：返回BOOL值，YES:服务器上收藏的cams和本地收藏的cams一样。NO:服务器上收藏的cams和本地收藏的cams不一样。
示例：
[storage merge_collections_list:[webservice get_collections_list]];

3）添加
说明：适用此函数，把添加的摄像机，添加存储到本地。
函数：
-(BOOL)add_collection:(NSString *)share_id
alias:(NSString *)alias
cover_url:(NSString *)cover_url;
参数：
share_id：分享id
alias：昵称
cover_url：预览图url
返回：返回一个BOOL值，YES:添加收藏到本地成功。NO:添加收藏到本地失败
示例：
[[Storage get_share] add_collection:m_share_id alias:alias cover_url:cover_url];

4）删除
说明：从本地指定删除收藏的一个摄像机
函数：
-(void)remove_collection:(NSString *)share_id;
参数：share_id：即将被删除的收藏摄像机share_id
示例：
[[Storage get_share] remove_collection:m_share_id];


5）更新
说明：以下函数用来更新本地收藏的摄像机信息
函数：
/*
 *更新本地收藏摄像机的登录名
 *share_id:要被更新的收藏摄像机分享id
 *valid:收藏摄像机的是否有效
 */
-(void)update_collection_valid:(NSString *)share_id
valid:(BOOL)valid;

/*
 *更新本地收藏摄像机的登录名
 *share_id:要被更新的收藏摄像机分享id
 *user:收藏摄像机的user本地更新为user
 */
-(void)update_collection_user:(NSString *)share_id
user:(NSString *)user;

/*
 *更新本地收藏摄像机的登录名
 *share_id:要被更新的收藏摄像机分享id
 *pwd:收藏摄像机的pwd本地更新为pwd
 */

-(void)update_collection_pwd:(NSString *)share_id
pwd:(NSString *)pwd;

示例：
[[Storage get_share] update_collection_pwd:share_id pwd:new_pwd]

#pragma mark 4.本地录像和图片 <获取文件／删除>

4.本地录像和图片
说明：适用以下函数，必须是适用了账号登录，即m_user_id不为空。
1）获取摄像机的拍照和录像文件
说明：此函数可以获取指定摄像机的所有拍照和录像文件
-(NSMutableArray *)get_album:(NSString *)camera_id;
参数：camera_id:摄像机id
返回：返回一个NSMutableArray，数组的每一个元素是一个字典，字典的key/value如下:
time/NSDate *    //时间NSDate
size/NSNumber * /long long  // 文件大小
type/NSNumber * /int //文件类型，两个值，0:图片 1:录像
path/NSString *    //文件路径

示例：
NSArray * album = [storage get_album:[ipcam camera_id]];

2）删除
说明：删除指定摄像机的文件
函数：
/*
 *删除指定摄像机的所有的录像和拍照文件
 *参数：camera_id:摄像机id
 */
-(void)remove_album:(NSString *)camera_id;//删除所有文件

/*
 *删除指定摄像机的指定的录像或拍照文件
 *参数：camera_id:摄像机id
 */
-(void)remove_album_item:(NSString *)path; //删除某一个文件

示例：

[[Storage get_share] remove_album:[ipcam camera_id]];//删除所有文件

[[Storage get_share] remove_album_item:[item objectForKey:@"path"]];//删除某一个文件

#pragma mark5.报警图片本地缓存<添加／获取>
5.报警图片本地缓存
说明：报警图片本地缓存是指：把图片picture保存缓存在本地，路径是NSTemporaryDirectory而不是NSHomeDirectory
注意：必须要设置了当前账号，因为缓存路径包括账号

函数：
/*
 *Storage方法：添加图片到缓存
 *参数：
 *camera_id:摄像机id
 *alarm_id:报警信息id,就是on_get_camera_alarms_list_result返回的alarm_id
 *index:第几张图片，就是on_get_image_result返回的image_id的intValue.或根据
 *picture:图片数据
 */
-(void)add_alarm_picture:(NSString *)camera_id
alarm_id:(NSString *)alarm_id
index:(int)index
picture:(NSData *)picture;

/*
 *Storage方法：从缓存中取出图片
 *参数：
 *camera_id:摄像机id
 *alarm_id:报警信息id,就是on_get_camera_alarms_list_result返回的alarm_id
 *index:第几张图片，就是on_get_image_result返回的image_id的intValue
 */
-(NSData *)get_alarm_picture:(NSString *)camera_id
alarm_id:(NSString *)alarm_id
index:(int)index;

示例：
[[Storage get_share] add_alarm_picture:m_camera_id alarm_id:m_alarm_id index:index picture:data];
