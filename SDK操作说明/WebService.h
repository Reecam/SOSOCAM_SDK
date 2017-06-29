
WebService类 用于和平台打交道
#pragma mark 7.1用户管理 <注册／忘记密码／登录／激活／账号信息>

7.1用户管理
说明：当用到用户的时候才使用WebService类，在使用WebService前，必须先初始化（[WebService get_share];），不用了也必须反初始化（[WebService release_share];），初始化和反初始化是成对调用的

7.1.1注册新用户
说明：如果没有用户，先注册一个用户，注册用户是直接打开一个连接即可，其他由网页那边去实现
函数：-(NSString *)get_new_user_url;//获取注册新用户连接
示列：
/* WebViewController是一个vc,vc上面添加了一个UIWebView*/
- (void)button_new_user_onclick:(id)sender {
    WebViewController *web_vc = [[WebViewController alloc] init];
    [self presentViewController:web_vc animated:YES completion:nil];
    NSString * url = [[WebService get_share]get_new_user_url];//获取注册用户链接
    [web_vc open:url];//打开链接
}

7.1.2忘记密码
说明：如果忘记密码了，直接打开一个连接即可，其他由网页那边去实现
函数：-(NSString *)get_forget_password_url;//获取忘记密码连接
示列：
/* WebViewController是一个vc,vc上面添加了一个UIWebView*/
- (void)button_forget_pwd_onclick:(id)sender {
    WebViewController *web_vc = [[WebViewController alloc] init];
    [self presentViewController:web_vc animated:YES completion:nil];
    NSString * url = [[WebService get_share]get_forget_password_url]; //获取忘记密码链接
    [web_vc open:url]; //打开链接
}


7.1.3三种登录方式
1）账号登录
说明：普通账号登录
函数：	-(NSString *)get_vetification_code_image_url;//获取验证码连接，用UIWebView打开
-(WEBSERVICE_ERROR)login_with_account:(NSString *)user
pwd:(NSString *)pwd
vertification_code:(NSString *)vertification_code
exit_on_failed:(BOOL)exit_on_failed;//账号用户登录

参数：user:账号名
pwd:账号密码
vertification_code:验证码，不需要验证码时是@“”
exit_on_failed：失败后是否退出 如果设置Yes，失败后就直接退出;如果设置为No,当登录失败因为是error:WEBSERVICE_ERROR_NETWORK_ERROR，会继续尝试登录.
示列：

/*获取验证码 若不需要的先直接跳过*/
 - (IBAction)webview_vertification_ontap:(id)sender {
 
 UIWebView *m_webview_vertification;
 [m_webview_vertification loadRequest: [ NSURLRequest requestWithURL:[NSURL URLWithString: [[WebService get_share] get_vetification_code_image_url]] cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:5.0 ]];
 }
 
 -(void)login_with_account
 {
 if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] login_with_account:m_text_username.text pwd:m_text_userpwd.text vertification_code:m_view_vertification_layout.hidden?@"":m_text_vertification.text exit_on_failed:YES]) {
 return;
 }
 
 m_auth_type = ACCOUNT_USER;
 m_auth_id = m_text_username.text;
 m_auth_token = m_text_userpwd.text;
 NSLog(@"login success!");
 }

 2）第三方登录
 说明：第三方登录，先要去第三方去申请，然后添加第三方插件，reecam采用的是ShareSdk
 函数：-(WEBSERVICE_ERROR)login_with_oauth:(WEBSERVICE_LOGIN_TYPE)type
 open_id:(NSString *)open_id
 access_token:(NSString *)access_token
 exit_on_failed:(BOOL)exit_on_failed;//第三方登录
 参数：open_id：
 access_token:
 exit_on_failed：失败后是否退出 如果设置Yes，失败后就直接退出，
 如果设置为No,当登录失败是因为error：WEBSERVICE_ERROR_NETWORK_ERROR，会继续尝试登录
 示列：

 - (void)button_fb_onclick:(id)sender {
 SSDKGetUserStateChangedHandler onStateChangedHandler = ^ (SSDKResponseState state, SSDKUser *user, NSError *error) {
 if (state == SSDKResponseStateSuccess) {
 if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] login_with_oauth:WEBSERVICE_LOGIN_TYPE_FACEBOOK open_id:user.credential.uid access_token:user.credential.token exit_on_failed:YES]) {
 return;}
 m_auth_type = FACEBOOK_USER;
 m_auth_id = user.credential.uid;
 m_auth_token = user.credential.token;
 NSLog(@"login success!");
 }
 };
 
 [ShareSDK authorize:SSDKPlatformTypeFacebook
 settings:@{SSDKAuthSettingKeyScopes : @[@"user_likes",
 @"user_about_me",
 @"user_birthday",
 @"user_education_history",
 @"email",
 @"user_hometown",
 @"user_relationship_details",
 @"user_location",
 @"user_religion_politics",
 @"user_website",
 @"user_work_history",
 @"user_photos",
 @"publish_actions",]}
 onStateChanged:onStateChangedHandler];
 }

 - (void)button_qq_onclick:(id)sender {
	SSDKGetUserStateChangedHandler onStateChangedHandler = ^ (SSDKResponseState state, SSDKUser *user, NSError *error)
 {
 if (state == SSDKResponseStateSuccess)
 {
 if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] login_with_oauth:WEBSERVICE_LOGIN_TYPE_QQ open_id:user.credential.uid access_token:user.credential.token exit_on_failed:YES]){
 return;
 }
 m_auth_type = QQ_USER;
 m_auth_id = @"";
 m_auth_token = @"";
 
 NSLog(@"login success!");
 };
 
 [ShareSDK authorize:SSDKPlatformTypeQQ
 settings:@{SSDKAuthSettingKeyScopes : @[@"all"]}
 onStateChanged:onStateChangedHandler];
 }

 3)网页qq登录
 说明：也是一种第三方登录，此登录主要是针对iPhone没有安装qq，这种登录也要去第三方申请认证，加载第三方插件
 函数：
 -(NSString *)get_web_qq_login_url;//获取网页qq登录连接
 -(WEBSERVICE_ERROR)login_with_web_qq:(NSString *)session_id
 exit_on_failed:(BOOL)exit_on_failed; //网页qq登录
 
 示列：
 /*打开qq网页登录页面，WebViewController是一个vc vc上加了一个UIWebView*/
- (void)button_qq_onclick:(id)sender {
    
    if (![QQApi isQQInstalled]) {
        WebViewController *web_vc = [[WebViewController alloc] init];
        web_vc.delegate = self;
        [self presentViewController:web_vc animated:YES completion:nil];
        NSString * url = [ [WebService get_share]get_web_qq_login_url];
        [web_vc open:url];
    }
}

/*打开成功后获取到session_id，然后回调开始登录*/
- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType

{
    NSString* strURL = request.URL.absoluteString;
    NSString* QQ_Login = @"SessionId=";
    NSRange range_session_id = [strURL rangeOfString:QQ_Login options:NSCaseInsensitiveSearch ];
    if( range_session_id.location != NSNotFound )
    {
        NSString* m_session_id = [strURL substringFromIndex: range_session_id.location + range_session_id.length ];
        if (_delegate) {
            [self dismissViewControllerAnimated:YES completion:^{
                [_delegate on_web_qq_login_succeed:m_session_id];
            }];
        }
    }
    return YES;
}
/*开始网页qq登录*/
-(void)on_web_qq_login_succeed:(NSString*)ssid;
{
    if (ssid) {
        if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share]login_with_web_qq:ssid exit_on_failed:NO])
        {
            m_auth_type = WEB_QQ_USER;
            m_auth_id = @"";
            m_auth_token = @"";
            NSLog(@"login success!");
        }
    }
}


7.1.4登录状态监控和异常处理
说明：一般登录会先添加代理，来监控登录状态的改变，当监控到登录的状态是WEBSERVICE_LOGIN_STATUS_IDLE时，才去获取错误值，根据不同错误值做不同处理（主要是帐户未激活／用户名或密码错误需要重试／账号被锁），这些是息息相关的，此处先分别介绍，最后一起举列。
1）登录代理
说明：使用用户管理，在使用前添加登录代理，能实时监控登录状态的改变，不再需要监控用户状态时必须删除代理
函数：-(void)add_login_delegate:(id<WebServiceLoginDelegate>)delegate;//添加登录代理
-(void)remove_login_delegate:(id<WebServiceLoginDelegate>)delegate;//删除登录代理
-(void)on_login_status_changed;//登录代理
2）登录状态
说明：此函数一般在登录代理函数中使用，每次登录状态有改变时，就实时获取当前登录状态，做出相应处理。共有三种登录状态，如下：
typedef enum {
    WEBSERVICE_LOGIN_STATUS_IDLE, //登录失败
    WEBSERVICE_LOGIN_STATUS_LOGGING_IN,//登录中
    WEBSERVICE_LOGIN_STATUS_LOGGED_ON,//登录成功
} WEBSERVICE_LOGIN_STATUS;
函数：-(WEBSERVICE_LOGIN_STATUS)get_login_status; //账号登录状态

3）错误值
说明：此函数一般当监控到登录的状态是WEBSERVICE_LOGIN_STATUS_IDLE时，才去获取错误值，根据不同的错误值做出相应处理。共有6种错误值（注释掉的错误，表示此处不用），如下：
typedef enum {
    WEBSERVICE_ERROR_NO_ERROR,//没有错误，表示登录成功
    //WEBSERVICE_ERROR_BAD_STATUS,
    WEBSERVICE_ERROR_NETWORK_ERROR,//网络错误
    WEBSERVICE_ERROR_SVR_ERROR,//服务器错误
    WEBSERVICE_ERROR_BAD_AUTH,//认证错误（用户名或密码错误）
    WEBSERVICE_ERROR_NEED_VERTIFICATION,//验证码错误
    WEBSERVICE_ERROR_NO_ACTIVATED,//账号未激活
    //WEBSERVICE_ERROR_REGISTERED_BY_OTHERS,
    //WEBSERVICE_ERROR_INVALID_SHARE_ID,
    //WEBSERVICE_ERROR_SHARE_ID_EXISTS,
} WEBSERVICE_ERROR;

函数：-(WEBSERVICE_ERROR)get_error; //账号登录错误

4）账号未激活
说明：当获取的错误值为WEBSERVICE_ERROR_NO_ACTIVATED时，才能去做激活处理，获取激活账号类型和激活码和激活链接打开激活链接页面即可，后面的就交给网页去处理
函数：-(NSString *)get_activate_user_type;//激活账号的类型 -(NSString*)get_activate_url函数内部使用
-(NSString *)get_activate_auth_code ; //账号激活码 -(NSString*)get_activate_url函数内部使用
-(NSString*)get_activate_url//获取激活连接
5）用户名或密码或验证码错误
说明：当获取的错误值是WEBSERVICE_ERROR_BAD_AUTH时，首先获取账号是否被锁（最多重试5次，不包含验证码错误），如果没有被锁，当剩下重试次数为4次时（即返回一次错误后开始开启验证码验证功能，这个功能可以根据自己的需求定，不一定是剩下四次也不一定非要用验证码），开启验证码登录验证
函数：-(BOOL)get_badauth_locked;//账号是否被锁

-(int)get_badauth_retry_times;//账号登录剩下允许重试的次数
示列：
[[WebService get_share] add_login_delegate:self]; //添加登录代理
/*监控登录状态，根据不同状态 做出相应处理*/
-(void)on_login_status_changed{
    WebService * webservice = [WebService get_share];
    WEBSERVICE_LOGIN_STATUS status = [webservice get_login_status];
    if (status == WEBSERVICE_LOGIN_STATUS_LOGGING_IN) {
        /*登录中，在此处做相应处理*/
        NSLog(@"logining");
    } else if (status == WEBSERVICE_LOGIN_STATUS_LOGGED_ON) {
        /*登录成功，在此处做相应处理*/
        NSLog(@"login success!");
    } else if (status == WEBSERVICE_LOGIN_STATUS_IDLE) {
        /*登录成功，根据不同错误值做不同处理*/
        WEBSERVICE_ERROR error = [webservice get_error];//获取错误值
        if (error == WEBSERVICE_ERROR_BAD_AUTH) {
            /*错误值为认证错误（用户名或密码错误）*/
            if ([webservice get_badauth_locked]) {
                /*获取到账号已经被锁住了，在此处做相应处理*/
                NSLog(@"account already lock!");
            }
            else {
                /*账号还未锁定，获取验证码和剩余重试次数，在此处做相应处理*/
                [m_webview_vertification loadRequest: [ NSURLRequest requestWithURL:[NSURL URLWithString: [webservice get_vetification_code_image_url]] cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:5.0 ]];//获取验证码
                NSLog(@"you can try %d times",[webservice get_badauth_retry_times]);//获取剩余重试数
            }
        } else if (error == WEBSERVICE_ERROR_NEED_VERTIFICATION) {
            /*错误值为验证码错误 重新获取验证码*/
            NSLog(@"vertification error! ");
            [m_webview_vertification loadRequest: [ NSURLRequest requestWithURL:[NSURL URLWithString: [webservice get_vetification_code_image_url]] cachePolicy:NSURLRequestReloadIgnoringLocalCacheData timeoutInterval:5.0 ]];
        } else if (error == WEBSERVICE_ERROR_NO_ACTIVATED) {
            /*错误值为未激活账号*/
            NSLog(@"account not activated! ");
            WebViewController *web_vc = [[WebViewController alloc] init];
            [self presentViewController:web_vc animated:YES completion:nil];
            NSString * url = [[WebService get_share]get_activate_url];//获取激活链接
            [web_vc open:url];//打开激活页面
        } else {
            /* 其他错误值*/
            NSLog(@"network error!");
        }
    }
}
[[WebService get_share] remove_login_delegate:self];//删除代理

7.1.5 登录成功获取到相关信息
说明：只有登录成功了，[[WebService get_share] get_login_status] == WEBSERVICE_LOGIN_STATUS_LOGGED_ON，才能获取到以下相关信息，否则获取到的是空值
1)获取当前账号用户id
函数：-(NSString *)get_user_id;//获取当前用户user_id
示列：NSString * current_user_id = [[WebService get_share]get_user_id];
2)获取当前账号用户别名
函数：-(NSString *)get_user_alias;//获取当前用户名称
示列：NSString * current_user_alias = [[WebService get_share]get_user_alias];

3)获取当前账号连接，用来管理此用户
函数：-(NSString *)get_current_user_info_url;//获取当前账号信息连接
示列：
- (void)button_user_setting_onclick:(id)sender {
    NSString * url = [[WebService get_share]get_current_user_info_url];
    if (！[url isEqualToString:@""]) {
        if ([[Util check_language] isEqualToString:@""])
            url = [url stringByAppendingString:@"&lng=zh_cn"]; //中文显示
            else
                url = [url stringByAppendingString:@"&lng=en"];//英文显示
                WebViewController * user_setting_vc = [[WebViewController alloc] init];
                [self presentViewController:user_setting_vc animated:YES completion:nil];
        [user_setting_vc open:url];
    }
}

4）获取当前摄像机
说明：从服务器上获取当前账号的摄像机列表，返回一个数组，数组的每一个元素是一个字典，一般用不和本地存储的摄像机做比较用，字典key/value如下：
//  camera_id/NSString *
//  sosocam_camera_id/NSString *
//  alias/NSString *
//  https/NSNumber */BOOL
//  user/NSString *
//  pwd/NSString *
//  model/NSNumber */int32_t

函数：-(NSArray *)get_cameras_list;//当前账号里添加的摄像机
示列：
NSArray * arry_svr_cams = [[WebService get_share] get_cameras_list];//从服务器上获取当前账号添加的cams
[[Storage get_share] merge_cameras_list:arry_svr_cams]; //服务器上获取到的摄像机和当前账号本地的cams做比较,如果一样返回Yes,如果不一样，此函数把服务器上的和本地的做同步，且返回No
/*一般如果返回No的话，都会先把IPCamMgr的所有摄像机清除，然后再从本地获取cams重新添加到IPCamMgr*/
[[IPCamMgr get_share] clear_cameras_list];//清除IPCamMgr所有的cams

NSArray * cameras_list = [[Storage get_share] get_cameras_list];//获取本地cams
IPCamMgr * ipcammgr = [IPCamMgr get_share];
NSDictionary * camera;
IPCam * ipcam;
int i;
for (i = 0;i < cameras_list.count;i ++) {
    camera = [cameras_list objectAtIndex:i];
    ipcam = [ipcammgr add_camera:[camera objectForKey:@"camera_id"] alias:[camera objectForKey:@"alias"] user:[camera objectForKey:@"user"] pwd:[camera objectForKey:@"pwd"] https:[[camera objectForKey:@"https"] boolValue]];//逐一添加cam到IPCamMgr
}

5）获取当前账号收藏摄像机
说明：从服务器上获取当前账号返回一个数组，数组的每一个元素是一个字典，，key/value如下：
//  share_id/NSString *
//  alias/NSString *
//  cover_url/NSString *
函数：-(NSArray *)get_collections_list;//当前账号收藏的摄像机
示列：
NSArray * arry_svr_collections = [[WebService get_share]get_collections_list];//从服务器上获取当前账号收藏的cams
[[Storage get_share] merge_collections_list:arry_svr_collections]; //服务器上获取到的摄像机和当前账号本地的cams做比较,如果一样返回Yes,如果不一样，此函数把服务器的和本地的做同步，且返回No

7.1.6注销账号
说明：需要退出账号时，使用次函数，当然app的页面根据自己需求也要做相应处理
函数：-(void)logout;//注销账号登录
示列：
- (IBAction)button_logout_onclick:(id)sender {
    [[WebService get_share] logout];//退出账号
    [g_app show_login_view];//页面做相应处理，根据自己需求自定义
}
     
#pragma mark 7.2服务器摄像机管理<添加／更新／删除／>
7.2服务器摄像机管理
7.2.1服务器上添加摄像机
说明：添加成功后，一般都要同步添加到Storage，再添加到IPCamMgr才能管理新添加的cam
函数：
-(void)on_add_camera_result:(WEBSERVICE_ERROR)error
sosocam_camera_id:(NSString *)sosocam_camera_id;//代理WebServiceAddCameraDelegate

-(WEBSERVICE_ERROR)add_camera:(NSString *)camera_id
alias:(NSString *)alias
https:(BOOL)https
model:(int32_t)model
delegate:(id<WebServiceAddCameraDelegate>)delegate;//添加摄像机到服务器
示列：
-(void)add_camera_to_server
{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                                                  alias:m_camera_name
                                                                  https:[m_ipcam https]
                                                                  model:[m_ipcam model]
                                                               delegate:self]) {
        NSLog(@"add fail!");
    } else {
        NSLog(@"add success!");
    }
}

-(void)on_add_camera_result:(WEBSERVICE_ERROR)error
sosocam_camera_id:(NSString *)sosocam_camera_id
{
    if (WEBSERVICE_ERROR_NO_ERROR == error) {
        [[Storage get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                  alias:m_camera_name
                                   user:@"admin"
                                    pwd:[m_ipcam pwd]
                                  https:[m_ipcam https]
                             sosocam_id:sosocam_camera_id
                                  model:[m_ipcam model]
                                 master:NO];
        IPCam * ipcam = [[IPCamMgr get_share] add_camera:[m_camera objectForKey:@"camera_id"]
                                                   alias:m_camera_name
                                                    user:@"admin"
                                                     pwd:[m_ipcam pwd]
                                                   https:[m_ipcam https]];    }
    else if (WEBSERVICE_ERROR_REGISTERED_BY_OTHERS == error) {
        NSLog(@"the camera already add to other user!");
    }
    else {
        NSLog(@"add camera to service fail!");
    }
}

7.2.2服务器上更新摄像机名称
说明：更新成功后，一般都要同步添加到Storage
函数：-(void)on_update_camera_alias_result:(WEBSERVICE_ERROR)error;//更新代理WebServiceUpdateCameraAliasDelegate

-(WEBSERVICE_ERROR)update_camera_alias:(NSString *)sosocam_camera_id
alias:(NSString *)alias
delegate:(id<WebServiceUpdateCameraAliasDelegate>)delegate;//更新名称到服务器上
示列:
-(void) update_name_to_server {
    if (WEBSERVICE_ERROR_NO_ERROR !=
        [[WebService get_share] update_camera_alias:[m_ipcam sosocam_id] alias:m_camera_name delegate:self]) {
        NSLog(@"update name to service fail!");
    } else {
        NSLog(@"update name to service!");
    }
}
-(void)on_update_camera_alias_result:(WEBSERVICE_ERROR)error {
    if (WEBSERVICE_ERROR_NO_ERROR == error) {
        [[Storage get_share] update_camera_alias:[m_ipcam camera_id] alias:m_camera_name];
    } else {
        NSLog(@"update name to service fail!");
    }
}


7.2.3服务器上删除摄像机
说明：删除成功后，一般都要去Storage删除此cam，再到IPCamMgr删除此cam
函数：-(void)on_remove_camera_result:(WEBSERVICE_ERROR)error;//删除WebServiceRemoveCameraDelegate
-(WEBSERVICE_ERROR)remove_camera:(NSString *)sosocam_camera_id
delegate:(id<WebServiceRemoveCameraDelegate>)delegate;
示列：
-(void)delete_server
{
    if (WEBSERVICE_ERROR_NO_ERROR != [[WebService get_share] remove_camera:m_sosocam_camera_id delegate:self]) {
        NSLog(@"remove camera from service fail!");
    }
}

-(void)on_remove_camera_result:(WEBSERVICE_ERROR)error
{
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        [[Storage get_share] remove_camera:m_camera_id];
        [[IPCamMgr get_share] remove_camera:m_camera_id];
        NSLog(@"remove camera from service success!");
    } else {
        NSLog(@"remove camera from service fail!");
    }
}
#pragma mark 7.3服务器报警信息管理<获取cams/cam报警信息>

7.3服务器报警信息管理
7.3.1服务器上获取cams报警信息
1）执行获取动作
说明：获取cams报警信息，且添加代理，如果不是返回WEBSERVICE_ERROR_NO_ERROR 说明获取失败
函数：-(WEBSERVICE_ERROR)get_alarm_cameras_list:(id<WebServiceGetAlarmCamerasListDelegate>)delegate;

2）获取到结果后掉用代理
说明：代理返回两个参数，WEBSERVICE_ERROR类型error值，error == WEBSERVICE_ERROR_NO_ERROR表示获取成功；
另一个是一个数组alarm_cameras_list，数组的每个元素是一个NSDictionary，key/value对应值如下：
sosocam_camera_id/NSString *//摄像机sosocam_id
camera_id/NSString * //摄像机id
unread/NSNumber */int //已查看报警数目
total/NSNumber */int  //报警总数目
函数：-(void)on_get_alarm_cameras_list_result:(WEBSERVICE_ERROR)error
alarm_cameras_list:(NSArray *)alarm_cameras_list;
示列：

[[WebService get_share] get_alarm_cameras_list:self];//获取cams报警信息且添加代理 如果不是返回WEBSERVICE_ERROR_NO_ERROR 说明获取失败

/*获取到结果后就会掉用代理，当代理中返回error == WEBSERVICE_ERROR_NO_ERROR表示获取成功*/
-(void)on_get_alarm_cameras_list_result:(WEBSERVICE_ERROR)error
alarm_cameras_list:(NSArray *)alarm_cameras_list
{
    NSMutableDictionary * camera;
    NSDictionary * server_camera;
    if (error == WEBSERVICE_ERROR_NO_ERROR) {
        int i, j;
        for (i = 0;i < m_cameras_list.count;i ++) {
            camera = [m_cameras_list objectAtIndex:i];//m_cameras_list从storage获取
            for (j = 0;j < alarm_cameras_list.count;j ++) {
                server_camera = [alarm_cameras_list objectAtIndex:j];
                if ([[camera objectForKey:@"camera_id"] isEqualToString:[server_camera objectForKey:@"camera_id"]]) {
                    [camera setValue:[server_camera objectForKey:@"sosocam_camera_id"] forKey:@"sosocam_camera_id"];
                    [camera setValue:[server_camera objectForKey:@"total"] forKey:@"total"];
                    [camera setValue:[server_camera objectForKey:@"unread"] forKey:@"unread"];
                    break;
                }
            }
        }
    }
}


7.3.2服务器上获取单个cam报警信息
1）
-(WEBSERVICE_ERROR)get_camera_alarms_list:(NSString *)sosocam_camera_id
delegate:(id<WebServiceGetCameraAlarmsListDelegate>)delegate;

@protocol WebServiceGetCameraAlarmsListDelegate
//  every element in camera_alarms_list passed is type of NSDictionary
//  key/value:
//  alarm_id/NSString *
//  alarm_type/NSNumber */(int32_t)
//  image_numbers/NSNumber */(int)
//  read/NSNumber */(BOOL)
//  time/NSDate *
//  thumb_url/NSString *
-(void)on_get_camera_alarms_list_result:(WEBSERVICE_ERROR)error
                     camera_alarms_list:(NSArray *)camera_alarms_list;

2）
-(WEBSERVICE_ERROR)get_alarm_images_list:(NSString *)alarm_id
                                delegate:(id<WebServiceGetAlarmImagesListDelegate>)delegate;
@protocol WebServiceGetAlarmImagesListDelegate
//  every element in alarm_images_list passed is type of NSDictionary
//  key/value:
//  time/NSDate *
//  url/NSString *
-(void)on_get_alarm_images_list_result:(WEBSERVICE_ERROR)error
                     alarm_images_list:(NSArray *)alarm_images_list;


-(void)cancel_get_alarm_images_list_tasks;
3）
-(void)get_alarm_image:(NSString *)image_id
                   url:(NSString *)url
              delegate:(id<WebServiceGetImageDelegate>)delegate;

-(void)on_get_image_result:(NSString *)image_id
                      data:(NSData *)data;


-(void)cancel_get_alarm_image_tasks;
     
     
     
#pragma mark 7.4分享和收藏<删除／添加>
7.4分享和收藏<删除／添加>
1)开启分享
/*
 *开启分享
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *delegate:代理WebServiceShareCameraDelegate
 */
-(WEBSERVICE_ERROR)share_camera:(NSString *)sosocam_camera_id
                       delegate:(id<WebServiceShareCameraDelegate>)delegate;
     
/*
 *WebServiceShareCameraDelegate回调
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 *share_id:分享的id
 *share_url:分享的url
 *share_qrcode:分享的二维码
 */
-(void)on_share_camera_result:(WEBSERVICE_ERROR)error
 share_id:(NSString *)share_id
 share_url:(NSString *)share_url
 share_qrcode:(NSString *)share_qrcode;
     
     
     
2）关闭分享
/*
 *关闭分享
 *参数：
 *sosocam_camera_id:摄像机sosocam_id
 *delegate：代理WebServiceDisshareCameraDelegate
 */
-(WEBSERVICE_ERROR)disshare_camera:(NSString *)sosocam_camera_id
                          delegate:(id<WebServiceDisshareCameraDelegate>)delegate;
/*
 *WebServiceDisshareCameraDelegate回掉
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
*/
-(void)on_disshare_camera_result:(WEBSERVICE_ERROR)error;
     
     
3)获取分享摄像机信息
     
/*
 *获取收藏摄像机
 */
-(WEBSERVICE_ERROR)get_collection_camera:(NSString *)share_id
                                delegate:(id<WebServiceGetCollectionCameraDelegate>)delegate;
/*
 *WebServiceGetCollectionDelegate代理回调
 *参数：
 *error:错误值
 当error=IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 当 error=WEBSERVICE_ERROR_INVALID_SHARE_ID ，说明分享关闭，已为无效分享
 *camera_id:摄像机id
 *https:摄像机加密值
 */
-(void)on_get_collection_camera_result:(WEBSERVICE_ERROR)error
 camera_id:(NSString *)camera_id
 https:(BOOL)https;


4）添加（收藏）分享的摄像机（服务器）
/*
 *账号添加分享的摄像机：即添加到服务器和本地
 *参数：
 *share_id:摄像机分享id号
 *delegate：代理WebServiceAddCollectionDelegate
 */
-(WEBSERVICE_ERROR)add_collection:(NSString *)share_id
                         delegate:(id<WebServiceAddCollectionDelegate>)delegate;
     
/*
 *WebServiceAddCollectionDelegate代理回调
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 *alias:摄像机别名
 *cover_url：摄像机预览图
 */
-(void)on_add_collection_result:(WEBSERVICE_ERROR)error
 alias:(NSString *)alias
 cover_url:(NSString *)cover_url;
 
5）获取收藏摄像机信息（基本用于本地添加收藏）
/*
 *获取收藏摄像机信息
 *参数：
 *share_id：分享id
 *delegate:WebServiceGetCollectionDelegate代理
 */
-(WEBSERVICE_ERROR)get_collection:(NSString *)share_id
 delegate:(id<WebServiceGetCollectionDelegate>)delegate;
/*
 *WebServiceGetCollectionDelegate代理回调
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明开启分享成功
 *alias:摄像机别名
 *cover_url：摄像机预览图
 */
-(void)on_get_collection_result:(WEBSERVICE_ERROR)error
 alias:(NSString *)alias
 cover_url:(NSString *)cover_url;
     
6）删除收藏摄像机机
/*
 *删除收藏的摄像机
 *参数：
 *share_id:分享id
 *delegate:代理WebServiceRemoveCollectionDelegate
 */
-(WEBSERVICE_ERROR)remove_collection:(NSString *)share_id
                            delegate:(id<WebServiceRemoveCollectionDelegate>)delegate;
/*
 *WebServiceRemoveCollectionDelegate代理回调函数
 *参数：
 *error:错误值，当错误值为IPCAM_ERROR_NO_ERROR时，说明删除成功
 */
-(void)on_remove_collection_result:(WEBSERVICE_ERROR)error;
     

7）获取收藏的摄像机（服务器）
/*
 *从服务器获取账号收藏的摄像机
 *返回:返回一个NSArray，NSArray的每一个元素师一个字典，key/value如下：
 *share_id：分享id
 *alias：别名
 *cover_url:预览图的连接
 */
-(NSArray *)get_collections_list;
     


     

#pragma mark 7.5新版本更新（app和fw）

7.5新版本更新（app和fw）
7.5.1
-(void)check_latest_camera_fw:(NSString *)current_version
                     delegate:(id<WebServiceCheckLatestVersionDelegate>)delegate;
7.5.2
-(void)check_latest_app_version_delegate:(id<WebServiceCheckLatestAppVersionDelegate>)delegate;


#pragma mark - 7.6 新版本更新接口/方法
     
7.6.1
/**
 使用瑞彩之外的服务器，请在程序启动时执行。即 AppDelegate 中， 不写，默认使用瑞彩服务器

 @param check_latest_version_url_head     检测固件版本更新url
 @param client_webservice_url_head        客户端服务器url
 @param current_user_info_url_head        用户信息url
 @param client_forget_password_url_head   忘记密码url
 @param client_new_user_url_head          新建用户url
 @param client_activate_url_head          激活账户url
 @param client_vetification_code_url_head 客户端验证码url
 @param client_web_qq_login_url_head      web QQ登录url
 */
+(void)set_url_head:(NSString *)check_latest_version_url_head
 client_webservice_url_head:(NSString *)client_webservice_url_head
 current_user_info_url_head:(NSString *)current_user_info_url_head
 client_forget_password_url_head:(NSString *)client_forget_password_url_head
 client_new_user_url_head:(NSString *)client_new_user_url_head
 client_activate_url_head:(NSString *)client_activate_url_head
 client_vetification_code_url_head:(NSString *)client_vetification_code_url_head
 client_web_qq_login_url_head:(NSString *)client_web_qq_login_url_head;
     

/**
 设置客户端ID  默认值：1

 @param client_id 客户端ID
 */
+(void)set_client_id:(int)client_id;





